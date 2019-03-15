//
// Created by sl on 13.03.19.
//


#define CATCH_CONFIG_MAIN
#include <iostream>
#include <sstream>
#include <catch.hpp>
#include <Serializable.h>

#define STRING_PARAM_NAME      "stringParam"
#define STRING_PARAM_OLD_VALUE "qwertyuiop"
#define STRING_PARAM_NEW_VALUE "asdfghjklm"

#define INT_PARAM_NAME         "intParam"
#define INT_PARAM_OLD_VALUE    123456789
#define INT_PARAM_NEW_VALUE    987654321

#define DOUBLE_PARAM_NAME      "doubleParam"
#define DOUBLE_PARAM_OLD_VALUE 3.14159
#define DOUBLE_PARAM_NEW_VALUE 2.71828

#define EMPTY_JSON "{}"

using namespace std;

SCENARIO( "Serializable can parse JSON", "[serializable]" ) {

    GIVEN( "new Serializable" ) {
        Serializable s;

        REQUIRE(s.Serialize() == EMPTY_JSON);
        REQUIRE( s.GetValue(STRING_PARAM_NAME, STRING_PARAM_OLD_VALUE) == STRING_PARAM_OLD_VALUE );
        REQUIRE( s.GetValue(INT_PARAM_NAME, INT_PARAM_OLD_VALUE) == INT_PARAM_OLD_VALUE );
        REQUIRE( s.GetValue(DOUBLE_PARAM_NAME, DOUBLE_PARAM_OLD_VALUE) == DOUBLE_PARAM_OLD_VALUE );

        WHEN( "it parses JSON" ) {
            ostringstream jsonStream;
            jsonStream << "{"
                    << "\"" << STRING_PARAM_NAME << "\"" << ":" << "\"" << STRING_PARAM_NEW_VALUE << "\"" << ","
                    << "\"" << INT_PARAM_NAME    << "\"" << ":" << INT_PARAM_NEW_VALUE                    << ","
                    << "\"" << DOUBLE_PARAM_NAME << "\"" << ":" << DOUBLE_PARAM_NEW_VALUE
            << "}";
            s.Parse(jsonStream.str().c_str());

            THEN( "value of parameters changes" ) {
                REQUIRE( s.GetValue(STRING_PARAM_NAME, STRING_PARAM_OLD_VALUE) == STRING_PARAM_NEW_VALUE );
                REQUIRE( s.GetValue(INT_PARAM_NAME, INT_PARAM_OLD_VALUE) == INT_PARAM_NEW_VALUE );
            }
        }
    }
}

SCENARIO( "Serializable can serialize JSON", "[serializable]" ) {

    GIVEN( "new Serializable" ) {
        Serializable s;

        REQUIRE(s.Serialize() == EMPTY_JSON);
        REQUIRE( s.GetValue(STRING_PARAM_NAME, STRING_PARAM_OLD_VALUE) == STRING_PARAM_OLD_VALUE );
        REQUIRE( s.GetValue(INT_PARAM_NAME, INT_PARAM_OLD_VALUE) == INT_PARAM_OLD_VALUE );
        REQUIRE( s.GetValue(DOUBLE_PARAM_NAME, DOUBLE_PARAM_OLD_VALUE) == DOUBLE_PARAM_OLD_VALUE );

        WHEN( "it's parameters are changed" ) {
            s.AddMemberOrSetValue(STRING_PARAM_NAME, STRING_PARAM_NEW_VALUE);
            s.AddMemberOrSetValue(INT_PARAM_NAME, INT_PARAM_NEW_VALUE);
            s.AddMemberOrSetValue(DOUBLE_PARAM_NAME, DOUBLE_PARAM_NEW_VALUE);

            THEN( "their are serialized to corresponding JSON" ) {
                ostringstream jsonStream;
                jsonStream << "{"
                           << "\"" << STRING_PARAM_NAME << "\"" << ":" << "\"" << STRING_PARAM_NEW_VALUE << "\"" << ","
                           << "\"" << INT_PARAM_NAME    << "\"" << ":" << INT_PARAM_NEW_VALUE                    << ","
                           << "\"" << DOUBLE_PARAM_NAME << "\"" << ":" << DOUBLE_PARAM_NEW_VALUE
                           << "}";
                REQUIRE(s.Serialize() == jsonStream.str());
            }
        }
    }
}