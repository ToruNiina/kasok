kasok
====
[![Build Status](https://travis-ci.org/ToruNiina/kasok.svg?branch=master)](https://travis-ci.org/ToruNiina/kasok)

a toolbox for series acceleration.

kasok requires C++11 or later.

Testing codes depend on Catch2.

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

### Using iterator as terms of the series.

Using pre-calculated table or user-defined class that emulates iterator.

```cpp
#include <kasok/aitken.hpp>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cmath>

int main()
{
    // pre-calculated table.
    const std::vector<double> table = {
        1.0,
        1.0 / 1.0,
        1.0 / (1.0 * 2.0),
        1.0 / (1.0 * 2.0 * 3.0),
        1.0 / (1.0 * 2.0 * 3.0 * 4.0),
        1.0 / (1.0 * 2.0 * 3.0 * 4.0 * 5.0),
        1.0 / (1.0 * 2.0 * 3.0 * 4.0 * 5.0 * 6.0),
        1.0 / (1.0 * 2.0 * 3.0 * 4.0 * 5.0 * 6.0 * 7.0),
        1.0 / (1.0 * 2.0 * 3.0 * 4.0 * 5.0 * 6.0 * 7.0 * 8.0),
        1.0 / (1.0 * 2.0 * 3.0 * 4.0 * 5.0 * 6.0 * 7.0 * 8.0 * 9.0),
        1.0 / (1.0 * 2.0 * 3.0 * 4.0 * 5.0 * 6.0 * 7.0 * 8.0 * 9.0 * 10.0)
    };

    // tolerance
    const auto tol = [](double x, double y) noexcept -> bool {
        return std::abs(x - y) < 1e-8 || std::abs(x / y - 1.0) < 1e-6;
    };

    // iterator that points the first element
    auto iter = table.begin();

    // caluclate sum using lookup table
    const auto sum = ksk::aitken_sum(iter, table.end(), tol);

    std::cout << std::setprecision(15);
    std::cout << "e ~ " << sum << " @ "
              << std::distance(table.begin(), iter) << " iteration." << std::endl;
    // after calculation, `iter` is set to the actual number of iteration.
    return 0;
}
```

For more information, see `sample/factorial.cpp`.

## Build

kasok is a header-only library.
To use it in your code, you need nothing except to add an include path.

To build samples, run this commands.

```sh
$ git clone --recursive https://github.com/ToruNiina/kasok.git
$ cd kasok
$ mkdir build
$ cd build
$ cmake ..
$ make
```

After build, the executables will be found in `bin/` directory.

```sh
$ cd ../bin
$ ./leibniz
```

## Testing

If you already built samples, you can run test programs just by `make test`.

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make test
```
