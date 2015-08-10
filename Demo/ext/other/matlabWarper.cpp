#include "matlabWarper.h"


//================================================================================================================================================


#ifdef MATLAB

namespace Other
{

	Engine *MatlabWarper::ep = NULL;
	int     MatlabWarper::count = 0;
	bool    MatlabWarper::eng_open = false;

	MatlabWarper::MatlabWarper(std::string name)
	{
		if (!eng_open) StartMatlabEngine();
		count++;
		warp_index = count;
		warp_name = name;
		if (warp_name == "") warp_name = intToStr(warp_index);
	}
	MatlabWarper::~MatlabWarper()
	{
		engEvalString(ep, "close all;");
		engEvalString(ep, "clear all;");
		engClose(ep);
		eng_open = false;
	}
	void MatlabWarper::StartMatlabEngine()
	{
		for (int i = 0; i <= 5; i++)
		{
			if (!(ep = engOpen(NULL)))
			{
				Sleep(5);
				if (i == 5) return;
			}
			else
			{
				break;
			}
		}
		eng_open = true;
	}
	std::string MatlabWarper::mxName(std::string name)
	{
		return name + intToStr(warp_index);
	}
	std::string MatlabWarper::intToStr(int i)
	{
		char sc[33];
		std::string str = "";

		_itoa(i, sc, 10);
		str.append(sc);

		return str;
	}
	std::string MatlabWarper::floatToStr(float f)
	{
		char sc[_CVTBUFSIZE];
		std::string str = "";

		_gcvt(f, 14, sc);
		str.append(sc);

		return str;
	}

