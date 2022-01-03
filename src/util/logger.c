#include "util/logger.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *log_file_path = NULL;
static bool log_file_append = false;
static FILE *log_file_ostream;

int log_setfile(const char *file_path, bool append) {
  log_file_path = malloc(sizeof(char) * strlen(file_path));
  strcpy(log_file_path, file_path);
  log_file_append = append;

  return 0;
}

int log_open() {
  if (log_file_path == NULL) {
    return 1;
  }

  if (log_file_append)
    log_file_ostream = fopen(log_file_path, "w");
  else
    log_file_ostream = fopen(log_file_path, "a");

  return 0;
}

int log_close() {
  fclose(log_file_ostream);
  return 0;
}

void log_exit() { free(log_file_path); }

void log_msg(const char *message) {
  fprintf(log_file_ostream, "%s/n", message);
}

void log_error(const char *message) {
  fprintf(log_file_ostream, "%s\n", message);
}

void log_warning(const char *message) {
  fprintf(log_file_ostream, "%s\n", message);
}
