/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef AFBCHARM_H
#define	AFBCHARM_H

#include <stdexcept>
#include <ThObservable.h>
#include "EW.h"

/**
 * @class AFBcharm
 * @ingroup EW 
 * @brief A class for the forward-backward asymmetry of @f$Z\to c\bar{c}@f$ 
 * at the @f$Z@f$ pole.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the forward-backward asymmetry of 
 * the @f$Z\to c\bar{c}@f$ channel  at the @f$Z@f$ pole in terms of the asymmetry
 * parameters @f$A_f\f$, computed in the \b EW class:
 * \f[A_{FB}^{0,c}=\frac 34 A_e A_c.\f]  
 */
class AFBcharm : public ThObservable {
public:

    /**
     * @brief Constructor.
     * @param[in] EW_i A reference to an object of EW class, which is the base class of 
     * the electroweak precision observables.
     */
    AFBcharm(const EW& EW_i) 
    : ThObservable(EW_i), myEW(EW_i) 
    {
    };
    
    /**
     * @brief The theory prediction for \f$A^{0,c}_{FB}\f$ at the \f$Z\f$ pole.
     * @return the forward-backward asymmetry in @f$e^+ e^-\to Z\to c\bar{c}@f$ at the 
     * @f$Z@f$ pole
     */
    double computeThValue();

    
private:

    /**
     * A reference to an object of EW class, which is the base class of the electroweak 
     * precision observables.
     */
    const EW& myEW;///< A reference to an object of the EW class.
};

#endif	/* AFBCHARM_H */

