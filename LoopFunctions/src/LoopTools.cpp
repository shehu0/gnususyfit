/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <iostream>
#include <complex>
#include <clooptools.h>
#include "LoopTools.h"

static bool LoopToolsInit = false;

LoopTools::LoopTools() 
{
    if (!LoopToolsInit) {
        //std::cout << std::endl;
        ltini();
        std::cout << std::endl;
        LoopToolsInit = true;
    }
}

LoopTools::~LoopTools() 
{
    // for debug
    //std::cout << std::endl
    //          << "************* LoopTools ****************" << std::endl;
    //ltexi();
    //std::cout << "****************************************" << std::endl;
}

double LoopTools::PV_A0(const double mu, const double m) const 
{
    setmudim(mu*mu);
    std::complex<double> A0val = A0(m*m);
    return ( - A0val.real() );
}
    
complex LoopTools::PV_B0(const double mu, const double p2, 
                         const double m0, const double m1) const 
{
    setmudim(mu*mu);
    std::complex<double> B0val = B0(p2, m0*m0, m1*m1);
    return complex( B0val.real(), B0val.imag(), false );
}

complex LoopTools::PV_B1(const double mu, const double p2,
                         const double m0, const double m1) const
{
    setmudim(mu*mu);
    std::complex<double> B1val = B1(p2, m0*m0, m1*m1);
    return complex( B1val.real(), B1val.imag(), false );
}

complex LoopTools::PV_B21(const double mu, const double p2,
                          const double m0, const double m1) const
{
    setmudim(mu*mu);
    std::complex<double> B21val = B11(p2, m0*m0, m1*m1);
    return complex( B21val.real(), B21val.imag(), false );
}

complex LoopTools::PV_B22(const double mu, const double p2,
                          const double m0, const double m1) const
{
    setmudim(mu*mu);
    std::complex<double> B22val = B00(p2, m0*m0, m1*m1);
    return complex( B22val.real(), B22val.imag(), false );
}

complex LoopTools::PV_B0p(const double muIR, const double p2,
                          const double m0, const double m1) const
{
    setmudim(muIR*muIR);
    std::complex<double> B0pval = DB0(p2, m0*m0, m1*m1);
    return complex( B0pval.real(), B0pval.imag(), false );
}

complex LoopTools::PV_B1p(const double mu, const double p2,
                          const double m0, const double m1) const
{
    setmudim(mu*mu);
    std::complex<double> B1pval = DB1(p2, m0*m0, m1*m1);
    return complex( B1pval.real(), B1pval.imag(), false );
}

complex LoopTools::PV_B21p(const double mu, const double p2,
                           const double m0, const double m1) const
{
    setmudim(mu*mu);
    std::complex<double> B21pval = DB11(p2, m0*m0, m1*m1);
    return complex( B21pval.real(), B21pval.imag(), false );
}

complex LoopTools::PV_B22p(const double mu, const double p2,
                           const double m0, const double m1) const
{
    setmudim(mu*mu);
    std::complex<double> B22pval = DB00(p2, m0*m0, m1*m1);
    return complex( B22pval.real(), B22pval.imag(), false );
}

complex LoopTools::PV_C0(const double p2, 
                         const double m0, const double m1, const double m2) const 
{
    std::complex<double> C0val = C0(0.0, 0.0, p2, m0*m0, m1*m1, m2*m2);
    return complex( - C0val.real(), - C0val.imag(), false );
}
    
complex LoopTools::PV_D0(const double s, const double t, const double m0, 
                         const double m1, const double m2, const double m3) const 
{
    std::complex<double> D0val = D0(0.0, 0.0, 0.0, 0.0, s, t, m0*m0, m1*m1, m2*m2, m3*m3);
    return complex( D0val.real(), D0val.imag(), false );
}


