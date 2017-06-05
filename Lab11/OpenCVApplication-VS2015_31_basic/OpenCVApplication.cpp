// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"
#include <queue>


Mat value_dst;
Mat hue_dst;
Mat saturation_dst;
Mat fromRGBToHSV(Mat src);

#define OBJECT 0
#define BACKGROUND 255
#define IDEAL_LOW_FILTER 100
#define IDEAL_HIGH_FILTER 101
#define GAUSS_LOW_FILTER 102
#define GAUSS_HIGH_FILTER 103

//sliding window
int WH = 5; //window 2*WH + 1
float TH = 0.0003; // threshold
double t;

/// PREDEFINED FUNCTIONS FOR THE PROJECT

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

void OpenImage()
{
	char fname[MAX_PATH];
	while (openFileDlg(fname))
	{
		Mat src;
		src = imread(fname);
		imshow("Source", src);
		Mat dst = src.clone();
		imshow("Destination", dst); //nume  diferit la ferestra de afisare
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
		imshow("source", frame);
		imshow("gray", grayFrame);
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

// processing part for the pixel we click ok
// the algorithm in laboratory 2 for the red color
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

		fromRGBToHSV(*src);

		float M, m;

		int height = (*src).rows;
		int width = (*src).cols;
		Mat final = Mat(height, width, CV_8UC1);

		float Da, Do, Dr, Drc, Drcn;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//Da = abs(hue_dst.at<uchar>(x, y) - (*src).at<uchar>(i, j));
				M = max(hue_dst.at<uchar>(i, j), hue_dst.at<uchar>(y, x));
				m = min(hue_dst.at<uchar>(i, j), hue_dst.at<uchar>(y, x));

				Da = M - m;

				Do = m + 255 - M;

				Dr = 30 - min(Da, Do);

				if (Dr > 0)
				{
					Drc = Dr;
				}
				else
				{
					Drc = 0;
				}

				Drcn = (float)(Drc) * 255 / 30;
				final.at<uchar>(i, j) = static_cast<uchar>(Drcn);

			}
		}

		imshow("red", final);
	}
}

void onMouse(int event, int x, int y, int flags, void* param);

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

		//show the image
		imshow("My Window", src);

		//set the callback function for any mouse event
		//setMouseCallback("My Window", MyCallBackFunc, &src);
		setMouseCallback("My Window", onMouse, &src);

		//show the image
		imshow("My Window", src);

		// Wait until user press some key
		waitKey(0);
	}
}

/* HistogramMultilevelAndFloyd display function - display a histogram using bars (simlilar to L3 / PI)
Input:
name - destination (output) window name
hist - pointer to the vector containing the histogram values
hist_cols - no. of bins (elements) in the histogram = histogram image width
hist_height - height of the histogram image
Call example:
showHistogram ("MyHist", hist_dir, 255, 200);
*/
void showHistogram(const std::string& name, int* hist, const int  hist_cols, const int hist_height)
{
	Mat imgHist(hist_height, hist_cols, CV_8UC3, CV_RGB(255, 255, 255)); // constructs a white image

																		 //computes histogram maximum
	int max_hist = 0;
	for (int i = 0; i < hist_cols; i++)
		if (hist[i] > max_hist)
			max_hist = hist[i];
	double scale = 1.0;
	scale = (double)hist_height / max_hist;
	int baseline = hist_height - 1;

	for (int x = 0; x < hist_cols; x++) {
		Point p1 = Point(x, baseline);
		Point p2 = Point(x, baseline - cvRound(hist[x] * scale));
		line(imgHist, p1, p2, CV_RGB(255, 0, 255)); // histogram bins colored in magenta
	}

	imshow(name, imgHist);
}

void CreateLookAheadArray(int histo[], int *dst);

/// ----------------------------------------------------------- LAB 1 ------------------------------------------------------
void negative_image() {

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

	/// my approach
	/*Mat src = imread("Images/cameraman.bmp",CV_LOAD_IMAGE_GRAYSCALE);
	for (int i = 0; i < src.rows; i++){
	for (int j = 0; j < src.cols; j++){
	src.at<uchar>(i, j) = 255 - src.at<uchar>(i, j);
	}
	}
	imshow("negative image", src);
	waitKey(0);*/
}

unsigned char in_interval(int value)
{
	if (value > 255)
	{
		return 255;
	}
	else if (value < 0)
	{
		return 0;
	}
	else
	{
		return (unsigned char)value;
	}
}

//3. Implement a function which changes the gray levels of an image by an additive factor 
void additive_factor_to_image() {
	Mat img = imread("Images/cameraman.bmp",
		CV_LOAD_IMAGE_GRAYSCALE);

	int additive_factor = 45;
	int pi;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {

			pi = img.at<uchar>(i, j);
			pi = pi + additive_factor;
			img.at<uchar>(i, j) = in_interval(pi);
		}
	}
	imshow("additive image", img);
	waitKey(0);
}

//4. Implement a function which changes the gray levels of an image by a multiplicative_factor_to_image
//factor.Save the resulting image.
void multiplicative_factor_to_image() {
	Mat img = imread("Images/cameraman.bmp",
		CV_LOAD_IMAGE_GRAYSCALE);

	int multi_factor = 2;
	int pi;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			pi = img.at<uchar>(i, j);
			pi = pi * multi_factor;

			img.at<uchar>(i, j) = in_interval(pi);
		}
	}
	imshow("multiplicative_factor_to_image image", img);
	//saving the image
	//imwrite("Images/cameraman2.bmp", src);
	waitKey(0);
}

//5. Create a color image of dimension 256 x 256. Divide it into 4 squares and color the
//squares from top to bottom, left to right as : white, red, green, yellow.
void create_color_image5()
{
	Mat img(256, 256, CV_8UC3);

	/*for (int i = 0; i < src.rows; i++){
	for (int j = 0; j < src.cols; j++){
	if (j < src.cols / 2 && i < src.rows / 2)
	{
	src.at< Vec3b>(i, j)[0] = 255;
	src.at< Vec3b>(i, j)[1] = 255;
	src.at< Vec3b>(i, j)[2] = 255;
	}
	else if (j > src.cols / 2 && i < src.rows / 2)
	{
	src.at< Vec3b>(i, j)[0] = 0;
	src.at< Vec3b>(i, j)[1] = 0;
	src.at< Vec3b>(i, j)[2] = 255;
	}
	else if (j < src.cols / 2 && i > src.rows / 2)
	{
	src.at< Vec3b>(i, j)[0] = 0;
	src.at< Vec3b>(i, j)[1] = 255;
	src.at< Vec3b>(i, j)[2] = 0;
	}
	else if (j > src.cols / 2 && i > src.rows / 2)
	{
	src.at< Vec3b>(i, j)[0] = 0;
	src.at< Vec3b>(i, j)[1] = 255;
	src.at< Vec3b>(i, j)[2] = 255;
	}
	}
	}*/

	//lines of different colors
	int i, j; i = 0; j = 0;
	while (i < img.rows) {
		while (j < img.cols) {
			if (j < 4 && j % 2 == 0) {
				img.at< Vec3b>(i, j)[0] = 0;
				img.at< Vec3b>(i, j)[1] = 255;
				img.at< Vec3b>(i, j)[2] = 0;
			}
			else if (j < 4 && j % 2 == 1) {
				img.at< Vec3b>(i, j)[0] = 0;
				img.at< Vec3b>(i, j)[1] = 0;
				img.at< Vec3b>(i, j)[2] = 255;
			}
			else if (j % 2 == 0 && j > 4 && j < img.cols) {
				img.at< Vec3b>(i, j)[0] = 0;
				img.at< Vec3b>(i, j)[1] = 0;
				img.at< Vec3b>(i, j)[2] = 255;

				img.at< Vec3b>(i, j + 1)[0] = 0;
				img.at< Vec3b>(i, j + 1)[1] = 255;
				img.at< Vec3b>(i, j + 1)[2] = 0;

				img.at< Vec3b>(i, j + 2)[0] = 255;
				img.at< Vec3b>(i, j + 2)[1] = 0;
				img.at< Vec3b>(i, j + 2)[2] = 0;

				j = j + 2;
			}
			j++;
		}
		i++;
	}

	imshow("color image", img);
	waitKey(0);
}

// 6. Create a 3x3 float matrix, determine its inverse and print it.
void testFloatMatrix()
{
	Mat mymatrix(3, 3, CV_32FC1);
	Mat mymatrixInverse(3, 3, CV_32FC1);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (i == j)
				mymatrix.at<float>(i, j) = 1.0f;
			else
				mymatrix.at<float>(i, j) = 0.0f;

		}
	}

	mymatrix = mymatrix.inv();

	std::cout << mymatrix;
	waitKey(0);
}

// Exercise
// create a darker circle to the margins of the image
void darker_image()
{
	Mat img = imread("Images/cameraman.bmp",
		CV_LOAD_IMAGE_GRAYSCALE);

	double delta_max = 300;
	double distance;
	double delta_p;
	double i0, j0;
	double dmax;
	i0 = img.rows / 2;
	j0 = img.cols / 2;
	dmax = sqrt(i0* i0 + j0*j0);

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			distance = sqrt(pow(i - i0, 2) + pow(j - j0, 2));
			delta_p = pow(distance / dmax, 2) * delta_max;

			int pi = img.at<uchar>(i, j);

			pi = (int)pi - delta_p;
			pi = in_interval(pi);

			img.at<uchar>(i, j) = pi;
		}
	}
	imshow("darker image", img);
	waitKey(0);
}

// Scale an image (zoom_in, zoom_out) with a scale factor
void scale_image(float scale_factor)
{
	Mat img = imread("Images/cameraman.bmp",
		CV_LOAD_IMAGE_GRAYSCALE);
	double i_aux, j_aux;

	Mat dst = img.clone();

	double i0, j0;
	i0 = img.rows / 2;
	j0 = img.cols / 2;

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) { // i,j destination
			i_aux = i0 + scale_factor * (i - i0);
			j_aux = j0 + scale_factor * (j - j0);

			if (i_aux > 0 && i_aux < dst.rows && j_aux > 0 && j_aux < dst.cols)
				dst.at<uchar>(i, j) = img.at<uchar>(i_aux, j_aux);
			else
				dst.at<uchar>(i, j) = 0;

		}
	}

	imshow("zoom", dst);
	waitKey(0);
}

