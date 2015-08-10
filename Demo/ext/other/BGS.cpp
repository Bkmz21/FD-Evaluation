/////////////////////////////////////////////////////////////////////////////////////////////////////////
///source code: http://www.cse.iitk.ac.in/users/vision/dipakmj/papers/OReilly%20Learning%20OpenCV.pdf ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;


//========================================================================================================


class StaticFrameDifferenceBGS
{
private:
	Mat IavgF, IdiffF, IprevF, IhiF, IlowF;
	Mat Iscratch, Iscratch2;
	Mat Igray1, Igray2, Igray3;
	Mat Ilow1, Ilow2, Ilow3;
	Mat Ihi1, Ihi2, Ihi3;
	Mat Imaskt, Imask_out;
	Mat scalar;
	float Icount;

	const float threshold = 0.1f;

protected:
	void AllocateImages(Mat& I)
	{
		cv::Size sz = I.size();
		IavgF = Mat::zeros(sz, CV_32FC3);
		IdiffF = Mat::zeros(sz, CV_32FC3);
		IprevF = Mat::zeros(sz, CV_32FC3);
		IhiF = Mat::zeros(sz, CV_32FC3);
		IlowF = Mat::zeros(sz, CV_32FC3);
		Ilow1 = Mat::zeros(sz, CV_32FC1);
		Ilow2 = Mat::zeros(sz, CV_32FC1);
		Ilow3 = Mat::zeros(sz, CV_32FC1);
		Ihi1 = Mat::zeros(sz, CV_32FC1);
		Ihi2 = Mat::zeros(sz, CV_32FC1);
		Ihi3 = Mat::zeros(sz, CV_32FC1);

		Icount = 0.00001; //Protect against divide by zero
		Iscratch = Mat::zeros(sz, CV_32FC3);
		Iscratch2 = Mat::zeros(sz, CV_32FC3);
		Igray1 = Mat::zeros(sz, CV_32FC1);
		Igray2 = Mat::zeros(sz, CV_32FC1);
		Igray3 = Mat::zeros(sz, CV_32FC1);
		Imaskt = Mat::zeros(sz, CV_8UC1);
		Imask_out = Mat::zeros(sz, CV_8UC1);

		scalar = Mat::zeros(sz, CV_8UC1);
		scalar.setTo(255);

	}
	void DeallocateImages()
	{
		IavgF.release();
		IdiffF.release();
		IprevF.release();
		IhiF.release();
		IlowF.release();
		Ilow1.release();
		Ilow2.release();
		Ilow3.release();
		Ihi1.release();
		Ihi2.release();
		Ihi3.release();
		Iscratch.release();
		Iscratch2.release();
		Igray1.release();
		Igray2.release();
		Igray3.release();
		Imaskt.release();
		Imask_out.release();
		scalar.release();
	}

	void setHighThreshold(float scale)
	{
		Iscratch = IdiffF * scale;
		IhiF = Iscratch + IavgF;
		Mat v[3];
		v[0] = Ihi1;
		v[1] = Ihi2;
		v[2] = Ihi3;
		split(IhiF, v);
	}
	void setLowThreshold(float scale)
	{
		Iscratch = IdiffF * scale;
		IlowF = IavgF - Iscratch;
		Mat v[3];
		v[0] = Ilow1;
		v[1] = Ilow2;
		v[2] = Ilow3;
		split(IlowF, v);
	}

	float checkROI(cv::Rect rect)
	{
		int counter = 0;
		int x2 = MIN(rect.x + rect.width, Imask_out.cols);
		int y2 = MIN(rect.y + rect.height, Imask_out.rows);
		int y = MAX(rect.y, 0);
		for (; y < y2; ++y)
		{
			uchar* ptr = (uchar*)(Imask_out.data + y * Imask_out.step[0]);
			int x = MAX(rect.x, 0);
			for (; x < x2; ++x)
			{
				if (ptr[x] > 0)
				{
					counter++;
				}
			}
		}

		return float(counter) / float((x2 - MAX(rect.x, 0)) * (y2 - MAX(rect.y, 0)));
	}

public:
	StaticFrameDifferenceBGS(Mat& I)
	{
		AllocateImages(I);
	}
	~StaticFrameDifferenceBGS()
	{
		DeallocateImages();
	}

	void accumulateBackground(Mat& I)
	{
		static int first = 1; // nb. Not thread safe
		I.convertTo(Iscratch, CV_32F, 1, 0); // convert to float
		if (!first)
		{
			accumulate(Iscratch, IavgF);
			absdiff(Iscratch, IprevF, Iscratch2);
			accumulate(Iscratch2, IdiffF);
			Icount += 1.f;
		}
		first = 0;
		IprevF = Iscratch.clone();
	}
	void createModelsfromStats()
	{
		IavgF.convertTo(IavgF, CV_32FC3, (float)(1.f / Icount));
		IdiffF.convertTo(IdiffF, CV_32FC3, (float)(1.f / Icount));
		//Make sure diff is always something
		IdiffF += 1.f;
		setHighThreshold(6.0);
		setLowThreshold(5.0);
	}
	void backgroundDiff(Mat& I, Mat& Imask)
	{
		I.convertTo(Iscratch, CV_32FC3, 1, 0);
		Mat v[3];
		v[0] = Igray1;
		v[1] = Igray2;
		v[2] = Igray3;
		split(Iscratch, v);
		//Channel 1
		//
		inRange(Igray1, Ilow1, Ihi1, Imask_out);
		//Channel 2
		//
		inRange(Igray2, Ilow2, Ihi2, Imaskt);
		bitwise_or(Imask_out, Imaskt, Imask_out);
		//Channel 3
		//
		inRange(Igray3, Ilow3, Ihi3, Imaskt);
		bitwise_or(Imask_out, Imaskt, Imask_out);
		//Finally, invert the results
		//
		cv::subtract(scalar, Imask_out, Imask_out);

		Imask = Imask_out.clone();
	}

	void dropDetect(std::vector<cv::Rect> &faces)
	{
		faces.erase(std::remove_if(faces.begin(), faces.end(),
			[=](const cv::Rect& rect) { return checkROI(rect) < threshold; }),
			faces.end());
	}

};