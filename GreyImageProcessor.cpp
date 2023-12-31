/*
 FCAI – OOP Programming – 2023 - Assignment 1
 Program Name: RGB_image_source_code.cpp
 Last Modification Date: 18/10/2023
 Author1 and ID and Group: Kirolos Adel Nan     20220253   B
 Author2 and ID and Group: Mario Michel Magdy   20220266   A
 Author3 and ID and Group: Iyad Mahdy Mahrous   20220075   A
 Purpose: A cpp program for image processing to apply 15 filters on Grey Bitmap images of 256x256 size
 */
#include "GreyImageProcessor.h"

void GreyImageProcessor::loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void GreyImageProcessor::saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

char GreyImageProcessor::options() {
    char choice;

    cout << "Options:" << endl;
    cout << "1- Black and white image" << endl;
    cout << "2- Invert image" << endl;
    cout << "3- Merge images" << endl;
    cout << "4- Flip image" << endl;
    cout << "5- Rotate image" << endl;
    cout << "6- Darken and lighten image" << endl;
    cout << "7- Detect image edges" << endl;
    cout << "8- Enlarge image" << endl;
    cout << "9- Shrink image" << endl;
    cout << "a- Mirror image" << endl;
    cout << "b- Shuffle image" << endl;
    cout << "c- Blur image" << endl;
    cout << "d- Crop image" << endl;
    cout << "e- Skew horizontally" << endl;
    cout << "f- Skew vertically" << endl;
    cout << "0- Exit & save changes" << endl;

    cout << "Choice: ";
    cin >> choice;

    return choice;
}

void GreyImageProcessor::imageProcessor(char option) {
    switch (option) {
        case '1':
            black_and_white();
            break;

        case '2':
            invert();
            break;

        case '3':
            merge();
            break;

        case '4':
            flip();
            break;

        case '5':
            rotate();
            break;

        case '6':
            darken_and_lighten();
            break;

        case '7':
            detect_edges();
            break;

        case '8':
            enlarge();
            break;

        case '9':
            shrink();
            break;

        case 'a':
            mirror();
            break;

        case 'b':
            shuffle();
            break;

        case 'c':
            blur();
            break;

        case 'd':
            crop();
            break;

        case 'e':
            skew_horizontal();
            break;

        case 'f':
            skew_vertical();
            break;

        default:
            return;
    }
}

//Changes image colors to black and white only if pixel value > 127 makes it white else makes it black
void GreyImageProcessor::black_and_white() {
    for (auto &row: image) {
        for (unsigned char &pixel: row) {
            if (pixel > 127)
                pixel = 255;
            else
                pixel = 0;
        }
    }
}

//Invert the image colors by subtracting the pixel value from 255
void GreyImageProcessor::invert() {
    for (auto &row: image) {
        for (unsigned char &pixel: row) {
            pixel = 255 - pixel;
        }
    }
}

//Merges two images by taking the average value of the corresponding pixels in each image
void GreyImageProcessor::merge() {
    unsigned char image2[SIZE][SIZE];
    char imageFileName[100];
    cout << "Enter another source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
}

//Flips the image vertically by swapping the pixel with its corresponding pixel from the end of its row,
// and horizontally by swapping the pixel with its corresponding pixel from the end of its column
void GreyImageProcessor::flip() {
    char choice;

    cout << "1- Flip Horizontally\n" << "2- Flip vertically\n" << "Choice: ";
    cin >> choice;

    if (choice == '2')
        for (auto &i: image) {
            for (int j = 0; j < SIZE / 2; ++j) {
                swap(i[j], i[SIZE - j - 1]);
            }
        }
    else if (choice == '1') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                swap(image[i][j], image[SIZE - i - 1][j]);
            }
        }
    } else
        cout << "Invalid choice";
}

//Makes the columns, rows, and the rows, inverse of the columns
void GreyImageProcessor::rotate_90() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            image[i][j] = imageCopy[255 - j][i];
        }
    }
}

//Changes the row to 255 - row and column to 255-column
void GreyImageProcessor::rotate_180() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            image[i][j] = imageCopy[255 - i][255 - j];
        }
    }
}

//copy pixels from the original image to a temporary image in reverse order
void GreyImageProcessor::rotate_270() {
    for (int i = 255; i >= 0; --i) {
        for (int j = 0; j < 256; ++j) {
            image[i][j] = imageCopy[j][i];
        }
    }
}

