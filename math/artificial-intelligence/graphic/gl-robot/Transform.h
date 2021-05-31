//
//  Transform.hpp
//  pa3
//
//  Created by Gyuseung Hwang on 10/22/19.
//  Copyright © 2019 Gyuseung Hwang. All rights reserved.
//

#ifndef Transform_h
#define Transform_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>
#include <iostream>
#include <vector>
#include "Node.h"

class Transform : public Node
{
private:
  std::list<Node *> children;

public:
  Transform();
  ~Transform();
  glm::mat4 trans = glm::mat4(1.0f), rot = glm::mat4(1.0f);

  glm::mat4 trans1 = glm::mat4(1.0f), trans_1 = glm::mat4(1.0f);

  glm::mat4 rot1 = glm::mat4(1.0f), rot_1 = glm::mat4(1.0f);

  int bound = 180;

  //int check(glm::);
  void update(int time);
  void addChild(Node *child);
  void draw(glm::mat4 C);
};
#endif
