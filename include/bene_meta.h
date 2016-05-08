#pragma once
#include <iostream>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif
#include <cstdlib>
#include <memory>
#include <string>

// Basically http://pdimov.com/cpp2/simple_cxx11_metaprogramming.html

template <class T>
using add_pointer = T*;
template <class T>
using add_const = const T;
template <class T>
using add_reference = T&;

template <class... T>
struct mp_list {
};

template <class A, template <class...> class B>
struct mp_rename_impl;

template <template <class...> class A, class... T, template <class...> class B>
struct mp_rename_impl<A<T...>, B> {
    using type = B<T...>;
};

template <class... T>
using mp_length = std::integral_constant<std::size_t, sizeof...(T)>;

template <class A, template <class...> class B>
using mp_rename = typename mp_rename_impl<A, B>::type;

template <class L>
using mp_size = mp_rename<L, mp_length>;

template <template <class...> class F, class L>
using mp_apply = mp_rename<L, F>;

template <class L, class... T>
struct mp_push_front_impl;

template <template <class...> class L, class... U, class... T>
struct mp_push_front_impl<L<U...>, T...> {
    using type = L<T..., U...>;
};

template <class L, class... T>
using mp_push_front = typename mp_push_front_impl<L, T...>::type;

template <template <class...> class F, class L>
struct mp_transform_impl;

template <template <class...> class F, class L>
using mp_transform = typename mp_transform_impl<F, L>::type;

template <template <class...> class F, template <class...> class L, class... T>
struct mp_transform_impl<F, L<T...> > {
    using type = L<F<T>...>;
};

template <template <class...> class F, class L1, class L2>
struct mp_transform2_impl;

template <template <class...> class F, class L1, class L2>
using mp_transform2 = typename mp_transform2_impl<F, L1, L2>::type;

template <template <class...> class F,
    template <class...> class L1, class... T1,
    template <class...> class L2, class... T2>
struct mp_transform2_impl<F, L1<T1...>, L2<T2...> > {
    static_assert(sizeof...(T1) == sizeof...(T2),
        "The arguments of mp_transform2 should be of the same size");

    using type = L1<F<T1, T2>...>;
};

template <class V>
struct mp_constant {
    template <class...>
    using apply = V;
};

template <class L, class V>
using mp_fill = mp_transform<mp_constant<V>::template apply, L>;

template <class T, T... Ints>
struct integer_sequence {
};

template <class S>
struct next_integer_sequence;

template <class T, T... Ints>
struct next_integer_sequence<integer_sequence<T, Ints...> > {
    using type = integer_sequence<T, Ints..., sizeof...(Ints)>;
};

template <class T, T I, T N>
struct make_int_seq_impl;

template <class T, T N>
using make_integer_sequence = typename make_int_seq_impl<T, 0, N>::type;

template <class T, T I, T N>
struct make_int_seq_impl {
    using type = typename next_integer_sequence<typename make_int_seq_impl<T, I + 1, N>::type>::type;
};

template <class T, T N>
struct make_int_seq_impl<T, N, N> {
    using type = integer_sequence<T>;
};

template <std::size_t... Ints>
using index_sequence = integer_sequence<std::size_t, Ints...>;

template <std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template <class S>
struct mp_from_sequence_impl;

template <template <class T, T... I> class S, class U, U... J>
struct mp_from_sequence_impl<S<U, J...> > {
    using type = mp_list<std::integral_constant<U, J>...>;
};

template <class S>
using mp_from_sequence = typename mp_from_sequence_impl<S>::type;

template <class N>
using mp_iota = mp_from_sequence<make_index_sequence<N::value> >;

template <class L>
using F = mp_iota<mp_size<L> >;

template <class... L>
struct mp_append_impl;

template <class... L>
using mp_append = typename mp_append_impl<L...>::type;

template <>
struct mp_append_impl<> {
    using type = mp_list<>;
};

template <template <class...> class L, class... T>
struct mp_append_impl<L<T...> > {
    using type = L<T...>;
};

template <template <class...> class L1, class... T1,
    template <class...> class L2, class... T2, class... Lr>
struct mp_append_impl<L1<T1...>, L2<T2...>, Lr...> {
    using type = mp_append<L1<T1..., T2...>, Lr...>;
};

