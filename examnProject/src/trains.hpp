//
// Created by felix on 10/17/16.
//

#ifndef CMS_TRAINS_H
#define CMS_TRAINS_H

#include <boost/mpl/list.hpp>
#include <boost/mpl/bool.hpp>
#include <iostream>
#include <list>
#include <boost/asio/detail/shared_ptr.hpp>
#include <algorithm>
#include <boost/variant/variant.hpp>
#include "cargo.hpp"

namespace cm {

    //Train instance creation will have the following syntax
    //static Train::Ptr&& Train::getInstance<Locomotive<Capacity>, CarriageList<Carriage<CargoList<Cargo...> >...> >();

    class Train {
    public:
        Train() {
            id++;
            ID = "Train " + id;
        }

        ~Train() {};

        Train(const Train &t) {};

        Train &operator=(const Train &t) {};

        Train(const Train &&t) {};

        Train &&operator=(const Train &&t) {};

        bool canHold(Cargo::Ptr);

        bool load(Cargo::Ptr);

        void unload(Cargo::Ptr);

        int getTotalWeight();

        int getCapacity();

    private:
        const int capacity = 0; //wont be zero. STUB
        std::string ID;
        static int id;
    };

    inline std::ostream &operator<<(std::ostream &out, Train &train) {
        out << "STUB TRAIN PRINT";
        return out;
    }

    /*********************************************************************
     **                ASSERTION structs for carriage                   **
     *********************************************************************/

    //First assertion is that all elements are Cargo classes
    //TODO: fix all elements are cargo
    /*
    template<bool, typename CL>
    struct ALL_ELEMENTS_ARE_CARGO;

    template<typename CL>
    struct ALL_ELEMENTS_ARE_CARGO<true, CL>{
        static const bool value = ALL_ELEMENTS_ARE_CARGO<
                IS_CARGO<typename CL::HEAD>::value,
                typename CL::TAIL>::value;
    };
    template<>
    struct ALL_ELEMENTS_ARE_CARGO<true, CL_NULL_ELEM>{
        static const bool value = true;
    };

    template<typename CL>
    struct ASSERT_IS_CARGO{
        static const bool value = ALL_ELEMENTS_ARE_CARGO<IS_CARGO<typename CL::HEAD>::value, typename CL::TAIL>::value;
    };
    */

    //Second assertion says that if any of the Cargo types are liquid Cargo types, all must be.
    template<bool, typename E, typename L>
    struct ALL_OR_NONE_ARE_LIQUID;
    template<typename E, typename L>
    struct ALL_OR_NONE_ARE_LIQUID<true, E, L> {
        static const bool value = ALL_OR_NONE_ARE_LIQUID<
                IS_LIQUID_CARGO<E>::value == IS_LIQUID_CARGO<typename L::HEAD>::value,
                typename L::HEAD, typename L::TAIL>::value;
    };
    template<typename E>
    struct ALL_OR_NONE_ARE_LIQUID<true, E, CL_NULL_ELEM> {
        static const bool value = IS_LIQUID_CARGO<E>::value;
    };
    template<typename CL>
    struct ASSERT_TANKER_VALIDITY {
        static const bool value = ALL_OR_NONE_ARE_LIQUID<true, typename CL::HEAD, typename CL::TAIL>::value;
    };

    //Third assertion says that one may not mix different kinds of livestock in one carriage
    //OBS: in the current implementation CARGO_LIST<Sheep, Sheep> is illegal.
    template<bool prevLivestock, bool currLivestock, typename REST>
    struct ONLY_ONE_KIND_OF_LIVESTOCK;
    //TODO: Use CL_AND_CONDITION again using nested templates.
    template<bool currLivestock, typename REST>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<false, currLivestock, REST> {
        static const bool hasLivestock = ONLY_ONE_KIND_OF_LIVESTOCK<
                currLivestock,
                IS_LIVESTOCK_CARGO<typename REST::HEAD>::value,
                typename REST::TAIL>::hasLivestock;
    };
    template<typename REST>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<true, false, REST> {
        static const bool hasLivestock = ONLY_ONE_KIND_OF_LIVESTOCK<
                true,
                IS_LIVESTOCK_CARGO<typename REST::HEAD>::value,
                typename REST::TAIL>::hasLivestock;
    };
    template<bool currLivestock>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<false, currLivestock, CL_NULL_ELEM> {
        static const bool hasLivestock = currLivestock;
    };
    template<>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<true, false, CL_NULL_ELEM> {
        static const bool hasLivestock = true;
    };

    template<typename CL>
    struct ASSERT_LIVESTOCK_VALIDITY {
        static const bool value = ONLY_ONE_KIND_OF_LIVESTOCK<
                false,
                IS_LIVESTOCK_CARGO<typename CL::HEAD>::value,
                typename CL::TAIL>::hasLivestock;
    };


    //Carriage validity class:
    //TODO: allow for empty carriages
    //this struct instantiates the different assertion structs, and thussly will only compile if they are fulfilled.
    template<typename CL>
    struct IS_A_VALID_CARGO_LIST {
        //typedef ASSERT_IS_CARGO<CL> ACCEPTS_CARGO;
        typedef ASSERT_TANKER_VALIDITY<CL> IS_TANKER;
        typedef ASSERT_LIVESTOCK_VALIDITY<CL> HAS_LIVESTOCK;
    };

