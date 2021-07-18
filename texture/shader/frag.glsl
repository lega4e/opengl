#version 330 core

out vec4 frag_color;

in vec3 vertex_color;
in vec2 frag_position;

uniform int gradient;
uniform vec4 out_color;
uniform vec4 bottom_color;





void main()
{
	if (gradient == 1)
		frag_color = vec4(vertex_color, 1.0);
	else if (frag_position.y < 0.0f)
		frag_color = bottom_color;
	else
		frag_color = out_color;
}





// END
