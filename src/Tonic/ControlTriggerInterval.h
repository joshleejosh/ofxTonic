//
//  ControlTriggerInterval.h
//

//

#ifndef __TonicDemo__ControlTriggerInterval__
#define __TonicDemo__ControlTriggerInterval__

#include <iostream>
#include "ControlConditioner.h"

namespace Tonic{

    namespace Tonic_{

        class ControlTriggerInterval_ : public ControlGenerator_{
            void computeOutput(const SynthesisContext_ & context);

        public:

            ControlGenerator interval;
            ControlGenerator trigger;
            int skips;

            ControlTriggerInterval_();

            void setTrigger(ControlGenerator arg){trigger = arg;}
            void setInterval(ControlGenerator arg){interval = arg;}
        };

        inline void ControlTriggerInterval_::computeOutput(const SynthesisContext_ & context){
            ControlGeneratorOutput intervalOut = interval.tick(context);

            output_.triggered = false;
            if(trigger.tick(context).triggered) {
                skips++;
                if (skips >= intervalOut.value) {
                    output_.triggered = true;
                    output_.value = 1;
                    skips = 0;
                }
            }
        }

    }

    /*!
      Outputs a 1 every X times it is triggered, where X is the value of interval.
     */

    class ControlTriggerInterval : public TemplatedControlGenerator<Tonic_::ControlTriggerInterval_>{
        public:
            createControlGeneratorSetters(ControlTriggerInterval, interval, setInterval);
            createControlGeneratorSetters(ControlTriggerInterval, trigger, setTrigger);
    };

}


#endif /* defined(__TonicDemo__ControlTriggerInterval__) */


