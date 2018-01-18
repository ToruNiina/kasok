//! \file aitken.hpp
//! \brief provides functions based on Aitken's delta squared process.
//! \author Toru Niina (niina.toru.68u@gmail.com)
#ifndef KASOK_AITKENS_DELTA_SQUARED_PROCESS_HPP
#define KASOK_AITKENS_DELTA_SQUARED_PROCESS_HPP
#include <boost/callable_traits/return_type.hpp>
#include <boost/callable_traits/is_invocable.hpp>
#include <type_traits>
#include <iterator>
#include <cstdint>

//! \brief namespace of this libraray "kasok".
namespace ksk
{

//! \brief Aitken's delta squared process.
//! \return a limit of given sequence.
//!         \f[ \lim_{n\to\infty} f(n) \f]
//! \param  f         is a function that calculates n-th term.
//! \param  tolerance is a function that judges convergence.
//! \param  iteration is a maximum number of function invocation. On exit,
//!                   it will be set to an actual number of function invocation.
//! \tparam Function  is `result_type Function(UInt)`.
//! \tparam Tolerance is `bool Tolerance(result_type, result_type)`
//! \tparam UInt      is an unsigned integer type.
//! \details accelerates the rate of convergence of a series that is generated
//!          by f. {s_i} = {f(0), f(1), f(2), ...}
template<typename Function, typename Tolerance, typename UInt>
boost::callable_traits::return_type_t<Function>
aitken(Function&& f, Tolerance&& tolerance, UInt& iteration)
{
    using result_type = boost::callable_traits::return_type_t<Function>;
    static_assert(boost::callable_traits::is_invocable<Function, UInt>::value,
        "Function must be callable as f(uint)");
    static_assert(boost::callable_traits::is_invocable_r<
            bool, Tolerance, result_type, result_type>::value,
        "Tolerance must be a type `bool tolerance(result_type, result_type)`");

    result_type xn  = f(0);
    result_type xn1 = f(1);
    result_type Axn = xn1;
    for(std::uintmax_t i=2, imax=iteration; i<imax; ++i)
    {
        const result_type xn2  = f(i);
        const result_type dxn  = xn1 - xn;
        const result_type d2xn = xn2 - xn1 - dxn;
        const result_type next_Axn = xn - (dxn * dxn) / d2xn;

        if(tolerance(Axn, next_Axn))
        {
            iteration = i;
            return next_Axn;
        }
        xn  = xn1;
        xn1 = xn2;
        Axn = next_Axn;
    }
    return Axn;
}

//! \brief Aitken's delta squared process.
//! \return a limit of given sequence. type will be FirstIterator::value_type.
//!         \f[ \lim_{n\to\infty} f(n) \f]
//! \param  first     is a iterator that points the first term. On exit,
//!                   it will be set to the iterator used in the last iteration.
//! \param  last      is a iterator that points the next of the last term.
//! \param  tolerance is a function that judges convergence.
//! \tparam FirstIterator must have Iterator::value_type, operator++ and operator*.
//! \tparam LastIterator  must have Iterator::value_type, operator++ and operator*.
//! \tparam Tolerance is `bool Tolerance(value_type, value_type)`
//! \details accelerates the rate of convergence of a series that is generated
//!          by f. {s_i} = {f(0), f(1), f(2), ...}
//! \details the declaration of std::iterator_traits<(First|Last)Iterator>
//!          should be valid. For user-defined class that emulates Iterator
//!          and acts a recarrence relation, LastIterator can be a different
//!          from FirstIterator if the not-equal relational operator
//!          `bool operator!=(FirstIterator, LastIterator)` is defined.
template<typename FirstIterator, typename LastIterator, typename Tolerance>
typename std::iterator_traits<FirstIterator>::value_type
aitken(FirstIterator& first, LastIterator last, Tolerance&& tolerance)
{
    using result_type = typename std::iterator_traits<FirstIterator>::value_type;
    static_assert(boost::callable_traits::is_invocable_r<
            bool, Tolerance, result_type, result_type>::value,
        "Tolerance must be a type `bool tolerance(result_type, result_type)`");

    result_type xn  = *first; ++first;
    if(first == last) {return xn;}

    result_type xn1 = *first; ++first;
    if(first == last) {return xn1;}

    result_type Axn = xn1;
    for(; first != last; ++first)
    {
        const result_type xn2  = *first;
        const result_type dxn  = xn1 - xn;
        const result_type d2xn = xn2 - xn1 - dxn;
        const result_type next_Axn = xn - (dxn * dxn) / d2xn;

        if(tolerance(Axn, next_Axn))
        {
            return next_Axn;
        }
        xn  = xn1;
        xn1 = xn2;
        Axn = next_Axn;
    }
    return Axn;
}

//! \brief  calculate sum of a series by using Aitken's delta squared process.
//! \return a limit of a sum of given sequence.
//!         \f[\lim_{n\to\infty} \sum_{k=0}^{n} f(k)\f].
//! \param  f         is a function that calculates n-th term.
//! \param  tolerance is a function that judges convergence.
//! \param  iteration is a maximum number of function invocation. On exit,
//!                   it will be set to an actual number of function invocation.
//! \tparam Function  is `result_type Function(UInt)`.
//! \tparam Tolerance is `bool Tolerance(result_type, result_type)`
//! \tparam UInt      is an unsigned integer type.
template<typename Function, typename Tolerance, typename UInt>
boost::callable_traits::return_type_t<Function>
aitken_sum(Function&& f, Tolerance&& tolerance, UInt& iteration)
{
    using result_type = boost::callable_traits::return_type_t<Function>;
    static_assert(
        boost::callable_traits::is_invocable<Function, UInt>::value,
        "Function must be callable as f(uint)");
    static_assert(
        boost::callable_traits::is_invocable_r<
            bool, Tolerance, result_type, result_type>::value,
        "Tolerance must be a type `bool tolerance(result_type, result_type)`");

    result_type xn  = f(0);
    result_type xn1 = xn + f(1);
    result_type Axn = xn1;
    for(std::uintmax_t i=2, imax=iteration; i<imax; ++i)
    {
        const result_type xn2  = xn1 + f(i);
        const result_type dxn  = xn1 - xn;
        const result_type d2xn = xn2 - xn1 - dxn;
        const result_type next_Axn = xn - (dxn * dxn) / d2xn;

        if(tolerance(Axn, next_Axn))
        {
            iteration = i;
            return next_Axn;
        }
        xn  = xn1;
        xn1 = xn2;
        Axn = next_Axn;
    }
    return Axn;
}

//! \brief   calculate sum of a series by using Aitken's delta squared process.
//! \return  a limit of a sum of given sequence.
//!          type will be FirstIterator::value_type.
//!          \f[\lim_{n\to\infty} \sum_{k=0}^{n} f(k)\f].
//! \param   first     is a iterator that points the first term. On exit, it
//!                    will be set to the iterator used in the last iteration.
//! \param   last      is a iterator that points the next of the last term.
//! \param   tolerance is a function that judges convergence.
//! \tparam  FirstIterator must have Iterator::value_type, operator++ and
//!                        operator*.
//! \tparam  LastIterator  must have Iterator::value_type, operator++ and
//!                        operator*.
//! \tparam  Tolerance     is `bool Tolerance(result_type, result_type)`
//! \details the declaration of std::iterator_traits<(First|Last)Iterator>
//!          should be valid. For user-defined class that emulates Iterator
//!          and acts a recarrence relation, LastIterator can be a different
//!          from FirstIterator if the not-equal relational operator
//!          `bool operator!=(FirstIterator, LastIterator)` is defined.
template<typename FirstIterator, typename LastIterator, typename Tolerance>
typename std::iterator_traits<FirstIterator>::value_type
aitken_sum(FirstIterator& first, LastIterator last, Tolerance&& tolerance)
{
    using result_type = typename std::iterator_traits<FirstIterator>::value_type;
    static_assert(boost::callable_traits::is_invocable_r<
            bool, Tolerance, result_type, result_type>::value,
        "Tolerance must be callable as tolerance(result_type)");

    result_type xn  = *first;      ++first;
    if(first == last) {return xn;}

    result_type xn1 = *first + xn; ++first;
    if(first == last) {return xn1;}

    result_type Axn = xn1;
    for(; first != last; ++first)
    {
        const result_type xn2  = xn1 + (*first);
        const result_type dxn  = xn1 - xn;
        const result_type d2xn = xn2 - xn1 - dxn;
        const result_type next_Axn = xn - (dxn * dxn) / d2xn;

        if(tolerance(Axn, next_Axn))
        {
            return next_Axn;
        }
        xn  = xn1;
        xn1 = xn2;
        Axn = next_Axn;
    }
    return Axn;
}

} // ksk
#endif// KASOK_AITKENS_DELTA_SQUARED_PROCESS_HPP
