PROJ_NAME = FliwaBot
BUILD_DIR = build
DEBUG_BUILD_DIR = build_debug

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(DEBUG_BUILD_DIR)

cmake-generate:
	cmake -DCMAKE_BUILD_TYPE=Release -S . -B $(BUILD_DIR) -G Ninja

cmake-generate-debug:
	cmake -DCMAKE_BUILD_TYPE=Debug -S . -B $(DEBUG_BUILD_DIR) -G Ninja

cmake-build:
	cmake --build $(BUILD_DIR) -j $(nproc)

cmake-build-debug:
	cmake --build $(DEBUG_BUILD_DIR) -j $(nproc)
	
release:
	$(MAKE) cmake-generate
	$(MAKE) cmake-build

debug:
	$(MAKE) cmake-generate-debug
	$(MAKE) cmake-build-debug

run:
	$(MAKE) release
	$(BUILD_DIR)/$(PROJ_NAME)

run-debug:
	$(MAKE) debug
	$(DEBUG_BUILD_DIR)/$(PROJ_NAME)

setup-clangd:
	ln -s build/compile_commands.json .
