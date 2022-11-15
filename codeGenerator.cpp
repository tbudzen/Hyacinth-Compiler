#include "codeGenerator.hpp"
#include "virtualMachine.hpp"
#include <tuple>
#include <cmath>

//-----------------------------------------------------------------------------

EVariableNotInitialized::EVariableNotInitialized
(std::string const message) throw()
    : std::runtime_error(message)
{
	whatMessage = message;
}

char const * EVariableNotInitialized::what() const throw()
{
    return whatMessage.c_str();
}

//-----------------------------------------------------------------------------

EVariableAlreadyDeclaredException::EVariableAlreadyDeclaredException
(std::string const message) throw()
    : std::runtime_error(message)
{
	whatMessage = message;
}

char const * EVariableAlreadyDeclaredException::what() const throw()
{
    return whatMessage.c_str();
}

//-----------------------------------------------------------------------------

EVariableNotDeclaredException::EVariableNotDeclaredException
(std::string const message) throw()
    : std::runtime_error(message)
{
	whatMessage = message;
}

char const * EVariableNotDeclaredException::what() const throw()
{
    return whatMessage.c_str();
}

//-----------------------------------------------------------------------------

EUnableToAllocateRegisterException::EUnableToAllocateRegisterException
(std::string const message) throw()
    : std::runtime_error(message)
{
	whatMessage = message;
}

char const * EUnableToAllocateRegisterException::what() const throw()
{
    return whatMessage.c_str();
}

//-----------------------------------------------------------------------------

ECompileNonArrayElementException::ECompileNonArrayElementException
(std::string const message) throw()
    : std::runtime_error(message)
{
	whatMessage = message;
}

char const * ECompileNonArrayElementException::what() const throw()
{
    return whatMessage.c_str();
}

//-----------------------------------------------------------------------------

EInvalidArrayBounds::EInvalidArrayBounds
(std::string const message) throw()
    : std::runtime_error(message)
{
	whatMessage = message;
}

char const * EInvalidArrayBounds::what() const throw()
{
    return whatMessage.c_str();
}

//-----------------------------------------------------------------------------

CodeGenerator::CodeGenerator()
{
	std::stringstream ss;
	Value * v;

	vMnemonics[GET] 	= std::make_tuple("GET", false, 100);
	vMnemonics[PUT] 	= std::make_tuple("PUT", false, 100);

	vMnemonics[LOAD] 	= std::make_tuple("LOAD", true, 10);
	vMnemonics[STORE] 	= std::make_tuple("STORE", true, 10);

	vMnemonics[LOADI] 	= std::make_tuple("LOADI", true, 20);
	vMnemonics[STOREI] 	= std::make_tuple("STOREI", true, 20);

	vMnemonics[ADD] 	= std::make_tuple("ADD", true, 10);
	vMnemonics[SUB] 	= std::make_tuple("SUB", true, 10);

	vMnemonics[SHIFT] 	= std::make_tuple("SHIFT", true, 5);

	vMnemonics[INC] 	= std::make_tuple("INC", false, 1);
	vMnemonics[DEC] 	= std::make_tuple("DEC", false, 1);

	vMnemonics[JUMP] 	= std::make_tuple("JUMP", true, 1);
	vMnemonics[JPOS] 	= std::make_tuple("JPOS", true, 1);
	vMnemonics[JZERO] 	= std::make_tuple("JZERO", true, 1);
	vMnemonics[JNEG] 	= std::make_tuple("JNEG", true, 1);

	vMnemonics[HALT] 	= std::make_tuple("HALT", false, 0);

	//-----------------------------------------------------

	vRegisters.reserve(REG_COUNT);

	for (int i = 0; i < REG_COUNT; i++)
	{
		ss.str("");
		ss << "REGISTER_" << i;

		v = new Value();

		v->name = ss.str();
		v->size = 1;
		v->startAddress = (i + 1);
		v->type = AT_REGISTER;
		v->inUse = false;
		v->value = -1;

		vRegisters.push_back(v);
	}

	//-----------------------------------------------------

	compilePreparation();
}

//-----------------------------------------------------------------------------

Value * CodeGenerator::newConst(long long value)
{
	std::string name;
	std::stringstream ss;
	std::map <std::string, Value *>::iterator it;

	ss.str("");
	ss << value;

	//it = mObjects.find(ss.str());
	//if(it == mObjects.end())
	{
		Value * ma = new Value();

		ma->type = AT_CONSTANT;
		ma->startAddress = vDataMemoryFreeIdx++;
		ma->value = value;
		ma->name = ss.str(); // Corrected, was ""
		ma->size = 1;
		ma->arrayIdxStart = -1;
		ma->arrayIdxEnd = -1;

		mObjects[ss.str()] = ma;

		//std::cout << "New const " << value << " at " << ma->startAddress << std::endl;

		return ma;
	}
	//else
	//{
	//	return (*it).second; // Bez błędu - zwracamy już istniejącą stałą
	//}
}

