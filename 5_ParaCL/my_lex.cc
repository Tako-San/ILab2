#include <iostream>
#include <memory>

#include "my_lexer.hh"

int yyFlexLexer::yywrap() {
    return 1;
}

int main()
{
    auto lexer = std::make_unique<MyLexer>();
    while(lexer->yylex() != 0) {
        lexer->print_current();
    }
    std::cout << std::endl;
    return 0;
}