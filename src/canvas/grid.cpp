#include "grid.h"
#include "camera.h"

#include <glm/glm.hpp>

namespace lviz {
namespace canvas {

static const glm::vec2 GRID_VERTICES[4] = {
    glm::vec2{-1.0f, -1.0f},
    glm::vec2{-1.0f, 1.0f},
    glm::vec2{1.0f, 1.0f},
    glm::vec2{1.0f, -1.0f},
};

static const glm::u32 GRID_INDICES[6] = {
    0, 1, 2, 0, 2, 3,
};

static const char *GRID_VS = R"(
#version 330 core

layout(location = 0) in vec2 aPos;

uniform mat4 view;
uniform mat4 projection;

out vec3 Near;
out vec3 Far;

vec3 unproject_point(float x, float y, float z) {
  mat4 inv = inverse(projection * view);
  vec4 unproj_point = inv * vec4(x, y, z, 1.0f);
  return unproj_point.xyz / unproj_point.w;
}

void main() {
  Near = unproject_point(aPos.x, aPos.y, -1.0f);
  Far = unproject_point(aPos.x, aPos.y, 1.0f);

  gl_Position = vec4(aPos, 0.0f, 1.0f);
}
)";

static const char *GRID_FS = R"(
#version 330 core

uniform float[2] camNearFar;
uniform mat4 view;
uniform mat4 projection;

in vec3 Near;
in vec3 Far;

out vec4 FragColor;

vec4 grid_color(vec3 point) {
  vec2 coord = point.xy;
  vec2 dd = fwidth(coord);
  float minX = min(dd.x, 1.0);
  float minY = min(dd.y, 1.0);

  if (-minY < point.y && point.y < minY) {
    return vec4(0.985, 0.382, 0.486, 1.0); // x-axis
  } else if (-minX < point.x && point.x < minX) {
    return vec4(0.382, 0.985, 0.486, 1.0); // y-axis
  } else {
    vec2 uv = fract(coord - 0.5) - 0.5;
    vec2 grid = abs(uv) / dd;
    float line = min(grid.x, grid.y);
    return vec4(vec3(0.2), 1.0 - min(line, 1.0));
  }
}

float compute_depth(vec3 point) {
  vec4 clipSpace = projection * view * vec4(point, 1.0);
  float clipSpaceDepth = clipSpace.z / clipSpace.w;
  float far = gl_DepthRange.far;
  float near = gl_DepthRange.near;
  float depth = (((far - near) * clipSpaceDepth) + near + far) / 2.0;
  return depth;
}

float compute_fade(vec3 point) {
  vec4 clipSpace = projection * view * vec4(point, 1.0);
  float clipSpaceDepth = (clipSpace.z / clipSpace.w) * 2.0 - 1.0;
  float near = camNearFar[0];
  float far = camNearFar[1];
  float linearDepth = (2.0 * near * far) / (far + near - clipSpaceDepth * (far - near));
  return linearDepth / far;
}

void main() {
  float t = -Near.z / (Far.z - Near.z);
  vec3 point =  Near + t * (Far - Near);

  FragColor = grid_color(point);
  FragColor *= smoothstep(0.3, 0.0, compute_fade(point));
  FragColor *= float(t > 0);

  gl_FragDepth = compute_depth(point);
}
)";

Grid::Grid() : shader_(nullptr), vbo_(0), vao_(0), ibo_(0) {
  shader_ = std::make_unique<render::Shader>(GRID_VS, GRID_FS);

  glGenVertexArrays(1, &vao_);

  glGenBuffers(1, &ibo_);
  glGenBuffers(1, &vbo_);

  glBindVertexArray(vao_);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GRID_VERTICES), GRID_VERTICES,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GRID_INDICES), GRID_INDICES,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

Grid::~Grid() {
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &ibo_);
  glDeleteBuffers(1, &vbo_);
  glDeleteVertexArrays(1, &vao_);
}

void Grid::Draw(Camera *camera) {
  shader_->Use();

  glm::f32 near_far[2] = {camera->GetNear(), camera->GetFar()};
  shader_->SetNums("camNearFar", 2, near_far);
  shader_->SetMat4("view", camera->GetViewMatrix());
  shader_->SetMat4("projection", camera->GetProjMatrix());

  glBindVertexArray(vao_);
  glDrawElements(GL_TRIANGLES, sizeof(GRID_INDICES) / sizeof(glm::u32),
                 GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

} // namespace canvas
} // namespace lviz
