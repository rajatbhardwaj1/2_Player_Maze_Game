all:
	g++ -o game main.cpp  `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer 

.PHONY: clean
clean::
	$(RM) game