Value * CodeGenerator::newVariable(std::string name)
{
	if(mObjects.find(name) == mObjects.end())
	{
		Value * ma = new Value();

		ma->type = AT_VARIABLE;
		ma->startAddress = vDataMemoryFreeIdx++;
		ma->value = -1;
		ma->initialized = false;
		ma->name = name;
		ma->size = 1;
		ma->arrayIdxStart = -1;
		ma->arrayIdxEnd = -1;

		mObjects[name] = ma;

		return ma;
	}
	else
	{
		throw EVariableAlreadyDeclaredException("Błąd: powtórna deklaracja zmiennej " + name);
	}

}

Value * CodeGenerator::newArray(std::string name, long long startIdx, long long endIdx)
{
	if(mObjects.find(name) == mObjects.end())
	{
		Value * ma = new Value();

		ma->type = AT_ARRAY;
		ma->startAddress = vDataMemoryFreeIdx++; // Was error: Without ++
		ma->value = -1;
		ma->name = name;
		ma->size = endIdx - startIdx + 1;
		if (ma->size < 1)
		{
			throw EInvalidArrayBounds("Błąd: błędny zakres tablicy " + name);
		}
		vDataMemoryFreeIdx += ma->size;
		ma->arrayIdxStart = startIdx;
		ma->arrayIdxEnd = endIdx;
		ma->arrayIdxConst = vDataMemoryFreeIdx ++;

		compileConst(ma->arrayIdxConst, startIdx);

		//std::cout << "newArray from " << startIdx << " to " << endIdx << std::endl;

		mObjects[name] = ma;

		return ma;
	}
	else
	{
		throw EVariableAlreadyDeclaredException("Błąd: powtórna deklaracja tablicy " + name);
	}
}

//-----------------------------------------------------------------------------

Value * CodeGenerator::getConst(long long value)
{
	std::stringstream ss;
	std::map <std::string, Value *>::iterator it;
	Value * ma;

	ss.str("");
	ss << value;

	//it = mObjects.find(ss.str());
	//if(it == mObjects.end())
	//{
		ma = newConst(value);
	//	mObjects[ss.str()] = ma;

		compileConst(ma->startAddress, ma->value); // Dla danej liczby robimy to tylko raz

		return ma;
	//}
	//else
	//{
	//	return (*it).second;
	//}
}

Value * CodeGenerator::getVariable(std::string name, bool bForIndex)
{
	std::map <std::string, Value *>::iterator it;

	it = mObjects.find(name);
	if(it == mObjects.end())
	{
		if (bForIndex)
		{
			return newVariable(name);
		}
		else
		{
			//std::cout << "getVariable(" << name << ") not found" << std::endl;
			throw EVariableNotDeclaredException("Błąd: brak deklaracji zmiennej " + name);
		}
	}
	else
	{
		if((*it).second->type == AT_ARRAY)
		{
			throw EVariableNotDeclaredException("Błąd: użycie tablicy " + name + " jako zmiennej");
		}
		else
		{
			//std::cout << "getVariable(" << name << ") found" << std::endl;
			return (*it).second;
		}
	}
}

void CodeGenerator::removeVariable(std::string name)
{
	mObjects.erase(name);
}

Value * CodeGenerator::getArray(std::string name)
{
	std::map <std::string, Value *>::iterator it;

	it = mObjects.find(name);
	if(it == mObjects.end())
	{
		throw EVariableNotDeclaredException("Błąd: brak deklaracji tablicy " + name);
	}
	else
	{
		if((*it).second->type == AT_VARIABLE)
		{
			throw EVariableNotDeclaredException("Błąd: użycie zmiennej " + name + " jako tablicy");
		}
		else
		{
			return (*it).second;
		}
	}
}

Value * CodeGenerator::getArrayIndexedElement(std::string name, long long idx)
{
	std::map <std::string, Value *>::iterator it;
	Value * v = NULL;

	it = mObjects.find(name);
	if(it == mObjects.end())
	{
		throw EVariableNotDeclaredException(
				"Błąd: brak deklaracji tablicy " + name +
				" przy odwołaniu do jej elementu.");
	}
	else
	{
		if((*it).second->type == AT_VARIABLE)
		{
			throw EVariableNotDeclaredException("Błąd: użycie zmiennej " + name + " jako tablicy");
		}
		else
		{
			v = new Value();

			v->type = AT_ARRAY_INDEXED_ELEMENT;
			v->name = name;
			v->idxName = "";
			v->idx = idx;
			v->size = 1;
			v->startAddress =
					(*it).second->startAddress + idx -
					(*it).second->arrayIdxStart; // Was error: + 1

			return v;
		}
	}
}

Value * CodeGenerator::getArrayNamedElement(std::string name, std::string nameIdx)
{
	std::map <std::string, Value *>::iterator it, itIdx;
	Value * v = NULL;

	it = mObjects.find(name);
	if(it == mObjects.end())
	{
		throw EVariableNotDeclaredException(
				"Błąd: brak deklaracji tablicy " + name +
				" przy odwołaniu do jej elementu.");
	}
	else
	{
		if((*it).second->type == AT_VARIABLE)
		{
			throw EVariableNotDeclaredException("Błąd: użycie zmiennej " + name + " jako tablicy");
		}
		else
		{
			itIdx = mObjects.find(nameIdx);
			if(itIdx == mObjects.end())
			{
				throw EVariableNotDeclaredException(
						"Błąd: brak deklaracji indeksu tablicy " + name);
			}

			v = new Value();

			v->type = AT_ARRAY_NAMED_ELEMENT;
			v->name = name;
			v->idxName = nameIdx;
			v->size = 1;
			v->startAddress = -1; // Do wyliczenia at runtime

			return v;
		}
	}
}

