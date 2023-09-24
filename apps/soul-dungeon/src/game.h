#include "camera_controll.h"
#include <asset-bundler/bundle.h>

namespace soul_dungeon {
    class Game {
    private:
        Game* singlton;
        
        assets::Bundle m_bundle;
    public:
        assets::Bundle bundle() const;

        int play();
    };
}