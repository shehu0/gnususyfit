/* 
 * Copyright (C) 2013 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef NPEFFECTIVE_H
#define	NPEFFECTIVE_H

#include <stdexcept>
#include <StandardModel.h>

/**
 * @class NPEffective
 * @brief A base class for new physics with the effective Lagrangian approach.
 * @ingroup NewPhysics
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details  
 */
class NPEffective : public StandardModel {
public:

    /**
     * @brief NPEffective constructor. 
     */
    NPEffective();

    virtual bool Update(const std::map<std::string, double>& DPars);
    virtual bool Init(const std::map<std::string, double>& DPars);    

    virtual bool InitializeModel();  
    virtual void SetEWSMflags(EWSM& myEWSM);    

    virtual bool SetFlag(const std::string, const bool&); 


    ////////////////////////////////////////////////////////////////////////

    double getCHL1p() const {
        return cHL1p;
    }

    double getCHL2p() const {
        return cHL2p;
    }
    double getCHL3p() const {
        return cHL3p;
    }

    double getCHL1() const {
        return cHL1;
    }

    double getCHL2() const {
        return cHL2;
    }

    double getCHL3() const {
        return cHL3;
    }

    double getCHQ1p() const
    {
        return cHQ1p;
    }

    double getCHQ2p() const
    {
        return cHQ2p;
    }

    double getCHQ3p() const
    {
        return cHQ3p;
    }

    double getCHQ1() const
    {
        return cHQ1;
    }

    double getCHQ2() const
    {
        return cHQ2;
    }

    double getCHQ3() const
    {
        return cHQ3;
    }

    double getCHE1() const {
        return cHE1;
    }

    double getCHE2() const {
        return cHE2;
    }

    double getCHE3() const {
        return cHE3;
    }
    
    double getCHU2() const {
        return cHU2;
    }

    double getCHD3() const {
        return cHD3;
    }

    double getLambdaNP() const
    {
        return LambdaNP;
    }


    ////////////////////////////////////////////////////////////////////////

    virtual double v() const;

    virtual double Mw_tree() const;

    virtual double DeltaGF() const;


    ////////////////////////////////////////////////////////////////////////     

    /**
     * @return Oblique parameter S.
     */
    virtual double obliqueS() const;

    /**
     * @return Oblique parameter T.
     */
    virtual double obliqueT() const;

    /**
     * @return Oblique parameter U.
     */
    virtual double obliqueU() const;


    ////////////////////////////////////////////////////////////////////////    

    double deltaGLl(StandardModel::lepton l) const;

    double deltaGLq(StandardModel::quark q) const;
    
    double deltaGRl(StandardModel::lepton l) const;

    double deltaGRq(StandardModel::quark q) const;

    virtual double deltaGVl(StandardModel::lepton l) const;
    
    virtual double deltaGVq(StandardModel::quark q) const;
    
    virtual double deltaGAl(StandardModel::lepton l) const;
    
    virtual double deltaGAq(StandardModel::quark q) const;


    ////////////////////////////////////////////////////////////////////////

    virtual double epsilon1() const;

    virtual double epsilon2() const;

    virtual double epsilon3() const;

    virtual double epsilonb() const;


    ////////////////////////////////////////////////////////////////////////

    /**
     * @return The W boson mass.
     */
    virtual double Mw() const;

    /**
     * @return @f$M_W^2/M_Z^2@f$.
     */
    virtual double cW2() const;

    /**
     * @return @f$1-M_W^2/M_Z^2@f$.
     */
    virtual double sW2() const;

    /**
     * @return The total width of the W boson.
     */
    virtual double GammaW() const;
    
    
    ////////////////////////////////////////////////////////////////////////    

protected:
    double cWB, cH;
    double cL1L1, cL1L2, cL1L3, cL2L2, cL2L3, cL3L3;
    double cHL1p, cHL2p, cHL3p;
    double cHQ1p, cHQ2p, cHQ3p;
    double cHL1, cHL2, cHL3;
    double cHQ1, cHQ2, cHQ3;
    double cHE1, cHE2, cHE3;
    double cHU1, cHU2, cHU3;
    double cHD1, cHD2, cHD3;
    double LambdaNP;
    

    ////////////////////////////////////////////////////////////////////////   

private:

};

#endif	/* NPEFFECTIVE_H */

