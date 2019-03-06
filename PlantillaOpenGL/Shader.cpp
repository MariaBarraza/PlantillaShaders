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
	if (vertexShaderStream.is_open())
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

	//4.-Verificar los errores de compilacion
	verificarComplicacion(vertexShaderID);
	verificarComplicacion(fragmentShaderID);

	//5.-Adjuntar shaders al programa,se ocupa el id del programa y el apuntador al shader
	//usualmente se usan en el orden vertex y fragment pero esto no afecta
	glAttachShader(shaderID,vertexShaderID);
	glAttachShader(shaderID, fragmentShaderID);

	//6.-Vincular el programa, aqui se vincula el shader a c
	glLinkProgram(shaderID);

	//7.-Verificar la vinculacion
	verificarVinculacion(shaderID);

	//8.-Usar el programa, en este momento se le dice que todo lo que tenga que ver con shaders lo va a mandar a este shader
	glUseProgram(shaderID);


}

void Shader::enlazar()
{
	glUseProgram(shaderID);
}

void Shader::desenlazar()
{
	glUseProgram(0);
}
//4.-Verificar errores de compilacion
void Shader::verificarComplicacion(GLuint id)
{
	//glfalse es = 0
	GLint resultado = GL_FALSE;
	//se conoce como log al guardar texto en la ejecucion de un programa
	GLint longitudLog = 0;

	//esta funcion trae informacion del shades, propiedades ya establecidas
	//primero es el id del shader despues lo que se quiere obtener y al final la direccion de memoria donde se va a guardar
	glGetShaderiv(id, GL_COMPILE_STATUS, &resultado);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &longitudLog);

	//los vectores son listas de c++
	if (longitudLog > 0)
	{
		//asi se declaran  los vectores, va a ser un vector tipo char, que se llamara mensaje error y tendra tantos elementos como la longitud del log
		vector<char> mensajeError(longitudLog);
		//aqui se obtiene el log, primero el id, despues el tamaño del buffer (que tamaño tiene el log),
		glGetShaderInfoLog(id,longitudLog,NULL,&mensajeError[0]);

		//iteradores para imprimir todos los caracteres
		//el primer parametro del for seria un iterador constante, que seria igual al inicio del vector, se usa para cuando se trabaja con iteradores
		//en este caso el i++ es una sobrecarga de operador para que pase al siguiente
		for (vector<char>::const_iterator i = mensajeError.begin(); i != mensajeError.end(); i++)
		{
			//se desapunta a i para imprimir el mensaje de error
			cout << *i;
		}
	}
}

void Shader::verificarVinculacion(GLuint id)
{
	GLint estadoVinculacion, estadoValidacion;
	//se obtiene lnformacion del status de conexion
	glGetProgramiv(id, GL_LINK_STATUS, &estadoVinculacion);
	if (estadoVinculacion == GL_FALSE)
	{
		cout << "no se pudo vincular programa" << endl;
	}

	glGetProgramiv(id, GL_VALIDATE_STATUS, &estadoValidacion);
	if (estadoValidacion == GL_FALSE)
	{
		cout << "no se pudo validad la vinculacion" << endl;
	}
}