/* 
 * Copyright (C) 2012-2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_sf.h>
#include "PVfunctions.h"

#define LEPS 1.0e-5 // Tolerance in the limit of masses.


PVfunctions::PVfunctions(const bool bExtraMinusSign)
{
    if (bExtraMinusSign) ExtraMinusSign = -1.0;
    else ExtraMinusSign = 1.0;
}

double PVfunctions::A0(const double mu2, const double m2) const
{
#ifdef USE_LOOPTOOLS
    return ( ExtraMinusSign * myLT.PV_A0(mu2, m2) );
#else    
    if ( mu2<=0.0 || m2<0.0 )
        throw std::runtime_error("PVfunctions::A0(): Invalid argument!");
    
    if (m2==0.0)
        return ( 0.0 );
    else
        return ( ExtraMinusSign * m2*(-log(m2/mu2)+1.0) );
#endif
}

complex PVfunctions::B0(const double mu2, const double p2,
                        const double m02, const double m12) const
{   
#ifdef USE_LOOPTOOLS
    return myLT.PV_B0(mu2, p2, m02, m12);
#else    
    if ( mu2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::B0(): Invalid argument!");

    complex B0(0.0, 0.0, false);
        
    if ( p2!=0.0 && m02!=0.0 && m12!=0.0 ) {
        double m0 = sqrt(m02), m1 = sqrt(m12);
        double Lambda = sqrt( fabs((p2-m02-m12)*(p2-m02-m12) - 4.0*m02*m12) );
        double R;
        if ( p2 > (m0-m1)*(m0-m1) && p2 < (m0+m1)*(m0+m1) )
            R = - Lambda/p2*atan(Lambda/(p2-m02-m12));
        else
            R = Lambda/p2*log( fabs((p2-m02-m12+Lambda)/2.0/m0/m1) );
        B0 = - log(m0*m1/mu2) + (m02-m12)/2.0/p2*log(m12/m02) - R + 2.0;
        if ( p2>(m0+m1)*(m0+m1) ) 
            B0 += M_PI*Lambda/p2*complex::i();// imaginary part
    } else if ( p2==0.0 && m02!=0.0 && m12!=0.0 ) {
        double m0 = sqrt(m02), m1 = sqrt(m12);
        if ( fabs(m0 - m1) > LEPS )
            B0 = - m02/(m02-m12)*log(m02/mu2) + m12/(m02-m12)*log(m12/mu2) + 1.0;
        else
            B0 = - log(m02/mu2);
    } else if ( p2!=0.0 && ((m02==0.0 && m12!=0.0) || (m02!=0.0 && m12==0.0)) ) {
        double M2;
        if (m02!=0.0) M2 = m02;
        if (m12!=0.0) M2 = m12;
        B0 = - log(M2/mu2) + 2.0;
        if ( p2<M2 )
            B0 += - (1.0 - M2/p2)*log(1.0 - p2/M2);
        else if ( p2>M2 ) {
            B0 += - (1.0 - M2/p2)*log(p2/M2 - 1.0);
            B0 += (1.0 - M2/p2)*M_PI*complex::i();// imaginary part        
        } else
            B0 += 0.0;
    } else if ( p2==0.0 && m02==0.0 && m12!=0.0 )
        B0 = - log(m12/mu2) + 1.0;
    else if ( p2==0.0 && m02!=0.0 && m12==0.0 )
        B0 = - log(m02/mu2) + 1.0;        
    else if ( p2!=0.0 && m02==0.0 && m12==0.0 ) {
        if ( p2<0.0 )
            B0 = - log(-p2/mu2) + 2.0;
        else {
            B0 = - log(p2/mu2) + 2.0;
            B0 += M_PI*complex::i();// imaginary part    
        }
    } else if ( p2==0.0 && m02==0.0 && m12==0.0 )
        throw std::runtime_error("PVfunctions::B0(): IR divergent! (vanishes in DR)");
    else
        throw std::runtime_error("PVfunctions::B0(): Missing case!");
    return B0;
#endif    
}

complex PVfunctions::B1(const double mu2, const double p2,
                        const double m02, const double m12) const
{
#ifdef USE_LOOPTOOLS
    return myLT.PV_B1(mu2, p2, m02, m12);
#else
    if ( mu2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::B1(): Invalid argument!");

    double DeltaM2 = m02 - m12; 
    complex B1(0.0, 0.0, false);
    
    if (p2==0.0) {
        if (m02!=0.0 && m12!=0.0) {
            if (fabs(m02 - m12) > LEPS) {
                double F0 = - log(m12/m02);
                double F1 = - 1.0 + m02/DeltaM2*F0;
                double F2 = - 1.0/2.0 + m02/DeltaM2*F1;
                B1.real() = 1.0/2.0*( log(m12/mu2) + F2 );
            } else
                B1.real() = 1.0/2.0*log(m12/mu2);                
        } else if (m02==0.0 && m12!=0.0)
            B1.real() = 1.0/2.0*log(m12/mu2) - 1.0/4.0;
        else if (m02!=0.0 && m12==0.0)
            B1.real() = 1.0/2.0*log(m02/mu2) - 1.0/4.0;
        else
            B1 = 0.0;
    } else
        B1 = -1.0/2.0/p2*(- ExtraMinusSign*A0(mu2,m02)
                          + ExtraMinusSign*A0(mu2,m12)
                          + (DeltaM2 + p2)*B0(mu2,p2,m02,m12));
    return B1;
#endif
}

complex PVfunctions::B21(const double mu2, const double p2,
                         const double m02, const double m12) const
{   
#ifdef USE_LOOPTOOLS
    return myLT.PV_B21(mu2, p2, m02, m12);
#else
    if ( mu2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::B21(): Invalid argument!");

    double DeltaM2 = m02 - m12; 
    complex B21(0.0, 0.0, false);

    if (p2==0.0) {
        if (m02!=0.0 && m12!=0.0) {
            if (fabs(m02 - m12) > LEPS ) {
                double F0 = - log(m12/m02);
                double F1 = - 1.0 + m02/DeltaM2*F0;
                double F2 = - 1.0/2.0 + m02/DeltaM2*F1;
                double F3 = - 1.0/3.0 + m02/DeltaM2*F2;
                B21.real() = - 1.0/3.0*( log(m12/mu2) + F3 );        
            } else
                B21.real() = - 1.0/3.0*log(m12/mu2);
        } else if (m02==0.0 && m12!=0.0)
            B21.real() = - 1.0/3.0*log(m12/mu2) + 1.0/9.0;
        else if (m02!=0.0 && m12==0.0)
            B21.real() = - 1.0/3.0*log(m02/mu2) + 1.0/9.0;
        else
            throw std::runtime_error("PVfunctions::B21(): Undefined!");
    } else {
        double Lambdabar2 = (p2-m02-m12)*(p2-m02-m12) - 4.0*m02*m12;
        B21 = - (3.0*(m02 + m12) - p2)/18.0/p2 
              + (DeltaM2 + p2)/3.0/p2/p2*(-ExtraMinusSign)*A0(mu2,m02)
              - (DeltaM2 + 2.0*p2)/3.0/p2/p2*(-ExtraMinusSign)*A0(mu2,m12)
              + (Lambdabar2 + 3.0*p2*m02)/3.0/p2/p2*B0(mu2,p2,m02,m12);
    }
    return B21;
#endif
}

complex PVfunctions::B22(const double mu2, const double p2,
                         const double m02, const double m12) const
{   
#ifdef USE_LOOPTOOLS
    return myLT.PV_B22(mu2, p2, m02, m12);
#else
    if ( mu2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::B22(): Invalid argument!");

    complex B22(0.0, 0.0, false);

    if (p2 == 0.0){
        if (m02 != 0.0 && m12 != 0.0) {
            if(fabs(m02 - m12) < LEPS)
                B22 = m02/2.0*(- log(m02/mu2) + 1.0);
            else
                B22 = 1.0/4.0*(m02 + m12)*(- log(sqrt(m02)*sqrt(m12)/mu2) + 3.0/2.0)
                      - (m02*m02 + m12*m12)/8.0/(m02 - m12)*log(m02/m12);
        } else if ((m02 != 0.0 && m12 == 0.0) || (m02 == 0.0 && m12 != 0.0)) {
            double M2;
            if (m02!=0.0) M2 = m02;
            if (m12!=0.0) M2 = m12;
            B22 = M2/4.0*(- log(M2/mu2) + 3.0/2.0);
        } else
            B22 = 0.0;
    } else {
        if (m02 != 0.0 && m12 != 0.0) {
            if(fabs(m02 - m12) < LEPS)
                B22 = (6.0*m02 - p2)/18.0 + ExtraMinusSign*A0(mu2,m02)/6.0
                       - (p2 - 4.0*m02)/12.0*B0(mu2,p2,m02,m12);
            else {
                double DeltaM2 = m02 - m12;
                double Lambdabar2 = (p2-m02-m12)*(p2-m02-m12) - 4.0*m02*m12;
                B22 = (3.0*(m02 + m12) - p2)/18.0
                       - (DeltaM2 + p2)/12.0/p2*(-ExtraMinusSign)*A0(mu2,m02)
                       + (DeltaM2 - p2)/12.0/p2*(-ExtraMinusSign)*A0(mu2,m12)
                       - Lambdabar2*B0(mu2,p2,m02,m12)/12.0/p2;
            }
        } else if ((m02 != 0.0 && m12 == 0.0) || (m02 == 0.0 && m12 != 0.0)) {
            double M2;
            if (m02!=0.0) M2 = m02;
            if (m12!=0.0) M2 = m12;
            B22 = (3.0*M2 - p2)/18.0 - (M2 + p2)/12.0/p2*(-ExtraMinusSign)*A0(mu2,M2)
                  - (M2 - p2)*(M2 - p2)/12.0/p2*B0(mu2,p2,M2,0.0);
        } else
            B22 = - p2/18.0 - p2/12.0*B0(mu2,p2,0.0,0.0);
    }
    return B22;
#endif
}

complex PVfunctions::Bf(const double mu2, const double p2,
                        const double m02, const double m12) const
{   
    if ( mu2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::Bf(): Invalid argument!");

    complex Bf(0.0, 0.0, false);
    Bf = 2.0*(B21(mu2,p2,m02,m12) + B1(mu2,p2,m02,m12));
    return Bf;
}

complex PVfunctions::B0p(const double muIR2, const double p2,
                         const double m02, const double m12) const
{   
#ifdef USE_LOOPTOOLS
    return myLT.PV_B0p(muIR2, p2, m02, m12);
#else
    if ( muIR2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::B0p(): Invalid argument!");
    
    complex B0p(0.0, 0.0, false);
        
    if (p2==0.0) {
        if ( m02!=0.0 && m12!=0.0 ) {
            if ( fabs(m02 - m12) < LEPS )
                B0p = 1.0/6.0/m02;
            else {
                double DeltaM2 = m02 - m12;
                B0p = (m02 + m12)/2.0/pow(DeltaM2,2.0)
                        + m02*m12/pow(DeltaM2,3.0)*log(m12/m02);
            } 
        } else if ( m02!=0.0 && m12==0.0 )
            B0p = 1.0/2.0/m02;
        else if ( m02==0.0 && m12!=0.0 )
            B0p = 1.0/2.0/m12;
        else
            throw std::runtime_error("PVfunctions::B0p(): Undefined!");
    } else {
        if ( m02!=0.0 && m12!=0.0 ) {
            double m0 = sqrt(m02), m1 = sqrt(m12);
            double Lambda = sqrt( fabs((p2-m02-m12)*(p2-m02-m12) - 4.0*m02*m12) );
            double Rprime;
            if ( p2 > (m0-m1)*(m0-m1) && p2 < (m0+m1)*(m0+m1) )
                Rprime = ((p2 - m02 - m12)/Lambda + Lambda/p2)
                          *atan(Lambda/(p2-m02-m12));
            else
                Rprime = ((p2 - m02 - m12)/Lambda - Lambda/p2)
                          *log( fabs((p2-m02-m12+Lambda)/2.0/m0/m1) );
            B0p = - (m02 - m12)/2.0/p2/p2*log(m12/m02) - (Rprime + 1.0)/p2;
            if ( p2>(m0+m1)*(m0+m1) )
                B0p += M_PI/p2*((p2 - m02 - m12)/Lambda - Lambda/p2)
                      *complex::i();// imaginary part
        } else if ( (m02==0.0 && m12!=0.0) || (m02!=0.0 && m12==0.0) ) {
            double M2;
            if (m02!=0.0) M2 = m02;
            if (m12!=0.0) M2 = m12;
            if ( p2<M2 )
                B0p = - M2/p2/p2*log(1.0 - p2/M2) - 1.0/p2;
            else if ( p2>M2 ) {
                B0p = - M2/p2/p2*log(p2/M2 - 1.0) - 1.0/p2;
                B0p += M2/p2/p2*M_PI*complex::i();// imaginary part        
            } else /* p2=M2 */
                B0p = 1.0/2.0/M2*(log(M2/muIR2) - 2.0);
        } else if ( m02==0.0 && m12==0.0 )
            B0p = - 1.0/p2;
        else
            throw std::runtime_error("PVfunctions::B0p(): Undefined!");
    }
    return B0p;