//Returns the original image
void GreyImageProcessor::rotate_360() {
    for (auto &row: image) {
        for (unsigned char &pixel: row) {
            pixel = pixel;
        }
    }
}

//Gives the user 4 options to choose the angle of rotation
void GreyImageProcessor::rotate() {
    cout << "Rotate (90), (180), (270) or (360) degrees?" << '\n';
    int degree;
    cout << "Choice: ";
    cin >> degree;
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            imageCopy[i][j] = image[i][j];
        }
    }
    if (degree == 90) {
        rotate_90();
    } else if (degree == 180) {
        rotate_180();
    } else if (degree == 270) {
        rotate_270();
    } else {
        rotate_360();
    }
}

//Darken the image by subtracting from the pixel half its value, and lightens the image by adding 60 to the pixel
void GreyImageProcessor::darken_and_lighten() {
    cout << "1- Darken Image" << endl;
    cout << "2- Lighten Image" << endl;
    char d_l;
    cout << "Your Choice : ";
    cin >> d_l;

    switch (d_l) {
        case '1':
            for (auto &row: image) {
                for (unsigned char &pixel: row) {
                    if (pixel > 2)
                        pixel = pixel - (pixel / 2);
                }
            }
            break;

        case '2':
            for (auto &row: image) {
                for (unsigned char &pixel: row) {
                    if (pixel < 196)
                        pixel += 60;
                }
            }
            break;
        default:
            break;
    }
}

//Sobel Operators are used to detect the x and y gradients of the image Forming a boolean image where 1 is an edge
// and 0 isn’t an edge Filling up the images with black and white
void GreyImageProcessor::detect_edges() {
    black_and_white();

    int gradient_x[SIZE][SIZE];
    int gradient_y[SIZE][SIZE];

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            // Apply the Sobel operator to the pixel.
            int sobel_x = 0;
            int sobel_y = 0;

            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sobel_x += SOBEL_X[k + 1][l + 1] * image[i + k][j + l];
                    sobel_y += SOBEL_Y[k + 1][l + 1] * image[i + k][j + l];
                }
            }

            // Compute the magnitude of the gradient.
            gradient_x[i][j] = sobel_x;
            gradient_y[i][j] = sobel_y;
        }
    }

    // 2-D Boolean Array to identify the image that are edges
    bool edge_detector[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            edge_detector[i][j] =
                    (gradient_x[i][j] * gradient_x[i][j] + gradient_y[i][j] * gradient_y[i][j])
                    > 0.5 * 0.5;
        }
    }

    int new_image[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (edge_detector[i][j] &&
                (edge_detector[i + 1][j] || edge_detector[i - 1][j] || edge_detector[i][j + 1] ||
                 edge_detector[i][j - 1])) {
                new_image[i][j] = 0;
            } else {
                new_image[i][j] = 255;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = new_image[i][j];
        }
    }
}

//Enlarges the image by putting the same pixel of the upper left quarter two times next to itself.
void GreyImageProcessor::enlarge_upper_left() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            imageCopy[i][j] = image[i / 2][j / 2];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = imageCopy[i][j];
        }
    }
}

//Enlarges the image by putting the same pixel of the upper right quarter two times next to itself.
void GreyImageProcessor::enlarge_upper_right() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            imageCopy[i][j] = image[i / 2][j / 2 + 127];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = imageCopy[i][j];
        }
    }
}

//Enlarges the image by putting the same pixel of the lower left quarter two times next to itself.
void GreyImageProcessor::enlarge_lower_left() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            imageCopy[i][j] = image[i / 2 + 127][j / 2];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = imageCopy[i][j];
        }
    }
}

//Enlarges the image by putting the same pixel of the lower right quarter two times next to itself
void GreyImageProcessor::enlarge_lower_right() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            imageCopy[i][j] = image[i / 2 + 127][j / 2 + 127];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = imageCopy[i][j];
        }
    }
}

//Shows the user 4 options to choose which to enlarge
void GreyImageProcessor::enlarge() {
    cout << "Options: " << '\n';
    cout << "1- Upper left" << '\n';
    cout << "2- Upper right" << '\n';
    cout << "3- Lower left" << '\n';
    cout << "4- Lower Right" << '\n';
    char choice{};
    cout << "Enter the quarter you want to change: " << '\n';
    cin >> choice;
    if (choice == '1')
        enlarge_upper_left();
    else if (choice == '2')
        enlarge_upper_right();
    else if (choice == '3')
        enlarge_lower_left();
    else if (choice == '4')
        enlarge_lower_right();
}

