#include <stdio.h>

#include "documentation_module.h"
#include "print_module.h"

int main() {
#ifdef Quest_1
    print_log(print_char, Module_load_success_message);
#endif

#ifdef Quest_2
    check_available_documentation_module(validate, Documents_count, Documents);
#endif

    // Output availability for each document....

    return 0;
}