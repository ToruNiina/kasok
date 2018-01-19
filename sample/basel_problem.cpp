#include <kasok/aitken.hpp>
#include <chrono>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    const auto zeta = [](std::size_t n) noexcept -> double {
        const double x = 1.0 / (n+1);
        return x * x;
    };

    std::cout << std::setprecision(15);

    // comparing rate of convergence.
    for(std::size_t i=1; i<=5; ++i)
    {
        const std::uintmax_t iteration_limit = std::pow(10, i);

        // using ksk::aitken_sum.
        {
            std::uintmax_t iteration = iteration_limit;
            const auto never_ends = [](double x, double y) noexcept -> bool {
                return false; // prevent early return
            };
            const auto sum = ksk::aitken_sum(zeta, never_ends, iteration);

            std::cout << "aitken sum : pi^2/6 = " << std::setw(16) << std::left
                      << sum << ", for "          << std::setw(7) << std::right
                      << iteration << " iteration | ";
        }

        // using normal sumup.
        {
            double sum = 0.0;
            for(std::uintmax_t j=0; j<iteration_limit; ++j)
            {
                sum += zeta(j);
            }
            std::cout << "normal sum : pi^2/6 = " << std::setw(16) << std::left
                      << sum << ", for "           << std::setw(7) << std::right
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
        const auto sum  = ksk::aitken_sum(zeta, tolerance, iteration);
        const auto stop = std::chrono::system_clock::now();
        const auto dur  = std::chrono::duration_cast<std::chrono::nanoseconds>(
                              stop - start);

        std::cout << "aitken sum : pi^2/6 = " << std::setw(16) << std::left
                  << sum << ", for "      << std::setw(5) << std::right
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
            sum += zeta(i);

            if(tolerance(s_prev, sum))
            {
                break;
            }
            ++i;
        }
        const auto stop = std::chrono::system_clock::now();
        const auto dur  = std::chrono::duration_cast<std::chrono::nanoseconds>(
                              stop - start);

        std::cout << "normal sum : pi^2/6 = " << std::setw(16) << std::left
                  << sum << ", for "      << std::setw(5) << std::right
                  << i << " iteration, tooks " << std::setw(12)
                  << std::right << dur.count() / 1e6 << " [ms]\n";
    }

    return 0;
}

