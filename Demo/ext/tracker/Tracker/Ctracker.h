///////////////////////////////////////////////////////////////////
///source code: https://github.com/Smorodov/Multitarget-tracker ///
///////////////////////////////////////////////////////////////////


#pragma once

#define OCV_300

#include "KalmanFilter/Kalman.h"
#include "HungarianAlg/HungarianAlg.h"

#include <iostream>
#include <vector>

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

#ifdef OCV_300

class CTrack
{
public:
	vector<Point2d> trace;
	cv::Rect bounding_box;
	bool detect;
	static size_t NextTrackID;
	size_t track_id;
	size_t detected_frames; 
	size_t skipped_frames;
	Point2d prediction;
	TKalmanFilter* KF;
	CTrack(cv::Rect rect, float dt, float Accel_noise_mag);
	~CTrack();
};

class CTracker
{
public:
	// Step polling time filter
	float dt; 

	float Accel_noise_mag;

	// Threshold distance. If the points are arcs from one another at a distance,
	// Greater than this threshold, then this pair is not considered the problem of appointments.
	double dist_thres;
	// Maximum number of shots that track saved without receiving data measurements.
	int maximum_allowed_skipped_frames;
	// Maximum length of the track
	int max_trace_length;

	vector<CTrack*> tracks;
	static Point2d rect2point(cv::Rect &rect);
	void Update(vector<cv::Rect>& detections);
	CTracker(float _dt, float _Accel_noise_mag, double _dist_thres=60, int _maximum_allowed_skipped_frames=10,int _max_trace_length=10);
	~CTracker(void);
};

#else

class CTrack
{
public:
	vector<Point2d> trace;
	cv::Rect bounding_box;
	bool detect;
	static size_t NextTrackID;
	size_t track_id;
	size_t detected_frames;
	size_t skipped_frames;
};

class CTracker
{
public:
	vector<CTrack*> tracks;
	void Update(vector<cv::Rect>& detections) { }
	CTracker(float _dt, float _Accel_noise_mag, double _dist_thres = 60, int _maximum_allowed_skipped_frames = 10, int _max_trace_length = 10) { }
	~CTracker(void) { }
};

#endif