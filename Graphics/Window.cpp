#include "Window.h"
#include <iostream>

#define OPEN_GL_MAJOR 4
#define OPEN_GL_MINOR 3
#define CORE_PROFILE GLFW_OPENGL_CORE_PROFILE



static int InitGLFW() {
	glfwInit();
	return 0;
}

void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}

//JIT initialization of glfw-must be the first action before any window creation
static int init = InitGLFW();

int Window::monitorCount = 0;
int Window::winCount = 0;
GLFWmonitor** Window::monitors = glfwGetMonitors(&Window::monitorCount);


void Window::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		break;

	default:
		return;
	}
}
 void Window::Framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static std::string MonitorType2Str(MonitorType monitor) {
	switch (monitor) {
	case MonitorType::PRIMARY:
		return "Primary";
	case MonitorType::SECONDARY:
		return "Secondary";
	case MonitorType::THIRD:
		return "Third";
	case MonitorType::FOURTH:
		return "Fourth";
	default:
		return std::string();

	}
}

bool Window::IsMonitorAvailable(MonitorType monitor) {
	return (int)monitor + 1 <= monitorCount;
}

GLFWwindow* Window::GetWindowHandler()
{
	return windowHandler;
}


Window::Window(const char* windowName, int width, int height, WindowPtr parent, MonitorType monitor) :
	windowHandler(nullptr),
	windowName(windowName),
	windowWidth(width),
	windowHeight(height),
	windowParent(parent),
	windowMonitor(monitor),
	valid(false)
{
	GLFWwindow* p = nullptr;

	if (windowParent != nullptr) {
		p = windowParent->GetWindowHandler();
	}
	//check if monitor is available if not we assign primary as default, if DONT_CARE is passed we won't assign a monitor(no full screen either)
	if (monitor != MonitorType::DONT_CARE && !IsMonitorAvailable(monitor)) {
		std::cout << MonitorType2Str(windowMonitor) << " not available! Assigning to Primary!" << std::endl;
		windowMonitor = MonitorType::PRIMARY;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, CORE_PROFILE);
	//glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	//glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
	//glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);


	windowHandler = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, p);
	if (windowHandler == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		//glfwTerminate();
	}

	if (monitor != MonitorType::DONT_CARE && !AttachWindowToMonitor(windowMonitor, windowWidth, windowHeight)) {
		std::cout << "Failed to attach GLFW window to Monitor" << std::endl;
		//glfwTerminate();
	}

	glfwMakeContextCurrent(windowHandler);
	//set callback to window in case of resize
	glfwSetFramebufferSizeCallback(windowHandler, &Window::Framebuffer_size_callback);
	glfwSetWindowSizeCallback(windowHandler, &Window::Framebuffer_size_callback);
	//glfwSwapInterval(1);

	//loads with glad the opengl function pointers according to opengl version
	//after this we can use opengl functions safely
	//if a parent is declared no need to load open gl function again
	if (!p && !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	valid = true;
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);

	glCullFace(GL_BACK);
	glDisable(GL_CULL_FACE);

	SetKeyboardHandler(&Window::KeyboardCallback);
	winCount++;
	//// During init, enable debug output
	//glEnable(GL_DEBUG_OUTPUT);
	//glDebugMessageCallback(MessageCallback, 0);
}


WindowPtr Window::CreateWindow(const char* windowName, int width, int height, WindowPtr parent, MonitorType monitor) {
	Window* w = new Window(windowName, width, height, parent, monitor);
	return WindowPtr(w);
}

bool Window::AttachWindowToMonitor(MonitorType monitor, int width, int height, int framerate) {
	if (IsMonitorAvailable(monitor)) {
		GLFWmonitor* m = monitors[(int)monitor];
		if (!m)
			return false;

		glfwSetWindowMonitor(windowHandler, m, 0, 0, windowWidth, windowHeight, framerate);
		glfwSetWindowSize(windowHandler, width, height);
		return true;
	}
	return false;
}

void Window::LocateWindowAtMonitor(MonitorType monitor, bool maximized)
{
	if (IsMonitorAvailable(monitor)) {
		GLFWmonitor* m = monitors[(int)monitor];
		if (!m)
			return;
		int xpos, ypos;
		glfwGetMonitorPos(m, &xpos, &ypos);
		auto desiredMonitorMode = glfwGetVideoMode(m);

		if (!maximized)
			ypos += desiredMonitorMode->height/2 - windowHeight / 2;
		
		if (!maximized)
			xpos += desiredMonitorMode->width / 2 - windowWidth / 2;
		
		SetWindowPosition(xpos, ypos);
		if (maximized) {
			//int top, bottom, left, right;
			//glfwGetWindowFrameSize(windowHandler, &left, &top, &right, &bottom);
			//xpos += (right - left);
			//ypos -= (top - bottom);
			
			glfwMaximizeWindow(windowHandler);
			//glfwSetWindowSize(windowHandler, desiredMonitorMode->width, desiredMonitorMode->height);
			//glfwSetWindowSize(windowHandler, desiredMonitorMode->width, desiredMonitorMode->height);

		}
			
		
	}

}

void Window::FocusOnContext()
{
	if (nullptr != windowHandler)
		glfwMakeContextCurrent(windowHandler);
}

void Window::FocusOnWindow()
{
	if (nullptr != windowHandler)
		glfwFocusWindow(windowHandler);
}

void Window::Refresh()
{
	if (windowHandler) {
		glfwSwapBuffers(windowHandler);
		//poll event like mouse/keyboard
		glfwPollEvents();
	}
}

void Window::SetKeyboardHandler(GLFWkeyfun f)
{
	if (nullptr != f)
		glfwSetKeyCallback(windowHandler, f);
}

bool Window::NeedToClose()
{
	if (windowHandler)
		return glfwWindowShouldClose(windowHandler);

	return true;
}

void Window::SetWindowPosition(int xpos, int ypos)
{
	if (windowHandler)
		glfwSetWindowPos(windowHandler, xpos, ypos);
}

void Window::GetWindowPosition(int& xpos, int& ypos)
{
	if (windowHandler)
		glfwSetWindowPos(windowHandler, xpos, ypos);
}

Window::~Window()
{
	if (windowHandler)
		glfwDestroyWindow(windowHandler);

	winCount--;
	if (winCount == 0) {
		//clean resources of the windows
		glfwTerminate();
	}
}
