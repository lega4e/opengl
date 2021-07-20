#include <glob.hpp>

#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>





void handle_input();
void main_loop_prepare();

void main_loop()
{
	using namespace glm;

	mat4 trans_base(1.f), trans;
	trans_base = translate(trans_base, vec3(0.1f, 0.1f, 0.1f));
	trans_base = scale(trans_base, vec3(0.8f, 0.8f, 0.8f));

	g_shader.use();
	main_loop_prepare();
	int out_color_location = g_shader.location("out_color");

	while (!glfwWindowShouldClose(g_window))
	{
		glfwPollEvents();
		handle_input();

		float time = glfwGetTime();
		float color = sin(time) / 2.0f + 0.5f;
		trans = rotate(trans_base, (float)M_PI*time, vec3(0.f, 0.f, 1.f));

		glClear(GL_COLOR_BUFFER_BIT);

		g_shader.uniform(out_color_location, 0.0f, color, 0.0f, 1.0f);
		glUniformMatrix4fv(
			glGetUniformLocation(g_shader.id(), "trans"),
			1, GL_FALSE, value_ptr(trans) );
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

void main_loop_prepare()
{
	glClearColor(EXTRC(DARK_BLUE));
	glBindVertexArray(g_vao_rectangle);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, g_texture2);


	g_shader.use();
	g_shader.uniform("bottom_color", EXTRC(LIGHT_RED));
	g_shader.uniform("mode",         0);
	g_shader.uniform("tex",          (int)0);
	g_shader.uniform("tex2",         (int)1);
}





// END
