/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

#include <iostream>
#include <string>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/deep_history.hpp>
#include <boost/statechart/shallow_history.hpp>


/**
 * Helpers
 * Makes it quick and easy to create entry and exit actions
 * -> constructor and destructor and have them write something to cout.
 *
 * Usage
 * struct Test
 * {
 *    PRINT_ENTRY_EXIT(0, Test)
 * };
 * 
 * Note the missing ;
 * param 1 - Is state inner level - denoted on printout with '*'
 * param 2 - Is the name of the class in question. No quotes!
 */
void print(unsigned int lvl, const std::string &name) {
    for (unsigned int i = 0; i < lvl; ++i)
        std::cout << "*";
    std::cout << " " << name << std::endl;
}

#define PRINT_ENTRY_EXIT(lvl, name)             \
  name() { print(lvl, #name"()"); }             \
  ~name() { print(lvl, "~"#name"()"); }


namespace sc = boost::statechart;


/**
 * Events that can be handled
 */
struct EvOn : sc::event<EvOn> {
};
struct EvOff : sc::event<EvOff> {
};

struct EvAMTuner : sc::event<EvAMTuner> {
};
struct EvFMTuner : sc::event<EvFMTuner> {
};
struct EvTuner : sc::event<EvTuner> {
};

struct EvCDState : sc::event<EvCDState> {
    EvCDState(bool validCd) : validCd(validCd) {}

    bool isValidCd() const {
        return validCd;
    }
private:
    bool validCd;
};

struct EvCD : sc::event<EvCD> {
};
struct EvCDInserted : sc::event<EvCDInserted> {
};
struct EvEject : sc::event<EvEject> {
};


/**
 * Machine definition and the top level states
 * forward declarations
 */

struct On;
struct Off;
struct Machine : sc::state_machine<Machine, Off> {
public:
    Machine() {
        cdIn_ = false;
    }

    bool isCdIn() const {
        return cdIn_;
    }

    void cdInserted() {
        cdIn_ = true;
    }

    bool cdIn_;
};


/**
 * Off
 */
struct Off : sc::simple_state<Off, Machine> {
    typedef sc::transition<EvOn, On> reactions;
    PRINT_ENTRY_EXIT(0, Off)
};


/**
 * 'On' and sub states
 * Forward declarations comes first...
 */
struct CDLoading;
struct CDPlaying;
struct RadioPlaying;

struct On : sc::simple_state<On, Machine, RadioPlaying> {
    typedef sc::transition<EvOff, Off> reactions;

    PRINT_ENTRY_EXIT(0, On)
};


/**
 * 'RadioPlaying' and sub states
 * Forward declarations comes first...
 */
struct FMTuner;
struct AMTuner;

struct RadioPlaying : sc::simple_state<RadioPlaying, On, FMTuner> {
    typedef boost::mpl::list<sc::transition<EvCDInserted, CDLoading>,
            sc::custom_reaction<EvCD>
    > reactions;

    PRINT_ENTRY_EXIT(1, RadioPlaying);

    sc::result react(const EvCD & event) {
        if (context<Machine>().isCdIn()) {
            return transit<CDPlaying>();
        } else {
            std::cout << "No CD is in the CD drive." << std::endl;
            discard_event();
        }
    }
};


/**
 * FMTuner
 */
struct FMTuner : sc::simple_state<FMTuner, RadioPlaying> {
    typedef sc::transition<EvAMTuner, AMTuner> reactions;
    PRINT_ENTRY_EXIT(2, FMTuner);
};


/**
 * AMTuner
 */
struct AMTuner : sc::simple_state<AMTuner, RadioPlaying> {
    typedef sc::transition<EvFMTuner, FMTuner> reactions;
    PRINT_ENTRY_EXIT(2, AMTuner);
};


/**
 * CDLoading
 */
struct CDLoading : sc::simple_state<CDLoading, On> {
    typedef boost::mpl::list<
            sc::custom_reaction<EvCDState>,
            sc::transition<EvEject, RadioPlaying>
    > reactions;

    PRINT_ENTRY_EXIT(1, CDLoading);

    sc::result react(const EvCDState & event) {
        std::cout << "CDLoading is loading:" << std::endl;
        if (event.isValidCd()) {
            context<Machine>().cdInserted();
            return transit<CDPlaying>();
        } else {
            return transit<RadioPlaying>();
        }
    }
};


/**
 * CDPlaying
 */
struct CDPlaying : sc::simple_state<CDPlaying, On> {
    typedef sc::transition<EvTuner, RadioPlaying> reactions;

    PRINT_ENTRY_EXIT(1, CDPlaying);
};


int main() {
    Machine myMachine;
    myMachine.initiate();

    myMachine.process_event(EvOn());
    myMachine.process_event(EvAMTuner());
    myMachine.process_event(EvCDInserted());
    myMachine.process_event(EvCDState(true));
    myMachine.process_event(EvTuner());
    myMachine.process_event(EvCD());

    myMachine.process_event(EvOff());
    myMachine.process_event(EvOn());
    myMachine.process_event(EvTuner());

    return 0;
}
