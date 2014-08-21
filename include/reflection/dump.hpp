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

#include "api.hpp"
#include "basic_types.hpp"
#include "serializer.hpp"

namespace reflection {  // UUID('c3549467-1615-4087-9829-176a2dc44b76')
using namespace serialization;

class ISeekBack {
public:
    virtual void seekBack(long amount) = 0;
};

class ISchemaProvider {
public:
    virtual IReader* openClassSchemaOrNull(const char* className) = 0;
    virtual void closeClassSchema(IReader* reader) = 0;
};

static bool dumpValue(Tag_t tag, IReader* reader, ISeekBack* sb, ISchemaProvider* sp = nullptr, int offset = 0);
static bool dumpTaggedValue(IReader* reader, ISeekBack* sb, ISchemaProvider* sp = nullptr, int offset = 0);

static const char* getTypeName(Tag_t tag) {
    switch (tag) {
        case TAG_VOID:          return "void";
        case TAG_BOOL:          return "bool";
        case TAG_CHAR:          return "char";
        case TAG_SMVINT:        return "int_smv";
        case TAG_REAL32:        return "float";
        case TAG_REAL64:        return "double";

        case TAG_UTF8:          return "utf8";
        case TAG_TYPED_ARRAY:   return "array_typed";
        case TAG_FIXED_ARRAY:   return "array_fixed";

        case TAG_CLASS:         return "class";
        case TAG_CLASS_SCHEMA:  return "class_schema";

        default:                return nullptr;
    }
}

static void doOffset(int offset) {
    for (int i = 0; i < offset; i++)
        printf("    ");
}

template <typename T>
bool dumpDeserialized(IReader* reader) {
    T value;

    if (!reflectDeserialize(value, reader))
        return false;

    std::string s = reflectToString(value);
    printf("\"%s\"", s.c_str());

    return true;
}

static bool dumpString(IReader* reader) {
    BufString_t value;

    if (!Serializer<BufString_t>::deserialize(err, reader, value))
        return false;

    printf("\"%s\"", value.buf);

    return true;
}

static bool dumpTaggedClass(IReader* reader, ISeekBack* sb, ISchemaProvider* sp = nullptr, int offset = 0) {
    BufString_t className, str;
    uint32_t numFields;

    if (!Serializer<BufString_t>::deserialize(err, reader, className)
            || !Serializer<uint32_t>::deserialize(err, reader, numFields))
        return false;

    printf("`%s`", className.buf);

    IReader* schemaReader = (sp == nullptr) ? nullptr : sp->openClassSchemaOrNull(className.buf);

    if (schemaReader == nullptr)
        printf(" (schema not available)");

    printf(" {\n");
    offset++;

    if (schemaReader != nullptr) {
        if (!checkTag(err, schemaReader, TAG_CLASS_SCHEMA))
            return false;

        if (/*!Serializer<BufString_t>::deserialize(err, schemaReader, className)
                ||*/ !Serializer<uint32_t>::deserialize(err, schemaReader, numFields))
            return false;

        // TODO: check if values as expected
    }

    for (uint32_t i = 0; i < numFields; i++) {
        doOffset(offset);

        if (schemaReader != nullptr) {
            Tag_t tag;

            if (!Serializer<BufString_t>::deserialize(err, schemaReader, className)
                    || !Serializer<BufString_t>::deserialize(err, schemaReader, str)
                    || !schemaReader->read(err, &tag, sizeof(tag)))
                return false;

            printf("`%s::%s` => ", className.buf, str.buf);

            if (tag == TAG_CLASS) {
                if (!Serializer<BufString_t>::deserialize(err, schemaReader, className))
                    return false;

                //printf("(class `%s`) ", className.buf);
            }
        }

        if (!dumpTaggedValue(reader, sb, sp, offset))
            return false;

        printf("\n");
    }

    if (schemaReader != nullptr)
        sp->closeClassSchema(schemaReader);

    offset--;
    doOffset(offset);
    printf("}");

    return true;
}

static bool dumpClass(IReader* reader, ISeekBack* sb, const char* className_, ISchemaProvider* sp, int offset = 0) {
    BufString_t className, str;
    uint32_t numFields;

    bufStringSet(err, className.buf, className.bufSize, className_, strlen(className_));

    printf("`%s`", className.buf);

    IReader* schemaReader = (sp == nullptr) ? nullptr : sp->openClassSchemaOrNull(className.buf);

    if (schemaReader == nullptr) {
        printf(" (schema not available)\n");
        return false;
    }

    printf(" {\n");
    offset++;

    if (!Serializer<uint32_t>::deserialize(err, schemaReader, numFields))
        return false;

    // TODO: check if values as expected

    for (uint32_t i = 0; i < numFields; i++) {
        doOffset(offset);

        Tag_t tag;

        if (!Serializer<BufString_t>::deserialize(err, schemaReader, className)
                || !Serializer<BufString_t>::deserialize(err, schemaReader, str)
                || !schemaReader->read(err, &tag, sizeof(tag)))
            return false;

        printf("`%s::%s` => ", className.buf, str.buf);

        if (tag == TAG_CLASS) {
            if (!Serializer<BufString_t>::deserialize(err, schemaReader, className))
                return false;

            if (!dumpClass(reader, sb, className.buf, sp, offset))
                return false;
        }
        else if (!dumpValue(tag, reader, sb, sp, offset))
            return false;

        printf("\n");
    }

    sp->closeClassSchema(schemaReader);

    offset--;
    doOffset(offset);
    printf("}");

    return true;
}

static bool dumpClassSchema(IReader* reader, int offset = 0) {
    BufString_t className, str;
    uint32_t numFields;

    if (/*!Serializer<BufString_t>::deserialize(err, reader, className)
            ||*/ !Serializer<uint32_t>::deserialize(err, reader, numFields))
        return false;

    printf(/*"`%s` "*/"{\n"/*, className.buf*/);
    offset++;

    for (uint32_t i = 0; i < numFields; i++) {
        doOffset(offset);

        Tag_t tag;

        if (!Serializer<BufString_t>::deserialize(err, reader, className)
                || !Serializer<BufString_t>::deserialize(err, reader, str)
                || !reader->read(err, &tag, sizeof(tag)))
            return false;

        printf("`%s::%s`", className.buf, str.buf);

        if (tag == TAG_CLASS) {
            if (!Serializer<BufString_t>::deserialize(err, reader, className))
                return false;

            printf("\t=> class `%s`", className.buf);
        }
        else {
            const char* typeName = getTypeName(tag);

            if (typeName != nullptr)
                printf("\t=> %s", typeName);
        }

        printf("\n");
    }

    offset--;
    doOffset(offset);
    printf("}");

    return true;
}

static bool dumpTaggedValue(IReader* reader, ISeekBack* sb, ISchemaProvider* sp, int offset) {
    Tag_t tag;

    if (!reader->read(err, &tag, sizeof(tag)))
        return false;

    const char* typeName = getTypeName(tag);

    if (typeName != nullptr)
        printf("%s\t", typeName);

    switch (tag) {
        case TAG_VOID: printf("\"void\""); return true;
        case TAG_BOOL: sb->seekBack(1); return dumpDeserialized<bool>(reader);
        case TAG_CHAR: sb->seekBack(1); return dumpDeserialized<unsigned char>(reader);
        case TAG_SMVINT: sb->seekBack(1); return dumpDeserialized<int64_t>(reader);

        case TAG_UTF8: sb->seekBack(1); return dumpString(reader);

        case TAG_CLASS: return dumpTaggedClass(reader, sb, sp, offset);
        case TAG_CLASS_SCHEMA: return dumpClassSchema(reader, offset);

        default: err->errorf("UnknownType", "Unrecognized tag %02X.\n", tag); return false;
    }

    return false;
}

static bool dumpValue(Tag_t tag, IReader* reader, ISeekBack* sb, ISchemaProvider* sp, int offset) {
    switch (tag) {
        case TAG_VOID: printf("\"void\""); return true;
        case TAG_BOOL: return dumpDeserialized<bool>(reader);
        case TAG_CHAR: return dumpDeserialized<unsigned char>(reader);
        case TAG_SMVINT: return dumpDeserialized<int64_t>(reader);

        case TAG_UTF8: return dumpString(reader);

        case TAG_CLASS_SCHEMA: return dumpClassSchema(reader, offset);

        default: err->errorf("UnknownType", "Unrecognized tag %02X.\n", tag); return false;
    }

    return false;
}
}
