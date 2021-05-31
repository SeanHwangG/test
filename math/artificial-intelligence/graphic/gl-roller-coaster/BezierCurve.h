//
//  BezierCurve.hpp
//  PA4
//
//  Created by Gyuseung Hwang on 11/10/19.
//  Copyright © 2019 Gyuseung Hwang. All rights reserved.
//

#ifndef BezierCurve_h
#define BezierCurve_h

#include <stdio.h>

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Geometry.h"

class BezierCurve : public Geometry
{
public:
    std::vector<glm::vec3> points;
    std::vector<int> indices;
    GLuint vao, vbos[2];
    BezierCurve(GLuint shader, int index, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
    void draw();
};

#endif
