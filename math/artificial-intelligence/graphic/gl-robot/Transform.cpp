//
//  Transform.cpp
//  pa3
//
//  Created by Gyuseung Hwang on 10/22/19.
//  Copyright © 2019 Gyuseung Hwang. All rights reserved.
//
#include "Transform.h"

Transform::Transform() {}

void Transform::draw(glm::mat4 C)
{
  for (Node *child : children)
  {
    child->draw(trans * C * rot);
  }
}

void Transform::addChild(Node *child)
{
  children.push_back(child);
}

void Transform::update(int time)
{
  if (time < bound)
  {
    trans = trans1 * trans;
    rot = rot1 * rot;
  }
  else
  {
    trans = trans_1 * trans;
    rot = rot_1 * rot;
  }
}
