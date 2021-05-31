#include "Window.h"

int Window::width;
int Window::height;

const char* Window::windowTitle = "GLFW Starter Project";

// Objects to display.
Skybox * Window::skybox;
Geometry* Window::sphere;
Track* Window::track;

glm::mat4 Window::projection; // Projection matrix.
glm::vec3 Window::eye(0, 0, 10); // Camera position.
glm::vec3 Window::center(0, 0, 0); // The point we are looking at.
glm::vec3 Window::up(0, 1, 0); // The up direction of the camera.
glm::vec3 Window::dir = glm::normalize(Window::center - Window::eye);

glm::mat4 Window::view = glm::lookAt(Window::eye, Window::center, Window::up);
glm::vec3 Window::lastPos;

int Window::current = 0;
GLuint Window::sphere_shader;
GLuint Window::skybox_shader;
GLuint Window::point_shader;
bool Window::pause = false;
bool Window::physics = false;
bool Window::friction = false;

bool Window::initializeProgram() {
    // Create a shader program with a vertex shader and a fragment shader.
    sphere_shader = LoadShaders("shaders/sphere.vert", "shaders/sphere.frag");
    skybox_shader = LoadShaders("shaders/skybox.vert", "shaders/skybox.frag");
    point_shader = LoadShaders("shaders/point.vert", "shaders/point.frag");

    // Check the shader program.
    if (!sphere_shader || !skybox_shader || !point_shader)
    {
        std::cerr << "Failed to initialize shader program" << std::endl;
        return false;
    }
    std::cout<< point_shader << "[0]\n";
    
    return true;
}

bool Window::initializeObjects()
{
    // Create a point cloud consisting of cube vertices.
    sphere = new Geometry("images/sphere.obj", sphere_shader);
    sphere->model = glm::translate(glm::vec3(1,-1,1));
    skybox = new Skybox(skybox_shader);
    skybox->model = glm::mat4(1);
    track = new Track(point_shader);

    return true;
}

void Window::cleanUp()
{
    delete skybox;
    delete sphere;
    glDeleteProgram(sphere_shader);
    glDeleteProgram(skybox_shader);
}

GLFWwindow* Window::createWindow(int width, int height)
{
    // Initialize GLFW.
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return NULL;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

    if (!window)
    {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return NULL;
    }

    // Make the context of the window.
    glfwMakeContextCurrent(window);

#ifndef __APPLE__
    // On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

    // Initialize GLEW.
    if (glewInit())
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return NULL;
    }
#endif

    glfwSwapInterval(0);

    // Call the resize callback to make sure things get drawn immediately.
    Window::resizeCallback(window, width, height);

    return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
    // In case your Mac has a retina display.
    glfwGetFramebufferSize(window, &width, &height);
#endif
    Window::width = width;
    Window::height = height;
    // Set the viewport size.
    glViewport(0, 0, width, height);

    // Set the projection matrix.
    Window::projection = glm::perspective(glm::radians(60.0),
        double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{
}

void Window::displayCallback(GLFWwindow* window)
{
    // Clear the color and depth buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(skybox_shader);
    glUniformMatrix4fv(glGetUniformLocation(skybox_shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(skybox_shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    skybox->draw();
    
    glUseProgram(sphere_shader);
    //printf("%s %s", glm::to_string(projection), glm::to_string(view));
    glUniformMatrix4fv(glGetUniformLocation(sphere_shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(sphere_shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    
    sphere->draw();
    
    glUseProgram(point_shader);
    glUniform1f(glGetUniformLocation(point_shader, "current"), current);
    glUniformMatrix4fv(glGetUniformLocation(point_shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(point_shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    track->draw();
    
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Check for a key press.
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            // Close the window. This causes the program to also terminate.
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        case GLFW_KEY_F:
                friction = !friction;
            break;
        case GLFW_KEY_V:
                physics = !physics;
            break;
        case GLFW_KEY_X:
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                
            }
            else{
                
            }
            break;
        case GLFW_KEY_Y:
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                
            }
            else{
                
            }
            break;
        case GLFW_KEY_Z:
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                
            } else{
                
            }
            break;
        case GLFW_KEY_P:
            pause = !pause;
            break;
        case GLFW_KEY_RIGHT:
            if (current == 23)  current = 0;
            else                current++;
            break;
        case GLFW_KEY_LEFT:
            if (current == 0)   current = 23;
            else                current--;
            break;
        default:
            break;
        }
    }
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        glm::mat4 trans = glm::translate(glm::normalize(eye) * 0.1f);
        eye = glm::vec3(trans * glm::vec4(eye, 1));
        view = glm::lookAt(Window::eye, Window::center, Window::up);
    }
    else {
        glm::mat4 trans = glm::translate(-glm::normalize(eye) * 0.1f);
        eye = glm::vec3(trans * glm::vec4(eye, 1));
        view = glm::lookAt(Window::eye, Window::center, Window::up);
    }
}

glm::vec3 Window::trackBallMapping(double xpos, double ypos) {
    glm::vec3 v;
    
    v.x = (2.0 * xpos - Window::width) / (float)Window::width;
    v.y = (Window::height - 2.0 * ypos) / (float)Window::height;
    float d = (glm::length(v) < 1.0? glm::length(v): 1.0);
    v.z = sqrtf(1.001 - d*d);
    
    return -glm::normalize(v);
}

void Window::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    glm::vec3 curPos = trackBallMapping(xpos, ypos);
    if (state == GLFW_PRESS && Window::lastPos.x != 0) {
        glm::vec3 rotAxis = glm::cross(Window::lastPos, curPos);
        glm::mat4 rot = glm::rotate(glm::radians(0.3f), rotAxis);
        dir = rot * glm::vec4(dir, 0);
        center = glm::vec4(eye, 1) + rot * glm::vec4(center - eye, 1);
        view = glm::lookAt(Window::eye, Window::center, Window::up);
    }
    
    Window::lastPos = curPos;
}
