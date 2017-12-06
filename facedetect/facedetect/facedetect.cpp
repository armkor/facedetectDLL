// facedetect.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "facedetect.h"

using namespace cv;
using namespace std;

FaceDetectDll::FaceDetectDll(void)
{
	newCamera(0);
}

FaceDetectDll::~FaceDetectDll(void)
{
	if (haar_cascade != nullptr) delete haar_cascade;
	releaseCamera();
}

FaceDetectDll::Face FaceDetectDll::getFace()
{
	Face result;
	if (haar_cascade == nullptr) return result;

	Mat frame;
	if (m_isOpen) {
		stream->read(frame);
	}
	
	Mat original = frame.clone();
	Mat gray;
	cvtColor(original, gray, CV_BGR2GRAY);
	vector< Rect_<int> > faces;
	haar_cascade->detectMultiScale(gray, faces);
	if (faces.size() != 0)
	{
		Rect face_i = faces[0];
		result.x = face_i.x;
		result.y = face_i.y;
		result.height = face_i.height;
		result.width = face_i.width;
		cv::Size s = frame.size();
		result.cameraSizeX = s.height;
		result.cameraSizeY = s.width;
	}
	return result;
}
void FaceDetectDll::loadCascade(const char* fn_haar)
{
	haar_cascade = new CascadeClassifier();
	haar_cascade->load(fn_haar);
}

bool FaceDetectDll::isFaceEmpty(Face * p)
{
	return (p->x == 0 &&
		p->y == 0 &&
		p->width == 0 &&
		p->height == 0);
}

void FaceDetectDll::releaseCamera()
{
	if (stream && stream->isOpened()) {
		stream->release();
		delete stream;
	}

	m_isOpen = false;
}

void FaceDetectDll::newCamera(int _cameraId)
{
	if (m_isOpen)
		releaseCamera();
	stream = new cv::VideoCapture();
	stream->open(_cameraId);
	cameraId = _cameraId;
	m_isOpen = stream->isOpened();
}