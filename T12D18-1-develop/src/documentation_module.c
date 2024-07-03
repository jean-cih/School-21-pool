#include "documentation_module.h"

#include <stdarg.h>
#include <stdlib.h>

int validate(char *data) {
    int validation_result = !s21_strcmp(data, Available_document);
    return validation_result;
}

int *check_available_documentation_module(int (*validate)(char *), int document_count, ...) {
    if (document_count > 15) return 0;

    va_list ap;
    va_start(ap, document_count);
    for (int i = 0; i < document_count; i++) {
        char *doc = va_arg(ap, char *);
        if (validate(doc)) {
            printf("%d. %-15s : available\n", i + 1, doc);
        } else
            printf("%d. %-15s : unavailable\n", i + 1, doc);
    }
    va_end(ap);

    return 0;
}

int s21_strcmp(const char *string1, const char *string2) {
    while (*string1 == *string2 && *string1 != '\0') {
        string1++;
        string2++;
    }

    if (*string1 == '\0' && *string2 == '\0') return 0;

    if (*string1 > *string2)
        return 1;
    else
        return -1;
}