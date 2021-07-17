#include <glob.hpp>

#include <fstream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;





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
