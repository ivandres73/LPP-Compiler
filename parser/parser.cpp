#include "parser.h"

void parser::parse() {
    tk = lex.getNextToken();
    program();
    if (tk != Token::EndFile)
        throw "something's wrong\n";
}

void parser::program() {
    subtypes_section();
    var_section();
    subprogram_decl();
}

void parser::subtypes_section() {
    if (tk == Token::KwTipo) {
        subtype_decl();
        subtypes_section();
    } else{
        /*epsilon*/
    }
}

void parser::subtype_decl() {
    if (tk == Token::KwTipo) {
        tk = lex.getNextToken();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            if (tk == Token::KwEs) {
                tk = lex.getNextToken();
                type();
                if (tk == Token::EndLine)
                    tk = lex.getNextToken();
                else
                    syntaxError("end of line");
            } else
                syntaxError("ES");
        } else
            syntaxError("type");
    } else
            syntaxError("TIPO");    
}

void parser::var_section() {
    if (tokenIs(Token::KwEntero, Token::KwReal, Token::KwCadena, Token::KwBooleano, Token::KwCaracter)) {
        var_decl();
        var_section();
    } else {
        /*epsilon*/
    }
}

void parser::subprogram_decl() {
    if (tokenIs(Token::KwFuncion, Token::KwProcedimiento)) {
        subprogram_header();
        if (tk == Token::EndLine) {
            tk = lex.getNextToken();
            var_section();
            if (tk == Token::KwInicio) {
                tk = lex.getNextToken();
                if (tk == Token::EndLine) {
                    tk = lex.getNextToken();
                    statements();
                    if (tk == Token::KwFin) {
                        tk = lex.getNextToken();
                        if (tk == Token::EndLine) {
                            tk = lex.getNextToken();
                            subprogram_decl();
                        } else
                            syntaxError("end of line");
                    } else {
                        cout << lex.toString(tk) << ", " << lex.getText() << endl;
                        syntaxError("fin");
                    }
                } else
                    syntaxError("end of line");
            } else
                syntaxError("inicio");
        } else
            syntaxError("end of line");
    } else {
        /*epsilon*/
    }
}

void parser::subprogram_header() {
    if (tk == Token::KwFuncion)
        function_header();
    else if (tk == Token::KwProcedimiento)
        procedure_header();
    else
        syntaxError("funcion o procedimiento");
}

void parser::function_header() {
    if (tk == Token::KwFuncion) {
        tk = lex.getNextToken();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            argument_list();
            if (tk == Token::Colon) {
                tk = lex.getNextToken();
                type();
            } else
                syntaxError("colon");
        } else
            syntaxError("identifier");
    } else
        syntaxError("funcion");
}

void parser::procedure_header() {
    if (tk == Token::KwProcedimiento) {
        tk = lex.getNextToken();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            argument_list();
        } else
            syntaxError("identifier");
    } else
        syntaxError("procedimiento");
}

void parser::argument_list() {
    if (tk == Token::OpenParens) {
        tk = lex.getNextToken();
        argument_decl();
        if (tk == Token::CloseParens)
            tk = lex.getNextToken();
        else
            syntaxError("close parens");
    } else
        syntaxError("open parens");
}

void parser::argument_decl() {
    if (tokenIs(Token::KwEntero, Token::KwReal, Token::KwCadena, Token::KwBooleano, Token::KwCaracter)) {
        type();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            more_args();
        } else
            syntaxError("identifier");
    } else if (tk == Token::KwVar) {
        tk = lex.getNextToken();
        type();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            more_args();
        } else
            syntaxError("identifier");
    } else {
        /*epsilon*/
    }
}

void parser::more_args() {
    if (tk == Token::Comma) {
        tk = lex.getNextToken();
        more_args_p();
    } else {
        /*epsilon*/
    }
}

void parser::more_args_p() {
    if (tokenIs(Token::KwEntero, Token::KwReal, Token::KwCadena, Token::KwBooleano, Token::KwCaracter)) {
        type();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            more_args();
        } else
            syntaxError("identifier");
    } else if (tk == Token::KwVar) {
        tk = lex.getNextToken();
        type();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            more_args();
        } else
            syntaxError("identifier");
    } else
        syntaxError("type");
}

void parser::statements() {
    if (tokenIs(Token::Iden, Token::KwLlamar, Token::KwEscriba, Token::KwLea, Token::KwSi))
        statement();
    else {
        /*epsilon*/
    }   
}

void parser::statement() {
    cout << lex.toString(tk) << ": " << lex.getText() << endl;
    if (tk == Token::Iden) {
        lvalue();
        if (tk == Token::Assign) {
            tk = lex.getNextToken();
            expr();
            more_statements();
        }
    } else if (tk == Token::KwLlamar) {
        tk = lex.getNextToken();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            args_call();
            more_statements();
        }
    } else if (tk == Token::KwEscriba) {
        tk = lex.getNextToken();
        string_args();
        more_statements();
    } else if (tk == Token::KwLea) {
        tk = lex.getNextToken();
        lvalue();
        more_statements();
    } else if (tk == Token::KwSi) {
        if_statement();
        more_statements();
    } else
        syntaxError("statement");
}

