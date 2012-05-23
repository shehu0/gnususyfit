 /* 
 * File:   EWSMTwoLoopEW.cpp
 * Author: mishima
 */

#include <TMath.h>
#include <gsl/gsl_sf_dilog.h>
#include "EWSMTwoLoopEW.h"


EWSMTwoLoopEW::EWSMTwoLoopEW(const EWSMcache& cache_i) : cache(cache_i), myOneLoopEW(cache_i) {
}


////////////////////////////////////////////////////////////////////////

double EWSMTwoLoopEW::DeltaAlpha_l() const {
    double xl[3] = { pow(cache.Mz()/cache.ml(StandardModel::ELECTRON), 2.0), 
                     pow(cache.Mz()/cache.ml(StandardModel::MU), 2.0), 
                     pow(cache.Mz()/cache.ml(StandardModel::TAU), 2.0) };
    double log_l[3] = { 2.0*cache.logMZtoME(), 
                        2.0*cache.logMZtoMMU(), 
                        2.0*cache.logMZtoMTAU() };

    double twoLoop[3];
    for (int i = 0; i < 3; i++) {
        twoLoop[i] = - 5.0/24.0 + cache.GetZeta3() + log_l[i]/4.0 
                     + 3.0/xl[i]*log_l[i];
    }
            
    return ( pow(cache.ale()/M_PI, 2.0)
             *(twoLoop[0] + twoLoop[1] + twoLoop[2]) );
}    


double EWSMTwoLoopEW::DeltaAlpha_t() const {   
    return (0.0);
}


double EWSMTwoLoopEW::DeltaRho(const double Mw_i) const {
    double Mz = cache.Mz();
    double Mw = cache.Mw(Mw_i);
    double sW2 = cache.sW2(Mw);
    double cW2 = cache.cW2(Mw);
    
    double DeltaRho = 3.0*rho_2();
    DeltaRho *= pow(cache.Xt_alpha(Mw), 2.0);
    
    /* added O(alpha^2) contribution from the Z-gamma mixing */
    DeltaRho += - pow(cache.ale()/4.0/M_PI, 2.0)*cW2/sW2
                  *pow(myOneLoopEW.PiZgamma_fer(Mz,Mz*Mz,Mw).real(), 2.0);

    return DeltaRho;
}


double EWSMTwoLoopEW::DeltaR_rem(const double Mw_i) const {

    /*!!!! Write codes for contribution of O(G^2Mt^2Mz^2) !!!!*/

    return (0.0);     
}


complex EWSMTwoLoopEW::deltaRho_rem_l(const StandardModel::lepton l, 
                                      const double Mw_i) const {

    /*!!!! Write codes for contribution of O(G^2Mt^2Mz^2) !!!!*/    
    
    return ( complex(0.0,0.0,false) );
}


complex EWSMTwoLoopEW::deltaRho_rem_q(const StandardModel::quark q, 
                                      const double Mw_i) const {
    if(q==StandardModel::TOP) return ( complex(0.0,0.0,false) );

    /*!!!! Write codes for contribution of O(G^2Mt^2Mz^2) !!!!*/    
    
    return ( complex(0.0,0.0,false) );
}


complex EWSMTwoLoopEW::deltaKappa_rem_l(const StandardModel::lepton l, 
                                        const double Mw_i) const {

    /*!!!! Write codes for contribution of O(G^2Mt^2Mz^2) !!!!*/
    
    return ( complex(0.0,0.0,false) );
}


complex EWSMTwoLoopEW::deltaKappa_rem_q(const StandardModel::quark q, 
                                        const double Mw_i) const {
    if(q==StandardModel::TOP) return ( complex(0.0,0.0,false) );

    /*!!!! Write codes for contribution of O(G^2Mt^2Mz^2) !!!!*/    
    
    return ( complex(0.0,0.0,false) );
}


////////////////////////////////////////////////////////////////////////   `

double EWSMTwoLoopEW::rho_2() const {
    double a = cache.mh()*cache.mh()/cache.Mt()/cache.Mt();
    if (a<=0.0) throw "a is out of range in EWSMTwoLoopEW::rho_2";
    double g_a = g(a);
    double f_a_0 = f0(a);// f(a,0)
    double f_a_1 = f1(a);// f(a,1)
    double log_a = - 2.0*cache.logMTOPtoMH();
    return ( 25.0 - 4.0*a + 0.5*(a*a - 12.0*a - 12.0)*log_a
             + (a - 2.0)/2.0/a*M_PI*M_PI + 0.5*(a - 4.0)*sqrt(a)*g_a
             - 3.0/a*(a - 1.0)*(a - 1.0)*(a - 2.0)*f_a_0
             + 3.0*(a*a - 6.0*a + 10.0)*f_a_1 );
}


double EWSMTwoLoopEW::tau_2() const {
    double a = cache.mh()*cache.mh()/cache.Mt()/cache.Mt();
    if (a<=0.0) throw "a is out of range in EWSMTwoLoopEW::tau_2";
    double g_a = g(a);
    double f_a_0 = f0(a);// f(a,0)
    double f_a_1 = f1(a);// f(a,1)
    double log_a = - 2.0*cache.logMTOPtoMH();
    return ( 9.0 - 13.0/4.0*a - 2.0*a*a - a/4.0*(19.0 + 6.0*a)*log_a
             - a*a/4.0*(7.0 - 6.0*a)*log_a*log_a
             - (1.0/4.0 + 7.0/2.0*a*a - 3.0*a*a*a)*M_PI*M_PI/6.0
             + (a/2.0 - 2.0)*sqrt(a)*g_a 
             + (a - 1.0)*(a - 1.0)*(4.0*a - 7.0/4.0)*f_a_0
             - (a*a*a - 33.0/4.0*a*a + 18.0*a - 7.0)*f_a_1 );
}


double EWSMTwoLoopEW::g(const double a) const {
    if (a >= 0.0 && a <= 4.0 ) {
        double phi = 2.0*asin(sqrt(a/4.0));
        return ( sqrt(4.0 - a)*(M_PI - phi) );
    } else if (a > 4.0) {
        double y = 4.0/a;
        double xi = (sqrt(1.0-y) - 1.0)/(sqrt(1.0-y) + 1.0);
        return ( sqrt(a - 4.0)*log(-xi) );
    } else
        throw "Out of range in EWSMTwoLoopEW::g()";
}


double EWSMTwoLoopEW::f0(const double a) const {
    if (a >= 0.0 )
        return ( gsl_sf_dilog(1.0-a) );
    else
        throw "Out of range in EWSMTwoLoopEW::f0()";
}


double EWSMTwoLoopEW::f1(const double a) const {
    if (a >= 0.0 && a <= 4.0 ) {
        double y = 4.0/a;
        double phi = 2.0*asin(sqrt(a/4.0));
        return ( -2.0/sqrt(y-1.0)*cache.getClausen().Cl2(phi) );
    } else if (a > 4.0) {
        double y = 4.0/a;
        double xi = (sqrt(1.0-y) - 1.0)/(sqrt(1.0-y) + 1.0);
        return ( -1.0/sqrt(1.0-y)*(M_PI*M_PI/6.0 + 2.0*gsl_sf_dilog(xi)) );
    } else
        throw "Out of range in EWSMTwoLoopEW::f1()";
}