//Shrinks the image to half by taking the average of 4 adjacent pixels.
void GreyImageProcessor::shrink_half() {
    int cnt1 = 0; //take the average of 4 adjacent pixels together
    for (int i = 0; i < SIZE - 2; i += 2) {
        int cnt2 = 0;
        for (int j = 0; j < SIZE - 2; j += 2) {
            image[cnt1][cnt2] =
                    (imageCopy[i][j] + imageCopy[i + 1][j] + imageCopy[i][j + 1] + imageCopy[i + 1][j + 1]) / 4;
            cnt2++;
        }
        cnt1++;
    }
}

//Shrinks the image to quarter by applying the shrink half logic two times.
void GreyImageProcessor::shrink_quarter() {
    int cnt1 = 0; //take the average of 4 adjacent pixels together for two times
    for (int i = 0; i < SIZE - 2; i += 2) {
        int cnt2 = 0;
        for (int j = 0; j < SIZE - 2; j += 2) {
            image[cnt1][cnt2] =
                    (imageCopy[i][j] + imageCopy[i + 1][j] + imageCopy[i][j + 1] + imageCopy[i + 1][j + 1]) / 4;
            cnt2++;
        }
        cnt1++;
    }
    int cnt3 = 0;
    for (int i = 0; i < SIZE - 2; i += 2) {
        int cnt4 = 0;
        for (int j = 0; j < SIZE - 2; j += 2) {
            image[cnt3][cnt4] = (image[i][j] + image[i + 1][j] + image[i][j + 1] + image[i + 1][j + 1]) / 4;
            cnt4++;
        }
        cnt3++;
    }
}

//Shrinks the image to third by taking the average of 9 adjacent pixels.
void GreyImageProcessor::shrink_third() {
    int cnt1 = 0; //take the average of 9 adjacent pixels together
    for (int i = 0; i < SIZE - 2; i += 3) {
        int cnt2 = 0;
        for (int j = 0; j < SIZE - 2; j += 3) {
            image[cnt1][cnt2] = (imageCopy[i][j] + imageCopy[i + 1][j] + imageCopy[i + 2][j] + imageCopy[i + 1][j] +
                                 imageCopy[i + 1][j + 1] + imageCopy[i + 1][j + 2] + imageCopy[i + 2][j] +
                                 imageCopy[i + 2][j + 1] + imageCopy[i + 2][j + 2]) / 9;
            cnt2++;
        }
        cnt1++;
    }
}

//Shows the user 3 ratios to shrink the image width.
void GreyImageProcessor::shrink() {
    cout << "Shrink to (1/2) , (1/3) or (1/4) ?" << '\n';
    string choice;
    cout << "Choice: ";
    cin >> choice;
    for (int i = 0; i < SIZE; ++i) { //make a copy of the image and make the original image white
        for (int j = 0; j < SIZE; ++j) {
            imageCopy[i][j] = image[i][j];
            image[i][j] = 255;
        }
    }
    if (choice == "1/2")
        shrink_half();
    else if (choice == "1/4")
        shrink_quarter();
    else if (choice == "1/3")
        shrink_third();

}

