// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"
#include <queue>

Mat value_dst;
Mat hue_dst;
Mat saturation_dst;
Mat fromRGBToHSV(Mat src);

//sliding window
int WH = 5; //window 2*WH + 1
float TH = 0.0003; // threshold

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
void showHistogram(const string& name, int* hist, const int  hist_cols, const int hist_height)
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

	for (int i=0; i< contor; i++)
	{
		printf("%d %d %d\n", visited[i][0], visited[i][1], visited[i][2]);
	}

	for (int i = 0; i < contor; i++)
	{
		if (areaObjects[i] > TH_area)
		{
			char name[30];
			sprintf(name, "Image %d", i);
			imshow(name, objects[i]*255);
		}
	}

	for (int i = 0; i < contor; i++)
	{
		if (phiObjects[i] > phi_LOW && phiObjects[i] < phi_HIGH)
		{
			char name[30];
			sprintf(name, "Image %d", i);
			imshow(name, objects[i]);
		}
	}

	waitKey(0);
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

		default:
			break;
		}
	} while (op != 0);
	return 0;
}