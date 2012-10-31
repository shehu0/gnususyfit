/* 
 * Copyright (C) 2012 SUSYfit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include "PtauPol.h"


double PtauPol::getThValue() {  
    double P_tau_pol;
    if (bCHMN)  
        P_tau_pol = myEW_CHMN.A_l(SM.TAU);
    else {
        P_tau_pol = myEW.A_l(SM.TAU);

        if ( myEW.checkModelForSTU() ) {
            double alpha = SM.alphaMz();
            double c2 = myEW.c02();
            double s2 = myEW.s02();
            double s4 = s2*s2;
            
            P_tau_pol -= 4.0*alpha*s2/pow(1.0-4.0*s2+8.0*s4, 2.0)
                         *( myEW.S() - 4.0*c2*s2*myEW.T() );
        }
    }
 
    return P_tau_pol;
}
        
