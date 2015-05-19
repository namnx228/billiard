#define GLEW_STATIC


#include"globalHeader.h"


#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include"model.h"
#include"scene.h"
#include"tutorial.h"
#include"shader.h"
#include"camera.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;




#define TABLE "resource/TournamentTable.obj"
//#define TABLE "resource/table2/Snooker_Table.obj"
#define BALL "resource/Balls/Ball_"
#define NUM_OF_BALL 2
//#define PATH "resource/Balls/Ball_1.obj"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.1f;
GLfloat lastFrame = 0.0f;
glm::vec3 position[NUM_OF_BALL];

scene displayScene;
Shader *shader;
Model *table, ball[NUM_OF_BALL];

string findBallPath(int i)
{
	
	return to_string(i) + ".obj";
}

void readPosition()
{
	FILE *stream;
	freopen_s( &stream,"resource/position.txt", "r", stdin);
	GLfloat x, y, z;
	for (int i = 1; i <= NUM_OF_BALL; i++)
	{
		fscanf_s(stream, "%f %f %f", &x, &y, &z);
		position[i].x = x;
		position[i].y = y;
		position[i].z = z;
	}
	fclose(stream);
}

void init()
{
	readPosition();


	table = new Model(TABLE);
	for (int i = 1; i <= NUM_OF_BALL; i++)
	{
		string ballPath = BALL + findBallPath(i);
		ball[i].loadModel(ballPath);
	}
	position[0].x = position[0].y = position[0].z = 0;
	shader = new Shader("resource/shader.vertex", "resource/shader.fragment");
}

void cleanMem()
{
	delete shader;
	delete table;
}

void draw(Model *activeModel, int pos)
{
	glm::mat4 model;
	//glPushMatrix();
	model = glm::translate(model, position[pos]); // Translate it down a bit so it's at the center of the scene
	if (pos)
	{
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// It's a bit too big for our scene, so scale it down
	}
	else
	{
	//	model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));	// It's a bit too big for our scene, so scale it down
	}
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

	displayScene.displayModel(*activeModel, *shader);
	//glPopMatrix();
}

void draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Use();   
	// Transformation matrices

	glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	

	glm::mat4 view = camera.GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	// Draw the loaded model
	draw(table,0);
	for (int i = 1; i <= NUM_OF_BALL; i++) draw(&ball[i], i);
}

int main(int argc, char *argv[])  {
	// Initialize GLUT.
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);
	init();
//	tu = new tutorial();
	while (!glfwWindowShouldClose(window))
	{
		
		glfwPollEvents();

		draw();
		
		glfwSwapBuffers(window);
	}

	cleanMem();
	glfwTerminate();

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	keys[key] = true;
	Do_Movement();
	keys[key] = false;
}

#pragma region "User input"

// Moves/alters the camera positions based on user input
void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

#pragma endregion

/* ----------------------------------------------------------------------- */



