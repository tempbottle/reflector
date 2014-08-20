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

#include <reflection/api.hpp>
#include <reflection/magic.hpp>

#include <reflection/basic_types.hpp>
#include <reflection/class.hpp>

#include <map>

using namespace std;

namespace serialization {
// Override postSerializationHook for all types using a stronger match (REFL_MATCH_0)
template <class T>
int postSerializationHook(IErrorHandler* err, IWriter* writer, const T& value, int serializationResult, REFL_MATCH_0) {
    printf(".");
    return -1;
}

// Override postSerializationHook for int32_t using a weak match but a specialized template (will take precedence)
template <>
int postSerializationHook(IErrorHandler* err, IWriter* writer, const int32_t& value, int serializationResult, REFL_MATCH_1) {
    printf("!");
    return -1;
}

// Stronger matching won't pick up for these ones - we need to specialize the template - WTF?!
template <>
int preInstanceSerializationHook(IErrorHandler* err, IWriter* writer, const char* className,
        const reflection::ReflectedFields& fields, REFL_MATCH_1) {
    printf("(%s:", className);
    return -1;
}

template <>
int postInstanceSerializationHook(IErrorHandler* err, IWriter* writer, const char* className,
        const reflection::ReflectedFields& fields, int serializationResult, REFL_MATCH_1) {
    printf(")");
    return -1;
}
}

struct DataPacket {
    string name;
    int32_t offset;
    int32_t length;

    REFL_BEGIN("DataPacket", 1)
        REFL_FIELD(name)
        REFL_FIELD(offset)
        REFL_FIELD(length)
    REFL_END
};

struct SpecialDataPacket : DataPacket {
    SpecialDataPacket() {
        name = reflection::reflectClassName(*this);
    }

    REFL_BEGIN_EXTENDS("SpecialDataPacket", 1, DataPacket)
    REFL_END
};

class Actor {
public:
    Actor(string name) : name(name) {
        health = 100;
    }

    string name;
    int health;

    REFL_BEGIN_VIRTUAL("Actor", 1)
        REFL_FIELD(name)
        REFL_FIELD(health)
    REFL_END
};

class Weapon {
public:
    string name;
    int attack;
    int agility_modifier;

    REFL_BEGIN_VIRTUAL("Weapon", 1)
        REFL_FIELD(name)
        REFL_FIELD(attack)
        REFL_FIELD(agility_modifier)
    REFL_END
};

class Sword : public Weapon {
public:
    Sword() {
        name = "Basic Sword";
        attack = 50;
        agility_modifier = -200;
        enhanced = true;
    }

    bool enhanced;

    REFL_BEGIN_VIRTUAL_EXTENDS("Sword", 1, Weapon)
        REFL_FIELD(enhanced)
    REFL_END
};

class GameCharacter: public Actor {
public:
    GameCharacter(string name) : Actor(name) {
        //weapon = new Sword;
    }

    //Weapon* weapon;
    Sword weapon;

    REFL_BEGIN_VIRTUAL_EXTENDS("GameCharacter", 1, Actor)
        REFL_FIELD(weapon)
    REFL_END
};

class MyReader: public serialization::IReader {
public:
    MyReader(FILE* file) : file(file) {}

    virtual bool read(reflection::IErrorHandler* err, void* buffer, size_t count) override {
        if (fread(buffer, 1, count, file) != count) {
            if (feof(file))
                return err->error("UnexpectedEOF", "Unexpected end of file."), false;
            else
                return err->error("IOError", "Failed to read file."), false;
        }

        return true;
    }

    FILE* file;
};

class MyWriter: public serialization::IWriter {
public:
    MyWriter(FILE* file) : file(file) {}

    virtual bool write(reflection::IErrorHandler* err, const void* buffer, size_t count) override {
        if (fwrite(buffer, 1, count, file) != count) {
            return err->error("IOError", "Failed to write to file."), false;
        }

        return true;
    }

    FILE* file;
};

template <typename C>
static void dumpSchema() {
    const char* className = reflection::versionedNameOfClass<C>();
    auto fields = reflection::reflectFieldsStatic<C>();

    string path = string("schemas/") + className + ".class_schema";
    FILE* file = fopen(path.c_str(), "wb");
    assert(file != nullptr);

    MyWriter wr(file);
    serialization::InstanceSerializer<C>::serializeSchema(reflection::err, &wr, className, fields);

    fclose(file);
}

int main(int argc, char** argv) {
    DataPacket packet = { "importantData", 1000, 200 };
    reflection::reflectPrint(packet);

    Actor* chr = new GameCharacter("kokos");

    reflection::reflectPrint(*chr);

    string asString = reflection::reflectToString(*chr);
    printf("chr asString: %s\n", asString.c_str());
    //reflection::reflectFromString(*chr, serialized);

    FILE* file = fopen("chr.class", "wb");
    assert(file != nullptr);

    MyWriter wr(file);
    reflection::reflectSerialize(*chr, &wr);
    printf("\n");

    fclose(file);

    dumpSchema<Sword>();
    dumpSchema<Actor>();
    dumpSchema<GameCharacter>();
}

#include <reflection/default_error_handler.cpp>
