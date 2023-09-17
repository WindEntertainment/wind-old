#include "utils.h"

namespace wind {
    namespace system {
        class Application {
        private:
            static bool isAlive;
        public:
            static void init();
            static int loop(std::function<void()> update);
            
            static void quit();
            static bool alive();
        };
    }
}