//
// Created by felix on 10/23/16.
//

#ifndef THREAD_SAFE_COUT_H
#define THREAD_SAFE_COUT_H

#include <iostream>
#include <mutex>

namespace tp {
    std::mutex & get_cout_mutex() {
        static std::mutex m;
        return m;
    }
    
    std::ostream& print_one(std::ostream &os) {
        return os;
    }

    template<typename A0, typename ...Args>
    std::ostream& print_one(std::ostream &os, const A0 &a0, const Args &...args) {
        os << a0;
        return print_one(os, args...);
    }

    template<typename ...Args>
    std::ostream& ostream_print(std::ostream &os, const Args &...args) {
        return print_one(os, args...);
    }

    template<typename ...Args>
    std::ostream & print(const Args &...args) {
        std::lock_guard<std::mutex> _(get_cout_mutex());
        return ostream_print(std::cout, args...);
    }
}
#endif // THREAD_SAFE_COUT_H