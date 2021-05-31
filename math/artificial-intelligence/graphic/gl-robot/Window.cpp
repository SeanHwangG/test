#include "Window.h"

int Window::width;
int Window::height;
int Window::frame;
int Window::count = 0;
bool Window::isNormal = false;
bool Window::isCulling = true;
bool Window::isSphere = true;
bool Window::isDebug = false;

GLuint Window::program;

const char *Window::windowTitle = "PA3";

Transform *Window::robotP[nRobot];
Transform *Window::sphereP[nRobot];
Transform *Window::head2robot;
Transform *Window::body2robot;
Transform *Window::larm2robot;
Transform *Window::rarm2robot;
Transform *Window::leye2robot;
Transform *Window::reye2robot;
Transform *Window::tongue2robot;

Geometry *Window::head;
Geometry *Window::body;
Geometry *Window::arms;
Geometry *Window::eyes;
Geometry *Window::sphere;
Geometry *Window::tongue;

glm::mat4 Window::projection; // Projection matrix.

bool Window::visible[nRobot];

glm::vec3 Window::lastPos;

glm::vec3 Window::eye(0, 5, 5);    // Camera position.
glm::vec3 Window::center(0, 0, 0); // The point we are looking at.
glm::vec3 Window::up(0, 1, 0);     // The up direction of the camera.
glm::vec3 Window::right(1, 0, 0);
glm::vec3 Window::dir = glm::normalize(Window::center - Window::eye);
glm::mat4 Window::view = glm::lookAt(Window::eye, Window::center, Window::up);

// corner point for near and far plane
glm::vec3 Window::ftl, Window::ftr, Window::fbl, Window::fbr,
    Window::ntl, Window::ntr, Window::nbl, Window::nbr;
// normal and center point for near, far, left, right, bottom, top planes
glm::vec3 Window::nn, Window::fn, Window::ln, Window::rn, Window::bn, Window::tn, Window::nc, Window::fc, Window::lc, Window::rc, Window::bc, Window::tc;

bool Window::initializeProgram()
{
  // Create a shader program with a vertex shader and a fragment shader.
  program = LoadShaders("/Users/sean/project/CSE167/PA3/shaders/shader.vert", "/Users/sean/project/CSE167/PA3/shaders/shader.frag");

  // Set view frustum plane
  calculateView();

  // Check the shader program.
  if (!program)
  {
    std::cerr << "Failed to initialize shader program" << std::endl;
    return false;
  }

  // Activate the shader program.
  glUseProgram(program);

  return true;
}

