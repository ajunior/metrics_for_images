
#include "common.h"
#include "SSIM.h"


void SSIM::computeSSIM(cv::Mat& ref_img, cv::Mat& test_img){
	t0 = clock();
    SSIM =0;
	const double C1 = 6.5025, C2 = 58.5225;
    /***************************** INITS **********************************/
    int d     = CV_32F;

    Mat I1, I2;
    ref_img.convertTo(I1, d);           // cannot calculate on one byte large values
    test_img.convertTo(I2, d);

    Mat I2_2   = I2.mul(I2);        // I2^2
    Mat I1_2   = I1.mul(I1);        // I1^2
    Mat I1_I2  = I1.mul(I2);        // I1 * I2

    /***********************PRELIMINARY COMPUTING ******************************/

    Mat mu1, mu2;   //
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);

    Mat mu1_2   =   mu1.mul(mu1);
    Mat mu2_2   =   mu2.mul(mu2);
    Mat mu1_mu2 =   mu1.mul(mu2);

    Mat sigma1_2, sigma2_2, sigma12;

    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;

    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;

    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;

    ///////////////////////////////// FORMULA ////////////////////////////////
    Mat t1, t2, t3;

    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))

    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

    Mat ssim_map;
    divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;

    Scalar mssim = mean( ssim_map ); // mssim = average of ssim map
    SSIM = mssim[0];




	cout << "Resultado ssim: " << SSIM << endl;


	t = clock();
	deltat = (t - t0)/CLOCKS_PER_SEC;
}

void SSIM::writeResultsInFile()
{
   	ofstream Name;
	ofstream time_exec("store/SSIM_Timeexec.txt",ios::app);
	Name.open("store/SSIM.txt", ios::app);
	if (!Name || !time_exec)
		cout << "The file couldn't open" << endl;

	else
	{
		Name << getSSIM() << endl;
		time_exec << deltat<< endl;
		Name.close();
		time_exec.close();
	}

}
double SSIM::getSSIM()
{
	return SSIM;
}
