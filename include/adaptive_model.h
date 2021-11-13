#pragma once

#include"model.h"

#ifndef __ADAPTIVE_MODEL__
#define __ADAPTIVE_MODEL__

class AdaptiveModel :public Model {
public:
    void startModel() override;
    void updateMode(int symbol) override;
};
#endif // ADAPTIVE_MODEL__