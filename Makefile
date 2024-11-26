.PHONY: native wasm clean-unix clean-win

native:
# cmake -S . -B build/native -DBUILD_WASM=OFF -DCMAKE_BUILD_TYPE=Debug
	cmake -S . -B build/native -DBUILD_WASM=OFF -DFETCHCONTENT_QUIET=FALSE
	cmake --build build/native

wasm:
	cmake -S . -B build/wasm -DBUILD_WASM=ON -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake -DFETCHCONTENT_QUIET=FALSE
	cmake --build build/wasm

clean-unix:
	rm -rf ./build

clean-win:
	rmdir /s /q build