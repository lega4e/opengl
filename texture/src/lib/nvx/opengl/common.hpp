#ifndef NVX_OPENGL_COMMON_HPP_6387109234
#define NVX_OPENGL_COMMON_HPP_6387109234





namespace nvx
{





int          create_shader(int type, char const *filename);
int          create_shader_program(int vertex_shader, int frag_shader);
unsigned int load_texture(char const *filename, int savetype, int intype, bool flip = false);





}





#endif
