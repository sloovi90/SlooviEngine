#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include "GraphicsDefinitions.h"

class Window;
typedef std::shared_ptr<Window> WindowPtr;

class Window {
	GLFWwindow* windowHandler;
	std::string windowName;
	
	MonitorType windowMonitor;
	WindowPtr windowParent;//context sharing 
	bool valid;
	Window() = delete;

protected:
	int windowWidth;
	int windowHeight;
	Window(const char* windowName, int width, int height, WindowPtr parent=nullptr, MonitorType monitor=MonitorType::DONT_CARE);

public:
	static WindowPtr CreateWindow(const char* windowName, int width, int height, WindowPtr parent = nullptr, MonitorType monitor=MonitorType::DONT_CARE);
	bool AttachWindowToMonitor(MonitorType monitor, int width, int height, int framerate = GLFW_DONT_CARE);
	void LocateWindowAtMonitor(MonitorType monitor,bool maximized=false);
	void FocusOnContext();
	void FocusOnWindow();
	virtual void Draw() {};
	void Refresh();
	
	bool NeedToClose();
	void SetWindowPosition(int xpos,int ypos);
	void GetWindowPosition(int &xpos, int &ypos);
	~Window();

private:
	bool IsMonitorAvailable(MonitorType monitor);
	GLFWwindow* GetWindowHandler();
	void SetKeyboardHandler(GLFWkeyfun f);

	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void Framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static int monitorCount;
	static GLFWmonitor** monitors;
	static int winCount;
};




