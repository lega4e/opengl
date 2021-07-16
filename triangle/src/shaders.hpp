#ifndef SHADERS_HPP_84792038
#define SHADERS_HPP_84792038

#include <fstream>
#include <string>





inline char const **vertex_shader_source()
{
	static std::string data  = "";
	static char const *pdata = nullptr;

	if (!pdata)
	{
		std::ifstream fin("shader/vertex.glsl");
		std::getline(fin, data, '\0');
		pdata = data.c_str();
	}

	return &pdata;
}

inline char const **frag_shader_source()
{
	static std::string data  = "";
	static char const *pdata = nullptr;

	if (!pdata)
	{
		std::ifstream fin("shader/frag.glsl");
		std::getline(fin, data, '\0');
		pdata = data.c_str();
	}

	return &pdata;
}






#endif
