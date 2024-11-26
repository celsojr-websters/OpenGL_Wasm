.PHONY: native wasm clean-unix clean-win

# cmake -S . -B build/native -DBUILD_WASM=OFF -DCMAKE_BUILD_TYPE=Debug
native:
	cmake -S . -B build/native -DBUILD_WASM=OFF
	cmake --build build/native

wasm:
	cmake -S . -B build/wasm -DBUILD_WASM=ON -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake
	cmake --build build/wasm

clean-unix:
	rm -rf ./build

clean-win:
	rmdir /s /q build