bool CodeGenerator::isArrayElement(Value * v)
{
	return
		(v->type == AT_ARRAY_INDEXED_ELEMENT) ||
		(v->type == AT_ARRAY_NAMED_ELEMENT);
}

//-----------------------------------------------------------------------------

void CodeGenerator::compileConst(long long addr, long long value)
{
	std::stringstream ss;
	long long valueLog2 = 0;
	long long r;
	std::vector <long> partialRegs;

	ss.str("");
	ss << "Kompilacja stałej " << value << " do adresu " << addr;

	pushCode(SUB, 0, ss.str());
	if (value > 0 && value <= 5)
	{
		for (unsigned int i = 0; i < value; i++)
		{
			pushCode(INC);
		}
	}
	else if (value < 0 && value >= -5)
	{
		for (unsigned int i = 0; i < llabs(value); i++)
		{
			pushCode(DEC);
		}
	}
	else if (value > 0)
	{
		r = value; // Remainder
		while (r > 5)
		{
			pushCode(SUB, 0, ss.str());
			pushCode(INC);

			valueLog2 = (long long) std::log2(r);

			for (unsigned int i = 1; i < valueLog2; i++)
			{
				pushCode(INC);
			}

			long long regResult = -1;

			regResult = allocRegister();

			pushCode(STORE, REG_ADDR(regResult));

			pushCode(SUB, 0);
			pushCode(INC);
			pushCode(SHIFT, REG_ADDR(regResult));

			pushCode(STORE, REG_ADDR(regResult));

			partialRegs.push_back(regResult);

			//std::cout << "r, valueLog2, 1 << valueLog2: " << r << ", " << valueLog2 << ", " << (1 << valueLog2) << std::endl;

			r = r - ((long long) 1 << valueLog2);
		}

		pushCode(SUB, 0);
		for (unsigned int i = 0; i < partialRegs.size(); i++)
		{
			pushCode(ADD, partialRegs[i], "");
			freeRegister(partialRegs[i]);
		}

		for (unsigned int i = r; i > 0; i--)
		{
			pushCode(INC);
		}
	}
	else if (value < 0)
	{
		r = llabs(value); // Remainder
		while (r > 5)
		{
			pushCode(SUB, 0, ss.str());
			pushCode(INC);

			valueLog2 = (long long) std::log2(r);

			for (unsigned int i = 1; i < valueLog2; i++)
			{
				pushCode(INC);
			}

			long long regResult = -1;

			regResult = allocRegister();

			pushCode(STORE, REG_ADDR(regResult));

			pushCode(SUB, 0);
			pushCode(INC);
			pushCode(SHIFT, REG_ADDR(regResult));

			pushCode(STORE, REG_ADDR(regResult));

			partialRegs.push_back(regResult);

			r = r - ((long long) 1 << valueLog2);
		}

		pushCode(SUB, 0);
		for (unsigned int i = 0; i < partialRegs.size(); i++)
		{
			pushCode(SUB, partialRegs[i], "");
			freeRegister(partialRegs[i]);
		}

		for (unsigned int i = r; i > 0; i--)
		{
			pushCode(DEC);
		}
	};

	ss.str("");
	ss << "Koniec kompilacji stałej " << value << " do adresu " << addr;

	pushCode(STORE, addr, ss.str());
}

void CodeGenerator::compileArrayElementWithStore(Value * v, std::string comment)
{
	Value * vIdx = NULL;
	Value * vArray = NULL;
	Value * vArrayAddrConst = NULL;
	Value * vArrayStartIdxConst = NULL;
	Value * vIndexConst = NULL;

	long long regResult = -1;
	long long regIdxConst = -1;
	long long regArrayStartIndexAddr = -1;
	long long regElementAddr = -1;

	switch (v->type)
	{
		case(AT_ARRAY_INDEXED_ELEMENT): // STORE
		{
			pushCode(STORE, v->startAddress, comment);
		};
		break;
		case(AT_ARRAY_NAMED_ELEMENT): // STOREI
		{
			//std::cout << "Compiling AT_ARRAY_NAMED_ELEMENT" << std::endl;

			regResult = allocRegister();
			pushCode(STORE, REG_ADDR(regResult), comment);

			vArray = getArray(v->name);
			vIdx = getVariable(v->idxName);

			vIndexConst = getConst(vIdx->startAddress); // Compile if not exists
			vArrayStartIdxConst = getConst(vArray->arrayIdxStart);
			vArrayAddrConst = getConst(vArray->startAddress);

			regIdxConst = allocRegister();
			regArrayStartIndexAddr = allocRegister();

			pushCode(LOAD, vIndexConst->startAddress);
			pushCode(STORE, REG_ADDR(regIdxConst));

			// ADRES = vArrayAddrConst + vIndexAddrConst (7) - vArrayStartIdxConst (5)

			pushCode(LOAD, vArrayStartIdxConst->startAddress);
			pushCode(STORE, REG_ADDR(regArrayStartIndexAddr));

			//std::cout << "Array index start = " << vArray->arrayIdxStart << std::endl;

			pushCode(LOADI, REG_ADDR(regIdxConst));
			pushCode(ADD, vArrayAddrConst->startAddress);
			pushCode(SUB, REG_ADDR(regArrayStartIndexAddr));

			regElementAddr = allocRegister();

			pushCode(STORE, REG_ADDR(regElementAddr));

			pushCode(LOAD, REG_ADDR(regResult));

			pushCode(STOREI, REG_ADDR(regElementAddr));

			freeRegister(regResult);
			freeRegister(regIdxConst);
			freeRegister(regElementAddr);
			freeRegister(regArrayStartIndexAddr);
		}
		break;
		default:
		{
			throw ECompileNonArrayElementException(
				"Błąd wewnętrzny: compileArrayElementWithStore() z obiektem niebędącym elementem tablicy.");
		}
	}
}

