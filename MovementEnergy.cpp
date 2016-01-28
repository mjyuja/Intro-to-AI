/** Converts a color image into a binary image
@param src the source color image
@param dst the output image
@param int the threshold for the conversion to binaru
*/
void myBinaryImage(Mat& src, Mat& dst, int threshold);

/** Differences two Binary Images 
@param src1 a Mat image
@param src2 a Mat image
@param dst the output image
*/
void myDifferenceImage(Mat& src1, Mat& src2, Mat& dst);

/** Takes the Union of two images 
@param src1 a Mat image
@param src2 a Mat image
*/
void myUnionImage(Mat& src1, Mat& src2);

// utilities from Lab 1

/** Creates a grayscale image from a color image.
@param src The source color image
@param dst The destination grayscale image
*/
void myGrayScale(Mat& src, Mat& dst);

/**
Creates a tinted image from a color image.
@param src The source color image
@param dst The destination tinted image
@param channel The channel specifies the tint
*/
void myTintImage(Mat& src, Mat& dst, int channel);

/**
Creates a thresholded image from a grayscale image.

@param src The source color image
@param dst The destination tinted image
@param threshold The specified threshold intensity
*/
void myThresholdImage(Mat& src, Mat& dst, int threshold);

int main()
{}

	//Creates a grayscale image from a color image.
	void myGrayScale(Mat& src, Mat& dst) {
		//Different algorithms for converting color to grayscale: http://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
		/*dst = Mat::zeros(src.rows, src.cols, CV_8UC1); //Returns a zero array of same size as src mat, and of type CV_8UC1
		for (int i = 0; i < src.rows; i++){
		for (int j = 0; j < src.cols; j++){
		//For each pixel, compute the average intensity of the 3 color channels
		Vec3b intensity = src.at<Vec3b>(i,j); //Vec3b is a vector of 3 uchar (unsigned character)
		int avg = (intensity[0] + intensity[1] + intensity[2])/3;
		dst.at<uchar>(i,j) = avg;
		}
		} */
		cvtColor(src, dst, CV_BGR2GRAY); //cvtColor documentation: http://docs.opencv.org/modules/imgproc/doc/miscellaneous_transformations.html
	}

	//Creates a tinted image from a color image.
	void myTintImage(Mat& src, Mat& dst, int channel)
	{
		dst = src.clone(); //the clone methods creates a deep copy of the matrix
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				//For each pixel, suppress the channels other than that passed in the argument of the function
				dst.at<Vec3b>(i, j)[(channel + 1) % 3] = 0;
				dst.at<Vec3b>(i, j)[(channel + 2) % 3] = 0;
			}
		}
	}

	//Creates a thresholded image from a grayscale image.
	void myThresholdImage(Mat& src, Mat& dst, int threshold)
	{
		dst = src.clone();
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				//For each pixel, assign intensity value of 0 if below threshold, else assign intensity value of 255
				int intensity = src.at<uchar>(i, j);
				if (intensity < threshold)
				{
					dst.at<uchar>(i, j) = 0;
				}
				else
				{
					dst.at<uchar>(i, j) = 255;
				}
			}
		}
	}

	//Creates a binary image from a color image
	void myBinaryImage(Mat&src, Mat& dst, int threshold) {
		dst = src.clone();   // create deep copy

		myGrayScale(src, dst);  // convert to gray scale

		myThresholdImage(src, dst, threshold);
		
	}

	//Creates a image to represnt the difference between two binary images
	void myDifferenceImage(Mat& src1, Mat& src2, Mat& dst) {
		dst = src.clone();
		for (int i = 0; i < src.rows; i++)
		{
			for (int j = 0; j < src.cols; j++)
			{
				// for each pixel, take the difference of that pixel between the images
				int value = src1.at<uchar>(i, j) - src2.at<uchar>(i, j);

				// if there is a difference between the values, assign instensity of value of 255 to output image
				if (value != 0)
					dst.at<uchar>(i, j) = 255;
				else
					dst.at<uchar>(i, j) = 0;
			}
		}
	}

	void myUnionImage(Mat& src1, Mat& src2, Mat& dst) {
		dst = src1.clone();
		for (int i = 0; i < src1.rows; i++)
		{
			for (int j = 0; j < src1.cols; j++)
			{
				// for each pizel, check its value
				int value1 = src1.at<uchar>(i, j);
				int value2 = src.at<uchar>(i, j);

				// if either pixel is 255 then output that to the image
				if (value1 > 0 || value2 > 0)
					dst.at<uchar>(i, j) = 255;
				else
					dst.at<uchar>(i, j) = 0;
			}
		}
	}
