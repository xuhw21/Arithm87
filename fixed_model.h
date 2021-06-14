#pragma once

#ifndef FIXED_MODEL__
#define FIXED_MODEL__

#define NO_OF_CHARS 256                 // Number of character symbols.
#define EOF_SYMBOLS  (NO_OF_CHARS + 1)  // Index of EOF symbol

#define NO_OF_SYMBOLS (NO_OF_CHARS + 1) // Total number of symbols

/* Cumulative frequency table. */
#define MAX_FREQUENCY 16383     // Maximum allowed frequency count: (1 << 14) - 1.


class FixedModel {
public:
    void startModel();
    void updateMode();

    int cumFreq[NO_OF_SYMBOLS + 1]; // Cumulative symbol frequencies.
    /* Translation tables between characters and symbol indexes. */
    int charToIndex[NO_OF_CHARS];             // To index from character.
    unsigned char indexToChar[NO_OF_SYMBOLS]; // To character frome index.

};
#endif //FIXED_MODEL__