bool Window::initializeObject()
{
  head = new Geometry("images/head_s.obj", program, 0.55);
  head->color = glm::vec3(0.1, 0.1, 0.1);
  body = new Geometry("images/body_s.obj", program, 0.5);
  body->color = glm::vec3(0.9, 0.7, 0.4);
  arms = new Geometry("images/limb_s.obj", program, 0.1); //glm::rotate(glm::radians(-10.0f), glm::vec3(0, 0.2, 0.2)));
  arms->color = glm::vec3(0.9, 0.7, 0.4);
  tongue = new Geometry("images/limb_s.obj", program, 0.08, glm::rotate(glm::radians(100.0f), glm::vec3(1, 0, 0)));
  tongue->color = glm::vec3(1, 0, 0);

  eyes = new Geometry("images/eyeball_s.obj", program, 0.1);
  eyes->color = glm::vec3(0.2, 0.2, 0.2);
  sphere = new Geometry("images/sphere.obj", program, 1);
  sphere->isSphere = true;
  sphere->color = glm::vec3(0, 0.5, 0.5);

  glm::mat4 r = glm::translate(glm::vec3(0, 0.2, 0)) *
                glm::rotate(glm::radians(0.3f), glm::vec3(1, 0, 0)) *
                glm::translate(glm::vec3(0, -0.2, 0));
  glm::mat4 r_1 = glm::inverse(r);
  glm::mat4 rb = glm::translate(glm::vec3(0, 0.2, 0)) *
                 glm::rotate(glm::radians(0.1f), glm::vec3(0, 1, 0)) *
                 glm::translate(glm::vec3(0, -0.2, 0));
  glm::mat4 rb_1 = glm::inverse(rb);

  head2robot = new Transform();
  head2robot->trans = glm::translate(glm::vec3(0, 0.4, 0));
  //head2robot->color = glm::translate(glm::vec3(0, 0.001, 0));

  body2robot = new Transform();
  body2robot->trans = glm::translate(glm::vec3(0, 0, 0));
  //body2robot->rot = rot;
  body2robot->rot_1 = rb;
  body2robot->rot1 = rb_1;

  larm2robot = new Transform();
  larm2robot->trans = glm::translate(glm::vec3(-0.30, -0.3, 0));
  larm2robot->rot_1 = r;
  larm2robot->rot1 = r_1;

  rarm2robot = new Transform();
  rarm2robot->trans = glm::translate(glm::vec3(0.30, -0.3, 0));
  rarm2robot->rot_1 = r;
  rarm2robot->rot1 = r_1;

  leye2robot = new Transform();
  leye2robot->trans = glm::translate(glm::vec3(-0.1, 0.2, 0.2));
  //leye2robot->rot = rot;
  leye2robot->rot1 = r;
  leye2robot->rot_1 = r_1;

  reye2robot = new Transform();
  reye2robot->trans = glm::translate(glm::vec3(0.1, 0.2, 0.2));
  //reye2robot->rot = rot;
  reye2robot->rot1 = r;
  reye2robot->rot_1 = r_1;

  tongue2robot = new Transform();
  tongue2robot->trans = glm::translate(glm::vec3(0, 0, 0.25));
  tongue2robot->trans1 = glm::translate(glm::vec3(0, 0, -0.001));
  tongue2robot->trans_1 = glm::translate(glm::vec3(0, 0, 0.001));

  int idx = 0;
  for (int i = -sqrt(nRobot - 1) / 2; i <= sqrt(nRobot - 1) / 2; i++)
  {
    for (int j = -sqrt(nRobot - 1) / 2; j <= sqrt(nRobot - 1) / 2; j++)
    {
      robotP[idx] = new Transform();
      sphereP[idx] = new Transform();
      sphereP[idx]->trans = glm::translate(glm::vec3(i, -0.1, j));
      sphereP[idx]->addChild(sphere);

      robotP[idx]->trans = glm::translate(glm::vec3(i, 0, j));
      robotP[idx]->addChild(head2robot);
      robotP[idx]->addChild(body2robot);
      robotP[idx]->addChild(leye2robot);
      robotP[idx]->addChild(reye2robot);
      robotP[idx]->addChild(larm2robot);
      robotP[idx]->addChild(rarm2robot);
      robotP[idx]->addChild(tongue2robot);
      idx++;
    }
  }

  head2robot->addChild(head);
  body2robot->addChild(body);
  leye2robot->addChild(eyes);
  reye2robot->addChild(eyes);
  body2robot->addChild(body);
  larm2robot->addChild(arms);
  rarm2robot->addChild(arms);
  tongue2robot->addChild(tongue);

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
  GLFWwindow *window = glfwCreateWindow(width, height, to_string(count).c_str(), NULL, NULL);

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
  Window::projection = glm::perspective(glm::radians(60.0), // fov
                                        double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{
  head2robot->update(frame);
  body2robot->update(frame);
  larm2robot->update(frame);
  rarm2robot->update(frame);
  tongue2robot->update(frame);
  if (++frame == 360)
    frame = 0;
}

// near, far, left, right, bottom, top planes
int Window::inside(glm::vec3 point, float rad)
{
  int ret = 0;
  if (glm::dot(point - nc, nn) > rad)
  {
    ret++;
  }
  if (glm::dot(point - fc, fn) > rad)
  {
    ret++;
  }
  if (glm::dot(point - lc, ln) > rad)
  {
    ret++;
  }
  if (glm::dot(point - rc, rn) > rad)
  {
    ret++;
  }
  if (glm::dot(point - bc, bn) > rad)
  {
    ret++;
  }
  if (glm::dot(point - tc, tn) > rad)
  {
    ret++;
  }
  return ret;
}

void Window::displayCallback(GLFWwindow *window)
{
  // Clear the color and depth buffers.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUniform3fv(glGetUniformLocation(program, "pl.pos"), 1, glm::value_ptr(eye));
  glUniform3fv(glGetUniformLocation(program, "pl.color"), 1, glm::value_ptr(glm::vec3(1, 1, 1)));

  glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(program, "viewPos"), 1, GL_FALSE, glm::value_ptr(view));
  glUniform1f(glGetUniformLocation(program, "isNormal"), isNormal);
  glfwSetWindowTitle(window, to_string(count).c_str());

  int idx = 0;
  for (int i = -sqrt(nRobot - 1) / 2; i <= sqrt(nRobot - 1) / 2; i++)
  {
    for (int j = -sqrt(nRobot - 1) / 2; j <= sqrt(nRobot - 1) / 2; j++)
    {
      visible[idx] = (inside(glm::vec3(i, -0.1, j), 1) == 6);
      idx++;
    }
  }

  count = 0;
  for (int i = 0; i < nRobot; i++)
  {
    if (!isCulling || visible[i])
    {
      robotP[i]->draw(glm::mat4(1.0f));
      count++;
    }
    if (visible[i] && isSphere)
      sphereP[i]->draw(glm::mat4(1.0f));
  }

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
    case GLFW_KEY_C:
      isCulling = !isCulling;
      break;
    case GLFW_KEY_D:
      isDebug = !isDebug;
      break;
    case GLFW_KEY_S:
      isSphere = !isSphere;
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
    glm::mat4 trans = glm::translate(glm::normalize(eye) * 0.1f);
    eye = glm::vec3(trans * glm::vec4(eye, 1));
    view = glm::lookAt(Window::eye, Window::center, Window::up);
  }
  else
  {
    glm::mat4 trans = glm::translate(-glm::normalize(eye) * 0.1f);
    eye = glm::vec3(trans * glm::vec4(eye, 1));
    view = glm::lookAt(Window::eye, Window::center, Window::up);
  }
  if (!isDebug)
  {
    calculateView();
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

void Window::calculateView()
{
  fc = eye + fd * dir;
  nc = eye + nd * dir;

  ftl = fc + (fh)*up - (fw)*right;
  ftr = fc + (fh)*up + (fw)*right;
  fbl = fc - (fh)*up - (fw)*right;
  fbr = fc - (fh)*up + (fw)*right;
  ntl = nc + up * (nh)-right * (nw);
  ntr = nc + up * (nh) + right * (nw);
  nbl = nc - up * (nh)-right * (nw);
  nbr = nc - up * (nh) + right * (nw);

  lc = (ftl + nbl) / 2.0f;
  rc = (ftr + nbr) / 2.0f;
  bc = (nbl + fbr) / 2.0f;
  tc = (ntl + ftr) / 2.0f;

  nn = dir;
  fn = -dir;
  ln = glm::normalize(glm::cross(ftl - fbl, nbl - fbl));
  rn = glm::normalize(glm::cross(ntr - nbr, fbr - nbr));
  bn = glm::normalize(glm::cross(fbl - fbr, nbr - fbr));
  tn = glm::normalize(glm::cross(ntl - ntr, ftr - ntr));
}

void Window::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
  int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
  glm::vec3 curPos = trackBallMapping(xpos, ypos);
  if (state == GLFW_PRESS && Window::lastPos.x != 0)
  {
    glm::vec3 rotAxis = glm::cross(Window::lastPos, curPos);
    glm::mat4 rot = glm::rotate(glm::radians(0.3f), rotAxis);
    dir = rot * glm::vec4(dir, 0);
    center = glm::vec4(eye, 1) + rot * glm::vec4(center - eye, 1);

    view = glm::lookAt(Window::eye, Window::center, Window::up);
  }

  Window::lastPos = curPos;
}
