/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef GAMMAW_H
#define	GAMMAW_H

#include <stdexcept>
#include <ThObservable.h>
#include "EW.h"

/**
 * @class GammaW 
 * @ingroup EW 
 * @brief A class for the total decay width of the \f$W\f$ boson 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This class is used to compute the total decay width of the \f$W\f$ boson
 * (in GeV), \f$\Gamma_W\f$. 
 */
class GammaW : public ThObservable {
public:
    
    /**
     * @brief Constructor.
     * @param[in] EW_i A reference to an object of EW class, which is the base class of 
     * the electroweak precision observables.
     */
    GammaW(const EW& EW_i) 
    : ThObservable(EW_i)
    {
    };

    /**
     * @brief The theory prediction for \f$\Gamma_W\f$.
     * @return the total width of the \f$W\f$ boson in GeV 
     */
    double computeThValue();

};

#endif	/* GAMMAW_H */

