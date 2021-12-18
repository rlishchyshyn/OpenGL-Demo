#pragma once

#include "glad.h"
#include "GLFW/glfw3.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <string_view>
#include <memory>

typedef void (*GLFWframebuffersizefun)(GLFWwindow *, int, int);

class Renderer;

class EventLoop;

struct LookAt {
    glm::vec3 eye = glm::vec3(.0f, .0f, .0f);
    glm::vec3 center = glm::vec3(.0f, .0f, .0f);
    glm::vec3 up = glm::vec3(.0f, .0f, .0f);
};

struct Perspective {
    float fovy = 90.f;
    float aspect;
    float zNear = .01f;
    float zFar = 500.f;
};

struct Light {
    glm::vec3 position = glm::vec3(0);
    glm::vec3 ambient = glm::vec3(0);
    glm::vec3 specular = glm::vec3(0);
    glm::vec3 diffuse = glm::vec3(0);
};

class Window {
public:
    Window(std::string_view title, unsigned int width, unsigned int height,
           LookAt modelview,
           Perspective projection,
           Light light
    );

    ~Window();

    unsigned int getWidht();

    unsigned int getHeight();

    void setWidth(unsigned int width);

    void setHeight(unsigned int height);

    bool update();

    Renderer &renderer();

private:
    unsigned int _width;
    unsigned int _height;
    LookAt _modelview;
    Perspective _projection;
    Light _light;
    struct Impl;
    std::unique_ptr<Impl> _impl;

    static void resize_callback(GLFWwindow *window, int width, int height);

    void adapt(GLFWwindow *window, int width, int height);
};