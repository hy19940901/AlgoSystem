#include <iostream>
#include "../include/mp3_info.h"

int main() {
    std::string inputFile = "Scott McKenzie - San Francisco (Be Sure To Wear Flowers In Your Hair).mp3";
    extract_stream_info(inputFile);

    return 0;
}
