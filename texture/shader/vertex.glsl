#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex;

out vec3 vertex_color;
out vec2 frag_position;
out vec2 tex_coord;





void main()
{
	gl_Position   = vec4(pos, 1.0);
	vertex_color  = color;
	frag_position = pos.xy;
	tex_coord     = tex;
}





// END
