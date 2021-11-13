#pragma once

#ifndef ARITHMETIC_CODING__
#define ARITHMETIC_CODING__

#include"common_def.h"
#include"bitsIO.h"

#define USE_ADAPTIVE_MODEL 0

#ifdef USE_ADAPTIVE_MODEL
#include "adaptive_model.h"
#else
#include "fixed_model.h"
#endif

class ArithmeticCoding {
public:
    ArithmeticCoding()
    {
#ifdef USE_ADAPTIVE_MODEL
        m_pModel = new AdaptiveModel();
#else
        m_pModel = new FixedModel();
#endif
        m_BitsIO = new BitsIO();
    }

    ~ArithmeticCoding()
    {
        if(m_pModel)
            delete m_pModel;
        if(m_BitsIO)
            delete m_BitsIO;
    }

    void startEncoding()
    {
        m_pModel->startModel();
        m_BitsIO->StartOutputBits();

        low = 0;
        high = TOP_VALUE;
        bitsToFollow = 0;
    }

    void StartDecoding()
    {
        m_pModel->startModel();
        m_BitsIO->StartInputBits();

        value = 0;
        for (int i = 0; i < CODE_VALUE_BITS; i++)
        {
            value = 2 * value + m_BitsIO->InputBit();
        }

        low  = 0;
        high = TOP_VALUE;
    }

    void encodeSymbol(int input);

    int DecodeSymbol();

    void bitPlusFollow(int bit)
    {
        m_BitsIO->outputBit(bit);

        while (bitsToFollow > 0)
        {
            m_BitsIO->outputBit(!bit);
            bitsToFollow--;
        }
    }

    void doneEncoding()
    {
        bitsToFollow++;

        if (low < FIRST_QTR) bitPlusFollow(0);
        else bitPlusFollow(1);
        
        m_BitsIO->DoneOutPutBits();
    }


private:

    CODEVALUE low   = 0;
    CODEVALUE high  = 0;
    CODEVALUE value = 0;
    long bitsToFollow = 0;

    Model* m_pModel  = nullptr;
    BitsIO* m_BitsIO = nullptr;
};

#endif // ARITHMETIC_CODING__