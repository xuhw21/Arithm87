#include"arithmetic_coding.h"

void ArithmeticCoding::encodeSymbol(int symbol, int* cumFreq)
{
    long range = (long)(high - low) + 1;
    high = low + (range * cumFreq[symbol - 1]) / cumFreq[0] - 1;
    low = low + (range * cumFreq[symbol]) / cumFreq[0];

    while (true)
    {
        if (high < HALF)
            bitPlusFollow(0);
        else if (low >= HALF)
        {
            bitPlusFollow(1);
            low -= HALF;
            high -= HALF;
        }
        else if (low >= FIRST_QTR && high < THIRD_QTR)
        {
            bitsToFollow++;
            low -= FIRST_QTR;
            high -= FIRST_QTR;
        }
        else
            break;
        low <<= 1;
        high = (high << 1) + 1;
    }
}

int ArithmeticCoding::DecodeSymbol(int* cumFreq)
{
    CODEVALUE range = (high - low) + 1;
    int cum         = (((value - low) + 1) * cumFreq[0] - 1) / range;

    int symbol = 1;
    for (; cumFreq[symbol] > cum; symbol++);

    high = low + (range * cumFreq[symbol - 1]) / cumFreq[0] - 1;
    low  = low + (range * cumFreq[symbol]) / cumFreq[0];
    while (true)
    {
        if (high < HALF)
        {
        }
        else if (low >= HALF)
        {
            value -= HALF;
            low   -= HALF;
            high  -= HALF;
        }
        else if (low >= FIRST_QTR && high < THIRD_QTR)
        {
            value -= FIRST_QTR;
            low   -= FIRST_QTR;
            high  -= FIRST_QTR;
        }
        else
            break;
        low   = 2 * low;
        high  = 2 * high + 1;
        value = 2 * value + bs->InputBit();
    }
    return symbol;
}