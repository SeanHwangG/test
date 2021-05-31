#ifndef _OBJECT_H_
#define _OBJECT_H_
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

class Object
{
public:
    glm::mat4 model;
    glm::vec3 color;
	
	virtual void draw() = 0;
	virtual void update() = 0;
};

#endif

