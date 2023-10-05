//OOP-first assignment:Image processor
//authers:Mahmoud Ayman Ramadan ID:20220313,
//// FCAI – OOP Programming – 2023 - Assignment 1 
// Program Name: imgprocessor.cpp
// Last Modification Date:	5/10/2023
// Author1 and ID and Group:	xxxxx xxxxx
// Author2 and ID and Group:	xxxxx xxxxx
// Author3 and ID and Group:	xxxxx xxxxx
// Teaching Assistant:		xxxxx xxxxx
// Purpose:..........

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];
bool ex = false;
void loadImage();

void loadImage2();
void saveImage () {
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}
void filter_bri_dark();
void filter_flip();
void filters();
void filter_rotate();
int main()
{
    cout<<"Ahlan ya user ya habibi \uF04A\n";
    loadImage();
    while (!ex){ filters(); }
    saveImage();
    return 0;
}
void filter_bri_dark(){
    char ch;
    cout<<"Do you want to (d)arken or (l)ighten? \n";
    cin>>ch;
    if(ch =='d') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = (image[i][j])/2;
            }
        }
    }
    else if(ch=='l'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[i][j] = image[i][j]+(255-image[i][j])/2 ;
            }
        }
    }
    else{
        cout<<"Please enter a valid character: ";
        filter_bri_dark();
    }
}
void filter_rotate(){
    int rot;
    cout << "Enter 90 if you want to rotate image by 90 degree: \n";
    cout << "Enter 180 if you want to rotate image by 180 degree: \n";
    cout << "Enter 270 if you want to rotate image by 270 degree: \n";
    cin >> rot;
    if (rot == 90) {
        int l = SIZE - 1, k = 0;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[k][l] = image3[i][j];
                k++;
            }
            l--;
            k = 0;
        }
    } else if (rot == 180) {
        int l = SIZE - 1, k = SIZE - 1;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[k][l] = image3[i][j];
                l--;
            }
            k--;
            l = SIZE - 1;
        }
    } else if (rot == 270) {
        int l = 0, k = SIZE - 1;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[k][l] = image3[i][j];
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
    char ch;
    cout << "Enter v if you want it to flip vertically : \n";
    cout << "Enter h if you want it to flip horizontally : \n";
    cin >> ch;
    ch = tolower(ch);
    if (ch == 'v') {
        int k = SIZE - 1, l = 0;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[k][l] = image3[i][j];
                ++l;
            }
            k--;
            l = 0;
        }
    } else if (ch == 'h') {
        int k = 0, l = SIZE - 1;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                image[k][l] = image3[i][j];
                --l;
            }
            k++;
            l = SIZE - 1;
        }
    }
    else{
        cout<<"Please choose a valid character: \n";
        filter_flip();
    }
}
void filters() {
    char filter_Applied;
    cout << "Please select a filter to apply or 0 to exit:\n";
    cout << "\n"
            "1-Black & White Filter\n"
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
            for (auto &i: image) {
                for (unsigned char &j: i) {
                    if (j >= 128)
                        j = 255;
                    else
                        j = 0;
                }
            }
            break;
        case '2':
            for (auto &i: image) {
                for (unsigned char &j: i) {
                    j = 255 - j;
                }
            }
            break;
        case '3':
            loadImage2();
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image[i][j] = (image[i][j] + image2[i][j]) / 2;
                }
            }
            break;
        case '4':
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image3[i][j] = image[i][j];
                }
            }
            filter_flip();
            break;
        case '6':
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    image3[i][j] = image[i][j];
                }
            }
            filter_rotate();
            break;
        case '5':
            filter_bri_dark();
            break;
        case 's':

        case '0':
            ex = true;
            break;
        default:
            cout << "Please try a vaild filter:";
            break;
    }
}

void loadImage () {
    char imageFileName[100];
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}
void loadImage2 () {
    char imageFileName[100];
    cout << "Enter the source image file name for the second image: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
}
