#include <stdio.h>

#include "lib/base/file/read_bytes.h"

int main()
{
    FILE* file;
    file = fopen("test/data/examples/HelloWorld.class", "rb");

    if(!file)
    {
        printf("Couldn't open file...\n");
    }

    u4 cafe_babe = u4_read(file);
    if(cafe_babe == 0xCAFEBABE)
    {
        printf("Is Cafe Baby!!\n");
    }

    fclose(file);
}
