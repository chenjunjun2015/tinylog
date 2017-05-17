#ifndef LOG_HELPER_HH
#define LOG_HELPER_HH

#include <time.h>
#include <stdbool.h>
#include "logstr.h"

time_t
timestamp();

ls_t
strtimenow(const char* fmt);

ls_t
strnow();

#endif//LOG_HELPER_HH
