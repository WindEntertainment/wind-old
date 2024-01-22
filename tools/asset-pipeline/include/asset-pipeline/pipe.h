#include <utils/utils.h>

namespace wind {
namespace asset_pipeline {

class Pipe {
public:
    virtual void compile(fs::path source, fs::path destination);
};

}  // namespace asset_pipeline
}  // namespace wind