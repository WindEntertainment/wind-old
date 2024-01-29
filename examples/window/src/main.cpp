#include <cstdlib>
#include <utils/utils.h>

int main() {
    using namespace wind::math;

    ivec2 vec{2, 2};

    spdlog::info("({}, {})", vec.x, vec.y);

    return EXIT_SUCCESS;
}