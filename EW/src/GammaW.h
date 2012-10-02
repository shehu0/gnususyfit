/* 
 * File:   GammaW.h
 * Author: mishima
 */

#ifndef GAMMAW_H
#define	GAMMAW_H

#include <ThObservable.h>
#include "EW.h"
#include "EW_CHMN.h"


class GammaW : public ThObservable {
public:
    
    /**
     * @brief GammaW constructor
     * @param[in] EW_i an object of EW class
     * @param[in] bCHMN_i true if using EW_CHMN class 
     */
    GammaW(const EW& EW_i, const bool bCHMN_i=false) : ThObservable(EW_i), 
            myEW(EW_i), myEW_CHMN(EW_i.getSM()), bCHMN(bCHMN_i) {};

    /**
     * @return the total width of the W boson 
     */
    double getThValue();

    
private:
    const EW& myEW;
    const EW_CHMN myEW_CHMN;
    const bool bCHMN;
};

#endif	/* GAMMAW_H */

