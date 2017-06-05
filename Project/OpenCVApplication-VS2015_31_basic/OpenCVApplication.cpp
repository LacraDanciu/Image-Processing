// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"


Mat value_dst;
Mat hue_dst;
Mat saturation_dst;
Mat Cb_dst;

#define OBJECT 0
#define BACKGROUND 255

void testOpenImage()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src;
		src = imread(fname);
		imshow("image", src);
		waitKey();
	}
}

void testOpenImagesFld()
{
	char folderName[MAX_PATH];
	if (openFolderDlg(folderName) == 0)
		return;
	char fname[MAX_PATH];
	FileGetter fg(folderName, "bmp");
	while (fg.getNextAbsFile(fname))
	{
		Mat src;
		src = imread(fname);
		imshow(fg.getFoundFileName(), src);
		if (waitKey() == 27) //ESC pressed
			break;
	}
}

void testImageOpenAndSave()
{
	Mat src, dst;

	src = imread("Images/Lena_24bits.bmp", CV_LOAD_IMAGE_COLOR);	// Read the image

	if (!src.data)	// Check for invalid input
	{
		printf("Could not open or find the image\n");
		return;
	}

	// Get the image resolution
	Size src_size = Size(src.cols, src.rows);

	// Display window
	const char* WIN_SRC = "Src"; //window for the source image
	namedWindow(WIN_SRC, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_SRC, 0, 0);

	const char* WIN_DST = "Dst"; //window for the destination (processed) image
	namedWindow(WIN_DST, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_DST, src_size.width + 10, 0);

	cvtColor(src, dst, CV_BGR2GRAY); //converts the source image to a grayscale one

	imwrite("Images/Lena_24bits_gray.bmp", dst); //writes the destination to file

	imshow(WIN_SRC, src);
	imshow(WIN_DST, dst);

	printf("Press any key to continue ...\n");
	waitKey(0);
}

void testNegativeImage()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		double t = (double)getTickCount(); // Get the current time [s]

		Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;
		Mat dst = Mat(height, width, CV_8UC1);
		// Asa se acceseaaza pixelii individuali pt. o imagine cu 8 biti/pixel
		// Varianta ineficienta (lenta)
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				uchar val = src.at<uchar>(i, j);
				uchar neg = MAX_PATH - val;
				dst.at<uchar>(i, j) = neg;
			}
		}

		// Get the current time again and compute the time difference [s]
		t = ((double)getTickCount() - t) / getTickFrequency();
		// Print (in the console window) the processing time in [ms] 
		printf("Time = %.3f [ms]\n", t * 1000);

		imshow("input image", src);
		imshow("negative image", dst);
		waitKey();
	}
}

void testParcurgereSimplaDiblookStyle()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
		int height = src.rows;
		int width = src.cols;
		Mat dst = src.clone();

		double t = (double)getTickCount(); // Get the current time [s]

		// the fastest approach using the “diblook style”
		uchar *lpSrc = src.data;
		uchar *lpDst = dst.data;
		int w = (int)src.step; // no dword alignment is done !!!
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++) {
				uchar val = lpSrc[i*w + j];
				lpDst[i*w + j] = 255 - val;
			}

		// Get the current time again and compute the time difference [s]
		t = ((double)getTickCount() - t) / getTickFrequency();
		// Print (in the console window) the processing time in [ms] 
		printf("Time = %.3f [ms]\n", t * 1000);

		imshow("input image", src);
		imshow("negative image", dst);
		waitKey();
	}
}

void testColor2Gray()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname);

		int height = src.rows;
		int width = src.cols;

		Mat dst = Mat(height, width, CV_8UC1);

		// Asa se acceseaaza pixelii individuali pt. o imagine RGB 24 biti/pixel
		// Varianta ineficienta (lenta)
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Vec3b v3 = src.at<Vec3b>(i, j);
				uchar b = v3[0];
				uchar g = v3[1];
				uchar r = v3[2];
				dst.at<uchar>(i, j) = (r + g + b) / 3;
			}
		}

		//imshow("input image", src);
		//imshow("gray image", dst);
		waitKey();
	}
}

