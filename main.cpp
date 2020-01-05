#include "argparse.hpp"
#include "fmt/core.h"

#include "tokenizer/tokenizer.h"
#include "analyser/analyser.h"
#include "fmts.hpp"

#include <iostream>
#include <fstream>
#include<bitset>

std::vector<miniplc0::Token> _tokenize(std::istream& input) {
	miniplc0::Tokenizer tkz(input);
	auto p = tkz.AllTokens();
	if (p.second.has_value()) {
		fmt::print(stderr, "Tokenization error: {}\n", p.second.value());
		exit(2);
	}
	return p.first;
}

void Tokenize(std::istream& input, std::ostream& output) {
	auto v = _tokenize(input);
	for (auto& it : v)
		output << fmt::format("{}\n", it);
	return;
}

void Analyse(std::istream& input, std::ostream& output) {
	auto tks = _tokenize(input);
	miniplc0::Analyser analyser(tks);
	auto p = analyser.Analyse(output);
	if (p.second.has_value()) {
		fmt::print(stderr, "Syntactic analysis error: {}\n", p.second.value());
		exit(2);
	}
	int32_t index = 0;
	auto v = p.first;
	output << ".constants:\n";

	for (auto& it : analyser._constants_list) {
		output << index << " " << fmt::format("{}\n", it);
		index++;
	}
	index = 0;
	output << ".start:\n";
	for (auto& it : analyser._start) {
		output << index << " " << fmt::format("{}\n", it);
		index++;
	}
	index = 0;
	output << ".functions:\n";
	for (auto& it : analyser._functions_list) {
		output << index << " " << index << " " << fmt::format("{}\n", it);
		index++;
	}
	index = 0;
	for (int j = 0; j < analyser._functions_list.size(); j++)
	{
		output << ".F" << j << ":\n";
		index = 0;
		for (auto& it : analyser._instructions_list[j]) {
			output << index << " " << fmt::format("{}\n", it);
			index++;
		}
	}


	return;
}
void trans(int* a, int num, std::ostream& output) {
	if (num == 1)
	{
		output.write(reinterpret_cast<char*>(a), 1);


	}
	if (num == 2)
	{
		char* c = reinterpret_cast<char*>(a);
		char b[2];
		b[0] = c[1];
		b[1] = c[0];
		output.write(b, 2);
	}
	if (num == 4)
	{
		char* c = reinterpret_cast<char*>(a);
		char b[4];
		b[0] = c[3];
		b[1] = c[2];
		b[2] = c[1];
		b[3] = c[0];
		output.write(b, 4);
	}

}
void AnalyseC(std::istream& input, std::ostream& output) {
	auto tks = _tokenize(input);
	miniplc0::Analyser analyser(tks);
	auto p = analyser.Analyse(output);
	if (p.second.has_value()) {
		fmt::print(stderr, "Syntactic analysis error: {}\n", p.second.value());
		exit(2);
	}
	int32_t index = 0;
	int32_t magic = 0x43303A29;
	int32_t version = 1;
	auto v = p.first;
	std::string a = "main";
	auto b = 0x1636;
	//output << a ;
	char* d = reinterpret_cast<char*>(&b);


	trans(&magic, 4, output);
	trans(&version, 4, output);
	int32_t funsize = analyser._functions_list.size();
	int32_t consize = analyser._constants_list.size() + funsize;

	trans(&(consize), 2, output);
	index = 0;
	for (auto& it : analyser._functions_list) {
		int32_t type = 0;
		int32_t stringlength = it.getname().length();
		std::string stringself = it.getname();

		trans(&(type), 1, output);
		trans(&(stringlength), 2, output);
		output << stringself;
		index++;
	}
	index = 0;
	for (auto& it : analyser._constants_list) {
		int32_t consize = analyser._constants_list[index].gettype();
		int32_t stringlength = analyser._constants_list[index].getvalue().length();
		std::string stringself = analyser._constants_list[index].getvalue();

		trans(&(consize), 1, output);
		trans(&(stringlength), 2, output);
		output << stringself;
		index++;
	}
	index = 0;
	int32_t startsize = analyser._start.size();

	trans((&startsize), 2, output);
	for (auto& it : analyser._start) {
		miniplc0::Operation op = it.GetOperation();
		int32_t op0x = analyser.get0x(op);
		trans((&op0x), 1, output);
		int32_t opx = it.GetX();
		int32_t opy = it.GetY();

		if (analyser.getparasize(op) == 1)
		{
			trans(&(opx), 1, output);
		}
		else if (analyser.getparasize(op) == 2)
		{
			trans(&(opx), 2, output);

		}
		else if (analyser.getparasize(op) == 4)
		{
			trans(&(opx), 4, output);

		}
		else if (analyser.getparasize(op) == 6)
		{
			trans(&(opx), 2, output);
			trans(&(opy), 4, output);

		}

		index++;
	}
	index = 0;

	trans(&funsize, 2, output);

	for (auto& it : analyser._functions_list) {
		trans(&index, 2, output);
		int32_t paralen = it.getparasize();
		trans(&paralen, 2, output);
		int32_t level = 1;
		trans(&level, 2, output);
		int32_t inssize = analyser._instructions_list[index].size();
		trans(&inssize, 2, output);
		for (auto& it : analyser._instructions_list[index]) {
			miniplc0::Operation op = it.GetOperation();
			int32_t op0x = analyser.get0x(op);
			trans((&op0x), 1, output);
			int32_t opx = it.GetX();
			int32_t opy = it.GetY();

			if (analyser.getparasize(op) == 1)
			{
				trans(&(opx), 1, output);
			}
			else if (analyser.getparasize(op) == 2)
			{
				trans(&(opx), 2, output);

			}
			else if (analyser.getparasize(op) == 4)
			{
				trans(&(opx), 4, output);

			}
			else if (analyser.getparasize(op) == 6)
			{
				trans(&(opx), 2, output);
				trans(&(opy), 4, output);

			}

		}
		index++;
	}

	return;
}

