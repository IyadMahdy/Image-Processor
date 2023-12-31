
#include "ColoredImageProcessor.h"

void ColoredImageProcessor::loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}

//_________________________________________
void ColoredImageProcessor::saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

//_________________________________________

char ColoredImageProcessor::options() {
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

void ColoredImageProcessor::imageProcessor(char option) {
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
void ColoredImageProcessor::black_and_white() {
    for (auto &row: image) {
        for (auto &pixel: row) {
            if (pixel[0] + pixel[1] + pixel[2] > (SIZE * 3) / 2)
                pixel[0] = 255, pixel[1] = 255, pixel[2] = 255;
            else
                pixel[0] = 0, pixel[1] = 0, pixel[2] = 0;
        }
    }
}

//Invert the image colors by subtracting the pixel value from 255
void ColoredImageProcessor::invert() {
    for (auto &row: image) {
        for (auto &pixel: row) {
            for (unsigned char &color: pixel) {
                color = 255 - color;
            }
        }
    }
}

//Merges two images by taking the average value of the corresponding pixels in each image
void ColoredImageProcessor::merge() {
    unsigned char image2[SIZE][SIZE][RGB];
    char imageFileName[100];
    cout << "Enter another source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = (image[i][j][k] + image2[i][j][k]) / 2;
            }
        }
    }
}

//Flips the image vertically by swaping the pixel with its corresponding pixel from the end of its row,
// and horizontally by swaping the pixel with its corresponding pixel from the end of its column
void ColoredImageProcessor::flip() {
    char choice;

    cout << "1- Flip Horizontally\n" << "2- Flip vertically\n" << "Choice: ";
    cin >> choice;

    if (choice == '2')
        for (auto &i: image) {
            for (int j = 0; j < SIZE / 2; ++j) {
                swap(i[j][0], i[SIZE - j - 1][0]),
                        swap(i[j][1], i[SIZE - j - 1][1]),
                        swap(i[j][2], i[SIZE - j - 1][2]);
            }
        }
    else if (choice == '1') {
        for (int i = 0; i < SIZE / 2; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                swap(image[i][j][0], image[SIZE - i - 1][j][0]),
                        swap(image[i][j][1], image[SIZE - i - 1][j][1]),
                        swap(image[i][j][2], image[SIZE - i - 1][j][2]);
            }
        }
    } else
        cout << "Invalid choice";
}

//Makes the columns, rows, and the rows, inverse of the columns
void ColoredImageProcessor::rotate_90() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[255 - j][i][k];
            }
        }
    }
}

//Changes the row to 255 - row and column to 255-column
void ColoredImageProcessor::rotate_180() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[255 - i][255 - j][k];
            }
        }
    }
}

//copy pixels from the original image to a temporary image in reverse order
void ColoredImageProcessor::rotate_270() {
    for (int i = 255; i >= 0; --i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[j][i][k];
            }
        }
    }
}

//Returns the original image
void ColoredImageProcessor::rotate_360() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[i][j][k];
            }
        }
    }
}

//Gives the user 4 options to choose the angle of rotation
void ColoredImageProcessor::rotate() {
    cout << "Rotate (90), (180), (270) or (360) degrees?" << '\n';
    int degree;
    cout << "Choice: ";
    cin >> degree;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                imageCopy[i][j][k] = image[i][j][k];
            }
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
void ColoredImageProcessor::darken_and_lighten() {
    cout << "1- Darken Image" << endl;
    cout << "2- Lighten Image" << endl;
    char d_l;
    cout << "Your Choice : ";
    cin >> d_l;

    switch (d_l) {
        case '1':
            for (auto &i: image) {
                for (auto &j: i) {
                    for (unsigned char &k: j) {
                        if (k > 2)
                            k = k - (k / 2);
                    }
                }
            }
            break;

        case '2':
            for (auto &i: image) {
                for (auto &j: i) {
                    for (unsigned char &k: j) {
                        if (k < 196)
                            k += 60;
                    }
                }
            }
            break;
        default:
            break;
    }
}