void CodeGenerator::compileArrayElementToPn(Value * v, long long idx, std::string comment)
{
	Value * vIdx = NULL;
	Value * vArray = NULL;
	Value * vArrayAddrConst = NULL;
	Value * vArrayStartIdxConst = NULL;
	Value * vIndexAddrConst = NULL;

	//long long regResult = -1;
	long long regIdxConst = -1;
	long long regArrayStartIndexAddr = -1;
	long long regElementAddr = -1;

	switch (v->type)
	{
		case(AT_ARRAY_INDEXED_ELEMENT): // LOAD
		{
			pushCode(LOAD, v->startAddress, comment);
		};
		break;
		case(AT_ARRAY_NAMED_ELEMENT): // LOADI + STORE
		{
			//std::cout << "Compiling AT_ARRAY_NAMED_ELEMENT" << std::endl;

			regIdxConst = allocRegister();
			regArrayStartIndexAddr = allocRegister();
			regElementAddr = allocRegister();

				vArray = getArray(v->name);
				vIdx = getVariable(v->idxName);

				if (vIdx == nullptr)
				{
					throw EVariableNotDeclaredException("Błąd: Nezadeklarowany indeks tablicy " + v->idxName);
				}

					vIndexAddrConst = newConst(vIdx->startAddress);
					compileConst(vIndexAddrConst->startAddress, vIndexAddrConst->value);

					vArrayAddrConst = newConst(vArray->startAddress);
					compileConst(vArrayAddrConst->startAddress, vArrayAddrConst->value);

					vArrayStartIdxConst = newConst(vArray->arrayIdxStart); // Can be negative
					compileConst(vArrayStartIdxConst->startAddress, vArrayStartIdxConst->value);

				pushCode(LOAD, vIndexAddrConst->startAddress);
				pushCode(STORE, REG_ADDR(regIdxConst)); // Ustawiamy adres zmiennej

				// ADRES = vArrayAddrConst - vArrayStartIdxConst + vIndexAddrConst

				pushCode(LOAD, vArrayStartIdxConst->startAddress);
				pushCode(STORE, REG_ADDR(regArrayStartIndexAddr));

				pushCode(LOADI, REG_ADDR(regIdxConst)); // Pobieramy adres zmiennej
				pushCode(ADD, vArrayAddrConst->startAddress);
				pushCode(SUB, REG_ADDR(regArrayStartIndexAddr));

				pushCode(STORE, REG_ADDR(regElementAddr));

			pushCode(LOADI, REG_ADDR(regElementAddr));
			pushCode(STORE, REG_ADDR(idx));

			freeRegister(regIdxConst);
			freeRegister(regElementAddr);
			freeRegister(regArrayStartIndexAddr);
		}
		break;
		default:
		{
			throw ECompileNonArrayElementException(
				"Błąd wewnętrzny: compileArrayElementToP0() z obiektem niebędącym elementem tablicy.");
		}
	}
}

// Wrapper for compileArrayElementToPn and constants and ordinary variables
void CodeGenerator::compileValueToPn
(Value * v, long long idx, std::string comment) // For FOR
{
	switch (v->type)
	{
		case (AT_CONSTANT):
		{
			Value * w = getConst(v->value);
			pushCode(LOAD, w->startAddress, comment);
			if (idx > 0)
			{
				pushCode(STORE, idx, "");
			}
		}
		break;
		case (AT_VARIABLE):
		{
			Value * w = getVariable(v->name);
			if (!w->initialized)
			{
				throw EVariableNotDeclaredException("Błąd: użycie niezainicjowanej zmiennej " + w->name);
			}
			else
			{
				pushCode(LOAD, w->startAddress, comment);
				if (idx > 0)
				{
					pushCode(STORE, idx, "");
				}
			}
		}
		break;
		case (AT_ARRAY_INDEXED_ELEMENT):
		{
			//Value * w = getVariable(v->name);
			//if (!w->initialized)
			//{
			//	throw EVariableNotDeclaredException("Błąd: użycie niezainicjowanej zmiennej " + w->name);
			//}
			//else
			//{
				if (idx > 0)
				{
					pushCode(LOAD, v->startAddress, comment);
					pushCode(STORE, idx);
				}
				else
				{
					pushCode(LOAD, v->startAddress, comment);
				}
			//}
		}
		break;
		case (AT_ARRAY_NAMED_ELEMENT):
		{
			//Value * w = getVariable(v->name);
			//if (!w->initialized)
			//{
			//	throw EVariableNotDeclaredException("Błąd: użycie niezainicjowanej zmiennej " + w->name);
			//}
			//else
			//{
				compileArrayElementToPn(v, idx, comment);
			//}
		}
		break;
		default:
		{
			// Internal error
		}
		break;
	}
}
//-----------------------------------------------------------------------------

