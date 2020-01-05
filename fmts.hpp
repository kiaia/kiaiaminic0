#include "fmt/core.h"
#include "tokenizer/tokenizer.h"
#include "analyser/analyser.h"

namespace fmt {
	template<>
	struct formatter<miniplc0::ErrorCode> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template <typename FormatContext>
		auto format(const miniplc0::ErrorCode& p, FormatContext& ctx) {
			std::string name;
			switch (p) {
			case miniplc0::ErrNoFunciton:
				name = "no funciotn";
				break;
			case miniplc0::ErrNeedReturnValue:
				name = "no return";
				break;
			case miniplc0::ErrVoid:
				name = "no void";
				break;
			case miniplc0::ErrNeedLeftBracket:
				name = "ErrNeedLeftBracket";
				break;
			case miniplc0::ErrNeedRightCurly:
				name = "NeedRightCurly";
				break;
			case miniplc0::ErrNeedLeftCurly:
				name = "NeedLeftCurly";
				break;

			case miniplc0::ErrType:
				name = "ErrType";
				break;
			case miniplc0::ErrNoType:
				name = "ErrNoType";
				break;
			case miniplc0::ErrNoError:
				name = "No error.";
				break;
			case miniplc0::ErrStreamError:
				name = "Stream error.";
				break;
			case miniplc0::ErrEOF:
				name = "EOF";
				break;
			case miniplc0::ErrInvalidInput:
				name = "The input is invalid.";
				break;
			case miniplc0::ErrInvalidIdentifier:
				name = "Identifier is invalid";
				break;
			case miniplc0::ErrIntegerOverflow:
				name = "The integer is too big(int64_t).";
				break;
			case miniplc0::ErrNoBegin:
				name = "The program should start with 'begin'.";
				break;
			case miniplc0::ErrNoEnd:
				name = "The program should end with 'end'.";
				break;
			case miniplc0::ErrNeedIdentifier:
				name = "Need an identifier here.";
				break;
			case miniplc0::ErrConstantNeedValue:
				name = "The constant need a value to initialize.";
				break;
			case miniplc0::ErrNoSemicolon:
				name = "Zai? Wei shen me bu xie fen hao.";
				break;
			case miniplc0::ErrInvalidVariableDeclaration:
				name = "The declaration is invalid.";
				break;
			case miniplc0::ErrIncompleteExpression:
				name = "The expression is incomplete.";
				break;
			case miniplc0::ErrNotDeclared:
				name = "The variable or constant must be declared before being used.";
				break;
			case miniplc0::ErrAssignToConstant:
				name = "Trying to assign value to a constant.";
				break;
			case miniplc0::ErrDuplicateDeclaration:
				name = "The variable or constant has been declared.";
				break;
			case miniplc0::ErrNotInitialized:
				name = "The variable has not been initialized.";
				break;
			case miniplc0::ErrInvalidAssignment:
				name = "The assignment statement is invalid.";
				break;
			case miniplc0::ErrInvalidPrint:
				name = "The output statement is invalid.";
				break;
			}
			return format_to(ctx.out(), name);
		}
	};

	template<>
	struct formatter<miniplc0::CompilationError> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template <typename FormatContext>
		auto format(const miniplc0::CompilationError& p, FormatContext& ctx) {
			return format_to(ctx.out(), "Line: {} Column: {} Error: {}", p.GetPos().first, p.GetPos().second, p.GetCode());
		}
	};
}