void parser::if_statement() {
    if (tk == Token::KwSi) {
        tk = lex.getNextToken();
        expr();
        if (tk == Token::EndLine) {
            tk = lex.getNextToken();
            if (tk == Token::KwEntonces) {
                tk = lex.getNextToken();
                cout << "entonces\n";
                if (tk == Token::EndLine) {
                    tk = lex.getNextToken();
                    if_stmt();
                } else
                    syntaxError("end of line");
            } else
                syntaxError("entonces");
        } else
            syntaxError("end of line");
    } else
        syntaxError("SI");
}

void parser::if_stmt() {
    cout << "soy " << lex.toString(tk) << endl;
    if (tk == Token::Iden) {
        lvalue();
        if (tk == Token::Assign) {
            tk = lex.getNextToken();
            expr();
            more_if_stmt();
        }
    } else if (tk == Token::KwLlamar) {
        tk = lex.getNextToken();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            args_call();
            more_if_stmt();
        }
    } else if (tk == Token::KwEscriba) {
        tk = lex.getNextToken();
        string_args();
        more_if_stmt();
    } else if (tk == Token::KwLea) {
        tk = lex.getNextToken();
        lvalue();
        more_if_stmt();
    } else if (tk == Token::KwSi) {
        if_statement();
        more_if_stmt();
    } else
        syntaxError("statement");
}

void parser::more_if_stmt() {
    if (tk == Token::EndLine) {
        cout << "otro if stmt\n";
        tk = lex.getNextToken();
        more_if_stmt_p();
    }
}

void parser::more_if_stmt_p() {
    if (tk == Token::Iden) {
        lvalue();
        if (tk == Token::Assign) {
            tk = lex.getNextToken();
            expr();
            more_if_stmt();
        }
    } else if (tk == Token::KwLlamar) {
        tk = lex.getNextToken();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            args_call();
            more_if_stmt();
        }
    } else if (tk == Token::KwEscriba) {
        tk = lex.getNextToken();
        string_args();
        more_if_stmt();
    } else if (tk == Token::KwLea) {
        tk = lex.getNextToken();
        lvalue();
        more_if_stmt();
    } else if (tk == Token::KwSi) {
        if_statement();
        more_if_stmt();
    } else if (tk == Token::KwSino) {
        else_if_block();
        cout << "aqui\n";
        if (tk == Token::KwFin) {
            tk = lex.getNextToken();
            if (tk == Token::KwSi)
                tk = lex.getNextToken();
        }
    } else if (tk == Token::KwFin) {
        cout << "cerrando if\n";
        tk = lex.getNextToken();
        if (tk == Token::KwSi)
            tk = lex.getNextToken();
        else
            syntaxError("SI");
    } else
        syntaxError("fin si");
}

void parser::else_if_block() {
    if (tk == Token::KwSino) {
        tk = lex.getNextToken();
        cout << "sino\n";
        else_if_block_p();
    } else {
        /*epsilon*/
    }
}

void parser::more_else_if_block() {
    cout << "en more_else_if_block" << lex.toString(tk) << endl;
    if (tk == Token::EndLine) {
        tk = lex.getNextToken();
        else_if_block();
    }
}

void parser::else_if_block_p() {
    if (tk == Token::KwSi) {
        tk = lex.getNextToken();
        expr();
        if (tk == Token::EndLine) {
            tk = lex.getNextToken();
            if (tk == Token::KwEntonces) {
                tk = lex.getNextToken();
                if (tk == Token::EndLine) {
                    tk = lex.getNextToken();
                    statement();
                    more_else_if_block();
                }
            }
        }
    } else if (tokenIs(Token::Iden, Token::KwLlamar, Token::KwEscriba, Token::KwLea, Token::KwSi
                       , Token::EndLine)) {
        cout << "tengo un: " << lex.toString(tk) << endl;
        optional_eol();
        statement();
    }
}

void parser::optional_eol() {
    if (tk == Token::EndLine)
        tk = lex.getNextToken();
    else {
        /*epsilon*/
    }
}

void parser::string_args() {
    cout << "string args: " << lex.toString(tk) << endl;
    if (tk == Token::StringConst) {
        tk = lex.getNextToken();
        more_string_args();
    } else if (tokenIs(Token::Iden, Token::IntConst, Token::CharConst, Token::StringConst, Token::KwVerdadero, Token::KwFalso
                , Token::Sub, Token::KwNo, Token::OpenParens)) {
        expr();
        more_string_args();
    }
}

void parser::more_string_args() {
    if (tk == Token::Comma) {
        tk = lex.getNextToken();
        string_args();
    } else {
        /*epsilon*/cout << "opcion epsilon\n";
    }
}

