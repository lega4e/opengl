#include <cstdio>
#include <cstdlib>

#include <glad/glad.h>  // должен быть первым среди opengl-include
#include <GLFW/glfw3.h>

#include "shaders.hpp"





// structs
struct color_t
{
	float r, g, b, a;
};





// global constants
constexpr int  const WIDTH  = 800;
constexpr int  const HEIGHT = 600;
constexpr char const *TITLE = "Hello, OpenGL";
constexpr int  const INFO_BUFFER_SIZE = 1024;


// colors
constexpr color_t const WHITE        = color_t { 1.000, 1.000, 1.000, 1.000 };
constexpr color_t const BLACK        = color_t { 0.000, 0.000, 0.000, 1.000 };

constexpr color_t const RED          = color_t { 0.678, 0.224, 0.224, 1.000 };
constexpr color_t const LIGHT_RED    = color_t { 0.867, 0.325, 0.325, 1.000 };
constexpr color_t const LLIGHT_RED   = color_t { 0.957, 0.412, 0.412, 1.000 };
constexpr color_t const DARK_RED     = color_t { 0.608, 0.106, 0.106, 1.000 };
constexpr color_t const DDARK_RED    = color_t { 0.510, 0.051, 0.051, 1.000 };

constexpr color_t const GREEN        = color_t { 0.259, 0.678, 0.224, 1.000 };
constexpr color_t const LIGHT_GREEN  = color_t { 0.541, 0.867, 0.325, 1.000 };
constexpr color_t const LLIGHT_GREEN = color_t { 0.412, 0.957, 0.486, 1.000 };
constexpr color_t const DARK_GREEN   = color_t { 0.200, 0.608, 0.106, 1.000 };
constexpr color_t const DDARK_GREEN  = color_t { 0.051, 0.510, 0.094, 1.000 };

constexpr color_t const BLUE         = color_t { 0.216, 0.302, 0.702, 1.000 };
constexpr color_t const LIGHT_BLUE   = color_t { 0.325, 0.400, 0.867, 1.000 };
constexpr color_t const LLIGHT_BLUE  = color_t { 0.412, 0.498, 0.957, 1.000 };
constexpr color_t const DARK_BLUE    = color_t { 0.133, 0.106, 0.608, 1.000 };
constexpr color_t const DDARK_BLUE   = color_t { 0.067, 0.051, 0.510, 1.000 };

constexpr color_t const YELLOW       = color_t { 0.745, 0.725, 0.235, 1.000 };
constexpr color_t const MAGENTA      = color_t { 0.224, 0.780, 0.655, 1.000 };
constexpr color_t const PURPLE       = color_t { 0.647, 0.224, 0.780, 1.000 };


// global variables
GLFWwindow *window = nullptr;
int  shader_prog   = 0;
uint triangle_vbo  = 0;
uint array_vao     = 0;




// function headers
void exit_with_error(char const *err, int code = -1);
void framebuffer_resized(GLFWwindow *window, int w, int h);

void create_window();
void init_glad();
int  create_vertex_shader();
int  create_frag_shader();
void init_shaders();
void init_triangle();
void init_graphics();

void handle_input(GLFWwindow *win);
void main_loop();

// functions
void exit_with_error(char const *err, int code)
{
	// Освобождение всех ресурсов, выделенных glfw
	glfwTerminate();
	fprintf(stderr, "%s\n", err);
	exit(code);
}

/*
 * Эта функция будет вызываться при изменении
 * размера окна (её нужно будет отдельно на это
 * назначить, что делаетсь в create_window)
 */
void framebuffer_resized(GLFWwindow *window, int w, int h)
{
	/*
	 * Установка окна просмотра. Интересно то, что координаты
	 * точек в OpenGL находятся между -1 и 1, а значения из
	 * окна просмотра необходимы лишь для отображения этих
	 * точек на пиксели экрана
	 */
	//          left top  width height
	glViewport( 0,   0,   w,    h      );
}


