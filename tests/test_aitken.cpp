#define CATCH_CONFIG_MAIN
#include <Catch2/single_include/catch.hpp>
#include <kasok/aitken.hpp>

TEST_CASE("aitken sumup for leibniz formula", "[aitken-leibniz]") {

    const auto leibniz = [](std::size_t n) noexcept -> double {
        return (n % 2 == 0) ? 4.0 / (2 * n + 1) : -4.0 / (2 * n + 1);
    };

    const auto tolerance = [](double x, double y) noexcept -> bool {
        return std::abs(x - y) < 1e-8 || std::abs(x / y - 1.0) < 1e-6;
    };

    const std::size_t max_iter = 1000000000;

    std::size_t iteration = max_iter;
    const auto sum  = ksk::aitken_sum(leibniz, tolerance, iteration);

    CHECK(sum == Approx(3.141592653589793238).epsilon(1e-6));

    std::size_t i = 0;
    double s = 0.0;
    while(i < max_iter)
    {
        const auto s_prev = s;
        s += leibniz(i);
        if(tolerance(s_prev, s))
        {
            break;
        }
        ++i;
    }

    // converge faster than normal summation.
    CHECK(iteration < i);
}
