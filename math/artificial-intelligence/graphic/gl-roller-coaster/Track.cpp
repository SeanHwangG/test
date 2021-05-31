//
//  Track.cpp
//  PA4
//
//  Created by Gyuseung Hwang on 11/10/19.
//  Copyright © 2019 Gyuseung Hwang. All rights reserved.
//
#include "Track.h"

Track::Track(GLuint shader) : Geometry(shader) {
    
    curves = {
        BezierCurve(shader, 0,
                        glm::vec3(-1.0f, 1.0f, 1.0f),
                        glm::vec3(-1.0f, -1.0f, 1.0f),
                        glm::vec3(1.0f, -1.0f, 1.0f),
                        glm::vec3(1.0f, 1.0f, 1.0f)),
        BezierCurve(shader, 1,
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        glm::vec3(-1.0f, 1.0f, -1.0f),
                        glm::vec3(-1.0f, -1.0f, -1.0f),
                        glm::vec3(1.0f, -1.0f, -1.0f)),
        BezierCurve(shader, 2,
                        glm::vec3(1.0f, -1.0f, -1.0f),
                        glm::vec3(1.0f, 1.0f, -1.0f),
                        glm::vec3(-2.0f, 2.0f, 2.0f),
                        glm::vec3(-2.0f, -2.0f, 2.0f)),
        BezierCurve(shader, 3,
                        glm::vec3(-2.0f, -2.0f, 2.0f),
                        glm::vec3(2.0f, -2.0f, 2.0f),
                        glm::vec3(2.0f, 2.0f, 2.0f),
                        glm::vec3(-2.0f, 2.0f, -2.0f)),
        BezierCurve(shader, 4,
                        glm::vec3(-2.0f, 2.0f, -2.0f),
                        glm::vec3(-2.0f, -2.0f, -2.0f),
                        glm::vec3(2.0f, -2.0f, -2.0f),
                        glm::vec3(2.0f, 2.0f, -2.0f)),
        BezierCurve(shader, 5,
                        glm::vec3(2.0f, 2.0f, -2.0f),
                        glm::vec3(-3.0f, 3.0f, 3.0f),
                        glm::vec3(-3.0f, -3.0f, 3.0f),
                        glm::vec3(3.0f, -3.0f, 3.0f)),
        BezierCurve(shader, 6,
                        glm::vec3(3.0f, -3.0f, 3.0f),
                        glm::vec3(3.0f, 3.0f, 3.0f),
                        glm::vec3(-3.0f, 3.0f, -3.0f),
                        glm::vec3(-3.0f, -3.0f, -3.0f)),
        BezierCurve(shader, 7,
                        glm::vec3(-3.0f, -3.0f, -3.0f),
                        glm::vec3(3.0f, -3.0f, -3.0f),
                        glm::vec3(3.0f, 3.0f, -3.0f),
                        glm::vec3(-1.0f, 1.0f, 1.0f))
    };
    model = glm::mat4(1);
    
    // Generate a vertex array (VAO) and a vertex buffer objects (VBO).
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbos);
    glBindVertexArray(vao);     // Bind to the VAO.

    // POINTS
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    // Unbind from the VBO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Track::draw() {
    //glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    for (BezierCurve c : curves) {
        c.draw();
        
    }
    // glBindVertexArray(vao);
    
    // uniform set color
    // glDrawArrays
    
    // glDrawElements(GL_LINES, (GLsizei) points.size(), GL_FLOAT, 0);
    // glBindVertexArray(0);
}
