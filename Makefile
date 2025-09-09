all: build_main build_file_management link

build_main:
	g++ -c ./src/main.cpp \
		-Iexternal/spdlog/include -Iexternal/nlohmann_json/include \
		-Iexternal/SDL3/include \
		-Iexternal/SDL3_Image/include \
		-o ./bin/main.o

build_file_management:
	g++ -c ./src/file_management.cpp \
		-Iexternal/spdlog/include -Iexternal/nlohmann_json/include \
		-o ./bin/file_management.o

link: ./bin/file_management.o ./bin/main.o
	g++ ./bin/file_management.o ./bin/main.o \
		-Lexternal/SDL3/lib \
		-Lexternal/SDL3_Image/lib \
		-lSDL3 -lSDL3_image -lwinmm -limm32 -lversion -lole32 -loleaut32 \
		-lsetupapi -lshell32 -luser32 -lgdi32 -luuid \
		-o ./bin/main

run:
	./bin/main.exe

clean:
	rm -rf ./bin/*.o
	rm -rf ./bin/*.exe