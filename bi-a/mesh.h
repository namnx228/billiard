#pragma once
#include"globalHeader.h"
#include<assimp/types.h>
#include<vector>
#include"shader.h"

#include<sstream>
class mesh
{
public:

	struct Vertex{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct Texture{
		GLuint id;
		string type;
		aiString path;
	};

	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	mesh();
	mesh(vector<Vertex>, vector<GLuint>, vector<Texture> textures);
	void draw(Shader shader);
	//void draw();
	~mesh();

private:
	GLuint VAO, VBO, EBO;
	void setMesh();
};

