#include "Shader.h"
#include "circle.h"

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

std::string Shader::readFile(const char* filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

Shader::Shader(const char *vertex_path, const char* fragment_path) {
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read shaders
	std::string vertShaderStr = readFile(vertex_path);
	std::string fragShaderStr = readFile(fragment_path);
	const char *vertShaderSrc = vertShaderStr.c_str();
	const char *fragShaderSrc = fragShaderStr.c_str();

	GLint result = GL_FALSE;
	int logLength;

	// Compile vertex shader
	std::cout << "Compiling vertex shader." << std::endl;
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);

	// Check vertex shader
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;

	// Compile fragment shader
	std::cout << "Compiling fragment shader." << std::endl;
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	// Check fragment shader
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
	std::cout << &fragShaderError[0] << std::endl;

	//std::cout << "Linking program" << std::endl;
	program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> programError((logLength > 1) ? logLength : 1);
	glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
	std::cout << &programError[0] << std::endl;

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

GLuint Shader::getShader() {
	glUseProgram(program);

	mat4 sca = Scale(DIVIDE_WINDOW, DIVIDE_WINDOW, 1);

	GLint loc = glGetUniformLocation(program, "scalef");
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, sca);
	}
	vec2 mv = vec2(defaultX - World_L, defaultY - World_B);

	GLint Mloc = glGetUniformLocation(program, "ModelView");
	if (Mloc != -1)
	{
		glUniform2fv(Mloc, 1, mv);
	}
	else {
		//std::cout << "get uniform error" << std::endl;
	}

	return program;
}

GLuint Shader::getShader2() {
	glUseProgram(program);

	vec4 mv = vec4(defaultX - World_L, defaultY - World_B,0,1);
	GLint Mloc = glGetUniformLocation(program, "wPos");

	if (Mloc != -1)
	{
		glUniform2fv(Mloc, 1, mv);
	}
	else {
		//std::cout << "get uniform error" << std::endl;
	}
	return program;
}