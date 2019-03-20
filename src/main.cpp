#include "../include/PSNR_GPDS.h"
#include "../include/SSIM.h"
#include "../include/PWSSIM.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include <streambuf>
#include <iostream>
#include <string>

#include <cstdio>
#include <cmath>

#include <sstream>

#include <stdio.h>
#include <ctime>
#include <fstream>

using namespace cv;


using namespace std;






int main (int argc, char const* argv[]){
	int n; 
	string file_path_eva 	= argv[1];
	string file_path_ref	= argv[2];

	
	ifstream file_eva;
	ifstream file_ref;


	file_eva.open(file_path_eva);
	file_ref.open(file_path_ref);

	if (!file_eva || !file_ref) {
		cout << "Arquivo não encontrado" << endl;
		exit(1);   // call system to stop
	}

	string ref_img, eva_img;
	while (file_ref >> ref_img && file_eva >> eva_img) {
		cout << "Avaliando as imagens: "<< ref_img << " - " << eva_img << endl;
	
			
		Mat mat_ref 	= imread(ref_img, CV_LOAD_IMAGE_GRAYSCALE);
		Mat mat_eva    	= imread(eva_img, CV_LOAD_IMAGE_GRAYSCALE);



		PSNR_GPDS  psnr;
		SSIM ssim;
		PWSSIM pwssim;

			// /**/
			// cout<< "Entrou na PSNR\n";
			// //============= PSNR ==============
			// psnr.computePSNR(original,teste);
			// psnr.writeResultsInFile();


			// cout<< "\nEntrou na SSIM\n";
			// //==============  SSIM  ===========
			// ssim.computeSSIM(original,teste);
			// ssim.writeResultsInFile();
			// //=================================


		// cout<< "\Calculando PWSSIM\n";
		// ==============  PWSSIM  ===========
		pwssim.computePWSSIM(metodo1_img, metodo2_img);
		pwssim.writeResultsInFile();
		// =================================

			// reference.deallocatePixelMap();
			// test.deallocatePixelMap();
			// reference.closeFile();
			// test.closeFile();
			// imshow("Original", original);
			//  imshow("Teste", teste);
			//  cvWaitKey(0);
	
	}
   
	return 0;

}
