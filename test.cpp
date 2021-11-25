#include "constexpr_change.hpp"

#include <array>
#include <iostream>

int main()
{
    // I believe the limit is implementation dependent. You might be able to
    //  change it using compiler args.
    constexpr int                value_as_cents{239};
    constexpr std::array<int, 4> coins{1, 5, 10, 25};

    std::cout << Change<int,            // Type of the value
                        value_as_cents, // Value
                        coins.size(),   // Number of different coins
                        coins,          // Coins
                        0               // This should always be zero
                        >()
              << std::endl;
}