void testBGR2HSV()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src = imread(fname);
		int height = src.rows;
		int width = src.cols;

		// Componentele d eculoare ale modelului HSV
		Mat H = Mat(height, width, CV_8UC1);
		Mat S = Mat(height, width, CV_8UC1);
		Mat V = Mat(height, width, CV_8UC1);

		// definire pointeri la matricele (8 biti/pixeli) folosite la afisarea componentelor individuale H,S,V
		uchar* lpH = H.data;
		uchar* lpS = S.data;
		uchar* lpV = V.data;

		Mat hsvImg;
		cvtColor(src, hsvImg, CV_BGR2HSV);

		// definire pointer la matricea (24 biti/pixeli) a imaginii HSV
		uchar* hsvDataPtr = hsvImg.data;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int hi = i*width * 3 + j * 3;
				int gi = i*width + j;

				lpH[gi] = hsvDataPtr[hi] * 510 / 360;		// lpH = 0 .. 255
				lpS[gi] = hsvDataPtr[hi + 1];			// lpS = 0 .. 255
				lpV[gi] = hsvDataPtr[hi + 2];			// lpV = 0 .. 255
			}
		}

		//imshow("input image", src);
		//imshow("H", H);
		//imshow("S", S);
		//imshow("V", V);

		waitKey();
	}
}

void testResize()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src;
		src = imread(fname);
		Mat dst1, dst2;
		//without interpolation
		resizeImg(src, dst1, 320, false);
		//with interpolation
		resizeImg(src, dst2, 320, true);
		imshow("input image", src);
		imshow("resized image (without interpolation)", dst1);
		imshow("resized image (with interpolation)", dst2);
		waitKey();
	}
}

void testCanny()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src, dst, gauss;
		src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
		double k = 0.4;
		int pH = 50;
		int pL = (int)k*pH;
		GaussianBlur(src, gauss, Size(5, 5), 0.8, 0.8);
		Canny(gauss, dst, pL, pH, 3);
		imshow("input image", src);
		imshow("canny", dst);
		waitKey();
	}
}

void testVideoSequence()
{
	VideoCapture cap("Videos/rubic.avi"); // off-line video from file
	//VideoCapture cap(0);	// live video from web cam
	if (!cap.isOpened()) {
		printf("Cannot open video capture device.\n");
		waitKey(0);
		return;
	}

	Mat edges;
	Mat frame;
	char c;

	while (cap.read(frame))
	{
		Mat grayFrame;
		cvtColor(frame, grayFrame, CV_BGR2GRAY);
		Canny(grayFrame, edges, 40, 100, 3);
		imshow("source", frame);
		imshow("gray", grayFrame);
		imshow("edges", edges);
		c = cvWaitKey(0);  // waits a key press to advance to the next frame
		if (c == 27) {
			// press ESC to exit
			printf("ESC pressed - capture finished\n");
			break;  //ESC pressed
		};
	}
}

void testSnap()
{
	VideoCapture cap(0); // open the deafult camera (i.e. the built in web cam)
	if (!cap.isOpened()) // openenig the video device failed
	{
		printf("Cannot open video capture device.\n");
		return;
	}

	Mat frame;
	char numberStr[256];
	char fileName[256];

	// video resolution
	Size capS = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	// Display window
	const char* WIN_SRC = "Src"; //window for the source frame
	namedWindow(WIN_SRC, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_SRC, 0, 0);

	const char* WIN_DST = "Snapped"; //window for showing the snapped frame
	namedWindow(WIN_DST, CV_WINDOW_AUTOSIZE);
	cvMoveWindow(WIN_DST, capS.width + 10, 0);

	char c;
	int frameNum = -1;
	int frameCount = 0;

	for (;;)
	{
		cap >> frame; // get a new frame from camera
		if (frame.empty())
		{
			printf("End of the video file\n");
			break;
		}

		++frameNum;

		imshow(WIN_SRC, frame);

		c = cvWaitKey(10);  // waits a key press to advance to the next frame
		if (c == 27) {
			// press ESC to exit
			printf("ESC pressed - capture finished");
			break;  //ESC pressed
		}
		if (c == 115) { //'s' pressed - snapp the image to a file
			frameCount++;
			fileName[0] = NULL;
			sprintf(numberStr, "%d", frameCount);
			strcat(fileName, "Images/A");
			strcat(fileName, numberStr);
			strcat(fileName, ".bmp");
			bool bSuccess = imwrite(fileName, frame);
			if (!bSuccess)
			{
				printf("Error writing the snapped image\n");
			}
			else
				imshow(WIN_DST, frame);
		}
	}

}