void create_window()
{
	/*
	 * Установка параметров:
	 * Первым аргументом тип параметра, вторым — значение
	 */

	// Устанавливаем минимальную и максимальную версию OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	// Указываем, что будем использовать core-profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Пользователь не сможет изменить размер окна
	// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Собственно, создаём окно
	window = glfwCreateWindow(
		WIDTH,   HEIGHT, TITLE,
		nullptr, nullptr
	);

	if (!window)
		exit_with_error("Error: can't create GLFW window");

	// Указываем, что контекст окна — основной контекст в данном потоке
	glfwMakeContextCurrent(window);

	// Установка функции обратного вызова при изменении размера окна.
	// Установка callback-функция должна происходит после создания
	// окна и до начала рендеринга
	glfwSetFramebufferSizeCallback(window, framebuffer_resized);
}


// Инициализация glad должна происходить после создания окна
void init_glad()
{
	/*
	 * gloadLoadGLLoader — функция, которая находит и устанавливает
	 * адреса указателей на платформозависимые OpenGL-функции; в
	 * качестве аргумента мы передаём ей функцию, которая возвращает
	 * указатели на OpenGL-функции
	 */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		exit_with_error("Error: failed to initialize GLAD");
}


int create_vertex_shader()
{
	/*
	 * Создаём шейдер, затем помещаем в него исходный
	 * код и компилируем, после чего можно проверить,
	 * была ли компиляция успешной, а если нет, то какие
	 * ошибки были найдены
	 */
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	//              шейдер   число строк  исходный код      ????
	glShaderSource(vertex_shader, 1, vertex_shader_source(), NULL);
	glCompileShader(vertex_shader);

	int success;
	char info[INFO_BUFFER_SIZE];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, INFO_BUFFER_SIZE, NULL, info);
		fprintf(stderr, "ERROR: VERTEX SHADER COMPILATION FAILED\n%s", info);
		exit(1);
	}

	return vertex_shader;
}

int create_frag_shader()
{
	/*
	 * Создание фрагментного шейдера аналогично
	 * вершинному, но, разумеется, нужно указать
	 * другой тип
	 */
	int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	//              шейдер   число строк  исходный код      ????
	glShaderSource(frag_shader, 1, frag_shader_source(), NULL);
	glCompileShader(frag_shader);

	int success;
	char info[INFO_BUFFER_SIZE];
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(frag_shader, INFO_BUFFER_SIZE, NULL, info);
		fprintf(stderr, "ERROR: FRAG SHADER COMPILATION FAILED\n%s", info);
		exit(1);
	}

	return frag_shader;
}

void init_shaders()
{
	/*
	 * Связываем шейдеры в шейдерную программу:
	 *
	 * 1. Создать программу        (glCreateProgram)
	 * 2. Прикрепить к ней шейдеры (glAttachShader)
	 * 3. Связать их               (glLinkProgram)
	 * 3. Удалить шейдеры, которые
	 *    теперь не нужны          (glDeleteShader)
	 *
	 * Теперь у нас есть программный объект, который
	 * мы можем использовать, вызывая glUseProgram(shader_prog)
	 */
	int vertex_shader = create_vertex_shader();
	int frag_shader   = create_frag_shader();

	shader_prog = glCreateProgram();
	glAttachShader(shader_prog, vertex_shader);
	glAttachShader(shader_prog, frag_shader);
	glLinkProgram(shader_prog);

	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);

	int success;
	char info[INFO_BUFFER_SIZE];
	glGetProgramiv(shader_prog, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shader_prog, INFO_BUFFER_SIZE, NULL, info);
		fprintf(stderr, "ERROR (%i): SHADER PROGRAMM CREATION FAILED\n%s", success, info);
		exit(-1);
	}
}

