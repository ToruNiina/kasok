#ifndef KASOK_TYPE_TRAITS_HPP
#define KASOK_TYPE_TRAITS_HPP
#include <type_traits>

namespace ksk
{

template<typename F, typename ... Args>
struct invoke_result :
#if __cplusplus >= 201703L
    std::invoke_result<F, Args...>
#else
    std::result_of<F(Args...)>
#endif
{};

template<typename F, typename ... Args>
using invoke_result_t = typename ::ksk::invoke_result<F, Args...>::type;

} // ksk
#endif// KASOK_TYPE_TRAITS_HPP
