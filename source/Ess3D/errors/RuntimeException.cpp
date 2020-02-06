#pragma once

#include <string>
#include <exception>

namespace Ess3D {
  class ERuntimeException: public std::exception {

    private:
      const char* ErrorMessage;
      std::string message;

    public:

      explicit ERuntimeException(const std::string& anErrorMessage) {
        this->message = anErrorMessage;
        this->ErrorMessage = anErrorMessage.c_str();
      }

      ~ERuntimeException() override = default;

      const char* what() const override {
        return this->ErrorMessage;
      }

      std::string getMessage() {
        return this->message;
      }

  };
}