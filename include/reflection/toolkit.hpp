/*
    Boost Software License - Version 1.0 - August 17, 2003

    Permission is hereby granted, free of charge, to any person or organization
    obtaining a copy of the software and accompanying documentation covered by
    this license (the "Software") to use, reproduce, display, distribute,
    execute, and transmit the Software, and to prepare derivative works of the
    Software, and to permit third-parties to whom the Software is furnished to
    do so, all subject to the following:

    The copyright notices in the Software and this entire statement, including
    the above license grant, this restriction and the following disclaimer,
    must be included in all copies of the Software, in whole or in part, and
    all derivative works of the Software, unless such copies or derivative
    works are solely in the form of machine-executable object code generated by
    a source language processor.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "magic.hpp"
#include "serialization_manager.hpp"
#include "serializer.hpp"

#include <limits>

#ifndef REFLECTOR_AVOID_STL
#include <string>
#endif

#define DECLARE_REFLECTION(name_, type_, template_) class name_: public ITypeReflection {\
public:\
    name_() {}\
\
    virtual bool isPolymorphic() override { return false; }\
    virtual const char* staticTypeName() override { return #type_; }\
    virtual const char* typeName(const void* p_value) override { return #type_; }\
    virtual const UUID_t* uuidOrNull(const void* p_value) override { return nullptr; }\
\
    virtual bool serialize(IErrorHandler* err, serialization::IWriter* writer, const void* p_value)  override {\
        type_ const& value = *reinterpret_cast<type_ const*>(p_value);\
        return serialization::SerializationManager<type_>::serialize(err, writer, value);\
    }\
    virtual bool deserialize(IErrorHandler* err, serialization::IReader* reader, void* p_value) override {\
        type_& value = *reinterpret_cast<type_*>(p_value);\
        return serialization::SerializationManager<type_>::deserialize(err, reader, value);\
    }\
    virtual bool serializeTypeInformation(IErrorHandler* err, serialization::IWriter* writer, const void* p_value)  override {\
        type_ const& value = *reinterpret_cast<type_ const*>(p_value);\
        return serialization::SerializationManager<type_>::serializeTypeInformation(err, writer, value);\
    }\
    virtual bool verifyTypeInformation(IErrorHandler* err, serialization::IReader* reader, void* p_value) override {\
        type_& value = *reinterpret_cast<type_*>(p_value);\
        return serialization::SerializationManager<type_>::verifyTypeInformation(err, reader, value);\
    }\
\
    virtual bool setFromString(IErrorHandler* err, const char* str, size_t strLen,\
            void* p_value) override {\
        type_& value = *reinterpret_cast<type_*>(p_value);\
        return template_::fromString(err, str, strLen, value);\
    }\
    virtual bool toString(IErrorHandler* err, char*& buf, size_t& bufSize, uint32_t fieldMask,\
            const void* p_value) override {\
        type_ const& value = *reinterpret_cast<type_ const*>(p_value);\
        return template_::toString(err, buf, bufSize, value);\
    }\
};\

#define PUBLISH_REFLECTION(reflection_, type_) \
template <> ITypeReflection* reflectionForType<type_>(type_) {\
    static reflection_ reflection;\
    return &reflection;\
}\
template <> ITypeReflection* reflectionForType2<type_>() {\
    static reflection_ reflection;\
    return &reflection;\
}\
template <> ITypeReflection* reflectionForType2<type_ const>() {\
    static reflection_ reflection;\
    return &reflection;\
}\

#define DEFINE_REFLECTION(name_, type_, template_) \
    DECLARE_REFLECTION(name_, type_, template_)\
    PUBLISH_REFLECTION(name_, type_)

#define DEFINE_INTEGRAL_REFLECTION(type_, oneTokenType_) DEFINE_REFLECTION(IntegralReflector_##oneTokenType_, type_,\
    IntegralReflectionTemplate<type_>)

#define DEFINE_FLOAT_REFLECTION(type_, oneTokenType_) DEFINE_REFLECTION(FloatReflector_##oneTokenType_, type_,\
    FloatReflectionTemplate<type_>)

namespace reflection {  // UUID('c3549467-1615-4087-9829-176a2dc44b76')

template <typename Bool_t>
class BoolReflectionTemplate {
public:
    static int strcasecmp(const char* a, const char* b) {
        int diff = tolower(*a) - tolower(*b);

        while (*a && *b && diff == 0) {
            diff = tolower(*a) - tolower(*b);
            a++;
            b++;
        }

        return diff;
    }

    static bool fromString(IErrorHandler* err, const char* str, size_t strLen, Bool_t& value_out) {
        char* end;

        if (strcasecmp(str, "true") == 0) {
            value_out = true;
            return true;
        }
        else if (strcasecmp(str, "false") == 0) {
            value_out = false;
            return true;
        }

        long asLong = strtol(str, &end, 0);

        if (*end != 0)
            return err->error("BooleanFormatError", "Specified value is not a valid boolean."), false;

        value_out = (asLong != 0);
        return true;
    }

    static bool toString(IErrorHandler* err, char*& buf, size_t& bufSize, const Bool_t& value) {
        return value ? bufStringSet(err, buf, bufSize, "true", 4)
                : bufStringSet(err, buf, bufSize, "false", 5);
    }
};

template <typename Int_t>
class IntegralReflectionTemplate {
public:
    typedef typename std::numeric_limits<Int_t> Limits;

    static bool fromString(IErrorHandler* err, const char* str, size_t strLen, Int_t& value_out) {
        if (Limits::is_signed) {
            char* end;
            long asLong = strtol(str, &end, 0); // FIXME: actually check for overflow

            if (*end != 0)
                return err->error("IntegerFormatError", "Specified value is not a valid integer."), false;

            if (asLong < (long) Limits::min() || asLong > (long) Limits::max())
                return err->error("IntegerOverflow", "Value is outside the limit for this type."), false;

            value_out = (Int_t) asLong;
            return true;
        }
        else {
            char* end;
            unsigned long asULong = strtoul(str, &end, 0);  // FIXME: actually check for overflow

            if (*end != 0)
                return err->error("IntegerFormatError", "Specified value is not a valid integer."), false;

            if (asULong < (unsigned long) Limits::min() || asULong > (unsigned long) Limits::max())
                return err->error("IntegerOverflow", "Value is outside the limit for this type."), false;

            value_out = (Int_t) asULong;
            return true;
        }
    }

    static bool toString(IErrorHandler* err, char*& buf, size_t& bufSize, const Int_t& value) {
#ifdef _MSC_VER
        if (Limits::is_signed)
            return bufStringPrintf(err, buf, bufSize, "%I64d", (int64_t) value);
        else
            return bufStringPrintf(err, buf, bufSize, "%I64u", (uint64_t) value);
#else
        if (Limits::is_signed)
            return bufStringPrintf(err, buf, bufSize, "%lld", (long long) value);
        else
            return bufStringPrintf(err, buf, bufSize, "%llu", (unsigned long long) value);
#endif
    }
};

template <typename Float_t>
class FloatReflectionTemplate {
public:
    static bool fromString(IErrorHandler* err, const char* str, size_t strLen, Float_t& value_out) {
        char* end;
        double asDouble = strtod(str, &end);

        if (*end != 0)
            return err->error("FloatFormatError", "Specified value is not a valid decimal value."), false;

        value_out = (Float_t) asDouble;
        return true;
    }

    static bool toString(IErrorHandler* err, char*& buf, size_t& bufSize, const Float_t& value) {
        return bufStringPrintf(err, buf, bufSize, "%g", (double) value);
    }
};

#ifndef REFLECTOR_AVOID_STL
class StdStringReflectionTemplate {
public:
    static bool fromString(IErrorHandler* err, const char* str, size_t strLen, std::string& value_out) {
        value_out = str;
        return true;
    }

    static bool toString(IErrorHandler* err, char*& buf, size_t& bufSize, const std::string& value) {
        return bufStringSet(err, buf, bufSize, value.c_str(), value.length());
    }
};
#endif
}
