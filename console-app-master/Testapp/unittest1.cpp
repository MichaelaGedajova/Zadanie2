#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "include/catch.hpp"
#include "../counter.h"

TEST_CASE("test(popis)", "test(nazov)") {
	string s = "";	
	REQUIRE(VratDlzkuZnaku(s) == 0);

	s = "ja som";
	REQUIRE(VratDlzkuZnaku(s) == 6);

	s = "dnes je pekny den";
	REQUIRE(VratPocetSlov(s) == 4);

	s = "";
	REQUIRE(VratPocetSlov(s) == 0);

	s = "skola\nskola";
	REQUIRE(VratPocetRiadkov(s) == 2);

	s = "co je\ndnes\nza\nden";
	REQUIRE(VratPocetRiadkov(s) == 4);

}
