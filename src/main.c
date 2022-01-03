#include "util/logger.h"

int main(int argc, char **argv) {
  // Setup the logger
  log_setfile("/tmp/edenv.log.txt", false);
  log_open();
  log_msg("Started application!");

  // Parse low-level arguments

  // Setup event loop

  // Read config files

  // Run event loop
}
