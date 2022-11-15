%{
#include "stdio.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <fstream>

#include "codeGenerator.hpp"

std::stringstream ss;
CodeGenerator * codeGen = NULL;
int compilationErrorCount = 0;
Value * v;

int yylex();
int yyparse();
void yyerror(char const *s);

extern FILE *yyin;
extern int yylineno;
extern char * yytext;

%}

// Rekord semantyczny

%union sem_rec
{
    std::string * pidentifier;
    long long numberValue;
    void * value; // Value pointer
}

// Tokeny

%start program

%token T_DECLARE T_BEGIN T_END

%token T_PLUS T_MINUS T_TIMES T_DIV T_MOD

%token T_EQ T_NEQ T_LE T_GE T_LEQ T_GEQ

%token T_ASSIGN

%token T_IF T_THEN T_ELSE T_ENDIF
%token T_WHILE T_DO T_ENDWHILE T_ENDDO
%token T_FOR T_FROM T_TO T_DOWNTO T_ENDFOR

%token T_READ T_WRITE

%token T_COMMA T_SEMICOLON T_COLON T_LEFT_BRACKET T_RIGHT_BRACKET

%token <numberValue> numberValue
%token <pidentifier> pidentifier

%type <value> value // zmienna lub stała
%type <value> identifier

%%    

program:
		T_DECLARE 
		{ 
			//std::cout << "Program with declare section" << std::endl; 
		
			codeGen->compilePreparation(); 
		}
		declarations          
       	T_BEGIN  
       	{}
		commands           
        T_END
        {	
			codeGen->pushCode(HALT);	
		}
	|      
       	T_BEGIN  
       	{
       		codeGen->compilePreparation();
       	}
		commands         
        T_END	
        {	
			codeGen->pushCode(HALT);	
		}
;

declarations:
	pidentifier
		{
			v = codeGen->newVariable($1->c_str());
		}
	|
	pidentifier T_LEFT_BRACKET numberValue T_COLON numberValue T_RIGHT_BRACKET
		{
			v = codeGen->newArray($1->c_str(), $3, $5);
		}
	|
	declarations T_COMMA pidentifier
		{
			v = codeGen->newVariable($3->c_str());
		}
	|
	declarations T_COMMA pidentifier T_LEFT_BRACKET numberValue T_COLON numberValue T_RIGHT_BRACKET
		{
			v = codeGen->newArray($3->c_str(), $5, $7);
		}
	|
;

commands:       
	commands command 
		{}
        | 
	command 
		{}      
;