void CodeGenerator::pushLabel(long long addr)
{
	//std::cout << "pushLabel(" << addr << ")" << std::endl;
	vLabels.push_back(addr);
}

long long CodeGenerator::popLabel()
{
	long long label;

	if (vLabels.size() > 0)
	{
		label = vLabels.back();
		vLabels.pop_back();
	}
	else
	{
		label = -1;
	}

	return label;
}

void CodeGenerator::popAndSetLabel(long long destAddrToArg)
{
	long long addr = -1;

	if (vLabels.size() > 0)
	{
		addr = vLabels[vLabels.size() - 1];

		vLabels.pop_back();

		//std::cout << "popAndSetLabel(" << addr << ") = " << destAddrToArg << std::endl;

		vCodeMemory[addr]->argValue = destAddrToArg;
	}
	else
	{
		// Internal error
	}
}

//-----------------------------------------------------------------------------

long long CodeGenerator::allocRegister()
{
	for (int i = 1; i < REG_COUNT; i++)
	{
		if (!vRegisters[i]->inUse)
		{
			vRegisters[i]->inUse = true;

			return i;
		}
	}

	throw EUnableToAllocateRegisterException("Błąd: Nie udało się zaalokować rejestru.");
}

void CodeGenerator::freeRegister(long long nr)
{
	if (vRegisters[nr]->inUse)
	{
		vRegisters[nr]->inUse = false;
	}
}

long long CodeGenerator::REG_ADDR(long long regNo)
{
	return (regNo);
}

//-----------------------------------------------------------------------------

void CodeGenerator::pushCode(VMInstruction code)
{
	vCodeMemory.push_back(new Instruction(code, -1));
}

void CodeGenerator::pushCode(VMInstruction code, long long arg)
{
	vCodeMemory.push_back(new Instruction(code, arg));
}

void CodeGenerator::pushCode(VMInstruction code, std::string s)
{
	vCodeMemory.push_back(new Instruction(code, s));
}

void CodeGenerator::pushCode(VMInstruction code, long long arg, std::string s)
{
	vCodeMemory.push_back(new Instruction(code, arg, s));
}

#define CODE getCurrentCodeAddr()

long long CodeGenerator::getCurrentCodeAddr()
{
	long long addr;

	addr = vCodeMemory.size() - 1;

	//std::cout << "getCurrentCodeAddr() = " << addr << std::endl;

	return addr;
}

Instruction* CodeGenerator::getCodeAtAddr(long long addr)
{
	return vCodeMemory[addr];
}

std::string CodeGenerator::getCodeText(bool withComments, bool withLineNumbers)
{
	std::string code;
	std::tuple <std::string, bool, int> t;
	std::stringstream ss;

	code = "";
	for (unsigned int i = 0; i < vCodeMemory.size(); i++)
	{
			if (withLineNumbers)
			{
				ss.str("");
				ss << i;
				code += ss.str() + ": ";
			}
			t = vMnemonics[vCodeMemory[i]->opCode];
			code += std::get <0> (t);
			if ((bool) std::get <1> (t))
			{
				ss.str("");
				ss << vCodeMemory[i]->argValue;
				code += " " + ss.str();
			}
			if (withComments && vCodeMemory[i]->comment != "")
			{
				code += " # " + vCodeMemory[i]->comment;
			}
		code += "\n";
	}

	return code;
}

//------------------------------------------------------------------------

void CodeGenerator::compileNegP0(long long fromReg, long long regConst, long long toReg)
{
	long long regMul2;

	regMul2 = allocRegister();

	pushCode(LOAD, REG_ADDR(fromReg), "compileNegP0");
	pushCode(SHIFT, REG_ADDR(regConst));

	pushCode(STORE, REG_ADDR(regMul2));

	pushCode(LOAD, REG_ADDR(fromReg));
	pushCode(SUB, REG_ADDR(regMul2));

	pushCode(STORE, REG_ADDR(toReg));

	freeRegister(regMul2);
}

void CodeGenerator::compile1ToReg(long long reg)
{
	pushCode(SUB, 0, "compile1ToReg");
	pushCode(INC);
	pushCode(STORE, REG_ADDR(reg));
}

