#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<iomanip>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;

// 函数声明
void LoadImage(vector<string> &vstImageFilenames, vector<double> &vdTimestampes, const string &filepath);

/*
入参：
文件路径 string
*/
int main(int argc,char **argv)
{
  if(argc != 2)
  {
    cerr<<"path_to_sequence"<<endl;
    return 1;
  }

  /*目的是为了读取图像和存储时间戳
   *
   * 路径： /home/er/Desktop/dataset/04/  + "image_0" + "000000.png"
   *       vector<string>
   * 时间戳： /home/er/Desktop/dataset/04 + "times.txt"
   *        vector<double>
   * */

    vector<string> vstImageFilenames;
    vector<double> vdTimestampes;
    string filepath = string(argv[1]);

    LoadImage(vstImageFilenames,vdTimestampes,filepath);
    int n = vdTimestampes.size();
    cout << n << endl;
    for(int i=0;i<n;i++)
    {
        // cout<< vstImageFilenames[i] <<endl;
        cv::Mat image = cv::imread(vstImageFilenames[i],CV_LOAD_IMAGE_UNCHANGED);
        cv::imshow("image",image);
        cv::waitKey(100);
    }

    /*
     * LoadImage()
     * 作用：
     * 1、将图像路径拼接起来保存
     * 2、打开times.txt 文件,将时间戳保存
     * void LoadImage(vector<string> &vstImageFilenames, vector<double> &vdTimestampes, const string &filepath)
     * */
}


void LoadImage(vector<string> &vstImageFilenames, vector<double> &vdTimestampes, const string &filepath)
{
    string timestampespath = filepath + "/times.txt";
    ifstream ftimes;
    ftimes.open(timestampespath.c_str());
    while(!ftimes.eof())
    {
        string s ;
        getline(ftimes,s);
        if(!s.empty())
        {
            stringstream ss;
            ss << s;
            double time;
            ss >> time;
            vdTimestampes.push_back(time);
        }

    }

    int ntimes = vdTimestampes.size();
    vstImageFilenames.resize(ntimes);
    string strImagepath = filepath  + "/image_0/";
    for(int i=0;i<ntimes;i++)
    {
        stringstream ss;
        ss << setfill('0') << setw(6) << i;
        string path = strImagepath + ss.str() + ".png";
        vstImageFilenames[i] = path;
    }
}