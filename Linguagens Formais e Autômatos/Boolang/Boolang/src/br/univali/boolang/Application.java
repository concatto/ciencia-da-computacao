/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package br.univali.boolang;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.Stack;
import java.util.function.BiFunction;

/**
 *
 * @author 5928036
 */
public class Application {
    private Map<String, Integer> variables = new HashMap<>();
    private Stack<Integer> stack = new Stack<>();
    private Optional<String> targetVariable = Optional.empty();
    
    private void dumpVariables() {
        variables.forEach((key, value) -> {
            System.out.println(key + " => " + value);
        });
    }
    
    private void completeAssignment() {
        targetVariable.ifPresent(value -> {
            variables.put(value, stack.pop());
            targetVariable = Optional.empty();
        });
    }
    
    private void displayValue() {
        System.out.println("Output: " + stack.pop());
    }
    
    private void modifyStack(BiFunction<Integer, Integer, Integer> operation) {
        int a = stack.pop();
        int b = stack.pop();
        stack.push(operation.apply(a, b));
    }
    
    private void handleAction(int action, Token token) throws SemanticError {
        switch (action) {
            case 0:
                targetVariable = Optional.of(token.getLexeme());
                break;
            case 1:
                completeAssignment();
                break;
            case 2:
                displayValue();
                break;
            case 3:
                stack.push(Integer.parseUnsignedInt(token.getLexeme(), 2));
                break;
            case 4:
                // Se a variável não existe
                if (!variables.containsKey(token.getLexeme())) {
                  throw new SemanticError("Variable not found: \"" + token.getLexeme() + "\"", token.getPosition());
                }
                
                stack.push(variables.get(token.getLexeme()));
                break;
            case 5:
                modifyStack((a, b) -> a + b);
                break;
            case 6:
                modifyStack((a, b) -> b - a);
                break;
            case 7:
                modifyStack((a, b) -> a * b);
                break;
            case 8:
                modifyStack((a, b) -> b / a);
                break;
            case 9:
                modifyStack((a, b) -> (int) Math.pow(b, a));
                break;
        }
    }
    
    public Application() {
        String program = "a <- 111 + 0101 + c; print b;";
        Sintatico syntactic = new Sintatico();
        Lexico lexical = new Lexico(program);
        Semantico semantic = new Semantico();
        
        semantic.onAction((action, token) -> {
          handleAction(action, token);
        });
        
        try {
            syntactic.parse(lexical, semantic);
            
            dumpVariables();
        } catch (LexicalError | SemanticError | SyntaticError ex) {
            ex.printStackTrace();
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new Application();
    }    
}
