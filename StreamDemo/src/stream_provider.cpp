// stream_provider.cpp
#include <memory>
#include "../include/stream_provider.h"
#include "../include/stream_provider_internal.h"

// Dynamically allocate StreamProvider using std::unique_ptr
static std::unique_ptr<StreamProvider> streamProvider(new StreamProvider());

void registerStreamCallback(StreamCallback cb) {
    streamProvider->registerCallback(cb);
}

void startStream() {
    streamProvider->startStream();
}
