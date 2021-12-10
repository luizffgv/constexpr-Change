# constexpr-Change

## What is this?

This code calculates at compile time the least number of coins needed to pay
change. It's not very fast and might not work for every single case, but it gave
the same result as [this website](http://honsing.com/Coins.htm) for every
reasonable value I tested. Also doubles as a compiler torturer.

This requires C++20 and was tested with clang and g++ using `-Wpedantic`.

## Example

### Input

```cpp
constexpr int                value_as_cents{239};
constexpr std::array<int, 4> coins{1, 5, 10, 25};
```

### Output

```plaintext
14
```
