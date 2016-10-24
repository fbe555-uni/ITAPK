//
// Created by felix on 10/17/16.
//

#ifndef CMS_CARGO_H
#define CMS_CARGO_H

#include <ratio>
#include <iostream>
#include <typeinfo>
#include <string.h>

#ifndef LOAD_SPEED_MULTIPLIER
#define LOAD_SPEED_MULTIPLIER 1
#endif
namespace cm{

    //Constants
    const double BASE_LOAD_FACTOR = 1/LOAD_SPEED_MULTIPLIER;
    const double LIQUID_LOAD_FACTOR = 0.5/LOAD_SPEED_MULTIPLIER;
    const double LIVESTOCK_LOAD_FACTOR = 2/LOAD_SPEED_MULTIPLIER;

    //Cargo struct
    class Cargo{
    public:
        typedef boost::mpl::bool_<false> IS_LIQUID;
        typedef boost::mpl::bool_<false> IS_LIVESTOCK;
        typedef std::shared_ptr<Cargo> Ptr;
        Cargo(int w, double lt) : weight(w), loadTime(lt)
        {
        }

        virtual ~Cargo(){}

        const int weight;
        const double loadTime;
    };

    class Timber : public Cargo{
    public:
        Timber(int w): Cargo(w, BASE_LOAD_FACTOR*w){}
        ~Timber(){};
    };

    class Coal : public Cargo{
    public:
        Coal(int w): Cargo(w, BASE_LOAD_FACTOR*w){}
        ~Coal(){};
    };

    class Grains : public Cargo{
    public:
        Grains(int w): Cargo(w, BASE_LOAD_FACTOR*w){}
        ~Grains(){};
    };

    class Oil : public Cargo{
    public:
        typedef boost::mpl::bool_<true> IS_LIQUID;
        Oil(int w): Cargo(w, LIQUID_LOAD_FACTOR*w){}
        ~Oil(){};
    };

    class Gasoline: public Cargo{
    public:
        typedef boost::mpl::bool_<true> IS_LIQUID;
        Gasoline(int w): Cargo(w, LIQUID_LOAD_FACTOR*w){}
        ~Gasoline(){};
    };

    class Water: public Cargo{
    public:
        typedef boost::mpl::bool_<true> IS_LIQUID;
        Water(int w): Cargo(w, LIQUID_LOAD_FACTOR*w){}
        ~Water(){};
    };

    class Sheep : public Cargo{
    public:
        typedef boost::mpl::bool_<true> IS_LIVESTOCK;
        Sheep(int w): Cargo(w, LIVESTOCK_LOAD_FACTOR*w){}
        ~Sheep(){};
    };

    class Cows : public Cargo{
    public:
        typedef boost::mpl::bool_<true> IS_LIVESTOCK;
        Cows(int w): Cargo(w, LIVESTOCK_LOAD_FACTOR*w){}
        ~Cows(){};
    };

    class Pigs : public Cargo{
    public:
        typedef boost::mpl::bool_<true> IS_LIVESTOCK;
        Pigs(int w): Cargo(w, LIVESTOCK_LOAD_FACTOR*w){}
        ~Pigs(){};
    };

    inline std::ostream& operator<<(std::ostream& out, Cargo const* cargo){
        out << cargo->weight << " kg of " << typeid(*cargo).name();
        out << " (" << cargo->loadTime << "s needed for loading)";
        return out;
    }

    /*******************************************************************
     **             TMP EVALUATION/CONDITION STRUCTS                  **
     *******************************************************************/
    template <typename CT>
    struct IS_LIQUID_CARGO{
        static const bool value = CT::IS_LIQUID::value;
    };

    template <typename CT>
    struct IS_LIVESTOCK_CARGO{
        static const bool value = CT::IS_LIVESTOCK::value;
    };

    // is same type tmp boolean
    template<typename T, typename U>
    struct IS_SAME_TYPE{
        static const bool value = false;
    };

    template<typename T>
    struct IS_SAME_TYPE<T, T>{
        static const bool value = true;
    };

    template<typename T>
    struct IS_CARGO{
        static const bool value = std::is_base_of<Cargo, T>::value;
    };

    /*******************************************************************
     **                    TMP CARGOLIST STRUCTS                      **
     *******************************************************************/
    struct CL_NULL_ELEM{};

    template<typename H, typename... REST>
    struct CARGO_LIST{
        static_assert(IS_CARGO<H>::value, "CARGO_LISTS may only contain subclasses of cargo.");
        typedef H HEAD;
        typedef CARGO_LIST<REST...> TAIL;
    };

    template<typename H>
    struct CARGO_LIST<H>{
        static_assert(IS_CARGO<H>::value, "CARGO_LISTS may only contain subclasses of cargo.");
        typedef H HEAD;
        typedef CL_NULL_ELEM TAIL;
    };

    /*
    template<typename... CARGO_TYPES>
    struct Cargo_LIST{
        typedef CARGO_LIST<
    };

    template<typename first, typename ... rest>
    struct CARGO_LIST{
        typedef CL<first, CARGO_LIST<rest...>::LIST > LIST;
    };
     */

    /*******************************************************************
     **                      Cargolist utilities                      **
     *******************************************************************/

    template<typename CL, typename T>
    struct CL_CONTAINS{
        static const bool value = IS_SAME_TYPE<typename CL::LIST::HEAD, T>::value || CL_CONTAINS<typename CL::LIST::TAIL, T>::value;
    };

    template<typename T>
    struct CL_CONTAINS<CL_NULL_ELEM, T>{
        static const bool value = false;
    };

    template<typename CL>
    struct CL_NUM_ELEMS{
        static const int value = 1 + CL_NUM_ELEMS<typename CL::TAIL>::value;
    };

    template<>
    struct CL_NUM_ELEMS<CL_NULL_ELEM>{
        static const int value = 0;
    };

    //TODO: how about out of bounds?
    template<typename CL, int index>
    struct CL_GET_ELEM{
        typedef typename CL_GET_ELEM<typename CL::TAIL, index-1>::TYPE TYPE;
    };

    template<typename CL>
    struct CL_GET_ELEM<CL, 0>{
        typedef typename CL::HEAD TYPE;
    };

    template<typename CL>
    class CL_RUNTIME_CONTAINS{
    public:
        template<typename T>
        inline static bool value(std::shared_ptr<T>& c){
            //std::cout << typeid(*c).name() << " " << typeid(typename CL::HEAD()).name()<< std::endl;;
            Cargo* c_ptr = c.get();
            typename CL::HEAD* other_ptr = dynamic_cast<typename CL::HEAD*>(c.get());
            if(dynamic_cast<typename CL::HEAD*>(c.get())){
                //std::cout << "returned true" << std::endl;
                return true;
            }
            else {
                //std::cout << "returned false" << std::endl;
                return CL_RUNTIME_CONTAINS<typename CL::TAIL>::value(c);
            }
        }
    };

    template <>
    class CL_RUNTIME_CONTAINS<CL_NULL_ELEM>{
    public:
        template<typename T>
        inline static bool value(std::shared_ptr<T>& c){
            return false;
        }
    };

    template<typename CL, typename... EXPANDED>
    struct MAKE_BOOST_VARIANT{
        typedef typename MAKE_BOOST_VARIANT<typename CL::TAIL, typename CL::HEAD, EXPANDED...>::VARIANT_TYPE VARIANT_TYPE;
    };

    template<typename... EXPANDED>
    struct MAKE_BOOST_VARIANT<CL_NULL_ELEM, EXPANDED...>{
        typedef boost::variant<EXPANDED...> VARIANT_TYPE;
    };


};
#endif //CMS_CARGO_H
