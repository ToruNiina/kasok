#include <kasok/aitken.hpp>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    const auto leibniz = [](std::size_t n) noexcept -> double {
        return (n % 2 == 0) ? 4.0 / (2 * n + 1) : -4.0 / (2 * n + 1);
    };

    std::cout << std::setprecision(15);

    // comparing rate of convergence.
    for(std::size_t i=4; i<=20; ++i)
    {
        const std::uintmax_t iteration_limit = std::pow(2, i);

        // using ksk::aitken_sum.
        {
            std::uintmax_t iteration = iteration_limit;
            const auto never_ends = [](double x, double y) noexcept -> bool {
                return false; // prevent early return
            };
            const auto sum = ksk::aitken_sum(leibniz, never_ends, iteration);

            std::cout << "aitken sum : pi = " << std::setw(16) << std::left
                      << sum << ", for "       << std::setw(8) << std::right
                      << iteration << " iteration | ";
        }

        // using normal sumup.
        {
            double sum = 0.0;
            for(std::uintmax_t j=0; j<iteration_limit; ++j)
            {
                sum += leibniz(j);
            }
            std::cout << "normal sum : pi = " << std::setw(16) << std::left
                      << sum << ", for "       << std::setw(8) << std::right
                      << iteration_limit << " iteration\n";
        }
    }

    std::cout << "\n----with tolerance : absolute = 1e-12 or relative 1e-8\n";

    const auto tolerance = [](double x, double y) noexcept -> bool {
        return std::abs(x - y) < 1e-12 || std::abs(x / y - 1.0) < 1e-8;
    };

    {
        const auto start = std::chrono::system_clock::now();
        std::uintmax_t iteration = 10000;
        const auto sum  = ksk::aitken_sum(leibniz, tolerance, iteration);
        const auto stop = std::chrono::system_clock::now();
        const auto dur  = std::chrono::duration_cast<std::chrono::nanoseconds>(
                              stop - start);

        std::cout << "aitken sum : pi = " << std::setw(16) << std::left
                  << sum << ", for "      << std::setw(10) << std::right
                  << iteration << " iteration, tooks " << std::setw(12)
                  << std::right << dur.count() / 1e6 << " [ms]\n";
    }
    {
        const auto start = std::chrono::system_clock::now();
        std::size_t i=0;
        double sum=0;
        while(true)
        {
            const auto s_prev = sum;
            sum += leibniz(i);

            if(tolerance(s_prev, sum))
            {
                break;
            }
            ++i;
        }
        const auto stop = std::chrono::system_clock::now();
        const auto dur  = std::chrono::duration_cast<std::chrono::nanoseconds>(
                              stop - start);

        std::cout << "normal sum : pi = " << std::setw(16) << std::left
                  << sum << ", for "      << std::setw(10) << std::right
                  << i << " iteration, tooks " << std::setw(12)
                  << std::right << dur.count() / 1e6 << " [ms]\n";
    }

    return 0;
}
