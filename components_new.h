#include "math.h"
CvPoint queue[307200];
int size[307200];
int number_of_components [640][480];
double points_x[2][3];
double points_y[2][3];
bool mouse_flag = false;

void MyMouse(int event, int x, int y, int flag, void* img)
{
    IplImage* image1 = (IplImage*) img;
    static int counter = 0;
    static double le;
    switch (event)
    {
     case CV_EVENT_MOUSEMOVE:
        break;
     case CV_EVENT_LBUTTONDOWN:
        b1[counter % 3] = getPixelColor(image1,x,y,0);
        g1[counter % 3] = getPixelColor(image1,x,y,1);
        r1[counter % 3] = getPixelColor(image1,x,y,2);
        le = sqrt(b1[counter % 3]*b1[counter % 3]+ g1[counter % 3]*g1[counter % 3]+r1[counter % 3]*r1[counter % 3]);
        b1[counter % 3] = b1[counter % 3]/le;
        g1[counter % 3] = g1[counter % 3]/le;
        r1[counter % 3] = r1[counter % 3]/le;
        counter++;
        break;
     case CV_EVENT_LBUTTONUP:
        break;
    }

}

void max_components(IplImage *image1, int count_of_components, int i, int tail, int head)
{
    int b_1,g_1,r_1,n;
            memset(number_of_components,-1,sizeof(number_of_components));
            if (i==0)
            {
                b_1 = 0;
                g_1 = 0;
                r_1 = 225;
            }
            if (i==1)
            {
                b_1=225;
                g_1=0;
                r_1=0;
            }
            if (i==2)
            {
                b_1 = 0;
                g_1 = 225;
                r_1 = 0;
            }
            memset(size,0,sizeof(size));
            count_of_components = 0;
            for (int x = 0; x<640; x++)
            {
                for(int y = 0; y<480; y++)
                {
                    if(((getPixelColor(image1,x,y,0)==b_1)&&
                        (getPixelColor(image1,x,y,1)==g_1)&&
                        (getPixelColor(image1,x,y,2)==r_1))&&
                        (number_of_components[x][y]==-1))
                    {
                        number_of_components[x][y] = count_of_components;
                        size[count_of_components] = 1;
                        head = tail = 0;
                        queue[tail++]=cvPoint(x,y);

                    while(head < tail)
                    {
                        CvPoint p = queue[head++];
                        for(int dx=-1; dx<=1; dx++)
                        {
                            for(int dy=-1; dy<=1; dy++)
                            {
                                if((p.x+dx>=0)&&(p.x+dx<=639)&&(dy+p.y>=0)&&(dy+p.y<=479))
                                {
                                    if(((getPixelColor(image1,p.x+dx,p.y+dy,0)==b_1)&&
                                        (getPixelColor(image1,p.x+dx,p.y+dy,1)==g_1)&&
                                        (getPixelColor(image1,p.x+dx,p.y+dy,2)==r_1))&&
                                        (number_of_components[p.x+dx][p.y+dy]==-1))
                                    {
                                            queue[tail++]=cvPoint(p.x+dx,p.y+dy);
                                            number_of_components[p.x+dx][p.y+dy] = count_of_components;
                                            size[count_of_components]++;
                                        }
                                }
                            }
                        }
                    }
                    count_of_components++;
                }

            }
        }
        int max_size = 0;
        k[i]=0;
        for (int j = 0; j<count_of_components; j++)
        {
            if(size[j]>max_size)
            {
                max_size = size[j];
                k[i] = j;
            }
        }
}
void middles_of_components(IplImage *image1,int i)
{
        x_sr[i] = 0;
        y_sr[i] = 0;
        int n = 0;
        for(int x = 0; x<640; x++)
        {
            for(int y = 0; y<480; y++)
            {
                if (number_of_components[x][y]!=k[i] && number_of_components[x][y] != -1)
                {
                    setPixelColor(image1,x,y,0,0);
                    setPixelColor(image1,x,y,1,0);
                    setPixelColor(image1,x,y,2,0);
                }
                else
                {
                    x_sr[i] =+ x;
                    y_sr[i] =+ y;
                    n++;
                }
            }
        }
            if (n!=0)
            {
                x_sr[i]/=n;
                y_sr[i]/=n;
            }
}
void dots_of_components(IplImage *image1, int i)
{
    int l;
    double max_length = 0;
    for(int x = 0; x<640; x++)
    {
        for(int y = 0; y<480; y++)
        {
            if (number_of_components[x][y]==k[i])
            {
                if(max_length < sqrt((x - x_sr[i])*(x - x_sr[i]) + (y - y_sr[i])*(y - y_sr[i])))
                {
                    max_length =sqrt((x - x_sr[i])*(x - x_sr[i]) + (y - y_sr[i])*(y - y_sr[i]));
                    points_x[i][0]=x;
                    points_y[i][0]=y;
                }
            }
        }
    }
    cvCircle(image1,cvPoint(points_x[i][0],points_y[i][0]),5,CV_RGB(255,128,0),-1);
    max_length = 0;
        //поиск второй точки относительно первой точки
            for(int x = 0; x<640; x++)
            {
                for(int y = 0; y<480; y++)
                {
                    if (number_of_components[x][y]==k[i])
                    {
                        if(max_length < sqrt((x -points_x[i][0])*(x - points_x[i][0]) + (y - points_y[i][0])*(y - points_y[i][0])))
                        {
                            max_length = sqrt((x -points_x[i][0])*(x - points_x[i][0]) + (y - points_y[i][0])*(y - points_y[i][0]));
                            points_x[i][2]=x;
                            points_y[i][2]=y;
                        }
                    }
                }
            }
            cvCircle(image1,cvPoint(points_x[i][2],points_y[i][2]),5,CV_RGB(128,255,0),-1);
            //конец поиска

            double a,b,c;
            a = points_y[i][2] - points_y[i][0];
            b = points_x[i][0]- points_x[i][2];
            c = points_y[i][0]*points_x[i][2] - points_x[i][0]*points_y[i][2];

            //поиск точек относительно прямой
            double d, d_max = 0, d_min = 0;
            for(int x = 0; x<640; x++)
            {
                for(int y = 0; y<480; y++)
                {
                    if (number_of_components[x][y]==k[i])
                    {
                        d = (a*x + b*y + c)/sqrt(a*a + b*b);
                        if (d > d_max)
                        {
                            d_max = d;
                            points_x[i][3]=x;
                            points_y[i][3]=y;
                        }
                        if (d < d_min)
                        {
                            d_min = d;
                            points_x[i][1]=x;
                            points_y[i][1]=y;
                        }
                    }
                }
            }
            cvCircle(image1,cvPoint(points_x[i][3],points_y[i][3]),5,CV_RGB(255,255,255),-1);
            cvCircle(image1,cvPoint(points_x[i][1],points_y[i][1]),5,CV_RGB(0,128,255),-1);

            for (l = 0; l<4; l++)
            {
                CvFont font;
                cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX, 1.0, 1.0, 0, 1, CV_AA);
                char navdata_string[2];
                sprintf(navdata_string,"%d",l);
                cvPutText(image1, navdata_string, cvPoint(points_x[i][l],points_y[i][l]), &font,CV_RGB(255,255,255));
            }
}
void calibration(int i)
{
    int n1,n3,k1,k2;
    if (i == 0)
    {
        k1 = 1;
        k2 = 2;
    }
    if (i == 1)
    {
        k1 = 0;
        k2 = 2;
    }
    if (i == 2)
    {
        k1 = 1;
        k2 = 0;
    }
    double max_dist = 0, min_dist = 1000, dist = 0;
    int arr_x[4], arr_y[4];
    for(int j = 0; j < 4; j++)
    {
        dist = sqrt((x_sr[k1] -points_x[i][j])*(x_sr[k1] - points_x[i][j]) + (y_sr[k1] - points_y[i][j])*(y_sr[k1] - points_y[i][j]));
       if ( max_dist < dist)
       {
           max_dist = dist;
           arr_x[2] = points_x[i][j];
           arr_y[2] = points_y[i][j];
           n3 = j;
       }
       if (min_dist > dist)
       {
           min_dist = dist;
           arr_x[0] = points_x[i][j];
           arr_y[0] = points_y[i][j];
           n1 = j;
       }
    }
    max_dist = 0;
    min_dist = 1000;
    for(int j = 0; j < 4; j++)
    {
        if ((j != n1) && (j != n3 ))
        {
            dist = sqrt((x_sr[k2] - points_x[i][j])*(x_sr[k2] - points_x[i][j]) + (y_sr[k2] - points_y[i][j])*(y_sr[k2] - points_y[i][j]));
            if ( max_dist < dist)
            {
                max_dist = dist;
                arr_x[1] = points_x[i][j];
                arr_y[1] = points_y[i][j];
            }
            if (min_dist > dist)
            {
                min_dist = dist;
                arr_x[3] = points_x[i][j];
                arr_y[3] = points_y[i][j];
            }
        }
    }
    for(int j=0; j< 4; j++)
    {
      points_x[i][j]=arr_x[j];
      points_y[i][j]=arr_y[j];
    }
}

