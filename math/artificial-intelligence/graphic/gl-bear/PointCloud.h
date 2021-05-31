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

class PointCloud : public Object
{
private:
	std::vector<glm::vec3> points, normals, step, out_vertices, out_normals;
    std::vector<glm::ivec3> indices;
	GLuint vao, vbos[2], num_step;
	GLfloat pointSize;
    
public:
	PointCloud(std::string objFilename, GLfloat pointSize);
	~PointCloud();
    
    GLboolean sw;
	void draw();
	void update();
    void transition(std::vector<glm::vec3>& pp);
	void updatePointSize(GLfloat size);
	void spin(float deg);
};

#endif

