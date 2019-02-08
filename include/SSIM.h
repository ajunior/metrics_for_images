#ifndef SSIM_H
#define SSIM_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

class SSIM
{
    public:
        void computeSSIM(cv::Mat& ref_img, cv::Mat& test_img);
        double getSSIM();
        void writeResultsInFile();
		//void SSIM();
    protected:

    private:
		double SSIM;
		long t0,t;
		double deltat;
};

#endif // SSIM_H
