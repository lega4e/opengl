#include <glob.hpp>





void main_loop()
{
	glClearColor(EXTRC(DARK_BLUE));

	while (glfwWindowShouldClose(g_window))
	{
		glfwPollEvents();
		handle_input();

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(g_window);
	}
}

void handle_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}





// END
