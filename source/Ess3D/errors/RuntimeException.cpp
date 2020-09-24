#include "RuntimeException.h"

namespace Ess3D {

  ERuntimeException::ERuntimeException(const std::string &anErrorMessage) {
    this->message = anErrorMessage;
    this->ErrorMessage = anErrorMessage.c_str();
  }

  const char *ERuntimeException::what() const noexcept {
    return this->ErrorMessage;
  }

  std::string ERuntimeException::getMessage() {
    return this->message;
  }

}