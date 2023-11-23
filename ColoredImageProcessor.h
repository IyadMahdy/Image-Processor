/*
 FCAI – OOP Programming – 2023 - Assignment 1
 Program Name: RGB_image_source_code.cpp
 Last Modification Date: 18/10/2023
 Author1 and ID and Group: Kirolos Adel Nan     20220253   B
 Author2 and ID and Group: Mario Michel Magdy   20220266   A
 Author3 and ID and Group: Iyad Mahdy Mahrous   20220075   A
 Purpose: A cpp program for image processing to apply 15 filters on Grey Bitmap images of 256x256 size
*/
#ifndef IMAGE_PROCESSOR_COLOREDIMAGEPROCESSOR_H
#define IMAGE_PROCESSOR_COLOREDIMAGEPROCESSOR_H

#include "Image.h"

class ColoredImageProcessor : public Image {
private:
    unsigned char image[SIZE][SIZE][RGB]{};
    unsigned char imageCopy[SIZE][SIZE][RGB]{};
protected:
    void loadImage() override;

    void saveImage() override;

    char options() override;

    void imageProcessor(char option) override;

    void black_and_white() override;

    void invert() override;

    void merge() override;

    void flip() override;

    void rotate() override;

    void rotate_90() override;

    void rotate_180() override;

    void rotate_270() override;

    void rotate_360() override;

    void darken_and_lighten() override;

    void detect_edges() override;

    void enlarge_upper_left() override;

    void enlarge_upper_right() override;

    void enlarge_lower_left() override;

    void enlarge_lower_right() override;

    void enlarge() override;

    void shrink() override;

    void shrink_half() override;

    void shrink_quarter() override;

    void shrink_third() override;

    void shuffle() override;

    void mirrorLeft() override;

    void mirrorRight() override;

    void mirrorUpper() override;

    void mirrorDown() override;

    void mirror() override;

    void blur() override;

    void crop() override;

    void skew_horizontal() override;

    void skew_vertical() override;
};


#endif //IMAGE_PROCESSOR_COLOREDIMAGEPROCESSOR_H