// change the size of the image with a n size
void change_the_size(float size)
{
	Mat img = imread("Images/cameraman.bmp",
		CV_LOAD_IMAGE_GRAYSCALE);
	double i_aux, j_aux;

	imshow("source", img);

	Mat dst((img.rows / size), (img.cols / size), CV_8UC1);

	double i0, j0, i0d, j0d;
	i0 = img.rows / 2;
	j0 = img.cols / 2;

	i0d = dst.rows / 2;
	j0d = dst.cols / 2;

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) { // i,j destination
			i_aux = i0 + size * (i - i0d);
			j_aux = j0 + size * (j - j0d);

			if (i_aux > 0 && i_aux < dst.rows && j_aux > 0 && j_aux < dst.cols)
				dst.at<uchar>(i, j) = img.at<uchar>(i_aux, j_aux);
			else
				dst.at<uchar>(i, j) = 0;

		}
	}

	imshow("changed", dst);
	waitKey(0);
}

// create a circle to the margins of the image - lentile effect
void lentile_effect(float k)
{
	Mat img = imread("Images/cameraman.bmp",
		CV_LOAD_IMAGE_GRAYSCALE);

	double i_aux, j_aux;

	Mat dst = img.clone();

	double i0, j0;
	i0 = img.rows / 2;
	j0 = img.cols / 2;

	double delta_max = 300;
	double distance;
	double delta_p;
	double dmax;
	double delta_k;

	dmax = sqrt(i0* i0 + j0*j0);

	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			distance = sqrt(pow(i - i0, 2) + pow(j - j0, 2));

			delta_k = pow(distance / dmax, 2) * k;

			i_aux = i0 + (k + delta_k) * (i - i0);
			j_aux = j0 + (k + delta_k) * (j - j0);

			if (i_aux > 0 && i_aux < dst.rows && j_aux > 0 && j_aux < dst.cols)
				dst.at<uchar>(i, j) = img.at<uchar>(i_aux, j_aux);
			else
				dst.at<uchar>(i, j) = 0;
		}
	}
	imshow("lentile image", dst);
	waitKey(0);
}

/// ------------------------------------------------------------ LAB 2 ---------------------------------------------------------
/// exercise 1 to 4 in this 3 functions
Mat fromColorToGray()
{
	char fname[MAX_PATH];
	if (openFileDlg(fname))
	{
		Mat src = imread(fname, CV_LOAD_IMAGE_COLOR);
		int height = src.rows;
		int width = src.cols;
		Mat dst = Mat(height, width, CV_8UC1);
		Mat red = Mat(height, width, CV_8UC1);
		Mat green = Mat(height, width, CV_8UC1);
		Mat blue = Mat(height, width, CV_8UC1);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				dst.at<uchar>(i, j) = (src.at< Vec3b>(i, j)[0] + src.at< Vec3b>(i, j)[1] + src.at< Vec3b>(i, j)[2]) / 3;
				red.at<uchar>(i, j) = src.at< Vec3b>(i, j)[2];
				blue.at<uchar>(i, j) = src.at< Vec3b>(i, j)[0];
				green.at<uchar>(i, j) = src.at< Vec3b>(i, j)[1];
			}
		}

		imshow("input image", src);
		imshow("gray image", dst);
		imshow("red image", red);
		imshow("blue image", blue);
		imshow("green image", green);
		waitKey();

		return dst;
	}
}

Mat from8UC1ToBinary(Mat src, float threshold)
{
	int height = src.rows;
	int width = src.cols;
	Mat dst = Mat(height, width, CV_8UC1);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (src.at<uchar>(i, j) < threshold)
			{
				dst.at<uchar>(i, j) = 0;
			}
			else
			{
				dst.at<uchar>(i, j) = 255;
			}
		}
	}

	imshow("input image", src);
	imshow("gray image", dst);
	waitKey();

	return dst;
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

	imshow("input image", src);
	imshow("hue image", hue_dst);
	imshow("saturation image", saturation_dst);
	imshow("value image", value_dst);
	return hue_dst;
}

/// extra exercises

void measureRed(Mat src, float threshold)
{
	Mat src1 = fromRGBToHSV(src);
	int height = src1.rows;
	int width = src1.cols;
	Mat final = Mat(height, width, CV_8UC1);

	float Do, Dr, Drc, Drcn;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Do = 255 - src1.at<uchar>(i, j);
			Dr = min(src1.at<uchar>(i, j), Do);

			if (Dr < threshold)
			{
				Drc = threshold - Dr;
			}
			else
			{
				Drc = 0;
			}

			Drcn = (float)Drc * 255 / 30;

			if (saturation_dst.at<uchar>(i, j) > 150)
			{
				final.at<uchar>(i, j) = Drcn;
			}
			else
			{
				final.at<uchar>(i, j) = 0;
			}
		}
	}

	imshow("input image", src);
	imshow("redness", final);
	waitKey();
}

/// -------------------------------------------------------------------- LAB 3 -----------------------------------------

//check if the value at position k is the local maximum
boolean MaxLocal(float histo[], int k)
{
	for (int i = k - WH; i <= k + WH; i++)
	{
		if (histo[i] > histo[k])
		{
			return false;
		}
	}
	return true;
}

// the average value of the histogram
float averageHisto(float histo[], int k)
{
	float sum = 0;

	for (int i = k - WH; i <= k + WH; i++)
	{
		sum += histo[i];
	}

	float average = sum / (2 * WH + 1);

	return average;
}

// build an array -> add +1 to it from an image, then normalize it 
void buildHistogramFromMat(Mat src, int histo[256], float histoNormalized[256])
{
	int height = src.rows;
	int width = src.cols;

	for (int i = 0; i < 256; i++)
	{
		histo[i] = 0;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			histo[src.at<uchar>(i, j)]++;
		}
	}

	showHistogram("Histo", histo, 256, 256);

	// Normalized histogram
	for (int i = 0; i < 256; i++)
	{
		histoNormalized[i] = (float)histo[i] / (width*height);
	}
}

void HistogramMultilevelAndFloyd(Mat src)
{
	int histo[256];
	float histoNormalized[256];
	int final[256];
	int *lookaheadArray;

	lookaheadArray = (int*)malloc(sizeof(int) * 256);

	int height = src.rows;
	int width = src.cols;
	int max = -1;
	float sum, average;

	Mat dst = Mat(height, width, CV_8UC1);

	buildHistogramFromMat(src, histo, histoNormalized);

	for (int i = 0; i < 256; i++)
	{
		final[i] = 0;
	}

	for (int k = WH; k < 255 - WH; k++)
	{
		if ((histoNormalized[k] > averageHisto(histoNormalized, k) + TH) && MaxLocal(histoNormalized, k))
		{
			final[k] = histo[k];
		}

	}

	final[0] = 1;
	final[255] = 255;
	showHistogram("Histogram2", final, 256, 256);

	CreateLookAheadArray(final, lookaheadArray);

	for (int i = 0; i < 256; i++)
	{
		printf("%d ", lookaheadArray[i]);
	}

	/// Multilevel thresholding

	Mat multilevel = src.clone();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			uchar old = multilevel.at<uchar>(i, j);
			uchar newPixel = lookaheadArray[old];

			multilevel.at<uchar>(i, j) = newPixel;
		}
	}

	imshow("RESULT multilevel", multilevel);


	//// Floyd
	int error;

	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			uchar old = src.at<uchar>(i, j);
			uchar newPixel = lookaheadArray[old];

			src.at<uchar>(i, j) = newPixel;

			error = old - newPixel;

			int res = src.at<uchar>(i + 1, j) + 7 * error / 16;
			if (res > 255)
				src.at<uchar>(i + 1, j) = 255;
			else if (res < 0)
				src.at<uchar>(i + 1, j) = 0;
			else
				src.at<uchar>(i + 1, j) = res;

			res = src.at<uchar>(i - 1, j + 1) + 3 * error / 16;
			if (res > 255)
				src.at<uchar>(i - 1, j + 1) = 255;
			else if (res < 0)
				src.at<uchar>(i - 1, j + 1) = 0;
			else
				src.at<uchar>(i - 1, j + 1) = res;

			res = src.at<uchar>(i, j + 1) + 5 * error / 16;
			if (res > 255)
				src.at<uchar>(i, j + 1) = 255;
			else if (res < 0)
				src.at<uchar>(i, j + 1) = 0;
			else
				src.at<uchar>(i, j + 1) = res;

			res = src.at<uchar>(i + 1, j + 1) + error / 16;
			if (res > 255)
				src.at<uchar>(i + 1, j + 1) = 255;
			else if (res < 0)
				src.at<uchar>(i + 1, j + 1) = 0;
			else
				src.at<uchar>(i + 1, j + 1) = res;
		}
	}

	imshow("DST", src);

	waitKey();
}

void CreateLookAheadArray(int histo[], int *dst)
{
	int src[256];

	for (int i = 0; i < 256; i++)
	{
		if (histo[i] != 0)
		{
			src[i] = i;
		}
		else
		{
			src[i] = -1;
		}
	}

	boolean found = true;
	for (int j = 0; j < 256; j++)
	{
		dst[j] = src[j];
	}

	while (found)
	{
		found = false;

		for (int i = 1; i < 255; i++)
		{
			if (src[i - 1] > -1 && src[i] == -1)
			{
				found = true;
				dst[i - 1] = src[i - 1];
				dst[i] = src[i - 1];
			}
			else if (src[i + 1] > -1 && src[i] == -1)
			{
				found = true;
				dst[i + 1] = src[i + 1];
				dst[i] = src[i + 1];
			}
		}
		for (int j = 0; j < 256; j++)
		{
			src[j] = dst[j];
		}
	}
}

void computeHistogramBins(Mat src, int *hist, int size, int numberOfBins)
{
	for (int i = 0; i < size / numberOfBins; i++)
	{
		hist[i] = 0;
	}

	int height = src.rows;
	int width = src.cols;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			uchar v = src.at<uchar>(i, j);
			hist[v / numberOfBins]++;
		}
	}
}

void multilevelThresoldingToColorImage(Mat src)
{
	int height = src.rows;
	int width = src.cols;

	Mat aux = src.clone();
	Mat dst = Mat(height, width, CV_8UC3);

	fromRGBToHSV(src);


	int histo[256];
	float histoNormalized[256];
	int final[256];
	int *lookaheadArray;

	lookaheadArray = (int*)malloc(sizeof(int) * 256);

	buildHistogramFromMat(hue_dst, histo, histoNormalized);

	for (int i = 0; i < 256; i++)
	{
		final[i] = 0;
	}

	for (int k = WH; k < 255 - WH; k++)
	{
		if ((histoNormalized[k] > averageHisto(histoNormalized, k) + TH) && MaxLocal(histoNormalized, k))
		{
			final[k] = histo[k];
		}

	}

	final[0] = 1;
	final[255] = 255;
	//showHistogram("Histogram2", final, 256, 256);

	CreateLookAheadArray(final, lookaheadArray);

	/// Multilevel thresholding

	Mat multilevel = hue_dst.clone();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			uchar old = multilevel.at<uchar>(i, j);
			uchar newPixel = lookaheadArray[old];

			multilevel.at<uchar>(i, j) = newPixel;
		}
	}

	Mat newConvertionImage[] = { multilevel, saturation_dst, value_dst };
	Mat newImage(height, width, CV_8UC3);
	merge(newConvertionImage, 3, newImage);
	cvtColor(newImage, dst, CV_HSV2BGR);
	imshow("New Image", dst);
	waitKey(0);
}

