#include "../include/log_initializer.hpp"
#include "../include/ffmpeg_handler.hpp"
#include "../include/taglib_metadata_reader.hpp"

#include <spdlog/spdlog.h>

#include <fcntl.h>
#include <unistd.h>

void suppress_ffmpeg_stderr() {
    int null_fd = open("/dev/null", O_WRONLY);
    if (null_fd != -1) {
        dup2(null_fd, STDERR_FILENO);  // Redirect stderr to /dev/null
        close(null_fd);
    }
}

int main(int argc, char* argv[]) {
    suppress_ffmpeg_stderr();
    
    log_initializer::init();
    spdlog::info("MediaInspector started");

    log_initializer::disable_console_output();

    FfmpegHandler handler("media/Adele-Hello.mp3");
    if (!handler.open()) {
        spdlog::error("Failed to open media file");
        return 1;
    }

    handler.print_media_info();

    auto taglib_logger = spdlog::get("taglib");
    if (taglib_logger) {
        TaglibMetadataReader reader("media/Adele-Hello.mp3");
        reader.print_to_log(taglib_logger);
    }

    return 0;
}