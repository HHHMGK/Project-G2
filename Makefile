all:
	g++ main.cpp -Isrc/include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main

# FILE = main.cpp
# FILE_NAME = main

# INCLUDE_PATHS = -Isrc/include

# LIBRARY_PATHS = -Lsrc/lib 

# COMPILER_FLAGS = -static -static-libgcc -static-libstdc++ 

# LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# SDLLIBS = -mwindows  -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -lRpcrt4

# all : $(FILE)
# 	g++ $(FILE) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(echo sdl2-config --static-libs) $(LINKER_FLAGS) $(SDLLIBS)  -o $(FILE_NAME)