command:
	identifier T_ASSIGN expression T_SEMICOLON
		{ 				
			if (codeGen->isArrayElement((Value *)$1))
			{
				codeGen->compileArrayElementWithStore((Value *)$1, ss.str());
			}
			else
			{
				((Value *)$1)->initialized = true;
				codeGen->pushCode(STORE, ((Value *)$1)->startAddress);
			}
		}
	|
	T_IF condition		
		T_THEN commands 
		T_ELSE 	 
		{ 
			// Jump Endif at first before Else commands
			codeGen->pushCode(JUMP, -1);
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 1);
			
			codeGen->pushLabel(codeGen->getCurrentCodeAddr()); // After pop
		} 
		commands 	
		T_ENDIF
		{
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 1);
		}
	|
	T_IF 
		condition 
		T_THEN commands 
		{ 
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 1);
		} 
		T_ENDIF
	|
	T_WHILE 
	{
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
	}
	condition T_DO commands 
		{ 
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 2); // From condition
			codeGen->pushCode(JUMP, codeGen->popLabel() + 1);
		}
		T_ENDWHILE
	|
	T_DO 
	{
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
	}
	commands T_WHILE condition T_ENDDO
		{ 
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 2); // From condition
			codeGen->pushCode(JUMP, codeGen->popLabel() + 1);
		}
	|
	T_FOR pidentifier T_FROM value T_TO value T_DO 
		{			
			/*
				FOR I = Va TO Vb DO Cmds ENDFOR
			
				LOAD Va // $4
				STORE I
				
				LOAD Vb // $6, Must NOT be calculated dynamically
				STORE tempReg
				
			Loop:
				
				LOAD I
				SUB tempReg
				STORE I
				
				JPOS EndFor
				
				... Cmds
				
				LOAD I
				INC
				STORE I
				
				JUMP Loop
				
			EndFor:
				HALT		
			*/
				
			long long regB;
							
			regB = codeGen->allocRegister();		
			
			// LOAD A
					
			codeGen->compileValueToPn((Value*)$4, 0, "Kompilacja FOR FROM TO");
			
			// STORE I
			
			Value * va;
			va = codeGen->getVariable($2->c_str(), true);
			va->initialized = true;
			
			codeGen->pushCode(STORE, va->startAddress);
				
			// LOAD B
			
			codeGen->compileValueToPn((Value*)$6, 0, "");
			
			// STORE tmpB
			
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regB));
			
			((Value *)$6)->regForB = regB;
			
		// Loop:	
			
			codeGen->pushLabel(codeGen->getCurrentCodeAddr());
			
			// LOAD I
			
			codeGen->pushCode(LOAD, va->startAddress);
			
			// SUB tmpB
			
			codeGen->pushCode(SUB, codeGen->REG_ADDR(regB));
			
			// JPOS EndFor			
						
			codeGen->pushCode(JPOS, -1, "");
			
			codeGen->pushLabel(codeGen->getCurrentCodeAddr());		
		}
		
	commands
	 
	T_ENDFOR
	{				
			/*
				LOAD I
				INC
				STORE I
				JUMP Loop
			EndFor:
			*/
			
			Value * va;
			va = codeGen->getVariable($2->c_str());
			
			codeGen->pushCode(LOAD, va->startAddress);
			codeGen->pushCode(INC);
			codeGen->pushCode(STORE, va->startAddress);
					
			// Backpatch JPOS EndFor
			// Simply top of labels stack	
				
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 2);
			
			// JUMP Loop
			
			codeGen->pushCode(JUMP, codeGen->popLabel() + 1);
					
			codeGen->freeRegister(((Value*)$6)->regForB);	
			
			// Remove idx variable - see error8.txt problem
			
			codeGen->removeVariable($2->c_str());	
	}
	|
	T_FOR pidentifier T_FROM value T_DOWNTO value T_DO
		{ 			
			/*
				FOR I = Va TO Vb DO Cmds ENDFOR
			
				LOAD Va // $4
				STORE I
			
				LOAD Vb // $6, Must NOT be calculated dynamically
				STORE tempReg
				
			Loop:
				
				LOAD I
				SUB tempReg
				STORE I
				
				JNEG EndFor
				
				... Cmds
				
				LOAD I
				DEC
				STORE I
				
				JUMP Loop
				
			EndFor:
				HALT		
			*/
			
			long long regB;
					
			regB = codeGen->allocRegister();		
					
			// LOAD A
					
			codeGen->compileValueToPn((Value*)$4, 0, "Kompilacja FOR FROM DOWNTO");
			
			// STORE I
			
			Value * va;
			
			va = codeGen->getVariable($2->c_str(), true);
			va->initialized = true;
			codeGen->pushCode(STORE, va->startAddress, "<--");
			
			// LOAD B
			
			codeGen->compileValueToPn((Value*)$6, 0, "");
			
			// STORE regB
			
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regB));
			
			((Value*)$6)->regForB = regB;
			
			
		// Loop:	
			
			codeGen->pushLabel(codeGen->getCurrentCodeAddr());
			
			// LOAD I
			
			codeGen->pushCode(LOAD, va->startAddress);
			
			// SUB tmpB
			
			codeGen->pushCode(SUB, codeGen->REG_ADDR(regB));
			
			// JNEG EndFor			
						
			codeGen->pushCode(JNEG, -1, "");
				codeGen->pushLabel(codeGen->getCurrentCodeAddr());
							
		}
		commands T_ENDFOR
		{		
			/*
				LOAD I
				DEC
				STORE I
				JUMP Loop
			EndFor:
			*/
				
			Value * vi;
				
			vi = codeGen->getVariable($2->c_str());
			
			codeGen->pushCode(LOAD, vi->startAddress);
			codeGen->pushCode(DEC);
			codeGen->pushCode(STORE, vi->startAddress);
					
			// Backpatch JNEG EndFor
			// Simply top of labels stack	
				
			codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr() + 2);
			
			// JUMP Loop
			
			codeGen->pushCode(JUMP, codeGen->popLabel() + 1);		
			
			codeGen->freeRegister(((Value*)$6)->regForB);	
			
			// Remove idx variable - see error8.txt problem
			
			codeGen->removeVariable($2->c_str());				
		}
	|
	T_READ identifier T_SEMICOLON
		{ 			
			codeGen->pushCode(GET, "");
			
			if (codeGen->isArrayElement((Value *)$2))
			{
				codeGen->compileArrayElementWithStore((Value *)$2, ss.str());
			}
			else
			{
				v = codeGen->getVariable(((Value *)$2)->name.c_str());
				v->initialized = true;
				codeGen->pushCode(STORE, v->startAddress);
			}
		}
	|
	T_WRITE value T_SEMICOLON
		{ 
			codeGen->compileValueToPn((Value *)$2, 0, "");
			codeGen->pushCode(PUT);
		}	
