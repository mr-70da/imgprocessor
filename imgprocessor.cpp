// Author1 and ID and Group: Mahmoud Ayman Ramadan ID:20220313 Email:man3092003city@gmail.com
// Author2 and ID and Group: Hassan Sherif Elkersh ID:20220112 Email:1243hassan@gmail.com

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char MergImage[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
bool Exit = false;
void loadImage();
void Image_for_Merging ();
void saveImage ();
//void filter_brighten_darken();
void filter_flip();
void filters();
void filter_rotate();
void filter_invert();
void filter_merge();
//void filter_detect_edges();
//void filter_enlarge();
//void filter_shuffle();
//void filter_mirror();
//void filter_crop();
//void filter_blur();
//void filter_shrink();
//void filter_skew();
int main(){
    cout<<"Ahlan ya user ya habibi \uF04A\n";
    loadImage();
    while (!Exit){ filters(); }
    return 0;
}
void saveImage () {
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}
void filter_merge(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            image[i][j] = (image[i][j] + MergImage[i][j]) / 2;
        }
    }
}

void filter_brighten_darken(){
    char ch;
    cout<<"Do you want to (d)arken or (l)ighten? \n";
    cin>>ch;
    if(ch =='d') {
        for (auto & i : image) {
            for (unsigned char & j : i) {
                j = j/2;
                //divide the pixel by 2 to become darker by 50%.
            }
        }
    }
    else if(ch=='l'){
        for (auto & i : image) {
            for (unsigned char & j : i) {
                j = j+(255-j)/2 ;
                //calculate how much should we add to pixel to become white one.
                //then divide it by 2 to apply a brightened filter.
            }
        }
    }
    else{
        //if user enter unvalid char apply recuersion by using filter_brighten_darken() again.
        cout<<"Please enter a valid character: ";
        filter_brighten_darken();
    }
}
void filter_rotate(){
    int Rotation_Degree;
    //ask user about rotation degree he wants.
    cout << "Rotate (90), (180) or (360) degrees? \n";
    cin >> Rotation_Degree;
    //check rotation degree.
    if (Rotation_Degree == 90) {
        int l = SIZE - 1, k = 0;
        for (auto & i : image3) {
            for (unsigned char j : i) {
                image[k][l] = j;
                k++;
            }
            l--;
            k = 0;
        }
    } else if (Rotation_Degree == 180) {
        int l = SIZE - 1, k = SIZE - 1;
        for (auto & i : image3) {
            for (unsigned char j : i) {
                image[k][l] = j;
                l--;
            }
            k--;
            l = SIZE - 1;
        }
    } else if (Rotation_Degree == 270) {
        int l = 0, k = SIZE - 1;
        for (auto & i : image3) {
            for (unsigned char j : i) {
                image[k][l] = j;
                k--;
            }
            l++;
            k = SIZE - 1;
        }
    }
    else{
        cout<<"Please choose a valid character: \n";
        filter_rotate();}
}
void filter_flip(){
    //ask user where to flip he wants.
    char flip;
    cout << "Flip (h)orizontally or (v)ertically ? \n";
    cin >> flip;
    flip = tolower(flip);
    //check flip.
    if (flip == 'v') {
        int k = SIZE - 1, l = 0;
        for (auto & i : image3) {
            for (unsigned char j : i) {
                image[k][l] = j;
                ++l;
            }
            k--;
            l = 0;
        }
    } else if (flip == 'h') {
        int k = 0, l = SIZE - 1;
        for (auto & i : image3) {
            for (unsigned char j : i) {
                image[k][l] = j;
                --l;
            }
            k++;
            l = SIZE - 1;
        }
    }
    else{
        //if user enter unvalid char apply recuersion
        cout<<"Please choose a valid character: \n";
        filter_flip();
    }
}
void filter_black_white(){
    // see if each pixel is greater than or equal 128 or less
    // if greater make it 255 else make it 0
    for (auto &i: image) {
        for (unsigned char &j: i) {
            if (j >= 128)
                j = 255;
            else
                j = 0;
        }
    }
}
void filter_invert(){
    for (auto &i: image) {
        for (unsigned char &j: i) {
            j = 255 - j;
        }
    }
}
void filters() {
    char filter_Applied;
    cout << "Please select a filter to apply or 0 to exit:\n";
    cout << "1-Black & White Filter\n"
            "2-Invert Filter\n"
            "3-Merge Filter \n"
            "4-Flip Image\n"
            "5-Darken and Lighten Image \n"
            "6-Rotate Image\n"
            "s-Save the image to a file\n"
            "0-Exit\n";
    cin >> filter_Applied;
    switch (filter_Applied) {
        case '1':
            filter_black_white();
            break;
        case '2':
            filter_invert();
            break;
        case '3':
            Image_for_Merging ();
            filter_merge();
            break;
        case '4':
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image3[i][j] = image[i][j];
                }
            }
            filter_flip();
            break;
        case '5':
            filter_brighten_darken();
            break;
        case '6':
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image3[i][j] = image[i][j];
                }
            }
            filter_rotate();
            break;
//        case '7':
//            filter_detect_edges();
//            break;
//        case '8':
//            filter_enlarge();
//            break;
//        case '9':
//            filter_shrink();
//            break;
//        case 'a':
//            filter_mirror();
//            break;
//        case 'b':
//            filter_shuffle();
//            break;
//        case 'd':
//            filter_crop();
//            break;
//        case 'c':
//            filter_blur();
//            break;
//        case'e':
//        case'f':
//            break;
        case 's':
            saveImage();
            break;
        case '0':
            Exit= true;
            break;
        default:
            cout << "Please try a vaild filter:";
            break;
    }
}

void loadImage () {
    char imageFileName[100];
    cout << "Please enter file name of the image to process: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
void Image_for_Merging () {
    char imageFileName[100];
    cout << "Please enter name of image file to merge with:  ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName,MergImage);
}
