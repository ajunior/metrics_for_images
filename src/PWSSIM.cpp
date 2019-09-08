#include "common.h"
#include "PWSSIM.h"


void PWSSIM::computePWSSIM(cv::Mat& ref_img, cv::Mat& test_img){
	t0 = clock();
    PWSSIM = 0;
	double C1 = 6.5025, C2 = 58.5225,
		   avg_Ref = 0, avg_Test = 0,
		   std_Ref = 0, std_Test = 0,
		   cov_RefTest = 0;

	double avg_Ref_sobel = 0,
		   std_Ref_sobel = 0,
		   total_std_Ref_sobel = 0;

	int noLines= ref_img.rows;
	int noCols = ref_img.cols;

	int blocks=8;

    Mat sobel, src;
    Sobel(ref_img, sobel,CV_32F,  1, 0, 3, 1, 0, BORDER_DEFAULT );
    // imshow("teste", sobel);
    for(int line = 0; line < noLines; line += blocks)
        for(int column = 0; column < noCols; column += blocks)
        {
            for(int i = column; i < (column+blocks); i++)
                for(int j = line; j < (line+blocks); j++)
                {

                    avg_Ref += double(ref_img.at<int8_t>(i, j));

                    avg_Test += double(test_img.at<int8_t>(i, j));

                    avg_Ref_sobel += double(sobel.at<int8_t>(i, j));

                }
                avg_Ref /= (blocks*blocks);

                avg_Test /= (blocks*blocks);

                avg_Ref_sobel /= (blocks*blocks);


            for(int i = column; i < (column+blocks); i++)
                for(int j = line; j < (line+blocks); j++)
                {
                    std_Ref += pow((int(ref_img.at<int8_t>(i, j)) - avg_Ref),2);

                    std_Test += pow((int(test_img.at<int8_t>(i, j)) - avg_Test),2);

                    std_Ref_sobel += pow((int(sobel.at<int8_t>(i, j)) - avg_Ref_sobel),2);

                }

                std_Ref  = sqrt(std_Ref/(blocks*blocks-1));

                std_Test = sqrt(std_Test/(blocks*blocks-1));

                std_Ref_sobel = sqrt(std_Ref_sobel/(blocks*blocks-1));

                total_std_Ref_sobel += std_Ref_sobel;


            for(int i = column; i < (column+blocks); i++){
                for(int j = line; j < (line+blocks); j++){
                    cov_RefTest += (int(ref_img.at<int8_t>(i, j)) - avg_Ref)*(int(test_img.at<int8_t>(i, j)) - avg_Test);
                }
            }

            cov_RefTest /= (blocks*blocks-1);


            PWSSIM += (((2*avg_Ref*avg_Test + C1)*(2*cov_RefTest + C2))/
                        ((avg_Ref*avg_Ref + avg_Test*avg_Test + C1)*(std_Ref*std_Ref + std_Test*std_Test + C2)))*std_Ref_sobel;

            avg_Ref = 0;  avg_Test = 0;
            std_Ref = 0;  std_Test = 0;
            cov_RefTest = 0;
            avg_Ref_sobel = 0;
            std_Ref_sobel = 0;
        }

	PWSSIM /= total_std_Ref_sobel;

	t = clock();
	deltat = (t - t0)/CLOCKS_PER_SEC;
    std::cout << "Resultado PWSSIM: " << PWSSIM << endl;

}
void PWSSIM::writeResultsInFile()
{
    ofstream Name("results/PWSSIM.txt", ios::app);
    ofstream time_exec("results/PWSSIM_Timeexec.txt", ios::app);
    if(!Name || !time_exec)
    	std::cout << "The file couldn't open" << endl;

    else
    {
    	Name << getPWSSIM() << endl;
    	time_exec << deltat<< endl;
    	Name.close();
    	time_exec.close();
    }
}
double PWSSIM::getPWSSIM()
{
	return PWSSIM;
}