void MyCallBackFunc(int event, int x, int y, int flags, void* param)
{
	//More examples: http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
	Mat* src = (Mat*)param;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		printf("Pos(x,y): %d,%d  Color(RGB): %d,%d,%d\n",
			x, y,
			(int)(*src).at<Vec3b>(y, x)[2],
			(int)(*src).at<Vec3b>(y, x)[1],
			(int)(*src).at<Vec3b>(y, x)[0]);
	}
}

void testMouseClick()
{
	Mat src;
	// Read image from file 
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		src = imread(fname);
		//Create a window
		namedWindow("My Window", 1);

		//set the callback function for any mouse event
		setMouseCallback("My Window", MyCallBackFunc, &src);

		//show the image
		imshow("My Window", src);

		// Wait until user press some key
		waitKey(0);
	}
}

/// ------------------------------------------------------- Methods written for project ----------------------------------------------

void erosion(Mat src, Mat *dst, Mat M);
void dilation(Mat src, Mat *dst, Mat M);

void opening(Mat src, Mat M)
{
	Mat dst = src.clone();

	erosion(src, &dst, M);
	//imshow("temp", dst);

	Mat dst2 = dst.clone();

	dilation(dst, &dst2, M);
	//imshow("opening", dst2);
}

void closing(Mat src, Mat M)
{
	Mat dst = src.clone();

	dilation(src, &dst, M);

	Mat dst2 = dst.clone();

	erosion(dst, &dst2, M);

	//imshow("closing", dst2);
}

void boundaryExtraction(Mat src, Mat *dst, Mat M)
{
	int width = src.cols;
	int height = src.rows;
	erosion(src, dst, M);
	Mat dst2 = Mat(height, width, CV_8UC1);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			dst2.at<uchar>(i, j) = BACKGROUND;
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (src.at<uchar>(i, j) != (*dst).at<uchar>(i, j))
			{
				dst2.at<uchar>(i, j) = src.at<uchar>(i, j);
			}
		}
	}

	//imshow("Boundary", dst2);
}

void dilation(Mat src, Mat *dst, Mat M)
{
	// M is a nucleu from which I map them onto image
	*dst = src.clone();
	int height = src.rows;
	int width = src.cols;
	int size = (M.rows - 1) / 2;

	for (int i = size; i < height - size; i++)
	{
		for (int j = size; j < width - size; j++)
		{
			if (src.at<uchar>(i, j) == OBJECT)
			{
				for (int m = 0; m < M.rows; m++)
				{
					for (int k = 0; k < M.rows; k++)
					{
						if (M.at<uchar>(m, k) == 1)
						{
							(*dst).at<uchar>(i + m - size, j + k - size) = OBJECT;
						}
					}
				}
			}
		}
	}

	//imshow("Result", dst);
}

void erosion(Mat src, Mat *dst, Mat M)
{
	// M is a nucleu from which I map them onto image
	*dst = src.clone();
	int height = src.rows;
	int width = src.cols;
	int size = (M.rows - 1) / 2;
	boolean found = true;

	for (int i = size; i < height - size; i++)
	{
		for (int j = size; j < width - size; j++)
		{
			if (src.at<uchar>(i, j) == OBJECT)
			{
				for (int m = 0; m < M.rows; m++)
				{
					for (int k = 0; k < M.rows; k++)
					{
						if (M.at<uchar>(m, k) == 1)
						{
							if (src.at<uchar>(i + m - size, j + k - size) == BACKGROUND)
							{
								(*dst).at<uchar>(i, j) = BACKGROUND;
							}
						}
					}
				}
			}
		}
	}

	//imshow("Result", *dst);
}

