#include <asset-pipeline/pipe.h>

namespace wind {
namespace asset_pipeline {

class ImgPipe : public Pipe {
public:
    void compile(const fs::path &_source,
                 const fs::path &_destination) override;

    ImgPipe() : Pipe("img"){};
};

} // namespace asset_pipeline
} // namespace wind