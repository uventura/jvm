@echo off

if not exist obj mkdir obj

gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\main.o -c src\main.c -Isrc

if not exist obj\lib\controller mkdir obj\lib\controller
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\controller\jvm_reader.o -c src\lib\controller\jvm_reader.c -Isrc

if not exist obj\lib\controller mkdir obj\lib\controller
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\controller\jvm_controller.o -c src\lib\controller\jvm_controller.c -Isrc

if not exist obj\lib\controller mkdir obj\lib\controller
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\controller\jvm_runner.o -c src\lib\controller\jvm_runner.c -Isrc

if not exist obj\lib\base\file mkdir obj\lib\base\file
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\base\file\read_bytes.o -c src\lib\base\file\read_bytes.c -Isrc

if not exist obj\lib\base\structures mkdir obj\lib\base\structures
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\base\structures\stack.o -c src\lib\base\structures\stack.c -Isrc

if not exist obj\lib\base\math mkdir obj\lib\base\math
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\base\math\iee754.o -c src\lib\base\math\iee754.c -Isrc

if not exist obj\lib\base\class_file mkdir obj\lib\base\class_file
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\base\class_file\class_defines.o -c src\lib\base\class_file\class_defines.c -Isrc

if not exist obj\lib\base\class_file mkdir obj\lib\base\class_file
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\base\class_file\cp_info.o -c src\lib\base\class_file\cp_info.c -Isrc

if not exist obj\lib\interpreter mkdir obj\lib\interpreter
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\interpreter\byte_code.o -c src\lib\interpreter\byte_code.c -Isrc

if not exist obj\lib\interpreter mkdir obj\lib\interpreter
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\interpreter\opcodes_generic.o -c src\lib\interpreter\opcodes_generic.c -Isrc

if not exist obj\lib\class_loader mkdir obj\lib\class_loader
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\class_loader\class_file_list.o -c src\lib\class_loader\class_file_list.c -Isrc

if not exist obj\lib\class_loader\bootstrap mkdir obj\lib\class_loader\bootstrap
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\class_loader\bootstrap\bootstrap.o -c src\lib\class_loader\bootstrap\bootstrap.c -Isrc

if not exist obj\lib\class_loader mkdir obj\lib\class_loader
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\class_loader\class_loader.o -c src\lib\class_loader\class_loader.c -Isrc

if not exist obj\lib\runtime_data_area mkdir obj\lib\runtime_data_area
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\runtime_data_area\method_area.o -c src\lib\runtime_data_area\method_area.c -Isrc

if not exist obj\lib\runtime_data_area mkdir obj\lib\runtime_data_area
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\runtime_data_area\object.o -c src\lib\runtime_data_area\object.c -Isrc

if not exist obj\lib\runtime_data_area mkdir obj\lib\runtime_data_area
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\runtime_data_area\frame.o -c src\lib\runtime_data_area\frame.c -Isrc

if not exist obj\lib\environment mkdir obj\lib\environment
gcc -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -o obj\lib\environment\jvm_debug_functions.o -c src\lib\environment\jvm_debug_functions.c -Isrc

if not exist bin mkdir bin
gcc -o bin\jvm obj\main.o obj\lib\controller\jvm_reader.o obj\lib\controller\jvm_controller.o obj\lib\controller\jvm_runner.o obj\lib\base\file\read_bytes.o obj\lib\base\structures\stack.o obj\lib\base\math\iee754.o obj\lib\base\class_file\class_defines.o obj\lib\base\class_file\cp_info.o obj\lib\interpreter\byte_code.o obj\lib\interpreter\opcodes_generic.o obj\lib\class_loader\class_file_list.o obj\lib\class_loader\bootstrap\bootstrap.o obj\lib\class_loader\class_loader.o obj\lib\runtime_data_area\method_area.o obj\lib\runtime_data_area\object.o obj\lib\runtime_data_area\frame.o obj\lib\environment\jvm_debug_functions.o -W -Wall -ansi -pedantic -std=c99 -g -O3 -Wno-unused-parameter -Wno-implicit-fallthrough -O3 -Isrc
