#include "terminal/misc.h"
#include <stdio.h>

#ifdef __LINUX__
#include <termios.h>
#include <unistd.h>

static struct termios t_orig;

void term_init() {
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t_orig = t;

  // Set flags
  t.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  t.c_oflag &= ~(OPOST);
  t.c_cflag |= (CS8);
  t.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); //"Local Flags"
  t.c_cc[VMIN] = 0;
  t.c_cc[VTIME] = 1;

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
}

void term_exit() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &t_orig); }

void term_ring_bell() { write(stdout, "\a", 1); }
#endif
