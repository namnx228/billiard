	#include "model.h"


	Model::Model()
	{
	}

	Model::Model(string path)
	{
		this->loadModel(path);
		
	}

	GLint TextureFromFile(const char* path, string directory)
	{
		//Generate texture ID and load texture data 
		//glActiveTexture(GL_TEXTURE0);
		
		string filename = string(path);
		filename = directory + '/' + filename;
		GLuint textureID;
		glGenTextures(1, &textureID);
		int width, height;
		unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		// Assign texture to ID
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);
		return textureID;
	}

	void Model::loadModel(std::string path)
	{
		Assimp::Importer *imp = new Assimp::Importer();
		const aiScene* scene = imp->ReadFile(path, aiProcessPreset_TargetRealtime_Quality);
		//const aiScene* scene = imp->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			cout << "ERROR::ASSIMP::" << imp->GetErrorString() << endl;
			return;
		}
		this->dir = path.substr(0, path.find_last_of('/'));

		this->procNode(scene->mRootNode, scene);

	}

	void Model::procNode(aiNode* node, const aiScene* scene)
	{
		// Process all the node's meshes (if any)
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(this->procMesh(mesh, scene));
		}
		// Then do the same for each of its children
		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->procNode(node->mChildren[i], scene);
		}
	}

	mesh Model::procMesh(aiMesh* meshes, const aiScene* scene)
	{
		vector<mesh::Vertex> vertices;
		vector<GLuint> indices;
		vector<mesh::Texture> textures;

		for (GLuint i = 0; i < meshes->mNumVertices; i++)
		{
			mesh::Vertex vertex;
			// Process vertex positions, normals and texture coordinates
			glm::vec3 vector;

			vector.x = meshes->mVertices[i].x;
			vector.y = meshes->mVertices[i].y;
			vector.z = meshes->mVertices[i].z;
			vertex.Position = vector;
			

			vector.x = meshes->mNormals[i].x;
			vector.y = meshes->mNormals[i].y;
			vector.z = meshes->mNormals[i].z;
			vertex.Normal = vector;

			if (meshes->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				vec.x = meshes->mTextureCoords[0][i].x;
				vec.y = meshes->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;
			}
			else
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			vertices.push_back(vertex);
		}
		// Process indices
		for (GLuint i = 0; i < meshes->mNumFaces; i++)
		{
			aiFace face = meshes->mFaces[i];
			for (GLuint j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
			// Process material
	

		if (meshes->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[meshes->mMaterialIndex];
			vector<mesh::Texture> diffuseMaps = this->loadMaterialTextures(material,aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			vector<mesh::Texture> specularMaps = this->loadMaterialTextures(material,
				aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return mesh(vertices, indices, textures);
	}

	vector<mesh::Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
	{
		/*vector<mesh::Texture> textures;
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			mesh::Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->dir);
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
		}
		return textures;*/

		vector<mesh::Texture> textures;
		for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			GLboolean skip = false;
			for (GLuint j = 0; j < textures_loaded.size(); j++)
			{
				if (textures_loaded[j].path == str)
				{
					textures.push_back(textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{   // If texture hasn't been loaded already, load it
				mesh::Texture texture;
				texture.id = TextureFromFile(str.C_Str(), this->dir);
				texture.type = typeName;
				texture.path = str;
				textures.push_back(texture);
				this->textures_loaded.push_back(texture);  // Add to loaded textures
			}
		}
		return textures;
	}

	  /*void Model::draw(Shader shader)
	{
		for (GLuint i = 0; i < this->meshes.size(); i++)
			this->meshes[i].draw(shader);
	}*/

	void Model::draw(Shader shader)
	{
		for (GLuint i = 0; i < this->meshes.size(); i++)
			this->meshes[i].draw(shader);
	}


	
