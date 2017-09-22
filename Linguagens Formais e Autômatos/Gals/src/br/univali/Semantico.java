package br.univali;

import java.util.Stack;
import java.util.function.BiFunction;

public class Semantico implements Constants {
	private Stack<Double> stack = new Stack<>();
	
    public void executeAction(int action, Token token)	throws SemanticError {
    	switch (action) {
    	case 1:
    		stack.push(Double.parseDouble(token.getLexeme()));
    		break;
    	case 2:
    		applyStackOperation((a, b) -> a + b);
    		break;
    	case 3:
    		applyStackOperation((a, b) -> a * b);
    		break;
    	case 4:
    		applyStackOperation((a, b) -> b - a);
    		break;
    	case 5:
    		applyStackOperation((a, b) -> b / a);
    		break;
    	case 6:
    		stack.push(-stack.pop());
    		break;
    	}
    }
    
    private void applyStackOperation(BiFunction<Double, Double, Double> consumer) {
    	stack.push(consumer.apply(stack.pop(), stack.pop()));
    }
    
    public Double getResult() {
    	return stack.peek();
    }
}
