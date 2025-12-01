COMPILER = clang++
SOURCE_LIBS =
INCLUDE_DIRS = -Ilib
CXXFLAGSDEBUG = -std=c++23 -g -D _DEBUG $(INCLUDE_DIRS)
CXXFLAGSBUILD = -std=c++23 -D _DEBUG $(INCLUDE_DIRS)
OSX_OPT = -Llib/ -framework CoreVideo -framework CoreFoundation -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a
OSX_OUT = -o "bin/build_osx"
CFILES = src/*.cpp
WASM_COMPILER = emcc
WASM_OUT = -o "wasm_build/index.html"

debug_osx:
	$(COMPILER) $(CXXFLAGSDEBUG) $(CFILES) $(SOURCE_LIBS) $(OSX_OUT) $(OSX_OPT)

build_osx:
	$(COMPILER) $(CXXFLAGSBUILD) $(CFILES) $(SOURCE_LIBS) $(OSX_OUT) $(OSX_OPT)