#include "lib/base/class_file/class_defines.h"

const char *get_access_flag_name(int id)
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
