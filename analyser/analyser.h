#pragma once

#include "error/error.h"
#include "instruction/instruction.h"
#include "tokenizer/token.h"

#include <vector>
#include<queue>
#include <optional>
#include <utility>
#include <map>
#include<stack>
#include <cstdint>
#include <cstddef> // for std::size_t

namespace miniplc0 {

	class Analyser final {
	private:
		using uint64_t = std::uint64_t;
		using int64_t = std::int64_t;
		using uint32_t = std::uint32_t;
		using int32_t = std::int32_t;
	public:
		Analyser(std::vector<Token> v)
			: _tokens(std::move(v)), _offset(0), _start({}), _constants_list({}), _functions_list({}),_instructions_list({}), _current_pos(0, 0),
			_vars_list(), _global_var_list() {}
		Analyser(Analyser&&) = delete;
		Analyser(const Analyser&) = delete;
		Analyser& operator=(Analyser) = delete;
		int32_t get0x(miniplc0::Operation& p);
		int32_t getparasize(miniplc0::Operation& p);

		// 唯一接口
		std::pair<std::vector<Instruction>, std::optional<CompilationError>> Analyse(std::ostream& output);
	private:
		// 所有的递归子程序

		// <程序>
		std::optional<CompilationError> analyseProgram();
		// <主过程>
		std::optional<CompilationError> analyseMain();
		// <常量声明>
		std::optional<CompilationError> analyseConstantDeclaration();
		// <变量声明>
		std::optional<CompilationError> analyseVoidDeclaration();
		std::optional<CompilationError> analyseVariableDeclaration();
		std::optional<CompilationError> ConstInitDeclarator(int32_t type);
		std::optional<CompilationError> VarInitDeclarator(int32_t type);
		std::optional<CompilationError> analyseFunctionDefinition();
		std::optional<CompilationError> analyseParameterClause(int32_t& para, std::vector<int32_t>& paratype, std::vector<std::string>& paraname);
		std::optional<CompilationError> analyseComponetSequence();
		std::optional<CompilationError> analyseParameterDeaclartion(std::vector<int32_t>& paratype, std::vector<std::string>& paraname);
		

		std::optional<CompilationError>  analyseStatementSeq();
		std::optional<CompilationError> analyseConditionStatement();
		std::optional<CompilationError> analyseCondition();

		std::optional<CompilationError> analyseLoopStatement();
		std::optional<CompilationError> analyseJumpStatement();
		std::optional<CompilationError> analyseInputStatement();
		std::optional<CompilationError> analysePrintable();
		// <语句序列>
		std::optional<CompilationError> analyseStatement();
		std::optional<CompilationError> analyseFunctionCall();
		// <常表达式>
		// 这里的 out 是常表达式的值
		std::optional<CompilationError> analyseConstantExpression(int32_t& out);
		// <表达式>
		std::optional<CompilationError> analyseExpression();
		// <赋值语句>
		std::optional<CompilationError> analyseAssignmentStatement();
		// <输出语句>
		std::optional<CompilationError> analyseOutputStatement();
		// <项>
		std::optional<CompilationError> analyseItem();
		// <因子>
		std::optional<CompilationError> analyseFactor();
		

		// Token 缓冲区相关操作
		int32_t funtionnum = 0;
		// 返回下一个 token
		std::optional<Token> nextToken();
		// 回退一个 token
		void unreadToken();

		// 下面是符号表相关操作

		// helper function
		void _add(const Token&, std::map<std::string, Variable>&,  int32_t type);
		// 添加变量、常量、未初始化的变量
		void addVariable(const Token&, int32_t type);//进行了修改  如果是未声明变量，会
		//void addConstant(const Token&, int32_t type);
		void addVariableGlobal(const Token&, int32_t type);
		//void addUninitializedVariable(const Token&);
		//将未初始化变量加入初始化变量
		//void convertUninitializedToVariable(const Token& tk); 
		// 是否被声明过
		bool isDeclared(const std::string&);
		bool isDeclaredGlobal(const std::string&);
		// 是否是未初始化的变量
		bool isVariable(const std::string&);
		// 是否是已初始化的变量
		bool isGlobalVariable(const std::string&);
		// 是否是常量
		bool isConstant(const std::string&);
		bool isConstantGlobal(const std::string&);
		int32_t isDeclaredFun(const std::string&);
		
		// 获得 {变量，常量} 在栈上的偏移
		Variable getIndex(const std::string&);
	public:
		std::vector<Token> _tokens;
		std::size_t _offset;
		std::vector<Instruction> _start;//start
		std::vector<Constants> _constants_list; //常量表
		std::vector<Function> _functions_list; //函数表、
		std::pair<uint64_t, uint64_t> _current_pos;
		std::vector<std::vector<Instruction>> _instructions_list; //函数指令段
		
		
		

		// 为了简单处理，我们直接把符号表耦合在语法分析里
		// 变量                   示例
		// _uninitialized_vars    var a;
		// _vars                  var a=1;
		// _consts                const a=1;
		std::stack<std::map<std::string, Variable >> _vars_list; //变量表
		std::map<std::string, Variable > _global_var_list;
		//std::map<std::string, Variable> _consts;
		// 下一个 token 在栈的偏移
		//int32_t _nextTokenIndex;
		//int32_t nowfuntionindex;
	};
}
