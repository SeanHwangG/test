//
//  Geometry.hpp
//  pa3
//
//  Created by Gyuseung Hwang on 10/22/19.
//  Copyright © 2019 Gyuseung Hwang. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include "Node.h"
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

class Geometry : public Node
{
private:
  GLuint vao, vbos[2], ebo;

  std::vector<glm::vec3> input_vertices, input_normals;
  std::vector<GLuint> input_vI, input_nI;
  GLfloat scale;
  // rearranged input
  std::vector<GLuint> indices;
  std::vector<glm::vec3> vertices, normals;

public:
  Geometry(std::string objFilename, GLuint program, GLfloat scale, glm::mat4 rot = glm::mat4(1));
  ~Geometry();
  glm::vec3 color;
  glm::mat4 rot;
  void rescale(float constant);
  bool isSphere = false;
  static GLuint program;
  void update(int time);
  void draw(glm::mat4 model);
};
#endif /* Geometry_hpp */