void init_triangle()
{
	/*
	 * Задаём координаты треугольника в 3D
	 * пространстве (помним, что координаты
	 * лежат в отрезке от -1 до 1 и по х и по y
	 */
	static constexpr float const vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	/*
	 * Создание буфера с помощью glGenBuffers,
	 * привязка его к вершинному буферу
	 * GL_ARRAY_BUFFER и, наконец, копирование
	 * созданных вершин в память буфера.
	 */
	glGenBuffers(1, &triangle_vbo);

	/*
	 * После следующей привязки любые инструкции,
	 * обращённые к GL_ARRAY_BUFFER, будут использоваться
	 * для конфигурирования текущего привязанного
	 * буфера, в данном случае — triangle_vbo
	 */
	glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);

	/*
	 * Способов использования данных в glBufferData
	 * всего три штуки:
	 * 
	 * 1. GL_STREAM_DRAW — данные указываются только
	 *    один раз и используются графическим
	 *    процессором не более нескольких раз.
	 * 
	 * 2. GL_STATIC_DRAW — данные указываются только
	 *    один раз и используются много раз.
	 * 
	 * 3. GL_DYNAMIC_DRAW — данные часто изменяются и
	 *    используются много раз.
	 */
	//             тип буфера      размер данных     данные   способ использования
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void init_graphics()
{
	init_shaders();
	init_triangle();

	/*
	 * Указываем, как воспринимать объекты,
	 * поступаемые в вершинный шейдер. То, из
	 * кокого буфера вершинный шейдер будет брать
	 * данные, определяется буфером, привязанным
	 * к GL_ARRAY_BUFFER в момент вызова
	 * glVertexAttribPointer
	 */
	glVertexAttribPointer(
		0,                 // location для объекта (см. вершинный шейдер)
		3,                 // количество элементов в объекте
		GL_FLOAT,          // тип элементов объекта
		GL_FALSE,          // требуется ли нормализация
		3 * sizeof(float), // расстояние между объектами
		nullptr            // 
	);

	/*
	 * Задействуем атрибут вершины, передавая
	 * в неё расположение (location) атрибута
	 */
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // ??
}



/*
 * Эта функция будет вызываться для обработки
 * пользовательского ввода
 */
void handle_input(GLFWwindow *win)
{
	static int key_p_counter = 0;

	/*
	 * Функция glfwGetKey проверяет, нажата ли определённая
	 * клавиша и, если нажата, возвращает GLFW_PRESS, иначе
	 * — GLFW_RELEASE
	 */
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(win, true);

	if (glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
		printf("Key P pressed (%i)\n", key_p_counter++),
		fflush(stdout);

	if (glfwGetKey(win, GLFW_KEY_R) == GLFW_PRESS)
		glClearColor(DDARK_RED.r, DDARK_RED.g, DDARK_RED.b, DDARK_RED.a);

	if (glfwGetKey(win, GLFW_KEY_G) == GLFW_PRESS)
		glClearColor(DDARK_GREEN.r, DDARK_GREEN.g, DDARK_GREEN.b, DDARK_GREEN.a);

	if (glfwGetKey(win, GLFW_KEY_B) == GLFW_PRESS)
		glClearColor(DDARK_BLUE.r, DDARK_BLUE.g, DDARK_BLUE.b, DDARK_BLUE.a);
}


/*
 * Основной цикл рендеринга, который будет продолжаться
 * до тех пор, пока мы сами не скажем ему остановиться
 */
void main_loop()
{
	/*
	 * Установка контекста: цвета, которым
	 * будет очищаться окно
	 */
	glClearColor(DDARK_BLUE.r, DDARK_BLUE.g, DDARK_BLUE.b, DDARK_BLUE.a);

	/*
	 * glfwWindowShouldClose проверяет,
	 * сообщали ли мы закрыть окно
	 */
	while (!glfwWindowShouldClose(window))
	{
		/*
		 * Проверить, были ли произведены какие-либо события
		 * со стороны пользователя, и вызвать соответствующие
		 * функции-обработчики, которые были установлены
		 * ранее как callback-функции
		 */
		glfwPollEvents();

		handle_input(window);

		/*
		 * Использование контекста: очистка буффера
		 *
		 * - GL_COLOR_BUFFER_BIT   — очистка буфера цвета;
		 * - GL_DEPTH_BUFFER_BIT   — очистка буфера глубины;
		 * - GL_STENCIL_BUFFER_BIT — очистка буфера трафарета.
		 */
		glClear(GL_COLOR_BUFFER_BIT);

		/*
		 * Отрисовываем треугольник
		 */
		// glUseProgram(shader_prog);
		// glBindVertexArray()
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		/*
		 * Заменяет буффер, который используется для отрисовки и
		 * содержимое которого видит пользователь (front-buffer)
		 * на тот, что использовался для рендеринга (back-buffer)
		 */
		glfwSwapBuffers(window);
	}
}





int main( int argc, char *argv[] )
{
	glfwInit();
	create_window();
	init_glad();
	init_graphics();

	main_loop();
	glfwTerminate();
	
	return 0;
}





// END
