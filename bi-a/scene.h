#pragma once
#include"globalHeader.h"
#include"model.h"
#include"shader.h"

class scene
{
public:
	scene();
	~scene();
	void displayModel(Model, Shader);
};

