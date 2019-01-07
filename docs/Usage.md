# Usage

kasok is a header-only library, so you don't need to build anything.

All the stuff are defined in the namespace `ksk`.

## With function objects

kasok works with function objects, including lambda.

The functions provided by kasok receives 3 arguments.

```cpp
template<typename Function, typename Tolerance, typename UInt>
auto func(Function&& f, Tolerance&& tol, UInt& maxiter);
```

First function object `f` receives unsigned integer and returns value.
It calculates n-th value of the sequence to converge. `func` returns the same
type as `f` returns after the value is converged. We call the type as `value_type`
hereafter.

Second function object `tol` recieves two `value_type` and returns `bool` that
represents the sequence is converged. The two arguments corresponds to the value
before and current term.

Third unsigned integer value represents maximum number of iteration. After this
iteration, it returns regardless of the result of convergence check.

### example

The code below calculates $$ \pi $$ using the [Leibniz formula](https://en.wikipedia.org/wiki/Leibniz_formula_for_%CF%80) that states

$$
1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \frac{1}{9} - \cdots = \frac{\pi}{4}.
$$

```cpp
// function that generates the quadraple of n-th term of leibniz formula.
const auto leibniz = [](std::uintmax_t n) noexcept -> double {
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
```

## With an array that contains a sequence

kasok works with arrays that contains the sequence to converge.

The functions also receives 3 arguments.

```cpp
template<typename FirstIterator, typename LastIterator, typename Tolerance>
auto func(FirstIterator& first, LastIterator last, Tolerance&& tol)
```

The first two iterators point `begin()` and `end()`, respectively.
After calculation, `first` points the term used at the last iteration.

The last function object `tol` recieves two `value_type` and returns `bool` that
represents the sequence is converged. The two arguments corresponds to the value
before and current term.

### example

The code below calculates $$ e $$ using the infinite series

$$
e = \sum_{n=0}^{\infty} \frac{1}{n!}
$$

```cpp
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
```
