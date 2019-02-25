#version 330 core
//primera linea siempre es la version

//atributos de entrada (vienen desde el VertexShader)
in vec4 fragmentColor;

//Atributos de salida
out vec4 salidaColor;

//Funcion main

void main()
{
	salidaColor = fragmentColor;
}
