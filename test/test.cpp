
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "characterType.cpp"

TEST_CASE("testing functions") {
    CHECK(isBracket('(') == true);
    CHECK(isBracket('a') == false);
}

