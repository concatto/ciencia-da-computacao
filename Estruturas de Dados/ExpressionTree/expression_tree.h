#ifndef EXPRESSION_TREE
#define EXPRESSION_TREE

enum NodeType {Number, Operator};
enum Operation {Division, Multiplication, Addition, Subtraction, None};

struct ExpressionNode {
  double value;
  Operation operation;
  NodeType type;
  ExpressionNode* left;
  ExpressionNode* right;

  ExpressionNode(double value, Operation operation, NodeType type) : value(value), operation(operation), type(type), left(nullptr), right(nullptr) {}
  ExpressionNode(double value) : ExpressionNode(value, Operation::None, NodeType::Number) {}
  ExpressionNode(Operation operation) : ExpressionNode(0, operation, NodeType::Operator) {}

  double evaluate() {
    if (type == NodeType::Number) {
      return value;
    } else {
      double lhs = left->evaluate();
      double rhs = right->evaluate();

      switch (operation) {
      case Division:
        return lhs / rhs;
      case Multiplication:
        return lhs * rhs;
      case Addition:
        return lhs + rhs;
      case Subtraction:
        return lhs - rhs;
      }
    }
  }
};

#endif
