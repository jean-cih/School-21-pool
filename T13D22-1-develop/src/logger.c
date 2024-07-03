#include "logger.h"

#include <time.h>

#include "log_levels.h"

FILE* log_init(char* filename) { return fopen(filename, "a"); }

int logcat(FILE* log_file, char* message, log_level level) {
    time_t mytime = time(NULL);
    struct tm* now = localtime(&mytime);
    fprintf(log_file, "%d Date: %d.%d.%d ", level, now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
    fprintf(log_file, "Time: %d:%d:%d %s\n", now->tm_hour, now->tm_min, now->tm_sec, message);

    return 0;
}

int log_close(FILE* log_file) {
    fclose(log_file);

    return 0;
}