#pragma once

#ifdef _WIN64
//#	define MATLAB
#endif

#ifdef MATLAB

#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")

#include <string>
#include <vector>

//MATLAB
#include <engine.h>

//OpenCV
#include <opencv2/opencv.hpp>

#include <windows.h>


//================================================================================================================================================


namespace Other
{

	class MatlabWarper
	{
	private:
		static Engine *ep;
		static int count;
		static bool eng_open;

		int warp_index;
		std::string warp_name;

		void StartMatlabEngine();
		std::string mxName(std::string name);
		std::string intToStr(int i);
		std::string floatToStr(float f);

	public:
		MatlabWarper(std::string name = "");
		~MatlabWarper();

		void evalFacePP(std::vector<cv::Rect> &rects, double &time, cv::Mat &img);
		void evalFDPL(std::vector<cv::Rect> &rects, double &time, cv::Mat &img, int model_type = 0);
		void evalMVJ(std::vector<cv::Rect> &rects, double &time, cv::Mat &img, int model_type = 0, float scaleFactor = 1.1, int minNeighbors = 2, cv::Size minSize = cv::Size(), cv::Size maxSize = cv::Size());

	};

}

#endif