template <class R, class... Is, class... Ks, class Tp>
R tuple_cat_(mp_list<Is...>, mp_list<Ks...>, Tp tp)
{
    return R{ std::get<Ks::value>(std::get<Is::value>(tp))... };
}

template <class... Tp,
    class R = mp_append<std::tuple<>, typename std::remove_reference<Tp>::type...> >
R tuple_cat(Tp&&... tp)
{
    std::size_t const N = sizeof...(Tp);

    // inner

    using list1 = mp_list<mp_rename<typename std::remove_reference<Tp>::type, mp_list>...>;
    using list2 = mp_from_sequence<make_index_sequence<N> >;

    // list1: [[x1, x2, x3], [], [y1, y2, y3], [z1, z2]]
    // list2: [0, 1, 2, 3]

    using list3 = mp_transform2<mp_fill, list1, list2>;

    // list3: [[0, 0, 0], [], [2, 2, 2], [3, 3]]

    using inner = mp_rename<mp_push_front<list3, mp_list<> >, mp_append>; // or mp_apply<mp_append, list3>

    // inner: [0, 0, 0, 2, 2, 2, 3, 3]

    // outer

    using list4 = mp_transform<F, list1>;

    // list4: [[0, 1, 2], [], [0, 1, 2], [0, 1]]

    using outer = mp_rename<list4, mp_append>;

    // outer: [0, 1, 2, 0, 1, 2, 0, 1]

    return tuple_cat_<R>(mp_rename<inner, mp_list>(), outer(),
        std::forward_as_tuple(std::forward<Tp>(tp)...));
}

template <class T>
std::string
type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void (*)(void*)> own(
#ifndef _MSC_VER
        abi::__cxa_demangle(typeid(TR).name(), nullptr,
            nullptr, nullptr),
#else
        nullptr,
#endif
        std::free);
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

template <class T>
void print_type(std::string const& a, const std::string& b)
{
    std::cout << a << type_name<T>() << b;
}

template <int I, int N, class... T>
struct print_tuple_ {
    void operator()(std::tuple<T...> const& tp) const
    {
        using Tp = typename std::tuple_element<I, std::tuple<T...> >::type;

        print_type<Tp>(" ", ": ");

        std::cout << std::get<I>(tp) << ";";

        print_tuple_<I + 1, N, T...>()(tp);
    }
};

template <int N, class... T>
struct print_tuple_<N, N, T...> {
    void operator()(std::tuple<T...> const&) const
    {
    }
};

template <class... T>
void print_tuple(std::tuple<T...> const& tp)
{
    std::cout << "{";
    print_tuple_<0, sizeof...(T), T...>()(tp);
    std::cout << " }\n";
}

template <class... T>
struct mp_plus_impl;

template <class... T>
using mp_plus = typename mp_plus_impl<T...>::type;

template <>
struct mp_plus_impl<> {
    using type = std::integral_constant<int, 0>;
};

template <class T1, class T2, class T3, class T4, class T5,
    class T6, class T7, class T8, class T9, class T10, class... T>
struct mp_plus_impl<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...> {
    static constexpr auto _v = T1::value + T2::value + T3::value + T4::value + T5::value + T6::value + T7::value + T8::value + T9::value + T10::value + mp_plus<T...>::value;

    using type = std::integral_constant<
        typename std::remove_const<decltype(_v)>::type, _v>;
};

template <class L, class V>
struct mp_count_impl;

template <template <class...> class L, class... T, class V>
struct mp_count_impl<L<T...>, V> {
    using type = mp_plus<std::is_same<T, V>...>;
};

template <class L, class V>
using mp_count = typename mp_count_impl<L, V>::type;

template <class L, template <class...> class P>
struct mp_count_if_impl;

template <class L, template <class...> class P>
using mp_count_if = typename mp_count_if_impl<L, P>::type;

template <bool v>
using mp_bool = std::integral_constant<bool, v>;

template <class L, template <class...> class P>
struct mp_count_if_impl;

template <template <class...> class L, class... T, template <class...> class P>
struct mp_count_if_impl<L<T...>, P> {
    using type = mp_plus<mp_bool<P<T>::value != 0>...>;
};

template <class L, template <class...> class P>
using mp_count_if = typename mp_count_if_impl<L, P>::type;

template <class L, class V>
using mp_contains = mp_bool<mp_count<L, V>::value != 0>;
