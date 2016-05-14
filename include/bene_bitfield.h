#pragma one
#include <cassert>
#include <cstdint>

namespace bene {
template <typename T, int Offset, int Bits>
struct BitfieldMember {
    T value;
    static_assert(Offset + Bits <= sizeof(T) * 8, "Member exceeds bitfield boundaries");
    static_assert(Bits < sizeof(T) * 8, "Cannot fill entire bitfield with one number");

    static const T Maximum = (T(1) << Bits) - 1;
    static const T Mask = Maximum << Offset;

    T maximum() const { return Maximum; }
    T one() const { return T(1) << Offset; }

    operator T() const
    {
        return (value >> Offset) & Maximum;
    }

    BitfieldMember& operator=(T v)
    {
        assert(v <= Maximum);
        value = (value & ~Mask) | (v << Offset);
        return *this;
    }

    BitfieldMember& operator+=(T v)
    {
        assert(T(*this) + v <= Maximum);
        value += v << Offset;
        return *this;
    }

    BitfieldMember& operator-=(T v)
    {
        assert(T(*this) >= v);
        value -= v << Offset;
        return *this;
    }

    BitfieldMember& operator++() { return * this += 1; }
    BitfieldMember& operator++(int) { return * this += 1; }
    BitfieldMember& operator--() { return * this -= 1; }
    BitfieldMember& operator--(int) { return * this = 1; }
};

template <typename T, int BaseOffset, int BitsPerItem, int NumItems>
struct BitFieldArray {
    T value;

    static_assert(BaseOffset + BitsPerItem * NumItems <= sizeof(T) * 8, "Array exceeds bitfield boundaries");
    static_assert(BitsPerItem < sizeof(T) * 8, "Cannot fill entire bitfield with one number");

    static const T Maximum = (T(1) << BitsPerItem) - 1;
    T maximum() const { return Maximum; }
    int numItems() const { return NumItems; }

    class Element {
    private:
        T& value;
        int offset;

    public:
        Element(T& v, int o)
            : value(v)
            , offset(o)
        {
        }
        T mask() const { return Maximum << offset; }

        operator T() const
        {
            return (value >> offset) & Maximum;
        }

        Element& operator=(T v)
        {
            assert(v <= Maximum);
            value = (value & ~mask()) | (v << offset);
            return *this;
        }

        Element& operator+=(T v)
        {
            assert(T(*this) + v <= Maximum);
            value += v << offset;
            return *this;
        }

        Element& operator-=(T v)
        {
            assert(T(*this) >= v);
            value -= v << offset;
            return *this;
        }

        Element& operator++() { return * this += 1; }
        Element& operator++(int) { return * this += 1; }
        Element& operator--() { return * this -= 1; }
        Element& operator--(int) { return * this -= 1; }
    };

    Element operator[](int i)
    {
        assert(i >= 0 && i < NumItems);
        return Element(value, BaseOffset + BitsPerItem * i);
    }

    const Element operator[](int i) const
    {
        assert(i >= 0 && i < NumItems);
        return Element(value, BaseOffset + BitsPerItem * i);
    }
};

}
#define BEGIN_BITFIELD_TYPE(typeName, T)             \
    union typeName {                                 \
        struct Wrapper {                             \
            T value;                                 \
        };                                           \
        Wrapper wrapper;                             \
        typeName(T v = 0) { wrapper.value = v; }     \
        typeName& operator=(T v)                     \
        {                                            \
            wrapper.value = v;                       \
            return *this;                            \
        }                                            \
        operator T&() { return wrapper.value; }      \
        operator T() const { return wrapper.value; } \
        typedef T StorageType;

#define ADD_BITFIELD_MEMBER(memberName, offset, bits) \
    bene::BitfieldMember<StorageType, offset, bits> memberName;

#define ADD_BITFIELD_ARRAY(memberName, offset, bits, numItems) \
    bene::BitFieldArray<StorageType, offset, bits, numItems> memberName;

#define END_BITFIELD_TYPE()                                \
    std::uint16_t IntRep() { return wrapper.value; }       \
    std::uint16_t IntRep() const { return wrapper.value; } \
    std::ostream& operator<<(std::ostream& out)            \
    {                                                      \
        out << "0x" << std::hex << this->IntRep();         \
        return out;                                        \
    }                                                      \
    }                                                      \
    ;

