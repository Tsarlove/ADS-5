// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "tstack.h"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;
    std::istringstream iss(inf);
    char token;

    while (iss >> token) {
        if (isdigit(token)) {
            result += token;
            while (iss.peek() != EOF && isdigit(iss.peek())) {
                char next;
                iss >> next;
                result += next;
            }
            result += ' ';
        } else if (token == '(') {
            stack.push(token);
        } else if (token == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                result += stack.pop();
                result += ' ';
            }
            if (!stack.isEmpty()) stack.pop();  // удаляем '('
        } else if (token == '+'  token == '-'  token == '*' || token == '/') {
            while (!stack.isEmpty() && precedence(stack.top()) >= precedence(token)) {
                result += stack.pop();
                result += ' ';
            }
            stack.push(token);
        }
    }

    while (!stack.isEmpty()) {
        result += stack.pop();
        result += ' ';
    }

    if (!result.empty() && result.back() == ' ')
        result.pop_back();

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;
    std::istringstream iss(post);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0])) {
            stack.push(std::stoi(token));
        } else {
            int b = stack.pop();
            int a = stack.pop();
            int result;
            switch (token[0]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default: result = 0; // не должно возникать
            }
            stack.push(result);
        }
    }

    return stack.pop();
}
