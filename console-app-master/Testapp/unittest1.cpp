#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "include/catch.hpp"
#include "../counter.h"

TEST_CASE("test(popis)", "test(nazov)") {
	string s = "";	
	REQUIRE(spocitaj<_char>(s) == 0);

	s = "ja som";
	REQUIRE(spocitaj<_char>(s) == 6);

	s = "dnes je pekny den";
	REQUIRE(spocitaj<_word>(s) == 4);

	s = "ides";
	REQUIRE(spocitaj<_word>(s) == 1);

	s = "skola nie je";
	REQUIRE(spocitaj<_line>(s) == 1);

	s = "co je\ndnes\nza\nden";
	REQUIRE(spocitaj<_line>(s) == 4);

}
