# StreamProvider SDK Demo

This is a minimal, modular SDK-style demo project written in C++20. It demonstrates the use of C/C++ interoperability, modular callback interfaces, and per-module logging using `log4cxx`. It simulates a simple streaming data pipeline between internal logic and an external consumer.

---

## 🚀 Features

* **Modular design**: Each module is clearly separated (provider, server, logging).
* **C-style callback API**: Easily integrates with C or external systems.
* **Internal implementation isolation**: `stream_provider_internal` hides logic details.
* **Custom log4cxx logging**: Each module logs independently with different files.
* **Fully compilable**: Includes `Makefile`, `log4cxx.properties`, and demo source code.

---

## 🧱 Project Structure

```
.
├── include/
│   ├── log_config.h                # Logging initializer
│   ├── stream_provider.h          # C interface (register/start)
│   ├── stream_provider_internal.h # Internal C++ logic
│   └── stream_server.h            # Demo consumer using the API
│
├── src/
│   ├── log_config.cpp
│   ├── stream_provider.cpp
│   ├── stream_provider_internal.cpp
│   └── stream_server.cpp
│
├── logs/                          # Output log files (after run)
│
├── bin/                           # Built executable & shared lib
├── build/                         # Intermediate object files
│
├── log4cxx.properties             # Log4cxx module-based config
├── Makefile                       # Build script
└── README.md                      # This file
```

---

## ⚙️ Build & Run

### Requirements

* C++20 compiler (e.g. `g++ >= 11`)
* `log4cxx` installed (linked via `-llog4cxx`)

### Build

```bash
make
```

### Run

```bash
./bin/stream_server
```

### Output

* `logs/server.log`
* `logs/provider.log`
* `logs/provider_internal.log`

---

## 🧪 What This Demonstrates

* Thread-safe callback usage
* Stream simulation using static strings
* Clean log separation between modules
* Basic use of shared library interface (`libstreamprovider.so`)

---

## 📤 Integration Usage

From external modules, you can:

```c
#include "stream_provider.h"

void MyCallback(const char* data, int size) {
    printf("Received: %.*s\n", size, data);
}

int main() {
    register_stream_callback(MyCallback);
    start_stream();
    return 0;
}
```

---

## 📦 Future Extensions

* Support JSON-formatted stream data
* Dynamic configuration of stream source
* Export installable `.so` / `.dll` version
* Add CMake support for cross-platform use

---

## 🔖 License

This demo is provided for educational and integration reference purposes.
