#include <iostream>
#include <limits>
#include <cstdlib>
#include "expression_tree.h"

Operation classifyOperation(char operation) {
  switch (operation) {
  case '+':
    return Operation::Addition;
  case '-':
    return Operation::Subtraction;
  case '*':
    return Operation::Multiplication;
  case '/':
    return Operation::Division;
  }

  return Operation::None;
}

int getPriority(char c) {
  if (c == '+' || c == '-') {
    return 1;
  } else if (c == '*' || c == '/') {
    return 0;
  }
  return -1;
}

int findLowest(std::string expression) {
  int parentheses = 0;
  int lowestValue = std::numeric_limits<int>::max();
  int lowestIndex = -1;
  for (int i = 0; i < expression.length(); i++) {
    if (expression[i] == '(') {
      parentheses++;
    } else if (expression[i] == ')') {
      parentheses--;
    }

    int value = getPriority(expression[i]);
    if (value == -1) continue;

    if (parentheses > 0) value = 10 + value + parentheses;
    if (value <= lowestValue) {
      lowestValue = value;
      lowestIndex = i;
    }
  }

  return lowestIndex;
}

std::string extractNumber(std::string s) {
  int first = -1;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9') {
      if (first == -1) {
        first = i;
        break;
      }
    }
  }

  return s.substr(first);
}

ExpressionNode* buildTree(std::string expression) {
  int index = findLowest(expression);
  if (index != -1) {
    ExpressionNode* node = new ExpressionNode(classifyOperation(expression[index]));

    std::string left = expression.substr(0, index);
    std::string right = expression.substr(index + 1);

    std::cout << "operation: " << expression[index] << "; left: " << left << "; right: " << right << std::endl;
    node->left = buildTree(left);
    node->right = buildTree(right);
    return node;
  } else {
    return new ExpressionNode(std::atof(extractNumber(expression).c_str()));
  }
}

void print(ExpressionNode* node, int depth = 0) {
  if (node == nullptr) return;

  std::cout << std::string(depth, ' ');
  std::string names[] = {"div", "mult", "add", "sub"};
  if (node->type == NodeType::Operator) {
    std::cout << names[node->operation] << "\n";
  } else {
    std::cout << node->value << "\n";
  }

  depth++;
  print(node->left, depth);
  print(node->right, depth);
}

int main() {
  std::string str = "(((64) * (32)) * (4 * 8.0)) - 1";

  ExpressionNode* root = buildTree(str);
  print(root);

  std::cout << "result: " << root->evaluate() << std::endl;
}
