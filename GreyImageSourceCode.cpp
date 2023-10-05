#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

<<<<<<< HEAD
void loadImage ();
void saveImage ();
void doSomethingForImage ();
char options();
void imageProcessor(char option);
void black_and_white();
void invert();
void merge();
void flip();
void rotate();
void darken_and_lighten();
void detect_edges();
void enlarge();
void shrink();
void shuffle();
void mirror();
void blur();
void crop();
void skew_horizontal();
void skew_vertical();

int main()
{
  loadImage();
  doSomethingForImage();
  saveImage();
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
=======
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

void darken_and_lighten();

void detect_edges();

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
>>>>>>> 456bfdd21786d81e5f3ee0cf7812723c97eb1f7c
}

//_________________________________________
void doSomethingForImage() {
<<<<<<< HEAD
  char c = options();
  imageProcessor(c);
}

char options()
{
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

void imageProcessor(char option)
{
  switch (option)
  {
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

void black_and_white()
{
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {
      if (image[i][j] > 127)
            image[i][j] = 255;
        else
            image[i][j] = 0;
    }
  }
}
void invert(){}
void merge(){}
void flip(){}
void rotate(){}
void darken_and_lighten(){}
void detect_edges(){}
void enlarge(){}
void shrink(){}
void shuffle(){}
void mirror(){}
void blur(){}
void crop(){}
void skew_horizontal(){}
void skew_vertical(){}
=======
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

void merge() {}

void flip() {}

void rotate() {}

void darken_and_lighten() {}

void detect_edges() {}

void enlarge() {}

void shrink() {}

void shuffle() {}

void mirror() {}

void blur() {}

void crop() {}

void skew_horizontal() {}

void skew_vertical() {}
>>>>>>> 456bfdd21786d81e5f3ee0cf7812723c97eb1f7c
