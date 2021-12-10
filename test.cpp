#include "constexpr_change.hpp"

#include <array>
#include <iostream>

int main()
{
    constexpr int        value_as_cents{239};
    constexpr std::array coins{1, 5, 10, 25};

    std::cout << Change<value_as_cents, coins>() << std::endl;
}