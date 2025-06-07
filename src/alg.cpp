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

std::string infx2pstfx(const std::string& inf) {
  std::stack<char> stack;
  std::string res;
  for (size_t i = 0; i < inf.size(); ++i) {
    if (isdigit(inf[i])) {
      while (i < inf.size() && isdigit(inf[i])) {
        res += inf[i];
        ++i;
      }
      res += ' ';
      --i;
    } else if (inf[i] == '(') {
      stack.push('(');
    } else if (inf[i] == ')') {
      while (!stack.empty() && stack.top() != '(') {
        res += stack.top();
        res += ' ';
        stack.pop();
      }
      if (!stack.empty()) stack.pop();
    } else if (inf[i] == '+'  inf[i] == '-'  inf[i] == '*' || inf[i] == '/') {
      while (!stack.empty() && priority(stack.top()) >= priority(inf[i])) {
        res += stack.top();
        res += ' ';
        stack.pop();
      }
      stack.push(inf[i]);
    }
  }
  while (!stack.empty()) {
    res += stack.top();
    res += ' ';
    stack.pop();
  }
  if (!res.empty() && res.back() == ' ') res.pop_back();
  return res;
}

int eval(const std::string& post) {
  std::stack<int> stack;
  std::istringstream iss(post);
  std::string token;
  while (iss >> token) {
    if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
      stack.push(std::stoi(token));
    } else {
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
  return stack.top();
}