Mat fromRGBToHSV(Mat src)
{
	int height = src.rows;
	int width = src.cols;
	value_dst = Mat(height, width, CV_8UC1);
	hue_dst = Mat(height, width, CV_8UC1);
	saturation_dst = Mat(height, width, CV_8UC1);

	float r, g, b, M, m, C, value, saturation, hue;
	uchar H_norm, V_norm, S_norm;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			r = (float)src.at< Vec3b>(i, j)[2] / 255;
			g = (float)src.at< Vec3b>(i, j)[1] / 255;
			b = (float)src.at< Vec3b>(i, j)[0] / 255;


			M = max(r, max(g, b));
			m = min(r, min(g, b));
			C = M - m;

			// value
			value = M;

			//saturation
			if (C)
			{
				saturation = C / value;
			}
			else
			{
				saturation = 0;
			}

			//hue
			if (C)
			{
				if (M == r)
				{
					hue = 60 * (g - b) / C;
				}
				if (M == g)
				{
					hue = 120 + 60 * (b - r) / C;
				}
				if (M == b)
				{
					hue = 240 + 60 * (r - g) / C;
				}
			}
			else
			{
				hue = 0;
			}

			if (hue < 0)
			{
				hue = hue + 360;
			}

			saturation_dst.at<uchar>(i, j) = saturation * 255;
			value_dst.at<uchar>(i, j) = value * 255;
			hue_dst.at<uchar>(i, j) = hue * 255 / 360;

		}
	}

	/*imshow("input image", src);
	imshow("hue image", hue_dst);
	imshow("saturation image", saturation_dst);
	imshow("value image", value_dst);*/
	return hue_dst;
}

void fromRGBtoYCrCb(Mat src)
{
	int height = src.rows;
	int width = src.cols;
	Cb_dst = Mat(height, width, CV_8UC1);
	float r, g, b;
	float Y = 0, Cr = 0;
	int delta = 128;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			r = (float)src.at< Vec3b>(i, j)[2] / 255;
			g = (float)src.at< Vec3b>(i, j)[1] / 255;
			b = (float)src.at< Vec3b>(i, j)[0] / 255;

			Y = (0.299 * r + 0.587 * g + 0.114 * b);
			Cr = ((r - Y) * 0.713 + delta);
			Cb_dst.at<uchar>(i, j) = (int)((b - Y) * 0.564 + delta);
		}
	}
}

