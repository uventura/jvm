#include "lib/base/class_file/cp_info.h"

const char *get_info_name(u2 id)
{
    switch (id)
    {
    case CONSTANT_Class:
        return "Class";
        break;
    case CONSTANT_Fieldref:
        return "Fieldref";
        break;
    case CONSTANT_Methodref:
        return "Methodref";
        break;
    case CONSTANT_InterfaceMethodref:
        return "InterfaceMethodref";
        break;
    case CONSTANT_String:
        return "String";
        break;
    case CONSTANT_Integer:
        return "Integer";
        break;
    case CONSTANT_Float:
        return "Float";
        break;
    case CONSTANT_Long:
        return "Long";
        break;
    case CONSTANT_Double:
        return "Double";
        break;
    case CONSTANT_NameAndType:
        return "NameAndType";
        break;
    case CONSTANT_Utf8:
        return "Utf8";
        break;
    }

    return "None";
}
