extern "C" {
#include <libavformat/avformat.h>
}

#include "../include/ffmpeg_handler.hpp"

FfmpegHandler::FfmpegHandler(const std::string& path)
    : file_path_(path), format_ctx_(nullptr) {}

FfmpegHandler::~FfmpegHandler() {
    if (format_ctx_) {
        avformat_close_input(reinterpret_cast<AVFormatContext**>(&format_ctx_));
    }
}

bool FfmpegHandler::open() {
    AVFormatContext* ctx = nullptr;
    if (avformat_open_input(&ctx, file_path_.c_str(), nullptr, nullptr) != 0) {
        spdlog::error("Failed to open media file: {}", file_path_);
        return false;
    }
    if (avformat_find_stream_info(ctx, nullptr) < 0) {
        spdlog::error("Failed to find stream info");
        avformat_close_input(&ctx);
        return false;
    }
    format_ctx_ = ctx;
    return true;
}

void FfmpegHandler::print_media_info() const {
    auto ctx = reinterpret_cast<AVFormatContext*>(format_ctx_);
    av_dump_format(ctx, 0, file_path_.c_str(), 0);

    for (unsigned int i = 0; i < ctx->nb_streams; ++i) {
        if (ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            print_audio_info(ctx->streams[i]);
        }
    }

    spdlog::info("[GLOBAL METADATA]");
    AVDictionaryEntry* tag = nullptr;
    while ((tag = av_dict_get(ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
        spdlog::info("{}: {}", tag->key, tag->value);
    }
}

void FfmpegHandler::print_audio_info(void* stream_ptr) const {
    auto stream = reinterpret_cast<AVStream*>(stream_ptr);
    auto codecpar = stream->codecpar;
    spdlog::info("[AUDIO STREAM]");
    spdlog::info("Codec ID: {}", codecpar->codec_id);
    spdlog::info("Sample Rate: {}", codecpar->sample_rate);
    spdlog::info("Channels: {}", codecpar->ch_layout.nb_channels);
    spdlog::info("Bitrate: {}", codecpar->bit_rate);
}
