#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>
#include "mpc.h"


int main(int argc, char** argv) {

    /* Create Some Parsers */
    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Lispy    = mpc_new("derpy");

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
            "                                                   \
            number   : /-?[0-9]+/ ;                             \
            operator : '+' | '-' | '*' | '/' ;                  \
            expr     : <number> | '(' <operator> <expr>+ ')' ;  \
            derpy    : /^/ <operator> <expr>+ /$/ ;             \
            ",
            Number, Operator, Expr, Lispy);

    puts("derpy Version 0.0.0.0.1");

    while (1) {
        char* input = readline("> ");
        add_history(input);

        /* Attempt to Parse the user Input */
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
              /* On Success Print the AST */
              mpc_ast_print(r.output);
                mpc_ast_delete(r.output);
        } else {
              /* Otherwise Print the Error */
              mpc_err_print(r.error);
                mpc_err_delete(r.error);
        }


        free(input);
    }

    /* Undefine and Delete our Parsers */
    /* mpc_cleanup(4, Number, Operator, Expr, Lispy); */

    return 0;
}

