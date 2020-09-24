#pragma once

#include "definitions.h"
#include <string>
#include <exception>

namespace Ess3D {
  class API ERuntimeException : public std::exception {

    private:
      const char* ErrorMessage;
      std::string message;

    public:

      explicit ERuntimeException(const std::string& anErrorMessage);

      ~ERuntimeException() override = default;

      const char* what() const noexcept override;

      std::string getMessage();

  };
}