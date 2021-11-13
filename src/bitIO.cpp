#include"bitsIO.h"
#include"common_def.h"

void BitsIO::outputBit(int bit)
{
    buffer >>= 1;
    if (bit) buffer |= 0x80;
    bitsToGo--;
    if (bitsToGo == 0)
    {
        fwrite(&buffer, 1, 1, outputFile);
        bitsToGo = 8;
    }
}

int BitsIO::InputBit()
{
    int t = 0;
    if (inputFile == nullptr) exit(-1);
    if (bitsToGo == 0)
    {
        if (feof(inputFile))
        {
            garbageBits++;
            if (garbageBits > CODE_VALUE_BITS - 2)
            {
                std::cout << "Bad Input Files. \n";
                exit(-1);
            }
            return 0;
        }
        fread(&buffer, 1, 1, inputFile);
        bitsToGo = 8;
    }

    t = buffer & 1;
    buffer >>= 1;
    bitsToGo -= 1;
    return t;
}
