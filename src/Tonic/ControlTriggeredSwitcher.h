//
//  ControlTriggeredSwitcher.h
//


#ifndef __Tonic__ControlTriggeredSwitcher__
#define __Tonic__ControlTriggeredSwitcher__

#include "ControlGenerator.h"

namespace Tonic {

    namespace Tonic_ {

        class ControlTriggeredSwitcher_ : public ControlGenerator_{

            protected:
                void computeOutput(const SynthesisContext_ & context);

                vector<ControlGenerator>  inputs_;
                ControlGenerator          inputIndex_;
                ControlGenerator          trigger;

                int                       lastInputIndex_;

            public:

                ControlTriggeredSwitcher_();
                void addInput(ControlGenerator input);
                void setInputs( vector<ControlGenerator> inputs );
                void setInputIndex(ControlGenerator inputIndexArg);
                void setTrigger(ControlGenerator arg) { trigger = arg; }

        };

        inline void ControlTriggeredSwitcher_::computeOutput(const SynthesisContext_ & context){

            for(vector<ControlGenerator>::iterator it = inputs_.begin(); it != inputs_.end(); it++){
                it->tick(context);
            }

            ControlGeneratorOutput indexOutput = inputIndex_.tick(context);
            int index = indexOutput.value;

            // ONLY send has-changed message when explicitly triggered AND the value has changed.
            if (trigger.tick(context).triggered && index != lastInputIndex_) {
                lastInputIndex_ = index;
                ControlGeneratorOutput output = inputs_.at(clamp(index, 0, inputs_.size() -1 )).tick(context);
                output_.triggered = true;
                output_.value = output.value;
            }else{
                output_.triggered = false;
            }
        }

    }

    /*!
      ControlTriggeredSwitcher allows you to switch between an unlimited number of inputs (added via addInput).
      Unlike regular ControlSwitcher, it only switches values when triggered.
      The "active" input is controlled by the value of inputIndex.
     */

    class ControlTriggeredSwitcher : public TemplatedControlGenerator<Tonic_::ControlTriggeredSwitcher_>{

        public:

            ControlTriggeredSwitcher & setFloatInputs( vector<float> inputs );

            createControlGeneratorSetters(ControlTriggeredSwitcher, addInput, addInput);
            createControlGeneratorSetters(ControlTriggeredSwitcher, inputIndex, setInputIndex);
            createControlGeneratorSetters(ControlTriggeredSwitcher, trigger, setTrigger);

    };
}

#endif /* defined(__Tonic__ControlTriggeredSwitcher__) */



