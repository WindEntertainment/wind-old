#include <regex>

#include "asset-pipeline.h"

namespace wind {
namespace asset_pipeline {

class PipeRegister {
    friend class AssetPipeline;

private:
    static std::vector<std::regex> m_regexs;
    static std::vector<Pipe*> m_pipes;

    static bool tryGetPipe(fs::path _path, Pipe* _out);

public:
    static void regPipe(const char* _regex, Pipe* _pipe);
};

}  // namespace asset_pipeline
}  // namespace wind