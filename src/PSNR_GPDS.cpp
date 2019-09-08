#include "common.h"
#include "PSNR_GPDS.h"


void PSNR_GPDS::computePSNR(cv::Mat& ref_img, cv::Mat& test_img){
    t0 = clock();
    cv::Mat s1;
    absdiff(ref_img, test_img, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2

    cv::Scalar s = sum(s1);         // sum elements per channel

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if( sse <= 1e-10){ // for small values return zero
        PSNR = 0;
    }else  {
        double  mse =sse /(double)(ref_img.channels() * ref_img.total());
        PSNR = 10.0*log10((255*255)/mse);
    }

    t1 = clock();
    deltat = (t1 - t0)/CLOCKS_PER_SEC;

    cout << "Resultado PSNR: " << PSNR << endl;
}

double PSNR_GPDS::getPSNR()
{
    return PSNR;
}

void PSNR_GPDS::writeResultsInFile()
{

	ofstream Name("results/PSNR.txt", ios::app);
	ofstream time_exec("results/PSNR_Timeexec.txt",ios::app);
	if (!Name || !time_exec)
		cout << "File couldn't open!!!" << endl;
	else
	{
		Name << getPSNR() << endl;
		time_exec << deltat << endl;
		Name.close();
		time_exec.close();	
	}
}
