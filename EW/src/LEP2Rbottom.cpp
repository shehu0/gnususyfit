/* 
 * File:   LEP2Rbottom.cpp
 * Author: mishima
 */

#include "LEP2Rbottom.h"


LEP2Rbottom::LEP2Rbottom(const EW& EW_i, const double sqrt_s_i) : ThObservable(EW_i), 
            myEW(EW_i), myLEP2oblique(EW_i), sqrt_s(sqrt_s_i) {
    bDP = true;
    bWEAK = true;
    bQED = true;
}


double LEP2Rbottom::getThValue() { 
    double s = sqrt_s*sqrt_s;
    double Mw = myEW.getSM().Mw(); 
    double GammaZ = myEW.Gamma_Z();

    if (!myEW.getSM().getEWSM()->checkForLEP2(SMparams_cache, bool_cache,
                                              s, Mw, GammaZ, bDP, bWEAK, bQED)) {
        double sigma_b, sigma_had;
        sigma_b = myEW.getSM().sigma_q_LEP2(StandardModel::BOTTOM, 
                                            s, Mw, GammaZ, bDP, bWEAK, bQED);
        sigma_had = myEW.getSM().sigma_q_LEP2(StandardModel::UP, 
                                              s, Mw, GammaZ, bDP, bWEAK, bQED)
                  + myEW.getSM().sigma_q_LEP2(StandardModel::DOWN, 
                                              s, Mw, GammaZ, bDP, bWEAK, bQED)
                  + myEW.getSM().sigma_q_LEP2(StandardModel::CHARM, 
                                              s, Mw, GammaZ, bDP, bWEAK, bQED)
                  + myEW.getSM().sigma_q_LEP2(StandardModel::STRANGE, 
                                              s, Mw, GammaZ, bDP, bWEAK, bQED)
                  + sigma_b;
        SMresult_cache = sigma_b/sigma_had;
    }
    double R_b = SMresult_cache;
    
    if ( myEW.checkModelForSTU() ) {
        R_b += myLEP2oblique.R_q_LEP2_NP(StandardModel::BOTTOM, s);
    }
    
    return R_b;
}
        




