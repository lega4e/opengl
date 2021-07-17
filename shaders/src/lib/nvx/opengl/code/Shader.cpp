#include <nvx/opengl/Shader.hpp>
#include <nvx/opengl/common.hpp>

#include <string>
#include <stdio.h>


using namespace std;





namespace nvx
{





Shader::Shader(): _id(0) {}

Shader::Shader(char const *vertex_shader, char const *frag_shader)
{
	int vsh = create_shader(GL_VERTEX_SHADER, vertex_shader);
	int fsh = create_shader(GL_FRAGMENT_SHADER, frag_shader);

	_id = create_shader_program(vsh, fsh);

	glDeleteShader(vsh);
	glDeleteShader(fsh);
}

Shader::Shader(int vertex_shader, int frag_shader)
{
	_id = create_shader_program(vertex_shader, frag_shader);
}





int Shader::id() const
{
	return _id;
}

int Shader::id(int newid)
{
	int tmp = _id;
	_id = newid;
	return tmp;
}

void Shader::use() const
{
	glUseProgram(_id);
}

int Shader::location(char const *name) const
{
	return glGetUniformLocation(_id, name);
}





// int
Shader const &Shader::uniform(int location, int x) const
{
	glUniform1i(location, x);
	return *this;
}

Shader const &Shader::uniform(int location, int x, int y) const
{
	glUniform2i(location, x, y);
	return *this;
}

Shader const &Shader::uniform(int location, int x, int y, int z) const
{
	glUniform3i(location, x, y, z);
	return *this;
}

Shader const &Shader::uniform(int location, int x, int y, int z, int w) const
{
	glUniform4i(location, x, y, z, w);
	return *this;
}





// float
Shader const &Shader::uniform(int location, float x) const
{
	glUniform1f(location, x);
	return *this;
}

Shader const &Shader::uniform(int location, float x, float y) const
{
	glUniform2f(location, x, y);
	return *this;
}

Shader const &Shader::uniform(int location, float x, float y, float z) const
{
	glUniform3f(location, x, y, z);
	return *this;
}

Shader const &Shader::uniform(int location, float x, float y, float z, float w) const
{
	glUniform4f(location, x, y, z, w);
	return *this;
}





// free functions
void swap(Shader &lhs, Shader &rhs)
{
	::swap(lhs._id, rhs._id);
}





}





// END
