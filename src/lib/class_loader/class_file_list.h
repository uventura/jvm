#ifndef JVM_CLASSES_FILE_LIST
#define JVM_CLASSES_FILE_LIST

#define SUPER_CLASSES_MAX_DEPTH 100000

#include "lib/base/class_file/class_file.h"
#include "lib/base/defines.h"

typedef struct
{
    void *value;
    CONSTANT_Fieldref_info *field;
    void *next;
} FieldStatic;

typedef struct class_file_element
{
    char *class_name;
    ClassFile *class;
    struct class_file_element *next;
    FieldStatic *static_fields;
} ClassFileElement;

typedef struct
{
    ClassFileElement *head;
    u4 num_elements;
} ClassFileList;

ClassFileList class_file_list_init();
void class_file_list_free(ClassFileList *list);

void class_file_list_insert(ClassFileList *list, ClassFile *class, char *name);
ClassFile *class_file_list_get(ClassFileList *list, const char *name);

#endif
