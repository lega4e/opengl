#include <glob.hpp>

#include <math.h>





void main_loop()
{
	glClearColor(EXTRC(DARK_BLUE));
	glBindVertexArray(g_vao_rectangle);
	glBindTexture(GL_TEXTURE_2D, g_texture);

	int out_color_location = g_shader.location("out_color");
	g_shader.use();
	g_shader.uniform("bottom_color", EXTRC(LIGHT_RED));
	g_shader.uniform("mode", 0);

	while (!glfwWindowShouldClose(g_window))
	{
		glfwPollEvents();
		handle_input();

		float time = glfwGetTime();
		float color = sin(time) / 2.0f + 0.5f;

		glClear(GL_COLOR_BUFFER_BIT);

		g_shader.uniform(out_color_location, 0.0f, color, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(g_window);
	}
}

void handle_input()
{
	if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(g_window, true);

	if (glfwGetKey(g_window, GLFW_KEY_C) == GLFW_PRESS)
		g_shader.uniform("mode", (int)0);

	if (glfwGetKey(g_window, GLFW_KEY_G) == GLFW_PRESS)
		g_shader.uniform("mode", (int)1);

	if (glfwGetKey(g_window, GLFW_KEY_T) == GLFW_PRESS)
		g_shader.uniform("mode", (int)2);
}





// END
