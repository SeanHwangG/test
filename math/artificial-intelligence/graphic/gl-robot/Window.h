#ifndef _WINDOW_H_
#define _WINDOW_H_

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <vector>
#include <memory>

#include "Transform.h"
#include "Geometry.h"
#include "Node.h"
#include "Transform.h"
#include "Geometry.h"
#include "shader.h"

#include <typeinfo>
#include <iostream>

using namespace std;

class Transform;
class Window
{
public:
  static int width;
  static int height;
  static int time;
  static int frame;

  constexpr static const GLfloat nw = 1.53960071, nh = 1.15470053, fw = nw * 1000.0, fh = nh * 1000.0, nd = 1, fd = 1000;
  static const char *windowTitle;
  static glm::mat4 projection;
  static glm::mat4 view;
  // near far left right bot top
  static glm::vec3 eye, center, up, dir, right;
  static glm::vec3 ftl, ftr, fbl, fbr, ntl, ntr, nbl, nbr;
  static glm::vec3 nn, fn, ln, rn, bn, tn, nc, fc, lc, rc, bc, tc;
  static glm::vec3 lastPos;

  static const int nRobot = 400;

  static int count;

  static bool visible[nRobot];
  static Transform *robotP[nRobot];
  static Transform *sphereP[nRobot];
  static Transform *head2robot;
  static Transform *body2robot;
  static Transform *leye2robot;
  static Transform *reye2robot;
  static Transform *larm2robot;
  static Transform *rarm2robot;
  static Transform *tongue2robot;

  static Geometry *head;
  static Geometry *body;
  static Geometry *arms;
  static Geometry *eyes;
  static Geometry *sphere;
  static Geometry *tongue;

  static GLuint program;
  static bool initializeProgram();
  static bool initializeObject();
  static bool createRobot(int i, int j);
  static bool isNormal;
  static bool isSphere;
  static bool isCulling;
  static bool isDebug;

  static int inside(glm::vec3 point, float radius);

  static GLFWwindow *createWindow(int width, int height);

  static void cleanUp();
  static void resizeCallback(GLFWwindow *window, int width, int height);
  static void idleCallback();
  static void displayCallback(GLFWwindow *);
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
  static void calculateView();
  static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
  static glm::vec3 trackBallMapping(double xpos, double ypos);
};

#endif
