/* 
 * Copyright (C) 2012-2014 SusyFit Collaboration
 * All rights reserved.
 *
 * For the licensing terms see doc/COPYING.
 */

#ifndef MODEL_H
#define	MODEL_H

#include <map>

/**
 * @class Model
 * @ingroup StandardModel
 * @brief A class for the template of models. 
 * @author SusyFit Collaboration
 * @copyright GNU General Public License
 * @details This template delineates the methods necessary for the construction
 * and updating of a particular model. An example of its use can be found in the
 * StandardModel class.
 */
class Model {
public:
    
    /**
     * @brief The default constructor.
     */
    Model(){
        ModelInitialized = false; 
    };
    
    /**
     * @brief The update method for the model class.
     * @details This method updates all the parameters of the model every time a
     * new set of parameter is generated.
     * @param[in] Dpar a map of parameters that are being updated in the Monte Carlo run
     * (including parameters that are varied and those that are held constant)
     * @return a boolean that is true if the execution is successful
     */
    virtual bool Update(const std::map<std::string, double>& Dpar) = 0;
    
    /**
     * @brief The pre-update method for the model class.
     * @details This method checks if all requisites for the update process of the
     * current model has been completed. Such requisites can be procedures like update
     * of other models or any other procedures that need to be done before the current 
     * model can be successfully updated.
     * @return a boolean that is true if the execution is successful
     */
    virtual bool PreUpdate() = 0;
    
    /**
     * @brief The post-update method for the model class.
     * @details This method runs all the procedures that are need to be executed
     * after the model is successfully updated. This includes updating
     * any other variable that needs to be updated at this time due to the update
     * of the model parameters
     * @return a boolean that is true if the execution is successful
     */
    virtual bool PostUpdate() = 0;
    
    /**
     * @brief A method to check if all the mandatory parameters for the model have
     * been provided in the SomeModel.conf file.
     * @param[in] Dpar a map of parameters that are being updated in the Monte Carlo run
     * (including parameters that are varied and those that are held constant)
     * @return a boolean that is true if the execution is successful
     */
    virtual bool CheckParameters(const std::map<std::string, double>& Dpar) = 0;
    
    /**
     * @brief A method to set a flag of the model.
     * @param[in] name name of a flag
     * @param[in] value the boolean to be assigned to the flag specified by name
     * @return a boolean that is true if the execution is successful
     */
    virtual bool setFlag(const std::string name, const bool value) = 0;

    /**
     * @brief A method to set a flag of the model.
     * @param[in] name name of a flag
     * @param[in] value the string to be assigned to the flag specified by name
     * @return a boolean that is true if the execution is successful
     */
    virtual bool setFlagStr(const std::string name, const std::string value) = 0;
    
    /**
     * @brief A method to check the sanity of the set of flags.
     * @return true if the set of flags is sane
     */
    virtual bool CheckFlags() const = 0;
    
    /**
     * @brief A method to set the value of a parameter in the model.
     * @param[in] name name of a parameter
     * @param[in] value the value to be assigned to the parameter specified by name
     */
    virtual void setParameter(const std::string name, const double& value) = 0;
    
    /**
     * @brief A method to initialize the model. 
     * @param[in] Dpars a map of parameters that are being updated in the Monte Carlo run
     * @return a boolean that is true if the execution is successful
     */
    virtual bool Init(const std::map<std::string, double>& Dpars) = 0;
    
    /**
     * @brief A method to fetch the name of the model. 
     * @return the name of the model as a string
     */
    virtual std::string ModelName() const = 0;
    
    /**
     * @brief A method to check if the model is initialized.
     * @return true if the model has been initialized
     */
    bool IsModelInitialized() const
    {
        return ModelInitialized;
    }
    
    /**
     * @brief A set method to fix the failure or success of the initialization of a model.
     * @param[in] ModelInitialized true if the model has been successfully initialized
     * @return true if the model has been successfully initialized
     */
    void setModelInitialized(bool ModelInitialized)
    {
        this->ModelInitialized = ModelInitialized;
    }
    
    /**
     * @brief A method to check if there was any error in the model update process.
     * @return false if the update was successful
     */
    bool IsUpdateError() const
    {
        return UpdateError;
    }
    
    /**
     * @brief A set method to fix the update status as success or failure
     * @param[in] UpdateError gives true if update is not successful
     */
    void setUpdateError(bool UpdateError)
    {
        this->UpdateError = UpdateError;
    }
    
    
protected:
    
    bool UpdateError; ///< A boolean set to false if update is successful.
    
private:

    bool ModelInitialized; ///< A boolean set to true if the model is successfully initialized.
    
};

#endif	/* MODEL_H */

