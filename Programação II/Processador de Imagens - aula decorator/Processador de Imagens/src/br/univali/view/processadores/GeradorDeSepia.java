package br.univali.view.processadores;

import java.awt.image.BufferedImage;
import java.awt.image.WritableRaster;

/**
 *
 * @author Elieser
 */
public class GeradorDeSepia implements Processador {
    private Processador processador = new ProcessadorNulo();

    public GeradorDeSepia(Processador processador) {
        this.processador = processador;
    }

    public GeradorDeSepia() {
    }
    
    @Override
    public BufferedImage processa(BufferedImage img) throws Exception {
        
        //código retirado de : http://www.rhinocerus.net/forum/lang-java-programmer/574119-sepia-tone-image-filter-java.html

        int sepiaIntensity = 30;

        // Play around with this. 20 works well and was recommended
        // by another developer. 0 produces black/white image
        int sepiaDepth = 20;

        int w = img.getWidth();
        int h = img.getHeight();

        WritableRaster raster = img.getRaster();

        // We need 3 integers (for R,G,B color values) per pixel.
        int[] pixels = new int[w * h * 3];
        raster.getPixels(0, 0, w, h, pixels);

        // Process 3 ints at a time for each pixel. Each pixel has 3 RGB colors in array
        for (int i = 0; i < pixels.length; i += 3) {
            int r = pixels[i];
            int g = pixels[i + 1];
            int b = pixels[i + 2];

            int gry = (r + g + b) / 3;
            r = g = b = gry;
            r += (sepiaDepth * 2);
            g += sepiaDepth;

            if (r > 255) {
                r = 255;
            }
            if (g > 255) {
                g = 255;
            }
            if (b > 255) {
                b = 255;
            }

            // Darken blue color to increase sepia effect
            b -= sepiaIntensity;

            // normalize if out of bounds
            if (b < 0) {
                b = 0;
            }
            if (b > 255) {
                b = 255;
            }

            pixels[i] = r;
            pixels[i + 1] = g;
            pixels[i + 2] = b;
        }
        raster.setPixels(0, 0, w, h, pixels);

        return processador.processa(img);
    }

}
