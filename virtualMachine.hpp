#pragma once

enum VMInstruction : int
{ 
	GET, 
	PUT, 

	LOAD, 
	STORE, 

	LOADI, 
	STOREI, 

	ADD, 
	SUB, 

	SHIFT, 

	INC, 
	DEC, 

	JUMP, 

	JPOS, 
	JZERO, 
	JNEG, 

	HALT
};

typedef enum VMInstruction VMInstruction;



