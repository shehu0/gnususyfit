/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef ZFSIGMAHADRON_H
#define	ZFSIGMAHADRON_H

#include <ThObservable.h>
#include "ZFitter.h"


class ZFsigmaHadron : public ThObservable {
public:

    /**
     * @brief ZFsigmaHadron constructor
     * @param[in] ZF_i an object of ZFitter class
     */
    ZFsigmaHadron(const ZFitter& ZF_i) : ThObservable(ZF_i), myZF(ZF_i) {};

    /**
     * @return the hadronic cross section in nb
     */
    double getThValue();

    
private:
    const ZFitter& myZF;
};

#endif	/* ZFSIGMAHADRON_H */

