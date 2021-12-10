/**
 * @file constexpr_change.hpp
 * @author Luiz Fernando F. G. Valle (luizfvalle@pm.me)
 * @brief Implements templates that constexprly (what?) solve the change-making
 *        problem.
 *
 * Uses dynamic programming with a bottom-up approach.
 *
 * @copyright Copyright (c) 2021 Luiz Fernando F. G. Valle
 */

#ifndef CONSTEXPR_CHANGE_HPP
#define CONSTEXPR_CHANGE_HPP

#include <algorithm>        // std::min_element
#include <array>            // std::array (duh)
#include <concepts>         // std::integral
#include <cstddef>          // std::size_t
#include <initializer_list> // std::initializer_list (duh)
#include <limits>           // std::numeric_limits

/**
 * @brief Returns the smallest element of an initializer list.
 *
 * Wraps std::min_element.
 *
 * @tparam T The initializer list's value_type.
 * @param list The initializer list.
 * @return constexpr T Smallest element.
 */
template <typename T>
constexpr T Min(std::initializer_list<T> const &list)
{
    return *std::min_element(list.begin(), list.end());
}

/**
 * @brief Solves one subproblem of the change-making problem using previous
 * cached results.
 *
 * This function is not exaclty a fold, but naming is hard. It works by
 * recursively testing each coin value and then choosing the one which produces
 * the best result. The results are temporarily stored in the p parameter pack.
 *
 * I don't think a parameter pack is the ideal way of solving this but I haven't
 * tried another way yet.
 *
 * @tparam result_tbl Previous cached results.
 * @tparam coins Available coin values.
 * @tparam p Internal usage.
 * @return constexpr std::size_t
 */
template <std::array result_tbl, std::array coins, std::size_t... p>
constexpr std::size_t Fold_()
{
    // clang-format off

    if constexpr (sizeof...(p) == coins.size())
        // We have all possible solutions
        return Min({p...}); // Return the best one
    else
        // Let's calculate the next solution
        return Fold_<result_tbl,
                     coins,
                     p...,
                     // Adding the current solution to the parameter pack. We
                     // use the maximum representable value if the current coin
                     // is unusable.
                     result_tbl.size() >= coins[sizeof...(p)]
                       ? result_tbl[result_tbl.size() - coins[sizeof...(p)]] + 1
                       : std::numeric_limits<std::size_t>::max()>();

    // clang-format on
}

/**
 * @brief Solves the change-making problem using dynamic programming with a
 * bottom-up approach.
 *
 * Large target values may exceed the recursive template instantiation depth
 * limit of your compiler.
 *
 * @tparam value Target value.
 * @tparam coins Available coin values.
 * @tparam result_tbl Cached results of already solved subproblems.
 * @return constexpr std::size_t Minimum number of coins needed to amount to
 *         the target value.
 */
template <std::integral auto value, std::array coins, std::size_t... result_tbl>
constexpr std::size_t Change_()
{
    static_assert(
      std::is_same_v<decltype(value), typename decltype(coins)::value_type>,
      "value's type must be the same as coins' value_type");

    if constexpr (sizeof...(result_tbl) > value)
        // We solved all subproblems—the last of which is our original problem,
        // so we return its solution.
        return std::array<std::size_t, sizeof...(result_tbl)>{result_tbl...}
          .back();
    else
        // We still have subproblems to solve.
        // Recurse with the ideal solution to the current subproblem appended
        // to the cached results table.
        return Change_<
          value,
          coins,
          result_tbl...,
          Fold_<std::array<std::size_t, sizeof...(result_tbl)>{result_tbl...},
                coins>()>();
};

/**
 * @brief Calculates the minimum number of coins needed to amount to a value.
 *
 * Wraps around Change_.
 *
 * Large target values may exceed the recursive template instantiation depth
 * limit of your compiler.
 *
 * @tparam value Target value (e.g. 217).
 * @tparam coins Available coin values (e.g. {1, 5, 10, 25}).
 * @return constexpr std::size_t Minimum number of coins needed.
 */
template <std::integral auto value, std::array coins>
constexpr std::size_t Change()
{
    return Change_<value, coins, 0>();
}

#endif // #ifndef CONSTEXPR_CHANGE_HPP
