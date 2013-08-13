//
//  ControlTriggeredSwitcher.cpp
//

#include "ControlTriggeredSwitcher.h"

namespace Tonic {

    namespace Tonic_{

        ControlTriggeredSwitcher_::ControlTriggeredSwitcher_():
            inputIndex_(ControlValue(0)),
            lastInputIndex_(-1),
            trigger(0) {
        }

        void ControlTriggeredSwitcher_::addInput(ControlGenerator input){
            inputs_.push_back(input);
        }

        void ControlTriggeredSwitcher_::setInputs(vector<ControlGenerator> inputs)
        {
            inputs_ = inputs;
        }

        void ControlTriggeredSwitcher_::setInputIndex(ControlGenerator inputIndexArg){
            inputIndex_ = inputIndexArg;
        }

    } // Namespace Tonic_

    ControlTriggeredSwitcher & ControlTriggeredSwitcher::setFloatInputs(vector<float> inputs){

        vector<ControlGenerator> newInputs;

        for(vector<float>::iterator it = inputs.begin(); it != inputs.end(); it++){
            newInputs.push_back(ControlValue(*it));
        }

        gen()->setInputs(newInputs);

        return *this;
    }

} // Namespace Tonic

