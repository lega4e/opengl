#include <glob.hpp>

#include <math.h>





void main_loop()
{
	glClearColor(EXTRC(DARK_BLUE));
	glBindVertexArray(g_vao_triangles);

	int out_color_location = glGetUniformLocation(g_shader_program, "out_color");

	while (!glfwWindowShouldClose(g_window))
	{
		glfwPollEvents();
		handle_input();

		float time = glfwGetTime();
		float color = sin(time) / 2.0f + 0.5f;


		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(g_shader_program);
		// f,i,ui,3f
		glUniform4f(out_color_location, 0.0f, color, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 3, 3);

		glfwSwapBuffers(g_window);
	}
}

void handle_input()
{
	if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(g_window, true);
}





// END
