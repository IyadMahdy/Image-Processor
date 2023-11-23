/*
 FCAI – OOP Programming – 2023 - Assignment 1
 Program Name: RGB_image_source_code.cpp
 Last Modification Date: 18/10/2023
 Author1 and ID and Group: Kirolos Adel Nan     20220253   B
 Author2 and ID and Group: Mario Michel Magdy   20220266   A
 Author3 and ID and Group: Iyad Mahdy Mahrous   20220075   A
 Purpose: A cpp program for image processing to apply 15 filters on Grey Bitmap images of 256x256 size
*/
#ifndef IMAGE_PROCESSOR_IMAGE_H
#define IMAGE_PROCESSOR_IMAGE_H

#include "bmplib.cpp"
#include <bits/stdc++.h>

using namespace std;

class Image {
protected:
    const int SOBEL_X[3][3] = {{1, 0, -1},
                               {2, 0, -2},
                               {1, 0, -1}};
    const int SOBEL_Y[3][3] = {{1,  2,  1},
                               {0,  0,  0},
                               {-1, -2, -1}};

    virtual void loadImage() = 0;

    virtual void saveImage() = 0;

    virtual char options() = 0;

    virtual void imageProcessor(char option) = 0;

    virtual void black_and_white() = 0;

    virtual void invert() = 0;

    virtual void merge() = 0;

    virtual void flip() = 0;

    virtual void rotate() = 0;

    virtual void rotate_90() = 0;

    virtual void rotate_180() = 0;

    virtual void rotate_270() = 0;

    virtual void rotate_360() = 0;

    virtual void darken_and_lighten() = 0;

    virtual void detect_edges() = 0;

    virtual void enlarge_upper_left() = 0;

    virtual void enlarge_upper_right() = 0;

    virtual void enlarge_lower_left() = 0;

    virtual void enlarge_lower_right() = 0;

    virtual void enlarge() = 0;

    virtual void shrink() = 0;

    virtual void shrink_half() = 0;

    virtual void shrink_quarter() = 0;

    virtual void shrink_third() = 0;

    virtual void shuffle() = 0;

    virtual void mirror() = 0;

    virtual void mirrorLeft() = 0;

    virtual void mirrorRight() = 0;

    virtual void mirrorUpper() = 0;

    virtual void mirrorDown() = 0;

    virtual void blur() = 0;

    virtual void crop() = 0;

    virtual void skew_horizontal() = 0;

    virtual void skew_vertical() = 0;

public:
    void run();
};

void Image::run() {
    loadImage();
    while (true) {
        char option = options();
        if (option == '0')
            break;
        imageProcessor(option);
    }
    saveImage();
}

#endif //IMAGE_PROCESSOR_IMAGE_H
