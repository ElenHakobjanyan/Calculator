#ifndef INPUT_HPP
#define INPUT_HPP

// Sets up terminal for one-char-at-a-time reads
void cbreak();

// Returns terminal to normal state after cbreak ()
void normal();

// Checks keyboard buffer (stdin) and returns key pressed, or -1 for no key pressed
int keypress();

//waits untill the pressed button is escape
bool escape();

//puts coursor in the inputed coordinates
void gotoxy(int ,int );

#endif // INPUT_HPP