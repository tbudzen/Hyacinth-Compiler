%option noyywrap
%option yylineno
     
%{

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstring>

#include "parser.tab.h"

%}

C_IDENTIFIER    [_a-z]
C_DIGIT         -?[0-9]
C_PUNCTUATION	[\(\)\:\;]

%x CMT

%%

"["             { BEGIN(CMT);       }
<CMT>"]"        { BEGIN(INITIAL);   }
<CMT>(\n|.)
<CMT><<EOF>>    { printf("Błąd: niedomknięty komentarz.\n"); yyterminate(); }

"DECLARE"       { return T_DECLARE; }
"BEGIN"         { return T_BEGIN; }
"END"           { return T_END; }

"PLUS" 		{ return T_PLUS; }
"MINUS" 	{ return T_MINUS; }
"TIMES" 	{ return T_TIMES; }
"DIV" 		{ return T_DIV; }
"MOD" 		{ return T_MOD; }

"EQ" 		{ return T_EQ; }
"NEQ" 		{ return T_NEQ; }
"LE" 		{ return T_LE; }
"GE"	 	{ return T_GE; }
"LEQ" 		{ return T_LEQ; }
"GEQ" 		{ return T_GEQ; }

"ASSIGN" 	{ return T_ASSIGN; }

"IF" 		{ return T_IF; }
"THEN" 		{ return T_THEN; }
"ELSE" 		{ return T_ELSE; }
"ENDIF" 	{ return T_ENDIF; }

"WHILE" 	{ return T_WHILE; }
"DO" 		{ return T_DO; }
"ENDWHILE" 	{ return T_ENDWHILE; }
"ENDDO" 	{ return T_ENDDO; }

"FOR" 		{ return T_FOR; }
"FROM" 		{ return T_FROM; }
"TO" 		{ return T_TO; }
"DOWNTO" 	{ return T_DOWNTO; }
"ENDFOR" 	{ return T_ENDFOR; }

"READ" 		{ return T_READ; }
"WRITE" 	{ return T_WRITE; }

","			{ return T_COMMA; }
":"			{ return T_COLON; }
";"			{ return T_SEMICOLON; }
"("			{ return T_LEFT_BRACKET; }
")"			{ return T_RIGHT_BRACKET; }

{C_IDENTIFIER}+         { 
                            yylval.pidentifier = new std::string(yytext);
                            return pidentifier;
                        }
{C_DIGIT}+              { yylval.numberValue = std::stoll(yytext); return numberValue; }



[ \t\r\n]+              {  }

.                       { return -1; }
%%

