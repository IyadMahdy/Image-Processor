#include <bits/stdc++.h>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char imageCopy[SIZE][SIZE];

void loadImage();

void saveImage();

void doSomethingForImage();

char options();

void imageProcessor(char option);

void black_and_white();

void invert();

void merge();

void flip();

void rotate();

void rotate_90();

void rotate_180();

void rotate_270();

void rotate_360();

void darken_and_lighten();

void detect_edges();

void enlarge_upper_left();

void enlarge_upper_right();

void enlarge_lower_left();

void enlarge_lower_right();

void enlarge();

void shrink();

void shuffle();

void mirror();

void blur();

void crop();

void skew_horizontal();

void skew_vertical();

//________________________________________

int main() {
    loadImage();
    doSomethingForImage();
    saveImage();
    return 0;
}

//_________________________________________
void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void doSomethingForImage() {
    char choice = options();
    imageProcessor(choice);
}

char options() {
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

    cout << "Choice: ";
    cin >> choice;

    return choice;
}

void imageProcessor(char option) {
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

void black_and_white() {
    for (auto &row: image) {
        for (unsigned char &pixel: row) {
            if (pixel > 127)
                pixel = 255;
            else
                pixel = 0;
        }
    }
}

void invert() {
    for (auto &row: image) {
        for (unsigned char &pixel: row) {
            pixel = 255 - pixel;
        }
    }
}

void merge() {
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

void flip() {
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

void rotate_90() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            image[i][j] = imageCopy[255 - j][i];
        }
    }
}

void rotate_180() {
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            image[i][j] = imageCopy[255 - i][255 - j];
        }
    }
}

void rotate_270() {
    for (int i = 255; i >= 0; --i) {
        for (int j = 0; j < 256; ++j) {
            image[i][j] = imageCopy[j][i];
        }
    }
}

void rotate_360() {
    for (auto &row: image) {
        for (unsigned char &pixel: row) {
            pixel = pixel;
        }
    }
}

void rotate() {
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

void darken_and_lighten() {
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
                    if (pixel < 196) pixel += 60;
                }
            }
            break;
        default:
            break;
    }
}

void detect_edges() {}

void enlarge_upper_left() {
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

void enlarge_upper_right() {
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

void enlarge_lower_left() {
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

void enlarge_lower_right() {
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

void enlarge() {
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

void shrink() {}

void shuffle() {
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
    if (v.size() != 4) {
        cout << "Invalid order save the original image and try again" << '\n';
        return;
    }
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
        if (i == 0) {
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
        } else if (i == 1) {
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
        } else if (i == 2) {
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
        } else if (i == 3) {
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

void mirror() {}

void blur() {}

void crop() {}

void skew_horizontal() {}

void skew_vertical() {}