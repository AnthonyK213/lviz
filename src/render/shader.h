#ifndef _LVIZ_RENDER_SHADER_H
#define _LVIZ_RENDER_SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include <string>

namespace lviz {
namespace render {

class Shader {
public:
  Shader();

  GLuint GetProgId() const {
    return prog_id_;
  }

  bool Load();

  void Use() const;

  void Unload();

  void SetMat4(const glm::mat4 &mat4, const std::string &name);

private:
  GLuint prog_id_;
};

} // namespace render
} // namespace lviz

#endif