    //TODO: add a details namespace to remove clutter
    //Carriage:
    template<int cap, typename CL>
    struct Carriage {
        typedef boost::mpl::bool_<true> IS_CARRIAGE;

        typedef IS_A_VALID_CARGO_LIST<CL> META_INFO;
        typedef CL CARGO_LIST;

        const bool isTanker = META_INFO::IS_TANKER::value;
        const bool hasLivestock = META_INFO::HAS_LIVESTOCK::value;

        static const int capacity = cap;

        Carriage() {}

        int getTotalWeight() const {
            int load = 0;
            std::for_each(cargo.begin(), cargo.end(), [&load](Cargo::Ptr c) { load += c->weight; });
        }

        bool canHold(Cargo::Ptr c) {
            if (getTotalWeight() + c->weight > capacity) return false;
            if (CL_RUNTIME_CONTAINS<CARGO_LIST>::value(c)) return true;
            return false;
        }

        bool load(Cargo::Ptr c) {
            if (canHold(c)) {
                cargo.push_back(c);
                return true;
            } else return false;

        }

        std::list<Cargo::Ptr> cargo;

    };

    //TODO: add constraints on CARGO_LIST in carriage and CARRIAGE_LIST in train.

    template<typename H, typename... REST>
    struct CARRIAGE_LIST {
        static_assert(IS_SAME_TYPE<typename H::IS_CARRIAGE, boost::mpl::bool_<true> >::value,
                      "CARRIAGE_LISTS may only contain carriages.");
        typedef H HEAD;
        typedef CARRIAGE_LIST<REST...> TAIL;
    };

    template<typename H>
    struct CARRIAGE_LIST<H> {
        static_assert(IS_SAME_TYPE<typename H::IS_CARRIAGE, boost::mpl::bool_<true> >::value,
                      "CARRIAGE_LISTS may only contain carriages.");
        typedef H HEAD;
        typedef CL_NULL_ELEM TAIL;
    };

    template<int cap>
    struct Locomotive {
        typedef boost::mpl::bool_<true> IS_LOCOMOTIVE;
        static const int capacity = cap;
    };

    template<typename CL>
    struct CAPACITY_SUM {
        static const int value = CL::HEAD::capacity + CAPACITY_SUM<typename CL::TAIL>::value;
    };

    template<>
    struct CAPACITY_SUM<CL_NULL_ELEM> {
        static const int value = 0;
    };

    /*
    template<typename CL>
    struct CARRIAGE_VARIANT_LIST {
        static std::list<MAKE_BOOST_VARIANT<CL>::VARIANT_TYPE> construct() {

        }
    };
    */

    /**********************************************************************************
     **                          carriage visitors                                   **
     **********************************************************************************/
    template<typename CL>
    struct CanHoldVisitor : public CanHoldVisitor<typename CL::TAIL> {
        CanHoldVisitor(Cargo::Ptr c) : cargo(c){};
        bool operator()(typename CL::HEAD e) const {
            return e.canHold(cargo);
        }
        Cargo::Ptr cargo;
    };

    template<>
    struct CanHoldVisitor<CL_NULL_ELEM> : public boost::static_visitor<bool> {
    };

    template<typename CL, typename T>
    struct CARRIAGE_LIST_INITIALIZER{
        static void initializeCarriageList(T cl){
            cl.push_back(typename CL::HEAD());
            CARRIAGE_LIST_INITIALIZER<typename CL::TAIL, T>::initializeCarriageList(cl);
        }
    };


    template<typename T>
    struct CARRIAGE_LIST_INITIALIZER<CL_NULL_ELEM, T>{
        static void initializeCarriageList(T cl){}
    };

    //template<template<int> typename Locomotive L, template<typename H, typename... REST> typename CARRIAGE_LIST CL>
    template<typename LOCOMOTIVE, typename CARRIAGE_L>
    struct TrainImpl {
        typedef typename MAKE_BOOST_VARIANT<CARRIAGE_L>::VARIANT_TYPE carriagevariant_t;
        typedef std::list<carriagevariant_t> carriagelist_t;
        static const int capacity = CAPACITY_SUM<CARRIAGE_L>::value;
        static_assert(LOCOMOTIVE::capacity >= capacity,
                      "The constructed train does not have a sufficiently strong locomotive to pull all it's carriages.");

        TrainImpl() : carriages() {
            CARRIAGE_LIST_INITIALIZER<CARRIAGE_L, carriagelist_t>::initializeCarriageList(carriages);
        };

        bool canHold(const Cargo::Ptr c) {
            bool ch = false;
            std::for_each(carriages.begin(),
                          carriages.end(),
                          [&c, &ch](carriagevariant_t cv) {
                              ch = ch || boost::apply_visitor(CanHoldVisitor<CARRIAGE_L>(c), cv);
                          });
            return ch;
        }

        carriagelist_t carriages;
    };




}
#endif //CMS_TRAINS_H
