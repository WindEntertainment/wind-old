
#include <utils/utils.h>

namespace wind {
namespace asset_pipeline {

using asset_id = unsigned long;

class AssetPipeline {
public:
    void load(fs::path importConfigPath);
};

}  // namespace asset_pipeline
}  // namespace wind