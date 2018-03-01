#include <Eigen/Eigen>

using namespace Eigen;


const int W = 640;
const int height = 480;

const double Hang = 2*M_PI/9;
const double trans = 2* tan(Hang/2) / height;

Vector2d getCalibratedCoordinates(double x, double y)
{
    x -= W/2;
    y -= height/2;
    //y = height/2 - y;
    Vector2d res;
    res.x() = x*trans;
    res.y() = y*trans;
    return res;
}

Vector2i getPixelCoordinates(Vector3d X)
{
    X.x() /= X.z() * trans;
    X.y() /= X.z() * trans;
    Vector2i res;
    res.x() = X.x() + W/2;
    res.y() = X.y() + height/2;
    return res;
}
const int count_of_dots = 36;
Vector2d X1[count_of_dots];

/*Vector3d X[cont_of_dots]{
    Vector3d(9.2,18.9,0),
    Vector3d(9.1,1.8,0),
    Vector3d(1.1,1.8,0),
    Vector3d(1.1,18.9,0),
    Vector3d(28.1,19,0),
    Vector3d(28.3,11,0),
    Vector3d(11.2,10.8,0),
    Vector3d(11,18.9,0),
    Vector3d(28.1,9.8,0),
    Vector3d(28,1.8,0),
    Vector3d(11,1.8,0),
    Vector3d(11,8.7,0)
};
Matrix <double, count_of_dots*2, 1> B;
Matrix <double, count_of_dots*2, 6> H;
Matrix <double, 6, 1> U;

Affine3d nextTransform(Affine3d  const & P)
{
    int k;
    for (int i=0; i<count_of_dots; i++)
    {
        Vector3d X_curr = P * X[i];

        Matrix <double, 3, 6> G;
        Matrix <double, 2, 3> M;

        G << 0, X_curr.z(), -X_curr.y(), 1, 0, 0,
             -X_curr.z(), 0, X_curr.x(), 0, 1, 0,
             X_curr.y(), -X_curr.x(), 0, 0, 0, 1;

        M << 0, -1, X1[i].y(),
             1, 0, -X1[i].x();

        //cout << i << endl << M << endl << endl;

        k = 2*i;
        H.block<2,6>(k,0) = M*G;
        B.block<2,1>(k,0) = -M*X_curr;
    }
    JacobiSVD<MatrixXd> svd(H, ComputeThinU | ComputeThinV);
    U=svd.solve(B);

    cout << (B - H*U).norm() << " ";

    Affine3d T = Affine3d::Identity();

    T.linear() = (AngleAxisd(U(2), Vector3d::UnitZ()) *
                AngleAxisd(U(1), Vector3d::UnitY()) *
                AngleAxisd(U(0), Vector3d::UnitX())).matrix();

    /*T.linear() << 1, -U(2), U(1),
                U(2), 1, -U(0),
                -U(1), U(0), 1;*/


    //T.translation() = U.bottomRows(3);  //U(3) = tx, U(4) = ty, U(5) = tz;

  /*  for (int i = 0; i < 3; i++)
        T.translation()(i) = U(i+3);

    return T * P;
}

void math_processing (IplImage* image)
{
    Affine3d P = Affine3d::Identity();
    for (int i = 0; i < 8; i++) {
        P = nextTransform(P);
    }
    Vector2i res = getPixelCoordinates(P * Vector3d(0,0,0));
    cvCircle(image, cvPoint(res.x(), res.y()), 3, CV_RGB(255,255,0), -1);
    //cout << res.transpose() << endl;
    cout << endl << endl;
    //cout << (P * Vector3d(0,0,0)).transpose() << endl << endl;
    cout << P.matrix() << endl;
}
*/
