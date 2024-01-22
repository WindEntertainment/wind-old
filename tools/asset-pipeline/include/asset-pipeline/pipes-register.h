#include <filesystem>
#include <map>
#include <regex>

#include "asset-pipeline.h"

namespace wind {
namespace asset_pipeline {

class PipeRegister {
    friend class AssetPipeline;

private:
    static std::map<std::regex, Pipe> m_pipes;

    static bool tryGetPipe(fs::path _path, Pipe& out) {
        auto path = _path.string();
        for (auto pair : m_pipes)
            if (std::regex_match(path, pair.first)) {
                out = pair.second;
                return true;
            }

        return false;
    }

public:
    static void regPipe(const std::regex& _extention, const Pipe& _pipe) {
        if (contains(m_pipes, _extention))
            return;

        m_pipes.insert_or_assign(_extention, _pipe);
    }
};

}  // namespace asset_pipeline
}  // namespace wind