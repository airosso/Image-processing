int getPixelColor(IplImage* img, int x, int y, int c)
{
  return (unsigned char)(*(img->imageData + y*img->widthStep + x*img->nChannels + c));
}

void setPixelColor(IplImage* img, int x , int y, int c, int value)
{
    *(img->imageData + y*img->widthStep + x*img->nChannels + c) = value;
}

double r1[3], g1[3], b1[3];
int x_sr[3], y_sr[3],k[3];

void poisk(int kol_of_color, IplImage *image, IplImage *image1)
{
    /*r1[0] = 0.84,g1[0] = 0.27, b1[0] = 0.45;
    r1[1] = 0, g1[1] = 0.36, b1[1] = 0.93;
    r1[2] = 0.32, g1[2] = 0.65, b1[2] = 0.67;*/

    for (int x = 0; x<640; x++)
        {
            for(int y = 0; y<480; y++)
            {
                double b = getPixelColor(image,x,y,0);
                double g = getPixelColor(image,x,y,1);
                double r = getPixelColor(image,x,y,2);
                double v2 = sqrt(r*r+g*g+b*b);
                bool flag = true;
                int i1;
                for (int i = 0; i<kol_of_color; i++)
                {
                    if (((b*b1[i]+g*g1[i]+r*r1[i])/v2>0.9) && (r+g+b >= 60))
                    {
                        flag = false;
                        i1 = i;
                    }
                }
                if (flag)
                {
                    setPixelColor(image1,x,y,0,0);
                    setPixelColor(image1,x,y,1,0);
                    setPixelColor(image1,x,y,2,0);
                }
                else
                {   if (i1 == 0)
                    {
                        setPixelColor(image1,x,y,0,0);
                        setPixelColor(image1,x,y,1,0);
                        setPixelColor(image1,x,y,2,225);
                    }
                    if (i1 == 1)
                    {
                        setPixelColor(image1,x,y,0,225);
                        setPixelColor(image1,x,y,1,0);
                        setPixelColor(image1,x,y,2,0);
                    }
                    if (i1 == 2)
                    {
                        setPixelColor(image1,x,y,0,0);
                        setPixelColor(image1,x,y,1,225);
                        setPixelColor(image1,x,y,2,0);
                    }
                }

            }
        }
}
