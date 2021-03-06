// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h" //ayuda a que compile mas rapido
#include <stdio.h> // esta cosa para librerias incluidas en c#
#include <stdlib.h>

#define GLEW_STATIC 

#include "GL/glew.h" //comillas para librerias personalizadas
#include "GLFW/glfw3.h"

#include <iostream>

#include "Shader.h"
#include "Vertice.h"

using namespace std; //aqui esta lo de c++

Shader *shader;
GLuint posicionID;
GLuint colorID;

//el vertice necesita saber como va a empezar a leer y donde
vector <Vertice> triangulo;
GLuint vertexArrayTrianguloID;
GLuint bufferTrianguloID;

vector<Vertice> cuadrado;
GLuint vertexArrayCuadradoID;
GLuint bufferCuadradoID;

void inicializarCuadrado()
{
	Vertice v1 = { vec3(-0.8, 0.8, 0.0), vec4(0.4, 0.7, 0.1, 1.0) };
	Vertice v2 = { vec3(-0.4, 0.8, 0.0), vec4(0.4, 0.7, 0.1, 1.0) };
	Vertice v3 = { vec3(-0.4, 0.5, 0.0), vec4(0.4, 0.7, 0.1, 1.0) };
	Vertice v4 = { vec3(-0.8, 0.5, 0.0), vec4(0.4, 0.7, 0.1, 1.0) };

	cuadrado.push_back(v1);
	cuadrado.push_back(v2);
	cuadrado.push_back(v3);
	cuadrado.push_back(v4);
		
}

void inicializarTriangulo()
{
	//al ponerle inicializador a la estructura da la capacidad de iniciarlas asi
	Vertice v1 =
	{
		vec3(0.0f,0.3f,0.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};

	Vertice v2 =
	{
		vec3(-0.3f,-0.3f,0.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};

	Vertice v3 =
	{
		vec3(0.3f,-0.3f,0.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};

	//la funcion push back añade nuevos elementos a un vertice
	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);
}


void dibujar()
{
	//Elegir el shader
	shader->enlazar();
	//Elegir un vertex array
	glBindVertexArray(vertexArrayTrianguloID);
	//Dibujar
	//toma de parametro el tipo de primitivas que va a dibujar,despues si va a tener un desface y el numero de vertices
	glDrawArrays(GL_TRIANGLES,0,triangulo.size());

	//cuadrado
	glBindVertexArray(vertexArrayCuadradoID);
	glDrawArrays(GL_QUADS, 0, cuadrado.size());

	//soltar el vertex array
	glBindVertexArray(0);
	//soltar el shader
	shader->desenlazar();
}

void actualizar() {

}

int main()
{
	//Declaramos apuntador de ventana

	GLFWwindow *window;

	//Si no se pudo iniciar glfw terminamos ejecución

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Si se pudo iniciar GLFW entonces inicializamos la ventana

	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido e contexto activamos funciones modernas
	glewExperimental = true; //permite trabajar con gpu y cpu al mismo tiempo,solo va a funcionar si ya esta establecido el contexto

	//en caso de haber error se guarda en la variable errorGlew que es tipo GLenum 
	GLenum errorGlew = glewInit(); //inicializa glew

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	//se obtiene la version de OpenGL y se imprime
	const GLubyte *versionGL = glGetString(GL_VERSION); 
	cout << "Version OpenGL: " << versionGL; 

	inicializarTriangulo();
	inicializarCuadrado();

	const char *rutaVertex = "VertexShader.shader";
	const char *rutaFragment = "FragmentShader.shader";

	//Se crea una nueva instancia de la clase
	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	//lleva 2 atributos el id del programa y la variable que va a obtener
	//aqui se estan guardando las entradas del vertex
	posicionID = glGetAttribLocation(shader -> getID(),"posicion");

	colorID = glGetAttribLocation(shader->getID(), "color");

	//Desenlazar el shader
	shader -> desenlazar();

	/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	//Vertex array y buffer para un cuadrado

	//Crear un vertex array (los vertex array son el conjunto de vertices)
	//pide cuantos arreglos se haran, la direccion de memoria donde se va a guardar
	glGenVertexArrays(1, &vertexArrayCuadradoID);
	//con este se le dice que todas las acciones referentes a los vertex array estan vinculadas al que acabamos de crear
	glBindVertexArray(vertexArrayCuadradoID);

	//crear vertex buffer
	//aqui es cantidad y direccion de memoria
	glGenBuffers(1, &bufferCuadradoID);
	//Se dice que todas las acciones de buffer se hacen a este que acabamos de hacer
	//se le dice que tipo de buffer es y la direccion
	glBindBuffer(GL_ARRAY_BUFFER, bufferCuadradoID);

	//llenar el buffer
	//se le dice que tipo de buffer es, cuanto es el tamaño en bits de lo que le queremos mandar, el espacio de memoria donde va a empezar a leer y para que lo vas a utilizar
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * cuadrado.size(), cuadrado.data(), GL_STATIC_DRAW);

	//habilitar atributos del shader
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);

	//Especificar a OpenGL como se van a comunicar
	//el primer atributo es cual se va a comunicar, el segundo es el tamaño de lo que se tiene que mandar(en este caso 3 flotantes), el tipo de dato de lo que estas mandando,si esta normalizado,el stride es que se van a leer 3 valores y que tanto espacio va a dejar pasar para tomar otros 3 valores, se le pasa el tamaño del vertice incluyendo los 3 que ya se tomaron en cuenta
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*) sizeof(vec3));

	/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

	//Crear un vertex array (los vertex array son el conjunto de vertices)
	//pide cuantos arreglos se haran, la direccion de memoria donde se va a guardar
	glGenVertexArrays(1, &vertexArrayTrianguloID);
	//con este se le dice que todas las acciones referentes a los vertex array estan vinculadas al que acabamos de crear
	glBindVertexArray(vertexArrayTrianguloID);
	
	//crear vertex buffer
	//aqui es cantidad y direccion de memoria
	glGenBuffers(1, &bufferTrianguloID);
	//Se dice que todas las acciones de buffer se hacen a este que acabamos de hacer
	//se le dice que tipo de buffer es y la direccion
	glBindBuffer(GL_ARRAY_BUFFER,bufferTrianguloID);

	//llenar el buffer
	//se le dice que tipo de buffer es, cuanto es el tamaño en bits de lo que le queremos mandar, el espacio de memoria donde va a empezar a leer y para que lo vas a utilizar
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * triangulo.size(), triangulo.data(), GL_STATIC_DRAW);

	//habilitar atributos del shader
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);

	//Especificar a OpenGL como se van a comunicar
	//el primer atributo es cual se va a comunicar, el segundo es el tamaño de lo que se tiene que mandar(en este caso 3 flotantes), el tipo de dato de lo que estas mandando,si esta normalizado,el stride es que se van a leer 3 valores y que tanto espacio va a dejar pasar para tomar otros 3 valores, se le pasa el tamaño del vertice incluyendo los 3 que ya se tomaron en cuenta
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice),(void*) sizeof(vec3));

	//soltar vertex array y buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//ciclo de dibujo (draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768); //dice donde va a empezar a renderear y donde va a terminar
		//Establecer color de borrado
		glClearColor(1.0f, 0.2f, 0.5f, 1.0f);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffer
		glfwSwapBuffers(window); //cambia el buffer de la pantalla por el otro que se lleno
		//reconocer si hay entradas
		glfwPollEvents();

	}

	glfwDestroyWindow(window); //terminamos los procesos y eliminamos la ventana
	glfwTerminate();
	return 0;
}



