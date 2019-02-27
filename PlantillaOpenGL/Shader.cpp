#include "stdafx.h"
#include "Shader.h"

//asi se implementa el codigo a la funcion
GLuint Shader :: getID() 
{
	return shaderID;
}

Shader::Shader(const char * rutaVertex, const char * rutaFragment)
{

	//Guardar en variables el texto de los codigos
	//aqui se guarda el codigo del shader
	string codigoVertexShader;

	//se declara una variable para leer la entrada de algo
	//se necesitan dos parametros la ruta de donde esta el vertex shader y el modo en el que quiero leer el parametro anterior
	//ios = input output string
	ifstream vertexShaderStream(rutaVertex, ios::in);
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
		cout << "no se pudo abrir el archivo" << rutaVertex << endl;
	}

	string codigoFragmentShader;

	ifstream fragmentShaderStream(rutaFragment, ios::in);

	if (fragmentShaderStream.is_open())
	{
		string linea;
		while (getline(fragmentShaderStream, linea))
		{
			codigoFragmentShader += linea + "\n";
		}
		fragmentShaderStream.close();
	}
	else
	{
		cout << "No se pudo abrir el archivo: " << rutaFragment << endl;
	}

	//convertir el string a cadena char
	// c_str nos dice que es un string de tipo c
	//se ocupa porque es el tipo de dato que usa OpenGL para compilar
	const char* cadenaCodigoVertex = codigoVertexShader.c_str();
	const char* cadenaCodigoFragment = codigoFragmentShader.c_str();

	//1.-Crear el programa de Shader
	//genera el identificador de un programa (conjunto de shader y vertex)
	shaderID = glCreateProgram();
	//crea el shader, en este caso al darle este parametro crea un vertex shader y regresa el identificador
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	//aca es el fragment shader
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//2.-Cargar el codigo del shader
	//necesita varios parametros, que shader, cuantos estoy pasando, el codigo y la longitud de cada shader
	//con este & decimos la direccion en memoria de algo
	glShaderSource(vertexShaderID,1,&cadenaCodigoVertex,NULL);
	glShaderSource(fragmentShaderID, 1, &cadenaCodigoFragment, NULL);

	//3.-Compilar
	//aqui se compila pero hay que pasarle el id
	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

}


//4.-Verificar errores de compilacion
void Shader::verificarComplicacion(GLuint id)
{
	//glfalse es = 0
	GLint resultado = GL_FALSE;
	//se conoce como log al guardar texto en la ejecucion de un programa
	int longitudLog = 0;

}