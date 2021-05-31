#ifndef _OBJECT_H_
#define _OBJECT_H_

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

class Node
{
public:
  virtual void update(int time) = 0;
  virtual void draw(glm::mat4 C) = 0;
};

#endif
