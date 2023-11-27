#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "lib/base/class_file/class_file.h"
#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/controller/jvm_controller.h"
#include "lib/controller/jvm_reader.h"
#include "lib/controller/jvm_runner.h"

// Function that parses the command line arguments.
// The program requires the user to pass two arguments:
//     - the execution mode ("-read" or "-run");
//     - the qualified name for the ".class" file.
int jvm_run(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("[JVM - ERROR] Missing Arguments\n");
        return -1;
    }

    if (!strcmp(argv[1], "-read"))
    {
        jvm_read_class(argv[2]);
    }
    else if (!strcmp(argv[1], "-run"))
    {
        jvm_run_class(argv[2]);
    }
    else
    {
        printf("[JVM - ERROR] Wrong Option");
        return -1;
    }

    return 0;
}

// Function that reads the bytecode of the ".class" file passed as an argument.
// The bytecode information is stored in a "class_file" struct, which is then printed on the standard output stream.
void jvm_read_class(char *class_file_path)
{
    ClassFile class_file = load_class_file(class_file_path);

    jvm_display_general_information(class_file);
    jvm_display_constant_pool(class_file.constant_pool, class_file.constant_pool_count);
    jvm_display_interfaces(class_file.interfaces_count, class_file.interfaces, class_file.constant_pool);
    jvm_display_fields(class_file.fields_count, class_file.fields, class_file.constant_pool);
    jvm_display_methods(class_file.methods_count, class_file.methods, class_file.constant_pool);
    jvm_display_attributes(class_file.attributes_count, class_file.attributes, class_file.constant_pool, 0);

    free_class_file(class_file);
}

void jvm_run_class(char *class_file_path)
{
    ClassFile *class_file = (ClassFile *)malloc(sizeof(ClassFile));
    *class_file = load_class_file(class_file_path);
    jvm_runner(class_file, class_file_path);
}
