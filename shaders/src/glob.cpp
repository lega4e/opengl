#include <glob.hpp>

#include <fstream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;





/************************** OBJECTS *************************/
GLFWwindow *g_window;
int         g_shader_program;





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



string read_file(char const *filename)
{
	ifstream fin(filename);
	if (!fin)
		throw string("Can't open file '") + filename + "'";
	string file;
	while (fin)
		file.push_back(fin.get());
	return file;
}

int create_shader(int type, char const *filename)
{
	int shader       = glCreateShader(type);
	string src       = read_file(filename);
	char const *srcp = src.data();
	glShaderSource(shader, 1, &srcp, NULL);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char info[INFO_BUFFER_SIZE];
		glGetShaderInfoLog(shader, INFO_BUFFER_SIZE, NULL, info);
		exit_with_error("Error: shader '%s' compilation failed:\n%s\n", filename, info);
	}

	return shader;
}

int create_shader_program(int vertex_shader, int frag_shader)
{
	int prog = glCreateProgram();
	glAttachShader(prog, vertex_shader);
	glAttachShader(prog, frag_shader);
	glLinkProgram(prog);

	int success;
	glGetProgramiv(prog, GL_LINK_STATUS, &success);

	if (!success)
	{
		char info[INFO_BUFFER_SIZE];
		glGetProgramInfoLog(prog, INFO_BUFFER_SIZE, NULL, info);
		exit_with_error(
			"Error: program %i-%i linking failed:\n%s\n",
			vertex_shader, frag_shader, info
		);
	}

	return prog;
}





// END
