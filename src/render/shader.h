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

  void SetBool(const std::string &name, bool value);

  void SetNums(const std::string &name, glm::u32 n_nums, const glm::f32 *nums);

  void SetVec3(const std::string &name, const glm::vec3 &vec3);

  void SetMat4(const std::string &name, const glm::mat4 &mat4);

private:
  GLuint prog_id_;
};

} // namespace render
} // namespace lviz

#endif
