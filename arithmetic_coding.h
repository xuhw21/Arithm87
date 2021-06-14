#pragma once

#ifndef ARITHMETIC_CODING__
#define ARITHMETIC_CODING__

#include"common_def.h"
#include"bitsIO.h"

class ArithmeticCoding {
public:
    ArithmeticCoding(BitsIO* bs) : bs(bs)
    {}

    void startEncoding()
    {
        low = 0;
        high = TOP_VALUE;
        bitsToFollow = 0;
    }

    void StartDecoding()
    {
        value = 0;
        for (int i = 0; i < CODE_VALUE_BITS; i++)
        {
            value = 2 * value + bs->InputBit();
        }

        low  = 0;
        high = TOP_VALUE;
    }

    void encodeSymbol(int symbol, int* cumFreq);

    int DecodeSymbol(int* cumFrq);

    void bitPlusFollow(int bit)
    {
        bs->outputBit(bit);

        while (bitsToFollow > 0)
        {
            bs->outputBit(!bit);
            bitsToFollow--;
        }
    }

    void doneEncoding()
    {
        bitsToFollow++;

        if (low < FIRST_QTR) bitPlusFollow(0);
        else bitPlusFollow(1);
    }


private:
    BitsIO* bs = nullptr;

    CODEVALUE low   = 0;
    CODEVALUE high  = 0;
    CODEVALUE value = 0;
    long bitsToFollow = 0;
};

#endif // ARITHMETIC_CODING__