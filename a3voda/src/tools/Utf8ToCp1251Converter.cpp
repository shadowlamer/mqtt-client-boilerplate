/**
 * @file Utf8ToCp1251Converter.cpp
 * @brief Реализация класса Utf8ToCp1251Converter.
 * @author Vadim Cherenev
 * @date 27.02.2019
 * @copyright MIT License
 */

#include <Utf8ToCp1251Converter.h>

static UTF8Encoding utf8Encoding;
static Windows1251Encoding windows1251Encoding;
static TextConverter cpToUtfConverter(windows1251Encoding, utf8Encoding);;
static TextConverter utfToCpConverter(utf8Encoding, windows1251Encoding);

Utf8ToCp1251Converter::Utf8ToCp1251Converter() {}

/**
 * @brief Переводит строку из кодировки utf8 в cp1251
 * @param source Строка в кодировке utf8.
 * @return Строка в кодировке cp1251.
 */
string Utf8ToCp1251Converter::cpToUtf(const string &source) {
    string res;
    cpToUtfConverter.convert(source, res);
    return res;
}

/**
 * @brief Переводит строку из кодировки cp1251 в utf8
 * @param source Строка в кодировке cp1251.
 * @return Строка в кодировке utf8.
 */
string Utf8ToCp1251Converter::utfToCp(const string &source) {
    string res;
    utfToCpConverter.convert(source, res);
    return res;
}

Utf8ToCp1251Converter::~Utf8ToCp1251Converter() {
}
