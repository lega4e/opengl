#ifndef SHADERS_HPP_84792038
#define SHADERS_HPP_84792038





constexpr char const *vertex_shader_source =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

constexpr char const *frag_shader_source =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";





// constexpr char const *vertex_shader_source =
	// "#version 330 core                                    \n"
	// "                                                     \n"
	// "layout (location = 0) in vec3 apos;                  \n"
	// "                                                     \n"
	// "void main()                                          \n"
	// "{                                                    \n"
	// "    gl_Position = vec4(apos.x, apos.y, apos.z, 1.0); \n"
	// "}                                                    \n\0";

// constexpr char const *frag_shader_source =
	// "#version 330 core                            \n"
	// "                                             \n"
	// "out vec4 FragColor;                          \n"
	// "                                             \n"
	// "void main()                                  \n"
	// "{                                            \n"
	// "    FragColor = vec4(1.f, 0.5f, 0.2f, 1.0f); \n"
	// "}                                            \n\0";





#endif
