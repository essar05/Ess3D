#pragma once

#include <Ess3D/definitions.h>
#include <string>
#include <GL/glew.h>
#include <cstdlib>
#include <fstream>
#include <map>

namespace Ess3D {

  enum ShaderType {
    VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER
  };

  class API Shader {
    public:
      explicit Shader(bool debugMode);
      ~Shader();

      void loadShader(ShaderType type, const std::string& shaderFilePath);

      void compileShaders();
      void linkShaders();

      void addAttribute(const std::string& attributeName);
      GLint getUniformLocation(const std::string& uniformName) const;

      void use() const;
      void unuse() const;

    private:
      int _attributeCount{};
      bool _debugMode;

      GLuint _programId;

      std::map<GLuint, GLuint> _shaderIds;

  };

}