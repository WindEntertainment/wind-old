#pragma once
#include "utils.h"

namespace wind {
    namespace system {
        class Application {
        private:
            static bool is_alive;
            static float delta_time;

            static vector<std::function<void()>> OnTerminateEvent;
            static std::function<bool()> OnQuitEvent;
        public:
            static void init(std::function<bool()> try_quiting);
           
            static int terminate();
            static void addTerminateCallback(std::function<void()> callback);

            static int loop(std::function<void()> update);
            
            static void quit(); 

            static bool alive();
            static float deltaTime();
        };
    }
}