/// ------------------------------------------------------ LAB 4 ---------------------------------------------------------
void functionI(Mat src, Mat mat)
{
	int height = src.rows;
	int width = src.cols;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			if (src.at<uchar>(i, j) != 0)
			{
				mat.at<uchar>(i, j) = 1;
			}
			else
			{
				mat.at<uchar>(i, j) = 0;
			}
		}
}

void findArea(Mat mat, int rows, int cols, double *area)
{
	*area = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			(*area) += mat.at<uchar>(i, j);
		}
	}
}

void centerOfMass(Mat matrix1, int rows, int cols, double *r, double *c, double area)
{
	double raux = 0;
	double caux = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			raux += i*matrix1.at<uchar>(i, j);
			caux += j*matrix1.at<uchar>(i, j);
		}
	}
	*r = raux / area;
	*c = caux / area;
}

void axisOfElongation(Mat matrix1, int rows, int cols, double ri, double ci, double *phi)
{
	double denominator = 0, nominator1 = 0, nominator2 = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			denominator += (i - ri)*(j - ci)*matrix1.at<uchar>(i, j);
			nominator1 += (j - ci)*(j - ci)*matrix1.at<uchar>(i, j);
			nominator2 += (i - ri)*(i - ri)*matrix1.at<uchar>(i, j);;
		}
	}

	*phi = 0.5 * atan2(2 * denominator, nominator1 - nominator2);
}

void calculatePerimeter(Mat img, Mat dst, Mat matrix1, int rows, int cols, double r, double c, double phi, double *perimeter)
{
	*perimeter = 0;

	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (matrix1.at<uchar>(i, j) == 0 && (matrix1.at<uchar>(i, j + 1) == 1 || matrix1.at<uchar>(i, j - 1) == 1
				|| matrix1.at<uchar>(i + 1, j) == 1 || matrix1.at<uchar>(i + 1, j - 1) == 1
				|| matrix1.at<uchar>(i + 1, j + 1) == 1 || matrix1.at<uchar>(i + 1, j - 1) == 1
				|| matrix1.at<uchar>(i - 1, j + 1) == 1 || matrix1.at<uchar>(i - 1, j - 1) == 1)) {
				(*perimeter) += 1;
				dst.at<uchar>(i, j) = 128;
			}
			else {
				dst.at<uchar>(i, j) = 255;
			}
		}
	}

	Point rplus = Point(c, r + 2);
	Point rminus = Point(c, r - 2);
	Point cplus = Point(c + 2, r);
	Point cminus = Point(c - 2, r);
	line(dst, rplus, rminus, 128, 1, 8, 0);
	line(dst, cplus, cminus, 128, 1, 8, 0);

	double len = 80;
	Point pdown = Point(c + len*cos(phi), r + len*sin(phi));
	Point pup = Point(c - len * cos(phi), r - len*sin(phi));
	line(dst, pdown, pup, 128, 1, 8, 0);


	int cmin = 1000, cmax = -1, rmin = 1000, rmax = -1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix1.at<uchar>(i, j) == 1) {
				if (i > rmax)
					rmax = i;
				if (j > cmax)
					cmax = j;
				if (i < rmin)
					rmin = i;
				if (j < cmin)
					cmin = j;
			}
		}
	}
	rectangle(dst, Point(cmin, rmin), Point(cmax, rmax), 128, 1, 8, 0);
}

void projection(Mat matI, int rows, int cols)
{
	int *h = new int[rows];
	int *v = new int[cols];

	for (int i = 0; i < rows; i++) {
		v[i] = 0;
		for (int j = 0; j < cols; j++) {
			if (matI.at<uchar>(i, j) == 1) {
				v[i] += matI.at<uchar>(i, j);
			}

		}
	}

	for (int i = 0; i < cols; i++) {
		h[i] = 0;
		for (int j = 0; j < rows; j++) {
			if (matI.at<uchar>(j, i) == 1) {
				h[i] += matI.at<uchar>(j, i);
			}
		}
	}

	showHistogram("V Histogram Vertical", v, cols, rows);
	showHistogram("H Histogram Horizontal", h, cols, rows);
}

void findThinnessRation(double area, double perim, double *t)
{
	*t = 4 * PI*(area / (perim*perim));
}

void onMouse(int event, int x, int y, int flags, void* param)
{
	Mat* src = (Mat*)param;
	Mat dst = Mat(src->rows, src->cols, CV_8UC1);

	Mat binary = Mat(src->rows, src->cols, CV_8UC1);

	double area, r, c, phi, perimeter, thiness;
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		printf("Pos(x,y): %d,%d\n", x, y);


		for (int i = 0; i < src->rows; i++)
			for (int j = 0; j < src->cols; j++)
			{
				if (src->at<Vec3b>(i, j) == src->at<Vec3b>(y, x))
				{
					binary.at<uchar>(i, j) = 1;
				}
				else
				{
					binary.at<uchar>(i, j) = 0;
				}
			}

		imshow("Binary", binary * 255);

		findArea(binary, src->rows, src->cols, &area);

		std::cout << "Area is: ";
		std::cout << area;
		std::cout << "\n";

		centerOfMass(binary, src->rows, src->cols, &r, &c, area);

		std::cout << "Center of mass is: ";
		std::cout << r << " " << c;
		std::cout << "\n";

		axisOfElongation(binary, src->rows, src->cols, r, c, &phi);

		std::cout << "Axis of elongation is: ";
		std::cout << phi;
		std::cout << "\n";

		Point p_start = Point(c - 200 * cos(phi), r - 200 * sin(phi));
		Point p_end = Point(c + 200 * cos(phi), r + 200 * sin(phi));

		line(*src, p_start, p_end, 150, 3);

		imshow("Image with axis", *src);

		calculatePerimeter(*src, dst, binary, src->rows, src->cols, r, c, phi, &perimeter);

		std::cout << "Perimeter is: ";
		std::cout << perimeter;
		std::cout << "\n";

		projection(binary, src->rows, src->cols);

		findThinnessRation(area, perimeter, &thiness);

		std::cout << "Thiness is: \n";
		std::cout << thiness;
	}
}

boolean visitedColor(Vec3b visited[256], Vec3b color)
{
	for (int i = 0; i < 256; i++)
	{
		if (visited[i] == color)
		{
			return true;
		}
	}

	return false;
}

void allObjects(Mat src, int TH_area, int phi_LOW, int phi_HIGH)
{
	Mat objects[100];
	int height = src.rows;
	int width = src.cols;
	float areaObjects[100];
	int contor = 0;
	double area, phi, r, c;
	float phiObjects[100];
	Vec3b visited[256];

	for (int i = 0; i < 256; i++)
	{
		visited[i] = 0;
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// sa fie diferita si sa nu mai existe deja
			// functie sa verificam sa nu mai existe deja in matrice
			if (src.at<Vec3b>(i, j) != Vec3b(255, 255, 255))
			{
				Mat binary = Mat(height, width, CV_8UC1);
				Vec3b aux = src.at<Vec3b>(i, j);

				if (!(visitedColor(visited, aux)))
				{
					visited[contor] = aux;
					for (int k = 0; k < height; k++)
					{
						for (int m = 0; m < width; m++)
						{
							if (src.at<Vec3b>(k, m) == aux)
							{
								binary.at<uchar>(k, m) = 1;
							}
							else
							{
								binary.at<uchar>(k, m) = 0;
							}
						}
					}

					objects[contor] = binary.clone();
					findArea(binary, height, width, &area);

					centerOfMass(binary, height, width, &r, &c, area);
					axisOfElongation(binary, height, width, r, c, &phi);

					areaObjects[contor] = area;
					phiObjects[contor] = phi;
					contor++;
				}
			}
		}
	}


	printf("Number of objects: %d\n", contor);

	for (int i = 0; i < contor; i++)
	{
		printf("%d %d %d\n", visited[i][0], visited[i][1], visited[i][2]);
	}

	for (int i = 0; i < contor; i++)
	{
		if (areaObjects[i] > TH_area)
		{
			imshow("First", objects[i]);
		}
	}


	for (int i = 0; i < contor; i++)
	{
		if (phiObjects[i] > phi_LOW && phiObjects[i] < phi_HIGH)
		{
			//imshow("First %d" + i, objects[i]);
		}
	}
}

/// ----------------------------------------------------- LAB 5 --------------------------------------------------------

boolean testInside(int x, int y, int rows, int cols)
{
	if (x <= 0 || x > cols)
	{
		return false;
	}
	if (y <= 0 || y > rows)
	{
		return false;
	}

	return true;
}

void Labelling1(Mat src, Mat result)
{
	int dx[]{ 0,0,-1,1,1,1,-1,-1 };
	int dy[]{ -1,1,0,0,1,-1,1,-1 };
	int label = 0;
	Mat labels = Mat::zeros(src.rows, src.cols, CV_32SC1);
	int height = src.rows;
	int width = src.cols;

	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if ((src.at<uchar>(i, j) == 0) && (labels.at<int32_t>(i, j) == 0))
			{
				label++;
				std::queue<Point2i> Q;
				labels.at<int32_t>(i, j) = label;
				Q.push({ j,i });
				while (!Q.empty())
				{
					Point2i q = Q.front();
					Q.pop();

					for (int k = 0; k < 8; k++)
					{
						int x = q.x + dx[k];
						int y = q.y + dy[k];
						if (testInside(x, y, height - 1, width - 1))
						{
							if ((src.at<uchar>(y, x) == 0) && (labels.at<int32_t>(y, x) == 0))
							{
								labels.at<int32_t>(y, x) = label;
								Q.push({ x,y });
							}
						}
					}
				}
			}
		}
	}

	Vec3b pallete[256];
	pallete[0] = Vec3b(255, 255, 255);

	for (int i = 1; i < 256; i++)
	{
		pallete[i][0] = rand() % 256;
		pallete[i][1] = rand() % 256;
		pallete[i][2] = rand() % 256;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			result.at<Vec3b>(i, j) = pallete[labels.at<int>(i, j)];
		}
	}
}

