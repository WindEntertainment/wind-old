#include "asset-bundler/loaders/iloader.h"
#include <regex>

namespace wind {
    namespace assets {
        class Bundler {
        private:
            vector<std::pair<std::regex, ILoader*>> m_loaders;
        public:
            void regLoader(string reg_exp, ILoader* loader);

            void assembly(
                const string&& src,
                const string&& dst
            );  

            ~Bundler();
        };
    }
}