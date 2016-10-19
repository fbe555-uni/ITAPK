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
            ID = "Train " + num_id;
        }
        std::string getID() const{
            return ID;
        }
        //STUB

        typedef std::unique_ptr<cm::Train> Ptr;
    private:
        std::string ID;
        static int num_id;
    };

    inline std::ostream& operator<<(std::ostream& out, Train& train){
        out << "STUB TRAIN PRINT";
        return out;
    }

/*
    //Carriage validity classes:
    //this struct instantiates the different assertion structs, and thussly will only compile if they are fulfilled.
    template<typename CL>
    struct IS_A_VALID_CARGO_LIST{
        typedef ASSERT_IS_CARGO<CL> IS_CARGO;
        typedef ASSERT_TANKER_VALIDITY<CL> IS_TANKER;
        typedef ASSERT_LIVESTOCK_VALIDITY<CL> HAS_LIVESTOCK;
    };

    //First assertion is that all elements are Cargo classes
    template<typename CL>
    struct ASSERT_IS_CARGO<CL>{
        typedef ALL_ELEMENTS_ARE_CARGO<CL_AND_CONDITION<CL, IS_CARGO> > VALID;
        static const value = true;
    };
    //struct used for error msg name
    template<>
    struct ALL_ELEMENTS_ARE_CARGO<true>{};

    //Second assertion says that if any of the Cargo types are liquid Cargo types, all must be.
    template<typename CL>
    struct ASSERT_TANKER_VALIDITY{
        typedef CL_OR_CONDITION<CL, IS_LIQUID_CARGO> HAS_LIQUID;
        typedef ALL_OR_NONE_ARE_LIQUID<CL_AND_CONDITION<CL, IS_LIQUID_CARGO>::value || HAS_LIQUID::value> VALLID;
        static const bool value = HAS_LIQUID::value;
    };
    template<>
    struct ALL_OR_NONE_ARE_LIQUID<true>{};

    //Third assertion says that one may not mix different kinds of livestock in one carriage
    //OBS: in the current implementation CARGO_LIST<Sheep, Sheep> is illegal.
    template<typename CARGO_LIST>
    struct ASSERT_LIVESTOCK_VALIDITY{
        static const bool value = ONLY_ONE_KIND_OF_LIVESTOCK<false, IS_LIVESTOCK_CARGO<CARGO_LIST::LIST::HEAD>::value, CARGO_LIST::LIST::TAIL>::hasLivestock;
    };

    template<bool currIsLivestock, typename CL>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<false, currIsLivestock, CL>{
        static const bool hasLivestock = ONLY_ONE_KIND_OF_LIVESTOCK<currIsLivestock, IS_LIVESTOCK_CARGO<CL::HEAD>::value, CL::TAIL>::hasLivestock;
    };

    template<bool currIsLivestock, typename CL>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<true, false, CL>{
        static const bool hasLivestock = ONLY_ONE_KIND_OF_LIVESTOCK<true, IS_LIVESTOCK_CARGO<CL::HEAD>::value, CL::TAIL>::hasLivestock;
    };

    template<bool currIsLivestock, CL_NULL_ELEM end>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<false, currIsLivestock, end>{
        static const bool hasLivestock = currIsLivestock;
    };

    template<CL_NULL_ELEM end>
    struct ONLY_ONE_KIND_OF_LIVESTOCK<true, false, end>{
        static const bool hasLivestock = true;
    };

    //TODO: add a details namespace to remove clutter
    //Carriage:
    template<CargoType ct, boost::mpl::list L>
    IS_VALID_TANKER_CARRIAGE<ct,
    template<boost::mpl::list>

    struct Train{

    };
*/
}

#endif //CMS_TRAINS_H
