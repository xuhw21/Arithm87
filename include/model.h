#pragma once

#ifndef __MODEL__
#define __MODEL__

#define NO_OF_CHARS 256                 // Number of character symbols.
#define EOF_OF_CHARS 255                 // EOF of character symbols.
#define EOF_SYMBOLS  NO_OF_CHARS  // Index of EOF symbol

#define NO_OF_SYMBOLS (NO_OF_CHARS + 1) // Total number of symbols

/* Cumulative frequency table. */
#define MAX_FREQUENCY 16383     // Maximum allowed frequency count: (1 << 14) - 1.

class Model {
public:
    virtual ~Model() {};
    virtual void startModel() = 0;
    virtual void updateMode(int symbol) = 0;

    int freq[NO_OF_SYMBOLS + 1];
    int cumFreq[NO_OF_SYMBOLS + 1]; // Cumulative symbol frequencies.
    /* Translation tables between characters and symbol indexes. */
    int charToIndex[NO_OF_CHARS];             // To index from character.
    unsigned char indexToChar[NO_OF_SYMBOLS]; // To character frome index.
};
#endif // __MODEL__