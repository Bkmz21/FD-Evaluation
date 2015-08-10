/*
*	Copyright (c) 2015, Ilya Kalinowski
*	All rights reserved.
*
*	This is an implementation of the algorithm described in the following paper:
*		I.A. Kalinowski, V.G. Spitsyn,
*		Compact Convolutional Neural Network Cascade for Face Detection,
*		http://arxiv.org/abs/1508.01292.
*
*	Redistribution and use of this program as source code or in binary form, with or without modifications, are permitted provided that the following conditions are met:
*		1. Redistributions may not be sold, nor may they be used in a commercial product or activity without prior permission from the copyright holder (contact him at kua_21@mail.ru).
*		2. Redistributions may not be used for military purposes.
*		3. Any published work which utilizes this program shall include the reference to the paper available at http://arxiv.org/abs/1508.01292
*		4. Redistributions must retain the above copyright notice and the reference to the algorithm on which the implementation is based on, this list of conditions and the following disclaimer.
*
*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
*	IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#pragma comment (linker, "/STACK:64000000")

//XML
#include <windows.h>
#include <msxml.h>
#include <objsafe.h>
#include <objbase.h>
#include <atlbase.h>
#include <tchar.h>

//------------------------ Frontal Face Detection Algorithms ------------------------

//SURF
//Lee J. Learning SURF Cascade for Fast and Accurate Object Detection (http://www.cv-foundation.org/openaccess/content_cvpr_2013/papers/Li_Learning_SURF_Cascade_2013_CVPR_paper.pdf)
//source code: https://sites.google.com/site/leeplus/publications/learningsurfcascadeforfastandaccurateobjectdetection
#ifndef _WIN64
//#	define SURF
#endif
#ifdef SURF
#	include "libFD.h"
#	pragma comment(lib, "libFD.lib")
#endif

//PICO
//Markus N. Pixel Intensity Comparison-based Object detection (http://arxiv.org/abs/1305.4537)
//source code: https://github.com/nenadmarkus/pico
//#define PICO
#ifdef PICO
#	include "picornt.h"
#	include "picornt.c"
#	include "sample/sample.c"
#endif

//CCNN
//Kalinowski I. Compact Convolutional Neural Network Cascade for Face Detection (http://arxiv.org/abs/1508.01292)
//#define CCNN
#ifdef CCNN
#	include "gpu_cnn_detector_2.h"
#endif

//FDLIB
//Kienzle W. Face detection: efficient and rank deficient (http://www.kyb.mpg.de/fileadmin/user_upload/files/publications/pdfs/pdf2776.pdf)
//source code: http://people.kyb.tuebingen.mpg.de/kienzle/fdlib/fdlib.htm
#if !defined(_WIN64)
//#	define FDLIB
#endif
#ifdef FDLIB
#	include "fdlib.h"
#	pragma comment(lib, "fdlib.lib")
#endif

//HeadHunter
//Mathias M. Face detection without bells and whistles (http://rodrigob.github.io/documents/2014_eccv_face_detection_with_supplementary_material.pdf)
//source code: http://markusmathias.bitbucket.org/2014_eccv_face_detection/
#if defined(_WIN64) && !defined(OCV_300)
//#	define HH
#endif
#ifdef HH
#	include "objects_detection_lib.hpp"
#	include <boost/gil/image_view.hpp>
#	include <boost/gil/image_view_factory.hpp>
#	pragma comment(lib, "objects_detection.lib")
#	pragma comment(lib, "cpp_stuff_library.lib")
#	pragma comment(lib, "cuda_stuff_library.lib")
#	pragma comment(lib, "libzlib-x64.lib")
#	pragma comment(lib, "libpng-x64.lib")
#	pragma comment(lib, "libprotobuf.lib")
#	pragma comment(lib, "SDL.lib")
#	pragma comment(lib, "LibJPEG.lib")
#	pragma comment(lib, "cudart_static.lib")
#endif

//AFLW (OpenCV Object Detection Framework)
//Koestinger M. Efficient metric learning for real - world face recognition (http://lrs.icg.tugraz.at/pubs/koestinger_phd_13.pdf)
//source code: https://lrs.icg.tugraz.at/research/aflw/

//MTP (OpenCV Object Detection Framework)
//Pham M. Fast training and selection and Haar features using statistics in boosting - based face detection (http://ieeexplore.ieee.org/xpl/articleDetails.jsp?tp=&arnumber=4409038&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D4409038)
//source code: http://www.ntu.edu.sg/home/astjcham/research.htm

//Matlab 
#ifdef _WIN64
//#	define MATLAB
#endif

//FDPL (Matlab code)
//Zhu X. Face detection, pose estimation, and landmark localization in the wild
//source code: http://www.ics.uci.edu/~xzhu/face/

//MVJ (Matlab code)
//MathWorks MatLab 2013b, Computer Vision System Toolbox
//source code: http://www.mathworks.com/help/vision/ref/vision.cascadeobjectdetector-class.html

//FacePP (Matlab code)
//http://www.faceplusplus.com
//source code: https://github.com/FacePlusPlus/facepp-java-sdk

//-----------------------------------------------------------------------------------

//OpenCV library 
//source code: http://opencv.org
#define OCV_300
#include <opencv2/opencv.hpp>
#ifdef OCV_300
#	include <opencv2/core/ocl.hpp>
#	ifdef _DEBUG
#		pragma comment(lib, "opencv_core300d.lib")
#		pragma comment(lib, "opencv_highgui300d.lib")
#		pragma comment(lib, "opencv_imgcodecs300d.lib")
#		pragma comment(lib, "opencv_imgproc300d.lib")
#		pragma comment(lib, "opencv_videoio300d.lib")
#		pragma comment(lib, "opencv_video300d.lib")
#		pragma comment(lib, "opencv_objdetect300d.lib")
#	else
#		pragma comment(lib, "opencv_core300.lib")
#		pragma comment(lib, "opencv_highgui300.lib")
#		pragma comment(lib, "opencv_imgcodecs300.lib")
#		pragma comment(lib, "opencv_imgproc300.lib")
#		pragma comment(lib, "opencv_videoio300.lib")
#		pragma comment(lib, "opencv_video300.lib")
#		pragma comment(lib, "opencv_objdetect300.lib")
#	endif
#
#	define OCV_CUDA
#	ifdef OCV_CUDA
//#		include <opencv2/cuda.hpp>
#		include <opencv2/cudaobjdetect.hpp>
#	ifdef _DEBUG
//#		pragma comment(lib, "opencv_cuda300d.lib")
#		pragma comment(lib, "opencv_cudaobjdetect300d.lib")
#	else
//#		pragma comment(lib, "opencv_cuda300.lib")
#		pragma comment(lib, "opencv_cudaobjdetect300.lib")
#	endif
#	endif
#else
#	ifdef _DEBUG
#		pragma comment(lib, "opencv_core249d.lib")
#		pragma comment(lib, "opencv_highgui249d.lib")
#		pragma comment(lib, "opencv_imgcodecs249d.lib")
#		pragma comment(lib, "opencv_imgproc249d.lib")
#		pragma comment(lib, "opencv_videoio249d.lib")
#		pragma comment(lib, "opencv_objdetect249d.lib")
#	else
#		pragma comment(lib, "opencv_core249.lib")
#		pragma comment(lib, "opencv_gpu249.lib")
#		pragma comment(lib, "opencv_highgui249.lib")
#		pragma comment(lib, "opencv_imgproc249.lib")
#		pragma comment(lib, "opencv_objdetect249.lib")
#	endif
#endif

//Libconfig
//source code: http://www.hyperrealm.com/libconfig/
#include "libconfig/libconfig.h"
#pragma comment(lib, "libconfig++.lib")

#ifdef USE_CUDA
#	pragma comment(lib, "cudart_static.lib")
#endif
#ifdef USE_CL
#	pragma comment(lib, "OpenCL.lib")
#endif

//Background subtraction
#include "BGS.cpp"

//Kalman object tracking
#include "Tracker/CTracker.h"

//Matlab
#ifdef MATLAB
#	include "matlabWarper.h"
	Other::MatlabWarper matlab;
#endif

//Other
#include "converter.h"
#include "work_dir.h"
#include "hr_timer.h"

#ifdef CCNN
using namespace NeuralNetworksLib;
#endif
using namespace Other;
using namespace libconfig;
using namespace cv;


//========================================================================================================


int image_border = 0;
int disp_step = 0;
int min_detected_frames = 0;

//--------------------------------------------------------------------------------------------------------
//GroundTruth and Statistic structures

struct GroundTruth
{
	struct TPerson
	{
		cv::Rect rect;
		int trackID;
		bool check;

		TPerson(int X, int Y, int Width, int Height, int _trackID)
		{
			rect = cv::Rect(X, Y, Width, Height);
			trackID = _trackID;
			check = false;
		}
	};

	int frameID;
	vector<TPerson> person;

	GroundTruth()
	{
		frameID = 0;
	}
};
map<int, GroundTruth*> frame_ground_truth;

struct StatRate
{
	int frame_count = 0;
	int face_count = 0;
	int track_count = 0;
	int true_detections = 0;
	int false_detections = 0;
	int true_tracks = 0;
	int false_tracks = 0;
	int label_tracks_fount = 0;
	double time_all = 0.;
	double time_avr = 0.;
	double time_min = 1.E6;
	double time_max = 0.;
	map<int, int> tracks;
	map<int, int> label_tracks;
};
StatRate stat_rate_CNN;
StatRate stat_rate_VJ;
StatRate stat_rate_SURF;
StatRate stat_rate_PICO;
StatRate stat_rate_FDLIB;
StatRate stat_rate_HH;
StatRate stat_rate_AFLW;
StatRate stat_rate_MTP;
StatRate stat_rate_FacePP;
StatRate stat_rate_FDPL;
StatRate stat_rate_MVJ;

//--------------------------------------------------------------------------------------------------------
//FD Benchmarks

void XMLPraser(string file_name, string decimal_separator = ",")
{
	if (!WorkDir::FileExists(file_name))
	{
		printf("error open ground truth file\n");
		return;
	}

	USES_CONVERSION;

	CoInitialize(NULL);

	CComPtr<IXMLDOMDocument> spXMLDOM;
	HRESULT hr = spXMLDOM.CoCreateInstance(__uuidof(DOMDocument));

	if (FAILED(hr))
		printf("Unable to create XML parser object\n");
	if (spXMLDOM.p == NULL)
		printf("Unable to create XML parser object\n");

	VARIANT_BOOL bSuccess = false;
	hr = spXMLDOM->load(CComVariant(file_name.c_str()), &bSuccess);

	if (FAILED(hr))
		printf("Unable to load XML document into the parser\n");
	if (!bSuccess)
		printf("Unable to load XML document into the parser\n");


	IXMLDOMNode*          pXMLNodeA;
	IXMLDOMNode*          pXMLNodeB;
	IXMLDOMNode*          pXMLNodeC;
	IXMLDOMNodeList*      pXMLNodeListA;
	IXMLDOMNodeList*      pXMLNodeListB;
	IXMLDOMNodeList*      pXMLNodeListC;
	IXMLDOMNamedNodeMap*  pXMLNodeMap;

	CComVariant           varNodeValue;
	long                  frame_index;
	long                  person_count;

	spXMLDOM->get_childNodes(&pXMLNodeListA);
	pXMLNodeListA->get_length(&frame_index);
	pXMLNodeListA->get_item(1, &pXMLNodeA);

	pXMLNodeA->get_attributes(&pXMLNodeMap);
	pXMLNodeMap->getNamedItem(L"Width", &pXMLNodeB);
	pXMLNodeB->get_nodeValue(&varNodeValue);
	char *temp = W2A(varNodeValue.bstrVal);
	float ClipWidth = atof(temp);

	pXMLNodeMap->get_item(1, &pXMLNodeB);
	pXMLNodeMap->getNamedItem(L"Height", &pXMLNodeB);
	pXMLNodeB->get_nodeValue(&varNodeValue);
	temp = W2A(varNodeValue.bstrVal);
	float ClipHeight = atof(temp);

	pXMLNodeA->get_childNodes(&pXMLNodeListA);
	pXMLNodeListA->get_length(&frame_index);

	for (int i = 0; i < frame_index; i++)
	{
		pXMLNodeListA->get_item(i, &pXMLNodeA);
		pXMLNodeA->get_attributes(&pXMLNodeMap);
		pXMLNodeMap->getNamedItem(L"Number", &pXMLNodeB);
		pXMLNodeB->get_nodeValue(&varNodeValue);

		char *temp = W2A(varNodeValue.bstrVal);
		int frameID = atoi(temp);

		GroundTruth *frame_data = new GroundTruth;
		frame_data->frameID = frameID;

		pXMLNodeA->get_childNodes(&pXMLNodeListB);
		pXMLNodeListB->get_length(&person_count);
		for (int j = 0; j < person_count; j++)
		{
			pXMLNodeListB->get_item(j, &pXMLNodeA);

			pXMLNodeA->get_attributes(&pXMLNodeMap);
			pXMLNodeMap->getNamedItem(L"TrackID", &pXMLNodeB);
			pXMLNodeB->get_nodeValue(&varNodeValue);
			temp = W2A(varNodeValue.bstrVal);
			int TrackID = atoi(temp);

			pXMLNodeA->get_childNodes(&pXMLNodeListC);
			pXMLNodeListC->get_item(0, &pXMLNodeC);
			pXMLNodeC->get_attributes(&pXMLNodeMap);

			pXMLNodeMap->getNamedItem(L"X", &pXMLNodeB);
			pXMLNodeB->get_nodeValue(&varNodeValue);
			temp = W2A(varNodeValue.bstrVal); temp[1] = decimal_separator[0];
			float X = atof(temp);

			pXMLNodeMap->getNamedItem(L"Y", &pXMLNodeB);
			pXMLNodeB->get_nodeValue(&varNodeValue);
			temp = W2A(varNodeValue.bstrVal); temp[1] = decimal_separator[0];
			float Y = atof(temp);

			pXMLNodeMap->getNamedItem(L"Width", &pXMLNodeB);
			pXMLNodeB->get_nodeValue(&varNodeValue);
			temp = W2A(varNodeValue.bstrVal); temp[1] = decimal_separator[0];
			float Width = atof(temp);

			pXMLNodeMap->getNamedItem(L"Height", &pXMLNodeB);
			pXMLNodeB->get_nodeValue(&varNodeValue);
			temp = W2A(varNodeValue.bstrVal); temp[1] = decimal_separator[0];
			float Height = atof(temp);

			frame_data->person.push_back(GroundTruth::TPerson(int(X*ClipWidth), int(Y*ClipHeight), int(Width*ClipWidth), int(Height*ClipHeight), TrackID));

			pXMLNodeB->Release();
			pXMLNodeC->Release();
			pXMLNodeMap->Release();
			pXMLNodeListC->Release();
		}

		frame_ground_truth[frame_data->frameID] = frame_data;
		pXMLNodeA->Release();
		pXMLNodeListB->Release();
	}
}

//Face Detection Data Set and Benchmark (FDDB) 
//http://vis-www.cs.umass.edu/fddb/
void FDDBPraser(string file_name, string decimal_separator = ",")
{
	if (!WorkDir::FileExists(file_name))
	{
		printf("error open ground truth file\n");
		return;
	}

	ifstream fAnnot(file_name.c_str());

	int frameID = 1;
	do
	{
		GroundTruth *frame_data = new GroundTruth;
		frame_data->frameID = frameID;

		string imS1;
		getline(fAnnot, imS1);

		int nAnnot;
		getline(fAnnot, imS1);

		stringstream ss1(imS1);
		ss1 >> nAnnot;

		for (int j = 0; j < nAnnot; j++)
		{
			double x, y, t, w, h, sc;

			string line;
			getline(fAnnot, line);
			stringstream ss(line);
			ss >> w >> h >> t >> x >> y >> sc;

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			///source code: http://stackoverflow.com/questions/87734/how-do-you-calculate-the-axis-aligned-bounding-box-of-an-ellipse ///
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//private static RectangleF EllipseBoundingBox(int ellipseCenterX, int ellipseCenterY, int ellipseRadiusX, int ellipseRadiusY, double ellipseAngle)
			//{
			//	double angle = ellipseAngle * Math.PI / 180;
			//	double a = ellipseRadiusX * Math.Cos(angle);
			//	double b = ellipseRadiusY * Math.Sin(angle);
			//	double c = ellipseRadiusX * Math.Sin(angle);
			//	double d = ellipseRadiusY * Math.Cos(angle);
			//	double width = Math.Sqrt(Math.Pow(a, 2) + Math.Pow(b, 2)) * 2;
			//	double height = Math.Sqrt(Math.Pow(c, 2) + Math.Pow(d, 2)) * 2;
			//	var x = ellipseCenterX - width * 0.5;
			//	var y = ellipseCenterY + height * 0.5;
			//	return new Rectangle((int)x, (int)y, (int)width, (int)height);
			//}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			double width = 2. * sqrt(w * w + (h * h - w * w) * sin(t) * sin(t));
			double height = 2. * sqrt(w * w + (h * h - w * w) * cos(t) * cos(t));
			x = x - width * 0.5;
			y = y - height * 0.5;

			int TrackID = 1;
			float X = x + (double)image_border;
			float Y = y + (double)image_border;
			float Width = width;
			float Height = height;

			frame_data->person.push_back(GroundTruth::TPerson(int(X), int(Y), int(Width), int(Height), TrackID));
		}

		frame_ground_truth[frame_data->frameID] = frame_data;

		frameID++;
	} while (!fAnnot.eof());
}

//The Annotated Faces in the Wild (AFW) 
//http://www.ics.uci.edu/~xzhu/face/
void AFWPraser(string file_name, string decimal_separator = ",")
{
	if (!WorkDir::FileExists(file_name))
	{
		printf("error open ground truth file\n");
		return;
	}

	ifstream fAnnot(file_name.c_str());

	int frameID = 1;
	do
	{
		GroundTruth *frame_data = new GroundTruth;
		frame_data->frameID = frameID;

		string imS1;
		getline(fAnnot, imS1);

		int nAnnot;
		getline(fAnnot, imS1);

		stringstream ss1(imS1);
		ss1 >> nAnnot;

		for (int j = 0; j < nAnnot; j++)
		{
			double x, y, w, h;

			string line;
			getline(fAnnot, line);
			stringstream ss(line);
			ss >> x >> y >> w >> h;

			int TrackID = 1;
			float X = x + (double)image_border;
			float Y = y + (double)image_border;
			float Width = w;
			float Height = h;

			frame_data->person.push_back(GroundTruth::TPerson(int(X), int(Y), int(Width), int(Height), TrackID));
		}

		frame_ground_truth[frame_data->frameID] = frame_data;

		frameID++;
	} while (!fAnnot.eof());
}

//Labeled Faces in the Wild (LFW) 
//http://vis-www.cs.umass.edu/lfw/
void LFWPraser(string file_name, string decimal_separator = ",")
{
	if (!WorkDir::FileExists(file_name))
	{
		printf("error open ground truth file\n");
		return;
	}

	ifstream fAnnot(file_name.c_str());

	string s;
	getline(fAnnot, s);
	getline(fAnnot, s);
	getline(fAnnot, s);
	getline(fAnnot, s);
	getline(fAnnot, s);
	getline(fAnnot, s);

	int frameID = 1;
	do
	{
		GroundTruth *frame_data = new GroundTruth;
		frame_data->frameID = frameID;

		string img_name;
		getline(fAnnot, img_name, ' ');

		double x, y, w, h;

		string line;
		getline(fAnnot, line);
		stringstream ss(line);
		ss >> x >> y >> w >> h;

		int TrackID = 1;
		float X = x + (double)image_border;
		float Y = y + (double)image_border;
		float Width = w;
		float Height = h;

		frame_data->person.push_back(GroundTruth::TPerson(int(X), int(Y), int(Width), int(Height), TrackID));
		frame_ground_truth[frame_data->frameID] = frame_data;

		frameID++;
	} while (!fAnnot.eof());
}

//IARPA Janus Benchmark A
//http://www.nist.gov/itl/iad/ig/facechallenges.cfm#ijba_detection
void IJBPraser(string file_name, string decimal_separator = ",")
{
	if (!WorkDir::FileExists(file_name))
	{
		printf("error open ground truth file\n");
		return;
	}

	ifstream fAnnot(file_name.c_str());

	string s;
	getline(fAnnot, s);

	int frameID = 1;
	int64 TEMPLATE_ID_TEMP = -1;
	GroundTruth *frame_data;
	do
	{
		string line;
		getline(fAnnot, line);
		replace(line.begin(), line.end(), ',', ' ');
		stringstream ss(line);

		int64 TEMPLATE_ID, SUBJECT_ID;
		string FILE;
		int64 MEDIA_ID, SIGHTING_ID, FRAME;
		int64 FACE_X, FACE_Y, FACE_WIDTH, FACE_HEIGHT;

		ss >> TEMPLATE_ID >> SUBJECT_ID >> FILE >> MEDIA_ID >> SIGHTING_ID >> FRAME >> FACE_X >> FACE_Y >> FACE_WIDTH >> FACE_HEIGHT;

		int TrackID = 1;
		int X = FACE_X + image_border;
		int Y = FACE_Y + image_border;
		int Width = FACE_WIDTH;
		int Height = FACE_HEIGHT;

		if (TEMPLATE_ID != TEMPLATE_ID_TEMP)
		{
			frame_data = new GroundTruth;
			frame_data->frameID = frameID;
			frame_data->person.push_back(GroundTruth::TPerson(X, Y, Width, Height, TrackID));
			frame_ground_truth[frame_data->frameID] = frame_data;
			frameID++;
			TEMPLATE_ID_TEMP = TEMPLATE_ID;
		}
		else
		{
			frame_data->person.push_back(GroundTruth::TPerson(X, Y, Width, Height, TrackID));
		}
	} while (!fAnnot.eof());
}

//--------------------------------------------------------------------------------------------------------
//Evaluation Detections

bool rectMatching(cv::Rect &annot, cv::Rect &det)
{
	std::vector<int> X(4);
	std::vector<int> Y(4);

	for (int j = -1; j <= 1; ++j)
	{
		for (int i = -1; i <= 1; ++i)
		{
			for (int s = -2; s <= 2; ++s)
			{
				double scale = 0.;
				if (s < 0)
				{
					scale = pow(1.1, double(-s));
				}
				else
				{
					scale = pow(0.95, double(s));
				}
				int scale_x = int(scale * double(annot.width));
				int scale_y = int(scale * double(annot.height));

				X[0] = annot.x - ((scale_x - annot.width) >> 1);
				Y[0] = annot.y - ((scale_y - annot.height) >> 1);
				X[1] = X[0] + scale_x;
				Y[1] = Y[0] + scale_y;

				int rx = int(double(X[1] - X[0]) * 0.2);
				if (i < 0)
				{
					X[0] += i * rx;
				}
				else
				{
					X[1] += i * rx;
				}

				int ry = int(double(Y[1] - Y[0]) * 0.2);
				Y[0] += j * ry;

				X[2] = det.x;
				Y[2] = det.y;
				X[3] = det.x + det.width;
				Y[3] = det.y + det.height;

				/*
					The Pascal Visual Object Classes (VOC) Challenge
					http://link.springer.com/article/10.1007%2Fs11263-009-0275-4
				*/
				if (!(X[0] >= X[3] || X[1] <= X[2] || Y[0] >= Y[3] || Y[1] <= Y[2]))
				{
					std::sort(X.begin(), X.end());
					std::sort(Y.begin(), Y.end());

					const float S_union = float((X[3] - X[0]) * (Y[3] - Y[0]));
					const float S_intersection = float((X[2] - X[1]) * (Y[2] - Y[1]));

					float overlapArea = S_intersection / S_union;

					if (overlapArea >= 0.5f)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
void evaluationDetections(string detector, int frame_id, vector<cv::Rect> &faces, double time, StatRate &stat_rate, CTracker *tracker = 0)
{
	int annot_count = 0;
	int max_track_id = 0;
	int detection_rate = faces.size();
	int true_detections = 0;
	int false_detections = faces.size();
	int true_tracks = 0;
	int false_tracks = 0;

	GroundTruth* fgt = frame_ground_truth[frame_id];

	if (fgt != NULL && fgt->frameID == frame_id)
	{
		annot_count = fgt->person.size();

		for (int det_id = 0; det_id < detection_rate; ++det_id)
		{
			for (int annot_id = 0; annot_id < annot_count; ++annot_id)
			{
				max_track_id = MAX(max_track_id, fgt->person[annot_id].trackID);

				if (!fgt->person[annot_id].check)
				{
					if (rectMatching(fgt->person[annot_id].rect, faces[det_id]))
					{
						true_detections++;
						fgt->person[annot_id].check = true;
						if (!stat_rate.label_tracks.count(fgt->person[annot_id].trackID))
						{
							stat_rate.label_tracks_fount++;
							stat_rate.label_tracks[fgt->person[annot_id].trackID] = 1;
						}
						break;
					}
				}
			}
		}
		false_detections -= true_detections;

		for (int k = 0; k < annot_count; ++k)
		{
			fgt->person[k].check = false;
		}

		if (tracker != 0)
		{
			for (int det_id = 0; det_id < tracker->tracks.size(); ++det_id)
			{
				if (!tracker->tracks[det_id]->detect || tracker->tracks[det_id]->detected_frames <= min_detected_frames) continue;

				for (int annot_id = 0; annot_id < annot_count; ++annot_id)
				{
					if (!fgt->person[annot_id].check)
					{
						if (rectMatching(fgt->person[annot_id].rect, tracker->tracks[det_id]->bounding_box))
						{
							if (!stat_rate.tracks.count(tracker->tracks[det_id]->track_id))
							{
								true_tracks++;
								stat_rate.tracks[tracker->tracks[det_id]->track_id] = 1;
							}
							fgt->person[annot_id].check = true;
							break;
						}
					}
				}

				if (!stat_rate.tracks.count(tracker->tracks[det_id]->track_id))
				{
					false_tracks++;
					stat_rate.tracks[tracker->tracks[det_id]->track_id] = 1;
				}
			}

			for (int k = 0; k < annot_count; ++k)
			{
				fgt->person[k].check = false;
			}
		}
	}
	else
	{
		if (tracker != 0)
		{
			for (int det_id = 0; det_id < tracker->tracks.size(); ++det_id)
			{
				if (!tracker->tracks[det_id]->detect || tracker->tracks[det_id]->detected_frames <= min_detected_frames) continue;

				if (!stat_rate.tracks.count(tracker->tracks[det_id]->track_id))
				{
					false_tracks++;
					stat_rate.tracks[tracker->tracks[det_id]->track_id] = 1;
				}
			}
		}
	}

	stat_rate.frame_count++;
	stat_rate.face_count += annot_count;
	stat_rate.track_count = MAX(max_track_id, stat_rate.track_count);
	stat_rate.true_detections += true_detections;
	stat_rate.false_detections += false_detections;
	stat_rate.true_tracks += true_tracks;
	stat_rate.false_tracks += false_tracks;
	stat_rate.time_avr = (stat_rate.time_avr * float(stat_rate.frame_count - 1) + time) / float(stat_rate.frame_count);
	stat_rate.time_min = MIN(stat_rate.time_min, time);
	stat_rate.time_max = MAX(stat_rate.time_max, time);
	if (disp_step > 0 && frame_id % disp_step == 0)
	{
		printf("%s:\n", detector.c_str());
		printf("	faces = %d\n", annot_count);
		printf("	true_detect = %d\n", true_detections);
		printf("	false_detect = %d\n", false_detections);
		printf("	total_faces = %d\n", stat_rate.face_count);
		printf("	total_true_detect = %d\n", stat_rate.true_detections);
		printf("	total_false_detect = %d\n\n", stat_rate.false_detections);
	}
}

#ifdef CCNN
void toCVRect(vector<cv::Rect> &cv_faces, vector<NeuralNetworksLib::CNNDetector::Detection> &faces)
{
	cv_faces.reserve(faces.size());
	for (int i = 0; i < faces.size(); ++i)
	{
		cv_faces.push_back(cv::Rect(faces[i].rect.x, faces[i].rect.y, faces[i].rect.width, faces[i].rect.height));
	}
}
#endif
#ifdef SURF
void toCVRect(vector<cv::Rect> &cv_faces, vector<CvMVRect> &faces)
{
	cv_faces.reserve(faces.size());
	for (int i = 0; i < faces.size(); ++i)
	{
		cv_faces.push_back(cv::Rect(faces[i].rc.x, faces[i].rc.y, faces[i].rc.width, faces[i].rc.height));
	}
}
#endif

//--------------------------------------------------------------------------------------------------------
//I/O

void createLogFile(string log_name, string cfg_mame)
{
	if (!WorkDir::FileExists(log_name))
	{
		string cols_name = "test_data	total_frames	total_faces	total_tracks	true_detections	false_detections	true_tracks	false_tracks	tracks_fount	mean_time	min_time	max_time\n";

		fstream file_cfg;
		ofstream file_out;

		file_out.open(log_name.c_str(), ios_base::out);
		file_cfg.open(cfg_mame.c_str(), ios_base::in);

		do
		{
			string str = "";
			getline(file_cfg, str);
			file_out << str << "\n";
		} while (!file_cfg.eof());

		file_out << "\n-----------------------------------------------------------------------------------------------\n\n";
		file_out << cols_name;
		file_out.close();
		file_cfg.close();
	}
}
void saveFaceStat(string clip_name, StatRate &stat_rate, string file_name)
{
	ofstream file_out;
	file_out.open(file_name.c_str(), ios_base::app);

	file_out << clip_name << "	"
		<< stat_rate.frame_count << "	"
		<< stat_rate.face_count << "	"
		<< stat_rate.track_count << "	"
		<< stat_rate.true_detections << "	"
		<< stat_rate.false_detections << "	"
		<< stat_rate.true_tracks << "	"
		<< stat_rate.false_tracks << "	"
		<< stat_rate.label_tracks_fount << "	"
		<< stat_rate.time_avr << "	"
		<< stat_rate.time_min << "	"
		<< stat_rate.time_max << "\n";

	file_out.close();
}

void print(string dtype, double time_, double fps_, int size)
{
	printf(dtype.c_str());
	printf(" processing times = %7.3f ms\n", time_);
	printf(dtype.c_str());
	printf(" frame rate = %5.1f fps\n", fps_);
	printf(dtype.c_str());
	printf(" detect = %d\n", size);
}
void draw(Mat &M_draw, string dtype, cv::Scalar color, double time, double fps, int &txt_offset, vector<cv::Rect> &faces, bool put_text, CTracker *tracker = 0)
{
	if (tracker == 0)
	{
		for (int p = 0; p < faces.size(); ++p)
		{
			if (dtype == "CNN")
			{
				rectangle(M_draw, faces[p], color, 3, 8, 0);
			}
			else
			{
				cv::Point center(faces[p].x + faces[p].width*0.5, faces[p].y + faces[p].height*0.5);
				ellipse(M_draw, center, cv::Size(faces[p].width*0.5, faces[p].height*0.5), 0, 0, 360, color, 3, 8, 0);
			}
		}
	}
	else
	{
		static int draw_id = 0;
		static map<int, int> tracks_draw_id;

		for (int p = 0; p < tracker->tracks.size(); ++p)
		{
			if (!tracker->tracks[p]->detect || tracker->tracks[p]->detected_frames <= min_detected_frames) continue;

			if (!tracks_draw_id.count(tracker->tracks[p]->track_id))
			{
				draw_id++;
				tracks_draw_id[tracker->tracks[p]->track_id] = draw_id;
			}

			rectangle(M_draw, tracker->tracks[p]->bounding_box, color, 3, 8, 0);
			for (int j = 0; j < tracker->tracks[p]->trace.size() - 1; ++j)
			{
				line(M_draw, tracker->tracks[p]->trace[j], tracker->tracks[p]->trace[j + 1], color, 2, CV_AA);
			}

			std::stringstream ss;
			ss << "id:" << tracks_draw_id[tracker->tracks[p]->track_id];
#ifdef OCV_300
			putText(M_draw, ss.str().c_str(), cv::Point(tracker->tracks[p]->bounding_box.x, tracker->tracks[p]->bounding_box.y - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, color, 1, cv::LINE_AA);
#else
			putText(M_draw, ss.str().c_str(), cv::Point(tracker->tracks[p]->bounding_box.x, tracker->tracks[p]->bounding_box.y - 5), FONT_HERSHEY_COMPLEX_SMALL, 1, color, 1, CV_AA);
#endif
		}
	}

	if (put_text)
	{
		std::stringstream ss;
		ss.precision(3);
		ss << dtype.c_str() << ": " << fps << " fps" << " (" << time << "ms) " << faces.size() << " dt";
#ifdef OCV_300
		putText(M_draw, ss.str().c_str(), cv::Point(5, txt_offset), FONT_HERSHEY_COMPLEX_SMALL, 3, color, 4, cv::LINE_AA);
#else
		putText(M_draw, ss.str().c_str(), cv::Point(5, txt_offset), FONT_HERSHEY_COMPLEX_SMALL, 3, color, 4, CV_AA);
#endif
		txt_offset += 60;
	}
}
void writeDetections(string output_file, string input_file, string img, int frame_index, string benchmark_name, string dtype, vector<cv::Rect> &faces)
{
	string log_name = output_file;
	string str = "_" + dtype + "_" + benchmark_name + "_";
	log_name.insert(log_name.size() - 4, str.c_str());

	if (benchmark_name == "FDDB")
	{
		str = input_file.substr(input_file.size() - 6, 2);
		log_name.insert(log_name.size() - 4, str.c_str());
	}

	if (benchmark_name == "IJB")
	{
		str = input_file.substr(input_file.size() - 6, 2);
		log_name.insert(log_name.size() - 4, str.c_str());
	}

	ofstream out_detect_list;
	if (frame_index == 1)
	{
		out_detect_list.open(log_name, ios_base::out);
	}
	else
	{
		out_detect_list.open(log_name, ios_base::app);
	}
	out_detect_list << img << "\n";
	out_detect_list << faces.size() << "\n";
	for (int p = 0; p < faces.size(); ++p)
	{
		out_detect_list << Converter::FloatToStr(faces[p].x - image_border) << " " << Converter::FloatToStr(faces[p].y - image_border) << " " << Converter::FloatToStr(faces[p].width) << " " << Converter::FloatToStr(faces[p].height) << " 1" << "\n";
	}
	out_detect_list.close();
}
void save(string dtype, StatRate &stat, string input_file, string output_file, string config_file)
{
	string log_name = output_file;
	log_name.insert(log_name.size() - 4, dtype);

	createLogFile(log_name, config_file);
	saveFaceStat(input_file, stat, log_name);
}
void rectExtension(vector<cv::Rect> &faces)
{
	for (int p = 0; p < (int)faces.size(); ++p)
	{
		faces[p].x -= int(0.2f * (float)faces[p].width);
		faces[p].y -= int(0.3f * (float)faces[p].height);
		faces[p].width += int(0.4f * (float)faces[p].width);
		faces[p].height += int(0.6f * (float)faces[p].height);
	}
}

//--------------------------------------------------------------------------------------------------------
//For Annotating

Mat *frame_temp;
static void onMouse(int event, int x, int y, int, void* _rects)
{
	vector<cv::Rect> *rects = (vector<cv::Rect>*)_rects;

	int scribbleRadius = 10;
	static bool rButtonDown = false;
	static bool lButtonDown = false;
	static int i = -1;
	static int corner = -1;

	if (event == EVENT_LBUTTONDOWN)
	{
		lButtonDown = true;

		i = -1;
		for (int p = 0; p < (int)(*rects).size(); ++p)
		{
			if (x >(*rects)[p].x && y > (*rects)[p].y)
			{
				if (x < (*rects)[p].x + (*rects)[p].width && y < (*rects)[p].y + (*rects)[p].height)
				{
					i = p;
					if (x < (*rects)[p].x + (*rects)[p].width * 0.5 && y < (*rects)[p].y + (*rects)[p].height * 0.5)
					{
						corner = 1;
					}
					if (x >(*rects)[p].x + (*rects)[p].width * 0.5 && y < (*rects)[p].y + (*rects)[p].height * 0.5)
					{
						corner = 2;
					}
					if (x < (*rects)[p].x + (*rects)[p].width * 0.5 && y >(*rects)[p].y + (*rects)[p].height * 0.5)
					{
						corner = 3;
					}
					if (x >(*rects)[p].x + (*rects)[p].width * 0.5 && y > (*rects)[p].y + (*rects)[p].height * 0.5)
					{
						corner = 4;
					}
				}
			}
		}

		if (i < 0)
		{
			(*rects).push_back(cv::Rect(x, y, 0, 0));
		}
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		rButtonDown = true;
	}
	else if (event == EVENT_LBUTTONUP)
	{
		lButtonDown = false;

		if (i < 0)
		{
			int index = rects->size() - 1;
			(*rects)[index].width = x - (*rects)[index].x;
			(*rects)[index].height = y - (*rects)[index].y;
		}
		else
		{
			if (corner == 1)
			{
				int del_x = (*rects)[i].x - x;
				int del_y = (*rects)[i].y - y;
				(*rects)[i].x -= del_x;
				(*rects)[i].y -= del_y;
				(*rects)[i].width += del_x;
				(*rects)[i].height += del_y;
			}
			if (corner == 2)
			{
				int del_y = (*rects)[i].y - y;
				(*rects)[i].width = x - (*rects)[i].x;
				(*rects)[i].y -= del_y;
				(*rects)[i].height += del_y;
			}
			if (corner == 3)
			{
				int del_x = (*rects)[i].x - x;
				(*rects)[i].x -= del_x;
				(*rects)[i].width += del_x;
				(*rects)[i].height = y - (*rects)[i].y;
			}
			if (corner == 4)
			{
				(*rects)[i].width = x - (*rects)[i].x;
				(*rects)[i].height = y - (*rects)[i].y;
			}
		}
	}
	else if (event == EVENT_RBUTTONUP)
	{
		rButtonDown = false;

		for (int p = 0; p < (int)(*rects).size();)
		{
			if (x >(*rects)[p].x && y > (*rects)[p].y)
			{
				if (x < (*rects)[p].x + (*rects)[p].width && y < (*rects)[p].y + (*rects)[p].height)
				{
					(*rects).erase((*rects).begin() + p);
					continue;
				}
			}
			p++;
		}
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		if (rButtonDown)
		{
		}
		else if (lButtonDown)
		{
			Mat frame = frame_temp->clone();
			int index = i;
			if (i < 0)
			{
				index = rects->size() - 1;
				(*rects)[index].width = x - (*rects)[index].x;
				(*rects)[index].height = y - (*rects)[index].y;
			}
			else
			{
				if (corner == 1)
				{
					int del_x = (*rects)[i].x - x;
					int del_y = (*rects)[i].y - y;
					(*rects)[i].x -= del_x;
					(*rects)[i].y -= del_y;
					(*rects)[i].width += del_x;
					(*rects)[i].height += del_y;
				}
				if (corner == 2)
				{
					int del_y = (*rects)[i].y - y;
					(*rects)[i].width = x - (*rects)[i].x;
					(*rects)[i].y -= del_y;
					(*rects)[i].height += del_y;
				}
				if (corner == 3)
				{
					int del_x = (*rects)[i].x - x;
					(*rects)[i].x -= del_x;
					(*rects)[i].width += del_x;
					(*rects)[i].height = y - (*rects)[i].y;
				}
				if (corner == 4)
				{
					(*rects)[i].width = x - (*rects)[i].x;
					(*rects)[i].height = y - (*rects)[i].y;
				}
			}
			rectangle(frame, Point((*rects)[index].x, (*rects)[index].y), Point((*rects)[index].x + (*rects)[index].width, (*rects)[index].y + (*rects)[index].height), Scalar(0, 255, 0), 3, 8, 0);
			imshow("Annotate frame", frame);
			waitKey(1);
		}
		else
		{
			Mat frame = frame_temp->clone();
			for (int p = 0; p < (int)(*rects).size(); ++p)
			{
				rectangle(frame, Point((*rects)[p].x, (*rects)[p].y), Point((*rects)[p].x + (*rects)[p].width, (*rects)[p].y + (*rects)[p].height), Scalar(0, 0, 255), 3, 8, 0);
			}
			imshow("Annotate frame", frame);
			waitKey(50);
		}
	}
}
void annotateFrame(Mat *frame, vector<cv::Rect> *rects, int frame_id)
{
	GroundTruth* fgt = frame_ground_truth[frame_id];
	if (fgt != NULL && fgt->frameID == frame_id)
	{
		rects->clear();
		for (int annot_id = 0; annot_id < fgt->person.size(); ++annot_id)
		{
			rects->push_back(fgt->person[annot_id].rect);
		}
	}

	static vector<cv::Rect> rects_temp;
	static bool copy_temp = false;

	if (copy_temp)
	{
		rects->clear();
		*rects = vector<cv::Rect>(rects_temp);
		rects_temp.clear();
		copy_temp = false;
	}

	frame_temp = frame;
	string wname = "Annotate frame";
	namedWindow(wname.c_str(), WINDOW_NORMAL);
	moveWindow(wname.c_str(), 1, 1);
	setMouseCallback(wname.c_str(), onMouse, (void*)rects);

	Mat frame_bf = frame_temp->clone();
	for (int p = 0; p < (int)(*rects).size(); ++p)
	{
		rectangle(frame_bf, Point((*rects)[p].x, (*rects)[p].y), Point((*rects)[p].x + (*rects)[p].width, (*rects)[p].y + (*rects)[p].height), Scalar(0, 0, 255), 3, 8, 0);
	}
	imshow(wname.c_str(), frame_bf);

	int c = waitKey(0);
	if (c == 'c')
	{
		rects_temp = vector<cv::Rect>(*rects);
		copy_temp = true;
	}
	destroyWindow(wname);
}

//--------------------------------------------------------------------------------------------------------

int FaceDetectorDemo(string config_file, string input_file = "", string output_file = "", string ground_truth_file = "", int min_sz = 0, float sf = 0.f, int min_nn = -1000000)
{
	struct Source
	{
		string type = "file"; //cam, file, image, image_list
		//video file: "H:/P1E_S2_C1.avi"; 
		//folder with images: "G:/Flickr/"
		string input_file = "G:/Flickr/";
		string mask = "jpg";
		string benchmark_name = "";
		string benchmark_path = "";

		cv::Size frame_size = { 640, 480 };
		int start_farame = 1;
		int max_frame = 0;
		bool resize_frame = false;

		bool use_Blur = false;
		bool use_BGS = false;

		bool use_Tracker = false;
		int max_distance = 40;
		int max_skipped_frames = 0;

		bool ground_truth = false;
		string ground_truth_data = "";

		bool save_result = false;
		bool save_stat = false;
		string output_file = "";

		bool show = false;
		int sleep = 1;
		bool pause = false;

		bool annotate = false;
	} source;

	struct Detectors
	{
		bool use_CNN = false;
		bool use_VJ = false;
		bool use_SURF = false;
		bool use_PICO = false;
		bool use_FDLIB = false;
		bool use_HH = false;
		bool use_AFLW = false;
		bool use_MTP = false;
		bool use_FacePP = false;
		bool use_FDPL = false;
		bool use_MVJ = false;

		cv::Size min_obj_size = { 40, 40 };
		cv::Size max_obj_size = { 0, 0 };
		float min_obj = 0.f;
		float max_obj = 0.f;

		float scale_factor = 1.2f;
		int min_neighbors = 3;

		int num_threads = 1;

		bool ocvOptimized = true;
		bool ocvOCL = false;
		bool ocvIPP = true;
		bool ocvThreads = false;
	} detectors;

	//---------------------------------------------------------------------------------

	if (config_file == "")
	{
		printf("Config file not found!\n");
		system("pause");
	}
	else
	{
		config_file = WorkDir::RecorPath(config_file);
	}

	printf("config_file = %s\n", config_file.c_str());
	printf("input_file = %s\n", input_file.c_str());
	printf("output_file = %s\n", output_file.c_str());
	printf("ground_truth_file = %s\n\n", ground_truth_file.c_str());

#if 1
	try
	{
		Config cfg_file;
		cfg_file.readFile(config_file.c_str());
		const Setting &root = cfg_file.getRoot();

		//-------------

		const Setting &general_source = root["general"]["source"];

		source.type.reserve(255);
		general_source.lookupValue("type", source.type);
		source.input_file.reserve(255);
		general_source.lookupValue("input_file", source.input_file);
		source.mask.reserve(255);
		general_source.lookupValue("mask", source.mask);
		source.benchmark_name.reserve(255);
		general_source.lookupValue("benchmark_name", source.benchmark_name);
		source.benchmark_path.reserve(255);
		general_source.lookupValue("benchmark_path", source.benchmark_path);

		source.frame_size.width = general_source["frame_size"][0];
		source.frame_size.height = general_source["frame_size"][1];
		general_source.lookupValue("start_farame", source.start_farame);
		general_source.lookupValue("max_frame", source.max_frame);
		general_source.lookupValue("resize_frame", source.resize_frame);

		general_source.lookupValue("add_border", image_border);

		general_source.lookupValue("use_Blur", source.use_Blur);
		general_source.lookupValue("use_BGS", source.use_BGS);

		general_source.lookupValue("use_Tracker", source.use_Tracker);
		general_source.lookupValue("max_distance", source.max_distance);
		general_source.lookupValue("max_skipped_frames", source.max_skipped_frames);
		general_source.lookupValue("min_detected_frames", min_detected_frames);

		general_source.lookupValue("ground_truth", source.ground_truth);
		source.ground_truth_data.reserve(255);
		general_source.lookupValue("ground_truth_data", source.ground_truth_data);

		general_source.lookupValue("save_result", source.save_result);
		general_source.lookupValue("save_stat", source.save_stat);
		source.output_file.reserve(255);
		general_source.lookupValue("output_file", source.output_file);

		general_source.lookupValue("show", source.show);
		general_source.lookupValue("disp_step", disp_step);
		general_source.lookupValue("sleep", source.sleep);
		general_source.lookupValue("pause", source.pause);

		general_source.lookupValue("annotate", source.annotate);

		if (input_file != "")
		{
			source.input_file = input_file;
			source.ground_truth_data = "";
		}

		if (output_file != "")
		{
			source.output_file = output_file;
		}
		else
		{
			if (source.output_file == "")
			{
				source.output_file = WorkDir::GetCurrentDir() + "detect_log.txt";
			}
		}

		if (source.ground_truth_data == "")
		{
			source.ground_truth_data = source.input_file + ".xml";
		}

		if (ground_truth_file != "")
		{
			source.ground_truth_data = ground_truth_file;
		}

		if (source.max_frame <= 0)
		{
			source.max_frame = INT_MAX;
		}

		source.input_file = WorkDir::RecorPath(source.input_file);
		source.ground_truth_data = WorkDir::RecorPath(source.ground_truth_data);

		general_source.~Setting();

		//-------------

		const Setting &general_detectors = root["general"]["detectors"];

		general_detectors.lookupValue("use_CNN", detectors.use_CNN);
		general_detectors.lookupValue("use_VJ", detectors.use_VJ);
		general_detectors.lookupValue("use_SURF", detectors.use_SURF);
		general_detectors.lookupValue("use_PICO", detectors.use_PICO);
		general_detectors.lookupValue("use_FDLIB", detectors.use_FDLIB);
		general_detectors.lookupValue("use_HH", detectors.use_HH);
		general_detectors.lookupValue("use_AFLW", detectors.use_AFLW);
		general_detectors.lookupValue("use_MTP", detectors.use_MTP);
		general_detectors.lookupValue("use_FacePP", detectors.use_FacePP);
		general_detectors.lookupValue("use_FDPL", detectors.use_FDPL);
		general_detectors.lookupValue("use_MVJ", detectors.use_MVJ);
		if (detectors.use_AFLW || detectors.use_MTP) detectors.use_VJ = true;

		detectors.min_obj_size.width = general_detectors["min_obj_size"][0];
		detectors.min_obj_size.height = general_detectors["min_obj_size"][1];
		detectors.max_obj_size.width = general_detectors["max_obj_size"][0];
		detectors.max_obj_size.height = general_detectors["max_obj_size"][1];

		general_detectors.lookupValue("min_obj", detectors.min_obj);
		general_detectors.lookupValue("max_obj", detectors.max_obj);

		general_detectors.lookupValue("scale_factor", detectors.scale_factor);
		general_detectors.lookupValue("min_neighbors", detectors.min_neighbors);

		general_detectors.lookupValue("num_threads", detectors.num_threads);

		general_detectors.lookupValue("ocvOptimized", detectors.ocvOptimized);
		general_detectors.lookupValue("ocvOCL", detectors.ocvOCL);
		general_detectors.lookupValue("ocvIPP", detectors.ocvIPP);
		general_detectors.lookupValue("ocvThreads", detectors.ocvThreads);

		general_detectors.~Setting();

		root.~Setting();

		if (min_sz != 0)
		{
			detectors.min_obj_size.width = min_sz;
			detectors.min_obj_size.height = min_sz;
		}
		if (sf != 0.f)
		{
			detectors.scale_factor = sf;
		}
		if (min_nn != -1000000)
		{
			detectors.min_neighbors = min_nn;
		}
	}
	catch (...)
	{
		printf("error open config file\n");
		system("pause");
	};
#endif

	//---------------------------------------------------------------------------------

#ifdef OCV_300
	//INIT OPENCV
	cv::setUseOptimized(detectors.ocvOptimized);
	cv::ocl::setUseOpenCL(detectors.ocvOCL);
	cv::ipp::setUseIPP(detectors.ocvIPP);

	if (detectors.ocvThreads)
	{
		cv::setNumThreads(detectors.num_threads);
	}

	if (cv::useOptimized())
	{
		printf("cvUseOptimized!\n");
		printf("	CV_CPU_SSE = %d\n", checkHardwareSupport(CV_CPU_SSE));
		printf("	CV_CPU_AVX = %d\n", checkHardwareSupport(CV_CPU_AVX));
	}
	if (cv::ipp::useIPP())
	{
		printf("cvUseIPP!\n");
		printf("	cv::ipp::getIppStatus = %d\n", cv::ipp::getIppStatus());
	}
	if (cv::ocl::useOpenCL())
	{
		printf("cvUseOpenCL!\n");
		if (ocl::Device::getDefault().type() != ocl::Device::TYPE_CPU)
		{
			printf("	ocl::Device::type %d\n", ocl::Device::getDefault().type());
			printf("	ocl::Device::vendorName = %s\n", ocl::Device::getDefault().vendorName().c_str());
			printf("	ocl::Device::name = %s\n", ocl::Device::getDefault().name().c_str());
			printf("	ocl::Device::maxComputeUnits = %d\n", ocl::Device::getDefault().maxComputeUnits());
			printf("	ocl::Device::maxClockFrequency = %d\n", ocl::Device::getDefault().maxClockFrequency());
		}
	}
#endif

	//---------------------------------------------------------------------------------

	if (source.ground_truth)
	{
		if (source.type == "file")
		{
			XMLPraser(source.ground_truth_data, ".");
		}
		if (source.type == "benchmark")
		{
			if (source.benchmark_name == "FDDB")
			{
				FDDBPraser(source.ground_truth_data, ".");
			}
			if (source.benchmark_name == "AFW")
			{
				AFWPraser(source.ground_truth_data, ".");
			}
			if (source.benchmark_name == "LFW")
			{
				LFWPraser(source.ground_truth_data, ".");
			}
			if (source.benchmark_name == "IJB")
			{
				IJBPraser(source.ground_truth_data, ".");
			}
		}
	}

	//---------------------------------------------------------------------------------

	cv::VideoCapture capture;
	if (source.type == "cam" || source.type == "ip_cam")
	{
		if (source.type == "cam")	 capture = cv::VideoCapture(0);
		if (source.type == "ip_cam") capture = cv::VideoCapture("http://192.168.43.1:8080/video?x.mjpeg");
		if (!capture.isOpened())
		{
			printf("error open cam\n");
			system("pause");
		}

#ifdef OCV_300
		capture.set(CAP_PROP_FRAME_WIDTH, source.frame_size.width);
		capture.set(CAP_PROP_FRAME_HEIGHT, source.frame_size.height);
#else
		capture.set(CV_CAP_PROP_FRAME_WIDTH, source.frame_size.width);
		capture.set(CV_CAP_PROP_FRAME_HEIGHT, source.frame_size.height);
#endif
	}

	if (source.type == "file")
	{
		printf("\n\nfile = %s\n\n", source.input_file.c_str());
		if (!WorkDir::FileExists(source.input_file))
		{
			printf("error open file\n");
			system("pause");
		}

		capture = VideoCapture(source.input_file.c_str());
		if (!capture.isOpened())
		{
			printf("error load file\n");
			system("pause");
		}

		if (!source.resize_frame)
		{
#ifdef OCV_300
			source.frame_size.width = (int)capture.get(CAP_PROP_FRAME_WIDTH);
			source.frame_size.height = (int)capture.get(CAP_PROP_FRAME_HEIGHT);
#else
			source.frame_size.width = (int)capture.get(CV_CAP_PROP_FRAME_WIDTH);
			source.frame_size.height = (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT);
#endif
		}
	}

	VideoWriter *record = 0;
	if (source.save_result)
	{
		if (source.type == "cam" || source.type == "ip_cam" || source.type == "file")
		{
			string file_name;
			if (source.type == "cam" || source.type == "ip_cam")
			{
				file_name = "cam_result.avi";
			}
			else
			{
				file_name = source.input_file + "_result.avi";
			}
#ifdef OCV_300
			record = new VideoWriter(file_name.c_str(), -1/*VideoWriter::fourcc('M', 'J', 'P', 'G')*/, 25, cv::Size(source.frame_size.width, source.frame_size.height), true);
#else
			record = new VideoWriter(file_name.c_str(), -1/*CV_FOURCC('M', 'J', 'P', 'G')*/, 25, cv::Size(source.frame_size.width, source.frame_size.height), true);
#endif

			if (!record->isOpened())
			{
				printf("VideoWriter failed to open!\n");
				return -1;
			}
		}
	}

	WIN32_FIND_DATA fd;
	HANDLE handle = 0;
	if (source.type == "image")
	{
		string folder = source.input_file + "*." + source.mask;
		printf("\n folder = %s\n", folder.c_str());

		TCHAR tchar[255];
		swprintf(tchar, 255, _T("%hs"), folder.c_str());
		handle = FindFirstFile(tchar, &fd);
	}

	vector<string> img_list;
	if (source.type == "benchmark")
	{
		if (!WorkDir::FileExists(source.input_file))
		{
			printf("error open image list file\n");
			system("pause");
		}

		if (source.benchmark_name == "FDDB" || source.benchmark_name == "AFW")
		{
			fstream flist;
			flist.open(source.input_file.c_str(), ios_base::in);
			while (flist)
			{
				string s;
				flist >> s;
				img_list.push_back(s + ".jpg");
			}
			flist.close();
		}
		if (source.benchmark_name == "LFW")
		{
			ifstream flist;
			flist.open(source.input_file.c_str(), ios_base::in);
			string s;
			getline(flist, s); getline(flist, s); getline(flist, s);
			getline(flist, s); getline(flist, s); getline(flist, s);
			while (flist)
			{
				string s;
				getline(flist, s, ' ');
				img_list.push_back(s);
				getline(flist, s);
			}
			flist.close();
		}
		if (source.benchmark_name == "IJB")
		{
			fstream flist;
			flist.open(source.input_file.c_str(), ios_base::in);
			while (flist)
			{
				string s;
				flist >> s;
				img_list.push_back(s);
			}
			flist.close();
		}
	}

	detectors.min_obj_size.width = MAX(1, detectors.min_obj_size.width);
	detectors.min_obj_size.height = MAX(1, detectors.min_obj_size.height);

	if (detectors.min_obj != 0.f)
	{
		detectors.min_obj_size.width = detectors.min_obj * source.frame_size.width;
		detectors.min_obj_size.height = detectors.min_obj * source.frame_size.height;
	}
	if (detectors.max_obj != 0.f)
	{
		detectors.max_obj_size.width = detectors.max_obj * source.frame_size.width;
		detectors.max_obj_size.height = detectors.max_obj * source.frame_size.height;
	}

	//---------------------------------------------------------------------------------

	//CNN
#ifdef CCNN	
	CNNDetector *CNNGPUD = NULL;
#endif

	//VJ
	cv::CascadeClassifier *VJD = NULL;
#ifdef OCV_CUDA
	//cuda::CascadeClassifier_CUDA *VJGPUD = NULL;
	Ptr<cuda::CascadeClassifier> VJGPUD;
#endif

#ifdef SURF
	//SURF
	tagFD *SURFD = NULL;
#endif

	//BGS
	StaticFrameDifferenceBGS *BGS = NULL;

	//Tracker
	CTracker *tracker = NULL;
	if (source.use_Tracker)
	{
		tracker = new CTracker(0.2, 0.2, source.max_distance, source.max_skipped_frames, 15);
	}

#ifdef CCNN
	if (detectors.use_CNN)
	{
		CNNDetector::Param cnn_param;
		CNNDetector::AdvancedParam cnn_ad_param;

		try
		{
			Config cfg_file;
			cfg_file.readFile(config_file.c_str());
			const Setting &root = cfg_file.getRoot();

			//-------------

			const Setting &CNN_param = root["CNN_param"];

			string pipeline = "CPU";
			CNN_param.lookupValue("pipeline", pipeline);
			if (pipeline == "CPU")		cnn_param.pipeline = CNNDetector::CPU;
			if (pipeline == "GPU")		cnn_param.pipeline = CNNDetector::GPU;
			if (pipeline == "GPU_CPU")	cnn_param.pipeline = CNNDetector::GPU_CPU;

			cnn_param.max_image_size = NeuralNetworksLib::Size(source.frame_size.width, source.frame_size.height);
			cnn_param.min_obj_size = NeuralNetworksLib::Size(detectors.min_obj_size.width, detectors.min_obj_size.height);
			cnn_param.max_obj_size = NeuralNetworksLib::Size(detectors.max_obj_size.width, detectors.max_obj_size.height);
			cnn_param.scale_factor = detectors.scale_factor;
			cnn_param.min_neighbors = detectors.min_neighbors;
			cnn_param.num_threads = detectors.num_threads;

			//-------------

			const Setting &CNN_ad_param = CNN_param["advanced"];

			int temp = -1;
			CNN_ad_param.lookupValue("check_detect", temp);
			if (temp >= 0)
			{
				cnn_ad_param.check_detect = (CNNDetector::CheckDetect)temp;
			}

			temp = -1;
			CNN_ad_param.lookupValue("type_check_detect", temp);
			if (temp >= 0)
			{
				cnn_ad_param.type_check_detect = (CNNDetector::TypeCheckDetect)temp;
			}

			CNN_ad_param.lookupValue("fast_check", cnn_ad_param.fast_check);
			CNN_ad_param.lookupValue("packet_detection", cnn_ad_param.packet_detection);

			CNN_ad_param.lookupValue("equalize", cnn_ad_param.equalize);
			CNN_ad_param.lookupValue("reflection", cnn_ad_param.reflection);
			CNN_ad_param.lookupValue("type_check", cnn_ad_param.type_check);
			CNN_ad_param.lookupValue("treshold_1", cnn_ad_param.treshold_1);
			CNN_ad_param.lookupValue("treshold_2", cnn_ad_param.treshold_2);
			CNN_ad_param.lookupValue("adapt_min_neighbors", cnn_ad_param.adapt_min_neighbors);
			CNN_ad_param.lookupValue("double_check", cnn_ad_param.double_check);
			CNN_ad_param.lookupValue("drop_detect", cnn_ad_param.drop_detect);
			CNN_ad_param.lookupValue("min_num_detect", cnn_ad_param.min_num_detect);

			CNN_ad_param.lookupValue("device_info", cnn_ad_param.device_info);
			CNN_ad_param.lookupValue("cuda_device_id", cnn_ad_param.cuda_device_id);
			CNN_ad_param.lookupValue("cl_platform_id", cnn_ad_param.cl_platform_id);
			CNN_ad_param.lookupValue("cl_device_id", cnn_ad_param.cl_device_id);

			CNN_ad_param.lookupValue("blur", cnn_ad_param.blur);
			temp = -1;
			CNN_ad_param.lookupValue("img_resize", temp);
			if (temp >= 0)
			{
				cnn_ad_param.img_resize = (CNNDetector::ImgResize)temp;
			}
			CNN_ad_param.lookupValue("uniform_noise", cnn_ad_param.uniform_noise);
			CNN_ad_param.lookupValue("merger_detect", cnn_ad_param.merger_detect);

			CNN_ad_param.~Setting();

			CNNGPUD = new CNNDetector(&cnn_param, &cnn_ad_param);
			if (CNNGPUD->IsEmpty())
			{
				printf("CNNDetector: error load\n");
				system("pause");
			}

			CNN_param.~Setting();
			root.~Setting();
		}
		catch (...) {};
	}
	if (CNNGPUD == NULL) detectors.use_CNN = false;
#endif

#if 1
	int VJ_step = 0;
	int VJ_flag = 2;
	float VJ_obj_size_correction = 1.f;
	if (detectors.use_VJ)
	{
		try
		{
			Config cfg_file;
			cfg_file.readFile(config_file.c_str());
			const Setting &root = cfg_file.getRoot();

			//-------------

			const Setting &VJ_param = root["VJ_param"];

			string pipeline = "CPU";
			string cascade = "../haarcascade_frontalface_default.xml";
			cascade.reserve(255);

			VJ_param.lookupValue("pipeline", pipeline);
			VJ_param.lookupValue("cascade", cascade);
			VJ_param.lookupValue("step", VJ_step);
			VJ_param.lookupValue("flag", VJ_flag);
			VJ_param.lookupValue("obj_size_correction", VJ_obj_size_correction);

			VJ_step = MAX(0, VJ_step);
			VJ_flag = MAX(0, VJ_flag);
			if (!detectors.use_AFLW)
			{
				VJ_obj_size_correction = 1.f;
			}

			cascade = WorkDir::RecorPath(cascade);

			printf("VJ cascade = %s\n", cascade.c_str());

			if (pipeline == "CPU")
			{
#ifdef OCV_300
				VJD = new CascadeClassifier();
				if (!WorkDir::FileExists(cascade) || !VJD->load(cascade) || VJD->empty())
				{
					printf("Error loading face cascade\n");
					system("pause");
				};
#else
				VJD = NULL;
				detectors.use_VJ = false;
#endif
			}
			if (pipeline == "GPU")
			{
#if defined(OCV_300) && defined(OCV_CUDA)
				int gpuCnt = cuda::getCudaEnabledDeviceCount();
				if (gpuCnt == 0)
				{
					printf("no CUDA device\n");
					system("pause");
				}
				cuda::DeviceInfo info = cuda::getDevice();
				printf("\n");
				printf("Device name = %s\n", info.name());
				printf("major version = %d\n", info.majorVersion());
				printf("multi processor count = %d\n", info.multiProcessorCount());
				if (info.isCompatible())
				{
					printf("OpenCV GPU compatible\n");
				}
				else
				{
					printf("OpenCV GPU not compatible\n");
				}

				//VJGPUD = new cuda::CascadeClassifier_CUDA();
				if (!WorkDir::FileExists(cascade) /*|| !VJGPUD->load(cascade) || VJGPUD->empty()*/)
				{
					printf("Error loading face cascade\n");
					system("pause");
				}
				else
				{
					VJGPUD = cuda::CascadeClassifier::create(cascade);
					if (VJGPUD->empty())
					{
						printf("Error loading face cascade\n");
						system("pause");
					}

					VJGPUD->setScaleFactor(detectors.scale_factor);
					VJGPUD->setMinNeighbors(detectors.min_neighbors);
					VJGPUD->setMinObjectSize(cv::Size((int)roundf(VJ_obj_size_correction * detectors.min_obj_size.width),
						(int)roundf(VJ_obj_size_correction * detectors.min_obj_size.height)));
					VJGPUD->setMaxObjectSize(cv::Size((int)roundf(VJ_obj_size_correction * detectors.max_obj_size.width),
						(int)roundf(VJ_obj_size_correction * detectors.max_obj_size.height)));
				}
#endif
			}
		}
		catch (...) {};
	}
#ifdef OCV_CUDA
	if (VJD == NULL && VJGPUD == NULL) detectors.use_VJ = false;
#else
	if (VJD == NULL) detectors.use_VJ = false;
#endif
#endif

#ifdef SURF
	tagDetectConfig SURF_config;
	float SURF_obj_size_correction = 1.f;
	if (detectors.use_SURF)
	{
		try
		{
			Config cfg_file;
			cfg_file.readFile(config_file.c_str());
			const Setting &root = cfg_file.getRoot();

			//-------------

			const Setting &SURF_param = root["SURF_param"];

			int model_type = 1;
			int step = 1;
			bool fast = true;

			SURF_param.lookupValue("model_type", model_type);
			SURF_param.lookupValue("step", step);
			SURF_param.lookupValue("fast", fast);
			SURF_param.lookupValue("obj_size_correction", SURF_obj_size_correction);

			SURF_config.step = step;
			SURF_config.zscale = detectors.scale_factor;
			SURF_config.knn = detectors.min_neighbors;
			SURF_config.minszx = (int)roundf(SURF_obj_size_correction * detectors.min_obj_size.width);
			SURF_config.minszy = (int)roundf(SURF_obj_size_correction * detectors.min_obj_size.height);
			if (detectors.max_obj_size.height != 0)
			{
				SURF_config.maxsz = (int)roundf(SURF_obj_size_correction * detectors.max_obj_size.height);
			}
			else
			{
				SURF_config.maxsz = (int)roundf(SURF_obj_size_correction * source.frame_size.height);
			}
			SURF_config.fast = fast;

			// get API entry point
			SURFD = getFaceDetector();

			// initialize model
			int nStage = SURFD->initDetector(model_type);

			// set detection parameters
			SURFD->setConfig(&SURF_config);

			// get detector model info (width and height of the detection template)
			int tw = SURFD->getTemplateWidth();
			int th = SURFD->getTemplateHeight();
			printf("SURF num stage = %d\n", nStage);
			printf("SURF pattern size = (%d, %d)\n", tw, th);

			SURF_param.~Setting();

			root.~Setting();
		}
		catch (...) {};
	}
	if (SURFD == NULL) detectors.use_SURF = false;
#endif

#ifdef PICO
	float PICO_step = 0.f;
	if (detectors.use_PICO)
	{
		try
		{
			Config cfg_file;
			cfg_file.readFile(config_file.c_str());
			const Setting &root = cfg_file.getRoot();

			const Setting &PICO_param = root["PICO_param"];

			PICO_param.lookupValue("step", PICO_step);
			PICO_step = MAX(0.f, PICO_step);

			PICO_param.~Setting();

			root.~Setting();
		}
		catch (...) {};
	}
#endif

#ifdef HH
	if (detectors.use_HH)
	{
		try
		{
			Config cfg_file;
			cfg_file.readFile(config_file.c_str());
			const Setting &root = cfg_file.getRoot();

			const Setting &HH_param = root["HH_param"];

			string config_file = "";
			HH_param.lookupValue("config_file", config_file);
			config_file = WorkDir::RecorPath(config_file);

			const boost::filesystem::path configuration_filepath = config_file;
			objects_detection::init_objects_detection(configuration_filepath, false, false);

			HH_param.~Setting();

			root.~Setting();
		}
		catch (...) {};
	}
#endif

#ifdef MATLAB
	int FDPL_model_type = 0;
	if (detectors.use_FDPL)
	{
		try
		{
			Config cfg_file;
			cfg_file.readFile(config_file.c_str());
			const Setting &root = cfg_file.getRoot();

			const Setting &FDPL_param = root["FDPL_param"];
			FDPL_param.lookupValue("model_type", FDPL_model_type);
			FDPL_param.~Setting();

			root.~Setting();
		}
		catch (...) {};
	}

	int MVJ_model_type = 0;
	if (detectors.use_MVJ)
	{
		try
		{
			Config cfg_file;
			cfg_file.readFile(config_file.c_str());
			const Setting &root = cfg_file.getRoot();

			const Setting &MVJ_param = root["MVJ_param"];
			MVJ_param.lookupValue("model_type", MVJ_model_type);
			MVJ_param.~Setting();

			root.~Setting();
		}
		catch (...) {};
	}
#endif

	//---------------------------------------------------------------------------------

	printf("\n");
	printf("start_farame = %d\n", source.start_farame);
	printf("use_Blur = %d\n", source.use_Blur);
	printf("use_BGS = %d\n", source.use_BGS);
	printf("use_Tracker = %d\n", source.use_Tracker);
	printf("scale_factor = %f\n", detectors.scale_factor);
	printf("min_neighbors = %d\n", detectors.min_neighbors);
	printf("min_obj_size.width = %d\n", detectors.min_obj_size.width);
	printf("min_obj_size.height = %d\n", detectors.min_obj_size.height);
	printf("max_obj_size.width = %d\n", detectors.max_obj_size.width);
	printf("max_obj_size.height = %d\n", detectors.max_obj_size.height);
	printf("param.num_threads = %d\n", detectors.num_threads);
	printf("\n");
	printf("---------------------------------------------------------------------------------------\n");
	printf("\n");

	//---------------------------------------------------------------------------------

	if (source.show)
	{
		namedWindow("Face Detection", WINDOW_NORMAL);
	}

	if (source.annotate)
	{
		if (!WorkDir::FileExists(source.input_file + "_test.xml"))
		{
			fstream fannotate(source.input_file + "_test.xml", std::ios_base::out);
			fannotate << "<?xml version='1.0' encoding='UTF-8'?>\n";
			fannotate << "<DemographicsGroundTruth Width=\"" << source.frame_size.width << "\" ";
			fannotate << "Height=\"" << source.frame_size.height << "\" FPS=\"25\">\n";
			fannotate.close();
		}
	}

	Other::Timer timer;
	string file_name = "";
	Mat frame_buff;
	int frame_index = 0;
	for (;;)
	{
		int txt_offset = 50;

		if (source.type != "image")
		{
			if (source.type != "benchmark")
			{
				if (!capture.grab()) break;
				capture.retrieve(frame_buff);
			}
			else
			{
				file_name = source.benchmark_path + img_list[frame_index];
				frame_buff = imread(file_name.c_str(), 1);
			}
		}
		else
		{
			char cstr[260];
			char DefChar = ' ';
			WideCharToMultiByte(CP_ACP, 0, fd.cFileName, -1, cstr, 260, &DefChar, NULL);
			file_name = cstr;
			file_name = source.input_file + file_name;
			frame_buff = imread(file_name.c_str(), 1);
		}

		if (frame_buff.empty())
		{
			if (source.type == "file") break;

			printf("error load file %s\n", file_name.c_str());
			frame_index++;

			if (source.type == "image")
			{
				if (!FindNextFile(handle, &fd)) break;
			}

			if (source.type == "benchmark")
			{
				if (frame_index >= img_list.size()) break;
			}

			continue;
		}

		if (source.type == "file" && source.resize_frame)
		{
			Mat dst;
			resize(frame_buff, dst, source.frame_size);
			frame_buff = dst;
		}

		if (source.use_Blur)
		{
			//cv::medianBlur(frame_buff, frame_buff, 3);
			cv::GaussianBlur(frame_buff, frame_buff, cv::Size(7, 7), 0.8);
		}

		if (source.type == "image" || source.type == "benchmark")
		{
			Mat frame_temp;
			Scalar value = Scalar(0, 0, 0);
			cv::copyMakeBorder(frame_buff, frame_temp, image_border, image_border, image_border, image_border, BORDER_CONSTANT, value);
			frame_buff.release();
			frame_buff = frame_temp;

			source.frame_size.width = frame_buff.cols;
			source.frame_size.height = frame_buff.rows;

#ifdef SURF
			if (detectors.max_obj_size.height == 0 && SURFD != NULL)
			{
				SURF_config.maxsz = (int)roundf(SURF_obj_size_correction * source.frame_size.height);
				SURFD->setConfig(&SURF_config);
			}
#endif

			if (detectors.min_obj != 0.f)
			{
				detectors.min_obj_size.width = detectors.min_obj * source.frame_size.width;
				detectors.min_obj_size.height = detectors.min_obj * source.frame_size.height;

#ifdef CCNN
				if (CNNGPUD != NULL)
				{
					CNNGPUD->setMinObjectSize(NeuralNetworksLib::Size(detectors.min_obj_size.width, detectors.min_obj_size.height));
				}
#endif
#ifdef OCV_CUDA
				if (VJGPUD != NULL)
				{
					VJGPUD->setMinObjectSize(cv::Size((int)roundf(VJ_obj_size_correction * detectors.min_obj_size.width),
						(int)roundf(VJ_obj_size_correction * detectors.min_obj_size.height)));
				}
#endif
#ifdef SURF
				if (SURFD != NULL)
				{
					SURF_config.minszx = (int)roundf(SURF_obj_size_correction * detectors.min_obj_size.width);
					SURF_config.minszy = (int)roundf(SURF_obj_size_correction * detectors.min_obj_size.height);
					SURFD->setConfig(&SURF_config);
				}
#endif
			}
			if (detectors.max_obj != 0.f)
			{
				detectors.max_obj_size.width = detectors.max_obj * source.frame_size.width;
				detectors.max_obj_size.height = detectors.max_obj * source.frame_size.height;

#ifdef CCNN
				if (CNNGPUD != NULL)
				{
					CNNGPUD->setMaxObjectSize(NeuralNetworksLib::Size(detectors.max_obj_size.width, detectors.max_obj_size.height));
				}
#endif
#ifdef OCV_CUDA
				if (VJGPUD != NULL)
				{
					VJGPUD->setMaxObjectSize(cv::Size((int)roundf(VJ_obj_size_correction * detectors.max_obj_size.width),
						(int)roundf(VJ_obj_size_correction * detectors.max_obj_size.height)));
				}
#endif
#ifdef SURF
				if (SURFD != NULL)
				{
					SURF_config.maxsz = (int)roundf(SURF_obj_size_correction * detectors.max_obj_size.height);
					SURFD->setConfig(&SURF_config);
				}
#endif
			}
		}

		if (source.type == "file")
		{
#ifdef OCV_300
			frame_index = (int)capture.get(CAP_PROP_POS_FRAMES);
#else
			frame_index = (int)capture.get(CV_CAP_PROP_POS_FRAMES);
#endif
		}
		else
		{
			frame_index++;
		}

		if (disp_step > 0 && frame_index % disp_step == 0)
		{
			printf("\nframe = %d\n", frame_index);
		}

		if (source.use_BGS)
		{
			if (BGS == NULL)
			{
				BGS = new StaticFrameDifferenceBGS(frame_buff);
			}

			if (frame_index <= source.start_farame + 25)
			{
				BGS->accumulateBackground(frame_buff);
				if (frame_index == source.start_farame + 25)
				{
					BGS->createModelsfromStats();
				}
				continue;
			}
			else
			{
				Mat mask;
				BGS->backgroundDiff(frame_buff, mask);
				//cv::imshow("BGS_mask", mask);
			}
		}

		if (frame_index < source.start_farame) continue;
		if (frame_index - source.start_farame >= source.max_frame) break;

		Mat M_draw;
		if (source.show || source.save_result)
		{
			M_draw = frame_buff.clone();
		}

#ifdef CCNN
		if (detectors.use_CNN)
		{
			Mat M_frame_temp = frame_buff.clone();

			Mat M_frame = M_frame_temp;
			//cv::cvtColor(M_frame_temp, M_frame, CV_BGR2GRAY);

			vector<NeuralNetworksLib::CNNDetector::Detection> cnn_faces;

			timer.start();

			SIMD::Image_8u image(M_frame.cols, M_frame.rows, M_frame.channels(), M_frame.data, (int)M_frame.step[0]);
			CNNGPUD->Detect(cnn_faces, image);

			double time_ = timer.get(1000);
			stat_rate_CNN.time_all += time_;
			double fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_CNN.time_all * 1000.;

#ifdef PROFILE_DETECTOR
			//			CNNGPUD->stat.print();
			//			CNNGPUD->stat.reset();
#endif
			vector<cv::Rect> cnn_faces_ocv;
			toCVRect(cnn_faces_ocv, cnn_faces);

			if (source.use_BGS)
			{
				BGS->dropDetect(cnn_faces_ocv);
			}

			if (source.use_Tracker)
			{
				tracker->Update(cnn_faces_ocv);
			}

			if (disp_step > 0 && frame_index % disp_step == 0)
			{
				print("CNN", time_, fps_, cnn_faces_ocv.size());
			}

			if (source.show || source.save_result)
			{
				draw(M_draw, "CNN", cv::Scalar(0, 0, 255), time_, fps_, txt_offset, cnn_faces_ocv, disp_step > 0 ? true : false, tracker);
			}

			if (source.ground_truth)
			{
				evaluationDetections("CNN", frame_index, cnn_faces_ocv, time_, stat_rate_CNN, tracker);
			}

			if (source.type == "benchmark" && source.save_stat)
			{
				writeDetections(source.output_file, source.input_file, img_list[frame_index - 1], frame_index, source.benchmark_name, "CNN", cnn_faces_ocv);
			}

			cnn_faces.clear();
			cnn_faces_ocv.clear();
		}
#endif

#if 1
		if (detectors.use_VJ)
		{
			Mat M_gray = frame_buff.clone();

			vector<cv::Rect> vj_faces;
			double time_, fps_;

#if defined(OCV_300) && defined(OCV_CUDA)
			if (VJGPUD != NULL)
			{
				cuda::GpuMat faces_dev;

				timer.start();

				cvtColor(M_gray, M_gray, COLOR_BGR2GRAY);
				cuda::GpuMat M_gray_gpu(M_gray);

				VJGPUD->detectMultiScale(M_gray_gpu, faces_dev);
				VJGPUD->convert(faces_dev, vj_faces);

				time_ = timer.get(1000);

				faces_dev.release();
				M_gray_gpu.release();
			}
#endif

			if (VJD != NULL)
			{
				timer.start();

				cvtColor(M_gray, M_gray, COLOR_BGR2GRAY);
#ifdef OCV_300
				VJD->detectMultiScale(M_gray,
					vj_faces,
					detectors.scale_factor,
					/*VJ_step,*/
					detectors.min_neighbors,
					0 | VJ_flag /*CV_HAAR_SCALE_IMAGE*/,
					cv::Size((int)roundf(VJ_obj_size_correction * detectors.min_obj_size.width),
					(int)roundf(VJ_obj_size_correction * detectors.min_obj_size.height)),
					cv::Size((int)roundf(VJ_obj_size_correction * detectors.max_obj_size.width),
					(int)roundf(VJ_obj_size_correction * detectors.max_obj_size.height)));
#endif
				time_ = timer.get(1000);
			}

			if (detectors.use_AFLW)
			{
				stat_rate_AFLW.time_all += time_;
				fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_AFLW.time_all * 1000.;
			}
			else
			{
				if (detectors.use_MTP)
				{
					stat_rate_MTP.time_all += time_;
					fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_MTP.time_all * 1000.;
				}
				else
				{
					stat_rate_VJ.time_all += time_;
					fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_VJ.time_all * 1000.;
				}
			}

			if (detectors.use_AFLW)
			{
				rectExtension(vj_faces);
			}

			if (source.use_BGS)
			{
				BGS->dropDetect(vj_faces);
			}

			if (source.use_Tracker)
			{
				tracker->Update(vj_faces);
			}

			string dtype;
			if (detectors.use_AFLW)
			{
				dtype = "AFLW";
			}
			else
			{
				if (detectors.use_MTP)
					dtype = "MTP";
				else
					dtype = "VJ";
			}

			if (disp_step > 0 && frame_index % disp_step == 0)
			{
				print(dtype, time_, fps_, vj_faces.size());
			}

			if (source.annotate)
			{
				annotateFrame(&frame_buff, &vj_faces, frame_index);
				if (vj_faces.size() > 0)
				{
					fstream fannotate(source.input_file + "_test.xml", std::ios_base::app);
					fannotate << "  <Frame Number=\"" << frame_index << "\">\n";
					for (int p = 0; p < (int)vj_faces.size(); ++p)
					{
						fannotate << "    <Person Gender=\"Male\" Group=\"Caucasian\" ID=\"1\" TrackID=\"1\" Age=\"0\">\n";
						fannotate << "      <Face X=\"" << (float)vj_faces[p].x / (float)source.frame_size.width << "\"";
						fannotate << " Y=\"" << (float)vj_faces[p].y / (float)source.frame_size.height << "\"";
						fannotate << " Width=\"" << (float)vj_faces[p].width / (float)source.frame_size.width << "\"";
						fannotate << " Height=\"" << (float)vj_faces[p].height / (float)source.frame_size.height << "\"/>\n";
						fannotate << "    </Person>\n";
					}
					fannotate << "  </Frame>\n";
					fannotate.close();
				}
			}

			if (source.show || source.save_result)
			{
				draw(M_draw, dtype, Scalar(255, 0, 0), time_, fps_, txt_offset, vj_faces, disp_step > 0 ? true : false, tracker);
			}

			if (source.ground_truth)
			{
				if (detectors.use_AFLW)
					evaluationDetections(dtype, frame_index, vj_faces, time_, stat_rate_AFLW, tracker);
				else
				{
					if (detectors.use_MTP)
						evaluationDetections(dtype, frame_index, vj_faces, time_, stat_rate_MTP, tracker);
					else
						evaluationDetections(dtype, frame_index, vj_faces, time_, stat_rate_VJ, tracker);
				}
			}

			if (source.type == "benchmark" && source.save_stat)
			{
				writeDetections(source.output_file, source.input_file, img_list[frame_index - 1], frame_index, source.benchmark_name, dtype, vj_faces);
			}

			vj_faces.clear();
		}
#endif

#ifdef SURF
		if (detectors.use_SURF)
		{
			Mat M_gray = frame_buff.clone();
			vector<CvMVRect> surf_faces(500);
			CxImage pGrayImg;

			timer.start();

			cvtColor(M_gray, M_gray, COLOR_BGR2GRAY);
			pGrayImg.width = M_gray.cols;
			pGrayImg.height = M_gray.rows;
			pGrayImg.widthStep = M_gray.step[0];
			pGrayImg.nChannel = M_gray.channels();
			pGrayImg.imageData = (uchar*)M_gray.data;
			int n = SURFD->detect(&pGrayImg, (CvMVRect*)surf_faces.data());

			double time_ = timer.get(1000);
			stat_rate_SURF.time_all += time_;
			double fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_SURF.time_all * 1000.;

			surf_faces.resize(n);

			vector<cv::Rect> surf_faces_ocv;
			toCVRect(surf_faces_ocv, surf_faces);
			rectExtension(surf_faces_ocv);

			if (source.use_BGS)
			{
				BGS->dropDetect(surf_faces_ocv);
			}

			if (source.use_Tracker)
			{
				tracker->Update(surf_faces_ocv);
			}

			if (disp_step > 0 && frame_index % disp_step == 0)
			{
				print("SURF", time_, fps_, surf_faces_ocv.size());
			}

			if (source.show || source.save_result)
			{
				draw(M_draw, "SURF", cv::Scalar(0, 255, 0), time_, fps_, txt_offset, surf_faces_ocv, disp_step > 0 ? true : false, tracker);
			}

			if (source.ground_truth)
			{
				evaluationDetections("SURF", frame_index, surf_faces_ocv, time_, stat_rate_SURF, tracker);
			}

			if (source.type == "benchmark" && source.save_stat)
			{
				writeDetections(source.output_file, source.input_file, img_list[frame_index - 1], frame_index, source.benchmark_name, "SURF", surf_faces_ocv);
			}

			surf_faces.clear();
			surf_faces_ocv.clear();
		}
#endif

#ifdef PICO
		if (detectors.use_PICO)
		{
			Mat M_gray = frame_buff.clone();
			vector<cv::Rect> pico_faces;

			timer.start();

			cvtColor(M_gray, M_gray, COLOR_RGB2GRAY);
			process_image(pico_faces, &M_gray, detectors.scale_factor, detectors.min_neighbors, PICO_step, detectors.min_obj_size, detectors.max_obj_size);

			double time_ = timer.get(1000);
			stat_rate_PICO.time_all += time_;
			double fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_PICO.time_all * 1000.;

			if (source.use_BGS)
			{
				BGS->dropDetect(pico_faces);
			}

			if (source.use_Tracker)
			{
				tracker->Update(pico_faces);
			}

			if (disp_step > 0 && frame_index % disp_step == 0)
			{
				print("PICO", time_, fps_, pico_faces.size());
			}

			if (source.show || source.save_result)
			{
				draw(M_draw, "PICO", cv::Scalar(102, 153, 204), time_, fps_, txt_offset, pico_faces, disp_step > 0 ? true : false, tracker);
			}

			if (source.ground_truth)
			{
				evaluationDetections("PICO", frame_index, pico_faces, time_, stat_rate_PICO, tracker);
			}

			if (source.type == "benchmark" && source.save_stat)
			{
				writeDetections(source.output_file, source.input_file, img_list[frame_index - 1], frame_index, source.benchmark_name, "PICO", pico_faces);
			}

			pico_faces.clear();
		}
#endif

#ifdef FDLIB
		if (detectors.use_FDLIB)
		{
			Mat M_gray = frame_buff.clone();
			vector<cv::Rect> fdlib_faces;
			const int threshold = detectors.min_neighbors;

			timer.start();

			cvtColor(M_gray, M_gray, COLOR_RGB2GRAY);
			unsigned char *graydata = new unsigned char[M_gray.cols *  M_gray.rows];
			for (int j = 0; j < M_gray.rows; ++j)
			{
				memcpy(graydata + j * M_gray.cols, M_gray.data + j * M_gray.step[0], M_gray.cols);
			}
			fdlib_detectfaces(graydata, M_gray.cols, M_gray.rows, threshold);
			delete[] graydata;

			double time_ = timer.get(1000);
			stat_rate_FDLIB.time_all += time_;
			double fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_FDLIB.time_all * 1000.;

			int n = fdlib_getndetections();
			for (int i = 0; i < n; i++)
			{
				int x, y, size;
				fdlib_getdetection(i, &x, &y, &size);
				fdlib_faces.push_back(cv::Rect(x - size, y - size, 2 * size, 2 * size));
			}

			if (source.use_BGS)
			{
				BGS->dropDetect(fdlib_faces);
			}

			if (source.use_Tracker)
			{
				tracker->Update(fdlib_faces);
			}

			if (disp_step > 0 && frame_index % disp_step == 0)
			{
				print("FDLIB", time_, fps_, fdlib_faces.size());
			}

			if (source.show || source.save_result)
			{
				draw(M_draw, "FDLIB", cv::Scalar(120, 120, 120), time_, fps_, txt_offset, fdlib_faces, disp_step > 0 ? true : false, tracker);
			}

			if (source.ground_truth)
			{
				evaluationDetections("FDLIB", frame_index, fdlib_faces, time_, stat_rate_FDLIB, tracker);
			}

			if (source.type == "benchmark" && source.save_stat)
			{
				writeDetections(source.output_file, source.input_file, img_list[frame_index - 1], frame_index, source.benchmark_name, "FDLIB", fdlib_faces);
			}

			fdlib_faces.clear();
		}
#endif

#ifdef HH
		if (detectors.use_HH)
		{
			Mat M_gray = frame_buff.clone();
			objects_detection::input_image_const_view_t input_image = boost::gil::interleaved_view(M_gray.cols, M_gray.rows, (const boost::gil::rgb8_pixel_t*)M_gray.data, M_gray.step[0]);

			objects_detection::detections_t detections;
			vector<cv::Rect> hh_faces;

			timer.start();

			objects_detection::set_monocular_image(input_image);
			objects_detection::compute();
			detections = objects_detection::get_detections();

			double time_ = timer.get(1000);
			stat_rate_HH.time_all += time_;
			double fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_HH.time_all * 1000.;

			for (int t = 0; t < detections.size(); ++t)
			{
				cv::Rect rect(
					cv::Point(
					detections[t].bounding_box.min_corner().x(),
					detections[t].bounding_box.min_corner().y()),
					cv::Point(
					detections[t].bounding_box.max_corner().x(),
					detections[t].bounding_box.max_corner().y())
					);
				hh_faces.push_back(rect);
			}

			rectExtension(hh_faces);

			if (source.use_BGS)
			{
				BGS->dropDetect(hh_faces);
			}

			if (source.use_Tracker)
			{
				tracker->Update(hh_faces);
			}

			if (disp_step > 0 && frame_index % disp_step == 0)
			{
				print("HH", time_, fps_, hh_faces.size());
			}

			if (source.show || source.save_result)
			{
				draw(M_draw, "HH", cv::Scalar(120, 255, 120), time_, fps_, txt_offset, hh_faces, disp_step > 0 ? true : false, tracker);
			}

			if (source.ground_truth)
			{
				evaluationDetections("HH", frame_index, hh_faces, time_, stat_rate_HH, tracker);
			}

			if (source.type == "benchmark" && source.save_stat)
			{
				writeDetections(source.output_file, source.input_file, img_list[frame_index - 1], frame_index, source.benchmark_name, "HH", hh_faces);
			}

			hh_faces.clear();
		}
#endif

#ifdef MATLAB
		if (detectors.use_FacePP)
		{
			Mat M_gray = frame_buff.clone();
			vector<cv::Rect> facePP_faces;

			double time_ = 0.;
			matlab.evalFacePP(facePP_faces, time_, M_gray);
			time_ *= 1000.0;

			stat_rate_FacePP.time_all += time_;
			double fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_FacePP.time_all * 1000.;

			rectExtension(facePP_faces);

			if (source.use_BGS)
			{
				BGS->dropDetect(facePP_faces);
			}

			if (source.use_Tracker)
			{
				tracker->Update(facePP_faces);
			}

			if (disp_step > 0 && frame_index % disp_step == 0)
			{
				print("Face++", time_, fps_, facePP_faces.size());
			}

			if (source.show || source.save_result)
			{
				draw(M_draw, "Face++", cv::Scalar(0, 120, 120), time_, fps_, txt_offset, facePP_faces, disp_step > 0 ? true : false, tracker);
			}

			if (source.ground_truth)
			{
				evaluationDetections("Face++", frame_index, facePP_faces, time_, stat_rate_FacePP, tracker);
			}

			if (source.type == "benchmark" && source.save_stat)
			{
				writeDetections(source.output_file, source.input_file, img_list[frame_index - 1], frame_index, source.benchmark_name, "Face++", facePP_faces);
			}

			facePP_faces.clear();
		}

		if (detectors.use_FDPL)
		{
			Mat M_gray = frame_buff.clone();
			vector<cv::Rect> FDPL_faces;

			double time_ = 0.;
			matlab.evalFDPL(FDPL_faces, time_, M_gray, FDPL_model_type);
			time_ *= 1000.0;

			stat_rate_FDPL.time_all += time_;
			double fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_FDPL.time_all * 1000.;

			if (source.use_BGS)
			{
				BGS->dropDetect(FDPL_faces);
			}

			if (source.use_Tracker)
			{
				tracker->Update(FDPL_faces);
			}

			if (disp_step > 0 && frame_index % disp_step == 0)
			{
				print("FDPL", time_, fps_, FDPL_faces.size());
			}

			if (source.show || source.save_result)
			{
				draw(M_draw, "FDPL", cv::Scalar(120, 120, 0), time_, fps_, txt_offset, FDPL_faces, disp_step > 0 ? true : false, tracker);
			}

			if (source.ground_truth)
			{
				evaluationDetections("FDPL", frame_index, FDPL_faces, time_, stat_rate_FDPL, tracker);
			}

			if (source.type == "benchmark" && source.save_stat)
			{
				writeDetections(source.output_file, source.input_file, img_list[frame_index - 1], frame_index, source.benchmark_name, "FDPL", FDPL_faces);
			}

			FDPL_faces.clear();
		}

		if (detectors.use_MVJ)
		{
			Mat M_gray = frame_buff.clone();
			vector<cv::Rect> MVJ_faces;

			double time_ = 0.;
			matlab.evalMVJ(MVJ_faces, time_, M_gray, MVJ_model_type, detectors.scale_factor, detectors.min_neighbors, detectors.min_obj_size, detectors.max_obj_size);
			time_ *= 1000.0;

			stat_rate_MVJ.time_all += time_;
			double fps_ = (double)(frame_index - source.start_farame - 25 * (int)source.use_BGS) / stat_rate_MVJ.time_all * 1000.;

			if (source.use_BGS)
			{
				BGS->dropDetect(MVJ_faces);
			}

			if (source.use_Tracker)
			{
				tracker->Update(MVJ_faces);
			}

			if (disp_step > 0 && frame_index % disp_step == 0)
			{
				print("MVJ", time_, fps_, MVJ_faces.size());
			}

			if (source.show || source.save_result)
			{
				draw(M_draw, "MVJ", cv::Scalar(120, 0, 120), time_, fps_, txt_offset, MVJ_faces, disp_step > 0 ? true : false, tracker);
			}

			if (source.ground_truth)
			{
				evaluationDetections("MVJ", frame_index, MVJ_faces, time_, stat_rate_MVJ, tracker);
			}

			if (source.type == "benchmark" && source.save_stat)
			{
				writeDetections(source.output_file, source.input_file, img_list[frame_index - 1], frame_index, source.benchmark_name, "MVJ", MVJ_faces);
			}

			MVJ_faces.clear();
		}
#endif

		if (source.ground_truth)
		{
			GroundTruth* fgt = frame_ground_truth[frame_index];

			if (fgt != NULL && fgt->frameID == frame_index)
			{
				for (int p = 0; p < fgt->person.size(); ++p)
				{
#if 0
					for (int j = -1; j <= 1; ++j)
					{
						for (int i = -1; i <= 1; ++i)
						{
							for (int s = -2; s <= 2; ++s)
							{
								double scale = 0.;
								if (s < 0)
								{
									scale = pow(1.1, double(-s));
								}
								else
								{
									scale = pow(0.95, double(s));
								}
								int scale_x = int(scale * double(fgt->person[p].rect.width));
								int scale_y = int(scale * double(fgt->person[p].rect.height));

								int X0 = fgt->person[p].rect.x - ((scale_x - fgt->person[p].rect.width) >> 1);
								int Y0 = fgt->person[p].rect.y - ((scale_y - fgt->person[p].rect.height) >> 1);
								int X1 = X0 + scale_x;
								int Y1 = Y0 + scale_y;

								int rx = int(double(X1 - X0) * 0.2);
								if (i < 0)
								{
									X0 += i * rx;
								}
								else
								{
									X1 += i * rx;
								}

								int ry = int(float(Y1 - Y0) * 0.2f);
								Y0 += j * ry;

								rectangle(M_draw, Point(X0, Y0), Point(X1, Y1), Scalar(255, 255, 0), 2, 8, 0);
							}
						}
					}
#endif			

					rectangle(M_draw, Point(fgt->person[p].rect.x, fgt->person[p].rect.y), Point(fgt->person[p].rect.x + fgt->person[p].rect.width, fgt->person[p].rect.y + fgt->person[p].rect.height), Scalar(0, 255, 255), 3, 8, 0);
				}
			}
		}

		//static int false_detect = stat_rate_PICO.false_detections;
		if (source.show)
		{
			cv::imshow("Face Detection", M_draw);
			waitKey(source.sleep);

			//if (false_detect != stat_rate_PICO.false_detections)
			//{
			//	false_detect = stat_rate_PICO.false_detections;
			//	waitKey(0);
			//}
		}

		if (source.save_result)
		{
			if (source.type == "cam" || source.type == "ip_cam" || source.type == "file")
			{
				record->write(M_draw);
			}

			if (source.type == "image" || source.type == "benchmark")
			{
				file_name.insert(file_name.size() - 4, "_result");
				cv::imwrite(file_name, M_draw);
			}
		}

		if (source.type == "image" || source.type == "benchmark")
		{
			frame_buff.release();
		}

		if (source.type == "image")
		{
			if (!FindNextFile(handle, &fd)) break;
		}
	}

#ifdef PROFILE_DETECTOR
	if (detectors.use_CNN) CNNGPUD->stat.print();
#endif

	if (source.annotate)
	{
		fstream fannotate(source.input_file + "_test.xml", std::ios_base::app);
		fannotate << "</DemographicsGroundTruth>";
		fannotate.close();
	}

	if (source.type == "cam" || source.type == "ip_cam" || source.type == "file")
	{
		if (capture.isOpened()) capture.release();
	}
	else
	{
		FindClose(handle);
	}

	if (source.save_result)
	{
		if (source.type == "cam" || source.type == "ip_cam" || source.type == "file")
		{
			record->release();
			delete record;
		}
	}

	if (source.pause)
	{
		system("pause");
	}

#if 1
	if (source.save_stat && source.ground_truth)
	{
		if (detectors.use_CNN)
		{
			save("CNN", stat_rate_CNN, source.input_file, source.output_file, config_file);
		}

		if (detectors.use_VJ)
		{
			string dtype = "";
			if (detectors.use_AFLW)
				dtype = "AFLW";
			else
			{
				if (detectors.use_MTP)
					dtype = "MTP";
				else
					dtype = "VJ";
			}

#ifdef OCV_CUDA
			if (VJGPUD != NULL) dtype.append("GPU");
#endif

			if (detectors.use_AFLW)
				save(dtype, stat_rate_AFLW, source.input_file, source.output_file, config_file);
			else
			{
				if (detectors.use_MTP)
					save(dtype, stat_rate_MTP, source.input_file, source.output_file, config_file);
				else
					save(dtype, stat_rate_VJ, source.input_file, source.output_file, config_file);
			}
		}

#ifdef SURF	
		if (detectors.use_SURF)
		{
			save("SURF", stat_rate_SURF, source.input_file, source.output_file, config_file);
		}
#endif

		if (detectors.use_PICO)
		{
			save("PICO", stat_rate_PICO, source.input_file, source.output_file, config_file);
		}

		if (detectors.use_FDLIB)
		{
			save("FDLIB", stat_rate_FDLIB, source.input_file, source.output_file, config_file);
		}

#ifdef USE_HH
		if (detectors.use_HH)
		{
			save("HH", stat_rate_HH, source.input_file, source.output_file, config_file);
			objects_detection::free_object_detector();
		}
#endif

#ifdef MATLAB
		if (detectors.use_FacePP)
		{
			save("Face++", stat_rate_FacePP, source.input_file, source.output_file, config_file);
		}

		if (detectors.use_FDPL)
		{
			save("FDPL", stat_rate_FDPL, source.input_file, source.output_file, config_file);
		}

		if (detectors.use_MVJ)
		{
			save("MVJ", stat_rate_MVJ, source.input_file, source.output_file, config_file);
		}
#endif
	}
#endif

	return 0;
}

//--------------------------------------------------------------------------------------------------------

#if defined(CCNN) && defined(_DEBUG)
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

void MemoryTest()
{
	_CrtMemState _ms;
	_CrtMemCheckpoint(&_ms);

	{
		printf("GPU CNN detector\n");

		CNNDetector *CNNGPUD;
		CNNDetector::Param param;
		CNNDetector::AdvancedParam ad_param;
		string path_model_1 = "cnn4face1_new.bin";
		string path_model_2 = "cnn4face2_new.bin";
		string path_model_3 = "cnn4face3_new.bin";
		ad_param.path_model[0] = WorkDir::GetCurrentDir() + path_model_1;
		ad_param.path_model[1] = WorkDir::GetCurrentDir() + path_model_2;
		ad_param.path_model[2] = WorkDir::GetCurrentDir() + path_model_3;
		ad_param.cl_platform_id = 0;
		ad_param.cl_device_id = 1;
		param.num_threads = 16;
		param.pipeline = CNNDetector::Pipeline::GPU;
		CNNGPUD = new CNNDetector(&param, &ad_param);

		SIMD::Image_8u img_8u(1920, 1080, 3, 1, false);
		vector<CNNDetector::Detection> detection;

		CNNGPUD->setMaxImageSize(NeuralNetworksLib::Size(320, 240));
		CNNGPUD->Detect(detection, img_8u);
		printf("Size(320, 240)\n");

		CNNGPUD->setMaxImageSize(NeuralNetworksLib::Size(640, 480));
		CNNGPUD->Detect(detection, img_8u);
		printf("Size(640, 480)\n");

		CNNGPUD->setMaxImageSize(NeuralNetworksLib::Size(800, 600));
		CNNGPUD->Detect(detection, img_8u);
		printf("Size(800, 600)\n");

		CNNGPUD->setMaxImageSize(NeuralNetworksLib::Size(1280, 720));
		CNNGPUD->Detect(detection, img_8u);
		printf("Size(1280, 720)\n");

		CNNGPUD->setMaxImageSize(NeuralNetworksLib::Size(1920, 1080));
		CNNGPUD->Detect(detection, img_8u);
		printf("Size(1920, 1080)\n");

		delete CNNGPUD;

		vector<SIMD::ConvNeuralNetwork*> cnn_simd;
		cnn_simd.push_back(new SIMD::ConvNeuralNetwork());
		cnn_simd[0]->Init("W:/Projects/NeuralNetworks/CNNFaceDetectorGPU/bin/Debug/x64/cnn4face1_new.bin");
		delete cnn_simd[0];
		cnn_simd.clear();
	}

	_CrtMemDumpAllObjectsSince(&_ms);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
}
#endif

//--------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	string path_prog = argv[0];
	string *param_ = new string[argc - 1];
	for (int i = 0; i < argc - 1; ++i)
	{
		param_[i].append(argv[i + 1]);
		param_[i] = WorkDir::RecorPath(param_[i]);
		if (param_[i] == "no") param_[i] = "";
	}

	if (argc < 2)
	{
		string config = WorkDir::GetCurrentDir() + "FaceDetectorConfig.txt";
		if (WorkDir::FileExists(config))
		{
			return FaceDetectorDemo(config);
		}
	}

	if (argc == 2) return FaceDetectorDemo(param_[0]);
	if (argc == 3) return FaceDetectorDemo(param_[0], param_[1]);

	if (argc == 4)
	{
		param_[2] = WorkDir::FileExistsAndRename(param_[2]);
		return FaceDetectorDemo(param_[0], param_[1], param_[2]);
	}

	if (argc == 5 && param_[3] != "")
	{
		return FaceDetectorDemo(param_[0], param_[1], param_[2], param_[3]);
	}

	if (argc == 7)
	{
		int min_sz = atoi(param_[3].c_str());
		float sf = atof(param_[4].c_str());
		int min_nn = atoi(param_[5].c_str());

		return FaceDetectorDemo(param_[0], param_[1], param_[2], "", min_sz, sf, min_nn);
	}

	if (argc == 8 && param_[3] != "")
	{
		int min_sz = atoi(param_[4].c_str());
		float sf = atof(param_[5].c_str());
		int min_nn = atoi(param_[6].c_str());

		return FaceDetectorDemo(param_[0], param_[1], param_[2], param_[3], min_sz, sf, min_nn);
	}

	//Video data analysis
	printf("start\n");
	printf("config_file = %s\n", param_[0].c_str());
	printf("input_file = %s\n", param_[1].c_str());
	printf("output_file = %s\n", param_[2].c_str());

	HANDLE handle;
	WIN32_FIND_DATA fd;
	string cmd_str;

	string current_path = WorkDir::GetCurrentDir();
	vector<string> file_masks = { "\\*.avi", "\\*.mp4", "\\*.mkv" };

	int clips_count = 1;
	for (int index = 0; index < file_masks.size(); ++index)
	{
		handle = FindFirstFile(Converter::StrToTChar(param_[1] + file_masks[index]), &fd);
		if (handle == INVALID_HANDLE_VALUE) continue;
		do
		{
			printf("\n\n\nclips_count = %d\n", clips_count++);

			printf("file_name = %s\n", Converter::WCharToStr(fd.cFileName).c_str());

			cmd_str = path_prog + " " + param_[0] + " " + param_[1] + "/" + Converter::WCharToStr(fd.cFileName) + " " + param_[2];
			if (argc == 8)
			{
				cmd_str += " " + param_[4] + " " + param_[5] + " " + param_[6];
			}

			printf("cmd_str = %s\n", cmd_str.c_str());

			system(cmd_str.c_str());
		} while (FindNextFile(handle, &fd) != 0);
		FindClose(handle);
	}

	printf("stop\n");
	return 0;
}