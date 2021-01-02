%option yyclass="MyLexer"
%option c++

%{

#include "my_lexer.hh"

%}

WS      [ \t\n\v]+
DIGIT   [0-9]
DIGIT1  [1-9]

%%
{WS}              { return process_ws(); }

"+"               { return process_plus(); }
"-"               { return process_minus(); }
"*"               { return process_mul(); }
"/"               { return process_div(); }
"="               { return process_eq(); }

">"               { return process_gr(); }
"<"               { return process_le(); }
">="              { return process_greq(); }
"<="              { return process_leeq(); }
"=="              { return process_iseq(); }

"if"              { return process_if(); }
"while"           { return process_while(); }
"print"           { return process_print(); }

"{"               { return process_op_br(); }
"}"               { return process_cl_br(); }

"("               { return process_op_br_r(); }
")"               { return process_cl_br_r(); }

";"               { return process_scolon(); }

{DIGIT1}{DIGIT}*  { return process_digit(); }

.                 { return process_unknown(); }
%%

// nothing