	void MatlabWarper::evalFacePP(std::vector<cv::Rect> &rects, double &time, cv::Mat &img)
	{
		if (!eng_open) return;

		cv::imwrite("W:/Projects/NeuralNetworks/CNNFaceDetectorGPU/ext/facepp-matlab-sdk/img.jpg", img);

		std::string cmd = "cd('W:/Projects/NeuralNetworks/CNNFaceDetectorGPU/ext/facepp-matlab-sdk');";
		cmd += "run FacePP_demo.m";

		engEvalString(ep, cmd.c_str());

		mxArray *mxN = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
		mxN = engGetVariable(ep, "FacePP_n");
		int n = (int)((double*)mxGetData(mxN))[0];

		mxArray *mxTime = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
		mxTime = engGetVariable(ep, "FacePP_time");
		time = ((double*)mxGetData(mxTime))[0];

		if (n > 0)
		{
			mxArray *mxRects = mxCreateNumericMatrix(n, 4, mxDOUBLE_CLASS, mxREAL);
			mxRects = engGetVariable(ep, "FacePP_face");
			double* ptrData = (double*)mxGetData(mxRects);
			for (int i = 0; i < n; ++i)
			{
				rects.push_back(cv::Rect(
					(int)ptrData[4 * i + 0],
					(int)ptrData[4 * i + 1],
					(int)ptrData[4 * i + 2],
					(int)ptrData[4 * i + 3]));
			}
			mxDestroyArray(mxRects);
		}

		engEvalString(ep, "clear;");

		mxDestroyArray(mxN);
	}
	void MatlabWarper::evalFDPL(std::vector<cv::Rect> &rects, double &time, cv::Mat &img, int model_type)
	{
		if (!eng_open) return;
		static bool bl = true;

		cv::imwrite("W:/Projects/NeuralNetworks/CNNFaceDetectorGPU/ext/face-release1.0-basic/img.jpg", img);

		std::string cmd = "cd('W:/Projects/NeuralNetworks/CNNFaceDetectorGPU/ext/face-release1.0-basic');";
		if (bl)
		{
			if (model_type == 0)
				cmd += "load face_p146_small.mat;";
			else
				cmd += "load face_p99.mat;";
			bl = false;
		}
		cmd += "run FDPL_demo.m";

		engEvalString(ep, cmd.c_str());

		mxArray *mxN = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
		mxN = engGetVariable(ep, "FDPL_n");
		int n = (int)((double*)mxGetData(mxN))[0];

		mxArray *mxTime = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
		mxTime = engGetVariable(ep, "FDPL_time");
		time = ((double*)mxGetData(mxTime))[0];

		if (n > 0)
		{
			mxArray *mxRects = mxCreateNumericMatrix(n, 4, mxDOUBLE_CLASS, mxREAL);
			mxRects = engGetVariable(ep, "FDPL_face");
			double* ptrData = (double*)mxGetData(mxRects);
			for (int i = 0; i < n; ++i)
			{
				rects.push_back(cv::Rect(
					(int)ptrData[4 * i + 0],
					(int)ptrData[4 * i + 1],
					(int)ptrData[4 * i + 2],
					(int)ptrData[4 * i + 3]));
			}
			mxDestroyArray(mxRects);
		}

		cmd = "clear FDPL_N; clear FDPL_face";
		engEvalString(ep, cmd.c_str());
		//engEvalString(ep, "clear;");

		mxDestroyArray(mxN);
	}
	void MatlabWarper::evalMVJ(std::vector<cv::Rect> &rects, double &time, cv::Mat &img, int model_type, float scaleFactor, int minNeighbors, cv::Size minSize, cv::Size maxSize)
	{
		if (!eng_open) return;
		static bool bl = true;

		cv::imwrite("W:/Projects/NeuralNetworks/CNNFaceDetectorGPU/ext/matlabVJ/img.jpg", img);

		std::string cmd = "cd('W:/Projects/NeuralNetworks/CNNFaceDetectorGPU/ext/matlabVJ');";
		if (bl)
		{
			switch (model_type)
			{
			default:
			case 0: 
				cmd += "VJDetect = vision.CascadeObjectDetector('FrontalFaceCART');";
				cmd += "VJDetect.MinSize = [" + intToStr(MAX(20, minSize.width)) + " " + intToStr(MAX(20, minSize.height)) + "];";
				break;
			case 1:
				cmd += "VJDetect = vision.CascadeObjectDetector('FrontalFaceLBP');";
				cmd += "VJDetect.MinSize = [" + intToStr(MAX(24, minSize.width)) + " " + intToStr(MAX(24, minSize.height)) + "];";
				break;
			}
			if (maxSize.width != 0 && maxSize.height != 0)
			{
				cmd += "VJDetect.MaxSize = [" + intToStr(maxSize.width) + " " + intToStr(maxSize.height) + "];";
			}
			cmd += "VJDetect.ScaleFactor = " + floatToStr(scaleFactor) + ";";
			cmd += "VJDetect.MergeThreshold = " + floatToStr(float(2 + minNeighbors)) + ";";
			bl = false;
		}
		cmd += "run MVJ_demo.m";

		engEvalString(ep, cmd.c_str());

		mxArray *mxN = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
		mxN = engGetVariable(ep, "MVJ_n");
		int n = (int)((double*)mxGetData(mxN))[0];

		mxArray *mxTime = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
		mxTime = engGetVariable(ep, "MVJ_time");
		time = ((double*)mxGetData(mxTime))[0];

		if (n > 0)
		{
			mxArray *mxRects = mxCreateNumericMatrix(n, 4, mxDOUBLE_CLASS, mxREAL);
			mxRects = engGetVariable(ep, "MVJ_face");
			double* ptrData = (double*)mxGetData(mxRects);
			for (int i = 0; i < n; ++i)
			{
				rects.push_back(cv::Rect(
					(int)ptrData[4 * i + 0],
					(int)ptrData[4 * i + 1],
					(int)ptrData[4 * i + 2],
					(int)ptrData[4 * i + 3]));
			}
			mxDestroyArray(mxRects);
		}

		cmd = "clear MVJ_N; clear MVJ_face";
		engEvalString(ep, cmd.c_str());
		//engEvalString(ep, "clear;");

		mxDestroyArray(mxN);
	}

}

#endif