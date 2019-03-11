//
// Created by sl on 27.02.2019.
//

#include <Utf8ToCp1251Converter.h>

static UTF8Encoding utf8Encoding;
static Windows1251Encoding windows1251Encoding;
static TextConverter cpToUtfConverter(windows1251Encoding, utf8Encoding);;
static TextConverter utfToCpConverter(utf8Encoding, windows1251Encoding);

Utf8ToCp1251Converter::Utf8ToCp1251Converter() {}

string Utf8ToCp1251Converter::cpToUtf(const string &source) {
    string res;
    cpToUtfConverter.convert(source, res);
    return res;
}

string Utf8ToCp1251Converter::utfToCp(const string &source) {
    string res;
    utfToCpConverter.convert(source, res);
    return res;
}

Utf8ToCp1251Converter::~Utf8ToCp1251Converter() {
}