;

expression:
	numberValue
		{
			v = codeGen->getConst($1);
			codeGen->pushCode(LOAD, v->startAddress);
		}
	|
	value
		{
			if (codeGen->isArrayElement((Value *)$1))
			{
				codeGen->compileArrayElementToPn((Value *)$1, 0, "");
			}
			else
			{
				//v = codeGen->getVariable(((Value*)$1)->name.c_str());
				//codeGen->pushCode(LOAD, v->startAddress);
				
				codeGen->compileValueToPn(codeGen->getVariable(((Value*)$1)->name.c_str()), 0, "");
			}
		}
	|
	value T_PLUS value
		{
			long long REG_A = codeGen->allocRegister();
			if (codeGen->isArrayElement((Value *)$1))
			{
				codeGen->compileArrayElementToPn((Value *)$1, 0, "Compilation of first array element of PLUS");
			}
			else
			{
				codeGen->pushCode(LOAD, ((Value *)$1)->startAddress, "Compilation of first normal value of PLUS");
			}
			codeGen->pushCode(STORE, codeGen->REG_ADDR(REG_A));
			
			if (codeGen->isArrayElement((Value *)$3))
			{
				codeGen->compileArrayElementToPn((Value *)$3, 0, "Compilation of second array element of PLUS");
			}
			else
			{
				codeGen->pushCode(LOAD, ((Value *)$3)->startAddress, "Compilation of second normal value of PLUS");
			}
			
			codeGen->pushCode(ADD, codeGen->REG_ADDR(REG_A));
			
			codeGen->freeRegister(REG_A);
		}
	|
	value T_MINUS value
		{
			long long REG_A = codeGen->allocRegister();
			if (codeGen->isArrayElement((Value *)$3))
			{
				codeGen->compileArrayElementToPn((Value *)$3, codeGen->REG_ADDR(REG_A), "Compilation of second array element of MINUS");
			}
			else
			{
				codeGen->pushCode(LOAD, ((Value *)$3)->startAddress, "Compilation of second normal value of MINUS");
				codeGen->pushCode(STORE, codeGen->REG_ADDR(REG_A));
			}
			
			if (codeGen->isArrayElement((Value *)$1))
			{
				codeGen->compileArrayElementToPn((Value *)$1, 0, "Compilation of first array element of MINUS");
			}
			else
			{
				codeGen->pushCode(LOAD, ((Value *)$1)->startAddress, "Compilation of first normal value of MINUS");
			}
			
			codeGen->pushCode(SUB, codeGen->REG_ADDR(REG_A));
			
			codeGen->freeRegister(REG_A);
		}
	|
	value T_TIMES value
		{			
			long long regN, regM, regAns;
			
			regN 	= codeGen->allocRegister();
			regM 	= codeGen->allocRegister();
			regAns 	= codeGen->allocRegister();		
			
			// regN = n
		
			codeGen->compileValueToPn((Value *) $1, 0, "regN = n");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regN));
			
			// regM = m
		
			codeGen->compileValueToPn((Value *) $3, 0, "regM = m");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regM));
	
			// Multiplication
	
			codeGen->compileMul(regN, regM, regAns); // <<<<<<<<<<<<<<<<<<<<<
			codeGen->pushCode(LOAD, codeGen->REG_ADDR(regAns));
			
			// Cleanup
			
			codeGen->freeRegister(regN);
			codeGen->freeRegister(regM);	
			codeGen->freeRegister(regAns);		
		}
	|
	value T_MOD value
		{
			/*
			
				(dividend -7/ divisor 3) => quotient -2
				-2 * 3 => -6
				so a%b => -1
				
				(7/-3) => -2
				-2 * -3 => 6
				so a%b => 1
				
				(-7/-3) => 2
				2 * -3 => -6
				so a%b => -1
			
			*/
			
			long long 
				regDividend, regDividend0, regDivisor, regDivisor0, regAns, regDivisorMulQuotient;		
		
			regDividend = codeGen->allocRegister();
			regDividend0 = codeGen->allocRegister();
			regDivisor = codeGen->allocRegister();
			regDivisor0 = codeGen->allocRegister();
			regAns = codeGen->allocRegister();
			regDivisorMulQuotient = codeGen->allocRegister();
		
			// regDividend = n

			codeGen->compileValueToPn((Value *) $1, 0, "regDividend = n");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDividend));
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDividend0));		
			
			// regDivisor = m

			codeGen->compileValueToPn((Value *) $3, 0, "regDivisor = m");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDivisor));
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDivisor0));
						
			// If regDivisor == 0 return 0;
			
			codeGen->pushCode(JZERO, codeGen->getCurrentCodeAddr() + 3);
			codeGen->pushCode(JUMP, codeGen->getCurrentCodeAddr() + 5);
			
			codeGen->pushCode(SUB, 0);
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regAns));
			codeGen->pushCode(JUMP, -1);
				codeGen->pushLabel(codeGen->getCurrentCodeAddr());
						
			// Division
			
			codeGen->compileDiv(regDividend, regDivisor, regAns);
			//codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDividend0));
			//codeGen->pushCode(PUT);
			//codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDivisor0));
			//codeGen->pushCode(PUT);
			
			// Multiplication
			
			codeGen->compileMul(regDivisor0, regAns, regDivisorMulQuotient);
			//codeGen->pushCode(PUT);
			
			//codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDivisor0));
			//codeGen->pushCode(PUT);
			//codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDivisorMulQuotient));
			//codeGen->pushCode(PUT);
			
			// Subtraction, 
			// Mod is dividend (-33) - divisor (7) * quotient (-5) = 2
			// Mod is dividend (33) - divisor (-7) * quotient (-5) = -2			
			
			codeGen->pushCode(LOAD, codeGen->REG_ADDR(regDividend0));
			codeGen->pushCode(SUB, codeGen->REG_ADDR(regDivisorMulQuotient));
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regAns));
			
				codeGen->popAndSetLabel(codeGen->getCurrentCodeAddr());
			
			// Cleanup
			
			codeGen->freeRegister(regDividend);
			codeGen->freeRegister(regDivisor);
			codeGen->freeRegister(regDividend0);
			codeGen->freeRegister(regDivisor0);
			codeGen->freeRegister(regAns);
			codeGen->freeRegister(regDivisorMulQuotient);							
		}
	|
	value T_DIV value
		{
			/*
				// Function to divide a by b and 
				// return floor value it 
				int divide(long long dividend, long long divisor) { 
				  
				  // Calculate sign of divisor i.e., 
				  // sign will be negative only iff 
				  // either one of them is negative 
				  // otherwise it will be positive 
				  int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1; 
				  
				  // remove sign of operands 
				  dividend = abs(dividend); 
				  divisor = abs(divisor); 
				  
				  // Initialize the quotient 
				  long long quotient = 0, temp = 0; 
				  
				  // test down from the highest bit and 
				  // accumulate the tentative value for 
				  // valid bit 
				  for (int i = 31; i >= 0; --i) { 
				  
				    if (temp + (divisor << i) <= dividend) { 
				      temp += divisor << i; 
				      quotient |= 1LL << i; 
				    } 
				  } 
				  
				  return sign * quotient; 
				} 
			*/

			long long regDividend, regDivisor, regAns;
			
			regDividend = codeGen->allocRegister();
			regDivisor = codeGen->allocRegister();
			regAns = codeGen->allocRegister();

			// regDividend = n

			codeGen->compileValueToPn((Value *) $1, 0, "regDividend = n");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDividend));		
			
			// regDivisor = m

			codeGen->compileValueToPn((Value *) $3, 0, "regDivisor = m");
			codeGen->pushCode(STORE, codeGen->REG_ADDR(regDivisor));	
			
			// Division
			
			codeGen->compileDiv(regDividend, regDivisor, regAns);
			
			// Cleanup
			
			codeGen->freeRegister(regDividend);
			codeGen->freeRegister(regDivisor);
			codeGen->freeRegister(regAns);
		}
