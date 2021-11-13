#include"bitsIO.h"
#include"arithmetic_coding.h"
#include"fixed_model.h"
#include"adaptive_model.h"
#include<iostream>

int main(int argc, char** argv)
{

    ArithmeticCoding* pEnc = new ArithmeticCoding();

    pEnc->startEncoding();

    while(true)
    {
        char ch;
        ch = getchar();
        if (ch == 10) break;
        pEnc->encodeSymbol(ch);
    }
    pEnc->encodeSymbol(EOF_SYMBOLS);
    pEnc->doneEncoding();
    delete pEnc;

    ArithmeticCoding* pDec = new ArithmeticCoding();
    pDec->StartDecoding();
    while (true)
    {
        int symbol;
        symbol = pDec->DecodeSymbol();
        if (symbol == EOF_SYMBOLS) break;
    }
    delete pDec;

    return 0;
}