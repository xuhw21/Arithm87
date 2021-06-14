#pragma once

#ifndef BITS_IO__
#define BITS_IO__

#include<iostream>
#include<fstream>

class BitsIO {
public:
    BitsIO() 
    {
        fopen_s(&inputFile, "input.bin", "a+");
        fopen_s(&outputFile, "output.bin", "a+");
    };

    ~BitsIO()
    {
        if (inputFile)
            fclose(inputFile);
        if (outputFile)
            fclose(outputFile);
    }

    void StartInputBits()
    {
        inputFile = outputFile;
        bitsToGo    = 0;
        garbageBits = 0;
    }

    void StartOutputBits()
    {
        buffer   = 0;
        bitsToGo =8;
    }

    void outputBit(int bit);

    int InputBit();

    void DoneOutPutBits()
    {
        if(outputFile)
            fwrite(&(buffer>>=bitsToGo), 1, 1, outputFile);
    }

private:
    int buffer      = 0;
    int bitsToGo    = 0;
    int garbageBits = 0;

    FILE* inputFile  = nullptr;
    FILE* outputFile = nullptr;
};

#endif
