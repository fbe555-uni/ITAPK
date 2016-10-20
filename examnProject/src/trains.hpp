//
// Created by felix on 10/17/16.
//

#ifndef CMS_TRAINS_H
#define CMS_TRAINS_H

#include <boost/shared_ptr.hpp>
#include <boost/mpl/list.hpp>
#include <iostream>
#include "cargo.hpp"

namespace cm{


    class Train{
    public:
        Train(){
            num_id++;
            ID = "Train " + std::to_string(num_id);
        }
        std::string getID() const{
            return ID;
        }
        //STUB

        typedef std::shared_ptr<cm::Train> Ptr;
    private:
        std::string ID;
        static int num_id;
    };

    inline std::ostream& operator<<(std::ostream& out, Train& train){
        out << train.getID();
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
    struct ALL_OR_NONE_ARE_LIQUID<true, E, L>{
        static const bool value = ALL_OR_NONE_ARE_LIQUID<
                IS_LIQUID_CARGO<E>::value == IS_LIQUID_CARGO<typename L::HEAD>::value,
                typename L::HEAD, typename L::TAIL>::value;
    };
    template<typename E>
    struct ALL_OR_NONE_ARE_LIQUID<true, E, CL_NULL_ELEM>{
        static const bool value = IS_LIQUID_CARGO<E>::value;
    };
    template<typename CL>
    struct ASSERT_TANKER_VALIDITY{
        static const bool value = ALL_OR_NONE_ARE_LIQUID<true, typename CL::HEAD, typename CL::TAIL>::value;
    };

    //Third assertion says that one may not mix different kinds of livestock in one carriage
    //OBS: in the current implementation CARGO_LIST<Sheep, Sheep> is illegal.
    template<bool prevLivestock, bool currLivestock, typename REST>
    struct ONLY_ONE_KIND_OF_LIVESTOCK;

    template<bool currLivestock, typename REST>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<false, currLivestock, REST>{
        static const bool hasLivestock = ONLY_ONE_KIND_OF_LIVESTOCK<
                currLivestock,
                IS_LIVESTOCK_CARGO<typename REST::HEAD>::value,
                typename REST::TAIL>::hasLivestock;
    };
    template<typename REST>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<true, false, REST>{
        static const bool hasLivestock = ONLY_ONE_KIND_OF_LIVESTOCK<
                true,
                IS_LIVESTOCK_CARGO<typename REST::HEAD>::value,
                typename REST::TAIL>::hasLivestock;
    };
    template<bool currLivestock>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<false, currLivestock, CL_NULL_ELEM>{
        static const bool hasLivestock = currLivestock;
    };
    template<>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<true, false, CL_NULL_ELEM>{
        static const bool hasLivestock = true;
    };

    template<typename CL>
    struct ASSERT_LIVESTOCK_VALIDITY{
        static const bool value = ONLY_ONE_KIND_OF_LIVESTOCK<
                false,
                IS_LIVESTOCK_CARGO<typename CL::HEAD>::value,
                typename CL::TAIL>::hasLivestock;
    };


    //Carriage validity class:
    //TODO: allow for empty carriages
    //this struct instantiates the different assertion structs, and thussly will only compile if they are fulfilled.
    template<typename CL>
    struct IS_A_VALID_CARGO_LIST{
        //typedef ASSERT_IS_CARGO<CL> ACCEPTS_CARGO;
        typedef ASSERT_TANKER_VALIDITY<CL> IS_TANKER;
        typedef ASSERT_LIVESTOCK_VALIDITY<CL> HAS_LIVESTOCK;
    };

    //TODO: add a details namespace to remove clutter
    //Carriage:
    template<typename CL>
    struct Carriage{
        typedef IS_A_VALID_CARGO_LIST<CL> META_INFO;

        //const bool acceptsCargo = META_INFO::ACCEPTS_CARGO::value;
        const bool isTanker = META_INFO::IS_TANKER::value;
        const bool hasLivestock = META_INFO::HAS_LIVESTOCK::value;

        Carriage(){}
    };
}

#endif //CMS_TRAINS_H
