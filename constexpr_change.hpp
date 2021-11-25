#ifndef CONSTEXPR_CHANGE_HPP
#define CONSTEXPR_CHANGE_HPP

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <limits>

template <typename T>
constexpr T Min(std::initializer_list<T> const &arr)
{
    return *std::min_element(arr.begin(), arr.end());
}

template <std::size_t                              prev_mins_count,
          std::array<std::size_t, prev_mins_count> prev_mins,
          std::integral                            CoinT,
          std::size_t                              coin_count,
          std::array<CoinT, coin_count>            coins,
          std::size_t... mins>
constexpr std::size_t Fold()
{
    if constexpr (sizeof...(mins) == coin_count)
        return Min({mins...});
    else
        return Fold < prev_mins_count, prev_mins, CoinT, coin_count, coins,
               mins...,
               prev_mins_count >= coins[sizeof...(mins)]
                 ? prev_mins[prev_mins_count - coins[sizeof...(mins)]] + 1
                 : std::numeric_limits<std::size_t>::max() > ();
}

template <std::integral                   ValueT,
          ValueT                          value,
          std::size_t                     coins_count,
          std::array<ValueT, coins_count> coins,
          std::size_t... mins>
constexpr int Change()
{
    if constexpr (sizeof...(mins) == value + 1)
        return std::array{mins...}.back();
    else
        return Change<ValueT,
                      value,
                      coins_count,
                      coins,
                      mins...,
                      Fold<sizeof...(mins),
                           std::array<std::size_t, sizeof...(mins)>{mins...},
                           ValueT,
                           coins_count,
                           coins>()>();
};

#endif // #ifndef CONSTEXPR_CHANGE_HPP