void Labelling1Call(Mat source)
{
	Mat result = Mat(source.rows, source.cols, CV_8UC3);
	int neigh;

	Labelling1(source, result);

	imshow("input", source);
	imshow("result", result);

	waitKey(0);
}

int minimVector(std::vector<int> L)
{
	int min = INT_MAX;
	for (int i = 0; i < L.size(); i++)
	{
		if (L[i] < min)
		{
			min = L[i];
		}
	}
	return min;
}

void Labelling2(Mat src, Mat result)
{
	int dx[]{ -1,-1,-1,0 };
	int dy[]{ 0,-1,1,-1 };
	int label = 0;
	int newLabel = 0;
	int *newLabels;
	Mat labels = Mat::zeros(src.rows, src.cols, CV_32SC1);
	int height = src.rows;
	int width = src.cols;
	std::vector<std::vector<int>> edges;
	std::vector<int> L;
	//ensure that edges has the proper size

	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if ((src.at<uchar>(i, j) == 0) && (labels.at<int32_t>(i, j) == 0))
			{
				L = std::vector<int>();
				for (int k = 0; k < 4; k++)
				{
					int x = i + dx[k];
					int y = j + dy[k];
					if (testInside(x, y, height - 1, width - 1))
					{
						if (labels.at<int>(x, y) > 0)
						{
							L.push_back(labels.at<int>(x, y));
						}
					}
				}

				if (L.size() == 0)
				{
					label++;
					labels.at<int>(i, j) = label;
					edges.resize(label + 1);
				}
				else
				{
					int x = minimVector(L);
					labels.at<int>(i, j) = x;
					for (int e = 0; e < L.size(); e++)
					{
						if (L[e] != x)
						{
							edges[x].push_back(L[e]);
							edges[L[e]].push_back(x);
						}
					}

				}
			}
		}
	}

	Vec3b pallete[256];
	pallete[0] = Vec3b(255, 255, 255);

	for (int i = 1; i < 256; i++)
	{
		pallete[i][0] = rand() % 256;
		pallete[i][1] = rand() % 256;
		pallete[i][2] = rand() % 256;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			result.at<Vec3b>(i, j) = pallete[labels.at<int>(i, j)];
		}
	}

	imshow("Partial", result);

	newLabels = new int[label + 1];

	memset(newLabels, 0, (label + 1) * sizeof(int));

	for (int i = 1; i <= label; i++)
	{
		if (newLabels[i] == 0)
		{
			newLabel++;
			std::queue<int> Q;
			newLabels[i] = newLabel;
			Q.push(i);

			while (!Q.empty())
			{
				int q = Q.front();
				Q.pop();

				for (int l = 0; l < edges[q].size(); l++)
				{
					//value from egdes[q][l]
					if (newLabels[edges[q][l]] == 0)
					{
						newLabels[edges[q][l]] = newLabel;
						Q.push(edges[q][l]);
					}
				}
			}

		}
	}


	for (int i = 0; i < height - 1; i++)
	{
		for (int j = 0; j < width - 1; j++)
		{
			labels.at<int>(i, j) = newLabels[labels.at<int>(i, j)];
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			result.at<Vec3b>(i, j) = pallete[labels.at<int>(i, j)];
		}
	}
}

void Labelling2Call(Mat source)
{
	Mat result = Mat(source.rows, source.cols, CV_8UC3);
	int neigh;

	Labelling2(source, result);

	imshow("input", source);
	imshow("result", result);

	waitKey(0);
}

/// ------------------------------------------------------- LAB 6 -------------------------------------------------------

void reconstructFromChainCode(int *arrayGiven, int N, Mat src)
{
	Mat newMat = Mat(src.rows, src.rows, CV_8UC1);

	int height = src.rows;
	int width = src.cols;
	int dirOld, dirNew;

	int di[] = { 0, -1, -1, -1, 0, 1, 1,1 };
	int dj[] = { 1,1,0,-1,-1,-1, 0,1 };

	int P0i, P0j;

	// make the destination white
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			newMat.at<uchar>(i, j) = 255;
		}
	}

	P0i = 100;
	P0j = 100;

	for (int i = 0; i < N; i++)
	{
		P0i += di[arrayGiven[i]];
		P0j += dj[arrayGiven[i]];

		if (P0i > 0 && P0j > 0)
		{
			newMat.at<uchar>(P0i, P0j) = 0;
		}
	}
	imshow("res1", newMat);
}

void reconstructFromDerivative(int *arrayGiven, int N, Mat src)
{
	Mat newMat = Mat(src.rows, src.rows, CV_8UC1);

	int height = src.rows;
	int width = src.cols;
	int dirOld, dirNew;

	int di[] = { 0, -1, -1, -1, 0, 1, 1,1 };
	int dj[] = { 1,1,0,-1,-1,-1, 0,1 };

	int P0i, P0j;

	// make the destination white
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			newMat.at<uchar>(i, j) = 255;
		}
	}

	P0i = 100;
	P0j = 100;
	dirOld = 0;

	for (int i = 0; i < N; i++)
	{
		dirOld = (dirOld + arrayGiven[i]) % 8;
		P0i += di[dirOld];
		P0j += dj[dirOld];

		if (P0i > 0 && P0j > 0)
		{
			newMat.at<uchar>(P0i, P0j) = 0;
		}
	}
	imshow("res2", newMat);
}

void BorderTracing(Mat src)
{
	Mat dst = Mat(src.rows, src.cols, CV_8UC1);
	int height = src.rows;
	int width = src.cols;
	int dirOld, dirNew;

	int di[] = { 0, -1, -1, -1, 0, 1, 1,1 };
	int dj[] = { 1,1,0,-1,-1,-1, 0,1 };

	int P0i, P0j, P1j, P1i, Poldi, Poldj, Pnewj, Pnewi;

	// 8 - connectivity
	dirOld = 7;
	int chainCode[1000];

	int contor = 0;
	int i, j;

	// make the destination white
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			dst.at<uchar>(i, j) = 255;
		}
	}

	//find the first object point
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (src.at<uchar>(i, j) == 0)
			{
				P0i = i;
				P0j = j;
				break;
			}
		}
	}

	// P old is P0
	Poldi = P0i;
	Poldj = P0j;

	do {
		if (dirOld % 2 == 0)
		{
			dirNew = (dirOld + 7) % 8;
		}
		else
		{
			dirNew = (dirOld + 6) % 8;
		}

		dirOld = dirNew;

		while (src.at<uchar>(Poldi + di[dirOld], Poldj + dj[dirOld]) != 0)
		{
			dirOld = (dirOld + 1) % 8;
		}

		if (contor == 0) {
			P1i = Poldi;
			P1j = Poldj;
		}

		dst.at<uchar>(Poldi + di[dirOld], Poldj + dj[dirOld]) = 0;

		Pnewi = Poldi + di[dirOld];
		Pnewj = Poldj + dj[dirOld];

		chainCode[contor] = dirOld;
		contor++;
		Poldi = Pnewi;
		Poldj = Pnewj;

	} while (P1i != Pnewi || P1j != Pnewj || P0i != Poldi || P0j != Poldj);

	imshow("input", src);
	imshow("result", dst);

	//the arrayGiven based on the chain code
	int *derivative = (int *)malloc(sizeof(int) *contor);

	printf("Chain code:\n");
	for (i = 0; i < contor; i++)
	{
		printf("%d ", chainCode[i]);
	}
	printf("Derivative:\n");
	for (i = 0; i < contor - 1; i++)
	{
		derivative[i] = (chainCode[i + 1] - chainCode[i] + 8) % 8;
		printf("%d ", derivative[i]);
	}

	reconstructFromChainCode(chainCode, contor, src);
	reconstructFromDerivative(derivative, contor, src);

	waitKey(0);
}

/// ---------------------------------------------------------------- LAB 7 ---------------------------------------------

void dilation2(Mat src, Mat *dst, Mat M);
void erosion2(Mat src, Mat *dst, Mat M);

void dilation(Mat src, Mat dst)
{
	int height = src.rows;
	int width = src.cols;
	imshow("original", src);

	int di[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
	int dj[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if (src.at<uchar>(i, j) == 0)
			{
				for (int k = 0; k < 8; k++)
				{
					dst.at<uchar>(i + di[k], j + dj[k]) = 0;
				}
			}
		}
	}

	imshow("dilation", dst);
	waitKey(0);
}

void erosion(Mat src, Mat dst)
{
	int height = src.rows;
	int width = src.cols;
	imshow("first", src);

	int di[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
	int dj[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			dst.at<uchar>(i, j) = 255;
		}
	}

	for (int k = 0; k < 8; k++)
	{
		for (int i = 1; i < height - 1; i++)
		{
			for (int j = 1; j < width - 1; j++)
			{
				if (src.at<uchar>(i, j) == 0)
				{
					if (src.at<uchar>(i - 1, j) == 0 &&
						src.at<uchar>(i, j - 1) == 0 &&
						src.at<uchar>(i + 1, j) == 0 &&
						src.at<uchar>(i, j + 1) == 0)
					{

						dst.at<uchar>(i, j) = 0;
					}
				}
			}
		}
	}
	imshow("erosion", dst);
	waitKey(0);
}

void opening(Mat src, Mat M)
{
	Mat dst = src.clone();

	erosion2(src, &dst, M);
	imshow("temp", dst);

	Mat dst2 = dst.clone();

	dilation2(dst, &dst2, M);
	imshow("opening", dst2);
	waitKey(0);
}

void closing(Mat src, Mat M)
{
	Mat dst = src.clone();

	dilation2(src, &dst, M);

	Mat dst2 = dst.clone();

	erosion2(dst, &dst2, M);

	imshow("closing", dst2);
	waitKey(0);
}

void boundaryExtraction(Mat src, Mat *dst, Mat M)
{
	int width = src.cols;
	int height = src.rows;
	erosion2(src, dst, M);
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

	imshow("Boundary", dst2);
	waitKey();
}

void dilation2(Mat src, Mat *dst, Mat M)
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
	//waitKey(0);
}

void erosion2(Mat src, Mat *dst, Mat M)
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
	//waitKey(0);
}

void MultipleTransformations(Mat src, int n, Mat M)
{
	Mat tmp = src.clone();
	Mat dst = src.clone();

	for (int i = 0; i < n; i++)
	{
		erosion2(tmp, &dst, M);
		//dilation2
		tmp = dst.clone();
	}

	imshow("Result", dst);
	waitKey(0);
}

