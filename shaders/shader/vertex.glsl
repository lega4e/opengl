#version 330 core

layout (location = 0) in vec3 apos;





void main()
{
	// устанавливаем выходное значение
	gl_Position = vec4(apos.x, apos.y, apos.z, 1.0);
}





// END
