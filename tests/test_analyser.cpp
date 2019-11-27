#include "catch2/catch.hpp"

#include "instruction/instruction.h"
#include "tokenizer/tokenizer.h"
#include "analyser/analyser.h"
#include "simple_vm.hpp"

#include <vector>
#include <sstream>



TEST_CASE("Test : Declaration") {
	std::string input =
		"begin\n"
		"const abc = 000123;\n"
		"var ABC = 456;\n"
		"print(abc);\n"
		"print(ABC);\n"
		"end";
	std::stringstream ss;
	ss.str(input);

	miniplc0::Tokenizer tkz(ss);
	auto tks = tkz.AllTokens();
	if (tks.second.has_value()) {
		FAIL();
	}

	miniplc0::Analyser analyser(tks.first);
	auto ins = analyser.Analyse();
	if (ins.second.has_value()) {
		FAIL();
	}

	miniplc0::VM vm(ins.first);
	auto result = vm.Run();
	std::vector<std::int32_t> ans = std::vector<std::int32_t>{ 123, 456 };
	REQUIRE(result == ans);
}