//Shuffles the four quarters of the images by the chosen order the user enters
void GreyImageProcessor::shuffle() {
    unsigned char upper_left[SIZE][SIZE];
    unsigned char upper_right[SIZE][SIZE];
    unsigned char lower_left[SIZE][SIZE];
    unsigned char lower_right[SIZE][SIZE];
    cout << "Enter the new order of quarters: ";
    vector<int> v;
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
        int num;
        cin >> num;
        if (1 <= num && num <= 4)
            v.push_back(num), cnt++;
    }
    auto it = unique(v.begin(), v.begin() + cnt);
    v.resize(distance(v.begin(), it));
    if (v.size() != 4) { //check if the vector has only numbers from 1 to 4
        cout << "Invalid order save the original image and try again" << '\n';
        return;
    }
    //add each quarter of the original image to a separate 2d array
    for (int i = 0; i < 128; ++i) {
        for (int j = 0; j < 128; ++j) {
            upper_left[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < 128; ++i) {
        for (int j = 128; j < 256; ++j) {
            upper_right[i][j] = image[i][j];
        }
    }
    for (int i = 128; i < 256; ++i) {
        for (int j = 0; j < 128; ++j) {
            lower_left[i][j] = image[i][j];
        }
    }
    for (int i = 128; i < 256; ++i) {
        for (int j = 128; j < 256; ++j) {
            lower_right[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (i == 0) { //choose which quarter of the original image to add to the first quarter of the new image
            for (int j = 0; j < 128; ++j) {
                for (int k = 0; k < 128; ++k) {
                    if (v[0] == 1)
                        imageCopy[j][k] = upper_left[j][k];
                    else if (v[0] == 2)
                        imageCopy[j][k] = upper_right[j][k + 128];
                    else if (v[0] == 3)
                        imageCopy[j][k] = lower_left[j + 128][k];
                    else if (v[0] == 4)
                        imageCopy[j][k] = lower_right[j + 128][k + 128];
                }
            }
        } else if (i ==
                   1) { //choose which quarter of the original image to add to the second quarter of the new image
            for (int j = 0; j < 128; ++j) {
                for (int k = 128; k < 256; ++k) {
                    if (v[1] == 1)
                        imageCopy[j][k] = upper_left[j][k - 128];
                    else if (v[1] == 2)
                        imageCopy[j][k] = upper_right[j][k];
                    else if (v[1] == 3)
                        imageCopy[j][k] = lower_left[j + 128][k - 128];
                    else if (v[1] == 4)
                        imageCopy[j][k] = lower_right[j + 128][k];
                }
            }
        } else if (i ==
                   2) { //choose which quarter of the original image to add to the third quarter of the new image
            for (int j = 128; j < 256; ++j) {
                for (int k = 0; k < 128; ++k) {
                    if (v[2] == 1)
                        imageCopy[j][k] = upper_left[j - 128][k];
                    else if (v[2] == 2)
                        imageCopy[j][k] = upper_right[j - 128][k + 128];
                    else if (v[2] == 3)
                        imageCopy[j][k] = lower_left[j][k];
                    else if (v[2] == 4)
                        imageCopy[j][k] = lower_right[j][k + 128];
                }
            }
        } else if (i ==
                   3) { //choose which quarter of the original image to add to the fourth quarter of the new image
            for (int j = 128; j < 256; ++j) {
                for (int k = 128; k < 256; ++k) {
                    if (v[3] == 1)
                        imageCopy[j][k] = upper_left[j - 128][k - 128];
                    else if (v[3] == 2)
                        imageCopy[j][k] = upper_right[j - 128][k];
                    else if (v[3] == 3)
                        imageCopy[j][k] = lower_left[j][k - 128];
                    else if (v[3] == 4)
                        imageCopy[j][k] = lower_right[j][k];
                }
            }
        }
    }
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            image[i][j] = imageCopy[i][j];
        }
    }
}

//Gives the user 4 options to choose which half to mirror
void GreyImageProcessor::mirror() {
    cout << "mirror (l)eft , (r)ight, (u)pper, (d)own" << endl;
    char choice;
    cout << "Choice: ";
    cin >> choice;
    if (choice == 'l')
        mirrorLeft();
    else if (choice == 'r')
        mirrorRight();
    else if (choice == 'u')
        mirrorUpper();
    else if (choice == 'd')
        mirrorDown();
    else
        cout << "Invalid Choice" << endl;
}

//Makes the right pixel in the row equal to the corresponding left pixel in the same row
void GreyImageProcessor::mirrorLeft() {
    for (auto &i: image) {
        for (int j = 0; j < SIZE / 2; j++) {
            i[255 - j] = i[j];
        }
    }
}

//Makes the left pixel in the row equal to the corresponding right pixel in the same row
void GreyImageProcessor::mirrorRight() {
    for (auto &i: image) {
        for (int j = 0; j < SIZE / 2; j++) {
            i[j] = i[255 - j];
        }
    }
}

//Makes the down pixel in the column equal to the corresponding upper pixel in the same column
void GreyImageProcessor::mirrorUpper() {
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[255 - i][j] = image[i][j];
        }
    }
}

//Makes the upper pixel in the column equal to the corresponding down pixel in the same column
void GreyImageProcessor::mirrorDown() {
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image[255 - i][j];
        }
    }
}