void regionFilling(Mat src, Mat *dst, Mat M)
{
	Mat Acomplementar = Mat(src.rows, src.cols, CV_8UC1);
	Mat temp = Mat(src.rows, src.cols, CV_8UC1);

	int x, y;
	boolean found = false;
	boolean changed = true;

	Mat X0 = Mat(src.rows, src.cols, CV_8UC1);

	// calculate the complementary matrix of the src
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			X0.at<uchar>(i, j) = BACKGROUND;
			temp.at<uchar>(i, j) = BACKGROUND;
			if (src.at<uchar>(i, j) == OBJECT)
			{
				x = i;
				y = j;
				Acomplementar.at<uchar>(i, j) = BACKGROUND;
			}
			else
			{
				Acomplementar.at<uchar>(i, j) = OBJECT;
				if (found == false)
				{
					x = i;
					y = j;
					found = true;
				}
			}
		}
	}

	while (changed)
	{
		//dilation2(X0, &temp, M);
		// cam mai bine modific dilation
		//fata de xk-i  am adaugat un punct nou -> marcam ca e changed; daca nu mai avem o schimbare, clar am ajuns la aceeasi valoare

	}

	imshow("Complement", Acomplementar);
	waitKey(0);
}

///---------------------------------------------------- LAB 8 -----------------------------------------------------------

float meanValue(Mat src)
{
	int height = src.rows;
	int width = src.cols;
	int M = height * width;

	float meanValue = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			meanValue = meanValue + src.at<uchar>(i, j);
		}
	}

	meanValue = meanValue / M;

	std::cout << "Mean value is " << meanValue << "\n";

	return meanValue;
}

float standardDeviation(Mat src)
{
	int height = src.rows;
	int width = src.cols;
	int M = height * width;

	float meanVal = meanValue(src);
	float standardDeviation = 0;


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			standardDeviation += pow((src.at<uchar>(i, j) - meanVal), 2);
		}
	}

	standardDeviation = sqrt(standardDeviation / M);

	std::cout << "Standard deviation is " << standardDeviation << "\n";

	return standardDeviation;
}

void HistogramEqualization(Mat src, float probability[256])
{
	int height = src.rows;
	int width = src.cols;
	int M = height * width;
	int histo[256];
	float cumulativeHistogram[256];
	int equalizeHistogram[256];
	Mat dst = Mat(src.rows, src.cols, CV_8UC1);

	imshow("source", src);

	float meanVal = meanValue(src);
	float standardDev = standardDeviation(src);

	//with histogram

	buildHistogramFromMat(src, histo, probability);

	// Equalize histogram

	cumulativeHistogram[0] = probability[0];

	for (int i = 1; i < 256; i++)
	{
		cumulativeHistogram[i] = probability[i] + cumulativeHistogram[i - 1];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			dst.at<uchar>(i, j) = cumulativeHistogram[src.at<uchar>(i, j)] * 255;
		}
	}

	imshow("See equalized image", dst);

	waitKey();
}

void globalThresoldingAlgorithm(Mat src)
{
	int histo[256];
	float probability[256];
	int height = src.rows;
	int width = src.cols;
	int IMax = INT_MIN, IMin = INT_MAX;
	int Thresold;
	float error = 0.1f;
	int lastThreshold = 0;
	int N1 = 0, N2 = 0;

	imshow("Original image", src);

	Mat dst = Mat(height, width, CV_8UC1);

	float mean1 = 0, mean2 = 0;

	buildHistogramFromMat(src, histo, probability);

	//calculate Imax and Imin from the image
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (src.at<uchar>(i, j) > IMax)
			{
				IMax = src.at<uchar>(i, j);
			}
			if (src.at<uchar>(i, j) < IMin)
			{
				IMin = src.at<uchar>(i, j);
			}
		}
	}

	Thresold = (IMax + IMin) / 2; //can be initialized with mean (miu)

	while ((Thresold - lastThreshold) >= error) {
		N1 = 0;
		N2 = 0;
		mean1 = 0;
		mean2 = 0;

		for (int i = IMin; i <= Thresold; i++)
		{
			N1 = N1 + histo[i];
		}

		for (int i = Thresold + 1; i <= IMax; i++)
		{
			N2 = N2 + histo[i];
		}

		for (int i = IMin; i <= Thresold; i++)
		{
			mean1 += (i * histo[i]);
		}

		mean1 = mean1 / N1;

		for (int i = Thresold + 1; i <= IMax; i++)
		{
			mean2 += (i * histo[i]);
		}

		mean2 = mean2 / N2;

		lastThreshold = Thresold;
		Thresold = (int)(mean1 + mean2) / 2;
	}

	printf("Thresold value: %d\n", Thresold);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (src.at<uchar>(i, j) < Thresold)
			{
				dst.at<uchar>(i, j) = 0;
			}
			else
			{
				dst.at<uchar>(i, j) = 255;
			}
		}
	}

	imshow("Result", dst);
	waitKey();
}

void histogramStrechingShrinking(Mat src, float deltaMean, float deltaDeviation)
{
	int histo[256];
	float probability[256];
	int height = src.rows;
	int width = src.cols;

	float gmin = 0, gmax = 0, gminPrim = 0, gmaxPrim = 0;
	float meanPrim = 0, meanInter = 0, deviationPrim = 0, deviationInter = 0;

	imshow("First image", src);

	Mat dst = Mat(height, width, CV_8UC1);

	buildHistogramFromMat(src, histo, probability);

	meanInter = meanValue(src);
	deviationInter = standardDeviation(src);

	meanPrim = meanInter + deltaMean;
	deviationPrim = deviationInter + deltaDeviation;

	gmin = meanInter - deviationInter;
	gmax = meanInter + deviationInter;

	gminPrim = meanPrim - deviationPrim;
	gmaxPrim = meanPrim + deviationPrim;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int val = (int)gminPrim + (gmaxPrim - gminPrim) / (gmax - gmin) * (src.at<uchar>(i, j) - gmin);
			if (val < 0)
			{
				dst.at<uchar>(i, j) = 0;
			}
			else {
				if (val > 255)
				{
					dst.at<uchar>(i, j) = 255;
				}
				else
				{
					dst.at<uchar>(i, j) = val;
				}
			}
		}
	}

	imshow("Resultat", dst);
	waitKey();
}

void gammaCorrection(Mat src, int gamma)
{
	int height = src.rows;
	int width = src.cols;
	imshow("First image", src);

	Mat dst = Mat(height, width, CV_8UC1);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int val = (uchar)255 * pow((src.at<uchar>(i, j) / (float)255), gamma);
			if (val < 0)
			{
				dst.at<uchar>(i, j) = 0;
			}
			else {
				if (val > 255)
				{
					dst.at<uchar>(i, j) = 255;
				}
				else
				{
					dst.at<uchar>(i, j) = val;
				}
			}
		}
	}

	imshow("Result gamma", dst);
	waitKey();
}

/// ------------------------------------------------------- LAB 9 -------------------------------------------------------
void lowPassFiltering(Mat src, Mat kernel, Mat *dst)
{
	int aux;
	int height = src.rows;
	int width = src.cols;
	int sum = 0;

	for (int i = 0; i < kernel.rows; i++)
	{
		for (int j = 0; j < kernel.cols; j++)
		{
			sum += kernel.at<uchar>(i, j);
		}
	}
	printf("Sum %d\n", sum);

	for (int u = kernel.rows; u < height - kernel.rows; u++)
	{
		for (int v = kernel.cols; v < width - kernel.cols; v++)
		{
			aux = 0;
			for (int m = 0; m < kernel.rows; m++)
			{
				for (int n = 0; n < kernel.cols; n++)
				{
					aux += (kernel.at<uchar>(m, n) * src.at<uchar>(u + m - 1, v + n - 1));
				}
			}
			(*dst).at<uchar>(u, v) = (int)aux / sum;
		}
	}

	imshow("Low pass filter", *dst);
	waitKey();
}

void highPassFilter(Mat src, Mat kernel, Mat *dst)
{
	int aux;
	int height = src.rows;
	int width = src.cols;

	for (int u = kernel.rows; u < height - kernel.rows; u++)
	{
		for (int v = kernel.cols; v < width - kernel.cols; v++)
		{
			aux = 0;
			for (int m = 0; m < kernel.rows; m++)
			{
				for (int n = 0; n < kernel.cols; n++)
				{
					aux += (kernel.at<int>(m, n) * src.at<uchar>(u + m - 1, v + n - 1));
				}
			}
			aux = aux + 128;
			if (aux > 255)
			{
				aux = BACKGROUND;
			}
			if (aux < 0)
			{
				aux = OBJECT;
			}
			(*dst).at<uchar>(u, v) = aux;
		}
	}

	imshow("High Pass Filter", *dst);
	waitKey();
}

void centering_transform(Mat img)
{
	//expects floating point image
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			img.at<float>(i, j) = ((i + j) & 1) ? -img.at<float>(i, j) : img.at<float>(i, j);
		}
	}
}

