#include"bitsIO.h"
#include"arithmetic_coding.h"
#include"fixed_model.h"
#include<iostream>

int main(int argc, char** argv)
{
    FixedModel* pModel     = new FixedModel();
    BitsIO* pOutputBin     = new BitsIO();
    ArithmeticCoding* pEnc = new ArithmeticCoding(pOutputBin);

    pModel->startModel();
    pOutputBin->StartOutputBits();
    pEnc->startEncoding();

    while(true)
    {
        char ch;
        int symbol;
        ch = getchar();
        if (ch == 10) break;
        symbol = pModel->charToIndex[ch];
        pEnc->encodeSymbol(symbol, pModel->cumFreq);
        pModel->updateMode();
    }
    pEnc->encodeSymbol(EOF_SYMBOLS, pModel->cumFreq);
    pEnc->doneEncoding();
    pOutputBin->DoneOutPutBits();

    delete pOutputBin;
    delete pEnc;
    pOutputBin = new BitsIO();
    pEnc = new ArithmeticCoding(pOutputBin);
    pOutputBin->StartInputBits();
    pEnc->StartDecoding();
    while (true)
    {
        char ch;
        int symbol;
        symbol = pEnc->DecodeSymbol(pModel->cumFreq);
        if (symbol == EOF_SYMBOLS) break;
        ch = pModel->indexToChar[symbol];
        std::cout << ch;
        pModel->updateMode();
    }

    return 0;
}