//
//  normalizeAdjustBrightnessAndContrastPreprocess.h
//  Seight
//
//  Created by Elisha Jeremy Gonzales on 3/30/15.
//  Copyright (c) 2015 Butil. All rights reserved.
//

#ifndef __Seight__normalizeAdjustBrightnessAndContrastPreprocess__
#define __Seight__normalizeAdjustBrightnessAndContrastPreprocess__

#include <stdio.h>
#include "IPreprocess.h"

class normalizeAdjustBrightnessAndContrastPreprocess : public IPreprocess
{
public:
    normalizeAdjustBrightnessAndContrastPreprocess();
    ~normalizeAdjustBrightnessAndContrastPreprocess();
    Mat perform(Mat image);
};

#endif /* defined(__Seight__normalizeAdjustBrightnessAndContrastPreprocess__) */
