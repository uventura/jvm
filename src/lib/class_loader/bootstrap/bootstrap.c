#include "lib/base/class_file/class_file.h"
#include "lib/base/file/read_bytes.h"
#include "lib/class_loader/bootstrap/bootstrap.h"

#include <stdio.h>
#include <stdlib.h>

ClassFile load_class_file(const char *filepath)
{
    FILE *class_file_element = fopen(filepath, "rb");

    if (!class_file_element)
    {
        printf("[Class Loader - Bootstrap](ERROR) Couldn't open file...\n");
        exit(-1);
    }

    u4 cafe_babe = u4_read(class_file_element);
    if (cafe_babe != 0xCAFEBABE)
    {
        printf("[Class Loader - Bootstrap](ERROR) This is not a .class file...\n");
        exit(-1);
    }

    ClassFile class_file;
    class_file.magic = cafe_babe;
    class_file.minor_version = u2_read(class_file_element);
    class_file.major_version = u2_read(class_file_element);
    class_file.constant_pool_count = u2_read(class_file_element);

    fclose(class_file_element);

    return class_file;
}