;

condition:
	value T_EQ value
	{		
		long long reg = codeGen->allocRegister();
		
		codeGen->compileValueToPn((Value*)$3, reg, "CONDITION EQ");		
		codeGen->compileValueToPn((Value*)$1, 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JZERO, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}
	|
	value T_NEQ value
	{
		long long reg = codeGen->allocRegister();
		
		codeGen->compileValueToPn((Value*)$3, reg, "CONDITION NEQ");		
		codeGen->compileValueToPn((Value*)$1, 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JPOS, codeGen->getCurrentCodeAddr() + 4); // Ommit next JUMP
		codeGen->pushCode(JNEG, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}
	|
	value T_LE value
	{
		long long reg = codeGen->allocRegister();
			
		codeGen->compileValueToPn((Value*)$3, reg, "CONDITION LE");	
		codeGen->compileValueToPn((Value*)$1, 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JNEG, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}
	|
	value T_GE value
	{
		long long reg = codeGen->allocRegister();
			
		codeGen->compileValueToPn((Value*)$3, reg, "CONDITION GE");	
		codeGen->compileValueToPn((Value*)$1, 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JPOS, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}
	|
	value T_LEQ value
	{
		long long reg = codeGen->allocRegister();
			
		codeGen->compileValueToPn((Value*)$3, reg, "CONDITION LEQ");	
		codeGen->compileValueToPn((Value*)$1, 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JNEG, codeGen->getCurrentCodeAddr() + 4); // Ommit next JUMP
		codeGen->pushCode(JZERO, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}
	|
	value T_GEQ value
	{
		long long reg = codeGen->allocRegister();
			
		codeGen->compileValueToPn((Value*)$3, reg, "CONDITION GEQ");	
		codeGen->compileValueToPn((Value*)$1, 0, "");
		
		codeGen->pushCode(SUB, codeGen->REG_ADDR(reg));
		codeGen->pushCode(JPOS, codeGen->getCurrentCodeAddr() + 4); // Ommit next JUMP
		codeGen->pushCode(JZERO, codeGen->getCurrentCodeAddr() + 3); // Ommit next JUMP
			
		codeGen->pushCode(JUMP, -1);
		codeGen->pushLabel(codeGen->getCurrentCodeAddr());
		
		codeGen->freeRegister(reg);
	}
;

value:
	numberValue
		{
			$$ = codeGen->getConst($1);
		}
	|
	identifier
		{
		}
;

identifier:
	pidentifier
		{
			$$ = codeGen->getVariable($1->c_str());
		}
	|
	pidentifier T_LEFT_BRACKET pidentifier T_RIGHT_BRACKET
		{
			$$ = codeGen->getArrayNamedElement($1->c_str(), $3->c_str());
		}
	|
	pidentifier T_LEFT_BRACKET numberValue T_RIGHT_BRACKET
		{
			$$ = codeGen->getArrayIndexedElement($1->c_str(), $3);
		}
;

%%

int main(int argc, char ** argv)
{
	bool error = false;
	char * srcFilename = NULL;
	char * destFilename = NULL;

	//std::cout << "Witamy w kompilatorze Lab_4." << std::endl;

	if (argc == 3)
	{
		srcFilename = argv[1];
		destFilename = argv[2];

		FILE * fileIn;
		fileIn = fopen(srcFilename, "r");
	
		if(fileIn)
		{
	    	yyin = fileIn;

        	std::cout << "Kompilowanie \"" << srcFilename << "\" do \"" << destFilename << "\"..." << std::endl;

			codeGen = new CodeGenerator();

			try
			{
        		yyparse();        		
        	
	  			std::fstream fileOut;
	  			
	  			fileOut.open (destFilename, std::fstream::trunc | std::fstream::out);  
	 			fileOut << codeGen->getCodeText(true, false);
	  			fileOut.close();
	        	
	        	std::cout << "Kompilacja zakończona sukcesem." << std::endl;   
	        	//std::cout << "--------------------------------------------" << std::endl;       	
	        	//std::cout << codeGen->getCodeText(true, true); 
        	}
        	catch (const EVariableAlreadyDeclaredException & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}
        	catch (const EVariableNotDeclaredException & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}
        	catch (const EUnableToAllocateRegisterException & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}      
        	catch (const ECompileNonArrayElementException & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}  	
        	catch (const EInvalidArrayBounds & e)
        	{
        		error = true;
        		std::cout << "Linia " << yylineno << ": " << e.what() << std::endl;
        	}       	
  
        	delete codeGen;
        	
    		if (error) return -1;
        }
        else
        {	
        	std::cout << "Błąd: Nie udało się otworzyć pliku wejściowego." << std::endl;
        	
    		return -1;
        }
	}
	else
	{
		std::cout << "Błąd: Niepoprawna liczba argumentów - wymagane są dwie nazwy plików." << std::endl;
		
    	return -1;
	}

	return 0;
}


void yyerror(char const *s) 
{
		std::cout << s << " - Linia nr " << yylineno << ": " << yytext << std::endl;
        exit(0);
}
