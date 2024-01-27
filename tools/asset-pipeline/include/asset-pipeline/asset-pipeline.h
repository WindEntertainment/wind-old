#include <utils/utils.h>

namespace wind {
namespace asset_pipeline {

using asset_id = unsigned long;

class AssetPipeline {
public:
    void linkDirectory(const fs::path& source, const fs::path& destination);
    void compileDirectory(const fs::path& source, const fs::path& destination);
    void compileFile(const fs::path& source, const fs::path& destination);
    void clearUnusedCache(const fs::path& source, const fs::path& cache);

private:
    fs::recursive_directory_iterator createRecursiveIterator(const fs::path& path);
};

}  // namespace asset_pipeline
}  // namespace wind