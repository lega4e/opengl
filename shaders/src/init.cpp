#include <glob.hpp>

#include <stdio.h>





uint g_vbo_triangles;
uint g_vao_triangles;

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

	init_shaders();
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


void init_shaders()
{
	int vertex_shader = create_shader(GL_VERTEX_SHADER,   "shader/vertex.glsl");
	int frag_shader   = create_shader(GL_FRAGMENT_SHADER, "shader/frag.glsl");

	g_shader_program  = create_shader_program(vertex_shader, frag_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);
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
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	    -0.9f, -0.9f, 0.0f,
		-0.8f, -0.9f, 0.0f,
		-0.9f, -0.8f, 0.0f
	};

	glGenVertexArrays(1, &g_vao_triangles);
	glBindVertexArray(g_vao_triangles);

	glGenBuffers(1, &g_vbo_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, g_vbo_triangles);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


void free_application()
{
	glfwTerminate();
}





// END
