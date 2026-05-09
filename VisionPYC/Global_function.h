#pragma once
#include <opencv2/opencv.hpp>

#include <QFile>
#include <QImage>
#include <QDebug>
#include <QString>
#include <string>



//读取图像 ，兼容中文路径
bool loadAndPrepareImage(const QString& filePath, cv::Mat& outMat, QImage& outImage);