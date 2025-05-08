#include <iostream>
extern "C" {
    #include <libavcodec/avcodec.h>
}

int main() {
    std::cout << "FFmpeg Version: " << av_version_info() << std::endl;
    return 0;
}
