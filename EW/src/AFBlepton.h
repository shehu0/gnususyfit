/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef AFBLEPTON_H
#define	AFBLEPTON_H

#include <stdexcept>
#include <ThObservable.h>
#include "EW.h"

/**
 * @class AFBlepton
 * @ingroup EW 
 * @brief A class for the forward-backward asymmetry of @f$Z\to \ell\bar{\ell}@f$ 
 * at the @f$Z@f$ pole.
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the forward-backward asymmetry of 
 * a @f$Z\to \ell\bar{\ell}@f$ channel at the @f$Z@f$ pole in terms of the asymmetry
 * parameters @f$A_f\f$, computed in the \b EW class:
 * \f[A_{FB}^{0,\ell}=\frac 34 A_e A_\ell\f].  
 */
class AFBlepton : public ThObservable {
public:
 
    /**
     * @brief Constructor.
     * @param[in] EW_i A reference to an object of EW class, which is the base class of 
     * the electroweak precision observables.
     */
    AFBlepton(const EW& EW_i) 
    : ThObservable(EW_i), myEW(EW_i)
    {
    };

    /**
     * @brief The theory prediction for \f$A^{0,\ell}_{FB}\f$ at the \f$Z\f$ pole.
     * @return the forward-backward asymmetry in @f$e^+ e^-\to Z\to \ell^+\ell^-@f$ 
     * at the @f$Z@f$ pole, where @f$\ell@f$ denotes a charged lepton
     */
    double computeThValue();

    
private:

    /**
     * A reference to an object of EW class, which is the base class of the electroweak 
     * precision observables.
     */
    const EW& myEW;///< A reference to an object of the EW class.
};

#endif	/* AFBLEPTON_H */

