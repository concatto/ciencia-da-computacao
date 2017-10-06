package br.univali.boolang;

import java.util.function.BiConsumer;

public class Semantico implements Constants {
    private BiConsumer<Integer, Token> handler = null;
    
    public void executeAction(int action, Token token) throws SemanticError {
        if (handler != null) {
            handler.accept(action, token);
        }
    }
    
    public void onAction(BiConsumer<Integer, Token> handler) {
        this.handler = handler;
    }
}
