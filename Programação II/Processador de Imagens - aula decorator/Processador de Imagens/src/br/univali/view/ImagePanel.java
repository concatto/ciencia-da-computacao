package br.univali.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.io.File;
import javax.imageio.ImageIO;
import javax.swing.JComponent;

public class ImagePanel extends JComponent {

    private Image imagem;
    private Point margens;
    private Dimension tamanhoDeExibicao;

    //++++++++++++++++++++++++++++++++++++++++
    public void setImagem(Image imagem) throws Exception {
        if (imagem != null) {
            this.imagem = imagem;
            recalculaTamanhoDeExibicao();
            repaint();
        }
    }
    //++++++++++++++++++++++++++++++++++++++++

    public void setImagem(File imagem) throws Exception {
        if (imagem != null) {
            setImagem(ImageIO.read(imagem));
        }
    }
    //++++++++++++++++++++++++++++++++++++++++

    public void setImagem(String imagem) throws Exception {
        setImagem(new File(imagem));
    }

    //++++++++++++++++++++++++++++++++++++++++

    private void recalculaTamanhoDeExibicao() {
        if (imagem == null)
            return;
        
        int larguraRealDaImagem = imagem.getWidth(null);
        int alturaRealDaImagem = imagem.getHeight(null);

        double proporcaoX = getProporcaoHorizontal();
        double proporcaoY = getProporcaoVertical();

        double fatorDeEscala = Math.min(proporcaoX, proporcaoY);
        int larguraDeExibicaoDaImagem = (int) (larguraRealDaImagem * fatorDeEscala);
        int alturaDeExibicaoDaImagem = (int) (alturaRealDaImagem * fatorDeEscala);
        tamanhoDeExibicao = new Dimension(larguraDeExibicaoDaImagem, alturaDeExibicaoDaImagem);

        //recalcula margens
        if (proporcaoX <= proporcaoY) {
            int margem = (int) ((Math.abs(getHeight() - alturaDeExibicaoDaImagem)) / 2.0f);
            margens = new Point(0, margem);
        } else {
            int margem = (int) ((Math.abs(getWidth() - larguraDeExibicaoDaImagem)) / 2.0f);
            margens = new Point(margem, 0);
        }
    }

    @Override
    public void revalidate() {
        super.revalidate();
        recalculaTamanhoDeExibicao();
    }
    
    
    //++++++++++++++++++++++++++++++++++++++++

    private double getProporcaoHorizontal() {
        if (imagem != null) {
            return (double) getWidth() / imagem.getWidth(null);
        }
        return 1;
    }
    //++++++++++++++++++++++++++++++++++++++++

    private double getProporcaoVertical() {
        if (imagem != null) {
            return (double) getHeight() / imagem.getHeight(null);
        }
        return 1;
    }
    //++++++++++++++++++++++++++++++++++++++++

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        if (imagem != null) {
            g.drawImage(imagem,
                    margens.x, margens.y,
                    tamanhoDeExibicao.width, tamanhoDeExibicao.height,
                    Color.WHITE, null);
        }
    }

    public void removeImagem() {
        this.imagem = null;
        repaint();
    }
}
