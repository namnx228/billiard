#include "scene.h"



scene::scene()
{
}

void scene::displayModel(Model activeModel, Shader shader)
{
	activeModel.draw(shader);
}


scene::~scene()
{
}
