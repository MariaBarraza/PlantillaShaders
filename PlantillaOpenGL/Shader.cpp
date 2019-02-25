#include "stdafx.h"
#include "Shader.h"

//asi se implementa el codigo a la funcion
GLuint Shader :: getID() 
{
	return shaderID;
}

Shader::Shader(const char * rutaVertex, const char * rutaFragment)
{
	//aqui se guarda el codigo del shader
	string codigoVertexShader;

	//se declara una variable para leer la entrada de algo
	//se necesitan dos parametros la ruta de donde esta el vertex shader y el modo en el que quiero leer el parametro anterior
	//ios = input output string
	ifstream vertexShaderStream(rutaVertex,ios::in);
	//aqui se verifica si se pudo abrir el stream
	if (vertexShaderStream.is_open)
	{
		//como lee linea por linea se declara una linea actual
		string linea;
		//se usa get line para saber en que linea vamos y se guarda en la variable linea
		while (getline(vertexShaderStream, linea))
		{
			codigoVertexShader += linea + "\n";
		}
		//despues de guardar todo el codigo en la variable se cierra
		vertexShaderStream.close();
	}
	else
	{
		cout << "no se pudo abrir el archivo" << rutaVertex;
	}
}