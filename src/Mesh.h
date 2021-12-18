#pragma once
#define _USE_MATH_DEFINES

#include <iostream>

#include <math.h>


#include <glm/vec3.hpp>

#include <vector>
#include <glm/gtx/normal.hpp>

struct Vertex : glm::vec3 {
    using glm::vec3::vec3;

    glm::vec3 color;

    Vertex(glm::vec3 vec3) : glm::vec3(vec3) {}
};

struct Triangle {
    Vertex a;
    Vertex b;
    Vertex c;

    glm::vec3 normal;
};

struct Circle {
    std::vector<Triangle> mesh;

    Circle(float radius, Vertex pos, int fragments, glm::vec3 color = glm::vec3(0)) {
        float prev_theta = 0;
        for (int i = 0; i < fragments; ++i) {
            float theta = i * float(M_PI) / float(fragments / 2);
            Triangle tr{};
            tr.a = glm::vec3{pos.x + radius * cosf(theta), pos.y + radius * sinf(theta), .0f};
            tr.b = glm::vec3{pos.x + radius * cosf(prev_theta), pos.y + radius * sinf(prev_theta), .0f};
            tr.c = glm::vec3{pos.x, pos.y, .0f};

            tr.a.color = color;
            tr.b.color = color;
            tr.c.color = color;

            prev_theta = theta;
            mesh.push_back(tr);
        }
        Triangle tr{};
        tr.a = glm::vec3{pos.x + radius * cosf(prev_theta), pos.y + radius * sinf(prev_theta), .0f};
        tr.b = glm::vec3{pos.x + radius * cosf(0), pos.y + radius * sinf(0), .0f};
        tr.c = glm::vec3{pos.x, pos.y, .0f};

        tr.a.color = color;
        tr.b.color = color;
        tr.c.color = color;

        mesh.push_back(tr);
    }
};

using Mesh = std::vector<Triangle>;
