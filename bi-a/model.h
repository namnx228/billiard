#pragma once
#include<string>
#include <assimp/scene.h>
#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>
#include<SOIL.h>
#include"globalHeader.h"
#include"mesh.h"
#include"shader.h"

class Model
{
public:
	Model();
	Model(string path);

	
	void loadModel(std::string);
	void draw(Shader);
	//id draw();
private:
	vector<mesh> meshes;
	vector<mesh::Texture> textures_loaded;
	string dir;
	
	void procNode(aiNode*, const aiScene*);
	mesh procMesh(aiMesh*, const aiScene*);
	vector<mesh::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string);
	


	
};

