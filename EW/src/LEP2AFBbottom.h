/* 
 * File:   LEP2AFBbottom.h
 * Author: mishima
 */

#ifndef LEP2AFBBOTTOM_H
#define	LEP2AFBBOTTOM_H

#include "LEP2ThObservable.h"


class LEP2AFBbottom : public LEP2ThObservable {
public:

    /**
     * @brief LEP2AFBbottom constructor
     * @param[in] EW_i an object of EW class
     * @param[in] sqrt_s_i the CM energy of the e^+ e^- pair
     */
    LEP2AFBbottom(const EW& EW_i, const double sqrt_s_i) : LEP2ThObservable(EW_i, sqrt_s_i) {
        q_flavor = StandardModel::BOTTOM;
    }

    /**
     * @return the forward-backward asymmetry for e^+ e^- -> b bbar at sqrt_s
     */
    double getThValue();

private:
     
};

#endif	/* LEP2AFBBOTTOM_H */

