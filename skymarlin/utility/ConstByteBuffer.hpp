#pragma once

#include <string>

#include <boost/core/noncopyable.hpp>
#include <boost/asio/buffer.hpp>
#include <skymarlin/utility/BitConverter.hpp>
#include <skymarlin/utility/ByteBufferExceptions.hpp>

namespace skymarlin::utility
{
class ConstByteBuffer : boost::noncopyable
{
public:
    ConstByteBuffer(byte* buffer, size_t size);

    ConstByteBuffer(ConstByteBuffer&& x) noexcept;

    template <NumericType T>
    T Read() const;

    template <typename T> requires std::same_as<T, std::string>
    T Read() const;

    void Skip(size_t n) const;

    const byte* data() const { return data_; }

    size_t size() const { return size_; }

    const byte& operator[](size_t pos) const;

    ConstByteBuffer& operator>>(bool& value) const;

    ConstByteBuffer& operator>>(byte& value) const;

    ConstByteBuffer& operator>>(u16& value) const;

    ConstByteBuffer& operator>>(u32& value) const;

    ConstByteBuffer& operator>>(u64& value) const;

    ConstByteBuffer& operator>>(i8& value) const;

    ConstByteBuffer& operator>>(i16& value) const;

    ConstByteBuffer& operator>>(i32& value) const;

    ConstByteBuffer& operator>>(i64& value) const;

    ConstByteBuffer& operator>>(f32& value) const;

    ConstByteBuffer& operator>>(f64& value) const;

    ConstByteBuffer& operator>>(std::string& value) const;

protected:
    byte* data_;
    size_t size_;
    mutable size_t rpos_{0};
};

inline ConstByteBuffer::ConstByteBuffer(byte* buffer, const size_t size)
    : data_(buffer), size_(size) {}

inline ConstByteBuffer::ConstByteBuffer(ConstByteBuffer&& x) noexcept
    : data_(x.data_), size_(x.size_), rpos_(x.rpos_)
{
    x.data_ = nullptr;
    x.size_ = 0;
    x.rpos_ = 0;
}


template <NumericType T>
T ConstByteBuffer::Read() const
{
    T value = BitConverter::Convert<T>(data_ + rpos_);
    rpos_ += sizeof(T);
    return value;
}

template <typename T> requires std::same_as<T, std::string>
T ConstByteBuffer::Read() const
{
    //TODO: Get StringHeader via BitConverter
    const size_t length = Read<StringLengthType>();
    if (rpos_ + length > size_) {
        throw ByteBufferInvalidValueException(true, std::to_string(length), "string length");
    }

    std::string value;
    const size_t end_pos = rpos_ + length;
    while (rpos_ < end_pos) {
        // TODO: encoding
        value += Read<char>();
    }

    return value;
}

inline void ConstByteBuffer::Skip(const size_t n) const
{
    if (rpos_ + n > size_) {
        throw ByteBufferPositionException(true, rpos_, n, size_);
    }

    rpos_ += n;
}

inline const byte& ConstByteBuffer::operator[](const size_t pos) const
{
    if (pos > size_) {
        throw ByteBufferPositionException(true, pos, sizeof(byte), size_);
    }

    return data_[pos];
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(bool& value) const
{
    value = Read<byte>() > 0;
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(byte& value) const
{
    value = Read<byte>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(u16& value) const
{
    value = Read<u16>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(u32& value) const
{
    value = Read<u32>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(u64& value) const
{
    value = Read<u64>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(i8& value) const
{
    value = Read<i8>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(i16& value) const
{
    value = Read<i16>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(i32& value) const
{
    value = Read<i32>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(i64& value) const
{
    value = Read<i64>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(f32& value) const
{
    value = Read<f32>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(f64& value) const
{
    value = Read<f64>();
    return *const_cast<ConstByteBuffer*>(this);
}

inline ConstByteBuffer& ConstByteBuffer::operator>>(std::string& value) const
{
    value = Read<std::string>();
    return *const_cast<ConstByteBuffer*>(this);
}
}
