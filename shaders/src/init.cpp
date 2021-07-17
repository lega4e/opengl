#include <glob.hpp>

#include <stdio.h>





GLFWwindow *create_window();
void       init_shaders();
void       init_triangle();





void init_application()
{
	glfwInit();

	// window
	g_window = create_window();
	glfwSetFramebufferSizeCallback(g_window,
		[](GLFWwindow *window, int neww, int newh)->void {
			glViewport(0, 0, neww, newh);
		});

	glfwMakeContextCurrent(g_window);

	// glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		exit_with_error("Error: failed to initialize GLAD\n");

}



GLFWwindow *create_window()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow *window = glfwCreateWindow(
		WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,
		nullptr, nullptr );

	if (!window)
		exit_with_error("Error: can't create GLFW window\n");

	return window;
}



void free_application()
{
	glfwTerminate();
}





// END
