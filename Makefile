#all:
#	g++ main.cpp -static -static-libgcc -static-libstdc++   -Isrc/include -Lsrc/bin -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o main

FILE = main.cpp
FILE_NAME = main

INCLUDE_PATHS = -Isrc/include

LIBRARY_PATHS = -Lsrc/lib 

COMPILER_FLAGS = -static -static-libgcc -static-libstdc++

SDLLIBS = -mwindows  -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -lRpcrt4

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

all : $(FILE)
	g++ $(FILE) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(SDLLIBS)  -o $(FILE_NAME)