void parser::more_statements() {
    cout << lex.toString(tk) << endl;
    if (tk == Token::EndLine) {
        tk = lex.getNextToken();
        statements();
    } else {
        /*epsilon*/
    }
}

void parser::lvalue() {
    if (tk == Token::Iden) {
        tk = lex.getNextToken();
        lvalue_p();
    }
}

void parser::lvalue_p() {
    if (tk == Token::OpenBra) {
        tk = lex.getNextToken();
        expr();
        if (tk == Token::CloseBra)
            tk = lex.getNextToken();
        else
            syntaxError("Close Parens");
    } else {
        /*epsilon*/
    }   
}

void parser::rvalue() {
    if (tk == Token::Iden) {
        tk = lex.getNextToken();
        rvalue_p();
    }
}

void parser::rvalue_p() {
    if (tk == Token::OpenBra) {
        tk = lex.getNextToken();
        expr();
        if (tk == Token::CloseBra)
            tk = lex.getNextToken();
    } else if(tk == Token::OpenParens)
        args_call();
    else {
        /*epsilon*/
    } 
}

void parser::args_call() {
    if (tk == Token::OpenParens) {
        tk = lex.getNextToken();
        arg_decl();
        if (tk == Token::CloseParens)
            tk = lex.getNextToken();
        else
            syntaxError("Close Parens");
    }
}

void parser::arg_decl() {
    if (tokenIs(Token::Iden, Token::IntConst, Token::CharConst, Token::StringConst, Token::KwVerdadero, Token::KwFalso
                , Token::Sub, Token::KwNo, Token::OpenParens)) {        expr();
        more_arg_decl();
    } else {
        /*epsilon*/
    }
}

void parser::more_arg_decl() {
    if (tk == Token::Comma) {
        tk = lex.getNextToken();
        arg_decl();
    } else {
        /*epsilon*/
    }
}

void parser::expr() {
    if (tk == Token::Iden)
        rvalue();
    else if (tokenIs(Token::IntConst, Token::CharConst, Token::StringConst, Token::KwVerdadero, Token::KwFalso))
        constant();
    else if (tk == Token::Sub) {
        tk = lex.getNextToken();
        expr();
    } else if (tk == Token::KwNo) {
        tk = lex.getNextToken();
        expr();
    } else if (tk == Token::OpenParens) {
        tk = lex.getNextToken();
        expr();
        if (tk == Token::CloseParens)
            tk = lex.getNextToken();
    }
}

void parser::constant() {
    if (tk == Token::IntConst)
        tk = lex.getNextToken();
    else if (tk == Token::CharConst)
        tk = lex.getNextToken();
    else if (tk == Token::StringConst)
        tk = lex.getNextToken();
    else if (tokenIs(Token::KwVerdadero, Token::KwFalso))
        bool_const();
}

void parser::bool_const() {
    if (tk == Token::KwFalso)
        tk = lex.getNextToken();
    if (tk == Token::KwVerdadero)
        tk = lex.getNextToken();
}

void parser::var_decl() {
    if (tokenIs(Token::KwEntero, Token::KwReal, Token::KwCadena, Token::KwBooleano, Token::KwCaracter)) {
        type();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            more_var();
            if (tk == Token::EndLine)
                tk = lex.getNextToken();
            else
                syntaxError("end of line");
        } else
            syntaxError("identifier");
    } else
        syntaxError("type");
}

void parser::more_var() {
    if (tk == Token::Comma) {
        tk = lex.getNextToken();
        if (tk == Token::Iden) {
            tk = lex.getNextToken();
            more_var();
        } else
            syntaxError("identifier");
    } else {
        /* epsilon */
    }
}

void parser::type() {
    if (tk == Token::KwEntero)
        tk = lex.getNextToken();
    else if (tk == Token::KwReal)
        tk = lex.getNextToken();
    else if (tk == Token::KwCadena)
        tk = lex.getNextToken();
    else if (tk == Token::KwBooleano)
        tk = lex.getNextToken();
    else if (tk == Token::KwCaracter)
        tk = lex.getNextToken();
    else if (tk == Token::KwArreglo)
        array_type();
    else
        syntaxError("type");
}

void parser::array_type() {
    if (tk == Token::KwArreglo) {
        tk = lex.getNextToken();
        if (tk == Token::OpenBra) {
            tk = lex.getNextToken();
            if (tk == Token::IntConst) {
                tk = lex.getNextToken();
                if (tk == Token::CloseBra) {
                    tk = lex.getNextToken();
                    if (tk == Token::KwDe) {
                        tk = lex.getNextToken();
                        type();
                    } else
                        syntaxError("DE");
                } else
                    syntaxError("Close bracket");
            } else
                syntaxError("int constant");
        } else
            syntaxError("Open bracket");
    } else
        syntaxError("arreglo");
}