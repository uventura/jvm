#include <stdio.h>

#include "lib/class_loader/bootstrap/bootstrap.h"

int main()
{
    ClassFile class_file = load_class_file("data/examples/HelloWorld.class");
    printf("%d %d\n", class_file.minor_version, class_file.major_version);
    printf("%d\n", class_file.constant_pool_count);
}
