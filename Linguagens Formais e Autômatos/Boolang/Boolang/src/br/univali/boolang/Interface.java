package br.univali.boolang;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.Stack;
import java.util.function.BiFunction;

public class Interface extends javax.swing.JFrame {
    Sintatico syntactic = new Sintatico();
    Semantico semantic = new Semantico();
    String console_result = "";
    
    private Map<String, Integer> variables = new HashMap<>();
    private Stack<Integer> stack = new Stack<>();
    private Optional<String> targetVariable = Optional.empty();
    
    private void dumpVariables() {
        
        variables.forEach((key, value) -> {
            console_result = console_result + key + " => " + value + "\n";
        });
        
        area_de_resultado.setText(console_result);
        console_result = "";
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
    
    public Interface() {
        semantic.onAction((action, token) -> {
            handleAction(action, token);
        });
        
        initComponents();
        on_execute();
    }

    @SuppressWarnings("unchecked")

    private void on_execute() { 
        botao_executar.addActionListener((ActionEvent e) -> {
            Lexico lexical = new Lexico(area_do_codigo.getText());
            
            try {
                syntactic.parse(lexical, semantic);

                dumpVariables();
            } catch (LexicalError | SemanticError | SyntaticError ex) {
                ex.printStackTrace();
            }
        });
    }
    
    private void initComponents() {

        botao_executar = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        area_do_codigo = new javax.swing.JTextArea();
        jScrollPane2 = new javax.swing.JScrollPane();
        area_de_resultado = new javax.swing.JTextArea();

        area_de_resultado.setEditable(false);

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        botao_executar.setText("Executar");
        botao_executar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                botao_executarActionPerformed(evt);
            }
        });

        area_do_codigo.setColumns(20);
        area_do_codigo.setRows(5);
        jScrollPane1.setViewportView(area_do_codigo);

        area_de_resultado.setColumns(20);
        area_de_resultado.setRows(5);
        jScrollPane2.setViewportView(area_de_resultado);

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 380, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(botao_executar)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addComponent(jScrollPane2))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(5, 5, 5)
                .addComponent(botao_executar)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 192, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 78, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>                        

    private void botao_executarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_botao_executarActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_botao_executarActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JTextArea area_de_resultado;
    private javax.swing.JTextArea area_do_codigo;
    private javax.swing.JButton botao_executar;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    // End of variables declaration//GEN-END:variables
}
