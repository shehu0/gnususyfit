/* 
 * File:   LEP2TwoFermions.h
 * Author: mishima
 */

#ifndef LEP2TWOFERMIONS_H
#define	LEP2TWOFERMIONS_H

#include <StandardModel.h>
#include "EW.h"
using namespace gslpp;


/**
 * @class LEP2TwoFermions
 * @brief Cross sections and forward-backward asymmetries for e^+e^- -> f fbar at LEP-II
 */
    class LEP2TwoFermions : public EW {
public:

    /**
     * @brief LEP2TwoFermions constructor
     * @param[in] SM_i an object of StandardModel class
     */    
    LEP2TwoFermions(const StandardModel& SM_i);

    
    ////////////////////////////////////////////////////////////////////////     
    
    /**
     * @param[in] l name of a lepton
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] cosTheta cosine of the scattering angle theta
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @param[in] bWeak flag to control weak corrections (not including box diagrams)
     * @return the differential cross section d sigma(e^+ e^- -> l lbar)/d cosTheta in GeV^{-2}
     */
    double dsigma_l(const StandardModel::lepton l, 
                    const double s, const double cosTheta,
                    const double Mw, const double GammaZ, const bool bWeak) const;

    /**
     * @param[in] q name of a quark
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] cosTheta cosine of the scattering angle theta
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @param[in] bWeak flag to control weak corrections (not including box diagrams)
     * @return the differential cross section d sigma(e^+ e^- -> q qbar)/d cosTheta in GeV^{-2}
     */
    double dsigma_q(const StandardModel::quark q, 
                    const double s, const double cosTheta,
                    const double Mw, const double GammaZ, const bool bWeak) const;

    /**
     * @param[in] l name of a lepton
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] cosTheta cosine of the scattering angle theta
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @return the box contribution to the differential cross section d sigma(e^+ e^- -> l lbar)/d cosTheta in GeV^{-2}
     */
    double dsigma_l_box(const StandardModel::lepton l, 
                        const double s, const double cosTheta,
                        const double Mw, const double GammaZ) const;
      
    /**
     * @param[in] q name of a quark
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] cosTheta cosine of the scattering angle theta
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @return the box contribution to the differential cross section d sigma(e^+ e^- -> q qbar)/d cosTheta in GeV^{-2}
     */
    double dsigma_q_box(const StandardModel::quark q, 
                        const double s, const double cosTheta,
                        const double Mw, const double GammaZ) const;
    
    /**
     * @param[in] l name of a lepton
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @param[in] bWeak flag to control weak corrections (not including box diagrams)
     * @return the total cross section for e^+ e^- -> l lbar in GeV^{-2}
     */
    double sigma_l(const StandardModel::lepton l, const double s, 
                   const double Mw, const double GammaZ, const bool bWeak) const;
    
    /**
     * @param[in] q name of a quark
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @param[in] bWeak flag to control weak corrections (not including box diagrams)
     * @return the total cross section for e^+ e^- -> q qbar in GeV^{-2}
     */
    double sigma_q(const StandardModel::quark q, const double s, 
                   const double Mw, const double GammaZ, const bool bWeak) const;

    /**
     * @param[in] l name of a lepton
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @param[in] bWeak flag to control weak corrections (not including box diagrams)
     * @return the forward-backward asymmetry for e^+ e^- -> l lbar
     */
    double AFB_l(const StandardModel::lepton l, const double s, 
                 const double Mw, const double GammaZ, const bool bWeak) const;
    
    /**
     * @param[in] q name of a quark
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @param[in] bWeak flag to control weak corrections (not including box diagrams)
     * @return the forward-backward asymmetry for e^+ e^- -> q qbar
     */
    double AFB_q(const StandardModel::quark q, const double s, 
                 const double Mw, const double GammaZ, const bool bWeak) const;

    /**
     * @param[in] s the invariant mass squared of the initial-state e^+ e^- pair
     * @return the final-state QCD corrections to cross sections 
     */
    double QCD_FSR_forSigma(const double s) const;
    
    /**
     * @param[in] q name of a quark
     * @param[in] s the invariant mass squared of the initial-state e^+ e^- pair
     * @return the final-state QCD corrections to forward-backward asymmetries
     */
    double QCD_FSR_forAFB(const StandardModel::quark q, const double s) const;

    /**
     * @param[in] s the invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] Qf the electromagnetic charge of the final-state fermion
     * @return the final-state QED corrections to cross sections 
     */
    double QED_FSR_forSigma(const double s, const double Qf) const;
    
    /**
     * @param[in] x s'=(1-x)s
     * @param[in] s the invariant mass squared of the initial-state e^+ e^- pair
     * @return the additive radiator of initial-state radiations in cross sections
     */
    double H_ISR(const double x, const double s) const;

    /**
     * @param[in] x s'=(1-x)s
     * @param[in] s the invariant mass squared of the initial-state e^+ e^- pair
     * @return the additive radiator of initial-state radiations in forward-backward asysmmetries
     */
    double H_ISR_FB(const double x, const double s) const;

    /**
     * @param[in] l name of a lepton
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @param[in] bWeak flag to control weak corrections (not including box diagrams)
     * @return the form factor beta_f^2*G_3(s) for e^+ e^- -> l lbar
     */
    double G_3prime_l(const StandardModel::lepton l, const double s, 
                      const double Mw, const double GammaZ, 
                      const bool bWeak) const;
    
    /**
     * @param[in] q name of a quark
     * @param[in] s invariant mass squared of the initial-state e^+ e^- pair
     * @param[in] Mw the W-boson mass 
     * @param[in] GammaZ the Z-boson decay width
     * @param[in] bWeak flag to control weak corrections (not including box diagrams)
     * @return the form factor beta_f^2*G_3(s) for e^+ e^- -> q qbar
     */
    double G_3prime_q(const StandardModel::quark q, const double s, 
                      const double Mw, const double GammaZ, 
                      const bool bWeak) const;   

    
    ////////////////////////////////////////////////////////////////////////     
private:

    /**
     * @param s invariant mass squared
     * @return the electromagnetic coupling at s
     */
    double alpha_at_s(const double s) const;
    
    /**
     * @param[in] l name of lepton
     * @return mass of lepton
     */
    double ml(const StandardModel::lepton l) const;

    /**
     * @param[in] q name of quark
     * @param[in] mu renormalization scale
     * @param[in] order (=LO, NLO, NNLO, FULLNLO[defalut], FULLNNLO)
     * @return the MSbar mass of u, d, s, c, b or the pole mass of t
     */
    double mq(const StandardModel::quark q, const double mu, 
              const orders order=FULLNLO) const;

    double dsigma(const double s, const double cosTheta, 
                  const double Mw, const double GammaZ, 
                  const double I3f, const double Qf, const double mf,
                  const double mfp, const double Ncf, const bool bWeak) const;

    double dsigma_box(const double s, const double cosTheta, 
                      const double Mw, const double GammaZ, 
                      const double I3f, const double Qf, const double mf,
                      const double mfp, const double Ncf) const;
    
    double sigma(const double s, const double Mw, const double GammaZ, 
                 const double I3f, const double Qf, const double mf,
                 const double mfp, const double Ncf, const bool bWeak) const;
    
    double AFB(const double s, const double Mw, const double GammaZ, 
               const double I3f, const double Qf, const double mf,
               const double mfp, const bool bWeak) const;
    
};

#endif	/* LEP2TWOFERMIONS_H */

