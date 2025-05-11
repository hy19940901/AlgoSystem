#include "../include/log_initializer.hpp"
#include "../include/ffmpeg_handler.hpp"
#include "../include/taglib_metadata_reader.hpp"

#include <spdlog/spdlog.h>

#include <fcntl.h>
#include <unistd.h>

void SuppressFfmpegStderr() {
    int null_fd = open("/dev/null", O_WRONLY);
    if (null_fd != -1) {
        dup2(null_fd, STDERR_FILENO);  // Redirect stderr to /dev/null
        close(null_fd);
    }
}

int main(int argc, char* argv[]) {
    SuppressFfmpegStderr();
    
    log_initializer::Init();
    spdlog::info("MediaInspector started");

    log_initializer::DisableConsoleOutput();

    FfmpegHandler handler("media/Adele-Hello.mp3");
    if (!handler.Open()) {
        spdlog::error("Failed to open media file");
        return 1;
    }

    handler.PrintMediaInfo();

    auto taglib_logger = spdlog::get("taglib");
    if (taglib_logger) {
        TaglibMetadataReader reader("media/Adele-Hello.mp3");
        reader.PrintToLog(taglib_logger);
    }

    return 0;
}