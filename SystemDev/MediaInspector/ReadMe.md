# MediaInspector

**MediaInspector** is a C++20-based utility that extracts and logs detailed metadata and audio stream information from media files (e.g., `.mp3`, `.mp4`). It integrates **FFmpeg**, **TagLib**, and **spdlog** to provide robust logging and inspection functionality.

---

## 🖥️ System Environment

- **Operating System**: Ubuntu 22.04 LTS
- **Compiler**: `g++ (Ubuntu 13+)` with C++20 support
- **Architecture**: x86_64

---

## 📦 Dependencies

This project requires the following libraries to be installed:

| Library      | Purpose                       | Install Command (APT)                                     |
|--------------|-------------------------------|------------------------------------------------------------|
| FFmpeg       | Parse and decode media files  | `sudo apt install libavformat-dev libavcodec-dev libavutil-dev` |
| TagLib       | Read ID3 metadata             | `sudo apt install libtag1-dev`                             |
| spdlog       | Logging library               | `sudo apt install libspdlog-dev`                           |
| fmt          | Fast formatting for spdlog    | `sudo apt install libfmt-dev`                              |

Ensure your package index is up to date:

```bash
sudo apt update
