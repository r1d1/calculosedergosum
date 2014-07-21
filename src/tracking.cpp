#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <opencv/highgui.h>
#include <opencv/cv.h>

int MAX_KERNEL_LENGTH = 31;

using namespace std;
using namespace cv;
 
int main (int argc, char* argv[])
{
	IplImage* img = NULL;
	const char* window_title = "Hello, OpenCV!"; 
	//int windowsOffset = 1380;
	int windowsOffset = 0;

	CvCapture * capture = cvCreateCameraCapture( CV_CAP_ANY );

	if (!capture)
	{
		cout << "Cant open video flow !" << endl;
		return EXIT_FAILURE;
	}
 
	int selectedColor = atoi(argv[2]);
 
	IplImage * camflow;
	IplImage * camflow_hsv;
	IplImage * camflow_h;
	IplImage * camflow_s;
	IplImage * camflow_v;
	IplImage * camflow_h_th;
	IplImage * camflow_h_th_up;
	IplImage * camflow_h_th_ls;
	IplImage * camflow_s_th;
	IplImage * camflow_s_th_up;
	IplImage * camflow_s_th_ls;
	IplImage * camflow_v_th;
	IplImage * camflow_v_th_up;
	IplImage * camflow_v_th_ls;
	IplImage * camflow_blobs;
	IplImage * camflow_blobs_smooth;
	
//	cvNamedWindow ("gray cam", CV_WINDOW_AUTOSIZE);  
//	cvNamedWindow ("cam flow", CV_WINDOW_AUTOSIZE);  
//	cvNamedWindow ("processing flow", CV_WINDOW_AUTOSIZE);
	
	char key;
	camflow = cvQueryFrame(capture);

	camflow_hsv = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, camflow->nChannels);
	camflow_h = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_s = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_v = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_h_th = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_h_th_up = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_h_th_ls = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_s_th = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_s_th_up = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_s_th_ls = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_v_th = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_v_th_up = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_v_th_ls = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_blobs = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_blobs_smooth = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);

	while(key != 'q')
	{
		camflow = cvQueryFrame(capture);

		std::cout << "Image channels (" << camflow->nChannels << ") ; channels organisation : " << camflow->dataOrder << std::endl;
		std::cout << "Image channel R (" << camflow_h->nChannels << ") ; channels organisation : " << camflow_h->dataOrder << std::endl;
		std::cout << "Image channel G (" << camflow_s->nChannels << ") ; channels organisation : " << camflow_s->dataOrder << std::endl;
		std::cout << "Image channel B (" << camflow_v->nChannels << ") ; channels organisation : " << camflow_v->dataOrder << std::endl;

		cvCvtColor(camflow, camflow_hsv, CV_BGR2HSV);
		cvSplit(camflow_hsv, camflow_h, camflow_s, camflow_v, NULL);

		// No transform
	/*	cvThreshold(camflow_h, camflow_h_th, 0, 255, THRESH_BINARY);
		cvThreshold(camflow_s, camflow_s_th, 0, 255, THRESH_BINARY);
		cvThreshold(camflow_v, camflow_v_th, 0, 255, THRESH_BINARY);*/

		// Get only red
		// Hue is 0-180, Saturation and Value are 0-255
		// For red : [H : 175 -> 5]
		// For blue : [H : 110 -> 130]
		// For blue : [H : 50 -> 70]

		cvThreshold(camflow_h, camflow_h_th_ls, 175, 255, THRESH_BINARY);
		cvThreshold(camflow_h, camflow_h_th_up, 5, 255, THRESH_BINARY_INV);
		cvMul(camflow_h_th_up, camflow_h_th_ls, camflow_h_th, 1.0/255.0);

		cvThreshold(camflow_s, camflow_s_th_ls, 0, 255, THRESH_BINARY);
		cvThreshold(camflow_s, camflow_s_th_up, 0, 255, THRESH_BINARY);
		cvMul(camflow_s_th_up, camflow_s_th_ls, camflow_s_th, 1.0/255.0);
		
		cvThreshold(camflow_v, camflow_v_th_ls, 204, 255, THRESH_BINARY);
		cvThreshold(camflow_v, camflow_v_th_up, 204, 255, THRESH_BINARY);
		cvMul(camflow_v_th_up, camflow_v_th_ls, camflow_v_th, 1.0/255.0);

//		cvThreshold(camflow_h, camflow_h_th, 115, 255, THRESH_BINARY);
//		cvThreshold(camflow_h_th, camflow_h_th, 125, 255, THRESH_BINARY_INV);
//		cvThreshold(camflow_h, camflow_h_th, 170, 255, THRESH_BINARY);
//		cvThreshold(camflow_h_th, camflow_h_th, 10, 255, THRESH_BINARY_INV);
//		cvThreshold(camflow_s, camflow_s_th, 200, 255, THRESH_BINARY);
//		cvThreshold(camflow_s, camflow_s_th, 5, 255, THRESH_BINARY_INV);
//		cvThreshold(camflow_v, camflow_v_th, 170, 255, THRESH_BINARY);
//		cvThreshold(camflow_v, camflow_v_th, 5, 255, THRESH_BINARY_INV);

		//camflow_blobs->imageData = (camflow_h_th->imageData + camflow_h_th->imageData + camflow_h_th->imageData) / 3.0;
		IplImage * camflow_tmp = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
		//cvAddWeighted(camflow_h_th, 1.0, camflow_s_th, 1.0, 0.0, camflow_tmp);
		//cvThreshold(camflow_tmp, camflow_tmp, 200, 255, THRESH_BINARY);
		//cvAdd(camflow_h_th, camflow_s_th, camflow_tmp);
		//cvAddWeighted(camflow_tmp, 1.0, camflow_v_th, 1.0, 0.0, camflow_tmp);
		//cvThreshold(camflow_tmp, camflow_blobs, 200, 255, THRESH_BINARY);
		cvMul(camflow_h_th, camflow_s_th, camflow_tmp, 1.0/255.0);
		cvMul(camflow_tmp, camflow_v_th, camflow_blobs, 1.0/255.0);

		Mat smoothed, detectionpic(camflow_blobs);
		for(int i=1 ; i < 31 ; i=i+2)
		{ GaussianBlur(detectionpic, smoothed, Size(i,i), 0, 0); }
		*camflow_blobs_smooth = smoothed;

		// Compute center of the cluster, draw a point to get the coordinates
		// TODO !

		cvShowImage("input", camflow);
	//	cvMoveWindow("input",windowsOffset,10);
		cvShowImage("H", camflow_h_th);
	//	cvMoveWindow("H",windowsOffset,525);
		cvShowImage("S", camflow_s_th);
	//	cvMoveWindow("S",windowsOffset+650,525);
		cvShowImage("V", camflow_v_th);
	//	cvMoveWindow("V",windowsOffset+650*2,525);
	//	cvShowImage("HSV", camflow_hsv);
	//	cvMoveWindow("HSV",windowsOffset+650,10);
		cvShowImage("Out", camflow_blobs_smooth);
	//	cvMoveWindow("Out",windowsOffset+650*2,10);
		key = cvWaitKey(10);
	}
	cvDestroyAllWindows();
	cvReleaseImage(&camflow);
	cvReleaseCapture(&capture);

	return EXIT_SUCCESS;
}
