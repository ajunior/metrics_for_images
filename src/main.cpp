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
#include <stdio.h>
#include <ctime>
#include <fstream>

using namespace cv;


using namespace std;






int main (int argc, char const* argv[]){

    Mat original = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat teste    = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);


    // int numberOfFrames, coef1 =2 , coef2 = 2;

    // float coef_mult = (1+((float)1/(coef1*coef1)) + ((float)1/(coef2*coef2)));

	// Image reference, test;

	PSNR_GPDS  psnr;
	SSIM ssim;
	PWSSIM pwssim;

	/**/
	cout<< "Entrou na PSNR\n";
	//============= PSNR ==============
	psnr.computePSNR(original,teste);
	psnr.writeResultsInFile();


	cout<< "\nEntrou na SSIM\n";
	//==============  SSIM  ===========
	ssim.computeSSIM(original,teste);
	ssim.writeResultsInFile();
	//=================================


	cout<< "\nEntrou na PWSSIM\n";
	//==============  PWSSIM  ===========
	pwssim.computePWSSIM(original,teste);
	pwssim.writeResultsInFile();
	//=================================

	// reference.deallocatePixelMap();
	// test.deallocatePixelMap();
	// reference.closeFile();
	// test.closeFile();
    // imshow("Original", original);
    //  imshow("Teste", teste);
    cvWaitKey(0);
	return 0;

}
