#include "Window.h"
#include <typeinfo>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

int Window::width;
int Window::height;

const char *Window::windowTitle = "GLFW Starter Project";
bool Window::on1 = true;
bool Window::on2 = true;
bool Window::on3 = true;
bool Window::isNormal = false;
int Window::rType = 1;
// Objects to display.
PointCloud *Window::bear;
PointCloud *Window::bunny;
PointCloud *Window::dragon;
PointCloud *Window::light;

// The object currently displaying.
PointCloud *Window::currentObj;

glm::mat4 Window::projection; // Projection matrix.

glm::vec3 Window::eye(0, 0, 20);   // Camera position.
glm::vec3 Window::center(0, 0, 0); // The point we are looking at.
glm::vec3 Window::up(0, 1, 0);     // The up direction of the camera.
glm::vec3 Window::lightPos(6, 6, -5);
glm::vec3 Window::lastPos(0, 0, 0);
glm::vec3 Window::dirLightPos(1, 0, 0);
glm::vec3 Window::spotLightPos(0, 1, 0);
// View matrix, defined by eye, center and up.
glm::mat4 Window::view = glm::lookAt(Window::eye, Window::center, Window::up);

GLuint Window::program;        // The shader program id.
GLuint Window::projectionLoc;  // Location of projection in shader.
GLuint Window::viewLoc;        // Location of view in shader.
GLuint Window::modelLoc;       // Location of model in shader.
GLuint Window::objectColorLoc; // Location of color in shader.
GLuint Window::lightPosLoc;
GLuint Window::lightColorLoc;
GLuint Window::viewPosLoc;
GLuint Window::ambiKLoc;
GLuint Window::diffKLoc;
GLuint Window::specKLoc;
GLuint Window::shinKLoc;

bool Window::initializeProgram()
{
  // Create a shader program with a vertex shader and a fragment shader.
  program = LoadShaders("/Users/sean/project/CSE167/PA2/PA2/shaders/shader.vert", "/Users/sean/project/CSE167/PA2/PA2/shaders/shader.frag");

  // Check the shader program.
  if (!program)
  {
    std::cerr << "Failed to initialize shader program" << std::endl;
    return false;
  }

  // Activate the shader program.
  glUseProgram(program);

  // Get the locations of uniform variables.
  projectionLoc = glGetUniformLocation(program, "projection");
  viewLoc = glGetUniformLocation(program, "view");
  modelLoc = glGetUniformLocation(program, "model");

  objectColorLoc = glGetUniformLocation(program, "objectColor");
  lightPosLoc = glGetUniformLocation(program, "lightPos");
  lightColorLoc = glGetUniformLocation(program, "lightColor");
  viewPosLoc = glGetUniformLocation(program, "viewPos");

  ambiKLoc = glGetUniformLocation(program, "ambiK");
  diffKLoc = glGetUniformLocation(program, "diffK");
  specKLoc = glGetUniformLocation(program, "specK");

  return true;
}

bool Window::initializeObjects()
{
  // Create a point cloud consisting of cube vertices.
  bunny = new PointCloud("bunny.obj", 1);
  bunny->color = glm::vec3(0.5, 0.5, 0.8);
  bunny->ambi = glm::vec3(0.1, 0.1, 0.1);
  bunny->diff = glm::vec3(0.1, 0.1, 0.1);
  bunny->spec = glm::vec3(1, 1, 1);

  bunny->shin = 10;

  // vec3(0, 0.1, 0.1); vec3(0, 0.1, 0.1); vec3(0, 0.1, 0.1);
  //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
  // vec3(0, 0.1, 0.1); vec3(0, 0.1, 0.1); vec3(0, 0.1, 0.1);
  //glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
  //glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);

  dragon = new PointCloud("dragon.obj", 1);
  dragon->color = glm::vec3(0.5, 0.9, 0.5);
  dragon->ambi = glm::vec3(0.1, 0.1, 0.1);
  dragon->diff = glm::vec3(1, 1, 1);
  dragon->spec = glm::vec3(0, 0, 0);
  dragon->shin = 0;

  bear = new PointCloud("bear.obj", 1);
  bear->color = glm::vec3(0.9, 0.3, 0.8);
  bear->ambi = glm::vec3(0.1, 0.1, 0.1);
  bear->diff = glm::vec3(1, 1, 1);
  bear->spec = glm::vec3(1, 1, 1);
  bear->shin = 100;

  light = new PointCloud("sphere.obj", 1);
  light->color = glm::vec3(0.3, 0.3, 0.7);
  currentObj = bunny;

  return true;
}

