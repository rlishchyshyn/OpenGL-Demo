#include <iostream>
#include "Window.h"
#include "Mesh.h"
#include "Renderer.h"

#include "glm/gtx/normal.hpp"

const unsigned int WIDTH = 1024U;
const unsigned int HEIGHT = 768U;

const LookAt modelview = LookAt({glm::vec3{0.f, 0.f, 5.f},
                                 glm::vec3{0.f, 0.f, 0.f},
                                 glm::vec3{0.f, 1.f, 0.f}});

const Perspective projection = Perspective({55.f,
                                            static_cast<float>(WIDTH) / static_cast<float>(HEIGHT),
                                            0.01f,
                                            500.f});

const Light light = Light({glm::vec3(0.0f, 0.0f, 3.0f),
                           glm::vec3(0.4f, 0.4f, 0.4f),
                           glm::vec3(2.0f, 2.0f, 2.0f),
                           glm::vec3(1.0f, 1.0f, 1.0f)
                          });

int main() {
    Window window("IT Step Viewer", WIDTH, HEIGHT, modelview, projection, light);
    Mesh mesh;

    Triangle tr;
    tr.a = glm::vec3{-5.0f, 0.0f, 0.0f};
    tr.a.color = glm::vec3{1.0f, 0.0f, 0.0f};
    tr.b = glm::vec3{5.0f, 0.0f, 0.0f};
    tr.b.color = glm::vec3{0.0f, 0.0f, 1.0f};
    tr.c = glm::vec3{0.0f, 5.0f, 0.0f};
    tr.c.color = glm::vec3{0.0f, 1.0f, 0.0f};

    tr.normal = glm::triangleNormal(tr.a, tr.b, tr.c);

    Circle c(3.5f, {-.0f, .0f, .0f}, 20, glm::vec3(255.0f, 255.0f, 255.0f));
    mesh.push_back(tr);

    window.renderer().addMesh(mesh);
    window.renderer().addMesh(c.mesh);

    for (;;) {
        if (!window.update()) break;
    }

    return 0;
}
