#ifndef TRIANGLES_MY_LEXER_HH
#define TRIANGLES_MY_LEXER_HH

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include <iostream>


class MyLexer : public yyFlexLexer
{
    std::string cur_lex_;
    std::string cur_val_;

    int process_ws() {
        cur_lex_ = "ws";
        cur_val_ = yytext;
        return 1;
    }

    int process_plus() {
        cur_lex_ = "op";
        cur_val_ = "+";
        return 1;
    }

    int process_minus() {
        cur_lex_ = "op";
        cur_val_ = "-";
        return 1;
    }

    int process_mul() {
        cur_lex_ = "op";
        cur_val_ = "*";
        return 1;
    }

    int process_div() {
        cur_lex_ = "op";
        cur_val_ = "/";
        return 1;
    }

    int process_eq() {
        cur_lex_ = "op";
        cur_val_ = "=";
        return 1;
    }

    int process_gr() {
        cur_lex_ = "op";
        cur_val_ = ">";
        return 1;
    }

    int process_le() {
        cur_lex_ = "op";
        cur_val_ = "<";
        return 1;
    }

    int process_greq() {
        cur_lex_ = "op";
        cur_val_ = ">=";
        return 1;
    }

    int process_leeq() {
        cur_lex_ = "op";
        cur_val_ = "<=>";
        return 1;
    }

    int process_iseq() {
        cur_lex_ = "op";
        cur_val_ = "==";
        return 1;
    }

    int process_digit() {
        cur_lex_ = "num";
        cur_val_ = yytext;
        return 1;
    }

    int process_if() {
        cur_lex_ = "sp wrd";
        cur_val_ = "if";
        return 1;
    }

    int process_while() {
        cur_lex_ = "sp wrd";
        cur_val_ = "while";
        return 1;
    }

    int process_print() {
        cur_lex_ = "sp wrd";
        cur_val_ = "print";
        return 1;
    }

    int process_op_br() {
        cur_lex_ = "br";
        cur_val_ = "{";
        return 1;
    }

    int process_cl_br() {
        cur_lex_ = "br";
        cur_val_ = "}";
        return 1;
    }

    int process_op_br_r() {
        cur_lex_ = "br";
        cur_val_ = "(";
        return 1;
    }

    int process_cl_br_r() {
        cur_lex_ = "br";
        cur_val_ = ")";
        return 1;
    }

    int process_scolon() {
        cur_lex_ = "sc";
        cur_val_ = ";";
        return 1;
    }

    int process_unknown() {
        cur_lex_ = "?";
        cur_val_ = yytext;
        return 1;
    }

public:
    int yylex() override;
    void print_current() const {
        if (cur_lex_ == "ws" || cur_lex_ == "?")
        {
            std::cout << cur_val_;
            return;
        }
        std::cout << cur_val_ << " /*" << cur_lex_ << "*/";
    }
};


#endif //TRIANGLES_MY_LEXER_HH
