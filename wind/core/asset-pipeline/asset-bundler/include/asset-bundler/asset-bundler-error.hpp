#include <exception>
#include <fmt/format.h>

namespace wind {
namespace assets {

class AssetBundlerError : public std::exception {
private:
  std::string m_message;

public:
  template <typename... T>
  AssetBundlerError(std::string _message, T&&... _args) noexcept {
    m_message = fmt::vformat(_message, fmt::make_format_args(_args...));
  }

  virtual ~AssetBundlerError() = default;

  virtual const char* what() const noexcept override {
    return m_message.c_str();
  }
};

} // namespace assets
} // namespace wind