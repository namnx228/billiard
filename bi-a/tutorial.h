#pragma once
#include"globalHeader.h"
class tutorial
{
public:
	tutorial();
	~tutorial();
	GLfloat  *vertices;
	GLuint VBO,VAO;
	const GLchar *vertexShaderSource, *fragmentShaderSource;
	GLuint vertexShader, fragmentShader;
	GLuint shaderProgram;

	void checkCompile(GLuint);
	void checkProgram(GLuint);
	void draw();
};

