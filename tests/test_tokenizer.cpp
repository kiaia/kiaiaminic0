#include "catch2/catch.hpp"
#include "tokenizer/tokenizer.h"
#include "fmt/core.h"

#include <sstream>
#include <vector>



TEST_CASE("Test : Invalid characters.") {
	std::string input =
		R"(!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~)";
	std::stringstream ss;
	ss.str(input);

	miniplc0::Tokenizer tkz(ss);
	auto result = tkz.AllTokens();
	if (result.second.has_value()) {
		SUCCEED();
	}
	else {
		FAIL();
	}
}

