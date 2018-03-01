#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

using namespace std;

#include "konus_lib.h"
#include "components_new.h"
//#include "math.h"

//double g_to_b = 9, g_to_r = 14.5, r_to_b = 15;

int main ()
{
    IplImage *image, *image1;
    image1 = cvCreateImage(cvSize(640, 480),IPL_DEPTH_8U,3);//создание изображения
    CvCapture *capture;//захват изображения с камеры(создание канала, по которому мы будем читать изображения)
    capture = cvCreateCameraCapture(2);

    int count_of_components = 3;
    int tail,head;

    char c = 0;

    cvNamedWindow("name");
    image = cvQueryFrame(capture);
    cvSetMouseCallback("name", MyMouse, (void*)image);

    while(c != 27)
    {
        image = cvQueryFrame(capture);
        cvCopyImage(image, image1);
        int k = 3;
        poisk(k, image, image1);
        great(image1, count_of_components, 3, tail, head);
        //math_processing(image);
        //cout << U.transpose()<< endl;
        cvShowImage("name", image);
        cvShowImage("result", image1);
        c = cvWaitKey(1);
    }
    return 0;
}
