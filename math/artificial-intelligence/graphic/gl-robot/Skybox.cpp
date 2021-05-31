//
//  Geometry.cpp
//  pa3
//
//  Created by Gyuseung Hwang on 10/22/19.
//  Copyright © 2019 Gyuseung Hwang. All rights reserved.
//
#include "Geometry.h"

GLuint Geometry::program;

std::vector<std::string> split(std::string s, std::string delim)
{
  std::vector<std::string> ret;
  size_t pos = 0;
  while ((pos = s.find_first_of(delim)) != std::string::npos)
  {
    ret.push_back(s.substr(0, pos));
    s.erase(0, pos + delim.length());
  }
  ret.push_back(s);
  return ret;
}

Geometry::Geometry(std::string objFilename, GLuint program, GLfloat scale, glm::mat4 rot)
{
  this->program = program;
  std::ifstream infile(objFilename);

  // if the file is open and infile is successfully initialized
  if (infile.is_open())
  {
    std::string line;
    while (getline(infile, line))
    {
      std::stringstream ss;
      ss << line;
      std::string tag;
      ss >> tag;
      if (tag == "v")
      {
        glm::vec3 point;
        ss >> point.x >> point.y >> point.z;
        point = glm::vec4(point, 1) * rot;
        input_vertices.push_back(point);
      }
      if (tag == "vn")
      {
        glm::vec3 point;
        ss >> point.x >> point.y >> point.z;
        point = glm::vec4(point, 1);
        input_normals.push_back(point);
      }
      if (tag == "f")
      {
        std::string tok;
        std::vector<std::string> strs = split(line.substr(2), " ");

        for (std::string s : strs)
        {
          std::vector<std::string> ints = split(s, "/");
          input_vI.push_back(std::stoi(ints[0]));
          input_nI.push_back(std::stoi(ints[2]));
        }
      }
    }
  }
  else
  {
    std::cerr << "Can't open the file " << objFilename << std::endl;
  }
  infile.close();
  for (unsigned i = 0; i < input_vI.size(); i++)
  {
    vertices.push_back(input_vertices[input_vI[i] - 1]);
    if (i < input_nI.size())
      normals.push_back(input_normals[input_nI[i] - 1]);
    indices.push_back(i);
  }
  for (unsigned long i = input_vI.size(); i < input_nI.size(); i++)
  {
    normals.push_back(input_normals[input_nI[i] - 1]);
  }

  rescale(scale);

  //     Set the model matrix to an identity matrix.
  color = glm::vec3(1, 1, 1);
  //rot = glm::mat4(1);
  //normals = ;
  //vertices = rot;

  // Generate a vertex array (VAO) and a vertex buffer objects (VBO).
  glGenVertexArrays(1, &vao);
  glGenBuffers(2, vbos);
  glBindVertexArray(vao); // Bind to the VAO.

  // Bind to the first VBO. We will use it to store the points.
  glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
  // Pass in the data.
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size() * 3, vertices.data(), GL_DYNAMIC_DRAW);
  // Enable vertex attribute 0. We will be able to access points through it.
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

  // Bind to the second VBO. We will use it to store the normals.
  glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
  // Pass in the data.
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size() * 3, normals.data(), GL_DYNAMIC_DRAW);
  // Enable vertex attribute 1. We will be able to access points through it.
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

  glGenBuffers(1, &ebo);
  // Bind buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  // Populate data in EBO
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);

  // Unbind from the VBO.
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  // Unbind from the VAO.
  glBindVertexArray(0);
}

Geometry::~Geometry()
{
  // Delete the VBO and the VAO.
  glDeleteBuffers(2, vbos);
  glDeleteVertexArrays(1, &vao);
}

void Geometry::draw(glm::mat4 model)
{
  glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniform3fv(glGetUniformLocation(program, "color"), 1, glm::value_ptr(color));

  if (isSphere)
  {
    //std::cout << vertices.size() << "\n";
    glBindVertexArray(vao);
    // Draw points
    glDrawElements(GL_LINES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
  }
  else
  {
    glBindVertexArray(vao);
    // Draw points
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
  }
}

void Geometry::update(int time)
{
}

void Geometry::rescale(float constant)
{
  // arrays storing mins and max of xyz axis.
  float INF = 1e6;

  // arrays storing mins and max of xyz axis.
  float mnX = INF, mxX = -INF, mnY = INF, mxY = -INF, mnZ = INF, mxZ = -INF;

  for (auto p : vertices)
  {
    mnX = std::min(mnX, p.x);
    mxX = std::max(mxX, p.x);
    mnY = std::min(mnY, p.y);
    mxY = std::max(mxY, p.y);
    mnZ = std::min(mnZ, p.z);
    mxZ = std::max(mxZ, p.z);
  }

  for (int i = 0; i != vertices.size(); i++)
  {
    float mX = (mnX + mxX) / 2.0, mY = (mnY + mxY) / 2.0, mZ = (mnZ + mxZ) / 2.0;
    float mxLen = std::max({mxX - mnX, mxX - mnX, mxX - mnX});
    vertices[i].x = (vertices[i].x - mX) / mxLen * constant;
    vertices[i].y = (vertices[i].y - mY) / mxLen * constant;
    vertices[i].z = (vertices[i].z - mZ) / mxLen * constant;
  }
}