void Window::cleanUp()
{
  // Delete the shader program.
  glDeleteProgram(program);
}

GLFWwindow *Window::createWindow(int width, int height)
{
  // Initialize GLFW.
  if (!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return NULL;
  }

  // 4x antialiasing.
  glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
  // Apple implements its own version of OpenGL and requires special treatments
  // to make it uses modern OpenGL.

  // Ensure that minimum OpenGL version is 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Enable forward compatibility and allow a modern OpenGL context
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // Create the GLFW window.
  GLFWwindow *window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

  // Check if the window could not be created.
  if (!window)
  {
    std::cerr << "Failed to open GLFW window." << std::endl;
    glfwTerminate();
    return NULL;
  }

  // Make the context of the window.
  glfwMakeContextCurrent(window);

#ifndef __APPLE__
  // On Window and Linux, we need GLEW to provide modern OpenGL functionality.

  // Initialize GLEW.
  if (glewInit())
  {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return NULL;
  }
#endif

  // Set swap interval to 1.
  glfwSwapInterval(0);

  // Call the resize callback to make sure things get drawn immediately.
  Window::resizeCallback(window, width, height);

  return window;
}

void Window::resizeCallback(GLFWwindow *window, int width, int height)
{
#ifdef __APPLE__
  // In case your Mac has a retina display.
  glfwGetFramebufferSize(window, &width, &height);
#endif
  Window::width = width;
  Window::height = height;
  // Set the viewport size.
  glViewport(0, 0, width, height);

  // Set the projection matrix.
  Window::projection = glm::perspective(glm::radians(60.0),
                                        double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{
}

void Window::displayCallback(GLFWwindow *window)
{
  // Clear the color and depth buffers.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Specify the values of the uniform variables we are going to use.
  glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(currentObj->model));

  glUniform3fv(objectColorLoc, 1, glm::value_ptr(currentObj->color));

  glUniform3fv(glGetUniformLocation(program, "pl.pos"), 1, glm::value_ptr(Window::lightPos));
  glUniform3fv(glGetUniformLocation(program, "pl.color"), 1, glm::value_ptr(light->color));
  glUniform1f(glGetUniformLocation(program, "pl.on"), on1);

  glUniform3fv(glGetUniformLocation(program, "dl.dir"), 1, glm::value_ptr(dirLightPos));
  glUniform3fv(glGetUniformLocation(program, "dl.color"), 1, glm::value_ptr(glm::vec3(0.6, 0.2, 0.5)));
  glUniform1f(glGetUniformLocation(program, "dl.on"), on2);

  glUniform3fv(glGetUniformLocation(program, "sl.color"), 1, glm::value_ptr(glm::vec3(0.4, 0.3, 0.9)));
  glUniform3fv(glGetUniformLocation(program, "sl.dir"), 1, glm::value_ptr(spotLightPos));
  glUniform1f(glGetUniformLocation(program, "sl.beamWidth"), 100);
  glUniform1f(glGetUniformLocation(program, "sl.taper"), 0);
  glUniform1f(glGetUniformLocation(program, "sl.on"), on3);

  //glUniform3fv(viewPosLoc, 1, glm::value_ptr(view));
  glUniform3fv(ambiKLoc, 1, glm::value_ptr(currentObj->ambi));
  glUniform3fv(diffKLoc, 1, glm::value_ptr(currentObj->diff));
  glUniform3fv(specKLoc, 1, glm::value_ptr(currentObj->spec));
  glUniform1f(shinKLoc, currentObj->shin);

  glUniform1f(glGetUniformLocation(program, "isNormal"), isNormal);
  glUniform1f(glGetUniformLocation(program, "sl.beamWidth"), currentObj->shin);

  // Render the object.
  currentObj->draw();

  glUniform3fv(objectColorLoc, 1, glm::value_ptr(light->color));
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(light->model));

  glm::mat4 trans = glm::translate(lightPos);
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.3, 0.3, 0.3));
  light->model = trans * scale;
  light->draw();

  // Gets events, including input such as keyboard and mouse or window resizing.
  glfwPollEvents();
  // Swap buffers.
  glfwSwapBuffers(window);
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  // Check for a key press.
  if (action == GLFW_PRESS)
  {
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
      // Close the window. This causes the program to also terminate.
      glfwSetWindowShouldClose(window, GL_TRUE);
      break;
    case GLFW_KEY_1:
      rType = 1;
      break;
    case GLFW_KEY_2:
      rType = 2;
      break;
    case GLFW_KEY_3:
      rType = 3;
      break;
    case GLFW_KEY_4:
      // only dir light
      rType = 4;
      break;
    case GLFW_KEY_5:
      // only spot light
      rType = 5;
      break;
    case GLFW_KEY_Q:
      on1 = !on1;
      break;
    case GLFW_KEY_W:
      on2 = !on2;
      break;
    case GLFW_KEY_E:
      on3 = !on3;
      break;
    case GLFW_KEY_F1:
      currentObj = bunny;
      break;
    case GLFW_KEY_F2:
      currentObj = dragon;
      break;
    case GLFW_KEY_F3:
      currentObj = bear;
      break;
    case GLFW_KEY_N:
      isNormal = !isNormal;
      break;
    default:
      break;
    }
  }
}

