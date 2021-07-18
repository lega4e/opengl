#include <glob.hpp>

#include <stdio.h>
#include <stb_image.h>

#include <nvx/opengl/Shader.hpp>





GLFWwindow *g_window;

uint g_vbo_rectangle;
uint g_vao_rectangle;
uint g_ebo_rectangle;
uint g_texture;

nvx::Shader g_shader;


GLFWwindow *create_window();
void       init_shaders();
void       init_texture();
void       init_rectangle();





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
	init_texture();
	init_rectangle();
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


void init_texture()
{
	int width, height, channelsc;
	unsigned char *data = stbi_load(
		"tex/wooden_container.jpg",
		&width, &height, &channelsc, 0);

	if (!data)
	{
		stbi_image_free(data);
		exit_with_error("Can't load texture 'wooden_container.jpg'\n");
	}

	glGenTextures(1, &g_texture);
	glBindTexture(GL_TEXTURE_2D, g_texture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}

void init_rectangle()
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
		 // координаты        // цвета            // текстурные координаты
		 0.7f,  0.7f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
		 0.7f, -0.7f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
		-0.7f, -0.7f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
		-0.7f,  0.7f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // верхняя левая 
	};

	static constexpr int const indices[] = {
		0, 1, 2,
		0, 3, 2
	};


	/* vao */
	glGenVertexArrays(1, &g_vao_rectangle);
	glBindVertexArray(g_vao_rectangle);


	/* vbo */
	glGenBuffers(1, &g_vbo_rectangle);
	glBindBuffer(GL_ARRAY_BUFFER, g_vbo_rectangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// verticies
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// tex coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	/* ebo */
	glGenBuffers(1, &g_ebo_rectangle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ebo_rectangle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void free_application()
{
	glfwTerminate();
}





// END
