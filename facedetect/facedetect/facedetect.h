#pragma once
//more about this in reference 1
#ifdef FACEDETECT_EX
#define FACEDETECT  __declspec(dllexport)   // export DLL information

#else
#define FACEDETECT  __declspec(dllimport)   // import DLL information

#endif 

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

class FACEDETECT FaceDetectDll
{
public:
	FaceDetectDll(void);
	~FaceDetectDll(void);

	struct Face
	{
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
		int cameraSizeX = 0;
		int cameraSizeY = 0;
	};

	Face getFace();
	void loadCascade(const char* fn_haar);
	static bool isFaceEmpty(Face* p);

private:

	void releaseCamera();
	void newCamera(int _cameraId);

	cv::VideoCapture* stream;
	bool m_isOpen = false;
	int cameraId = 0;
	cv::CascadeClassifier* haar_cascade;
};

