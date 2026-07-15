A spreadsheet engine written in C++ that can be run headless in the terminal or can be run in the web using WASM.

Eventually the aim is to create a web interface that uses this code to handle all of the functional spreadsheet pieces, and can only worry about rendering it correctly.

-----

This can be built as normal using CMake, then building the output folder that's generated.

Alternatively, it can be built using Emscripten to be run in the web as WASM.
```
emcmake cmake ..
cmake --build .
emrun test.html
```