namespace fmt {
	template<>
	struct formatter<miniplc0::Token> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template <typename FormatContext>
		auto format(const miniplc0::Token& p, FormatContext& ctx) {
			return format_to(ctx.out(),
				"Line: {} Column: {} Type: {} Value: {}",
				p.GetStartPos().first, p.GetStartPos().second, p.GetType(), p.GetValueString());
		}
	};

	template<>
	struct formatter<miniplc0::TokenType> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template <typename FormatContext>
		auto format(const miniplc0::TokenType& p, FormatContext& ctx) {
			std::string name;
			switch (p) {
			case miniplc0::NULL_TOKEN:
				name = "NullToken";
				break;
			case miniplc0::UNSIGNED_INTEGER:
				name = "UnsignedInteger";
				break;
			case miniplc0::IDENTIFIER:
				name = "Identifier";
				break;
			case miniplc0::BEGIN:
				name = "Begin";
				break;
			case miniplc0::END:
				name = "End";
				break;
			case miniplc0::VAR:
				name = "Var";
				break;
			case miniplc0::CONST:
				name = "Const";
				break;
			case miniplc0::PRINT:
				name = "Print";
				break;
			case miniplc0::PLUS_SIGN:
				name = "PlusSign";
				break;
			case miniplc0::MINUS_SIGN:
				name = "MinusSign";
				break;
			case miniplc0::MULTIPLICATION_SIGN:
				name = "MultiplicationSign";
				break;
			case miniplc0::DIVISION_SIGN:
				name = "DivisionSign";
				break;
			case miniplc0::EQUAL_SIGN:
				name = "EqualSign";
				break;
			case miniplc0::SEMICOLON:
				name = "Semicolon";
				break;
			case miniplc0::LEFT_BRACKET:
				name = "LeftBracket";
				break;
			case miniplc0::RIGHT_QURLY:
				name = "rightcurly";
				break;
			case miniplc0::LEFT_QURLY:
				name = "leftcurly";
				break;
			}
			return format_to(ctx.out(), name);
		}
	};
}

