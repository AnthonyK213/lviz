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

vec3 UnprojectPoint(float x, float y, float z) {
  mat4 inv = inverse(projection * view);
  vec4 point = inv * vec4(x, y, z, 1.0f);
  return point.xyz / point.w;
}

void main() {
  Near = UnprojectPoint(aPos.x, aPos.y, -1.0f);
  Far = UnprojectPoint(aPos.x, aPos.y, 1.0f);

  gl_Position = vec4(aPos, 0.0f, 1.0f);
}
)";

static const char *GRID_FS = R"(
#version 330 core

uniform mat4 view;
uniform mat4 projection;

in vec3 Near;
in vec3 Far;

out vec4 FragColor;

vec4 FragGrid(vec3 point) {
  vec2 coord = point.xy;
  vec2 deriv = fwidth(coord);
  float minX = min(deriv.x, 1.0f);
  float minY = min(deriv.y, 1.0f);

  if (-minY < point.y && point.y < minY) {
    return vec4(0.985f, 0.382f, 0.486f, 1.0f); // x-axis
  } else if (-minX < point.x && point.x < minX) {
    return vec4(0.382f, 0.985f, 0.486f, 1.0f); // y-axis
  } else {
    vec2 uv = fract(coord - 0.5f) - 0.5f;
    vec2 grid = abs(uv) / deriv;
    float line = min(grid.x, grid.y);
    return vec4(vec3(0.2f), 1.0f - min(line, 1.0f));
  }
}

float ComputeDepth(vec3 point) {
  vec4 clipSpacePos = projection * view * vec4(point, 1.0f);
  float depth = clipSpacePos.z / clipSpacePos.w;
  return (depth + 1.0f) * 0.5f;
}

float ComputeLinearDepth(vec3 point) {
  vec4 viewSpacePos = view * vec4(point, 1.0f);
  return -viewSpacePos.z;
}

void main() {
  float t = -(Near.z + 0.01f) / (Far.z - Near.z);
  vec3 fragPos =  Near + t * (Far - Near);

  FragColor = FragGrid(fragPos);
  FragColor *= smoothstep(0.3f, 0.0f, ComputeLinearDepth(fragPos) / 1000.0f);
  FragColor *= float(t > 0);

  gl_FragDepth = ComputeDepth(fragPos);
}
)";

Grid::Grid() : shader_(nullptr), vbo_(0), vao_(0), ibo_(0) {
  render::ShaderSource shader_source{};
  shader_source.vertex_shader = GRID_VS;
  shader_source.fragment_shader = GRID_FS;
  shader_ = std::make_unique<render::Shader>(shader_source);

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
  shader_->SetMat4("view", camera->GetViewMatrix());
  shader_->SetMat4("projection", camera->GetProjMatrix());

  glBindVertexArray(vao_);
  glDrawElements(GL_TRIANGLES, sizeof(GRID_INDICES) / sizeof(glm::u32),
                 GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

} // namespace canvas
} // namespace lviz
