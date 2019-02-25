#version 330 core
//la primera linea del shader siempre es la version de shader con la que se va a trabajar

//la primera parte de los shaders es la declaracion de variables y usualmente se le dice si es de entrada o salida, si no se dice in/out solo se pueden usar en el shader

//Atributos de entrada (vienen desde c++)
in vec3 posicion;
in vec4 color;

//Atributos de salida (van hacia el fragment shader)
out vec4 fragmentColor;

//Funcion main
void main() 
{
	//es la posicion de salida del vertice (posicion final en la que se va a renderear el vertice)
	//esta variable ya existe en los shaders, es de tipo vec4
	gl_Position.xyz = posicion;
	gl_Position.w = 1.0; // w es 0 si no vamos a renderear el vertice y 1 si si lo vamos a renderear

	//Establecer valores de atributos de salida
	fragmentColor = color;
}

