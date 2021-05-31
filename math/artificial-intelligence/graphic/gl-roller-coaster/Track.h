//
//  Track.h
//  PA4
//
//  Created by Gyuseung Hwang on 11/10/19.
//  Copyright © 2019 Gyuseung Hwang. All rights reserved.
//

#ifndef Track_h
#define Track_h

#include "Geometry.h"
#include "BezierCurve.h"
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class Track : public Geometry
{
public:
    int N_segment = 8;
    std::vector<BezierCurve> curves;
    std::vector<glm::vec3> points;
    Track(GLuint shader);
    void draw();
};

#endif /* Track_h */
