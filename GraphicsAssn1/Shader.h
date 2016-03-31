#pragma once

#include "default.h"
#include <iostream>

class Shader {

public :
	Shader(const char *vertex_path, const char *fragment_path);
	GLuint getShader();
private :
	std::string readFile(const char *filePath);
	GLuint program;

};