// the step to choose by the hue channel of the HSV transform
void firstSkinStep(Mat *src)
{
	int height = src->rows;
	int width = src->cols;

	// choose only the skin by the hue channel
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (hue_dst.at<uchar>(i, j) < 250 && hue_dst.at<uchar>(i, j) > 19)
			{
				src->at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
}

// the step to choose by the Cr channel of the YCrCb transform 
void secondSkinStep(Mat *src)
{
	int height = src->rows;
	int width = src->cols;

	// choose regarding the CB channel
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (Cb_dst.at<uchar>(i, j) <= 102 || Cb_dst.at<uchar>(i, j) >= 128)
			{
				src->at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
}

// the Thresolding on the G and B color channels
void RBGThresolding(Mat src, Mat *dst)
{
	int height = src.rows;
	int width = src.cols;
	//RGB color space
	float r, g, b;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			r = src.at<Vec3b>(i, j)[2];
			g = src.at<Vec3b>(i, j)[1];
			b = src.at<Vec3b>(i, j)[0];

			if (b <= (0.836 * g - 14) || b >= (0.836 * g + 44))
			{
				dst->at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
			if (b <= (0.79 * g - 67) || b >= (0.78 * g + 42))
			{
				dst->at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
}

// obtain the binary image 
void binarizeImage(Mat src, Mat *dst)
{
	int height = src.rows;
	int width = src.cols;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (src.at<Vec3b>(i, j) != Vec3b(0, 0, 0))
			{
				dst->at<uchar>(i, j) = BACKGROUND;
			}
			else
			{
				dst->at<uchar>(i, j) = OBJECT;
			}
		}
	}
}

// masking the lower part of an image -> it's not ok for all pictures
// it works only for pictures where people are all standing up and we can see their whole body
void maskingLowerPart(Mat *src)
{
	int height = src->rows;
	int width = src->cols;
	// this masking isn't ok for close up photos - > optional to use this
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i > (2 * height / 3))
			{
				src->at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
}

void basedOnSaturationStep(Mat *src)
{
	int height = src->rows;
	int width = src->cols;

	// choose only the skin by the hue channel
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (saturation_dst.at<uchar>(i, j) < 40)
			{
				src->at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
}

void GetMatBlobRemove(Mat *src)
{
	// threashold specifying minimum area of a blob
	double threshold = 200;

	std::vector<std::vector<Point>> contours;

	std::vector<Vec4i> hierarchy;
	int *small_blobs;
	double contour_area;
	Mat temp_image;
	cvtColor(*src, temp_image, CV_RGB2GRAY);

	// find all contours in the binary image
	//src.copyTo(temp_image);
	findContours(temp_image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	int p = 0;
	small_blobs = (int *)malloc(sizeof(int) * (contours.size()));
	// Find indices of contours whose area is less than `threshold` 
	if (!contours.empty()) {
		for (size_t i = 0; i < contours.size(); ++i) {

			contour_area = contourArea(contours[i]);
			if (contour_area < threshold) {
				small_blobs[p] = i;
				p++;
			}
		}
	}

	// fill-in all small contours with zeros
	for (size_t i = 0; i < p; ++i) {
		drawContours(*src, contours, small_blobs[i], cv::Scalar(0), CV_FILLED, 8);
	}

	imshow("After blob removal", *src);
}

Mat face;
void templateGenerator() {
	Mat tmpl;
	Mat tmpl1 = imread("template.jpg", CV_LOAD_IMAGE_GRAYSCALE); //open and read the image
	resize(tmpl1, tmpl, Size(150, 180)); // 5 pe primul rand x 30, 6 pe coloana x 30
	face = Mat(Size(30, 30), tmpl.type());
	Mat hist;
	equalizeHist(tmpl, hist);
	
	//aduna de la primul pixel din imaginea 1, al doilea din imaginea 2 ....
	for (int i = 0; i < tmpl.rows; i++)
		for (int j = 0; j < tmpl.cols; j++) {
			face.at<uchar>(i % 30, j % 30) += 0.033333 * tmpl.at<uchar>(i, j);
		}

	imshow("Average face", face);
	imshow("Normalized histogram", hist);

}

Mat fromColorToGray(Mat src)
{
	int height = src.rows;
	int width = src.cols;
	Mat dst = Mat(height, width, CV_8UC1);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			dst.at<uchar>(i, j) = (src.at< Vec3b>(i, j)[0] + src.at< Vec3b>(i, j)[1] + src.at< Vec3b>(i, j)[2]) / 3;
		}
	}

	return dst;
}

void convolutionAndNormalization(Mat src, Mat kernel, Mat *dst, Mat *convolution)
{
	int height = src.rows;
	int width = src.cols;
	double sum;
	int median;

	int energy = 0;

	for (int i = 0; i < kernel.rows; i++)
	{
		for (int j = 0; j < kernel.cols; j++)
		{
			energy += kernel.at<uchar>(i, j);
		}
	}

	for (int i = kernel.rows; i < height - kernel.rows; i++)
	{
		for (int j = kernel.cols; j < width - kernel.cols; j++)
		{
			sum = 0;
			for (int p = 0; p < kernel.rows; p++)
			{
				for (int q = 0; q < kernel.cols; q++)
				{
					sum += src.at<uchar>(i + p - 1, j + q - 1) * kernel.at<uchar>(p, q);
				}
			}

			// normalize by the energy in the template
			sum = sum / energy;
			dst->at<double>(i, j) = sum;
		}
	}

	int maxim = INT_MIN;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (maxim <= dst->at<double>(i, j))
			{
				maxim = dst->at<double>(i, j);
			}
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			convolution->at<uchar>(i, j) = (int)255 * dst->at<double>(i, j) / maxim;

		}
	}

}

