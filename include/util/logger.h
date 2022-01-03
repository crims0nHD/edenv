#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdbool.h>

int log_setfile(const char *file_path, bool append);
void log_exit();

int log_open();
int log_close();

void log_msg(const char *message);
void log_error(const char *error);
void log_warning(const char *warning);

#endif // LOGGER_H_
