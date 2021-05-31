#include "PointCloud.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include<stdio.h>
#include<errno.h>
#include<math.h>
#include<time.h>
using namespace std;

double INF = 99999999.0f;
PointCloud::PointCloud(std::string objFilename, GLfloat pointSize)
    : pointSize(pointSize)
{
    // set errno to zero to record the error message
    errno = 0;
    ifstream infile(objFilename);
    // if the file open failed, print out the error message
    if (errno != 0 && infile.is_open()) {
        cerr << strerror(errno) << endl;
    }

    // if the file is open and infile is successfully initialized
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            stringstream ss;
            ss << line;
            string tag;
            ss >> tag;
            if (tag == "v") {
                glm::vec3 point;
                ss >> point.x >> point.y >> point.z;
                points.push_back(point);
            }
            if (tag == "f") {
                string part;
                ss >> part;
                glm::ivec3 id;
                part = part.substr(0, part.find("//"));
                id.x = stoi(part) - 1;
                ss >> part;
                part = part.substr(0, part.find("//"));
                id.y = stoi(part) - 1;
                ss >> part;
                part = part.substr(0, part.find("//"));
                id.z = stoi(part) - 1;
            
                indices.push_back(id);
            }
            if (tag == "vn") {
                glm::vec3 point;
                ss >> point.x >> point.y >> point.z;
                normals.push_back(point);
            }
        }
    }
    else {
        cerr << "Can't open the file " << objFilename << endl;
    }
    infile.close();

    // arrays storing mins and max of xyz axis.
    float mnX = INF, mxX = -INF, mnY = INF, mxY = -INF, mnZ = INF, mxZ = -INF;
    
    for (auto p : points) {
        mnX = std::min(mnX, p.x);
        mxX = std::max(mxX, p.x);
        mnY = std::min(mnY, p.y);
        mxY = std::max(mxY, p.y);
        mnZ = std::min(mnZ, p.z);
        mxZ = std::max(mxZ, p.z);
    }

    float constant = 14;

    for (int i = 0; i != points.size(); i++) {
        float mX = (mnX + mxX) / 2.0, mY = (mnY + mxY) / 2.0, mZ = (mnZ + mxZ) / 2.0;
        float mxLen = max({mxX - mnX, mxX - mnX, mxX - mnX});
        points[i].x = (points[i].x - mX) / mxLen * constant;
        points[i].y = (points[i].y - mY) / mxLen * constant;
        points[i].z = (points[i].z - mZ) / mxLen * constant;
    }

    // Set the model matrix to an identity matrix.
    model = glm::mat4(1);
    // Set the color.
    color = glm::vec3(1, 0, 0);
    
    // Generate a vertex array (VAO) and a vertex buffer objects (VBO).
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbos);
    glBindVertexArray(vao);     // Bind to the VAO.

    // Bind to the first VBO. We will use it to store the points.
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_DYNAMIC_DRAW);
    // Enable vertex attribute 0. We will be able to access points through it.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // Bind to the second VBO. We will use it to store the normals.
    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_DYNAMIC_DRAW);
    // Enable vertex attribute 1. We will be able to access points through it.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    glGenBuffers(1, &ebo);
    // Bind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // Populate data in EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);
    
    // Unbind from the VBO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

PointCloud::~PointCloud()
{
    // Delete the VBO and the VAO.
    glDeleteBuffers(2, vbos);
    glDeleteVertexArrays(1, &vao);
}

void PointCloud::draw()
{
    // Bind to the VAO.
    glBindVertexArray(vao);
    // Draw points
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size() * 3, GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

void PointCloud::update()
{
    spin(0.1f);
}

void PointCloud::updatePointSize(GLfloat size)
{
    pointSize += size;
    if (pointSize < 0) pointSize = 0;
    if (pointSize > 100) pointSize = 100;
    glPointSize(pointSize);
}

void PointCloud::spin(float deg)
{
    // Update the model matrix by multiplying a rotation matrix
    model = glm::rotate(model, glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}