void CodeGenerator::compileMul(long long regN, long long regM, long long regAns)
{
	/*
	int multiply(int n, int m)
	{
	    int ans = 0, count = 0;
	    while (m)
	    {
	        // check for set bit and left
	        // shift n, count times
	        if (m % 2 == 1)
	        {
	            ans += n << count;
	  		}

	        // increment of place value (count)
	        count++;
	        m /= 2;
	    }
	    return ans;
	}
	*/

	long long regN0, regM0, regCount,
		regConst1, regConstNeg2, regConstNeg1, regSignN, regSignM;

	regN0 = allocRegister();
	regM0 = allocRegister();
	regCount = allocRegister();
	regConst1 = allocRegister();
	regConstNeg2 = allocRegister();
	regConstNeg1 = allocRegister();
	regSignN = allocRegister();
	regSignM = allocRegister();

	// regConst1 = 1

	pushCode(SUB, 0, "-------------- START MUL, regConst1 = 1");
	pushCode(INC);
	pushCode(STORE, REG_ADDR(regConst1), "");

	// regConstNeg2 = 2

	pushCode(SUB, 0, "regConstNeg2 = 2");
	pushCode(DEC);
	pushCode(DEC);
	pushCode(STORE, REG_ADDR(regConstNeg2), "");

	// regConstNeg1 = -1

	pushCode(SUB, 0, "regConstNeg1 = -1");
	pushCode(DEC);
	pushCode(STORE, REG_ADDR(regConstNeg1), "");

	// regSignN = 0, regSignM = 0

	pushCode(SUB, 0);
	pushCode(STORE, REG_ADDR(regSignN), "STORE regSignN");

	pushCode(SUB, 0);
	pushCode(STORE, REG_ADDR(regSignM), "STORE regSignM");


// if regN < 0 then ...
	// ... regN = -regN (= regN - 2*regN) ...
	// signN = 1 (denotes minus)

	pushCode(LOAD, REG_ADDR(regN), "");
	pushCode(JNEG, getCurrentCodeAddr() + 3, "regN < 0");
	pushCode(JUMP, getCurrentCodeAddr() + 11);
	compileNegP0(regN, regConst1, regN);
	compile1ToReg(regSignN);

	// ans = 0

	pushCode(SUB, 0, "ans = 0");
	pushCode(STORE, REG_ADDR(regAns), "");

	// count = 0

	pushCode(SUB, 0, "count = 0");
	pushCode(STORE, REG_ADDR(regCount), "");

// if regM < 0 then ...
	// ... regM = -regM (= regM - 2*regM) ...
	// signM = 1 (denotes minus)

	pushCode(LOAD, REG_ADDR(regM), "");
	pushCode(JNEG, getCurrentCodeAddr() + 3, "if regM < 0 then ...");
	pushCode(JUMP, getCurrentCodeAddr() + 11); // Label1
	compileNegP0(regM, regConst1, regM);
	compile1ToReg(regSignM);

// While loop:
// Label_0:

	long long label_0 = getCurrentCodeAddr() + 1;

	pushCode(LOAD, REG_ADDR(regM), "while (m)");

	// If m (p0) > 0

	pushCode(JPOS, getCurrentCodeAddr() + 3, "if (m > 0)");
	pushCode(JUMP, -1, "");

/****/	pushLabel(getCurrentCodeAddr());

		// If m % 2 == 1
		// 		m%2 = m - 2*(m/2) [ m - regM0 ]

		pushCode(LOAD, REG_ADDR(regM));
		pushCode(SHIFT, REG_ADDR(regConstNeg1));
		pushCode(SHIFT, REG_ADDR(regConst1));
		pushCode(STORE, REG_ADDR(regM0));
		pushCode(LOAD, REG_ADDR(regM));
		pushCode(SUB, REG_ADDR(regM0));
		pushCode(DEC);

		pushCode(JZERO, getCurrentCodeAddr() + 3, "if (m % 2) = 1"); // Label_1
		pushCode(JUMP, -1); // Label_count++

/****/	pushLabel(getCurrentCodeAddr());

			// 		ans += n << count;

			pushCode(LOAD, REG_ADDR(regN), "n0 = n << count");
			pushCode(SHIFT, REG_ADDR(regCount));
			pushCode(STORE, REG_ADDR(regN0));

			pushCode(LOAD, REG_ADDR(regAns), "ans += n0");
			pushCode(ADD, REG_ADDR(regN0));
			pushCode(STORE, REG_ADDR(regAns));

// endif

/****/	popAndSetLabel(CODE + 1);

	pushCode(LOAD, REG_ADDR(regCount), "count ++");
	pushCode(INC, REG_ADDR(regCount));
	pushCode(STORE, REG_ADDR(regCount));

	// m /= 2

	pushCode(LOAD, REG_ADDR(regM), "m /= 2");
	pushCode(SHIFT, REG_ADDR(regConstNeg1));
	pushCode(STORE, REG_ADDR(regM));

	pushCode(JUMP, label_0); // Label_0

// end if

// Label_End

	// return ans in P0

/****/		popAndSetLabel(CODE + 1);

	// if
	//		(signM = 1 and signN = 0) OR
	//		(signM = 0 and signN = 1)
	// then p0 = -p0  (signM + signN == 1, that is XOR)

	pushCode(LOAD, REG_ADDR(regSignN));
	pushCode(ADD, REG_ADDR(regSignM));
	pushCode(DEC);
	pushCode(JZERO, getCurrentCodeAddr() + 3); // LabelNeg
	pushCode(JUMP, getCurrentCodeAddr() + 8); // LabelExit

// LabelNeg:

	compileNegP0(regAns, regConst1, regAns);

// LabelExit:
	// Zwolnienie rejestrów i stałych

	pushCode(LOAD, REG_ADDR(regAns));
	//pushCode(PUT);

	freeRegister(regCount);
	freeRegister(regN0);
	freeRegister(regM0);

	freeRegister(regSignN);
	freeRegister(regSignM);

	freeRegister(regConstNeg1);
	freeRegister(regConst1);
	freeRegister(regConstNeg2);
}