void great(IplImage *image1, int count_of_components, int kol_of_color, int tail, int head)
{
    for(int i=0; i<kol_of_color; i++)
    {
       max_components(image1, count_of_components,i, tail, head);
       middles_of_components(image1, i);
       dots_of_components(image1,i);
    }
   // for (int i=0; i<kol_of_color;i++)
//        for(int j=0; j<3; j++)

    /*X1[0]=getCalibratedCoordinates(points_x[0][0],points_y[0][0]);
    X1[3]=getCalibratedCoordinates(points_x[0][1],points_y[0][1]);
    X1[6]=getCalibratedCoordinates(points_x[0][2],points_y[0][2]);
    X1[3]=getCalibratedCoordinates(points_x[0][3],points_y[0][3]);
    X1[4]=getCalibratedCoordinates(points_x[1][0],points_y[1][0]);
    X1[5]=getCalibratedCoordinates(points_x[1][1],points_y[1][1]);
    X1[6]=getCalibratedCoordinates(points_x[1][2],points_y[1][2]);
    X1[7]=getCalibratedCoordinates(points_x[1][3],points_y[1][3]);
    X1[8]=getCalibratedCoordinates(points_x[2][0],points_y[2][0]);
    X1[9]=getCalibratedCoordinates(points_x[2][1],points_y[2][1]);
    X1[10]=getCalibratedCoordinates(points_x[2][2],points_y[2][2]);
    X1[11]=getCalibratedCoordinates(points_x[2][3],points_y[2][3]);*/
}
