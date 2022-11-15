#pragma once

#include "virtualMachine.hpp"

#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <tuple>

#define SHIFT_BITS 63 // Albo 31 dla zwykłej maszyny rejestrowej

class EVariableAlreadyDeclaredException : public std::runtime_error
{
private:
	std::string whatMessage;
public:
	EVariableAlreadyDeclaredException(std::string const message) throw();
    char const* what() const throw();
};

class EVariableNotDeclaredException : public std::runtime_error
{
private:
	std::string whatMessage;
public:
	EVariableNotDeclaredException(std::string const message) throw();
    char const* what() const throw();
};

class EUnableToAllocateRegisterException : public std::runtime_error
{
private:
	std::string whatMessage;
public:
	EUnableToAllocateRegisterException(std::string const message) throw();
    char const* what() const throw();
};

class ECompileNonArrayElementException : public std::runtime_error
{
private:
	std::string whatMessage;
public:
	ECompileNonArrayElementException(std::string const message) throw();
    char const* what() const throw();
};

class EInvalidArrayBounds : public std::runtime_error
{
private:
	std::string whatMessage;
public:
	EInvalidArrayBounds(std::string const message) throw();
    char const* what() const throw();
};

class EVariableNotInitialized : public std::runtime_error
{
private:
	std::string whatMessage;
public:
	EVariableNotInitialized(std::string const message) throw();
    char const* what() const throw();
};

enum AllocType
{
	AT_NOT_SET,
	AT_REGISTER,
	AT_CONSTANT,
	AT_VARIABLE,
	AT_ARRAY,
	AT_ARRAY_INDEXED_ELEMENT,
	AT_ARRAY_NAMED_ELEMENT
};

typedef enum AllocType AllocType;

typedef struct
{
	AllocType type;
	long long startAddress;
	long long value;
	long long idx; // Dla elementów tablic indeksowanych liczbą
	std::string idxName; // Dla elementów tablic indeksowanych zmienną
	bool inUse;
	bool initialized;
	std::string name;
	long long size;
	long long arrayIdxStart;
	long long arrayIdxEnd;
	long long arrayIdxConst;
    long long regForB;
}
Value;

typedef struct ArrayElement
{
	std::string * pidentifier;
	long long idx;

	ArrayElement(std::string * name, long long elemIdx)
	{
		pidentifier = name;
		idx = elemIdx;
	}
}
	ArrayElement;

class Instruction
{
public:
	VMInstruction opCode;
	long long argValue;
	std::string comment;

	Instruction()
	{
		opCode = HALT; // Do testów pustych instrukcji
		argValue = -1;
		comment = "";
	}

	Instruction(VMInstruction op)
	{
		opCode = op;
		argValue = -1;
		comment = "";
	}

	Instruction(VMInstruction op, long long value)
	{
		opCode = op;
		argValue = value;
		comment = "";
	}

	Instruction(VMInstruction op, std::string s)
	{
		opCode = op;
		argValue = -1;
		comment = s;
	}

	Instruction(VMInstruction op, long long value, std::string s)
	{
		opCode = op;
		argValue = value;
		comment = s;
	}
};

class CodeGenerator
{
	private:

		// Stałe, rejestry, zmienne i tablice
		std::map <std::string, Value *> mObjects;


		// Pamięć robocza
		const int REG_COUNT = 1024;
		long long vRegIndex = 0;
		std::vector <Value *> vRegisters;
		long long vDataMemoryFreeIdx = REG_COUNT + 1; // 11 z powodu rejestrów

		// Kod maszynowy
		std::vector <Instruction*> vCodeMemory;

		// Etykiety do backpatching
		std::vector <long long> vLabels;

		std::map <VMInstruction, std::tuple <std::string, bool, int> > vMnemonics;

		Value * cConstNeg1 = nullptr;
		Value * cConst1 = nullptr;

	public:

		CodeGenerator();

		Value * newConst(long long value);
		Value * newVariable(std::string name);
		Value * newArray(std::string name, long long startIdx, long long endIdx);

		Value * getConst(long long value);
		Value * getVariable(std::string name, bool bForIndex = false);
		Value * getArray(std::string name);
		Value * getArrayIndexedElement(std::string name, long long idx);
		Value * getArrayNamedElement(std::string name, std::string nameIdx);

		void removeVariable(std::string name);

		bool isArrayElement(Value * v);

		Value * getValue();

		void compileConst(long long addr, long long value);
		void compileArrayElementWithStore(Value * v, std::string comment);
		void compileArrayElementToPn(Value * v, long long idx, std::string comment);
		void compileValueToPn(Value * v, long long idx, std::string comment);

		void pushCode(VMInstruction code);
		void pushCode(VMInstruction code, long long arg);
		void pushCode(VMInstruction code, std::string s);
		void pushCode(VMInstruction code, long long arg, std::string s);

		void compileNegP0(long long fromReg, long long regConst, long long toReg);
		void compile1ToReg(long long regSignDividend);

		void compileDec(long long reg);
		void compileInc(long long reg);

		void compileMul(long long regN, long long regM, long long regAns);
		void compileDiv(long long regDividend, long long regDivisor, long long regAns);

		void compilePreparation();

		long long allocRegister();
		void freeRegister(long long nr);

		long long REG_ADDR(long long regNo);

		void pushLabel(long long addr);
		long long popLabel();
		void popAndSetLabel(long long destAddrToArg);

		long long getCurrentCodeAddr();
		Instruction * getCodeAtAddr(long long addr);

		// Do zapisu do pliku i/lub wyświetlania
		std::string getCodeText(bool withComments, bool withLineNumbers);

};

#define Zero0			codeGen->pushCode(SUB, 0)
#define ZeroN(n)		codeGen->pushCode(SUB, 0); codeGen->pushCode(STORE, n)
#define StoreReg(r) 	codeGen->pushCode(STORE, codeGen->REG_ADDR(r))