Mat generic_frequency_domain_filter(Mat src, int filter, int R)
{
	int height = src.rows;
	int width = src.cols;
	float maxim = FLT_MIN;

	//convert input image to float image
	Mat srcf;
	src.convertTo(srcf, CV_32FC1);

	//centering transformation
	centering_transform(srcf);

	//perform forward transform with complex image output
	Mat fourier;

	dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

	//split into real and imaginary channels
	Mat channels[] = { Mat::zeros(src.size(), CV_32F), Mat::zeros(src.size(), CV_32F) };
	split(fourier, channels); // channels[0] = Re(DFT(I)), channels[1] = Im(DFT(I))
							  //calculate magnitude and phase in floating point images mag and phi
							  //store in real part in channels[0] and imaginary part in channels[1]
	Mat mag, phi;
	magnitude(channels[0], channels[1], mag);
	phase(channels[0], channels[1], phi);

	//display the phase and magnitude images here
	imshow("Magnitude", mag);
	imshow("Phase", phi);

	Mat LMag, outP;
	// Add 1 to the magnitude Matrix
	log(mag + 1, LMag);

	// get the maximum from LMag
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (maxim < LMag.at<float>(i, j))
			{
				maxim = LMag.at<float>(i, j);
			}
		}
	}


	Mat aux = Mat(height, width, CV_8UC1);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			aux.at<uchar>(i, j) = (int)255 * LMag.at<float>(i, j) / (float)maxim;
		}
	}
	imshow("After normalizing", aux);

	//insert filtering operations on Fourier coefficients here
	///  ( channels[0] = Re(DFT(I), channels[1] = Im(DFT(I) )
	///  0 is low pass
	if (filter == IDEAL_LOW_FILTER)
	{
		for (int u = 0; u < channels[0].rows; u++)
		{
			for (int v = 0; v < channels[0].cols; v++)
			{

				if (pow(channels[0].rows / 2 - u, 2) + pow(channels[0].cols / 2 - v, 2) > R*R)
				{
					channels[0].at<float>(u, v) = 0;
					channels[1].at<float>(u, v) = 0;
				}
			}
		}
	}
	if (filter == IDEAL_HIGH_FILTER)
	{
		for (int u = 0; u < channels[0].rows; u++)
		{
			for (int v = 0; v < channels[0].cols; v++)
			{
				if (pow(channels[0].rows / 2 - u, 2) + pow(channels[0].cols / 2 - v, 2) <= R*R)
				{
					channels[0].at<float>(u, v) = 0;
					channels[1].at<float>(u, v) = 0;
				}
			}
		}
	}
	// A is 1/standard deviation witch will be the same with the radius
	int A = R;
	if (filter == GAUSS_LOW_FILTER)
	{
		for (int u = 0; u < channels[0].rows; u++)
		{
			for (int v = 0; v < channels[0].cols; v++)
			{

				channels[0].at<float>(u, v) = channels[0].at<float>(u, v)*((exp(-(pow(LMag.rows / 2 - u, 2) + pow(LMag.cols / 2 - v, 2)) / (A*A))));
				channels[1].at<float>(u, v) = channels[1].at<float>(u, v)*((exp(-(pow(LMag.rows / 2 - u, 2) + pow(LMag.cols / 2 - v, 2)) / (A*A))));

			}
		}
	}

	if (filter == GAUSS_HIGH_FILTER)
	{
		for (int u = 0; u < channels[0].rows; u++)
		{
			for (int v = 0; v < channels[0].cols; v++)
			{
				channels[0].at<float>(u, v) = channels[0].at<float>(u, v)*(1 - (exp(-(pow(LMag.rows / 2 - u, 2) + pow(LMag.cols / 2 - v, 2)) / (A*A))));
				channels[1].at<float>(u, v) = channels[1].at<float>(u, v)*(1 - (exp(-(pow(LMag.rows / 2 - u, 2) + pow(LMag.cols / 2 - v, 2)) / (A*A))));

			}
		}
	}


	//perform inverse transform and put results in dstf
	Mat dst, dstf;
	merge(channels, 2, fourier);
	dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

	//inverse centering transformation
	centering_transform(dstf);

	//normalize the result and put in the destination image
	normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);
	imshow("My result", dst);

	waitKey();
	return dst;
}

///-------------------------------------------------------------- LAB 10 ------------------------------------------------------------

void timeComputationStart()
{
	t = (double)getTickCount(); // Get the current time [ms]
								// … Actual processing …
								// Get the current time again and compute the time difference [ms]
}

void timeComputationEnd()
{
	t = ((double)getTickCount() - t) / getTickFrequency();
	// Display (in the console window) the processing time in [ms]
	printf("Time = %.3f [ms]\n", t * 1000);
}

int MedianValue(int *aux, int n)
{
	int val;

	for (int i = 1; i < n - 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (aux[i] > aux[j])
			{
				val = aux[i];
				aux[i] = aux[j];
				aux[j] = val;
			}
		}
	}
	return aux[n / 2];
}

void MedianFilter(Mat src, Mat kernel, Mat *dst)
{
	int height = src.rows;
	int width = src.cols;
	int *aux;
	int sum = 0;
	int k = (kernel.rows) / 2;
	int val = 0;
	int median;

	aux = (int*)malloc(sizeof(int)* (kernel.rows * kernel.cols));

	for (int i = kernel.rows; i < height - kernel.rows; i++)
	{
		for (int j = kernel.cols; j < width - kernel.cols; j++)
		{
			val = 0;
			for (int p = 0; p < kernel.rows; p++)
			{
				for (int q = 0; q < kernel.cols; q++)
				{
					aux[val] = src.at<uchar>(i + p - k, j + q - k);
					val++;
				}
			}

			median = MedianValue(aux, kernel.rows * kernel.cols);
			dst->at<uchar>(i, j) = median;
		}
	}

	imshow("Clean", *dst);
	waitKey();
}

void GaussianFilter(Mat src, Mat *dst, float sigma)
{
	int height = src.rows;
	int width = src.cols;
	int aux;
	float sum = 0;
	int x0;

	timeComputationStart();
	int sizeKernel = (6 * sigma);
	if (sizeKernel % 2 == 0)
	{
		sizeKernel++;
	}

	Mat kernel = Mat(sizeKernel, sizeKernel, CV_32FC1);

	x0 = sizeKernel / 2;

	for (int i = 0; i < kernel.rows; i++)
	{
		for (int j = 0; j < kernel.cols; j++)
		{
			kernel.at<float>(i, j) = (1 / (2 * PI *pow(sigma, 2))) * exp(-((pow(i - x0, 2) + pow(j - x0, 2)) / (2 * pow(sigma, 2))));
			sum += kernel.at<float>(i, j);
		}
	}
	printf("%f ", sum);
	// filtering 
	for (int i = kernel.rows; i < height - kernel.rows; i++)
	{
		for (int j = kernel.cols; j < width - kernel.cols; j++)
		{
			aux = 0;
			for (int m = 0; m < kernel.rows; m++)
			{
				for (int n = 0; n < kernel.cols; n++)
				{
					aux += (kernel.at<float>(m, n) * src.at<uchar>(i + m - 1, j + n - 1));
				}
			}
			(*dst).at<uchar>(i, j) = aux;
		}
	}

	timeComputationEnd();
	imshow("Clean", *dst);
	waitKey();
}

// with 2 unidimensional filters
void GaussianFilterSecondOption(Mat src, Mat *dst, float sigma)
{
	int height = src.rows;
	int width = src.cols;
	int aux;
	int x0;
	float sum = 0;

	timeComputationStart();
	int sizeKernel = (6 * sigma);
	if (sizeKernel % 2 == 0)
	{
		sizeKernel++;
	}

	float *G1 = (float *)malloc(sizeof(float)* sizeKernel);
	float *G2 = (float *)malloc(sizeof(float)* sizeKernel);

	x0 = sizeKernel / 2;

	for (int i = 0; i < sizeKernel; i++)
	{
		G1[i] = (float)(1.0 / (sqrt(2 * PI) * sigma)) * exp(-((pow(i - x0, 2)) / (float)(2 * sigma*sigma)));
		G2[i] = (float)(1.0 / (sqrt(2 * PI) * sigma)) * exp(-((pow(i - x0, 2)) / (float)(2 * sigma*sigma)));
	}

	// filtering 
	// convolution twice
	//first convolution operation
	Mat temp = Mat(height, width, CV_8UC1);
	for (int i = sizeKernel; i < height - sizeKernel; i++)
	{
		for (int j = sizeKernel; j < width - sizeKernel; j++)
		{
			aux = 0;
			for (int m = 0; m < sizeKernel; m++)
			{
				aux += src.at<uchar>(i + m - 1, j + m - 1) * G1[m];
			}
			temp.at<uchar>(i, j) = aux;
		}
	}

	//second convolution operation
	for (int i = sizeKernel; i < height - sizeKernel; i++)
	{
		for (int j = sizeKernel; j < width - sizeKernel; j++)
		{
			aux = 0;
			for (int m = 0; m < sizeKernel; m++)
			{
				aux += temp.at<uchar>(i + m - 1, j + m - 1) * G2[m];
			}
			(*dst).at<uchar>(i, j) = aux;
		}
	}

	timeComputationEnd();
	imshow("Clean", *dst);
	waitKey();
}

void gaussian2(Mat img) {
	double t = (double)getTickCount();
	float sigma;
	std::cout << "SIGMA";
	std::cin >> sigma;
	int w = sigma * 6;
	int k = w / 2;
	//float sigma = w / 6.0;
	float Gx[500], Gy[500];
	for (int k = 0; k < w; k++)
	{
		float fractie = ((k - 3)*(k - 3)) / (2.0*sigma*sigma);
		Gx[k] = (1 / (sqrt(2 * PI)*sigma))*exp(-fractie);

		Gy[k] = Gx[k];
	}

	Mat dest = Mat(img.rows, img.cols, CV_8UC1);
	Mat aux2 = Mat(img.rows, img.cols, CV_8UC1);

	for (int y = k; y < img.cols - k; y++)
	{
		for (int x = k; x < img.rows - k; x++)
		{
			int aux = 0;
			for (int i = -k; i <= k; i++)
				for (int j = -k; j <= k; j++)
				{
					aux += img.at<uchar>(x + j, y + i) * Gx[j + k];
				}
			aux2.at<uchar>(x, y) = aux;
		}
	}

	for (int y = k; y < img.cols - k; y++)
		for (int x = k; x < img.rows - k; x++)
		{
			int aux = 0;
			for (int i = -k; i <= k; i++)
				for (int j = -k; j <= k; j++)
				{
					aux += aux2.at<uchar>(x + j, y + i) * Gy[i + k];
				}
			dest.at<uchar>(x, y) = aux;
		}

	t = ((double)getTickCount() - t) / getTickFrequency();
	printf("Time = %.3f [ms]\n", t * 1000);

	imshow("Dest", dest);
	waitKey();
}

