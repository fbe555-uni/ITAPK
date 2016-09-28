#include <iostream>
#include <vector>
#include "boost/variant.hpp"
class Profanity{
public:
    Profanity(){
        srand((unsigned int) time(NULL));
        int r;
        //random index number between 0 and 19
        do{r = rand() % 100/5;
        //std::cout << r << std::endl; check to determine index number
        }
        while(r > profanityList_.size()-1);
        profanity_ = profanityList_[r];
    }

    std::string get_profanity() const{
            return profanity_;
    };


private:
    std::vector<std::string> profanityList_ = {"RØV!", "LORT!", "PIS!", "SATAN!","PISRØV!",
                                             "FORBANDEDE LORTE RØV!","RØVPULELORT!","PIK!","LORTEPIK!",
                                             "Av for Søren (Hansen)!"};
    std::string profanity_;
};

std::ostream& operator<<(std::ostream& os, const Profanity& profanity){
    os << profanity.get_profanity();
    return os;
}

class my_visitor : public boost::static_visitor<std::string>
{
public:
    std::string operator()(int & i) const
    {
        return std::string("the integer ") + std::to_string(i) + std::string(" has been accessed");
    }

    std::string operator()(Profanity & p) const
    {
        return std::string("the profanity ") + p.get_profanity() + std::string(" has been accessed");
    }

    std::string operator()(double & d) const
    {
        return std:: string("the double ") + std::to_string(d) + std::string(" has been accessed");
    }

};

int main() {
    boost::variant<int, Profanity, double> u = 20.2;
    std::cout << u << std::endl; //profanity print.
    u.which();

    std::string res = boost::apply_visitor( my_visitor(), u);
    std::cout << res;
}
