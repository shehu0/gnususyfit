/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "ThObservable.h"

ThObservable::ThObservable(const ThObsType& ObsType_i) : ObsType(ObsType_i), 
        SM(ObsType_i.getModel()) {
}

ThObservable::ThObservable(const ThObservable& orig) : ObsType(orig.ObsType),
        SM(orig.SM) {
}

ThObservable::~ThObservable() {
}

double const ThObservable::GeVminus2_to_nb = 389379.338;