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

	CvCapture * capture = cvCreateCameraCapture( CV_CAP_ANY );

	if (!capture)
	{
		cout << "Cant open video flow !" << endl;
		return EXIT_FAILURE;
	}
 
	int selectedColor = atoi(argv[2]);
 
/*	if (argc < 2)
	{
		fprintf (stderr, "usage: %s IMAGE\n", argv[0]);
		return EXIT_FAILURE;
	}*/

//	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_UNCHANGED);
 
 /*	if (img == NULL)
	{
		fprintf (stderr, "couldn't open image file: %s\n", argv[1]);
		return EXIT_FAILURE;
	}
  */
/*	cout << "img metadata : " << img->nSize << " w : " << img->width << " h: " << img->height << " chan : " << img->nChannels << " sep : " << img->dataOrder << " imgsize : " << img->imageSize << endl;
	cout << "img data : " << (int)img->imageData[0] << " " << (int)img->imageData[1] << " " << (int)img->imageData[2] << " " << (int)img->imageData[3] << " " << (int)img->imageData[4] << " " << (int)img->imageData[5] << " " << (int)img->imageData[6] << " " << endl;
*/
	IplImage * camflow;
	IplImage * camflow_hsv;
	IplImage * camflow_r;
	IplImage * camflow_g;
	IplImage * camflow_b;
	
	cvNamedWindow ("gray cam", CV_WINDOW_AUTOSIZE);  
	cvNamedWindow ("cam flow", CV_WINDOW_AUTOSIZE);  
	cvNamedWindow ("processing flow", CV_WINDOW_AUTOSIZE);
	
	char key;
	camflow = cvQueryFrame(capture);


	camflow_hsv = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, camflow->nChannels);
	camflow_r = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_g = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);
	camflow_b = cvCreateImage(cvSize(camflow->width,camflow->height), camflow->depth, 1);

	while(key != 'q')
	{
		camflow = cvQueryFrame(capture);

		std::cout << "Image channels (" << camflow->nChannels << ") ; channels organisation : " << camflow->dataOrder << std::endl;
		std::cout << "Image channel R (" << camflow_r->nChannels << ") ; channels organisation : " << camflow_r->dataOrder << std::endl;
		std::cout << "Image channel G (" << camflow_g->nChannels << ") ; channels organisation : " << camflow_g->dataOrder << std::endl;
		std::cout << "Image channel B (" << camflow_b->nChannels << ") ; channels organisation : " << camflow_b->dataOrder << std::endl;

		cvCvtColor(camflow, camflow_hsv, CV_BGR2HSV);
		cvSplit(camflow_hsv, camflow_r, camflow_g, camflow_b, NULL);

//		120, 255, 255
	/*	double meanofpix=0;
		double maxi=0;
			
		for(int i=0 ; i < graycam->imageSize ; i++)
		{
			diffcam->imageData[i] = ((graycam->imageData[i] - previousgraycam->imageData[i]) < 64) ? 0 : graycam->imageData[i] - previousgraycam->imageData[i];
			previousgraycam->imageData[i] = graycam->imageData[i];
		}

		Mat smoothimage, originalimage(diffcam);
		for(int i=1 ; i < MAX_KERNEL_LENGTH ; i=i+2 )
			GaussianBlur(originalimage, smoothimage, Size(i,i), 0, 0);
		
		*smoothcam = smoothimage;

		float maxima = 0;
		int indexmaxi = 0;

		for(int i=0 ; i < smoothcam->imageSize ; i++)
		{
			maxima = (smoothcam->imageData[i] > maxima) ? smoothcam->imageData[i] : maxima;
			indexmaxi = (smoothcam->imageData[i] > maxima) ? i : indexmaxi;
		}
	
		smoothcam->imageData[indexmaxi] = 255;
		cvShowImage ("gray cam", graycam);
		cvShowImage ("cam flow", diffcam);
		cvShowImage ("processing flow", smoothcam);
		*/
		cvShowImage ("input", camflow);
		cvShowImage ("Red input", camflow_r);
		cvShowImage ("Green input", camflow_g);
		cvShowImage ("Blue input", camflow_b);
		cvShowImage ("HSV", camflow_hsv);
		key = cvWaitKey(10);
	}
	cvDestroyAllWindows();
	cvReleaseImage(&camflow);
	cvReleaseCapture(&capture);

	return EXIT_SUCCESS;
}
