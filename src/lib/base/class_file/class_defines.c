#include "lib/base/class_file/class_defines.h"

// Function to get an access flag's name based on its ID.
const char *get_access_flag_name(u2 id)
{
    switch (id)
    {
    case ACC_PUBLIC:
        return "public";
    case ACC_PRIVATE:
        return "private";
    case ACC_PROTECTED:
        return "protected";
    case ACC_STATIC:
        return "static";
    case ACC_FINAL:
        return "final";
    case ACC_VOLATILE:
        return "volatile";
    case ACC_TRANSIENT:
        return "transient";
    case ACC_SYNTHETIC:
        return "synthetic";
    case ACC_ENUM:
        return "enum";
    }

    return "";
}

// Function to get the type of a constant based on its ID.
const char *get_cp_info_name(u2 id)
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
