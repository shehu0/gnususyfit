/* 
 * Copyright (C) 2012 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef SIN2THETAEFF_H
#define	SIN2THETAEFF_H

#include <stdexcept>
#include <ThObservable.h>
#include "EW.h"

/**
 * @class sin2thetaEff 
 * @ingroup EW 
 * @brief A class for the effective weak mixing angle @f$\sin^2\theta_{\rm eff}^{\rm lept}@f$ 
 * for a leptonic channel at the @f$Z@f$ pole.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the effective weak mixing angle 
 * @f$\sin^2\theta_{\rm eff}^{\rm lept}@f$ for a leptonic channel at the @f$Z@f$ pole.
 */
class sin2thetaEff : public ThObservable {
public:

    /**
     * A constructor.
     * @param[in] EW_i A reference to an object of EW class, which is the base 
     * class of the electroweak precision observables.
     */
    sin2thetaEff(const EW& EW_i) 
    : ThObservable(EW_i), myEW(EW_i), myEWTYPE(EW_i.getEWTYPE()) 
    {
    };

    /**
     * @return The effective weak mixing angle @f$\sin^2\theta_{\rm eff}^{\rm lept}@f$ 
     * for a leptonic channel at the @f$Z@f$ pole.
     */
    double getThValue();

    
private:

    /**
     * A reference to an object of EW class, which is the base class of the 
     * electroweak precision observables.
     */
    const EW& myEW;

    /**
     * An enumerator controlling the formulae used in the computation.
     */
    const EW::EWTYPE myEWTYPE;
};

#endif	/* SIN2THETAEFF_H */

