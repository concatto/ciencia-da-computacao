package br.univali.boolang;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.HeadlessException;
import java.awt.event.ActionEvent;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;
import java.util.Stack;
import java.util.function.BiFunction;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.plaf.nimbus.NimbusLookAndFeel;

@SuppressWarnings("serial")
public class Interface_Ide extends JFrame {
    
    private JPanel panel_area_codigo = new JPanel(new BorderLayout());
    private JPanel panel_area_console = new JPanel(new BorderLayout());
    private JPanel panel_botao_executar = new JPanel(new FlowLayout());
    
    private JTextArea area_codigo = new JTextArea();
    private JTextArea area_console = new JTextArea();
    
    private JScrollPane scroll_area_codigo = new JScrollPane(area_codigo);
    private JScrollPane scroll_area_console = new JScrollPane(area_console);
    
    private JButton botao_executar = new JButton("▶");
    
    Sintatico syntactic = new Sintatico();
    Semantico semantic = new Semantico();
    String console_result = "";
    
    private Map<String, Integer> variables = new HashMap<>();
    private Stack<Integer> stack = new Stack<>();
    private Optional<String> targetVariable = Optional.empty();
    
    private void print_console() {
        
       /* variables.forEach((key, value) -> {
            console_result = console_result + key + " => " + value + "\n";
        });
        */
        area_console.setText(console_result);
        console_result = "";
    }
    
    private void completeAssignment() {
        targetVariable.ifPresent(value -> {
            variables.put(value, stack.pop());
            targetVariable = Optional.empty();
        });
    }
    
    private void displayValue() {
        console_result = console_result + stack.pop() + "\n";
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
                  throw new SemanticError("Variavel não encontrada: \"" + token.getLexeme() + "\"", token.getPosition());
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
     private void on_execute() { 
        botao_executar.addActionListener((ActionEvent e) -> {
            Lexico lexical = new Lexico(area_codigo.getText());
            
            try {
                syntactic.parse(lexical, semantic);

                print_console();
            } catch (LexicalError | SemanticError | SyntaticError ex) {
                console_result = ex.getMessage();
                area_console.setText(console_result);
                console_result = "";
            }
        });
    }
    
    public Interface_Ide() throws HeadlessException {
        
        semantic.onAction((action, token) -> {
            handleAction(action, token);
        });
        
        init();
        on_execute();
    }
    
    private void init() {
        try {
            UIManager.setLookAndFeel(new NimbusLookAndFeel());
        } catch (UnsupportedLookAndFeelException ex) {
            Logger.getLogger(Interface_Ide.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        this.setSize(700, 500);
        this.setMinimumSize(new Dimension(500, 400));
        this.setLayout(new BorderLayout());
        this.setTitle("Boolang");
        
        area_console.setEditable(false);
        
        area_codigo.setColumns(5);
        area_codigo.setRows(15);
        
        area_console.setColumns(5);
        area_console.setRows(5);
        
        panel_area_codigo.add(BorderLayout.CENTER, area_codigo);
        panel_botao_executar.add(botao_executar);
        panel_area_console.add(BorderLayout.SOUTH, area_console);
        
        panel_area_codigo.setBorder(BorderFactory.createEmptyBorder(0, 0, 20, 0));
        panel_area_console.setBorder(BorderFactory.createEmptyBorder(0, 0, 20, 0));
        panel_botao_executar.setBorder(BorderFactory.createEmptyBorder(0, 0, 20, 0));
        
        botao_executar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                botao_executarActionPerformed(evt);
            }
        });
        
        getContentPane().add(panel_area_codigo, BorderLayout.CENTER);
        add(BorderLayout.NORTH, panel_botao_executar);
        add(BorderLayout.CENTER, panel_area_codigo);
        add(BorderLayout.SOUTH, panel_area_console);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null); 
    }
    
    private void botao_executarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_botao_executarActionPerformed
        // TODO add your handling code here:
    }
}