namespace fmt {
	template<>
	struct formatter<miniplc0::Operation> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template <typename FormatContext>
		auto format(const miniplc0::Operation& p, FormatContext& ctx) {
			std::string name;
			int32_t number;
			switch (p) {


			case miniplc0::IRET:
				name = "IRET";
				number = 0x89;
				break;
			case miniplc0::JE:
				name = "JE";
				number = 0x71;
				break;
			case miniplc0::JNE:
				name = "JNE";
				number = 0x72;
				break;
			case miniplc0::JL:
				name = "JL";
				number = 0x73;
				break;
			case miniplc0::JGE:
				name = "JGE";
				number = 0x74;
				break;
			case miniplc0::JG:
				name = "JG";
				number = 0x75;
				break;
			case miniplc0::JLE:
				name = "JLE";
				number = 0x76;
				break;
			case miniplc0::LOADA:
				name = "LOADA";
				number = 0x0a;
				break;
			case miniplc0::LOADC:
				name = "LOADC";
				break;
			case miniplc0::IPUSH:
				name = "IPUSH";
				number = 0x02;
				break;
			case miniplc0::BIPUSH:
				name = "BIPUSH";
				number = 0x01;
				break;
			case miniplc0::NEW:
				name = "NEW";
				number = 0x0b;
				break;
			case miniplc0::SNEW:
				name = "SNEW";
				number = 0x0c;
				break;
			case miniplc0::POP:
				name = "POP";

				break;
			case miniplc0::DUP:
				name = "DUP";
				number = 0x07;
				break;
			case miniplc0::I2D:
				name = "I2D";
				number = 0x60;
				break;
			case miniplc0::I2C:
				name = "I2C";
				number = 0x62;
				break;
			case miniplc0::D2I:
				name = "D2I";
				number = 0x61;
				break;
			case miniplc0::JMP:
				name = "JMP";
				number = 0x70;
				break;
			case miniplc0::CALL:
				name = "CALL";
				number = 0x80;
				break;
			case miniplc0::RET:
				name = "RET";
				number = 0x88;
				break;
			case miniplc0::CSCAN:
				name = "CSCAN";
				number = 0xb2;
				break;

			case miniplc0::ILOAD:
				name = "ILOAD";
				number = 0x10;
				break;
			case miniplc0::ISTORE:
				name = "ISTORE";
				number = 0x20;
				break;
			case miniplc0::IALOAD:
				name = "IALOAD";
				number = 0x18;
				break;
			case miniplc0::IADD:
				name = "IADD";
				number = 0x30;
				break;
			case miniplc0::ISUB:
				name = "ISUB";
				number = 0x34;
				break;
			case miniplc0::IMUL:
				name = "IMUL";
				number = 0x38;
				break;
			case miniplc0::IDIV:
				name = "IDIV";
				number = 0x3c;
				break;
			case miniplc0::INEG:
				name = "INEG";
				number = 0x40;
				break;
			case miniplc0::ICMP:
				name = "ICMP";
				number = 0x44;
				break;
			case miniplc0::IPRINT:
				name = "IPRINT";
				number = 0xa0;
				break;
			case miniplc0::CPRINT:
				name = "CPRINT";
				number = 0xa2;
				break;
			case miniplc0::SPRINT:
				name = "SPRINT";
				number = 0xa3;
				break;
			case miniplc0::PRINTL:
				name = "PRINTL";
				number = 0xaf;
				break;
			case miniplc0::ISCAN:
				name = "ISCAN";
				number = 0xb0;
				break;



			}
			//if(num==0)
			return format_to(ctx.out(), name);
			/*else
				return format_to(ctx.out(), reinterpret_cast<char*>(&(number), 1));*/
		}
		/*template <typename FormatContext>
		auto formatc(const miniplc0::Operation& p, FormatContext &ctx) {
			std::string name;
			int32_t number;
			switch (p) {


			case miniplc0::IRET:
				name = "IRET";
				number = 0x89;
				break;
			case miniplc0::JE:
				name = "JE";
				number = 0x71;
				break;
			case miniplc0::JNE:
				name = "JNE";
				number = 0x72;
				break;
			case miniplc0::JL:
				name = "JL";
				number = 0x73;
				break;
			case miniplc0::JGE:
				name = "JGE";
				number = 0x74;
				break;
			case miniplc0::JG:
				name = "JG";
				number = 0x75;
				break;
			case miniplc0::JLE:
				name = "JLE";
				number = 0x76;
				break;
			case miniplc0::LOADA:
				name = "LOADA";
				number = 0x0a;
				break;
			case miniplc0::LOADC:
				name = "LOADC";
				break;
			case miniplc0::IPUSH:
				name = "IPUSH";
				number = 0x02;
				break;
			case miniplc0::BIPUSH:
				name = "BIPUSH";
				number = 0x01;
				break;
			case miniplc0::NEW:
				name = "NEW";
				number = 0x0b;
				break;
			case miniplc0::SNEW:
				name = "SNEW";
				number = 0x0c;
				break;
			case miniplc0::POP:
				name = "POP";

				break;
			case miniplc0::DUP:
				name = "DUP";
				number = 0x07;
				break;
			case miniplc0::I2D:
				name = "I2D";
				number = 0x60;
				break;
			case miniplc0::I2C:
				name = "I2C";
				number = 0x62;
				break;
			case miniplc0::D2I:
				name = "D2I";
				number = 0x61;
				break;
			case miniplc0::JMP:
				name = "JMP";
				number = 0x70;
				break;
			case miniplc0::CALL:
				name = "CALL";
				number = 0x80;
				break;
			case miniplc0::RET:
				name = "RET";
				number = 0x88;
				break;
			case miniplc0::CSCAN:
				name = "CSCAN";
				number = 0xb2;
				break;

			case miniplc0::ILOAD:
				name = "ILOAD";
				number = 0x10;
				break;
			case miniplc0::ISTORE:
				name = "ISTORE";
				number = 0x20;
				break;
			case miniplc0::IALOAD:
				name = "IALOAD";
				number = 0x18;
				break;
			case miniplc0::IADD:
				name = "IADD";
				number = 0x30;
				break;
			case miniplc0::ISUB:
				name = "ISUB";
				number = 0x34;
				break;
			case miniplc0::IMUL:
				name = "IMUL";
				number = 0x38;
				break;
			case miniplc0::IDIV:
				name = "IDIV";
				number = 0x3c;
				break;
			case miniplc0::INEG:
				name = "INEG";
				number = 0x40;
				break;
			case miniplc0::ICMP:
				name = "ICMP";
				number = 0x44;
				break;
			case miniplc0::IPRINT:
				name = "IPRINT";
				number = 0xa0;
				break;
			case miniplc0::SPRINT:
				name = "SPRINT";
				number = 0xa3;
				break;
			case miniplc0::PRINTL:
				name = "PRINTL";
				number = 0xaf;
				break;
			case miniplc0::ISCAN:
				name = "ISCAN";
				number = 0xb0
					break;



			}
			return format_to(ctx.out(), reinterpret_cast<char*>(&(number), 1));
		}*/
	};


	template<>
	struct formatter<miniplc0::Instruction> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template <typename FormatContext>
		auto format(const miniplc0::Instruction& p, FormatContext& ctx) {
			//if (num == 0) {
			std::string name;
			switch (p.GetOperation())
			{


			case miniplc0::IADD:
			case miniplc0::ISUB:
			case miniplc0::IMUL:
			case miniplc0::IDIV:
			case miniplc0::INEG:
			case miniplc0::ICMP:
			case miniplc0::IPRINT:
			case miniplc0::CPRINT:
			case miniplc0::SPRINT:
			case miniplc0::PRINTL:
			case miniplc0::POP:
			case miniplc0::DUP:
			case miniplc0::I2D:
			case miniplc0::I2C:
			case miniplc0::D2I:
			case miniplc0::RET:
			case miniplc0::IRET:
			case miniplc0::NEW:
			case miniplc0::ILOAD:
			case miniplc0::ISTORE:
			case miniplc0::CSCAN:
			case miniplc0::IALOAD:
			case miniplc0::IASTORE:
			case miniplc0::ISCAN:
				return format_to(ctx.out(), "{}", p.GetOperation());

			case miniplc0::JE:
			case miniplc0::JNE:
			case miniplc0::JL:
			case miniplc0::JGE:
			case miniplc0::JG:
			case miniplc0::JLE:
			case miniplc0::LOADC:
			case miniplc0::IPUSH:
			case miniplc0::BIPUSH:
			case miniplc0::SNEW:
			case miniplc0::JMP:
			case miniplc0::CALL:

				return format_to(ctx.out(), "{} {}", p.GetOperation(), p.GetX());

			case miniplc0::LOADA:

				return format_to(ctx.out(), "{} {},{}", p.GetOperation(), p.GetX(), p.GetY());

				//}
			}
			//return format_to(ctx.out(), "IRET");
			/*if (num == 1) {
				std::string name;
				switch (p.GetOperation())
				{


				case miniplc0::IADD:
				case miniplc0::ISUB:
				case miniplc0::IMUL:
				case miniplc0::IDIV:
				case miniplc0::INEG:
				case miniplc0::ICMP:
				case miniplc0::IPRINT:
				case miniplc0::PRINTL:
				case miniplc0::POP:
				case miniplc0::DUP:
				case miniplc0::I2D:
				case miniplc0::I2C:
				case miniplc0::D2I:
				case miniplc0::RET:
				case miniplc0::IRET:
				case miniplc0::NEW:
				case miniplc0::ILOAD:
				case miniplc0::ISTORE:
				case miniplc0::CSCAN:
					return format_to(ctx.out(), "{}", p.GetOperation());

				case miniplc0::JE:
				case miniplc0::JNE:
				case miniplc0::JL:
				case miniplc0::JGE:
				case miniplc0::JG:
				case miniplc0::JLE:
				case miniplc0::LOADC:
				case miniplc0::IPUSH:
				case miniplc0::BIPUSH:
				case miniplc0::SNEW:
				case miniplc0::JMP:
				case miniplc0::CALL:
				case miniplc0::IALOAD:
				case miniplc0::IASTORE:
				case miniplc0::ISCAN:
					return format_to(ctx.out(), "{}{}", p.GetOperation(), reinterpret_cast<char*>(&(p.GetX()), 4));

				case miniplc0::LOADA:

					return format_to(ctx.out(), "{}{}{}", p.GetOperation(), reinterpret_cast<char*>(&(p.GetX()), 4), reinterpret_cast<char*>(&(p.GetY()), 4));

				}
			}*/

		}

	};



	template<>
	struct formatter<miniplc0::Constants> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template <typename FormatContext>
		auto format(const miniplc0::Constants& p, FormatContext& ctx) {
			std::string name;


			return format_to(ctx.out(), "S {}{}{}", '\"', p.getvalue(), '\"');



			//return format_to(ctx.out(), "IRET");


		}
	};
	template<>
	struct formatter<miniplc0::Function> {
		template <typename ParseContext>
		constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

		template <typename FormatContext>
		auto format(const miniplc0::Function& p, FormatContext& ctx) {
			std::string name;
			if (p.gettype() == 0)name = "char";
			if (p.gettype() == 1)name = "int";
			if (p.gettype() == 3)name = "void";



			return format_to(ctx.out(), "{} {}", p.getparasize(), 1);



			//return format_to(ctx.out(), "IRET");


		}
	};
}