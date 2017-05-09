// OpenCVApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "common.h"

Mat value_dst;
Mat hue_dst;
Mat saturation_dst;
Mat fromRGBToHSV(Mat src);

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
		imshow("image", src);
		Mat dst = src.clone();
		imshow("image2", dst); //nume  diferit la ferestra de afisare
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

				Drcn = (float)Drc * 255 / 30;
				final.at<uchar>(i, j) = Drcn;

			}
		}

		imshow("red", final);
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

/* Histogram display function - display a histogram using bars (simlilar to L3 / PI)
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
	/*Mat img = imread("Images/cameraman.bmp",
		CV_LOAD_IMAGE_GRAYSCALE);
	for (int i = 0; i < img.rows; i++){
		for (int j = 0; j < img.cols; j++){
			img.at<uchar>(i, j) = 255 - img.at<uchar>(i, j);
		}
	}
	imshow("negative image", img);
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

//4. Implement a function which changes the gray levels of an image by a multiplicative
//factor.Save the resulting image.
void multiplicative() {
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
	imshow("multiplicative image", img);
	imwrite("Images/cameraman2.bmp", img);
	waitKey(0);
}

//5. Create a color image of dimension 256 x 256. Divide it into 4 squares and color the
//squares from top to bottom, left to right as : white, red, green, yellow.
void create_color_image5()
{
	Mat img(256, 256, CV_8UC3);

	/*for (int i = 0; i < img.rows; i++){
		for (int j = 0; j < img.cols; j++){
		if (j < img.cols / 2 && i < img.rows / 2)
		{
		img.at< Vec3b>(i, j)[0] = 255;
		img.at< Vec3b>(i, j)[1] = 255;
		img.at< Vec3b>(i, j)[2] = 255;
		}
		else if (j > img.cols / 2 && i < img.rows / 2)
		{
		img.at< Vec3b>(i, j)[0] = 0;
		img.at< Vec3b>(i, j)[1] = 0;
		img.at< Vec3b>(i, j)[2] = 255;
		}
		else if (j < img.cols / 2 && i > img.rows / 2)
		{
		img.at< Vec3b>(i, j)[0] = 0;
		img.at< Vec3b>(i, j)[1] = 255;
		img.at< Vec3b>(i, j)[2] = 0;
		}
		else if (j > img.cols / 2 && i > img.rows / 2)
		{
		img.at< Vec3b>(i, j)[0] = 0;
		img.at< Vec3b>(i, j)[1] = 255;
		img.at< Vec3b>(i, j)[2] = 255;
		}
		}
		}*/
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

			pi = pi - delta_p;
			pi = in_interval(pi);

			img.at<uchar>(i, j) = pi;
		}
	}
	imshow("grey image", img);
	waitKey(0);
}

// Scale an image (zoom_in, zoom_out)
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

void change_the_size(float size)
{
	Mat img = imread("Images/cameraman.bmp",
		CV_LOAD_IMAGE_GRAYSCALE);
	double i_aux, j_aux;

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

	imshow("zoom1", dst);
	waitKey(0);
}

// create a circle to the margins of the image
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

	waitKey();

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
			multiplicative();
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
		case 13:
			float size;
			scanf("%f", &size);
			change_the_size(size);
		case 14:
			float size2;
			scanf("%f", &size2);
			lentile_effect(size2);
		case 15:
			negative_image();
		case 16:
			fromColorToGray();
		case 17:
			float threshold;
			scanf("%f", &threshold);
			from8UC1ToBinary(fromColorToGray(), threshold);
		case 18:
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_COLOR);

				fromRGBToHSV(src);
			}

		case 19:
			scanf("%f", &threshold);
			if (openFileDlg(fname))
			{
				Mat src = imread(fname, CV_LOAD_IMAGE_COLOR);

				measureRed(src, threshold);
			}
		}
	} while (op != 0);
	return 0;
}