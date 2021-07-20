#ifndef NVX_OPENGL_SHADER_HPP_8739851391
#define NVX_OPENGL_SHADER_HPP_8739851391

#include <glad/glad.h>
#include <GLFW/glfw3.h>





namespace nvx
{





class Shader
{
public:
	Shader();
	Shader(char const *vertex_shader, char const *frag_shader);
	Shader(int vertex_shader, int frag_shader);

	int  id()  const;
	int  id(int newid);
	void use() const;
	int  location(char const *name) const;

	// int
	Shader const &uniform(int location, int x) const;
	Shader const &uniform(int location, int x, int y) const;
	Shader const &uniform(int location, int x, int y, int z) const;
	Shader const &uniform(int location, int x, int y, int z, int w) const;

	// float
	Shader const &uniform(int location, float x) const;
	Shader const &uniform(int location, float x, float y) const;
	Shader const &uniform(int location, float x, float y, float z) const;
	Shader const &uniform(int location, float x, float y, float z, float w) const;

	// Shader const &uniform(int location, float x, float y, float z, float w) const;

	template<typename...Args>
	inline Shader const &uniform(char const *name, Args...args)
	{
		return uniform(location(name), args...);
	}

private:
	int _id;

	friend void swap(Shader &lhs, Shader &rhs);

};





}





#endif // NVX_OPENGL_SHADER_HPP_8739851391
