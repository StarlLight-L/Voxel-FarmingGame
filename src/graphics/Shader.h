#pragma once

#include <filesystem>
#include <string_view>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace craft::graphics {

// Owns a linked GLSL program and provides helpers for setting its uniforms.
// A valid OpenGL context must exist for the lifetime of each Shader.
class Shader {
 public:
  // Compiles the two shader files and links them into one GPU program.
  Shader(const std::filesystem::path& vertexPath,
         const std::filesystem::path& fragmentPath);
  ~Shader();

  // An OpenGL program has one owner, so Shader objects cannot be copied.
  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

  // Makes this program active for later draw calls and uniform updates.
  void use() const;

  // Sends a 4x4 matrix to the named GLSL uniform.
  void setMat4(std::string_view name, const glm::mat4& value) const;

  // Sends a three-component vector to the named GLSL uniform.
  void setVec3(std::string_view name, const glm::vec3& value) const;

 private:
  [[nodiscard]] int uniformLocation(std::string_view name) const;

  unsigned int program_ = 0;
};

}  // namespace craft::graphics
