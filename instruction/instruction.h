#pragma once

#include <cstdint>
#include <utility>
#include <string>
#include<vector>
namespace miniplc0 {

	enum Operation {
		CPRINT,
		CSCAN,
		IRET,
		JE,
		JNE,
		JL,
		JGE,
		JG,
		JLE,
		LOADA,
		LOADC,
		IPUSH,
		BIPUSH,
		NEW,
		SNEW,
		POP,
		DUP,
		I2D,
		I2C,
		D2I,
		
		JMP,
		CALL,
		RET,
		TRET,
		ILOAD,
		ISTORE,
		IALOAD,
		IASTORE,
		IADD,
		ISUB,
		IMUL,
		IDIV,
		INEG,
		ICMP,
		IPRINT,
		SPRINT,
		PRINTL,
		ISCAN


	};
	
	class Instruction final {
	private:
		using int32_t = std::int32_t;
	public:
		friend void swap(Instruction& lhs, Instruction& rhs);
	public:
		Instruction(Operation opr) : _opr(opr), _x(0), _y(0) {}
		Instruction(Operation opr, int32_t x) : _opr(opr), _x(x) ,_y(0){}
		Instruction(Operation opr, int32_t x,int32_t y) : _opr(opr), _x(x), _y(y) {}

		//Instruction() : Instruction(Operation::ILL, 0){}
	//	Instruction(const Instruction& i) { _opr = i._opr; _x = i._x; }
		//Instruction(Instruction&& i) :Instruction() { swap(*this, i); }
		/*Instruction& operator=(Instruction i) { swap(*this, i); return *this; }
		bool operator==(const Instruction& i) const { return _opr == i._opr && _x == i._x; }*/
		void backfille(int32_t offset) {
			_x = offset;
		}
		Operation GetOperation() const { return _opr; }
		int32_t GetX() const { return _x; }
		int32_t GetY() const { return _y; }
	private:
		Operation _opr;
		int32_t _x;
		int32_t _y;
	};

	inline void swap(Instruction& lhs, Instruction& rhs) {
		using std::swap;
		swap(lhs._opr, rhs._opr);
		swap(lhs._x, rhs._x);
	};

	class Constants final
	{
	private:
		using int32_t = std::int32_t;
		using string = std::string;
	private:
		
		int32_t _type_code; // STRING = 0,
    // INT = 1,
    // DOUBLE = 2

		std::string _value;
	public:
		Constants(int32_t type, std::string value) : _type_code(type), _value(value) {}

		Constants() : Constants(0, 0) {}
		Constants(const Constants& i) { _type_code=i._type_code, _value=i._value; }
		int32_t gettype() const { return _type_code; }
		std::string getvalue() const { return _value; }


	};
	class Function final
	{
	private:
		
		using int32_t = std::int32_t;
		using string = std::string;
	private:
		std::string _name;
		int32_t _name_index;  //type char0 int 1  double 2 void 3 const char4 const int 5
		int32_t _params_size;//canshu 
		std::vector<int32_t> _para_type;
		std::vector<std::string> _para_name;
	public:
		Function(std::string name, int32_t type, int32_t params, std::vector<int32_t> paratype, std::vector<std::string> paraname) :_name(name), _name_index(type), _params_size(params),_para_type(paratype),_para_name(paraname) {}
		int32_t gettype() const{ return _name_index; }
		std::string getname()const { return _name; }
		int32_t getparasize() const{ return _params_size; }
		int32_t getparatype(int32_t num) { return _para_type[num]; }
		std::string getparaname(int32_t num) { return _para_name[num]; }

		

	};
	class Variable final
	{
	private:

		using int32_t = std::int32_t;
		using string = std::string;
	public:
		int32_t _type;//char0 int 1 double2 void 3 const char4 const int 5
		//int32_t _isconst; //0 no 1 yes
	
		int32_t _offset=0;
	public:
		Variable(std::int32_t type, int32_t offset) : _type(type),_offset(offset) {}
		Variable() :_type(0), _offset(0) {}
		Variable(std::int32_t offset) :Variable(1, offset) {}
		int32_t getoffset() const { return _offset; }
		

	};
	

}