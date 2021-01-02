%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::NumDriver* driver}

%code requires
{
#include <iostream>
#include <string>

// forward decl of argument to parser
namespace yy { class NumDriver; }
}

%code
{
#include "numdriver.hpp"

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         NumDriver* driver);
}
}

%token
  EQUAL   "="
  MINUS   "-"
  PLUS    "+"
  SCOLON  ";"
  ERR
;

%token <int> NUMBER
%nterm <int> equals
%nterm <int> expr

%left '+' '-'

%start program

%%

program: eqlist
;

eqlist: equals SCOLON eqlist
| equals SCOLON
;

equals: expr EQUAL expr       { 
                                $$ = ($1 == $3); 
                                std::cout << "Checking: " << $1 << " vs " << $3 
                                          << "; Result: " << $$
                                          << std::endl; 
                              }
;

expr: NUMBER                  { $$ = $1; }
| expr PLUS expr              { $$ = $1 + $3; }
| expr MINUS expr             { $$ = $1 - $3; }
;

%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         NumDriver* driver)
{
  return driver->yylex(yylval);
}

void parser::error(const std::string&){}
}
