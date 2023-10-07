#include "asset-bundler/loaders/iloader.h"
#include "asset-bundler/objects/text.h"

namespace wind {
    namespace assets {
        /*
            @details
            Loader for raw text files

            @return 
            Returns a reference to the text structure
            if the file was read successfully
            otherwise nullptr
        */
       
        class TextLoader : public ILoader {
        public:
            ISerializable* load(fs::path) override;
        };
    }
}