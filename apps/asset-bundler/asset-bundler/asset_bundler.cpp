#include "asset_bundler.h"

namespace wind {
    namespace assets {
        void Bundler::regLoader(string reg_exp, ILoader* loader) {
            try {
                m_loaders.push_back(std::make_pair(
                    std::regex(reg_exp), loader
                ));
            } catch (std::regex_error& ex) {
                log().error() << "Can't create regex from '" << reg_exp << "': " << ex.what();
            }
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

            fs::recursive_directory_iterator it;
            try {
                it = fs::recursive_directory_iterator(_src);
            } catch (fs::filesystem_error& ex) {
                log().error() << "Asset Bundler: can't open source directory: " << ex.what();
                return;
            }

            auto num_assets = numberOfFilesInRecursiveDirectory(_src);
            auto header_size = num_assets * (sizeof(size_t) + sizeof(asset_id)) + sizeof(size_t);
            // header struct:
            // asset id (long) = asset offset (long) 

            write(output, (size_t)num_assets);
            output.seekp(header_size, std::ios_base::beg);
            
            uint resource_ind = 0;
            for (const auto& entry : it) {
                ISerializable* obj = nullptr;
                auto filename = entry.path().relative_path().string();
                
                for (const auto& pair : m_loaders) {
                    if (!std::regex_match(filename, pair.first))
                        continue;
                        
                    obj = pair.second->load(entry.path());
                    if (!obj) {
                        log().error() << "Asset Bundler: can't load resource: " << filename;
                        break;
                    }

                    try {
                        obj->id = getAssetIdByName(filename);

                        auto save_pos = output.tellp();
                        output.seekp(resource_ind * (sizeof(size_t) + sizeof(asset_id)) + sizeof(size_t), std::ios_base::beg);
    
                        write(output, obj->id);
                        write(output, (size_t)save_pos);

                        output.seekp(save_pos, std::ios_base::beg);

                        obj->serialize(output);
                    } catch (std::exception& ex) {
                        log().error() << "Asset Bundler: can't serialize resource: " << filename << " what(): " << ex.what();
                    }

                    break;
                }

                resource_ind += 1;

                if (!obj) {
                    log().warning() << "Asset Bundler: ignore resource: " << filename; 
                    continue;
                }

                delete obj;
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