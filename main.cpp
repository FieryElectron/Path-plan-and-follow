#include <opencv2/opencv.hpp>
#include <queue>

using namespace cv;
using namespace std;

Mat img(500, 500, CV_8UC1, Scalar(0));
Mat cimg = img.clone();

class Path
{
public:
    Point start;
    Point end;
    Point vec;

    bool vertical = false;
    bool horizontal = false;

    bool onSegment(Point point)
    {
        if (vertical)
        {
            if (min(start.y, end.y) <= point.y && max(start.y, end.y) >= point.y)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (min(start.x, end.x) <= point.x && max(start.x, end.x) >= point.x)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    Path(Point s, Point e)
    {
        start = s;
        end = e;
        vec = end - start;

        if (start.x == end.x)
        {
            vertical = true;
        }
        else if (start.y == end.y)
        {
            horizontal = true;
        }
    }
};

float GetAngle(Point point)
{
    float point_len = sqrt(point.x * point.x + point.y * point.y);
    Point2f point_unit = Point2f((float)point.x / point_len, (float)point.y / point_len);
    return CV_PI / 2 - atan2(point_unit.y, point_unit.x);
}

float correctAng(float ang)
{
    while (!(ang >= 0.0 && ang < CV_2PI))
    {
        if (ang > CV_2PI)
        {
            ang -= CV_2PI;
        }
        else if (ang < 0.0)
        {
            ang += CV_2PI;
        }
    }
    return ang;
}

float Distance(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct DirInfo
{
    char dir;
    float value;
};

DirInfo calAng(float ref_ang, float one_ang)
{
    char l_dir;
    float l_value;
    float dif_ang = one_ang - ref_ang;

    if (dif_ang >= 0 && dif_ang <= CV_PI)
    {
        l_dir = 'r';
        l_value = dif_ang;
    }
    else if (dif_ang > CV_PI)
    {
        l_dir = 'l';
        l_value = CV_2PI - dif_ang;
    }
    else if (dif_ang < 0 && dif_ang >= -CV_PI)
    {
        l_dir = 'l';
        l_value = -dif_ang;
    }
    else if (dif_ang < -CV_PI)
    {
        l_dir = 'r';
        l_value = CV_2PI + dif_ang;
    }
    else
    {
        printf("Something wrong in calAng!!!!\n");
    }

    return DirInfo{l_dir, l_value};
}

queue<Path> pathQueue;
Point3f pos(50, 50, 0);
int times = 0;
Point pp;

void onMouse(int event, int x, int y, int flags, void *param)
{
    switch (event)
    {
    case EVENT_LBUTTONDOWN:
        if (times == 0)
        {
            pos = Point3f(x, y, 0);
        }
        else
        {
            pathQueue.push(Path(pp, Point(x, y)));
            arrowedLine(img, pp, Point(x, y), Scalar(255), 1, 1);
        }
        pp = Point(x, y);
        ++times;
        break;
    }
}

int main()
{
    cv::namedWindow("Map", WINDOW_AUTOSIZE);
    cv::setMouseCallback("Map", onMouse, reinterpret_cast<void *>(&img));

    float speed_Left = 2;
    float speed_Right = 2;

    float ang = CV_PI / 180.0 * 0.0;
    float dt = 0.5;
    float speed;

    float forward;
    float rightward;

    while (true)
    {
        if (pathQueue.empty())
        {
            imshow("Map", cimg);
            waitKey(1);
            continue;
        }

        Path p = pathQueue.front();
        pathQueue.pop();

        float pathang = GetAngle(p.vec);
        pathang = correctAng(pathang);

        while (true)
        {
            ang += (speed_Left - speed_Right) * dt / 2.0;
            ang = correctAng(ang);

            Point2f tmp_vec = Point(pos.x, pos.y) - p.start;
            float posang;
            if (tmp_vec.x == 0 && tmp_vec.y == 0)
            {
                posang = pathang;
            }
            else
            {
                posang = GetAngle(tmp_vec);
            }

            if (Distance(p.start, Point(pos.x, pos.y)) > 40 && !p.onSegment(Point(pos.x, pos.y)))
            {
                break;
            }

            posang = correctAng(posang);
            DirInfo tmp = calAng(pathang, posang);

            if (tmp.dir == 'l')
            {
                DirInfo tmp1 = calAng(pathang, ang);
                if (tmp1.dir == 'l')
                {
                    speed_Left = 3;
                    speed_Right = 2;
                }
                else if (tmp1.dir == 'r')
                {
                    if (tmp1.value < CV_PI / 19)
                    {
                        speed_Left = 3;
                        speed_Right = 2;
                    }
                    else
                    {
                        speed_Left = 2;
                        speed_Right = 2;
                    }
                }
            }
            else if (tmp.dir == 'r')
            {
                DirInfo tmp1 = calAng(pathang, ang);
                if (tmp1.dir == 'r')
                {
                    speed_Left = 2;
                    speed_Right = 3;
                }
                else if (tmp1.dir == 'l')
                {
                    if (tmp1.value < CV_PI / 19)
                    {
                        speed_Left = 2;
                        speed_Right = 3;
                    }
                    else
                    {
                        speed_Left = 2;
                        speed_Right = 2;
                    }
                }
            }

            speed = (speed_Left + speed_Right) / 2.0;
            forward = speed * cos(ang);
            rightward = speed * sin(ang);

            forward *= dt;
            rightward *= dt;

            pos = pos + Point3f(rightward, forward, 0);
            cimg = img.clone();
            arrowedLine(cimg, Point(pos.x, pos.y), Point(pos.x + 60 * sin(ang), pos.y + 60 * cos(ang)), Scalar(255), 1, LINE_8);
            circle(cimg, Point(pos.x, pos.y), 40, Scalar(255), 1, LINE_8, 0);
            imshow("Map", cimg);
            waitKey(1);
        }
    }
    cout << "end!" << endl;
    waitKey(0);
    return 0;
}
