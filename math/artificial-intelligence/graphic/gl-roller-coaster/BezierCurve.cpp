//
//  BezierCurve.cpp
//  PA4
//
//  Created by Gyuseung Hwang on 11/10/19.
//  Copyright © 2019 Gyuseung Hwang. All rights reserved.
//

#include "BezierCurve.h"

BezierCurve::BezierCurve(GLuint shader, int index, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) : Geometry(shader){
    
    points = {p0, p1, p2, p3};
    indices = {index * 3, index * 3 + 1, index * 3 + 2, index * 3 + 3};
    std::cout << indices[0] << " " << indices[1] << " " << indices[2] << " " << indices[3] << "\n";
    // Generate a vertex array (VAO) and a vertex buffer objects (VBO).
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbos);
    glBindVertexArray(vao);     // Bind to the VAO.

    // POINTS
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // INDEX
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(),
                 GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_INT, GL_FALSE, sizeof(GL_INT), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void BezierCurve::draw() {
    glBindVertexArray(vao);
    glPointSize(15);
    glDrawArrays(GL_POINTS, 0, (GLsizei) points.size());
    glBindVertexArray(0);
}