//Sobel Operators are used to detect the x and y gradients of the image Forming a boolean image where 1 is an edge
// and 0 isn’t an edge Filling up the images with black and white
void ColoredImageProcessor::detect_edges() {
    int bw_image[SIZE][SIZE];
    int sum;

    // Convert RGB into Black and White
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            sum = 0;
            for (int k = 0; k < RGB; ++k)
                sum += image[i][j][k];
            if (sum >= (SIZE * 3) / 2)
                bw_image[i][j] = 255;
            else
                bw_image[i][j] = 0;
        }
    }

    // Using same algorithm for Black and White Edge Detection
    int gradient_x[SIZE][SIZE];
    int gradient_y[SIZE][SIZE];

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            // Apply the Sobel operator to the pixel.
            int sobel_x = 0;
            int sobel_y = 0;

            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sobel_x += SOBEL_X[k + 1][l + 1] * bw_image[i + k][j + l];
                    sobel_y += SOBEL_Y[k + 1][l + 1] * bw_image[i + k][j + l];
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
                    (gradient_x[i][j] * gradient_x[i][j] + gradient_y[i][j] * gradient_y[i][j]) > 0.5 * 0.5;
        }
    }

    int new_image[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (edge_detector[i][j] && (edge_detector[i + 1][j] || edge_detector[i - 1][j] || edge_detector[i][j + 1] ||
                                        edge_detector[i][j - 1])) {
                new_image[i][j] = 0;
            } else {
                new_image[i][j] = 255;
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j][0] = new_image[i][j],
            image[i][j][1] = new_image[i][j],
            image[i][j][2] = new_image[i][j];
        }
    }
}

//Enlarges the image by putting the same pixel of the upper left quarter two times next to itself.
void ColoredImageProcessor::enlarge_upper_left() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            for (int k = 0; k < RGB; ++k) {
                imageCopy[i][j][k] = image[i / 2][j / 2][k];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[i][j][k];
            }
        }
    }
}

//Enlarges the image by putting the same pixel of the upper right quarter two times next to itself.
void ColoredImageProcessor::enlarge_upper_right() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            for (int k = 0; k < RGB; ++k) {
                imageCopy[i][j][k] = image[i / 2][j / 2 + 127][k];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[i][j][k];
            }
        }
    }
}

//Enlarges the image by putting the same pixel of the lower left quarter two times next to itself.
void ColoredImageProcessor::enlarge_lower_left() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            for (int k = 0; k < RGB; ++k) {
                imageCopy[i][j][k] = image[i / 2 + 127][j / 2][k];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[i][j][k];
            }
        }
    }
}

//Enlarges the image by putting the same pixel of the lower right quarter two times next to itself
void ColoredImageProcessor::enlarge_lower_right() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            for (int k = 0; k < RGB; ++k) {
                imageCopy[i][j][k] = image[i / 2 + 127][j / 2 + 127][k];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[i][j][k];
            }
        }
    }
}