void findPeaksInImage(Mat src, Mat dst, int threshold)
{
	int height = src.rows;
	int width = src.cols; 
	int maxim = INT_MIN;
	int notDone;

	for (int i = 30; i < height - 30; i++)
	{
		for (int j = 30; j < width - 30; j++)
		{
			if (src.at<uchar>(i, j) > threshold)
			{
				notDone = 0;
				maxim = INT_MIN;
				for (int p = 0; p < 30; p++)
				{
					for (int m = 0; m < 30; m++)
					{
						if (src.at<uchar>(i + p - 15, j + m - 15) > maxim)
						{
							maxim = src.at<uchar>(i + p - 15, j + m - 15);
						}
					}
				}

				if (src.at<uchar>(i,j) == maxim)
				{
					dst.at<Vec3b>(i, j) = Vec3b(0, 0, 255);
				}
			
			}
		}
	}

	Scalar color = Scalar(0, 255, 0);
	for (int i = 0; i < height; i++)
	{
		for (int j =0; j < width ; j++)
		{

			if (dst.at<Vec3b>(i, j) == Vec3b(0, 0, 255))
			{
				Point p;
				p.x = j;
				p.y = i;
				Point p1;
				p1.x = j + 30;
				p1.y = i + 30;
				rectangle(dst, p, p1, color, 2, 8, 0);
			}
		}
	}

	imshow("Result!", dst);
}

int main()
{
	char fname[MAX_PATH];

	system("cls");
	destroyAllWindows();
	printf("Select an image:\n");

	if (openFileDlg(fname))
	{
		Mat src = imread(fname, CV_LOAD_IMAGE_COLOR);
		printf("Apply the RGB to HSV transform on the image.\n");
		Mat aux2;
		Mat aux = src.clone();
		Mat binary = Mat(src.rows, src.cols, CV_8UC1);
		fromRGBToHSV(aux);

		// the first skin thresolding
		firstSkinStep(&aux);
		imshow("First skin step", aux);

		// RGB to YCrCb transform
		fromRGBtoYCrCb(aux);
		imshow("After YCrCb step", aux);

		// the second skin thresolding
		secondSkinStep(&aux);
		imshow("Second skin step", aux);

		//the RBG thresolding where we try to get rid of other colors from the image != skin color
		RBGThresolding(src, &aux);
		imshow("After RGB thresholding", aux);

		basedOnSaturationStep(&aux);
		imshow("After saturation thresholding", aux);

		// obtain the binary image based on what we have until now -> skin and not skin
		binarizeImage(aux, &binary);

		Mat M = Mat(3, 3, CV_8UC1);
		M.at<uchar>(0, 0) = 1;
		M.at<uchar>(0, 1) = 1;
		M.at<uchar>(0, 2) = 1;
		M.at<uchar>(1, 0) = 1;
		M.at<uchar>(1, 1) = 1;
		M.at<uchar>(1, 2) = 1;
		M.at<uchar>(2, 0) = 1;
		M.at<uchar>(2, 1) = 1;
		M.at<uchar>(2, 2) = 1;

		//After opening transform
		opening(aux, M);

		//After blob removal
		GetMatBlobRemove(&aux);
		aux2 = fromColorToGray(aux);
		imshow("gray image", aux2);

		//generate the template face
		templateGenerator();

		// do the convolution with the face
		Mat convo = Mat::zeros(aux2.rows, aux2.cols, CV_64FC1);
		Mat convolution = Mat(aux2.rows, aux2.cols, CV_8UC1);
		convolutionAndNormalization(aux2, face, &convo, &convolution);

		imshow("convolution", convolution);

		// the threshold should be over 150 or something
		findPeaksInImage(convolution, src, 150);
		waitKey();

	}

	return 0;
}