void CodeGenerator::compileDec(long long reg)
{
	pushCode(LOAD, REG_ADDR(reg));
	pushCode(DEC);
	pushCode(STORE, REG_ADDR(reg));
}

void CodeGenerator::compileInc(long long reg)
{
	pushCode(LOAD, REG_ADDR(reg));
	pushCode(INC);
	pushCode(STORE, REG_ADDR(reg));
}


void CodeGenerator::compileDiv(long long regDividend, long long regDivisor, long long regAns)
{
	/*
	unsigned divide(unsigned dividend, unsigned divisor)
	{
		unsigned denom=divisor;
		unsigned current = 1;
		unsigned answer=0;

		if ( denom > dividend)
			return 0;

		if ( denom == dividend)
			return 1;

		while (denom <= dividend) {
			denom <<= 1;
			current <<= 1;
		}

		denom >>= 1;
		current >>= 1;

		while (current!=0) {
			if ( dividend >= denom) {
				dividend -= denom;
				answer |= current;
			}
			current >>= 1;
			denom >>= 1;
		}
		return answer;
    }
    */

	long long
		regDivisor0, regDividend0, regDenom, regCurrent, regAnswer,
		regDividendSign, regDivisorSign;

	regDenom = allocRegister();
	regCurrent = allocRegister();
	regAnswer = allocRegister();

	regDividendSign = allocRegister();
	regDivisorSign = allocRegister();

	regDivisor0 = allocRegister();
	regDividend0 = allocRegister();

	// Zerujemy rejestry tymczasowe

	pushCode(SUB, 0, "-------------- START DIV");
	pushCode(STORE, REG_ADDR(regDenom));
	pushCode(STORE, REG_ADDR(regCurrent));
	pushCode(STORE, REG_ADDR(regAnswer));
	pushCode(STORE, REG_ADDR(regDividendSign));
	pushCode(STORE, REG_ADDR(regDivisorSign));

	// Sprawdzamy i ustawiamy znaki, co będzie potrzebne na końcu
	// i jeśli ujemne to negujemy Dividend i Divisor.

	pushCode(LOAD, REG_ADDR(regDivisor), "if divisor == 0 then return 0");
	pushCode(JZERO, CODE + 3);
	pushCode(JUMP, CODE + 5);

	pushCode(SUB, 0);
	pushCode(STORE, REG_ADDR(regAnswer));
	pushCode(JUMP, -1);
pushLabel(CODE);

	pushCode(LOAD, REG_ADDR(regDivisor), "if divisor < 0 then store sign and negate");
	pushCode(STORE, REG_ADDR(regDivisor0));
	pushCode(JNEG, CODE + 3);
	pushCode(JUMP, CODE + 11);
	compileNegP0(regDivisor, cConst1->startAddress, regDivisor);
	pushCode(SUB, 0); // Ustawienie znaku Divisor
	pushCode(INC);
	pushCode(STORE, REG_ADDR(regDivisorSign));

	pushCode(LOAD, REG_ADDR(regDividend), "if dividend < 0 then store sign and negate");
	pushCode(STORE, REG_ADDR(regDividend0));
	pushCode(JNEG, CODE + 3);
	pushCode(JUMP, CODE + 11);
	compileNegP0(regDividend, cConst1->startAddress, regDividend);
	pushCode(SUB, 0); // Ustawienie znaku Dividend
	pushCode(INC);
	pushCode(STORE, REG_ADDR(regDividendSign));

	//unsigned denom=divisor;
	//unsigned current = 1;
	//unsigned answer=0;

	pushCode(LOAD, REG_ADDR(regDivisor));
	pushCode(STORE, REG_ADDR(regDenom));

	pushCode(SUB, 0);
	pushCode(STORE, REG_ADDR(regAnswer));

	pushCode(SUB, 0);
	pushCode(INC);
	pushCode(STORE, REG_ADDR(regCurrent));

	//if ( denom > dividend)
	//	return 0;

	pushCode(LOAD, REG_ADDR(regDenom), "if (denom > dividend)");
	pushCode(SUB, REG_ADDR(regDividend));
	pushCode(JPOS, CODE + 3); // denom > dividend
	pushCode(JUMP, CODE + 4); // to 1st while

	pushCode(SUB, 0); // return 0
	pushCode(JUMP, -1); // End of div
pushLabel(CODE);

//if ( denom == dividend)
//	return 1;
//	pushCode(SUB, 0); // return 1
//	pushCode(INC); // return 1
//	pushCode(JUMP, -1); // End of div
//pushLabel(CODE);

//// 1st while -----------------------------------------------------------------------
//while (denom <= dividend) {
//	denom <<= 1;
//	current <<= 1;
//}

	pushCode(LOAD, REG_ADDR(regDenom), "while (denom <= dividend)");
	pushCode(SUB, REG_ADDR(regDividend));
	pushCode(JNEG, CODE + 4); // denom < dividend, go inside while
	pushCode(JZERO, CODE + 3); // denom == dividend, go inside while
	pushCode(JUMP, CODE + 9); // after while

		//	denom <<= 1;

		pushCode(LOAD, REG_ADDR(regDenom), "denom <<= 1");
		pushCode(SHIFT, cConst1->startAddress);
		pushCode(STORE, REG_ADDR(regDenom));

		//	current <<= 1;

		pushCode(LOAD, REG_ADDR(regCurrent), "current <<= 1");
		pushCode(SHIFT, cConst1->startAddress);
		pushCode(STORE, REG_ADDR(regCurrent));

	// Back to while

	pushCode(JUMP, CODE - 10, "back to 1st while");

	//}
//// End of 1st while -----------------------------------------------------------------------

	// denom >>= 1;

	pushCode(LOAD, REG_ADDR(regDenom), "denom >>= 1");
	pushCode(SHIFT, cConstNeg1->startAddress);
	pushCode(STORE, REG_ADDR(regDenom));

	// current >>= 1;

	pushCode(LOAD, REG_ADDR(regCurrent), "current >>= 1");
	pushCode(SHIFT, cConstNeg1->startAddress);
	pushCode(STORE, REG_ADDR(regCurrent));

//// 2nd while -----------------------------------------------------------------------

	//while (current!=0) {
	//	if ( dividend >= denom) {
	//		dividend -= denom;
	//		answer |= current;
	//	}
	//	current >>= 1;
	//	denom >>= 1;
	//}

	pushCode(LOAD, REG_ADDR(regCurrent), "2nd while - while (current!=0)");
	pushCode(JPOS, CODE + 3); // Inside 2nd while
	pushCode(JUMP, -1); // After 2nd while
pushLabel(CODE);

	//	if ( dividend >= denom) {

		pushCode(LOAD, REG_ADDR(regDividend), "if (dividend >= denom)");
		pushCode(SUB, REG_ADDR(regDenom));
		pushCode(JPOS, CODE + 4); // Inside if
		pushCode(JZERO, CODE + 3);
		pushCode(JUMP, CODE + 8); // Outside if, rest of while

		//		dividend -= denom;
		//		answer |= current;

			pushCode(LOAD, REG_ADDR(regDividend), "dividend -= denom");
			pushCode(SUB, REG_ADDR(regDenom));
			pushCode(STORE, REG_ADDR(regDividend));

			pushCode(LOAD, REG_ADDR(regAnswer), "answer |= current");
			pushCode(ADD, REG_ADDR(regCurrent));
			pushCode(STORE, REG_ADDR(regAnswer));

		//		}

		//	current >>= 1;
		//	denom >>= 1;

		pushCode(LOAD, REG_ADDR(regDenom), "current >>= 1");
		pushCode(SHIFT, cConstNeg1->startAddress);
		pushCode(STORE, REG_ADDR(regDenom));

		pushCode(LOAD, REG_ADDR(regCurrent), "denom >>= 1");
		pushCode(SHIFT, cConstNeg1->startAddress);
		pushCode(STORE, REG_ADDR(regCurrent));

	pushCode(JUMP, CODE - 19, "to 2nd while"); // To 2nd while

//// End of 2nd while -----------------------------------------------------------------------

popAndSetLabel(CODE + 1);
popAndSetLabel(CODE + 1);

	pushCode(LOAD, REG_ADDR(regDividendSign));
	pushCode(ADD, REG_ADDR(regDivisorSign));
	pushCode(DEC);

	pushCode(JZERO, CODE + 3); // Mamy różne znaki, answer = -answer, oraz ...
	pushCode(JUMP, -1);
pushLabel(CODE);
	compileNegP0(regAnswer, cConst1->startAddress, regAnswer);

	// ... jeżeli w dodatku mamy resztę to odejmujemy 1

	pushCode(LOAD, REG_ADDR(regDividend));
	pushCode(JPOS, CODE + 3);
	pushCode(JUMP, -1);
pushLabel(CODE);

	pushCode(LOAD, REG_ADDR(regAnswer));
	pushCode(DEC);
	pushCode(STORE, REG_ADDR(regAnswer));

	// return regAnswer in p0

	popAndSetLabel(CODE + 1);
	popAndSetLabel(CODE + 1);
	popAndSetLabel(CODE + 1);
	pushCode(LOAD, REG_ADDR(regAnswer), "return ans in p0");
	pushCode(STORE, REG_ADDR(regAns));

	//-------------------------------------------------------------

	freeRegister(regDenom);
	freeRegister(regCurrent);
	freeRegister(regAnswer);
	freeRegister(regDivisor0);
	freeRegister(regDividend0);
	freeRegister(regDividendSign);
	freeRegister(regDivisorSign);
}

void CodeGenerator::compilePreparation()
{
	cConst1 = newConst(1);
	compileConst(cConst1->startAddress, cConst1->value);
	cConstNeg1 = newConst(-1);
	compileConst(cConstNeg1->startAddress, cConstNeg1->value);
}
