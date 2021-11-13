#pragma once

#include "model.h"

#ifndef __FIXED_MODEL__
#define __FIXED_MODEL__

class FixedModel :public Model{
public:
    void startModel() override;
    void updateMode(int symbol) override;

};
#endif //FIXED_MODEL__