int main(int argc, char** argv) {
	argparse::ArgumentParser program("c0");
	program.add_argument("input")
		.help("speicify the file to be compiled.");
	program.add_argument("-t")
		.default_value(false)
		.implicit_value(true)
		.help("perform tokenization for the input file.");
	program.add_argument("-s")
		.default_value(false)
		.implicit_value(true)
		.help("perform syntactic analysis for the input file.");
	program.add_argument("-c")
		.default_value(false)
		.implicit_value(true)
		.help("output .o.");
	program.add_argument("-o", "--output")
		.required()
		.default_value(std::string("-"))
		.help("specify the output file.");

	try {
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error & err) {
		fmt::print(stderr, "{}\n\n", err.what());
		program.print_help();
		exit(2);
	}

	auto input_file = program.get<std::string>("input");
	auto output_file = program.get<std::string>("--output");
	std::istream* input;
	std::ostream* output;
	std::ifstream inf;
	std::ofstream outf;
	if (input_file != "-") {
		inf.open(input_file, std::ios::in);
		if (!inf) {
			fmt::print(stderr, "Fail to open {} for reading.\n", input_file);
			exit(2);
		}
		input = &inf;
	}
	else
		input = &std::cin;
	if (output_file != "-") {
		if (program["-c"] == true)outf.open(output_file, std::ios::binary | std::ios::trunc);
		else
		{
			outf.open(output_file, std::ios::out | std::ios::trunc);
		}

		if (!outf) {
			fmt::print(stderr, "Fail to open {} for writing.\n", output_file);
			exit(2);
		}
		output = &outf;
	}
	else {
		if (program["-c"] == true)outf.open("out", std::ios::binary | std::ios::trunc);
		else
		{
			outf.open("out", std::ios::out | std::ios::trunc);
		}

		if (!outf) {
			fmt::print(stderr, "Fail to open {} for writing.\n", "out");
			exit(2);
		}
		output = &outf;
	}
	if (program["-s"] == true && program["-c"] == true) {
		fmt::print(stderr, "You can only perform .c or .s at one time.");
		exit(2);
	}
	if (program["-t"] == true) {
		Tokenize(*input, *output);
	}
	else if (program["-s"] == true) {
		Analyse(*input, *output);
	}
	else if (program["-c"] == true) {
		AnalyseC(*input, *output);
	}
	else {
		program.print_help();
		//fmt::print(stderr, "You must choose tokenization or syntactic analysis.");
		exit(2);
	}
	return 0;
}