/// -------------------------------------------------------------- LAB 11 - PART 1 ------------------------------------------------------
// kernels Si, Sj
void firstConvolution(Mat src, Mat Si, Mat Sj, Mat *dst, float p)
{
	int height = src.rows;
	int width = src.cols;
	int sum;
	int median;
	Mat Di(height, width, CV_8UC1);
	Mat Dj(height, width, CV_8UC1);
	Mat Mag(height, width, CV_8UC1);
	Mat Magintitial = Mat::zeros(height, width, CV_32FC1);
	Mat unghi = Mat::zeros(height, width, CV_32FC1);

	for (int i = Si.rows; i < height - Si.rows; i++)
	{
		for (int j = Si.cols; j < width - Si.cols; j++)
		{
			sum = 0;
			for (int p = 0; p < Si.rows; p++)
			{
				for (int q = 0; q < Si.cols; q++)
				{
					sum += src.at<uchar>(i + p - 1, j + q - 1) * Si.at<int>(p, q);
				}
			}

			sum = sum + 128;
			if (sum > 255)
			{
				sum = BACKGROUND;
			}
			if (sum < 0)
			{
				sum = OBJECT;
			}

			Di.at<uchar>(i, j) = sum;
		}
	}

	for (int i = Sj.rows; i < height - Sj.rows; i++)
	{
		for (int j = Sj.cols; j < width - Sj.cols; j++)
		{
			sum = 0;
			for (int p = 0; p < Sj.rows; p++)
			{
				for (int q = 0; q < Sj.cols; q++)
				{
					sum += src.at<uchar>(i + p - 1, j + q - 1) * Sj.at<int>(p, q);
				}
			}

			sum = sum + 128;
			if (sum > 255)
			{
				sum = BACKGROUND;
			}
			if (sum < 0)
			{
				sum = OBJECT;
			}
			Dj.at<uchar>(i, j) = sum;

		}
	}
	//imshow("Di", Di);
	//imshow("Dj", Dj);

	//get rid of the 128
	for (int i = Si.rows; i < height - Si.rows; i++)
	{
		for (int j = Si.cols; j < width - Si.cols; j++)
		{
			sum = 0;
			for (int p = 0; p < Si.rows; p++)
			{
				for (int q = 0; q < Si.cols; q++)
				{
					sum += src.at<uchar>(i + p - 1, j + q - 1) * Si.at<int>(p, q);
				}
			}

			if (sum > 255)
			{
				sum = BACKGROUND;
			}
			if (sum < 0)
			{
				sum = OBJECT;
			}

			Di.at<uchar>(i, j) = sum;
		}
	}

	//get rid of the 128
	for (int i = Sj.rows; i < height - Sj.rows; i++)
	{
		for (int j = Sj.cols; j < width - Sj.cols; j++)
		{
			sum = 0;
			for (int p = 0; p < Sj.rows; p++)
			{
				for (int q = 0; q < Sj.cols; q++)
				{
					sum += src.at<uchar>(i + p - 1, j + q - 1) * Sj.at<int>(p, q);
				}
			}

			if (sum > 255)
			{
				sum = BACKGROUND;
			}
			if (sum < 0)
			{
				sum = OBJECT;
			}
			Dj.at<uchar>(i, j) = sum;
		}
	}

	//find the magnitude
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float valForMag = sqrt(pow(Di.at<uchar>(i, j), 2) + pow(Dj.at<uchar>(i, j), 2));
			Magintitial.at<float>(i, j) = valForMag;

			if (valForMag > 255)
			{
				Mag.at<uchar>(i, j) = BACKGROUND;
			}
			else {
				if (valForMag < 0)
				{
					Mag.at<uchar>(i, j) = OBJECT;
				}
				else
					Mag.at<uchar>(i, j) = valForMag;
			}
		}
	}

	imshow("Mag", Mag);

	//calculate the angle
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			unghi.at<float>(i, j) = atan2(Di.at<uchar>(i, j), Dj.at<uchar>(i, j));
		}
	}

	Mat aux2 = Mat(height, width, CV_8UC1);
	//create the image based on the circle
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (Mag.at<uchar>(i, j) > 20) {
				if (unghi.at<float>(i, j) >= 0 && unghi.at<float>(i, j) <= PI / 8)
				{
					dst->at<Vec3b>(i, j) = Vec3b(255, 0, 0);
					aux2.at<uchar>(i, j) = 2;
				}
				if (unghi.at<float>(i, j) <= (3 * PI) / 8 && unghi.at<float>(i, j) > PI / 8)
				{
					dst->at<Vec3b>(i, j) = Vec3b(0, 255, 0);
					aux2.at<uchar>(i, j) = 1;
				}
				if (unghi.at<float>(i, j) > (3 * PI) / 8 && unghi.at<float>(i, j) <= (5 * PI) / 8)
				{
					dst->at<Vec3b>(i, j) = Vec3b(0, 0, 255);
					aux2.at<uchar>(i, j) = 0;
				}
				if (unghi.at<float>(i, j) > (5 * PI) / 8 && unghi.at<float>(i, j) <= (7 * PI) / 8)
				{
					dst->at<Vec3b>(i, j) = Vec3b(0, 255, 255);
					aux2.at<uchar>(i, j) = 3;
				}
				if (unghi.at<float>(i, j) > (7 * PI) / 8 && unghi.at<float>(i, j) <= PI)
				{
					dst->at<Vec3b>(i, j) = Vec3b(255, 0, 0);
					aux2.at<uchar>(i, j) = 2;
				}

				if (unghi.at<float>(i, j) > PI && unghi.at<float>(i, j) <= PI + (PI / 8))
				{
					dst->at<Vec3b>(i, j) = Vec3b(255, 0, 0);
					aux2.at<uchar>(i, j) = 1;
				}

				/*if (unghi.at<float>(i, j) < 0 / 8 && unghi.at<float>(i, j) >= -PI / 8)
				{
					dst->at<Vec3b>(i, j) = Vec3b(255, 0, 0);
					aux2.at<uchar>(i, j) = 1;
				}*/
				/*if (unghi.at<float>(i, j) >= -(3 * PI) / 8 && unghi.at<float>(i, j) < -PI / 8)
				{
					dst->at<Vec3b>(i, j) = Vec3b(0, 255, 255);
					aux2.at<uchar>(i, j) = 3;
				}*/

				if (unghi.at<float>(i, j) > PI + (PI / 8) && unghi.at<float>(i, j) <= PI + ((3 * PI) / 8))
				{
					dst->at<Vec3b>(i, j) = Vec3b(0, 255, 255);
					printf("aici %d %d ", i, j);
					aux2.at<uchar>(i, j) = 3;
				}
			/*	if (unghi.at<float>(i, j) < -(3 * PI) / 8 && unghi.at<float>(i, j) >= -(5 * PI) / 8)
				{
					dst->at<Vec3b>(i, j) = Vec3b(0, 0, 255);
					aux2.at<uchar>(i, j) = 0;
				}*/

				if (unghi.at<float>(i, j) > PI + ((3 * PI) / 8) && unghi.at<float>(i, j) <= PI + ((5 * PI) / 8))
				{
					dst->at<Vec3b>(i, j) = Vec3b(0, 0, 255);
					printf("aici %d %d ", i, j);
					aux2.at<uchar>(i, j) = 0;
				}
				/*if (unghi.at<float>(i, j) < -(5 * PI) / 8 && unghi.at<float>(i, j) >= -(7 * PI) / 8)
				{
					dst->at<Vec3b>(i, j) = Vec3b(0, 255, 0);
					aux2.at<uchar>(i, j) = 1;
				}*/

				if (unghi.at<float>(i, j) > PI + ((5 * PI) / 8) && unghi.at<float>(i, j) <= PI + ((7 * PI) / 8))
				{
					dst->at<Vec3b>(i, j) = Vec3b(0, 255, 0);
					aux2.at<uchar>(i, j) = 1;
				}
				if (unghi.at<float>(i, j) < -(7 * PI) / 8 && unghi.at<float>(i, j) >= -PI)
				{
					dst->at<Vec3b>(i, j) = Vec3b(255, 0, 0);
					aux2.at<uchar>(i, j) = 2;
				}
			}
		}
	}

	Mat toFinal = Mag.clone();
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if (aux2.at<uchar>(i, j) == 2) {
				if (Magintitial.at<float>(i, j) < Magintitial.at<float>(i, j - 1) ||
					Magintitial.at<float>(i, j) < Magintitial.at<float>(i, j + 1))
				{
					toFinal.at<uchar>(i, j) = 0;
				}
			}
			if (aux2.at<uchar>(i, j) == 0) {
				if (Magintitial.at<float>(i, j) < Magintitial.at<float>(i - 1, j) ||
					Magintitial.at<float>(i, j) < Magintitial.at<float>(i + 1, j))
				{
					toFinal.at<uchar>(i, j) = 0;
					
				}
			}

			if (aux2.at<uchar>(i, j) == 1) {
				if (Magintitial.at<float>(i, j) < Magintitial.at<float>(i - 1, j + 1) ||
					Magintitial.at<float>(i, j) < Magintitial.at<float>(i + 1, j - 1))
				{
					toFinal.at<uchar>(i, j) = 0;
				}
			}

			if (aux2.at<uchar>(i, j) == 3) {
				if (Magintitial.at<float>(i, j) <Magintitial.at<float>(i - 1, j - 1) ||
					Magintitial.at<float>(i, j) < Magintitial.at<float>(i + 1, j + 1))
				{
					toFinal.at<uchar>(i, j) = 0;
				}
			}
		}
	}

	imshow("final", *dst);

	imshow("mag modified", toFinal);

	//adaptive thresholding
	int histo[256];
	float histoNormalized[256];
	int searchedThreshold;
	int thresholdLow;

	buildHistogramFromMat(toFinal, histo, histoNormalized);

	int NoNonEdge = (1 - p)*(height*width - histo[0]);

	int sumHisto = 0;
	for (int i = 1; i < 256; i++)
	{
		sumHisto += histo[i];
		if (sumHisto > NoNonEdge)
		{
			searchedThreshold = i;
			break;
		}
	}
	
	thresholdLow = 0.4 * searchedThreshold;
	printf("High %d \n", searchedThreshold);
    printf("Low %d \n", thresholdLow);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (toFinal.at<uchar>(i,j) >= searchedThreshold)
			{
				toFinal.at<uchar>(i, j) = 255;
			}
			else
			{
				if (toFinal.at<uchar>(i, j) <= thresholdLow)
				{
					toFinal.at<uchar>(i, j) = 0;
				}
				else
				{
					toFinal.at<uchar>(i, j) = 128;
				}
			}
		}
	}

	imshow("After edge strong and stuff", toFinal);

	//labelling
	for (int i = 1; i < height -1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if (toFinal.at<uchar>(i,j) == BACKGROUND)
			{
				std::queue<Point2i> Q;
				Q.push({ i, j });
				while (!Q.empty())
				{
					Point2i p = Q.front();
					Q.pop();

					for (int k = -1; k <= 1; k++)
					{
						for (int l = -1; l <= 1; l++)
						{
							if (toFinal.at<uchar>(p.x + k, p.y + l) == 128)
							{
								toFinal.at<uchar>(p.x + k, p.y + l) = 255;
								Q.push({ p.x + k, p.y + l });
							}
						}
					}
				}
			}
		}
	}

	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			if (toFinal.at<uchar>(i, j) != 255)
			{
				toFinal.at<uchar>(i, j) = 0;
			}
		}
	}

	imshow("Result", toFinal);

	waitKey();
}

