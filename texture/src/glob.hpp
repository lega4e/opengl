#ifndef GLOB_H_853928539
#define GLOB_H_853928539

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include <nvx/opengl/Shader.hpp>





/************************** OBJECTS *************************/
// core
constexpr int  const  WINDOW_WIDTH     = 1000;
constexpr int  const  WINDOW_HEIGHT    = 1000;
constexpr char const *WINDOW_TITLE     = "Sahders";
constexpr int  const  INFO_BUFFER_SIZE = 1024;

extern GLFWwindow *g_window;
extern nvx::Shader g_shader;

extern uint g_vbo_rectangle;
extern uint g_vao_rectangle;
extern uint g_ebo_rectangle;
extern uint g_texture;


// colors
struct color_t
{
	float r, g, b, a;
};

#define EXTRC(c) c.r, c.g, c.b, c.a

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





/************************* FUNCTIONS ************************/
void init_application();
void free_application();

void handle_input();
void main_loop();

void exit_with_error(int code, char const *fmt = nullptr, ...);
void exit_with_error(char const *fmt = nullptr, ...);





#endif
