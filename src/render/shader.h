#ifndef _LVIZ_RENDER_SHADER_H
#define _LVIZ_RENDER_SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>

namespace lviz {
namespace render {

class Shader {
public:
  Shader(const char *vertex_shader, const char *fragment_shader);

  ~Shader();

  void Use() const;

  void SetMat4(const glm::mat4 &mat4, const std::string &name);

private:
  GLuint prog_id_;
};

} // namespace render
} // namespace lviz

#endif
