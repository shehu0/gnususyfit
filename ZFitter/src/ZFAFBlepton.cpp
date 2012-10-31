/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "ZFAFBlepton.h"


double ZFAFBlepton::getThValue() {
    return ( 3.0/4.0*myZF.Af(1)*myZF.Af(1) );
}

