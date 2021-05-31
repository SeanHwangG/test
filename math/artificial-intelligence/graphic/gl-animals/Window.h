#ifndef _WINDOW_H_
#define _WINDOW_H_

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

#include "Object.h"
#include "Cube.h"
#include "PointCloud.h"
#include "shader.h"

class Window
{
public:
  static int width;
  static int height;
  static int rType;
  static const char *windowTitle;
  static Cube *cube;
  static PointCloud *cubePoints;
  static PointCloud *bear;
  static PointCloud *bunny;
  static PointCloud *dragon;
  static PointCloud *light;
  static bool on1;
  static bool on2;
  static bool isNormal;
  static bool on3;
  static PointCloud *currentObj;
  static glm::mat4 projection;
  static glm::mat4 view;
  static glm::vec3 eye, center, up, lightPos, dirLightPos, spotLightPos;
  static glm::vec3 lastPos;
  static GLuint program, projectionLoc, viewLoc, modelLoc;
  static GLuint objectColorLoc, lightPosLoc, lightColorLoc, viewPosLoc, ambiKLoc, diffKLoc, specKLoc, shinKLoc;

  static bool initializeProgram();
  static bool initializeObjects();
  static void cleanUp();
  static GLFWwindow *createWindow(int width, int height);
  static void resizeCallback(GLFWwindow *window, int width, int height);
  static void idleCallback();
  static void displayCallback(GLFWwindow *);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
  static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
  static glm::vec3 trackBallMapping(double xpos, double ypos);
};

#endif
