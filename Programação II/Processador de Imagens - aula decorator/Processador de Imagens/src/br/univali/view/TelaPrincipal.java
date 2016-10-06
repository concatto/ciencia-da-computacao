package br.univali.view;

import br.univali.view.processadores.GeradorDeSepia;
import br.univali.view.processadores.Processador;
import br.univali.view.processadores.ProcessadorNulo;
import br.univali.view.processadores.Riscador;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;
import java.awt.image.WritableRaster;
import java.io.File;
import javax.imageio.ImageIO;
import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class TelaPrincipal extends JFrame {

    private static final String DIRETORIO_IMAGENS = "./imagens/";

    private BufferedImage imagemSelecionada;

    private final Processador processador; // a aplicação sempre usará um processador de imagem

    public TelaPrincipal() { //construtor
        initComponents();
        setExtendedState(JFrame.MAXIMIZED_BOTH); //inicia maximizado

        criaListaDeImagens();

        configuraListeners();

        //cria a instância do processador de imagem que será utilizado
        processador = new Riscador(new Riscador(new GeradorDeSepia()));
    }

    private void atualizaPreviewDaImagem() {
        try {
            //processa a imagem selecionada
            if (imagemSelecionada != null) {
                BufferedImage imagemClonada = getClone(imagemSelecionada); //sempre usa um clone para preservar a imagem original. Alguns filtros vão modificar os pixels da imagem original.
                BufferedImage imagemProcessada = processador.processa(imagemClonada);
                painelDaImagem.setImagem(imagemProcessada);
            }
        } catch (Exception excecao) {
            JOptionPane.showMessageDialog(this, excecao);
        }
    }

    private void criaListaDeImagens() {
        File diretorioImagens = new File(DIRETORIO_IMAGENS);
        if (!diretorioImagens.exists()) {
            JOptionPane.showMessageDialog(this, "O diretório das imagens não foi encontrado!");
            return;
        }

        File imagens[] = diretorioImagens.listFiles();// listando todos os arquivos sem filtrar pelo tipo
        DefaultListModel<String> model = new DefaultListModel<>();
        for (File imagem : imagens) {
            model.addElement(imagem.getName());
        }
        listaImagens.setModel(model);
    }

    private void configuraListeners() {
        listaImagens.addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                if (!e.getValueIsAdjusting()) { //evita duplicidade na seleção de imagens
                    carregaImagem(listaImagens.getSelectedValue());
                }
            }
        });
        
        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent ce) {
                painelDaImagem.revalidate();
            }
            
        });
    }

    private void carregaImagem(String nomeDaImagem) {
        try {
            File imagem = new File(DIRETORIO_IMAGENS + nomeDaImagem);
            this.imagemSelecionada = ImageIO.read(imagem);
            painelDaImagem.setImagem(imagem);
            atualizaPreviewDaImagem(); //aplica o processador atual na imagem recém selecionada
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(rootPane, ex);
            imagemSelecionada = null;
        }
    }

    //http://stackoverflow.com/questions/3514158/how-do-you-clone-a-bufferedimage
    private static BufferedImage getClone(BufferedImage bi) {
        ColorModel cm = bi.getColorModel();
        boolean isAlphaPremultiplied = cm.isAlphaPremultiplied();
        WritableRaster raster = bi.copyData(null);
        return new BufferedImage(cm, raster, isAlphaPremultiplied, null);
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        painelDaImagem = new br.univali.view.ImagePanel();
        scrollListaImagens = new javax.swing.JScrollPane();
        listaImagens = new javax.swing.JList<>();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Processador de Imagens");
        setName("tela"); // NOI18N
        getContentPane().setLayout(new java.awt.BorderLayout(12, 0));

        javax.swing.GroupLayout painelDaImagemLayout = new javax.swing.GroupLayout(painelDaImagem);
        painelDaImagem.setLayout(painelDaImagemLayout);
        painelDaImagemLayout.setHorizontalGroup(
            painelDaImagemLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        painelDaImagemLayout.setVerticalGroup(
            painelDaImagemLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 561, Short.MAX_VALUE)
        );

        getContentPane().add(painelDaImagem, java.awt.BorderLayout.CENTER);

        scrollListaImagens.setBorder(javax.swing.BorderFactory.createTitledBorder(null, "Imagens", javax.swing.border.TitledBorder.CENTER, javax.swing.border.TitledBorder.DEFAULT_POSITION, new java.awt.Font("Courier New", 0, 14))); // NOI18N
        scrollListaImagens.setMinimumSize(new java.awt.Dimension(250, 47));
        scrollListaImagens.setPreferredSize(new java.awt.Dimension(270, 154));

        listaImagens.setForeground(new java.awt.Color(153, 153, 153));
        listaImagens.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        listaImagens.setName("listaImagens"); // NOI18N
        scrollListaImagens.setViewportView(listaImagens);

        getContentPane().add(scrollListaImagens, java.awt.BorderLayout.WEST);

        setSize(new java.awt.Dimension(800, 600));
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JList<String> listaImagens;
    private br.univali.view.ImagePanel painelDaImagem;
    private javax.swing.JScrollPane scrollListaImagens;
    // End of variables declaration//GEN-END:variables

    public static void main(String[] args) {
        try {
            javax.swing.UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                TelaPrincipal tela = new TelaPrincipal();
                tela.setVisible(true);
            }
        });

    }

}
