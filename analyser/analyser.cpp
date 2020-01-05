#include "analyser.h"
#include<iostream>
#include <climits>


#include <iomanip> 
#include <string> 

/*
<digit> ::=
	'0'|<nonzero-digit>
<nonzero-digit> ::=
	'1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9'
<hexadecimal-digit> ::=
	<digit>|'a'|'b'|'c'|'d'|'e'|'f'|'A'|'B'|'C'|'D'|'E'|'F'

<integer-literal> ::=
	<decimal-literal>|<hexadecimal-literal>
<decimal-literal> ::=
	'0'|<nonzero-digit>{<digit>}
<hexadecimal-literal> ::=
	('0x'|'0X')<hexadecimal-digit>{<hexadecimal-digit>}


<nondigit> ::=    'a'|'b'|'c'|'d'|'e'|'f'|'g'|'h'|'i'|'j'|'k'|'l'|'m'|'n'|'o'|'p'|'q'|'r'|'s'|'t'|'u'|'v'|'w'|'x'|'y'|'z'|'A'|'B'|'C'|'D'|'E'|'F'|'G'|'H'|'I'|'J'|'K'|'L'|'M'|'N'|'O'|'P'|'Q'|'R'|'S'|'T'|'U'|'V'|'W'|'X'|'Y'|'Z'

<identifier> ::=
	<nondigit>{<nondigit>|<digit>}
<reserved-word> a
	 'const'
	|'void'   |'int'    |'char'   |'double'
	|'struct'
	|'if'     |'else'
	|'switch' |'case'   |'default'
	|'while'  |'for'    |'do'
	|'return' |'break'  |'continue'
	|'print'  |'scan'

<unary-operator>          ::= '+' | '-'
<additive-operator>       ::= '+' | '-'
<multiplicative-operator> ::= '*' | '/'
<relational-operator>     ::= '<' | '<=' | '>' | '>=' | '!=' | '=='
<assignment-operator>     ::= '='



<type-specifier>         ::= <simple-type-specifier>
<simple-type-specifier>  ::= 'void'|'int'
<const-qualifier>        ::= 'const'


<C0-program> ::=
	{<variable-declaration>}{<function-definition>}


<variable-declaration> ::=
	[<const-qualifier>]<type-specifier><init-declarator-list>';'
<init-declarator-list> ::=
	<init-declarator>{','<init-declarator>}
<init-declarator> ::=
	<identifier>[<initializer>]
<initializer> ::=
	'='<expression>


<function-definition> ::=
	<type-specifier><identifier><parameter-clause><compound-statement>

<parameter-clause> ::=
	'(' [<parameter-declaration-list>] ')'
<parameter-declaration-list> ::=
	<parameter-declaration>{','<parameter-declaration>}
<parameter-declaration> ::=
	[<const-qualifier>]<type-specifier><identifier>


<compound-statement> ::=
	'{' {<variable-declaration>} <statement-seq> '}'
<statement-seq> ::=
	{<statement>}
<statement> ::=
	 '{' <statement-seq> '}'
	|<condition-statement>
	|<loop-statement>
	|<jump-statement>
	|<print-statement>
	|<scan-statement>
	|<assignment-expression>';'
	|<function-call>';'
	|';'


<condition> ::=
	 <expression>[<relational-operator><expression>]

<condition-statement> ::=
	 'if' '(' <condition> ')' <statement> ['else' <statement>]

<loop-statement> ::=
	'while' '(' <condition> ')' <statement>

<jump-statement> ::=
	<return-statement>
<return-statement> ::=
	'return' [<expression>] ';'

<scan-statement> ::=
	'scan' '(' <identifier> ')' ';'
<print-statement> ::=
	'print' '(' [<printable-list>] ')' ';'
<printable-list>  ::=
	<printable> {',' <printable>}
<printable> ::=
	<expression>

<assignment-expression> ::=
	<identifier><assignment-operator><expression>

<expression> ::=
	<additive-expression>
<additive-expression> ::=
	 <multiplicative-expression>{<additive-operator><multiplicative-expression>}
<multiplicative-expression> ::=
	 <unary-expression>{<multiplicative-operator><unary-expression>}
<unary-expression> ::=
	[<unary-operator>]<primary-expression>
<primary-expression> ::=
	 '('<expression>')'
	|<identifier>
	|<integer-literal>
	|<function-call>

<function-call> ::=
	<identifier> '(' [<expression-list>] ')'
<expression-list> ::=
	<expression>{','<expression>}*/

namespace miniplc0 {
	std::pair<std::vector<Instruction>, std::optional<CompilationError>> Analyser::Analyse(std::ostream& output) {
		auto err = analyseProgram();
		if (err.has_value())
			return std::make_pair(std::vector<Instruction>(), err);
		else
		{
			/*for(int i=0;i<_constants_list.size();i++)
			{ }
			for (int i = 0; i < _functions_list.size(); i++)
			{
				for (auto& it : _start)
					output << fmt::format("{}\n", it);



			}*/


			return std::make_pair(_start, std::optional<CompilationError>());
		}

	}

	// <程序> ::= 'begin'<主过程>'end'
	std::optional<CompilationError> Analyser::analyseProgram() {


		auto vd = analyseVariableDeclaration();
		if (vd.has_value())
			return vd;



		auto fd = analyseFunctionDefinition();
		if (fd.has_value())
			return fd;
		return {};
	}

