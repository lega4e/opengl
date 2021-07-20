cflags  := -std=gnu++17 -c -Wall
ldflags :=
libs    := -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl





# main
build: main

run: main
	main


re: clean build

rerun: clean run


source_dirs     := src src/lib/nvx/opengl/code
header_dirs     := src/lib src ../shared
search_wildcard := $(wildcard $(addsuffix /*.cpp,$(source_dirs)))
object_files    := $(patsubst %.cpp,%.o,$(search_wildcard))
object_files    := $(notdir $(object_files))
object_files    := $(addprefix target/,$(object_files))
VPATH           := $(source_dirs)

main: ./target $(object_files) target/glad.o target/stb_image.o
	g++ $(ldflags) -o $@ $(object_files) target/glad.o target/stb_image.o $(libs)

./target:
	mkdir -p target

target/%.o: %.cpp
	g++ $(cflags) -o $@ -MD $(addprefix -I,$(header_dirs)) $<

target/glad.o: ../shared/glad.c
	g++ $(cflags) -o $@ $<

target/stb_image.o: ../shared/stb_image.c
	g++ $(cflags) -o $@ $< -I ../shared

include $(wildcard target/*.d)



# clean
clean:
	-rm -r target main





# end
