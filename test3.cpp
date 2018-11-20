#include <vlcpp/vlc.hpp>
#include <thread>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <dlib/opencv.h>
#include "NeuralNetworkSettings.hpp"
#include <mutex>

bool face_detected = true;
net_type net;
std::mutex m;

void FaceDetect()
{
    cv::VideoCapture cap("/dev/video1");
    cv::Mat temp;
    while(true)
    {
        cap >> temp;
        dlib::matrix<dlib::rgb_pixel> img;
        dlib::assign_image(img, dlib::cv_image<dlib::bgr_pixel>(temp));
        auto dets = net(img);
        int faces = dets.size();
        std::cout<<"Faces = "<<faces<<'\n';
        if(faces > 0)
        {
            if(face_detected == false)
            {
                m.lock();
                face_detected = true;
                m.unlock();
            }
        }
        else
        {
            if(face_detected == true)
            {
                m.lock();
                face_detected = false;
                m.unlock();
            }
        }
        if((char)cv::waitKey(1) == 'q')
            break;
    }
    cap.release();
}

void VideoPlay(std::string filename)
{
    dlib::deserialize("mmod_human_face_detector.dat") >> net;
    auto instance = VLC::Instance(0, nullptr);
    auto media = VLC::Media(instance, filename, VLC::Media::FromPath);
    auto mp = VLC::MediaPlayer(media);
    mp.play();
    int state = mp.state();
    while(state != 6)       // As long as it is not over
    {
        if(face_detected == true && state == 4)
            mp.play();
        else if(face_detected == false && state == 3)
            mp.pause();
        state = mp.state();
    }
    mp.stop();
}

int main(int ac, char** av)
{
    std::string filename;
    std::cout<<"Enter filename:\n";
    std::getline(std::cin, filename);
    std::thread t1(&FaceDetect);
    std::thread t2(&VideoPlay, filename);
    t1.join(); t2.join();
}