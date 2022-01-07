#ifndef INPUT_H_
#define INPUT_H_

struct term_keycombo {
  char key;
  int ctrl;
  int meta;
  int super;
};

struct term_input_seq {
  int length;
  struct term_keycombo *keycombos;
};

// Read sequence from sequence queue and delete the entry it read
struct term_input_seq t_get_input();

#endif // INPUT_H_
