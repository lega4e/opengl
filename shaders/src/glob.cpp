#include <glob.hpp>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>





/************************** OBJECTS *************************/
GLFWwindow *g_window;





/************************* FUNCTIONS ************************/
void exit_with_error(int code, char const *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	free_application();
	exit(code);
}

void exit_with_error(char const *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	free_application();
	exit(-1);
}





// END
