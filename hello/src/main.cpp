#include <cstdio>
#include <cstdlib>

#include <glad/glad.h>  // должен быть первым среди opengl-include
#include <GLFW/glfw3.h>





// structs
struct color_t
{
	float r, g, b, a;
};





// global constants
constexpr int  const WIDTH  = 800;
constexpr int  const HEIGHT = 600;
constexpr char const *TITLE = "Hello, OpenGL";


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





// functions
void exit_with_error(char const *err, int code = -1)
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
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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

	main_loop();
	glfwTerminate();
	
	return 0;
}





// END
