#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "devil.lib")
#pragma comment(lib, "ilu.lib")
#pragma comment(lib, "ilut.lib")
#pragma comment(lib, "assimp.lib")
#pragma comment(lib, "SOIL.lib")
#endif

#include<windows.h>

#include <gl/glew.h>
#include<gl/glut.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include"scene.h"
#include"model.h"
/*#include "camera.hpp"
#include "vertex.hpp"
#include "SceneManager.hpp"
#include "ResourceManager.hpp"
#include "Constant.hpp"
#include "Ball.hpp"
#include "handling.hpp"
*/

//#define PATH "resource/stol_bilyard.obj"
#define PATH "resource/TournamentTable.lwo"


using namespace std;

//SceneManager sceneManager;
//ResourceManager resourceManager;

void setExperimental()
{
	glewExperimental = GL_TRUE;
	glewInit();
}

void init(int argc, char *argv[]){
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	
	glutCreateWindow("bi-a");
	setExperimental();

	fprintf(stdout, "======================= System Info =======================\n");
	fprintf(stdout, "\tVendor: %s\n", glGetString(GL_VENDOR));
	fprintf(stdout, "\tRenderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, "\tGL Version: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "\tGLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	fprintf(stdout, "\tGLEW Version: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, "===========================================================\n");

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	/*glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POLYGON_OFFSET_LINE);*/
	//glEnable(GL_DEPTH_TEST);

	

	//resourceManager.load(Constant::RESOURCE_FILE);
	//sceneManager.load(Constant::SCENE_FILE, &resourceManager);
}

void displayFunc(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	scene displayScene;
	displayScene.displayModel(*(new model(PATH)));
	setExperimental();
	glBegin(GL_LINE);
	glColor3b(255, 0, 0);
	glVertex2d(100, 100);
	glVertex2d(300, 300);
	glEnd();
	glutWireCube(0.5);
	//sceneManager.renderScene(0);
	//cout << "View point = " << sceneManager.getScene(0)->getUsingCamera()->getViewPoint() << endl;
	//import *imp = new import();
	//imp->load("resource/TournamentTable.lwo");
	/*glBegin(GL_LINES);
	glVertex2d(100, 100);
	glVertex2d(300, 300);
	glEnd();*/
	glutSwapBuffers();
	//glFlush();
}

void idleFunc(){
	glutPostRedisplay();
}

void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, 640 / 480, 0, 100);
	
}



/*int main(int argc, char *argv[]){
	init(argc, argv);
	//glutInit(argc, argv;)

	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	//sceneManager.getScene(0)->setUsingCamera(0);
	//Keyboard::setCamera(sceneManager.getScene(0)->getUsingCamera());
	//Keyboard::setSceneManager(&sceneManager);
//	glutSpecialFunc(Keyboard::specialKeyFunc);
//	glutKeyboardFunc(Keyboard::keyboardFunc);

/*	Mouse::setCamera(sceneManager.getScene(0)->getUsingCamera());
	Mouse::setWindow(Constant::SCREEN_WIDTH, Constant::SCREEN_HEIGHT);
	Mouse::setControllObject((Ball *)(sceneManager.getScene(0)->objects[1]));
	glutMouseFunc(Mouse::mouseFunc);
	glutMotionFunc(Mouse::mouseMotionFunc);
	//glutMouseWheelFunc(mouseWheel);
	myInit();
	glutMainLoop();

	//sceneManager.unload();
//	resourceManager.unload();

	return 0;
}*/