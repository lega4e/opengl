#include <nvx/opengl/common.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <fstream>
#include <string>





using namespace std;

namespace nvx
{





constexpr int const INFO_BUFFER_SIZE = 1024;



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
		throw string("Error: shader '") + filename + "' compilation failed:\n" + info;
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
		throw string("Error: shader program linking failed:\n") + info;
	}

	return prog;
}

unsigned int load_texture(char const *filename, int savetype, int intype, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	int width, height, channelsc;
	unsigned char *data = stbi_load(filename,
		&width, &height, &channelsc, 0);
	printf("(%s) Channels number: %i\n", filename, channelsc);

	if (!data)
	{
		stbi_image_free(data);
		throw std::string("Can't load texture '") + filename + "'";
	}

	uint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0, savetype, width, height, 0,
		intype, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	return texture;
}





}





// end
