#pragma once

#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

using namespace std;

class Shader
{
	public:
		//asi se declara que existira esta funcion
		GLuint getID(); //obtiene el id del shader
		Shader(const char * rutaVertex, const char * rutaFragment);

		void enlazar();
		void desenlazar();
	private:
		GLuint shaderID;
		void verificarComplicacion(GLuint id);
		void verificarVinculacion(GLuint id);

};