//Takes the average of the corresponding pixels with respect to the intensity
void GreyImageProcessor::blur() {
    int intensity = 2;

    for (int i = intensity; i < SIZE - intensity; i++) {
        for (int j = intensity; j < SIZE - intensity; j++) {
            int avg = 0;

            // adding the color of these group of pixels then diving by the number of them
            for (int k = i - intensity; k <= i + intensity; k++) {
                for (int l = j - intensity; l <= j + intensity; l++) {
                    avg += image[k][l];
                }
            }
            avg /= (int) pow((2 * intensity + 1), 2);

            // filling the correspondent pixels with the blurred average in the new image
            for (int k = i - intensity; k <= i + intensity; k++) {
                for (int l = j - intensity; l <= j + intensity; l++) {
                    image[k][l] = avg;
                }
            }
        }
    }
}

//crops an image from the original image and copies the cropped image back to the original image.
// The cropping region is defined by the user's input.
void GreyImageProcessor::crop() {
    int cropped_image[SIZE][SIZE];
    int x, y, l, w;

    for (auto &i: cropped_image) {
        for (int &j: i) {
            j = 255;
        }
    }

    cout << "Enter the point to start cropping from (x, y): ";
    cin >> x >> y;
    cout << "Enter the length and width (l, w): ";
    cin >> l >> w;

    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + l; j++) {
            cropped_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = cropped_image[i][j];
        }
    }
}

void GreyImageProcessor::skew_horizontal() {
    // Create a temporary image to store the shrunken image.
    unsigned char temp_image[SIZE][SIZE];

// Initialize the image copy to all white pixels.
    for (auto &i: imageCopy) {
        for (unsigned char &j: i) {
            j = 255;
        }
    }

// Read in the skew angle from the user and convert it to radians.
    double skew_degree;
    cout << "Please enter the skew skew_degree: ";
    cin >> skew_degree;
    skew_degree = 90 - skew_degree;
    double radians = skew_degree * M_PI / 180.0;

// Calculate the skew factor, which is the tangent of the rotation angle.
    double skewFactor = tan(radians);

// Calculate the scaling factor and the shift distance.
    double scaling_factor = 255 / (255 / (1 + (1 / skewFactor)));
    double shift_distance = SIZE - (255 / (1 + (1 / skewFactor)));
    double slope = shift_distance / SIZE;

// Shrink the original image and copy it to the temporary array.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i * scaling_factor <= 255) {
                temp_image[i][j] = image[i * (int) scaling_factor][j];
            }
        }
    }

// Shift the pixels of the shrunken image to the left by the shift distance.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < (255 / (1 + (1 / skewFactor))); ++j) {
            imageCopy[j + (int) shift_distance][i] = temp_image[j][i];
        }
        shift_distance -= slope;
    }

// Copy the shifted image back to the original image.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = imageCopy[i][j];
        }
    }
}

void GreyImageProcessor::skew_vertical() {
    // Create a temporary image to store the shrunken image.
    unsigned char temp_image[SIZE][SIZE];

// Initialize the image copy to all white pixels.
    for (auto &i: imageCopy) {
        for (unsigned char &j: i) {
            j = 255;
        }
    }

// Read in the skew angle from the user and convert it to radians.
    double skew_degree;
    cout << "Please enter the skew skew_degree: ";
    cin >> skew_degree;
    skew_degree = 90 - skew_degree;
    double radians = skew_degree * M_PI / 180.0;

// Calculate the skew factor, which is the tangent of the rotation angle.
    double skewFactor = tan(radians);

// Calculate the scaling_factor and the shift_distance.
    double scaling_factor = 255 / (255 / (1 + (1 / skewFactor)));
    double shift_distance = SIZE - (255 / (1 + (1 / skewFactor)));
    double slope = shift_distance / SIZE;

// Shrink the original image and copy it to the temporary array.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (j * scaling_factor <= 255) {
                temp_image[i][j] = image[i][j * (int) scaling_factor];
            }
        }
    }

// Shift the pixels of the shrunken image to the left by the shift_distance factor.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < (255 / (1 + (1 / skewFactor))); ++j) {
            imageCopy[i][j + (int) shift_distance] = temp_image[i][j];
        }
        shift_distance -= slope;
    }

// Copy the shifted image back to the original image.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = imageCopy[i][j];
        }
    }
}