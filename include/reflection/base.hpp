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

#include <cassert>
#include <cstdarg>
#include <cstddef>
#include <cstdint>

#include "bufstring.hpp"

// FUNCTION OVERLOAD MATCHING
// http://stackoverflow.com/a/1092724/2524350

// perfect match (char->char)
#define REFL_MATCH_0 char

// match with promotion (char->int)
#define REFL_MATCH_1 int

//
#define REFL_MATCH ((char) 0)

namespace reflection {  // UUID('c3549467-1615-4087-9829-176a2dc44b76')
class IErrorHandler;
}

namespace serialization {
using reflection::IErrorHandler;

class IReader {
public:
    virtual bool read(IErrorHandler* err, void* buffer, size_t count) = 0;
};

class IWriter {
public:
    virtual bool write(IErrorHandler* err, const void* buffer, size_t count) = 0;
};
}

namespace reflection {

enum {
    FIELD_STATE = 1,
    FIELD_CONFIG = 2,
    FIELD_DEPENDENCY = 4,
    FIELD_RESOURCE = 8,
    FIELD_MANDATORY = 256
};

struct UUID_t {
    uint32_t uuid[4];

    bool operator < (const UUID_t& other) const { return memcmp(uuid, other.uuid, sizeof(uuid)) < 0; }
    bool operator == (const UUID_t& other) const { return memcmp(uuid, other.uuid, sizeof(uuid)) == 0; }

    int toString(char buffer[37]) const {
        return snprintf(buffer, 37, "%08x-%04x-%04x-%04x-%04x%08x",
                (unsigned int)(uuid[0]), (unsigned int)(uuid[1] >> 16), (unsigned int)(uuid[1] & 0xffff),
                (unsigned int)(uuid[2] >> 16), (unsigned int)(uuid[2] & 0xffff), (unsigned int)(uuid[3]));
    }
};

class IErrorHandler {
public:
    virtual void error(const char* errorCode, const char* description) = 0;

    void errorf(const char* errorCode, const char* format, ...) {
        char* buf = nullptr;
        size_t bufSize = 0;
        AllocGuard guard(buf);

        va_list args;

        va_start(args, format);
        int length = vsnprintf(nullptr, 0, format, args);
        va_end(args);

        assert(length >= 0);

        size_t newBufSize = length + 1;

        assert(ensureSize(this, buf, bufSize, newBufSize));

        va_start(args, format);
        length = vsnprintf(buf, bufSize, format, args);
        va_end(args);

        assert(length >= 0);

        this->error(errorCode, buf);
    }

    void allocationError(const char* functionName) { this->errorf("AllocationError", "Memory allocation failed in `%s`.", functionName); }
    void unexpectedEndOfInput(const char* fileName) { this->errorf("UnexpectedEOF", "Unexpected end of input in `%s`.", fileName); }
    void notImplemented(const char* functionName) { this->errorf("NotImplemented", "Function `%s` is not implemented.", functionName); }
};

// general class for type reflection
class ITypeReflection {
public:
    virtual bool isPolymorphic() = 0;
    virtual const char* staticTypeName() = 0;
    virtual const char* typeName(const void* p_value) = 0;
    virtual const UUID_t* uuidOrNull(const void* p_value) = 0;

    virtual bool serialize(IErrorHandler* err, serialization::IWriter* writer, const void* p_value) = 0;
    virtual bool deserialize(IErrorHandler* err, serialization::IReader* reader, void* p_value) = 0;
    virtual bool serializeTypeInformation(IErrorHandler* err, serialization::IWriter* writer, const void* p_value) = 0;
    virtual bool verifyTypeInformation(IErrorHandler* err, serialization::IReader* reader, void* p_value) = 0;

    virtual bool setFromString(IErrorHandler* err, const char* str, size_t strLen,
            void* p_value) = 0;
    virtual bool toString(IErrorHandler* err, char*& buf, size_t& bufSize, uint32_t fieldMask,
            const void* p_value) = 0;
};

// reflectable class field
struct Field_t {
    const char* name;                       // statically allocated field name
    void* (*fieldGetter)(const void*);      // instance pointer -> field pointer (no, offsetof won't do)
    uint32_t systemFlags;                   // built-in field flags
    uint32_t flags;                         // user-specified field flags
    const char* params;                     // user-specified field properties or nullptr

    union {
        ITypeReflection* refl;              // field type information
        const UUID_t* uuid;                 // dependency uuid
    };
};

// set of all reflectable fields in a class not including base class(es)
struct FieldSet_t {
    const char* className;
    Field_t const* fields;                  // fields for this class
    size_t numFields;                       // number of fields for this class

    FieldSet_t const* baseClassFields;      // base class fields
    void* (*derivedPtrToBasePtr)(void*);    // helper to convert derived* to base* (which may or may not differ)
};

template <class C>
struct ReflectionForType2;

template <class C>
ITypeReflection* reflectionForType(C);

// If you get an error about "use of undefined type ReflectionForType2<C>", you need to include <reflection/class.hpp>
template <class C>
ITypeReflection* reflectionForType2() { return ReflectionForType2<C>::reflectionForType2(); }

struct ReflectedValue_t {
    ITypeReflection* refl;
    void* p_value;

    ReflectedValue_t()
    {
        refl = nullptr;
        p_value = nullptr;
    }

    ReflectedValue_t(const ReflectedValue_t& other)
            : refl(other.refl), p_value(other.p_value)
    {
    }

    template <typename T>
    ReflectedValue_t(T& value)
    {
        refl = reflectionForType(value);
        p_value = &value;
    }
};
}
