#include "Window.h"
#include "Renderer.h"

#include <mutex>

#include <iostream>

struct Window::Impl {
    GLFWwindow *window = nullptr;
    Renderer *renderer = nullptr;
};

Window::Window(std::string_view title, unsigned int width, unsigned int height,
               LookAt modelview, Perspective projection, Light light
)
        : _impl(std::make_unique<Window::Impl>()), _width(width), _height(height),
          _modelview(modelview), _projection(projection), _light(light) {

    static std::once_flag glfwInitFlag;
    std::call_once(glfwInitFlag, []() {
        if (!glfwInit())
            exit(0);
    });

    _impl->window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.data(), nullptr, nullptr);
    if (_impl->window == nullptr) {
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(_impl->window);
    glfwSetWindowUserPointer(_impl->window, this);
    glfwSetFramebufferSizeCallback(_impl->window, &resize_callback);

    static std::once_flag gladInitFlag;
    std::call_once(gladInitFlag, []() {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            exit(0);
    });
    _impl->renderer = new Renderer();

    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(light.position));
    glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(light.ambient));
    glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(light.specular));
    glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(light.diffuse));

    glViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(glm::lookAt(modelview.eye, modelview.center, modelview.up)));

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(
            glm::value_ptr(glm::perspective(projection.fovy, projection.aspect, projection.zNear, projection.zFar)));

}

Window::~Window() = default;

unsigned int Window::getWidht() {
    return _width;
}

unsigned int Window::getHeight() {
    return _height;
}

void Window::setWidth(unsigned int width) {
    _width = width;
    glfwSetWindowSize(_impl->window, width, _height);
    adapt(_impl->window, width, _height);
}

void Window::setHeight(unsigned int height) {
    _height = height;
    glfwSetWindowSize(_impl->window, _width, height);
    adapt(_impl->window, _width, _height);
}

bool Window::update() {
    _impl->renderer->update();

    glfwSwapBuffers(_impl->window);
    glfwPollEvents();

    return !glfwWindowShouldClose(_impl->window);
}

Renderer &Window::renderer() {
    return *_impl->renderer;
}

void Window::resize_callback(GLFWwindow *window, int width, int height) {
    auto gl_window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    gl_window->adapt(window, width, height);
    gl_window->setHeight(height);
    gl_window->setWidth(width);
}

void Window::adapt(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    auto gl_window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    gl_window->_projection.aspect = static_cast<float>(width) / static_cast<float>(height);

    const auto projection = glm::perspective(gl_window->_projection.fovy, gl_window->_projection.aspect,
                                             gl_window->_projection.zNear, gl_window->_projection.zFar);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(projection));
}