int main()
{
	int op;

	char fname[MAX_PATH];
	do
	{
		system("cls");
		destroyAllWindows();
		printf("Menu:\n");
		printf(" 1 - Open image\n");
		printf(" 2 - Open BMP images from folder\n");
		printf(" 3 - Resize image\n");
		printf(" 4 - Process video\n");
		printf(" 5 - Snap frame from live video\n");
		printf(" 6 - Mouse callback demo\n");
		printf(" 7 - Open both\n");
		printf(" 8 - Additive factor to an image\n");
		printf(" 9 - Multiplicative factor to an image\n");
		printf(" 10 - Color image\n");
		printf(" 11 - circular image\n");
		printf(" 12 - scale (zoom in/ out)\n");
		printf(" 13 - resize\n");
		printf(" 14 - lentile effect\n");
		printf(" 15 - negative image \n");
		printf(" 16 - gray image \n");
		printf(" 17 - from gray image to binary image \n");
		printf(" 18 - from color image to HSV \n");
		printf(" 19 - Redness in an image \n");
		printf(" 20 - HistogramMultilevelAndFloyd \n");
		printf(" 21 - Multi-level thresholding to a color image\n");
		printf(" 22 - Find geometric properties\n");
		printf(" 23 - Find objects\n");
		printf(" 24 - Algorithm 1 labelling\n");
		printf(" 25 - Algorithm 2 labelling\n");
		printf(" 26 - Border Tracing algorithm then reconstruct from chain code and derivative\n");
		printf(" 27 - Dilation\n");
		printf(" 28 - Erosion\n");
		printf(" 29 - Multiple times transformation\n");
		printf(" 30 - Opening \n");
		printf(" 31 - Closing\n");
		printf(" 32 - Boundary extraction\n");
		printf(" 33 - Edge filling\n");
		printf(" 34 - Histogram Equalization\n");
		printf(" 35 - Global thresolding algorithm\n");
		printf(" 36 - Histogram streching/ shrinking\n");
		printf(" 37 - Gamma correction \n");
		printf(" 38 - Low pass \n");
		printf(" 39 - High pass \n");
		printf(" 40 - Filtering\n");
		printf(" 41 - Median Filter\n");
		printf(" 42 - Gaussian Filter\n");
		printf(" 43 - Gaussian Filter second approach\n");
		printf(" 44 - Lab 11\n");
		printf(" 0 - Exit\n\n");
		printf("Option: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			testOpenImage();
			break;
		case 2:
			testOpenImagesFld();
			break;
		case 3:
			testResize();
			break;
		case 4:
			testVideoSequence();
			break;
		case 5:
			testSnap();
			break;
		case 6:
			testMouseClick();
			break;
		case 7:
			OpenImage();
			break;
		case 8:
			additive_factor_to_image();
			break;
		case 9:
			multiplicative_factor_to_image();
			break;
		case 10:
			create_color_image5();
			break;
		case 11:
			darker_image();
			break;
		case 12:
			float scale_factor;
			scanf("%f", &scale_factor);
			scale_image(scale_factor);
			break;
		case 13:
			float size;
			scanf("%f", &size);
			change_the_size(size);
			break;
		case 14:
			float size2;
			scanf("%f", &size2);
			lentile_effect(size2);
			break;
		case 15:
			negative_image();
			break;
		case 16:
			fromColorToGray();
			break;
		case 17:
			float threshold;
			scanf("%f", &threshold);
			from8UC1ToBinary(fromColorToGray(), threshold);
			break;
		case 18:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_COLOR);

				fromRGBToHSV(src);
			}
			break;
		case 19:
			scanf("%f", &threshold);
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_COLOR);

				measureRed(src, threshold);
			}
			break;
		case 20:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);

				HistogramMultilevelAndFloyd(src);
			}
			break;
		case 21:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_COLOR);

				multilevelThresoldingToColorImage(src);
			}
			break;
		case 22:
			testMouseClick();

			break;
		case 23:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_COLOR);

				allObjects(src, 1234, 34, 345);
			}
		case 24:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);

				Labelling1Call(src);
			}
			break;

		case 25:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);

				Labelling2Call(src);
			}
			break;

		case 26:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);

				BorderTracing(src);
			}
			break;
		case 27:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				Mat dst = src.clone();
				Mat M = Mat(3, 3, CV_8UC1);
				M.at<uchar>(0, 1) = 1;
				M.at<uchar>(1, 0) = 1;
				M.at<uchar>(1, 1) = 1;
				M.at<uchar>(1, 2) = 1;
				M.at<uchar>(2, 1) = 1;

				dilation2(src, &dst, M);
			}

			break;
		case 28:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				Mat dst = src.clone();
				Mat M = Mat(3, 3, CV_8UC1);
				M.at<uchar>(0, 1) = 1;
				M.at<uchar>(1, 0) = 1;
				M.at<uchar>(1, 1) = 1;
				M.at<uchar>(1, 2) = 1;
				M.at<uchar>(2, 1) = 1;

				erosion2(src, &dst, M);
			}

			break;
		case 29:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);

				Mat M = Mat(3, 3, CV_8UC1);
				M.at<uchar>(0, 1) = 1;
				M.at<uchar>(1, 0) = 1;
				M.at<uchar>(1, 1) = 1;
				M.at<uchar>(1, 2) = 1;
				M.at<uchar>(2, 1) = 1;

				MultipleTransformations(src, 5, M);
			}

			break;
		case 30:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				Mat M = Mat(3, 3, CV_8UC1);
				M.at<uchar>(0, 1) = 1;
				M.at<uchar>(1, 0) = 1;
				M.at<uchar>(1, 1) = 1;
				M.at<uchar>(1, 2) = 1;
				M.at<uchar>(2, 1) = 1;

				opening(src, M);
			}

			break;
		case 31:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				Mat M = Mat(3, 3, CV_8UC1);
				M.at<uchar>(0, 1) = 1;
				M.at<uchar>(1, 0) = 1;
				M.at<uchar>(1, 1) = 1;
				M.at<uchar>(1, 2) = 1;
				M.at<uchar>(2, 1) = 1;

				closing(src, M);
			}

			break;
		case 32:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				Mat dst = src.clone();
				Mat M = Mat(3, 3, CV_8UC1);
				M.at<uchar>(0, 1) = 1;
				M.at<uchar>(1, 0) = 1;
				M.at<uchar>(1, 1) = 1;
				M.at<uchar>(1, 2) = 1;
				M.at<uchar>(2, 1) = 1;

				boundaryExtraction(src, &dst, M);
			}

			break;
		case 34:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				float probability[256];
				HistogramEqualization(src, probability);
			}

			break;
		case 35:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				globalThresoldingAlgorithm(src);
			}

			break;
		case 36:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				int deltaMean, deltaDeviation;
				printf("Delta mean value:\n");
				std::cin >> deltaMean;
				printf("Delta Standard Deviation: \n");
				std::cin >> deltaDeviation;
				histogramStrechingShrinking(src, deltaMean, deltaDeviation);
			}

			break;

		case 37:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				int gamma;
				printf("Gamma correction value :\n");
				std::cin >> gamma;
				gammaCorrection(src, gamma);
			}

			break;
		case 38:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				Mat dst;
				Mat M = Mat(3, 3, CV_8UC1);
				dst = Mat(src.rows, src.cols, CV_8UC1);
				M.at<uchar>(0, 1) = 1;
				M.at<uchar>(1, 0) = 1;
				M.at<uchar>(1, 1) = 1;
				M.at<uchar>(1, 2) = 1;
				M.at<uchar>(2, 1) = 1;
				M.at<uchar>(2, 2) = 1;
				M.at<uchar>(0, 2) = 1;
				M.at<uchar>(0, 0) = 1;
				M.at<uchar>(2, 0) = 1;

				lowPassFiltering(src, M, &dst);
			}

			break;
		case 39:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				Mat dst;
				Mat M = Mat(3, 3, CV_32SC1);
				dst = Mat(src.rows, src.cols, CV_8UC1);
				M.at<int>(0, 1) = -1;
				M.at<int>(0, 2) = -1;
				M.at<int>(0, 0) = -1;
				M.at<int>(1, 0) = -1;
				M.at<int>(1, 1) = 8;
				M.at<int>(1, 2) = -1;
				M.at<int>(2, 1) = -1;
				M.at<int>(2, 2) = -1;
				M.at<int>(2, 0) = -1;

				highPassFilter(src, M, &dst);
			}

			break;
		case 40:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				int R;
				std::cin >> R;
				generic_frequency_domain_filter(src, GAUSS_LOW_FILTER, R);
			}

			break;
		case 41:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				Mat dst = src.clone();
				Mat M = Mat(3, 3, CV_8UC1);
				M.at<uchar>(0, 1) = 1;
				M.at<uchar>(1, 0) = 1;
				M.at<uchar>(1, 1) = 1;
				M.at<uchar>(1, 2) = 1;
				M.at<uchar>(2, 1) = 1;


				MedianFilter(src, M, &dst);
			}

			break;

		case 42:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				float sigma;
				printf("Sigma value :\n");
				std::cin >> sigma;
				Mat dst = Mat(src.rows, src.cols, CV_8UC1);


				GaussianFilter(src, &dst, sigma);
			}

			break;

		case 43:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				/*float sigma;
				printf("Sigma value :\n");
				std::cin >> sigma;
				Mat dst = Mat(src.rows, src.cols, CV_8UC1);*/

				gaussian2(src);
			}

			break;
		case 44:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_GRAYSCALE);
				Mat dst = Mat(src.rows, src.cols, CV_8UC3);
				float p;
				printf("p value :\n");
				std::cin >> p;

				Mat M = Mat(3, 3, CV_32SC1);
				Mat M2 = Mat(3, 3, CV_32SC1);
				M.at<int>(0, 0) = -1;
				M.at<int>(0, 1) = -2;
				M.at<int>(0, 2) = -1;
				M.at<int>(1, 0) = 0;
				M.at<int>(1, 1) = 0;
				M.at<int>(1, 2) = 0;
				M.at<int>(2, 0) = 1;
				M.at<int>(2, 1) = 2;
				M.at<int>(2, 2) = 1;

				M2.at<int>(0, 0) = -1;
				M2.at<int>(0, 1) = 0;
				M2.at<int>(0, 2) = 1;
				M2.at<int>(1, 0) = -2;
				M2.at<int>(1, 1) = 0;
				M2.at<int>(1, 2) = 2;
				M2.at<int>(2, 0) = -1;
				M2.at<int>(2, 1) = 0;
				M2.at<int>(2, 2) = 1;

				firstConvolution(src, M, M2, &dst, p);
			}

			break;
		default:
			break;
		}
	} while (op != 0);
	return 0;
}