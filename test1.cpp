#include <vlcpp/vlc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <dlib/opencv.h>
#include "NeuralNetworkSettings.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
int main()
{ 
    //std::string filename = "/home/rohan/Downloads/videoplayback.avi";
    std::string filename;
    std::cout<<"Enter filename:\n";
    std::getline(std::cin, filename);
    std::cout<<filename<<'\n';
    cv::VideoCapture cap(filename);
    int duration = cap.get(cv::CAP_PROP_FRAME_COUNT) / cap.get(cv::CAP_PROP_FPS);
    std::cout << "Duration " << duration << "s\n";
    cap.release();

    auto instance = VLC::Instance(0, nullptr);
    auto media = VLC::Media(instance, filename, VLC::Media::FromPath);
    auto mp = VLC::MediaPlayer(media);

    cap = cv::VideoCapture("/dev/video1");
    net_type net;
    dlib::deserialize("mmod_human_face_detector.dat") >> net;
    cv::Mat temp;

    mp.play();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //sleep(1);
    int current_time = 1;
    bool ctrl = true;
    while(ctrl)
    {
        cap >> temp;
        dlib::matrix<dlib::rgb_pixel> img;
        dlib::assign_image(img, dlib::cv_image<dlib::bgr_pixel>(temp));
        auto dets = net(img);
        int faces = dets.size();
        // std::cout<<faces<<'\n';
        // std::cout<<"Status = " << mp.state() << '\n';
        std::cout << "Faces: " << faces << " Status " << mp.state() << " % completed = " << mp.position() * 100 << '\n';

        /*
        3 - Playing
        4 - Paused
        6 - Stopped
        */
        if(faces > 0)
        {
            if(mp.state() == 4)
                mp.play();
            if(mp.state() == 6)
            {
                mp.stop();
                ctrl = false;
            }
        }
        else
        {
            if(mp.state() == 3)
            {
                mp.pause();
            }
        }
    }
    cap.release();
}
