#include<adaptive_model.h>


void AdaptiveModel::startModel()
{
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
    {
        charToIndex[i]   = i+1;
        indexToChar[i+1] = i;
    }
    for (i = 0; i <= NO_OF_SYMBOLS; i++)
    {
        freq[i]    = 1;
        cumFreq[i] = NO_OF_SYMBOLS - i;
    }
    freq[0] = 0;
}

void AdaptiveModel::updateMode(int symbol)
{
    int i;
    if (cumFreq[0] == MAX_FREQUENCY)
    {
        int cum = 0;
        for (i = NO_OF_SYMBOLS; i >= 0; i--)
        {
            freq[i] = (freq[i] + 1)/2;
            cumFreq[i] = cum;
            cum += freq[i];
        }
    }

    for(i = symbol; freq[i] == freq[i-1]; i--);

    if (i < symbol)
    {
        int chi      = indexToChar[i];
        int chSymbol = indexToChar[symbol];
        indexToChar[i]        = chSymbol;
        indexToChar[symbol]   = chi;
        charToIndex[chi]      = symbol;
        charToIndex[chSymbol] = i;
    }

    freq[i]++;
    while (i > 0)
    {
        i--;
        cumFreq[i] += 1;
    }
}