//Shows the user 4 options to choose which to enlarge
void ColoredImageProcessor::enlarge() {
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
void ColoredImageProcessor::shrink_half() {
    int cnt1 = 0; //take the average of 4 adjacent pixels together
    for (int i = 0; i < SIZE - 2; i += 2) {
        int cnt2 = 0;
        for (int j = 0; j < SIZE - 2; j += 2) {
            for (int k = 0; k < RGB; ++k) {
                image[cnt1][cnt2][k] = (imageCopy[i][j][k] + imageCopy[i + 1][j][k] + imageCopy[i][j + 1][k] +
                                        imageCopy[i + 1][j + 1][k]) / 4;
            }
            cnt2++;
        }
        cnt1++;
    }
}

//Shrinks the image to quarter by applying the shrink half logic two times.
void ColoredImageProcessor::shrink_quarter() {
    int cnt1 = 0; //take the average of 4 adjacent pixels together for two times
    for (int i = 0; i < SIZE - 2; i += 2) {
        int cnt2 = 0;
        for (int j = 0; j < SIZE - 2; j += 2) {
            for (int k = 0; k < RGB; ++k) {
                image[cnt1][cnt2][k] = (imageCopy[i][j][k] + imageCopy[i + 1][j][k] + imageCopy[i][j + 1][k] +
                                        imageCopy[i + 1][j + 1][k]) / 4;
            }
            cnt2++;
        }
        cnt1++;
    }
    int cnt3 = 0;
    for (int i = 0; i < SIZE - 2; i += 2) {
        int cnt4 = 0;
        for (int j = 0; j < SIZE - 2; j += 2) {
            for (int k = 0; k < RGB; ++k) {
                image[cnt3][cnt4][k] =
                        (image[i][j][k] + image[i + 1][j][k] + image[i][j + 1][k] + image[i + 1][j + 1][k]) / 4;
            }
            cnt4++;
        }
        cnt3++;
    }
}

//Shrinks the image to third by taking the average of 9 adjacent pixels.
void ColoredImageProcessor::shrink_third() {
    int cnt1 = 0; //take the average of 9 adjacent pixels together
    for (int i = 0; i < SIZE - 2; i += 3) {
        int cnt2 = 0;
        for (int j = 0; j < SIZE - 2; j += 3) {
            for (int k = 0; k < RGB; ++k) {
                image[cnt1][cnt2][k] =
                        (imageCopy[i][j][k] + imageCopy[i + 1][j][k] + imageCopy[i + 2][j][k] + imageCopy[i + 1][j][k] +
                         imageCopy[i + 1][j + 1][k] + imageCopy[i + 1][j + 2][k] + imageCopy[i + 2][j][k] +
                         imageCopy[i + 2][j + 1][k] + imageCopy[i + 2][j + 2][k]) / 9;
            }
            cnt2++;
        }
        cnt1++;
    }
}

//Shows the user 3 ratios to shrink the image with
void ColoredImageProcessor::shrink() {
    cout << "Shrink to (1/2) , (1/3) or (1/4) ?" << '\n';
    string choice;
    cout << "Choice: ";
    cin >> choice;
    for (int i = 0; i < SIZE; ++i) { //make a copy of the image and make the original image white
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < RGB; ++k) {
                imageCopy[i][j][k] = image[i][j][k];
                image[i][j][k] = 255;
            }
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
void ColoredImageProcessor::shuffle() {
    unsigned char upper_left[SIZE][SIZE][RGB];
    unsigned char upper_right[SIZE][SIZE][RGB];
    unsigned char lower_left[SIZE][SIZE][RGB];
    unsigned char lower_right[SIZE][SIZE][RGB];
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
            for (int k = 0; k < RGB; ++k) {
                upper_left[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 0; i < 128; ++i) {
        for (int j = 128; j < 256; ++j) {
            for (int k = 0; k < RGB; ++k) {
                upper_right[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 128; i < 256; ++i) {
        for (int j = 0; j < 128; ++j) {
            for (int k = 0; k < RGB; ++k) {
                lower_left[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 128; i < 256; ++i) {
        for (int j = 128; j < 256; ++j) {
            for (int k = 0; k < RGB; ++k) {
                lower_right[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (i == 0) { //choose which quarter of the original image to add to the first quarter of the new image
            for (int j = 0; j < 128; ++j) {
                for (int k = 0; k < 128; ++k) {
                    for (int l = 0; l < RGB; ++l) {
                        if (v[0] == 1)
                            imageCopy[j][k][l] = upper_left[j][k][l];
                        else if (v[0] == 2)
                            imageCopy[j][k][l] = upper_right[j][k + 128][l];
                        else if (v[0] == 3)
                            imageCopy[j][k][l] = lower_left[j + 128][k][l];
                        else if (v[0] == 4)
                            imageCopy[j][k][l] = lower_right[j + 128][k + 128][l];
                    }
                }
            }
        } else if (i == 1) { //choose which quarter of the original image to add to the second quarter of the new image
            for (int j = 0; j < 128; ++j) {
                for (int k = 128; k < 256; ++k) {
                    for (int l = 0; l < RGB; ++l) {
                        if (v[1] == 1)
                            imageCopy[j][k][l] = upper_left[j][k - 128][l];
                        else if (v[1] == 2)
                            imageCopy[j][k][l] = upper_right[j][k][l];
                        else if (v[1] == 3)
                            imageCopy[j][k][l] = lower_left[j + 128][k - 128][l];
                        else if (v[1] == 4)
                            imageCopy[j][k][l] = lower_right[j + 128][k][l];
                    }
                }
            }
        } else if (i == 2) { //choose which quarter of the original image to add to the third quarter of the new image
            for (int j = 128; j < 256; ++j) {
                for (int k = 0; k < 128; ++k) {
                    for (int l = 0; l < RGB; ++l) {
                        if (v[2] == 1)
                            imageCopy[j][k][l] = upper_left[j - 128][k][l];
                        else if (v[2] == 2)
                            imageCopy[j][k][l] = upper_right[j - 128][k + 128][l];
                        else if (v[2] == 3)
                            imageCopy[j][k][l] = lower_left[j][k][l];
                        else if (v[2] == 4)
                            imageCopy[j][k][l] = lower_right[j][k + 128][l];
                    }
                }
            }
        } else if (i == 3) { //choose which quarter of the original image to add to the fourth quarter of the new image
            for (int j = 128; j < 256; ++j) {
                for (int k = 128; k < 256; ++k) {
                    for (int l = 0; l < RGB; ++l) {
                        if (v[3] == 1)
                            imageCopy[j][k][l] = upper_left[j - 128][k - 128][l];
                        else if (v[3] == 2)
                            imageCopy[j][k][l] = upper_right[j - 128][k][l];
                        else if (v[3] == 3)
                            imageCopy[j][k][l] = lower_left[j][k - 128][l];
                        else if (v[3] == 4)
                            imageCopy[j][k][l] = lower_right[j][k][l];
                    }
                }
            }
        }
    }
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[i][j][k];
            }
        }
    }
}

//Gives the user 4 options to choose which half to mirror
void ColoredImageProcessor::mirror() {
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
void ColoredImageProcessor::mirrorLeft() {
    for (auto &i: image) {
        for (int j = 0; j < SIZE / 2; j++) {
            for (int k = 0; k < RGB; ++k) {
                i[255 - j][k] = i[j][k];
            }
        }
    }
}

//Makes the left pixel in the row equal to the corresponding right pixel in the same row
void ColoredImageProcessor::mirrorRight() {
    for (auto &i: image) {
        for (int j = 0; j < SIZE / 2; j++) {
            for (int k = 0; k < RGB; ++k) {
                i[j][k] = i[255 - j][k];
            }
        }
    }
}

//Makes the down pixel in the column equal to the corresponding upper pixel in the same column
void ColoredImageProcessor::mirrorUpper() {
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[255 - i][j][k] = image[i][j][k];
            }
        }
    }
}

//Makes the upper pixel in the column equal to the corresponding down pixel in the same column
void ColoredImageProcessor::mirrorDown() {
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = image[255 - i][j][k];
            }
        }
    }
}

//Takes the average of the corresponding pixels with respect to the intensity
void ColoredImageProcessor::blur() {
    int intensity = 2;

    for (int i = intensity; i < SIZE - intensity; i++) {
        for (int j = intensity; j < SIZE - intensity; j++) {
            for (int m = 0; m < RGB; ++m) {
                int avg = 0;
                // adding the color of these group of pixels then diving by the number of them
                for (int k = i - intensity; k <= i + intensity; k++) {
                    for (int l = j - intensity; l <= j + intensity; l++) {
                        avg += image[k][l][m];
                    }
                }
                avg /= (int) pow((2 * intensity + 1), 2);

                // filling the correspondent pixels with the blurred average in the new image
                for (int k = i - intensity; k <= i + intensity; k++) {
                    for (int l = j - intensity; l <= j + intensity; l++) {
                        image[k][l][m] = avg;
                    }
                }
            }
        }
    }
}

//crops an image from the original image and copies the cropped image back to the original image.
// The cropping region is defined by the user's input.
void ColoredImageProcessor::crop() {
    int cropped_image[SIZE][SIZE][RGB];
    int x, y, l, w;

    for (auto &i: cropped_image) {
        for (auto &j: i) {
            j[0] = 255,
            j[1] = 255,
            j[2] = 255;
        }
    }

    cout << "Enter the point to start cropping from (x, y): ";
    cin >> x >> y;
    cout << "Enter the length and width (l, w): ";
    cin >> l >> w;

    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + l; j++) {
            cropped_image[i][j][0] = image[i][j][0],
            cropped_image[i][j][1] = image[i][j][1],
            cropped_image[i][j][2] = image[i][j][2];
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j][0] = cropped_image[i][j][0],
            image[i][j][1] = cropped_image[i][j][1],
            image[i][j][2] = cropped_image[i][j][2];
        }
    }
}

void ColoredImageProcessor::skew_horizontal() {
    // Create a temporary image to store the shrunken image.
    unsigned char temp_image[SIZE][SIZE][RGB];

// Initialize the image copy to all white pixels.
    for (auto &i: imageCopy) {
        for (auto &j: i) {
            for (unsigned char &k: j) {
                k = 255;
            }
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
            for (int k = 0; k < RGB; ++k) {
                if (i * scaling_factor <= 255) {
                    temp_image[i][j][k] = image[i * (int) scaling_factor][j][k];
                }
            }
        }
    }

// Shift the pixels of the shrunken image to the left by the shift distance.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < (255 / (1 + (1 / skewFactor))); ++j) {
            for (int k = 0; k < RGB; ++k) {
                imageCopy[j + (int) shift_distance][i][k] = temp_image[j][i][k];
            }
        }
        shift_distance -= slope;
    }

// Copy the shifted image back to the original image.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[i][j][k];
            }
        }
    }
}

void ColoredImageProcessor::skew_vertical() {
    // Create a temporary image to store the shrunken image.
    unsigned char temp_image[SIZE][SIZE][RGB];

// Initialize the image copy to all white pixels.
    for (auto &i: imageCopy) {
        for (auto &j: i) {
            for (unsigned char &k: j) {
                k = 255;
            }
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
            for (int k = 0; k < RGB; ++k) {
                if (j * scaling_factor <= 255) {
                    temp_image[i][j][k] = image[i][j * (int) scaling_factor][k];
                }
            }
        }
    }

// Shift the pixels of the shrunken image to the left by the shift_distance factor.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < (255 / (1 + (1 / skewFactor))); ++j) {
            for (int k = 0; k < RGB; ++k) {
                imageCopy[i][j + (int) shift_distance][k] = temp_image[i][j][k];
            }
        }
        shift_distance -= slope;
    }

// Copy the shifted image back to the original image.
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < RGB; ++k) {
                image[i][j][k] = imageCopy[i][j][k];
            }
        }
    }
}