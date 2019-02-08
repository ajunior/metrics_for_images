#ifndef PWSSIM_H
#define PWSSIM_H


#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

class PWSSIM {

	public:
		void computePWSSIM(cv::Mat& ref_img, cv::Mat& test_img);
		double getPWSSIM();
		void writeResultsInFile();
	
	private:
		double PWSSIM;
		long t0,t;
		double deltat;

};
#endif
