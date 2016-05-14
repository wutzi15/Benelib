#pragma once
#include <exception>

namespace bene {

class constexpr_txt {
private:
    const char* const p_;
    const std::size_t sz_;

public:
    template <std::size_t N>
    constexpr constexpr_txt(const char(&a)[N])
        : p_(a)
        , sz_(N - 1)
    {
    }

    constexpr char operator[](std::size_t n) const
    {
        return n < sz_ ? p_[n] : throw std::out_of_range("");
    }

    constexpr std::size_t size() const { return sz_; }
};

template <typename T = std::uint32_t>
constexpr T constexpr_bin(const char* t)
{
    T x = 0;
    std::size_t b = 0;
    for (std::size_t i = 0; t[i] != '\0'; ++i) {
        if (b >= std::numeric_limits<T>::digits) {
            throw std::overflow_error("To many bits!");
        }
        switch (t[i]) {
        case ',':
            break;
        case '0':
            x = (x * 2);
            ++b;
            break;
        case '1':
            x = (x * 2) + 1;
            ++b;
            break;
        default:
            throw std::domain_error("only '0', '1' and ',' are allowed");
        }
    }
    return x;
}
}