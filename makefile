# default target
.PHONY: clean build 

# folder build stuff goes into
BUILD_DIR := build

# the html page that emscripten compiles to 
EMCC_HTML_FILE := shell_minimal.html

# emscripten output
TARGET := $(BUILD_DIR)/index.html

# c++ source code
SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard src/*.h)

# emcc flags
# -O3 => highest optimization level
# --shell-file => the html page emscripten compiles to
# -s => compile for webgl2 
#  -m => tells emscripten to use SIMD128
FLAGS := -O3 --shell-file ${EMCC_HTML_FILE} -sMAX_WEBGL_VERSION=2 -msimd128 -I./lib/glm

# ---------------------------------------------------------------

# compiles c++ code
build:
	mkdir -p ${BUILD_DIR}
	emcc $(SOURCES) -o $(TARGET) ${FLAGS}

# delete build folder and files
clean:
	rm -rf $(BUILD_DIR)
	@echo build directory '${BUILD_DIR}' removed!

# kills any currently running instances of python3 -m http.server
server-kill:
	@pids=$$(ps aux | grep -E -i "[p]ython(3)? -m http.server" | awk '{print $$2}'); \
	if [ -n "$$pids" ]; then \
		echo "killing server with pid: $$pids"; \
		kill -9 $$pids; \
	else \
		echo "no server running"; \
	fi

# stops all servers and starts a new one
server-start:
	${MAKE} server-kill
	@echo "starting server in backgroud ..."
	python3 -m http.server > /dev/null 2>&1 &