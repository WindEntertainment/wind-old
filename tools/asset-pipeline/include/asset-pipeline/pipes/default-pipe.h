#include <asset-pipeline/pipe.h>

namespace wind {
class DefaultPipe : public asset_pipeline::Pipe {
private:
    const char* c_id = "TxtPipe";

public:
    void compile(const fs::path& _source, const fs::path& _destination) override;
};
}  // namespace wind