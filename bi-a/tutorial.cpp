#include "tutorial.h"


tutorial::tutorial()
{
	GLfloat tmpVertices[] = {
		-0.5f,-0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f };
	vertices = new GLfloat();
	*vertices = *tmpVertices;
	
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	const GLchar* tmpSourceVertex =
		"# version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main(){\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);}\0";
	const GLchar* tmpFragment =
		"# version 330 core\n"
		"out vec4 color;\n"
		"void main(){\n"
		"color = vec4(1.0f,0.5f,0.2f,1.0f);}\0";

	vertexShaderSource = tmpSourceVertex;
	fragmentShaderSource = tmpFragment;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkCompile(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkCompile(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

}

void tutorial::draw()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

}

void tutorial::checkCompile(GLuint shader)
{
	GLint success;
	GLchar info[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info);
		cout << "Error shader:" << info << endl;
		
	}
}

void tutorial::checkProgram(GLuint program)
{
	GLint success;
	GLchar info[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, info);
		cout << "Error program linker:" << info << endl;
	}
}


tutorial::~tutorial()
{
}
