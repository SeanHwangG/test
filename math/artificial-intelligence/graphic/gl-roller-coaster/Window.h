#ifndef _WINDOW_H_
#define _WINDOW_H_
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
#include <iostream>

#include "Object.h"
#include "Skybox.h"
#include "Geometry.h"
#include "shader.h"
#include "Track.h"

class Window
{
public:
	static int width;
	static int height;
    static int current;
	static const char* windowTitle;
    static Track* track;
	static Skybox* skybox;
    static Geometry* sphere;
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::vec3 eye, center, up;
    static glm::vec3 lastPos;
    static GLuint sphere_shader;
    static GLuint skybox_shader;
    static GLuint point_shader;
    static glm::vec3 dir;
    static bool pause;
    static bool physics;
    static bool friction;
	static bool initializeProgram();
	static bool initializeObjects();
	static void cleanUp();
	static GLFWwindow* createWindow(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);
	static void idleCallback();
	static void displayCallback(GLFWwindow*);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
    static glm::vec3 trackBallMapping(double xpos, double ypos);
};

#endif
