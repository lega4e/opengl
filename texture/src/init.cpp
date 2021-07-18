#include <glob.hpp>

#include <stdio.h>

#include <nvx/opengl/Shader.hpp>





GLFWwindow *g_window;

uint g_vbo_triangles;
uint g_vao_triangles;

nvx::Shader g_shader;


GLFWwindow *create_window();
void       init_shaders();
void       init_triangles();





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

	g_shader = nvx::Shader("shader/vertex.glsl", "shader/frag.glsl");
	init_triangles();
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


void init_triangles()
{
	/*
	 * Узнать максимальное число вершинных атрибутов
	 * (тех переменных, которые объявляются в vertex.glsl
	 * с меткой location ... in
	 */
	int n;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);
	printf("Max vertex attribs: %i\n", n);

	static constexpr float const vertices[] = {
		//   vertecies             colors
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.f,
	};

	glGenVertexArrays(1, &g_vao_triangles);
	glBindVertexArray(g_vao_triangles);

	glGenBuffers(1, &g_vbo_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, g_vbo_triangles);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// verticies
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


void free_application()
{
	glfwTerminate();
}





// END