void Window::scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
  if (yoffset > 0)
  {
    if (rType == 1)
    {
      glm::mat4 trans = glm::scale(glm::mat4(1.0f), glm::vec3(1.01, 1.01, 1.01));
      Window::currentObj->model *= trans;
    }
    else if (rType == 2)
    {
      glm::mat4 trans = glm::translate(glm::normalize(lightPos) * 0.1f);
      lightPos = glm::vec3(trans * glm::vec4(lightPos, 1));
    }
    else if (rType == 3)
    {
      glm::mat4 trans = glm::scale(glm::mat4(1.0f), glm::vec3(1.01, 1.01, 1.01));
      Window::currentObj->model *= trans;
      glm::mat4 tran = glm::translate(glm::normalize(lightPos) * 0.1f);
      lightPos = glm::vec3(tran * glm::vec4(lightPos, 1));
    }
  }
  else
  {
    if (rType == 1)
    {
      glm::mat4 trans = glm::scale(glm::mat4(1.0f), glm::vec3(0.99, 0.99, 0.99));
      Window::currentObj->model *= trans;
    }
    else if (rType == 2)
    {
      glm::mat4 trans = glm::translate(glm::normalize(lightPos) * -0.1f);
      lightPos = glm::vec3(trans * glm::vec4(lightPos, 1));
    }
    else if (rType == 3)
    {
      glm::mat4 trans = glm::scale(glm::mat4(1.0f), glm::vec3(0.99, 0.99, 0.99));
      Window::currentObj->model *= trans;
      glm::mat4 tran = glm::translate(glm::normalize(lightPos) * -0.1f);
      lightPos = glm::vec3(tran * glm::vec4(lightPos, 1));
    }
  }
}

glm::vec3 Window::trackBallMapping(double xpos, double ypos)
{
  glm::vec3 v;
  float d;

  v.x = (2.0 * xpos - Window::width) / (float)Window::width;
  v.y = (Window::height - 2.0 * ypos) / (float)Window::height;
  d = (glm::length(v) < 1.0 ? glm::length(v) : 1.0);
  v.z = sqrtf(1.001 - d * d);

  return -glm::normalize(v);
}

void Window::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
  int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  glm::vec3 curPos = trackBallMapping(xpos, ypos);
  if (state == GLFW_PRESS && Window::lastPos.x != 0)
  {
    glm::vec3 rotAxis = glm::cross(Window::lastPos, curPos);
    glm::mat4 rot = glm::rotate(glm::radians(1.5f), rotAxis);
    if (rType == 1)
    {
      // You rotate model
      Window::currentObj->model = rot * Window::currentObj->model;
    }
    else if (rType == 2)
    {
      // You only move light -> using point rotation given in the lecture
      lightPos = glm::vec3(rot * glm::vec4(lightPos, 0));
    }
    else if (rType == 3)
    {
      Window::currentObj->model = rot * Window::currentObj->model;
      light->model = rot * light->model;
      lightPos = glm::vec3(rot * glm::vec4(lightPos, 0));
      //dirLightPos = glm::vec3(rot * glm::vec4(dirLightPos, 0));
    }
    else if (rType == 4)
    {
      dirLightPos = glm::vec3(rot * glm::vec4(dirLightPos, 0));
    }
    else if (rType == 5)
    {
      spotLightPos = glm::vec3(rot * glm::vec4(spotLightPos, 0));
    }
  }
  Window::lastPos = curPos;
}

// YOu sshould have differnet model for light and object
