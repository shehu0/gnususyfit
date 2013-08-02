/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef ZFACHARM_H
#define	ZFACHARM_H

#include <ThObservable.h>
#include "ZFitterWrapper.h"


class ZFAcharm : public ThObservable {
public:

    /**
     * @brief ZFAcharm constructor
     * @param[in] ZF_i an object of ZFitter class
     */
    ZFAcharm(const ZFitterWrapper& ZF_i) : ThObservable(ZF_i), myZF(ZF_i) {};

    /**
     * @return the left-right asymmetry of the c-cbar channel
     */
    double getThValue();

    
private:
    const ZFitterWrapper& myZF;
};

#endif	/* ZFACHARM_H */
