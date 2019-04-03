#include <iostream>
#include "PDIUtils.h"
#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
	Mat imagem;
	Mat imagemResultado;
	imagem = imread("Imagens/cores.png");
	imagem = PDIUtils::escalaCinza(imagem);
	
	//Local do processamento

	imshow("Original", imagem);
	//imshow("Resultado", imagemResultado);
	waitKey(0);

    
	return 0;
}