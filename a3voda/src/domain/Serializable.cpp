//
// Created by sl on 13.02.2019.
//

#include <domain/Serializable.h>

#include "domain/Serializable.h"
#include <iostream>

Serializable::Serializable(string json) : Document() {
    Parse(json.c_str());
}

Serializable::Serializable() : Document() {
    SetObject();
};

Serializable::Serializable(Serializable &other) : Serializable(other.Serialize()) {}

void Serializable::AddMemberOrSetValue(StringRefType name, Value value) {
    RemoveMember(name);
    AddMember(name, value, GetAllocator());
}

void Serializable::AddMemberOrSetValue(StringRefType name, string value) {
    AddMemberOrSetValue(name, Value(value.c_str(), GetAllocator()));
}

void Serializable::AddMemberOrSetValue(StringRefType name, double value) {
    AddMemberOrSetValue(name, Value(value));
}

void Serializable::AddMemberOrSetValue(StringRefType name, int value) {
    AddMemberOrSetValue(name, Value(value));
}

const string Serializable::GetValue(StringRefType name, string defaultValue) const {
    return HasMember(name)?(*this)[name.s].GetString():defaultValue;
}

double Serializable::GetValue(StringRefType name, double defaultValue) const {
    return HasMember(name)?(*this)[name.s].GetDouble():defaultValue;
}

int Serializable::GetValue(StringRefType name, int defaultValue) const {
    return HasMember(name)?(*this)[name.s].GetInt():defaultValue;
}

string Serializable::Serialize() {
    StringBuffer s;
    s.Clear();
    Writer<StringBuffer> writer(s);
    Serializable::Accept(writer);
    return s.GetString();
}

void Serializable::forceSetName(string name) {
    forcedName = move(name);
}

string Serializable::name() const {
    if (!forcedName.empty())
        return forcedName;
    return Notification::name();
}