	// <主过程> ::= <常量声明><变量声明><语句序列>
	// 需要补全
	std::optional<CompilationError> Analyser::analyseVariableDeclaration() {
		// 预读判断是否进入函数声明 
		while (true)
		{
			auto test0 = nextToken();
			if (!test0.has_value())
				return {};
			auto test1 = nextToken();
			if (!test0.has_value())
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);
			auto test2 = nextToken();
			if (!test0.has_value())
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);//todo make sure the error code
			unreadToken();
			unreadToken();
			unreadToken();
			if (test2.value().GetType() == TokenType::LEFT_BRACKET)
			{
				return {};
			}

			if (test0.value().GetType() != TokenType::CONST && test0.value().GetType() != TokenType::TYPE)
			{
				return {};
			}

			if (test0.value().GetType() == TokenType::CONST)
			{
				// <常量声明>
				auto cd = analyseConstantDeclaration();
				if (cd.has_value())
					return cd;
			}
			else
			{
				auto vd = analyseVoidDeclaration();
				if (vd.has_value())
					return vd;
			}

		}
		auto next = nextToken();
		if (next.value().GetType() != TokenType::SEMICOLON)
		{
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoSemicolon);
		}
		return {};
	}

	// <常量声明> ::= {<常量声明语句>}
	// <常量声明语句> ::= 'const'<标识符>'='<常表达式>';'
	std::optional<CompilationError> Analyser::analyseConstantDeclaration() {
		// 示例函数，示例如何分析常量声明

		// 常量声明语句可能有 0 或无数个
			// 预读一个 token，不然不知道是否应该用 <常量声明> 推导
		int32_t type = 0;
		auto next = nextToken();
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::TYPE)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoType);
		if (next.value().GetValueString() == "int")
			type = 5;
		else if (next.value().GetValueString() == "char")
			type = 4;
		else if (next.value().GetValueString() == "void")
		{
			type = 3;
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrVoid);

		}
		else
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrType);


		// <常量声明语句>
		auto id = ConstInitDeclarator(type);
		if (id.has_value())
			return id;


		while (true)
		{
			next = nextToken();
			if (!next.has_value())break;
			if (next.value().GetType() == TokenType::COMMA) {
				auto id = ConstInitDeclarator(type);
				if (id.has_value())
					return id;
			}
			else
			{
				unreadToken();
				break;
			}
		}
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::SEMICOLON)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoSemicolon);


		return {};
	}
	std::optional<CompilationError> Analyser::ConstInitDeclarator(int32_t type) {
		auto name = nextToken();
		if (!name.has_value() || name.value().GetType() != TokenType::IDENTIFIER)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);

		auto next = nextToken();
		if (_vars_list.empty() == false) {
			if (isDeclared(name.value().GetValueString()))
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrDuplicateDeclaration);
			if (next.value().GetType() != TokenType::EQUAL_SIGN)
			{
				addVariable(name.value(), type);
				_instructions_list[_instructions_list.size() - 1].emplace_back(Instruction(Operation::IPUSH, 0)); //ins
				unreadToken();
				return {};
			}
			// '='
			else
			{


				int32_t val;
				auto err = analyseExpression();
				if (err.has_value())
					return err;
				addVariable(name.value(), type);
				//_start.emplace_back(Instruction(Operation::IPUSH, val)); //ins

			}
		}
		else {
			if (isDeclaredGlobal(name.value().GetValueString()))
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrDuplicateDeclaration);
			if (next.value().GetType() != TokenType::EQUAL_SIGN)
			{
				addVariableGlobal(name.value(), type);
				_start.emplace_back(Instruction(Operation::IPUSH, 0)); //ins
				unreadToken();
				return {};
			}
			// '='
			else
			{


				int32_t val;
				auto err = analyseExpression();
				if (err.has_value())
					return err;
				addVariableGlobal(name.value(), type);
				//_start.emplace_back(Instruction(Operation::IPUSH, val)); //ins

			}

		}
		//ins

		// <常表达式>

		return {};
	}
	



	// <变量声明> ::= {<变量声明语句>}
	// <变量声明语句> ::= 'var'<标识符>['='<表达式>]';'
	// 需要补全
	std::optional<CompilationError> Analyser::analyseVoidDeclaration() {
		// 变量声明语句可能有一个或者多个
		auto type = 4;
		auto next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::TYPE)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoType);
		if (next.value().GetValueString() == "int")
			type = 1;
		else if (next.value().GetValueString() == "char")
			type = 0;
		else if (next.value().GetValueString() == "void")
		{
			type = 3;
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoType);//

		}
		else
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrType);
		auto id = VarInitDeclarator(type);
		if (id.has_value())
			return id;



		while (true)
		{
			next = nextToken();
			if (!next.has_value())break;
			if (next.value().GetType() == TokenType::COMMA) {
				auto id = VarInitDeclarator(type);
				if (id.has_value())
					return id;
			}
			else
			{
				unreadToken();
				break;
			}
		}
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::SEMICOLON)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoSemicolon);




		return {};
	}
	std::optional<CompilationError> Analyser::VarInitDeclarator(int32_t type) {
		auto name = nextToken();
		if (!name.has_value() || name.value().GetType() != TokenType::IDENTIFIER)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);

		auto next = nextToken();
		if (_vars_list.empty() == false) {
			if (isDeclared(name.value().GetValueString()))
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrDuplicateDeclaration);
			if (next.value().GetType() != TokenType::EQUAL_SIGN)
			{
				addVariable(name.value(), type);
				_instructions_list[_instructions_list.size()-1].emplace_back(Instruction(Operation::IPUSH, 0)); //ins
				unreadToken();
				return {};
			}
			// '='
			else
			{


				int32_t val;
				auto err = analyseExpression();
				if (err.has_value())
					return err;
				addVariable(name.value(), type);
				//_start.emplace_back(Instruction(Operation::IPUSH, val)); //ins

			}
		}
		else {
			if (isDeclaredGlobal(name.value().GetValueString()))
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrDuplicateDeclaration);
			if (next.value().GetType() != TokenType::EQUAL_SIGN)
			{
				addVariableGlobal(name.value(), type);
				_start.emplace_back(Instruction(Operation::IPUSH, 0)); //ins
				unreadToken();
				return {};
			}
			// '='
			else
			{


				int32_t val;
				auto err = analyseExpression();
				if (err.has_value())
					return err;
				addVariableGlobal(name.value(), type);
				//_start.emplace_back(Instruction(Operation::IPUSH, val)); //ins

			}

		}
		//ins

		// <常表达式>

		return {};
	}
	// <语句序列> ::= {<语句>}
	// <语句> :: = <赋值语句> | <输出语句> | <空语句>
	// <赋值语句> :: = <标识符>'='<表达式>';'
	// <输出语句> :: = 'print' '(' <表达式> ')' ';'
	// <空语句> :: = ';'
	// 需要补全
	std::optional<CompilationError> Analyser::analyseFunctionDefinition() {
		while (true)
		{
			int32_t type = 4;
			int32_t para = 0;
			std::vector<int32_t> paratype;
			std::vector<std::string> paraname;
			auto next = nextToken();
			if (!next.has_value())
				return {};

			else if (next.value().GetType() != TokenType::TYPE)
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoType);

			if (next.value().GetValueString() == "char")
				type = 0;
			else if (next.value().GetValueString() == "int")
				type = 1;
			else if (next.value().GetValueString() == "void")
				type = 3;
			else
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrType);
			auto name = nextToken();
			if (!name.has_value() || name.value().GetType() != TokenType::IDENTIFIER)
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);
			if(name.value().GetValueString()=="main"&&type!=3)
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoFunciton);

			if (isDeclaredFun(name.value().GetValueString()) >= 0)
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrDuplicateDeclaration);
			if (isDeclaredGlobal(name.value().GetValueString()))
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrDuplicateDeclaration);


			auto pc = analyseParameterClause(para, paratype, paraname);
			if (pc.has_value())
				return pc;
			if (isDeclaredFun(name.value().GetValueString()) >= 0) {
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);
			}
			else
			{
				_constants_list.emplace_back(Constants(0, name.value().GetValueString()));
				std::vector<Instruction> teminslist;
				_instructions_list.emplace_back(teminslist);
				_functions_list.emplace_back(Function(name.value().GetValueString(), type, para, paratype, paraname));

			}


			auto cs = analyseComponetSequence();
			if (cs.has_value())
				return cs;

			switch (type) {
			case 1:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IPUSH, 0));
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IRET));
				break;
			case 0:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IPUSH, 0));
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IRET));
				break;
			case 3:_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::RET));
				break;
			}

		}
		return {};
	}
	std::optional<CompilationError> Analyser::analyseParameterClause(int32_t& para, std::vector<int32_t>& paratype, std::vector<std::string>& paraname) {
		auto next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::LEFT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedLeftBracket);
		next = nextToken();
		if (next.value().GetType() == TokenType::RIGHT_BRACKET)
		{
			return {};
		}
		unreadToken();
		auto pd = analyseParameterDeaclartion(paratype, paraname);
		if (pd.has_value())
			return pd;
		para++;

		while (true)
		{
			next = nextToken();
			if (!next.has_value())break;
			if (next.value().GetType() == TokenType::COMMA) {
				auto pd = analyseParameterDeaclartion(paratype, paraname);
				if (pd.has_value())
					return pd;
				para++;
			}
			else
			{
				unreadToken();
				break;
			}

		}
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::RIGHT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedRightBracket);
		return {};
		//ins


	}
	std::optional<CompilationError> Analyser::analyseParameterDeaclartion(std::vector<int32_t>& paratype, std::vector<std::string>& paraname) {
		int32_t type = 0;
		int32_t isconst = 0;
		auto next = nextToken();
		if (!next.has_value()) {
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);

		}
		if (next.value().GetType() == TokenType::CONST)
		{
			isconst = 4;
			next = nextToken();
		}

		if (next.value().GetType() != TokenType::TYPE || !next.has_value()) {
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);
		}
		if (next.value().GetValueString() == "char")
			type = 0;
		else if (next.value().GetValueString() == "int")
			type = 1;
		else
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrType);
		paratype.emplace_back(type + isconst);
		next = nextToken(); //实际变量名字无所谓其实，别重名
		if (!next.has_value() || next.value().GetType() != TokenType::IDENTIFIER) {
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);

		}
		paraname.emplace_back(next.value().GetValueString());
		return {};

	}
	std::optional<CompilationError> Analyser::analyseComponetSequence() {
		auto next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::LEFT_QURLY)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedLeftCurly);
		next = nextToken();
		if (!next.has_value())
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedRightCurly);
		std::map<std::string, Variable > newvarmap;
		_vars_list.push(newvarmap);
		for (int i = 0; i < _functions_list[_functions_list.size() - 1].getparasize(); i++) {
			_vars_list.top()[_functions_list[_functions_list.size() - 1].getparaname(i)] = Variable(_functions_list[_functions_list.size() - 1].getparatype(i), i); //将传入参数作为变量表成员


		}
		if (next.value().GetType() == TokenType::CONST || next.value().GetType() == TokenType::TYPE)
		{
			unreadToken();
			auto vd = analyseVariableDeclaration();
			if (vd.has_value())
				return vd;
			auto ss = analyseStatementSeq();
			if (ss.has_value())
				return ss;
		}

		else {
			unreadToken();
			auto ss = analyseStatementSeq();
			if (ss.has_value())
				return ss;
		}


		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::RIGHT_QURLY)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedRightCurly);
		return {};

	}
	std::optional<CompilationError> Analyser::analyseStatementSeq() {
		auto next = nextToken();
		if (!next.has_value())
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedRightCurly);
		if (next.value().GetType() == TokenType::RIGHT_QURLY)
		{

			return {};
		}
		unreadToken();
		while (true)
		{
			auto s = analyseStatement();
			if (s.has_value())
				return s;
			next = nextToken();
			if (next.value().GetType() != TokenType::IF &&
				next.value().GetType() != TokenType::LEFT_QURLY &&
				next.value().GetType() != TokenType::WHILE &&
				next.value().GetType() != TokenType::RETURN &&
				next.value().GetType() != TokenType::SCAN &&
				next.value().GetType() != TokenType::PRINT &&
				next.value().GetType() != TokenType::IDENTIFIER &&
				next.value().GetType() != TokenType::SEMICOLON) {
				unreadToken();
				return {};
			}
			else unreadToken();

		}
		return {};

	}

	std::optional<CompilationError> Analyser::analyseStatement() {

		// 预读
		auto next = nextToken();
		if (!next.has_value())
			return {};

		if (next.value().GetType() != TokenType::IF &&
			next.value().GetType() != TokenType::LEFT_QURLY &&
			next.value().GetType() != TokenType::WHILE &&
			next.value().GetType() != TokenType::RETURN &&
			next.value().GetType() != TokenType::SCAN &&
			next.value().GetType() != TokenType::PRINT &&
			next.value().GetType() != TokenType::IDENTIFIER &&
			next.value().GetType() != TokenType::SEMICOLON) {
			unreadToken();
			return {};
		}
		std::optional<CompilationError> err;
		switch (next.value().GetType()) {

		case IDENTIFIER:
		{
			next = nextToken();
			if (next.value().GetType() == TokenType::EQUAL_SIGN)
			{
				unreadToken();
				unreadToken();
				auto err = analyseAssignmentStatement();
				if (err.has_value())
					return err;

				break;
			}
			else if (next.value().GetType() == TokenType::LEFT_BRACKET)
			{
				unreadToken();
				unreadToken();
				auto err = analyseFunctionCall();
				if (err.has_value())
					return err;

				break;
			}
		}
		case PRINT:
		{unreadToken();
		auto err = analyseOutputStatement();
		if (err.has_value())
			return err;
		break;
		}
		case IF:
		{
			unreadToken();
			auto error = analyseConditionStatement();
			if (err.has_value())
				return err;

			break;
		}
		case WHILE:
		{
			unreadToken();
			auto error = analyseLoopStatement();
			if (err.has_value())
				return err;
			break;
		}
		case SCAN:
		{
			unreadToken();
			auto error = analyseInputStatement();
			if (err.has_value())
				return err;
			break;
		}
		case LEFT_QURLY:
		{

			auto error = analyseStatementSeq();
			if (err.has_value())
				return err;
			auto next2 = nextToken();
			if (!next2.has_value() || next2.value().GetType() != TokenType::RIGHT_QURLY)
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedRightCurly);
			break;
		}
		case RETURN:
		{
			unreadToken();
			auto error = analyseJumpStatement();
			if (error.has_value())
				return error;
			break;
		}
		case SEMICOLON:
			return{};


			// 这里需要你针对不同的预读结果来调用不同的子程序
			// 注意我们没有针对空语句单独声明一个函数，因此可以直接在这里返回
		default:
			break;
		}

		return {};
	}

	std::optional<CompilationError>Analyser::analyseConditionStatement() {
		auto next = nextToken();
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::LEFT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);

		auto err = analyseCondition();
		if (err.has_value())
			return err;
		auto ifoffset = _instructions_list[_functions_list.size() - 1].size() - 1;
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::RIGHT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
		auto s = analyseStatement();
		if (s.has_value())
			return s;
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::ELSE)
		{
			unreadToken();
			auto elseoff = _instructions_list[_functions_list.size() - 1].size() - 1;
			_instructions_list[_functions_list.size() - 1][ifoffset].backfille(elseoff + 1);
			return {};
		}
		auto elseoff = _instructions_list[_functions_list.size() - 1].size() - 1;
		_instructions_list[_functions_list.size() - 1][ifoffset].backfille(elseoff + 1); //tbc
		s = analyseStatement();
		if (s.has_value())
			return s;
		return {};


	}
	std::optional<CompilationError>Analyser::analyseCondition() {
		auto err = analyseExpression();
		if (err.has_value())
			return err;
		auto next = nextToken();
		if (!next.has_value())
			return {};
		if (next.value().GetType() == TokenType::MORE || next.value().GetType() == TokenType::NOEUQAL || next.value().GetType() == TokenType::MOREEQUAL || next.value().GetType() == TokenType::EQUAL || next.value().GetType() == TokenType::LESS || next.value().GetType() == TokenType::LESSEQUAL)
		{
			auto err = analyseExpression();
			if (err.has_value())
				return err;

			_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::ICMP));
			switch
				(next.value().GetType()) {
			case TokenType::MORE:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::JLE));
				break;
			case TokenType::MOREEQUAL:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::JL));
				break;
			case TokenType::EQUAL:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::JNE));
				break;
			case TokenType::NOEUQAL:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::JE));
				break;

			case TokenType::LESS:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::JGE));
				break;
			case TokenType::LESSEQUAL:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::JG));
				break;
			default:
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
				break;
			}
			return {};


		}
		unreadToken();
		return {};
	}
	std::optional<CompilationError> Analyser::analyseLoopStatement()
	{
		int32_t outoffset;

		auto next = nextToken();
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::LEFT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
		int32_t whileoffset = _instructions_list[_functions_list.size() - 1].size() - 1;
		auto err = analyseCondition();
		int32_t aftercondition = _instructions_list[_functions_list.size() - 1].size() - 1;;
		if (err.has_value())
			return err;
		//tbc

		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::RIGHT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
		auto s = analyseStatement();
		if (s.has_value())
			return s;
		_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::JMP, whileoffset + 1));
		outoffset = _instructions_list[_functions_list.size() - 1].size() - 1;
		_instructions_list[_functions_list.size() - 1][aftercondition].backfille(outoffset + 1);

		return {};
	}
	std::optional<CompilationError> Analyser::analyseJumpStatement() {
		int32_t type = 0;
		auto next = nextToken();
		next = nextToken();
		type = _functions_list[_functions_list.size() - 1].gettype();
		if (!next.has_value())
			return {};
		if (next.value().GetType() == TokenType::SEMICOLON)
		{
			switch (type) {
			case 1:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IPUSH, 0));
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IRET));
				break;
			case 0:
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IPUSH, 0));
				_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IRET));
				break;
			case 3:_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::RET));
				break;
			}
			return {};
		}
		else {
			unreadToken();
			auto err = analyseExpression();
			if (err.has_value())
				return err;
			switch (type) {
			case 1:_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IRET));
				break;
			case 0:_instructions_list[_functions_list.size() - 1].emplace_back(Instruction(Operation::IRET));
				break;
			case 3:return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrVoid);
				break;
			}


		}
		next = nextToken();
		if (next.value().GetType() != TokenType::SEMICOLON)
		{
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);

		}

		return {};
	}

	std::optional<CompilationError> Analyser::analyseInputStatement() {

		auto next = nextToken();
		next = nextToken();
		if (!next.has_value())
			return {};
		if (!next.has_value() || next.value().GetType() != TokenType::LEFT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::IDENTIFIER)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
		{
			if (!((isDeclared(next.value().GetValueString()) || isDeclaredGlobal(next.value().GetValueString()))))
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNotDeclared);
			if (isConstant(next.value().GetValueString()) || isConstantGlobal(next.value().GetValueString()))
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrAssignToConstant);


			if (isVariable(next.value().GetValueString()))
			{
				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::LOADA, 0, _vars_list.top()[next.value().GetValueString()]._offset);
				if (_vars_list.top()[next.value().GetValueString()]._type = 0) {

					_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::CSCAN);
				}
				else { _instructions_list[_instructions_list.size() - 1].emplace_back(Operation::ISCAN); }

			}
			else if (isGlobalVariable(next.value().GetValueString()))
			{
				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::LOADA, 1, _global_var_list[next.value().GetValueString()]._offset);
				if (_global_var_list[next.value().GetValueString()]._type = 0) {

					_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::CSCAN);

				}
				else { _instructions_list[_instructions_list.size() - 1].emplace_back(Operation::ISCAN); }
			}

		}
		_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::ISTORE);
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::RIGHT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::SEMICOLON)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoSemicolon);

	}
	// <语句序列>

	std::optional<CompilationError> Analyser::analyseFunctionCall()
	{
		auto next = nextToken();
		std::string name = next.value().GetValueString();
		if (next.value().GetType() != TokenType::IDENTIFIER)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
		int32_t index = isDeclaredFun(next.value().GetValueString());
		int32_t parasize = _functions_list[index].getparasize();
		if (index < 0)

			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
		else {
			for (int i = 0; i < parasize; i++) {
				auto err = analyseExpression();
				if (err.has_value())
				{
					return err;
				}
				if (_functions_list[index].getparatype(i) == 0 || _functions_list[index].getparatype(i) == 4)
					_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::I2C);

				if (i == parasize - 1)break;
				next = nextToken();
				if (next.value().GetType() != TokenType::COMMA)
				{
					return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrInvalidInput);

				}
			}

		}

		_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::CALL, isDeclaredFun(name));

		return {};


	}

	// <常表达式> ::= [<符号>]<无符号整数>
	// 需要补全
	std::optional<CompilationError> Analyser::analyseConstantExpression(int32_t& out) {
		auto next = nextToken();
		int32_t convert;
		int sign = 1;
		if (!next.has_value())
			return {};// out 是常表达式的结果
		if (next.has_value() == TokenType::PLUS_SIGN)
			next = nextToken();
		else if (next.has_value() == TokenType::MINUS_SIGN)
		{
			sign = -1;
			next = nextToken();
		}
		if (next.has_value() != TokenType::UNSIGNED_INTEGER || next.has_value() != TokenType::HEX_INTERGER)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrConstantNeedValue);
		try {
			out = stoi(next.value().GetValueString());//为啥getvalue转不了
		}
		catch (std::out_of_range&) {
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrIntegerOverflow);
		}
		if (sign == -1)//因为常数在底下 选择用乘法取负数
		{
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IPUSH, -1);
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IMUL, 0);
		}




		// 这里你要分析常表达式并且计算结果
		// 注意以下均为常表达式
		// +1 -1 1
		// 同时要注意是否溢出
		return {};
	}

	// <表达式> ::= <项>{<加法型运算符><项>}
	std::optional<CompilationError> Analyser::analyseExpression() {
		// <项>
		auto err = analyseItem();
		if (err.has_value())
			return err;

		// {<加法型运算符><项>}
		while (true) {
			// 预读
			auto next = nextToken();
			if (!next.has_value())
				return {};
			auto type = next.value().GetType();
			if (type != TokenType::PLUS_SIGN && type != TokenType::MINUS_SIGN) {
				unreadToken();
				return {};
			}

			// <项>
			err = analyseItem();
			if (err.has_value())
				return err;

			// 根据结果生成指令
			if (type == TokenType::PLUS_SIGN)
				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IADD);
			else if (type == TokenType::MINUS_SIGN)
				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::ISUB);
		}

		return {};
	}

	// <赋值语句> ::= <标识符>'='<表达式>';'
	// 需要补全
	std::optional<CompilationError> Analyser::analyseAssignmentStatement() {
		bool trans = false;
		// <标识符>
		auto next = nextToken();
		std::string name = next.value().GetValueString();
		//convertUninitializedToVariable(next.value());
		if (!(isDeclared(next.value().GetValueString()) || isDeclaredGlobal(next.value().GetValueString())))
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNotDeclared);
		if (isConstant(next.value().GetValueString()) || isConstantGlobal(next.value().GetValueString()))
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrAssignToConstant);
		auto next2 = nextToken();
		if (next2.value().GetType() != TokenType::EQUAL_SIGN)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrIncompleteExpression);
		//类型转换 显示
		while (true) {
			auto test0 = nextToken();
			if (!test0.has_value())
				return {};
			auto test1 = nextToken();
			if (!test0.has_value())
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);
			auto test2 = nextToken();
			if (!test0.has_value())
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNeedIdentifier);//todo make sure the error code
			if (test0.value().GetType() == TokenType::LEFT_BRACKET && test1.value().GetType() == TokenType::TYPE && test0.value().GetType() == TokenType::RIGHT_BRACKET) {
				if (test1.value().GetValueString() == "char")
					trans = true;
				continue;
			}
			unreadToken();
			unreadToken();
			unreadToken();
			break;
		}
		if (isVariable(next.value().GetValueString()))
		{
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::LOADA, 0, _vars_list.top()[(std::string)name]._offset);
			if (_vars_list.top()[next.value().GetValueString()]._type = 0 || trans == true) {
				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::I2C);

			}



		}
		else if (isGlobalVariable(next.value().GetValueString()))
		{
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::LOADA, 1, _global_var_list[(std::string)name]._offset);
			if (_global_var_list[next.value().GetValueString()]._type = 0 || trans == true) {
				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::I2C);

			}

		}
		auto err = analyseExpression();
		if (err.has_value())
			return err;
		next2 = nextToken();
		if (!next2.has_value() || next2.value().GetType() != TokenType::SEMICOLON)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoSemicolon);
		_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::ISTORE);



		//tbc
		// 这里除了语法分析以外还要留意
		// 标识符声明过吗？
		// 标识符是常量吗？
		// 需要生成指令吗？
		return {};
	}

	// <输出语句> ::= 'print' '(' <表达式> ')' ';'
	std::optional<CompilationError> Analyser::analyseOutputStatement() {
		// 如果之前 <语句序列> 的实现正确，这里第一个 next 一定是 TokenType::PRINT
		auto next = nextToken();

		// '('
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::LEFT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrInvalidPrint);

		// <表达式>

		else {
			auto err = analysePrintable();
			if (err.has_value())
				return err;
			while (true)
			{
				next = nextToken();
				if (!next.has_value())
				{
					return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrInvalidPrint);

				}
				if (next.value().GetType() != TokenType::COMMA)
				{
					unreadToken();
					break;
				}
				auto err = analysePrintable();
				if (err.has_value())
					return err;
			}
		}

		// ')'
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::RIGHT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrInvalidPrint);

		// ';'
		next = nextToken();
		if (!next.has_value() || next.value().GetType() != TokenType::SEMICOLON)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoSemicolon);

		// 生成相应的指令 WRT
		//ins

		return {};
	}
	std::optional<CompilationError> Analyser::analysePrintable() {
		auto test = nextToken();
		if (test.value().GetType() == TokenType::CHAR) {
			
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IPUSH,test.value().GetValueString().c_str()[0]);
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::CPRINT);
		}
		else if (test.value().GetType() == TokenType::STRING) {
			_constants_list.emplace_back(Constants(0, test.value().GetValueString()));
			
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::LOADC, _constants_list.size() - 1);
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::SPRINT);



		}
		else {
			unreadToken();
			auto err = analyseExpression();
			if (err.has_value())
				return err;
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IPRINT);

		}
		return {};
	}

	// <项> :: = <因子>{ <乘法型运算符><因子> }
	// 需要补全
	std::optional<CompilationError> Analyser::analyseItem() {
		// 可以参考 <表达式> 实现
		// <因子>
		auto err = analyseFactor();
		if (err.has_value())
			return err;

		// {<加法型运算符><项>}
		while (true) {
			// 预读
			auto next = nextToken();
			if (!next.has_value())
				return {};
			auto type = next.value().GetType();
			if (type != TokenType::MULTIPLICATION_SIGN && type != TokenType::DIVISION_SIGN) {
				unreadToken();
				return {};
			}

			// <项>
			err = analyseFactor();
			if (err.has_value())
				return err;

			// 根据结果生成指令
			if (type == TokenType::MULTIPLICATION_SIGN)
				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IMUL);
			else if (type == TokenType::DIVISION_SIGN)
				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IDIV);

		}

		return {};
	}

	// <因子> ::= [<符号>]( <标识符> | <无符号整数> | '('<表达式>')' )
	// 需要补全
	std::optional<CompilationError> Analyser::analyseFactor() {
		// [<符号>]
		auto next = nextToken();
		auto prefix = 1;
		if (!next.has_value())
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrIncompleteExpression);
		if (next.value().GetType() == TokenType::PLUS_SIGN)
			prefix = 1;
		else if (next.value().GetType() == TokenType::MINUS_SIGN) {
			prefix = -1;


		}
		else
			unreadToken();

		// 预读
		next = nextToken();
		if (!next.has_value())
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrIncompleteExpression);
		switch (next.value().GetType()) {
		case IDENTIFIER:
			if (!(isDeclared(next.value().GetValueString()) || isDeclaredGlobal(next.value().GetValueString()) || (isDeclaredFun(next.value().GetValueString()) >= 0)))
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNotDeclared);




			if (isVariable(next.value().GetValueString()) || isConstant(next.value().GetValueString()))
			{
				int32_t num = _vars_list.top()[next.value().GetValueString()]._offset;
				int32_t insoffset = _instructions_list.size() - 1;
				_instructions_list[insoffset].emplace_back(Operation::LOADA, 0, num);



				_instructions_list[insoffset].emplace_back(Operation::ILOAD);
			}
			else if (isGlobalVariable(next.value().GetValueString()) || isConstantGlobal(next.value().GetValueString()))
			{
				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::LOADA, 1, _global_var_list[next.value().GetValueString()]._offset);

				_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::ILOAD);
			}
			else
			{	if(isDeclaredFun(next.value().GetValueString())<0)
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrInvalidInput);
			else if(_functions_list[isDeclaredFun(next.value().GetValueString())].gettype()==3)
				return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrNoFunciton);

				unreadToken();
				auto err = analyseFunctionCall();

				if (err.has_value())
					return err;
			}
			break;//tobeconfirm;

		case UNSIGNED_INTEGER:
		{try {
			stoi(next.value().GetValueString());//为啥getvalue转不了
		}
		catch (std::out_of_range&) {
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrIntegerOverflow);
		}
		if (_instructions_list.size() == 0)
			_start.emplace_back(Operation::IPUSH, stoi(next.value().GetValueString()));
		else
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IPUSH, stoi(next.value().GetValueString()));


		break;
		}

		case CHAR:
		{
			stoi(next.value().GetValueString());//为啥getvalue转不了
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IPUSH, (int)next.value().GetValueString().c_str()[0]);


			break;
		}

		case HEX_INTERGER:
		{int32_t num;
			try {
				std::string  stoc = next.value().GetValueString();
				num=std::stoi(next.value().GetValueString(), 0, 16);
				
			//num=stoi(next.value().GetValueString(), 0, 0);//为啥getvalue转不了
		}
		catch (std::out_of_range&) {
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrIntegerOverflow);
		}
		if (_instructions_list.size() == 0)
			_start.emplace_back(Operation::IPUSH, num);
		else
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::IPUSH, num);

		break;
		}

		case LEFT_BRACKET:

		{auto err = analyseExpression();
		if (err.has_value())
			return err;
		next = nextToken();
		if (next.value().GetType() != TokenType::RIGHT_BRACKET)
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrIncompleteExpression);
		break;
		}
		// 这里和 <语句序列> 类似，需要根据预读结果调用不同的子程序
		// 但是要注意 default 返回的是一个编译错误
		default:
			return std::make_optional<CompilationError>(_current_pos, ErrorCode::ErrIncompleteExpression);
		}

		// 取负
		if (prefix == -1)
			_instructions_list[_instructions_list.size() - 1].emplace_back(Operation::INEG);

		return {};
	}

	std::optional<Token> Analyser::nextToken() {
		if (_offset == _tokens.size())
			return {};
		// 考虑到 _tokens[0..._offset-1] 已经被分析过了
		// 所以我们选择 _tokens[0..._offset-1] 的 EndPos 作为当前位置
		_current_pos = _tokens[_offset].GetEndPos();
		return _tokens[_offset++];
	}

	void Analyser::unreadToken() {
		if (_offset == 0)
			DieAndPrint("analyser unreads token from the begining.");
		_current_pos = _tokens[_offset - 1].GetEndPos();
		_offset--;
	}


	void Analyser::_add(const Token& tk, std::map<std::string, Variable>& mp, int32_t type) {
		if (tk.GetType() != TokenType::IDENTIFIER)
			DieAndPrint("only identifier can be added to the table.");
		mp[tk.GetValueString()] = Variable(type, mp.size()); //tbc 
	}
	void Analyser::addVariable(const Token& tk, int32_t type) {

		_add(tk, _vars_list.top(), type);
	}
	void Analyser::addVariableGlobal(const Token& tk, int32_t type) {

		_add(tk, _global_var_list, type);


	}
	/*void Analyser::convertUninitializedToVariable(const Token& tk) {
		int32_t stackposition;
		if (_uninitialized_vars.find(tk.GetValueString()) != _uninitialized_vars.end())
		{
			stackposition = _uninitialized_vars[tk.GetValueString()];
			_uninitialized_vars.erase(tk.GetValueString());
			_vars[tk.GetValueString()] = stackposition;
		}


	}*/


	/*(void Analyser::addConstant(const Token& tk, int32_t type) {
		_add(tk, _consts, type);
	}*/

	/*void Analyser::addUninitializedVariable(const Token& tk) {
		_add(tk, _uninitialized_vars);
	}*/

	Variable Analyser::getIndex(const std::string& s) {
		if (_vars_list.top().find(s) != _vars_list.top().end())
			return _vars_list.top()[s];
		else if (_global_var_list.find(s) != _global_var_list.end())
			return _global_var_list[s];

	}

	bool Analyser::isDeclared(const std::string& s) {
		return  isVariable(s) || isConstant(s);
	}
	bool Analyser::isDeclaredGlobal(const std::string& s) {
		return  isGlobalVariable(s) || isGlobalVariable(s);
	}

	bool Analyser::isVariable(const std::string& s) {
		return (_vars_list.top().find(s) != _vars_list.top().end() && ((_vars_list.top()[s]._type == 0) || (_vars_list.top()[s]._type == 1)));
	}
	bool Analyser::isGlobalVariable(const std::string& s) {
		return (_global_var_list.find(s) != _global_var_list.end() && ((_global_var_list[s]._type == 0) || (_global_var_list[s]._type == 1)));
	}

	bool Analyser::isConstant(const std::string& s) {





		return (_vars_list.top().find(s) != _vars_list.top().end() && ((_vars_list.top()[s]._type == 4) || (_vars_list.top()[s]._type == 5)));
	}
	bool Analyser::isConstantGlobal(const std::string& s) {
		return (_global_var_list.find(s) != _global_var_list.end() && ((_global_var_list[s]._type == 4) || (_global_var_list[s]._type == 5)));
	}
	int32_t Analyser::isDeclaredFun(const std::string& s) {
		for (int i = 0; i < _functions_list.size(); ++i)
		{

			if (_functions_list[i].getname() == s) {
				return i;
			}
		}
		return -1;
	}
	int32_t Analyser::get0x(miniplc0::Operation& p) {
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
		return number;
	}
	int32_t Analyser::getparasize(miniplc0::Operation& p) {
		std::string name;
		int32_t number;
		switch (p) {


		case miniplc0::IADD:
		case miniplc0::ISUB:
		case miniplc0::IMUL:
		case miniplc0::IDIV:
		case miniplc0::INEG:
		case miniplc0::ICMP:
		case miniplc0::IPRINT:
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
		case miniplc0::IALOAD:
		case miniplc0::ISTORE:
		case miniplc0::CPRINT:
		case miniplc0::CSCAN:
		case miniplc0::IASTORE:
		case miniplc0::ISCAN:
			return 0;

		case miniplc0::BIPUSH:
			return 1;

		case miniplc0::JE:
		case miniplc0::JNE:
		case miniplc0::JL:
		case miniplc0::JGE:
		case miniplc0::JG:
		case miniplc0::JLE:
		case miniplc0::LOADC:
		case miniplc0::JMP:
		case miniplc0::CALL:
			return 2;

		case miniplc0::IPUSH:
		case miniplc0::SNEW:
			return 4;

		case miniplc0::LOADA:
			return 6;


		}
		//if(num==0)
		return 0;
	}
}