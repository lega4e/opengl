#include <glob.hpp>





void main_loop()
{
	glClearColor(EXTRC(DARK_BLUE));
	glBindVertexArray(g_vao_triangles);

	while (!glfwWindowShouldClose(g_window))
	{
		glfwPollEvents();
		handle_input();


		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(g_shader_program);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(g_window);
	}
}

void handle_input()
{
	if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(g_window, true);
}





// END
