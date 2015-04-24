/*
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "SJPsiK.h"

double SJPsiK::computeThValue() 
{
    return sin(-AmpBd(FULLNLO).arg());
}
