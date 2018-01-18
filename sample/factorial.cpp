#include <kasok/aitken.hpp>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <cmath>

struct factorial_iterator
{
    typedef double value_type;
    typedef value_type const& reference;
    typedef value_type const* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::forward_iterator_tag iterator_category;

    factorial_iterator() noexcept : term(1.0), index(0){}
    factorial_iterator(std::size_t idx) noexcept : term(1.0), index(idx){}

    reference operator*() const noexcept {return this->term;}

    factorial_iterator& operator++() noexcept
    {
        this->index++;
        term /= static_cast<value_type>(index);
        return *this;
    }

    value_type  term;
    std::size_t index;
};

inline bool
operator==(factorial_iterator const& lhs, factorial_iterator const& rhs) noexcept
{
    return lhs.index == rhs.index;
}

inline bool
operator!=(factorial_iterator const& lhs, factorial_iterator const& rhs) noexcept
{
    return lhs.index != rhs.index;
}

int main()
{
    std::cout << std::setprecision(15);

    // comparing rate of convergence.
    for(std::size_t i=1; i<=10; ++i)
    {
        const std::uintmax_t iteration_limit = i;

        // using ksk::aitken.
        {
            const auto never_ends = [](double x, double y) noexcept -> bool {
                return false;
            };
            auto first = factorial_iterator();
            const auto last = factorial_iterator(iteration_limit);
            const auto e    = ksk::aitken_sum(first, last, never_ends);

            std::cout << "aitken : e = " << std::setw(16) << std::left
                      << e << ", for "   << std::setw(3) << std::right
                      << first.index << " iteration | ";
        }

        // using normal iteration.
        {
            double s = 0.0;
            auto first = factorial_iterator();
            for(std::uintmax_t j=0; j<iteration_limit; ++j)
            {
                s += *first;
                ++first;
            }
            std::cout << "normal : e = " << std::setw(16) << std::left
                      << s << ", for "   << std::setw(3) << std::right
                      << iteration_limit << " iteration\n";
        }
    }
    return 0;
}
