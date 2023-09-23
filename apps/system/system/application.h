#include "utils.h"

namespace wind {
    namespace system {
        class Application {
        private:
            static bool isAlive;
            static vector<std::function<void()>> terminate_event;
            static std::function<bool()> quit_event;
        public:
            static void init(std::function<bool()> try_quiting);
           
            static int terminate();
            static void addTerminateCallback(std::function<void()> callback);

            static int loop(std::function<void()> update);
            
            static void quit();
            static bool alive();
        };
    }
}