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

uniform float[2] aNearFar;
uniform mat4 view;
uniform mat4 projection;

in vec3 Near;
in vec3 Far;

out vec4 FragColor;

vec4 gen_grid(vec3 point, float scale, bool is_axis) {
  vec2 coord = point.xy * scale;
  vec2 dd = fwidth(coord);
  vec2 uv = fract(coord - 0.5) - 0.5;
  vec2 grid = abs(uv) / dd;
  float line = min(grid.x, grid.y);
  float min_x = min(dd.x, 1.0);
  float min_y = min(dd.y, 1.0);
  vec4 col = vec4(0.3);
  col.a = 1.0 - min(line, 1.0);

  if (-1.0 * min_x < point.x && point.x < 0.1 * min_x && is_axis)
    col.rgb = vec3(0.427, 0.909, 0.486);
  if (-1.0 * min_y < point.y && point.y < 0.1 * min_y && is_axis)
    col.rgb = vec3(0.984, 0.380, 0.490);

  return col;
}

float compute_depth(vec3 point) {
  vec4 clip_space = projection * view * vec4(point, 1.0);
  float clip_space_depth = clip_space.z / clip_space.w;
  float far = gl_DepthRange.far;
  float near = gl_DepthRange.near;
  float depth = (((far - near) * clip_space_depth) + near + far) / 2.0;
  return depth;
}

float compute_fade(vec3 point) {
  vec4 clip_space = projection * view * vec4(point, 1.0);
  float clip_space_depth = (clip_space.z / clip_space.w) * 2.0 - 1.0;
  float near = aNearFar[0];
  float far = aNearFar[1];
  float linear_depth = (2.0 * near * far) / (far + near - clip_space_depth * (far - near));
  return linear_depth / far;
}

void main() {
  float t = -Near.z / (Far.z - Near.z);
  vec3 R =  Near + t * (Far - Near);
  float is_on = float(t > 0);

  float fade = smoothstep(0.3, 0.0, compute_fade(R));
  FragColor = gen_grid(R, 1, true);
  FragColor *= fade;
  FragColor *= is_on;

  gl_FragDepth = compute_depth(R);
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
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  shader_->Use();
  camera->UpdateShader(shader_.get());
  glm::f32 near_far[2] = {camera->GetNear(), camera->GetFar()};
  shader_->Numbers("aNearFar", 2, near_far);

  glBindVertexArray(vao_);
  glDrawElements(GL_TRIANGLES, sizeof(GRID_INDICES) / sizeof(glm::u32),
                 GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

} // namespace canvas
} // namespace lviz
