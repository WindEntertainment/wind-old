#include "pipe.h"

namespace wind {
namespace asset_pipeline {

using asset_id = unsigned long;

class AssetPipeline {
public:
    void compileDirectory(const fs::path& source, const fs::path& destination,
                          const fs::path& cache);

    void compileFile(const fs::path& source, const fs::path& destination);
};

}  // namespace asset_pipeline
}  // namespace wind