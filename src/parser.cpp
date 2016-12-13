#include "common.hpp"

void Parser::parse(Expr &expr, TokenQueue::iterator& i, int depth) {
    while(i != lexer.tokens.end()) {
        unique_ptr<Value> token = move(*i++);

        if (isType<ExprStart>(*token)) {
            unique_ptr<Expr> subexpression(new Expr);
            parse(*subexpression, i, depth + 1);
            expr.lst.emplace_back(move(subexpression));
        }
        else if (isType<ExprEnd>(*token)) {
            if (depth < 1)
                throw SyntaxError("Missing opening parenthesis.");
            return;
        }
        else {
            expr.lst.emplace_back(move(token));
        }
    }
    if (depth > 0)
        throw SyntaxError("Missing closing parenthesis.");
}

unique_ptr<Expr> Parser::parse() {
    TokenQueue::iterator i = lexer.tokens.begin();
    unique_ptr<Expr> expr(new Expr);
    parse(*expr, i, 0);
    return expr;
}
