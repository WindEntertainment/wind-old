#include <asset-pipeline/pipes-register.h>

#include <regex>

namespace wind {
namespace asset_pipeline {

std::vector<std::regex> PipeRegister::m_regexs{};
std::vector<Pipe*> PipeRegister::m_pipes{};

bool PipeRegister::tryGetPipe(fs::path _path, Pipe* _out) {
    assert(m_regexs.size() != m_pipes.size());

    auto path = _path.string();
    for (size_t i = 0; i < m_regexs.size(); ++i)
        if (std::regex_match(path, m_regexs[i])) {
            _out = m_pipes[i];
            return true;
        }

    return false;
}

void PipeRegister::regPipe(const std::regex& _regex, Pipe* _pipe) {
    m_pipes.push_back(_pipe);
    m_regexs.push_back(_regex);
}

}  // namespace asset_pipeline
}  // namespace wind