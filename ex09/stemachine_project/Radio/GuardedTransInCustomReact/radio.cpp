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

/* Missing code */
struct EvCDState : sc::event<EvCDState> {
    EvCDState(bool valid) : valid_(valid) {}

    bool valid_;
};

struct EvCD : sc::event<EvCD> {
};
struct EvCDInserted : sc::event<EvCDInserted> {
};
struct EvEject : sc::event<EvEject> {
};


/**
 * Radio definition and the top level states
 * forward declarations
 */

struct On;
struct Off;
struct Radio : sc::state_machine<Radio, Off> {
};


/**
 * Off
 */
struct Off : sc::simple_state<Off, Radio> {
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

struct On : sc::simple_state<On, Radio, RadioPlaying> {
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
            sc::transition<EvCD, CDPlaying>
    > reactions;

    PRINT_ENTRY_EXIT(1, RadioPlaying);
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
    /* Missing code */
    typedef boost::mpl::list<sc::custom_reaction<EvCDState>,
            sc::transition<EvEject, RadioPlaying> > reactions;

    PRINT_ENTRY_EXIT(1, CDLoading);

    /* Missing code */
    sc::result react(const EvCDState& ev)
    {
        if (ev.valid_) return transit<CDPlaying>();
        else return transit<RadioPlaying>(); 
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
    Radio myRadio;
    myRadio.initiate();

    myRadio.process_event(EvOn());
    myRadio.process_event(EvAMTuner());
    myRadio.process_event(EvCDInserted());
    myRadio.process_event(EvCDState(true));
    myRadio.process_event(EvTuner());
    myRadio.process_event(EvCD());

    myRadio.process_event(EvOff());
    myRadio.process_event(EvOn());
    myRadio.process_event(EvTuner());
    myRadio.process_event(EvOff());
    return 0;
}
