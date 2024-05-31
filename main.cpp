#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace cv;
using namespace std;
using json = nlohmann::json;

void applyMosaic(Mat &frame, Rect region, int mosaicSize) {
    for (int y = region.y; y < region.y + region.height; y += mosaicSize) {
        for (int x = region.x; x < region.x + region.width; x += mosaicSize) {
            Rect mosaicRect = Rect(x, y, mosaicSize, mosaicSize) & Rect(0, 0, frame.cols, frame.rows);
            Scalar color = mean(frame(mosaicRect));
            rectangle(frame, mosaicRect, color, FILLED);
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return -1;
    }

    ifstream configFile("config.json");
    if (!configFile.is_open()) {
        cerr << "Error opening config file: config.json" << endl;
        return -1;
    }

    json config;
    configFile >> config;

    Rect mosaicRegion(
            config["mosaicRegion"]["x"],
            config["mosaicRegion"]["y"],
            config["mosaicRegion"]["width"],
            config["mosaicRegion"]["height"]
    );
    int mosaicSize = config["mosaicSize"];

    string inputFile = argv[1];
    VideoCapture cap(inputFile);

    if (!cap.isOpened()) {
        cerr << "Error opening input file: " << inputFile << endl;
        return -1;
    }

    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        applyMosaic(frame, mosaicRegion, mosaicSize);

        imshow("VeilFlow", frame);
        if (waitKey(10) == 27) {
            break;
        }
    }

    return 0;
}
