//
//  ControlRandomTrigger.h
//

//

#ifndef __TonicDemo__ControlRandomTrigger__
#define __TonicDemo__ControlRandomTrigger__

#include <iostream>
#include "ControlConditioner.h"

namespace Tonic{

    namespace Tonic_{

        class ControlRandomTrigger_ : public ControlGenerator_{
            void computeOutput(const SynthesisContext_ & context);

        public:

            ControlGenerator chance;
            ControlGenerator trigger;

            ControlRandomTrigger_();

            void setTrigger(ControlGenerator arg){trigger = arg;}
            void setChance(ControlGenerator arg){chance = arg;}
        };

        inline void ControlRandomTrigger_::computeOutput(const SynthesisContext_ & context) {
            ControlGeneratorOutput chanceOut = chance.tick(context);

            output_.triggered = false;
            if(trigger.tick(context).triggered) {
                float v = randomFloat(0.,1.);
                if (v < chanceOut.value) {
                    output_.triggered = true;
                    output_.value = 1;
                }
            }
        }

    }

    /*!
      May or may not output a 1 when triggered, depending on the value of chance.
     */

    class ControlRandomTrigger : public TemplatedControlGenerator<Tonic_::ControlRandomTrigger_>{
        public:
            createControlGeneratorSetters(ControlRandomTrigger, chance, setChance);
            createControlGeneratorSetters(ControlRandomTrigger, trigger, setTrigger);
    };

}


#endif /* defined(__TonicDemo__ControlRandomTrigger__) */

