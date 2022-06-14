/**
 * @file constexpr_change.hpp
 * @author Luiz Fernando F. G. Valle (luizfvalle@pm.me)
 * @brief Adds a function that constexprly (what?) solves the change-making
 *        problem.
 *
 * Uses dynamic programming with a bottom-up approach.
 *
 * @copyright Copyright (c) 2021-2022 Luiz Fernando F. G. Valle
 */

#ifndef CONSTEXPR_CHANGE_HPP
#define CONSTEXPR_CHANGE_HPP

#include <concepts>
#include <limits>
#include <ranges>
#include <vector>

/**
 * @brief Solves the change-making problem using dynamic programming with a
 * bottom-up approach.
 *
 * @tparam T Type of the target value.
 * @tparam Coins Type of the coins input range.
 * @param value Target value.
 * @param coins Available coin values.
 * @return Minimum number of coins needed to amount to the target value.
 */
template <std::integral T, std::ranges::input_range Coins>
auto constexpr Change(T const &value, Coins const &coins)
{
    using std::numeric_limits, std::vector;

    vector<T> tbl{0};
    tbl.resize(value + 1, numeric_limits<T>::max());

    for (T i{1}; i <= value; ++i)
        for (auto const &coin : coins)
            if (coin <= i && tbl[i - coin] + 1 < tbl[i])
                tbl[i] = tbl[i - coin] + 1;

    return tbl.back();
}

#endif // #ifndef CONSTEXPR_CHANGE_HPP
