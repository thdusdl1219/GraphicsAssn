#pragma once

#include "default.h"
#include <iostream>

class Shader {

public :
	Shader(const char *vertex_path, const char *fragment_path, const std::string tag);
	GLuint getShader();
	GLuint getShader2();
	std::string getTag();
private :
	std::string readFile(const char *filePath);
	GLuint program;
	std::string tag;

};