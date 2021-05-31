#ifndef _POINT_CLOUD_H_
#define _POINT_CLOUD_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>

#include "Object.h"

class PointCloud
{
private:
  std::vector<glm::vec3> points, normals;
  std::vector<glm::ivec3> indices;
  GLuint vao, vbos[2], ebo;
  GLfloat pointSize;

public:
  PointCloud(std::string objFilename, GLfloat pointSize);
  ~PointCloud();

  glm::mat4 model;
  glm::vec3 color;
  glm::vec3 diff, spec, ambi;
  float shin;
  std::vector<glm::vec3> rescale(std::vector<glm::vec3> points, float constant);
  void draw();
  void transition(std::vector<glm::vec3> &pp);
  void updatePointSize(GLfloat size);
  void spin(float velocity, glm::vec3 rotAxis);
};

#endif
