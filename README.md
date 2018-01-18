kasok
====
[![Build Status](https://travis-ci.org/ToruNiina/kasok.svg?branch=master)](https://travis-ci.org/ToruNiina/kasok)

a toolbox for series acceleration.

kasok requires C++11 and Boost.CallableTraits.

For testing, Catch2 is required(see below).

## Example

### Calculate Leibniz formula using Aitken's delta squared process

```cpp
#include <kasok/aitken.hpp>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cmath>

int main()
{
    // function that generates the quadraple of n-th term of leibniz formula.
    const auto leibniz = [](std::size_t n) noexcept -> double {
        return (n % 2 == 0) ? 4.0 / (2 * n + 1) : -4.0 / (2 * n + 1);
    };

    // function that judges convergence with some tolerance.
    const auto tolerance = [](double x, double y) noexcept -> bool {
        return std::abs(x - y) < 1e-12 || std::abs(x / y - 1.0) < 1e-8;
    };

    // maximum number of iteration.
    std::uintmax_t iteration = 10000;

    // calculating sum of {leibniz(n)} for 0...iteration.
    const auto sum = ksk::aitken_sum(leibniz, tolerance, iteration);

    std::cout << std::setprecision(15);
    std::cout << "pi ~ " << sum
              << " @ " << iteration << " iteration." << std::endl;
    // after calculation, `iteration` is set to the actual number of iteration.
    return 0;
}
```

For more information, see `sample/leibniz.cpp`.
After building, you can run it.

## Build

kasok is a header-only library.
You need nothing except to add a include path.

To build a sample, run this commands.

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ cd ..
$ ./bin/leibniz
```

## Testing

Using CMake. It will downloads Catch2 and Boost.CallableTraits.

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make test
```
