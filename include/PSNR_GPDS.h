#ifndef PSNR_GPDS_H
#define PSNR_GPDS_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;


class PSNR_GPDS
{
    public:
        void computePSNR(cv::Mat& ref_img, cv::Mat& test_img);
        double getPSNR();
        void writeResultsInFile();
    protected:

    private:
        double PSNR;
        long t0; // Executions time of the method computePSNR();
        long t1;
        double deltat;
};

#endif
