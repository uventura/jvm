mkdir -p obj/
gcc -W -Wall -ansi -pedantic -std=c99 -o obj/main.o -c src/main.c -Isrc
mkdir -p obj/lib/controller/
gcc -W -Wall -ansi -pedantic -std=c99 -o obj/lib/controller/controller.o -c src/lib/controller/controller.c -Isrc
mkdir -p obj/lib/base/file/
gcc -W -Wall -ansi -pedantic -std=c99 -o obj/lib/base/file/read_bytes.o -c src/lib/base/file/read_bytes.c -Isrc
mkdir -p obj/lib/base/class_file/
gcc -W -Wall -ansi -pedantic -std=c99 -o obj/lib/base/class_file/class_defines.o -c src/lib/base/class_file/class_defines.c -Isrc
mkdir -p obj/lib/base/class_file/
gcc -W -Wall -ansi -pedantic -std=c99 -o obj/lib/base/class_file/cp_info.o -c src/lib/base/class_file/cp_info.c -Isrc
mkdir -p obj/lib/class_loader/bootstrap/
gcc -W -Wall -ansi -pedantic -std=c99 -o obj/lib/class_loader/bootstrap/bootstrap.o -c src/lib/class_loader/bootstrap/bootstrap.c -Isrc
mkdir -p bin
gcc -o bin/jvm obj/main.o obj/lib/controller/controller.o obj/lib/base/file/read_bytes.o obj/lib/base/class_file/class_defines.o obj/lib/base/class_file/cp_info.o obj/lib/class_loader/bootstrap/bootstrap.o -W -Wall -ansi -pedantic -std=c99 -O3 -Isrc
