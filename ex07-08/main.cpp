#include <iostream>

template < size_t N>
struct Binary
{
    static_assert(N >= 10, "The binary struct can be used only on values consisting of ones and zeros.");
    static const size_t value = Binary<N/10 >::value << 1 | Binary<N%10>::value;
};

template <>
struct Binary <0>
{
    static const size_t value = 0;
};

template <>
struct Binary <1>
{
    static const size_t value = 1;
};

/*
template < size_t N>
struct Binary
{
static_assert(N%10 < 2, "The binary struct can be used only on values consisting of ones and zeros.");
static const size_t value = Binary <N/10 >:: value << 1 | N%10;
};
template <>
struct Binary <0>
{
static const size_t value = 0;
};
*/

int main() {
    std::cout << "Binary <1011 >:: value = " << Binary <1011>:: value << std :: endl;
    /* Should generate a compiler error , but does not! */
    return 0;
}