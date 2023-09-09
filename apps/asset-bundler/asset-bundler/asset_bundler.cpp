#include "asset_bundler.h"

namespace wind {
    namespace assets {
        void Bundler::regLoader(string reg_exp, ILoader* loader) {
            m_loaders.push_back(std::make_pair(
                std::regex(reg_exp), loader
            ));
        }

        void Bundler::assembly(
            const string&& _src, 
            const string&& _dst
        ) {
            log().info() << "Asset Bundler: assembly " << _src;

            std::ofstream output(_dst, std::ofstream::binary);
            if (!output.is_open()) {
                log().error() << "Asset Bundler: can't create destination file: " << _dst;
                return;
            }

            for (const auto& entry : fs::directory_iterator(_src))
                for (const auto& pair : m_loaders) {
                    auto filename = entry.path().filename().string();
                    if (std::regex_match(filename, pair.first)) {
                        auto obj = pair.second->load(entry.path().c_str());
                        if (obj) {
                            try {
                                obj->serialize(output);
                            } catch (std::exception& ex) {
                                log().error() << "Asset Bundler: can't serialize resource:" << filename << " what():" << ex.what();
                            }
                            delete obj;
                        } else 
                            log().error() << "Asset Bundler: can't load resource:" << filename;
                    } else 
                        log().warning() << "Asset Bundler: ignore resource:" << filename;
                }

            output.close();
            log().info() << "Asset Bundler: assembly success";
        }

        Bundler::~Bundler() {
            for (auto pair : m_loaders)
                delete pair.second;
            m_loaders.clear();
        }
    }
}