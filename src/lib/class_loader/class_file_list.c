#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/base/defines.h"
#include "lib/class_loader/bootstrap/bootstrap.h"
#include "lib/class_loader/class_file_list.h"

ClassFileList class_file_list_init()
{
    ClassFileList class_file_list;
    class_file_list.num_elements = 0;
    class_file_list.head = NULL;
    return class_file_list;
}

void class_file_list_free(ClassFileList *list)
{
    ClassFileElement *current_cfe;
    for (u4 index = 0; index < list->num_elements; ++index)
    {
        current_cfe = (list->head)->next;

        ClassFile *element = list->head->class;
        free_class_file(*element);
        free(element);

        free(list->head);
        list->head = current_cfe;
    }
}

void class_file_list_insert(ClassFileList *list, ClassFile *class, char *name)
{
    if (class_file_list_get(list, name) != NULL)
    {
        return;
    }

    list->num_elements += 1;

    ClassFileElement *new_element = (ClassFileElement *)malloc(sizeof(ClassFileElement));
    new_element->class = class;
    new_element->class_name = name;
    new_element->next = NULL;

    if (list->head == NULL)
    {
        list->head = new_element;
        return;
    }

    ClassFileElement *element = list->head;
    while (element->next != NULL)
    {
        element = element->next;
    }
    element->next = new_element;
}

ClassFile *class_file_list_get(ClassFileList *list, const char *name)
{
    ClassFileElement *current_element = list->head;
    for (u4 index = 0; index < list->num_elements; ++index)
    {
        if (strcmp(current_element->class_name, name) == 0)
        {
            return current_element->class;
        }
    }

    return NULL;
}