#endif
}

complex PVfunctions::B1p(const double mu2, const double p2,
                         const double m02, const double m12) const
{   
#ifdef USE_LOOPTOOLS
    return myLT.PV_B1p(mu2, p2, m02, m12);
#else
    if ( mu2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::B1p(): Invalid argument!");

    complex B1p(0.0, 0.0, false);
    
    if (p2==0.0)
        throw std::runtime_error("PVfunctions::B1p(): Undefined!");
    else {
        double DeltaM2 = m02 - m12;
        B1p = - ( 2.0*B1(mu2,p2,m02,m12) + B0(mu2,p2,m02,m12)
                 + (DeltaM2 + p2)*B0p(mu2,p2,m02,m12) )/2.0/p2;
    }
    return B1p;
#endif
}

complex PVfunctions::B21p(const double mu2, const double p2,
                          const double m02, const double m12) const
{   
#ifdef USE_LOOPTOOLS
    return myLT.PV_B21p(mu2, p2, m02, m12);
#else
    if ( mu2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::B21p(): Invalid argument!");

    double p4 = p2*p2, p6=p2*p2*p2;
    double DeltaM2 = m02 - m12; 
    complex B21p(0.0, 0.0, false);

    if (p2==0.0)
        throw std::runtime_error("PVfunctions::B21p(): Undefined!");
    else {
        double Lambdabar2 = (p2-m02-m12)*(p2-m02-m12) - 4.0*m02*m12;
        B21p = (m02 + m12)/6.0/p4 - (2.0*DeltaM2 + p2)/3.0/p6*(-ExtraMinusSign)*A0(mu2,m02)
                + 2.0*(DeltaM2 + p2)/3.0/p6*(-ExtraMinusSign)*A0(mu2,m12)
                - (2.0*DeltaM2*DeltaM2 + p2*m02 - 2.0*p2*m12)/3.0/p6*B0(mu2,p2,m02,m12)
                + (Lambdabar2 + 3.0*p2*m02)/3.0/p4*B0p(mu2,p2,m02,m12);
    }
    return B21p;
#endif
}

complex PVfunctions::B22p(const double mu2, const double p2,
                          const double m02, const double m12) const
{   
#ifdef USE_LOOPTOOLS
    return myLT.PV_B22p(mu2, p2, m02, m12);
#else
    if ( mu2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::B22p(): Invalid argument!");

    complex B22p(0.0, 0.0, false);
    double DeltaM2 = m02 - m12;
    if (p2==0.0) {
        if ( fabs(DeltaM2) < LEPS )
            B22p = - 1.0/18.0 - 1.0/12.0*B0(mu2,0.0,m02,m12)
                   + (m02 + m12)/6.0*B0p(mu2,0.0,m02,m12);
        else if ( m02==0.0 || m12==0.0 )
            B22p = - 1.0/18.0 - 1.0/12.0*B0(mu2,0.0,m02,m12)
                   + (m02 + m12)/6.0*B0p(mu2,0.0,m02,m12) - 1.0/72.0;
        else
            B22p = - 1.0/18.0 - 1.0/12.0*B0(mu2,0.0,m02,m12)
                   + (m02 + m12)/6.0*B0p(mu2,0.0,m02,m12)
                   - 1.0/24.0
                   *( (m02*m02 + 10.0*m02*m12 + m12*m12)/3.0/DeltaM2/DeltaM2
                       + 2.0*m02*m12*(m02 + m12)/DeltaM2/DeltaM2/DeltaM2*log(m12/m02) );
    } else {
        double Lambdabar2 = (p2-m02-m12)*(p2-m02-m12) - 4.0*m02*m12;
        if ( fabs(DeltaM2) < LEPS )
            B22p = - 1.0/18.0 - B0(mu2,p2,m02,m12)/12.0
                   - Lambdabar2/12.0/p2*B0p(mu2,p2,m02,m12);
        else
            B22p = - 1.0/18.0
                   + DeltaM2/12.0/p2/p2*(- ExtraMinusSign*A0(mu2,m02)
                                         + ExtraMinusSign*A0(mu2,m12)
                                         + DeltaM2*B0(mu2,p2,m02,m12))
                   - B0(mu2,p2,m02,m12)/12.0
                   - Lambdabar2/12.0/p2*B0p(mu2,p2,m02,m12);
    }
    return B22p;
#endif
}

complex PVfunctions::Bfp(const double mu2, const double p2,
                         const double m02, const double m12) const
{   
    if ( mu2<=0.0 || p2<0.0 || m02<0.0 || m12<0.0 )
        throw std::runtime_error("PVfunctions::Bfp(): Invalid argument!");

    complex Bfp(0.0, 0.0, false);
    Bfp = 2.0*(B21p(mu2,p2,m02,m12) + B1p(mu2,p2,m02,m12));
    return Bfp;
}

complex PVfunctions::C0(const double p2, 
                        const double m02, const double m12, const double m22) const
{
#ifdef USE_LOOPTOOLS
    return ( ExtraMinusSign * myLT.PV_C0(p2, m02, m12, m22) );
#else 
    if ( p2<0.0 || m02<0.0 || m12<0.0 || m22<0.0 )
        throw std::runtime_error("PVfunctions::C0(): Invalid argument!");

    complex C0(0.0, 0.0, false);   

    if (p2==0.0) {
        if (m02!=0.0 && m12!=0.0 && m22!=0.0) {
            bool diff01 = (fabs(m02 - m12) > LEPS);
            bool diff12 = (fabs(m12 - m22) > LEPS);
            bool diff20 = (fabs(m22 - m02) > LEPS);
            if (diff01 && diff12 && diff20)
                return ( - ( m12/(m02 - m12)*log(m12/m02)
                            - m22/(m02 - m22)*log(m22/m02) )/(m12 - m22) );
            else if (!diff01 && diff12 && diff20)
                return ( - (- m02 + m22 - m22*log(m22/m02))/(m02 - m22)/(m02 - m22) );
            else if (diff01 && !diff12 && diff20)
                return ( - (  m02 - m12 + m02*log(m12/m02))/(m02 - m12)/(m02 - m12) );
            else if (diff01 && diff12 && !diff20)
                return ( - (- m02 + m12 - m12*log(m12/m02))/(m02 - m12)/(m02 - m12) );
            else
                return ( 1.0/2.0/m02 );
        }
    } else {
        if (fabs(m02 - m22) < LEPS && fabs(m02 - m12) > LEPS) {
            double epsilon = 1.0e-12;
            gsl_complex tmp = gsl_complex_rect(1.0 - 4.0*m02/p2, epsilon);
            tmp = gsl_complex_sqrt(tmp);
            complex tmp_complex(GSL_REAL(tmp), GSL_IMAG(tmp), false);
            complex x0 = 1.0 - (m02 - m12)/p2;
            complex x1 = (1.0 + tmp_complex)/2.0;
            complex x2 = (1.0 - tmp_complex)/2.0;
            complex x3 = m02/(m02 - m12);

            if ( x0==x1 || x0==x2 || x0==x3)
                throw std::runtime_error("PVfunctions::C0(): Undefined-2!");

            complex arg[6];
            arg[0] = (x0 - 1.0)/(x0 - x1);
            arg[1] = x0/(x0 - x1);
            arg[2] = (x0 - 1.0)/(x0 - x2);
            arg[3] = x0/(x0 - x2);
            arg[4] = (x0 - 1.0)/(x0 - x3);
            arg[5] = x0/(x0 - x3);
            
            complex Li2[6];
            for (int i=0; i<6; i++) {
                gsl_sf_result re, im;
                gsl_sf_complex_dilog_xy_e(arg[i].real(), arg[i].imag(), &re, &im);
                Li2[i].real() = re.val;
                Li2[i].imag() = im.val;
                
                /* Check the sizes of errors */
                //std::cout << "re.val=" << re.val << "  re.err=" << re.err << std::endl;
                //std::cout << "im.val=" << im.val << "  im.err=" << im.err << std::endl;                
            }
            C0 = - 1.0/p2*( Li2[0] - Li2[1] + Li2[2] - Li2[3] - Li2[4] + Li2[5]);        
        } else if (m02!=0.0 && m22!=0.0 && fabs(sqrt(m02) - sqrt(m22)) > LEPS && m12==0.0) {
            double epsilon = 1.0e-12;
            double tmp_real = pow((m02+m22-p2),2.0) - 4.0*m02*m22;
            gsl_complex tmp = gsl_complex_rect(tmp_real, epsilon);
            tmp = gsl_complex_sqrt(tmp);
            complex tmp_complex(GSL_REAL(tmp), GSL_IMAG(tmp), false);
            complex x1 = (p2 - m02 + m22 + tmp_complex)/2.0/p2;
            complex x2 = (p2 - m02 + m22 - tmp_complex)/2.0/p2;            

            if ( x1==0.0 || x1==1.0 || x2==0.0 || x2==1.0 )
                throw std::runtime_error("PVfunctions::C0(): Undefined-3!");
            
            complex arg1 = (x1 - 1.0)/x1;
            complex arg2 = x2/(x2 - 1.0);
            gsl_complex arg1_tmp = gsl_complex_rect(arg1.real(), arg1.imag());
            gsl_complex arg2_tmp = gsl_complex_rect(arg2.real(), arg2.imag());            
            C0.real() = - 1.0/p2*( GSL_REAL(gsl_complex_log(arg1_tmp))
                                    *GSL_REAL(gsl_complex_log(arg2_tmp))
                                   - GSL_IMAG(gsl_complex_log(arg1_tmp))
                                     *GSL_IMAG(gsl_complex_log(arg2_tmp)) );
            C0.imag() = - 1.0/p2*( GSL_REAL(gsl_complex_log(arg1_tmp))
                                    *GSL_IMAG(gsl_complex_log(arg2_tmp))
                                   + GSL_IMAG(gsl_complex_log(arg1_tmp))
                                      *GSL_REAL(gsl_complex_log(arg2_tmp)) );            
        } else if (m02 == 0. && m12 != 0. && m22 != 0.) {
            complex arg[2];
            arg[0] = 1.0 - m22/m12;
            arg[1] = 1.0 - (-p2+m22)/m12;
            complex Li2[2];
            for (int i=0; i<2; i++) {
                gsl_sf_result re, im;
                gsl_sf_complex_dilog_xy_e(arg[i].real(), arg[i].imag(), &re, &im);
                Li2[i].real() = re.val;
                Li2[i].imag() = im.val;
            }
            C0 = 1./(-p2)*(Li2[0]-Li2[1]);
        } else if (m02 != 0. && m12 != 0. && m22 != 0.
                && fabs(sqrt(m02) - sqrt(m12)) > LEPS
                && fabs(sqrt(m12) - sqrt(m22)) > LEPS) {
            double x0 = 1.0 - (m02-m12)/p2;
            double x1 = -(-p2+m02-m22-sqrt(fabs((m02+m22-p2)*(m02+m22-p2) - 4.*m02*m22)))/p2/2.0;
            double x2 = -(-p2+m02-m22+sqrt(fabs((m02+m22-p2)*(m02+m22-p2) - 4.*m02*m22)))/p2/2.0;
            double x3 = m22/(m22-m12);
            
            complex arg[6];
            arg[0] = (x0-1.0)/(x0-x1);
            arg[1] = x0/(x0-x1);
            arg[2] = (x0-1.0)/(x0-x2);
            arg[3] = x0/(x0-x2);
            arg[4] = (x0-1.0)/(x0-x3);
            arg[5] = x0/(x0-x3);
            
            complex Li2[6];
            for (int i=0; i<2; i++) {
                gsl_sf_result re, im;
                gsl_sf_complex_dilog_xy_e(arg[i].real(), arg[i].imag(), &re, &im);
                Li2[i].real() = re.val;
                Li2[i].imag() = im.val;
            }
            
            C0 = -1.0/p2*(Li2[0] - Li2[1] + Li2[2] - Li2[3] - Li2[4] + Li2[5]);
        } else
            throw std::runtime_error("PVfunctions::C0(): Undefined-4!");
    }
    return ( - ExtraMinusSign * C0 );
#endif    
}

complex PVfunctions::D0(const double s, const double t, const double m02,
                        const double m12, const double m22, const double m32) const
{
    if (s==0.0 && t==0.0) {
        bool diff01 = (fabs(m02 - m12) > LEPS);
        if ( diff01 )
            return ( ( ExtraMinusSign * C0(0.0, m02, m22, m32)
                       - ExtraMinusSign * C0(0.0, m12, m22, m32) ) / (m02 - m12) );
        else {
            if (m02!=0.0 && m12!=0.0 && m22!=0.0 && m32!=0.0) {
                bool diff02 = (fabs(m02 - m22) > LEPS);
                bool diff03 = (fabs(m02 - m32) > LEPS);
                bool diff23 = (fabs(m22 - m32) > LEPS);
                if ( diff02 && diff03 && diff23 )
                    return ( - 1.0/(m02 - m22)/(m02 - m32)
                             + m22/(m02 - m22)/(m02 - m22)/(m32 - m22)*log(m22/m02)
                             + m32/(m02 - m32)/(m02 - m32)/(m22 - m32)*log(m32/m02) );
                else if ( !diff02 && diff03 && diff23 )
                    return ( (m02*m02 - m32*m32 + 2.0*m02*m32*log(m32/m02))
                             /2.0/m02/(m02 - m32)/(m02 - m32)/(m02 - m32) );
                else if ( diff02 && !diff03 && diff23 )
                    return ( (m02*m02 - m22*m22 + 2.0*m02*m22*log(m22/m02))
                             /2.0/m02/(m02 - m22)/(m02 - m22)/(m02 - m22) );
                else if ( diff02 && diff03 && !diff23 )
                    return ( ( - 2.0*m02 + 2.0*m22 - (m02 + m22)*log(m22/m02))
                             /(m02 - m22)/(m02 - m22)/(m02 - m22) );
                else
                    return ( 1.0/6.0/m02/m02 );
            } else
                throw std::runtime_error("PVfunctions::D0(): Undefined!");
        }
    } 

#ifdef USE_LOOPTOOLS
    return myLT.PV_D0(s, t, m02, m12, m22, m32);
#else
    complex D0(0.0, 0.0, false);

    if (s>0.0 && t<0.0 && m02!=0.0 && m12==0.0 && m22==m02 && m32!=0.0
            && m02!=m32 && t-m32*m32+m02*m02!=0.0) {
        //D0(s,t; m02, 0.0, m02, m32)
        double x1, x2;
        if (s >= 4.0*m02) {
            x1 = (1.0 - sqrt(1.0 - 4.0*m02/s))/2.0;
            x2 = (1.0 + sqrt(1.0 - 4.0*m02/s))/2.0;        
        } else {
            throw std::runtime_error("PVfunctions::D0(): Undefined!");
        }
        double x3 = m32/(m32 - m02);
        double x4 = (t - m32)/(t - m32 + m02);
        double d4 = 1.0 - 4.0*m02*t*(t - m32 + m02)/(s*(t - m32)*(t - m32));
        double x1tilde, x2tilde;
        if (d4 >= 0.0) {
            x1tilde = x4/2.0*(1.0 - sqrt(d4));
            x2tilde = x4/2.0*(1.0 + sqrt(d4));
        } else {
            throw std::runtime_error("PVfunctions::D0(): Undefined!");
        }
            

        throw std::runtime_error("PVfunctions::D0(): Undefined!");
    } else if (s>0.0 && t<0.0 && m02!=0.0 && m12==0.0 && m22==m02 && m32==0.0) {
        //D0(s,t; m02, 0.0, m02, 0.0)
        
        throw std::runtime_error("PVfunctions::D0(): Undefined!");
    } else 
        throw std::runtime_error("PVfunctions::D0(): Undefined!");
        
    return D0; 
#endif
}

complex PVfunctions::D22(const double s, const double t, const double m02,
                         const double m12, const double m22, const double m32) const
{
    if (s==0.0 && t==0.0) {
        bool diff01 = (fabs(m02 - m12) > LEPS);
        if ( diff01 )
            return ( 0.25/(m02 - m12)*(m02*ExtraMinusSign*C0(0.0, m02, m22, m32)
                     - m12*ExtraMinusSign*C0(0.0, m12, m22, m32)) );
        else {
            if (m02!=0.0 && m12!=0.0 && m22!=0.0 && m32!=0.0) {
                bool diff02 = (fabs(m02 - m22) > LEPS);
                bool diff03 = (fabs(m02 - m32) > LEPS);
                bool diff23 = (fabs(m22 - m32) > LEPS);
                if ( diff02 && diff03 && diff23 )
                    return ( m02/4.0/(m02 - m22)/(m32 - m02)
                             + m22*m22/4.0/(m02 - m22)/(m02 - m22)/(m32 - m22)*log(m22/m02)
                             + m32*m32/4.0/(m02 - m32)/(m02 - m32)/(m22 - m32)*log(m32/m02) );
                else if ( !diff02 && diff03 && diff23 )
                    return ( ( - m02*m02 + 4.0*m02*m32 - 3.0*m32*m32
                               + 2.0*m32*m32*log(m32/m02) )
                             /8.0/(m02 - m32)/(m02 - m32)/(m02 - m32) );
                else if ( diff02 && !diff03 && diff23 )
                    return ( ( - m02*m02 + 4.0*m02*m22 - 3.0*m22*m22
                               + 2.0*m22*m22*log(m22/m02) )
                             /8.0/(m02 - m22)/(m02 - m22)/(m02 - m22) );
                else if ( diff02 && diff03 && !diff23 )
                    return ( ( - m02*m02 + m22*m22 - 2.0*m02*m22*log(m22/m02) )
                             /4.0/(m02 - m22)/(m02 - m22)/(m02 - m22) );
                else
                    return ( - 1.0/12.0/m02 );
            } else
                throw std::runtime_error("PVfunctions::D22(): Undefined!");
        }
    }

#ifdef USE_LOOPTOOLS
    return myLT.PV_D22(s, t, m02, m12, m22, m32);
#else
    complex D22(0.0, 0.0, false);

    throw std::runtime_error("PVfunctions::D22(): Undefined!");

    return D22;
#endif
}

