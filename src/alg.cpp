// Copyright 2025 NNTU-CS
#include <string>
#include <sstream>
#include <cctype>
#include <stack>

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool isOperator(char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

std::string infx2pstfx(const std::string& input) {
  std::stack<char> stack;
  std::string result;

  for (size_t i = 0; i < input.length(); ++i) {
    char ch = input[i];

    if (isdigit(ch)) {
      while (i < input.length() && isdigit(input[i])) {
        result += input[i];
        ++i;
      }
      result += ' ';
      --i;
    } else if (ch == '(') {
      stack.push(ch);
    } else if (ch == ')') {
      while (!stack.empty() && stack.top() != '(') {
        result += stack.top();
        result += ' ';
        stack.pop();
      }
      if (!stack.empty()) stack.pop();
    } else if (isOperator(ch)) {
      while (!stack.empty() && priority(stack.top()) >= priority(ch)) {
        result += stack.top();
        result += ' ';
        stack.pop();
      }
      stack.push(ch);
    }
  }

  while (!stack.empty()) {
    result += stack.top();
    result += ' ';
    stack.pop();
  }

  if (!result.empty() && result.back() == ' ') result.pop_back();
  return result;
}

int eval(const std::string& postfix) {
  std::stack<int> stack;
  std::istringstream iss(postfix);
  std::string token;

  while (iss >> token) {
    if (isdigit(token[0]) ||
        (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
      stack.push(std::stoi(token));
    } else if (token.size() == 1 && isOperator(token[0])) {
      if (stack.size() < 2) continue;
      int b = stack.top(); stack.pop();
      int a = stack.top(); stack.pop();

      switch (token[0]) {
        case '+': stack.push(a + b); break;
        case '-': stack.push(a - b); break;
        case '*': stack.push(a * b); break;
        case '/': stack.push(a / b); break;
      }
    }
  }

  return stack.empty() ? 0 : stack.top();
}
