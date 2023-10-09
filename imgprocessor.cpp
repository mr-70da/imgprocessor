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
//void filter_skew(){
//
//}
//void filter_shrink(){
//    string shrink_scale;
//    unsigned char shrink_image[SIZE][SIZE];
//    cout<<"Shrink to (1/2), (1/3) or (1/4)? \n";
//    cin>>shrink_scale;
//    for (auto & i : shrink_image) {
//        for (unsigned char & j : i) {
//            j = 255;
//        }
//    }
//    if(shrink_scale=="1/2"){
//        for (int i = 0; i < SIZE/2 - 1; i++) {
//            for (int j = 0; j < SIZE/2 - 1; j++) {
//                shrink_image[i][j] = (image[i*2][j*2] + image[i*2][j*2 + 1] + image[i*2 + 1][j*2] + image[i*2 + 1][j*2 + 1]) / 4;
//            }
//        }
//    }
//    else if(shrink_scale=="1/3"){
//        for (int i = 0; i < SIZE/3 - 2; i++) {
//            for (int j = 0; j < SIZE/3 - 2; j++) {
//                shrink_image[i][j] = (image[i*3][j*3] + image[i*3][j*3 + 1] + image[i*3][j*3+2]+image[i*3+1][j*3]+image[i*3+1][j*3+1]+image[i*3+1][j*3+2]+image[i*3+2][j*3]+image[i*3+2][j*3+1]+image[i*3+2][j*3+2]) / 9;
//            }
//        }
//    }
//    else if(shrink_scale=="1/4"){
//        for (int i = 0; i < SIZE/4 - 3; i++) {
//            for (int j = 0; j < SIZE/4 - 3; j++) {
//                shrink_image[i][j] = (image[i*4][j*4] + image[i*4][j*4 + 1] + image[i*4][j*4+2]+image[i*4][j*4+3]+image[i*4+1][j*4]+image[i*4+1][j*4+1]+image[i*4+1][j*4+2]+image[i*4+1][j*4+3]+image[i*4+2][j*4]+image[i*4+2][j*4+1]+image[i*4+2][j*4+2]+image[i*4+2][j*4+3]+image[i*4+3][j*4]+image[i*4+3][j*4+1]+image[i*4+3][j*4+2]+image[i*4+3][j*4+3]) / 16;
//            }
//        }
//    }
//    else{
//        cout<<"Invalid input\n";
//        filter_shrink();
//    }
//    for (int i = 0; i < SIZE; i++) {
//        for (int j = 0; j < SIZE; j++) {
//            image[i][j] = shrink_image[i][j];
//        }
//    }
//}
//void filter_blur(){
//    for(int k =0;k<5;k++){
//        for (int i = 1; i <= SIZE; i++) {
//            for (int j = 1; j <= SIZE; j++) {
//                image[i][j] = (image[i + 1][j - 1] + image[i - 1][j + 1] + image[i + 1][j] + image[i][j + 1]
//                               + image[i + 1][j + 1] + image[i - 1][j - 1] + image[i - 1][j] + image[i][j - 1]) / 8;
//            }
//        }
//    }
//}
//void filter_mirror(){
//    char mirror_side;
//    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side? \n";
//    cin>>mirror_side;
//    mirror_side = tolower(mirror_side);
//    int row,column;
//    switch(mirror_side){
//        case'l':
//            for (auto & i : image) {
//                for (int j = 0; j < SIZE; ++j) {
//                    i[SIZE-j] = i[j];
//                }//choose where to start from and put it in reverse
//            }
//            break;
//        case'r':
//            for (auto & i : image) {
//                for (int j = 0; j < SIZE; ++j) {
//                    i[j] = i[SIZE-j];
//                }
//            }
//            break;
//        case'u':
//            for (int i = 0; i < SIZE/2; ++i) {
//                for (int j = 0; j < SIZE; ++j) {
//                    image[SIZE-i][j] = image[i][j];
//                }
//            }
//            break;
//        case'd':
//            for (int i = 128; i < SIZE; ++i) {
//                for (int j = 0; j < SIZE; ++j) {
//                    image[SIZE-i][j] = image[i][j];
//                }
//            }
//            break;
//        default:
//            cout<<"Invalid option! \n";
//            filter_mirror();
//            break;
//    }
//}
//void filter_crop(){
//    unsigned char whiteImage[SIZE][SIZE];
//    for(auto & i : whiteImage){
//        for(auto & j : i){
//            j=255;
//        }
//    }
//
//    vector<int>v(4);
//    cout<< "Please enter x y l w: ";
//    for(int  i = 0; i<4;i++){
//        cin>>v[i];
//    }if(v.size()==4){
//        //x-axis pos=v[0],y-axis pos=v[1],length of rect=v[2],width of rect=v[3].
//        for(int i=v[0];i<v[0]+v[2];i++){
//            for(int j=v[1];j<v[1]+v[3];j++){
//                whiteImage[i][j]=image[i][j];
//            }
//        }for(int i = 0 ;i<SIZE;i++){
//            for(int j=0;j<SIZE;j++){
//                image[i][j]=whiteImage[i][j];
//            }
//        }
//
//    }else{
//        cout<<"Invalid option! \n";
//        filter_crop();
//    }
//}
//void filter_shuffle(){
//    unsigned char shuffled_image[SIZE][SIZE];
//    int newRow,newColoumn,row,coloumn;
//    vector<int>order_of_shuffle(4);
//    set<int>correctness;
//    cout<<"New order of quarters ? ";
//    for(int k=0;k<4;k++){
//        cin>>order_of_shuffle[k];
//        correctness.insert(order_of_shuffle[k]);
//    }if(correctness.size()==4){
//        for (int k = 0; k < 4; k++) {
//            newRow = k < 2 ? 0 : SIZE / 2;           //for the first & the second quarters start rows from 0 else start from 128
//            row = order_of_shuffle[k] < 3 ? 0 : SIZE / 2;            // for the first & the second quarters start rows from 0 else start from 128
//            for (int i = row; i < row + SIZE / 2; i++,newRow++) {
//                coloumn = order_of_shuffle[k] % 2 == 1 ? 0 : SIZE / 2;         // for the first & the second quarters start coloumn from 0 else start from 128
//                newColoumn = k % 2 == 0 ? 0 : SIZE / 2;          //for the first & the second quarters start coloumn from 0 else start from 128
//                for (int j = coloumn; j < coloumn + SIZE / 2; j++,newColoumn++) {
//                    shuffled_image[newRow][newColoumn] = image[i][j];
//                }
//            }
//        }//replace the original image with the shuffled one;
//        for(int i = 0;i <SIZE;i++){
//            for(int j = 0;j < SIZE;j++ ){
//                image[i][j] = shuffled_image[i][j];
//            }
//        }
//    }else{
//        cout<<"Please enter a valid order\n";
//        filter_shuffle();
//    }
//}
//void filter_enlarge(){
//    char quarter;
//    cout<<"Which quarter to enlarge 1, 2, 3 or 4?\n";
//    cin>>quarter;
//    unsigned char enlarged_image[SIZE][SIZE];
//    switch (quarter) {
//        case '1':
//            //put each pixel between( row 0 to row 127 && coloumn 0 to coloumn 127) in 4 pixel in shape of square 2x2
//            for (int i = 0; i < (SIZE/2); i++){
//                for (int j =0 ; j <(SIZE/2); j++){
//                    enlarged_image[(i*2)][(j*2)]     = image[i][j];
//                    enlarged_image[(i*2)+1][(j*2)]   = image[i][j];
//                    enlarged_image[(i*2)][(j*2)+1]   = image[i][j];
//                    enlarged_image[(i*2)+1][(j*2)+1] = image[i][j];
//                }
//            }for(int i = 0;i <SIZE;i++){
//        for(int j = 0;j < SIZE;j++ ){
//            image[i][j] = enlarged_image[i][j];
//        }
//    }
//            break;
//        case '2':
//            //put each pixel between( row 0 to row 127 && coloumn 128 to coloumn 255) in 4 pixel in shape of square 2x2
//            for (int i = 0; i < (SIZE/2); i++){
//                for (int j =0 ; j <(SIZE/2); j++){
//                    enlarged_image[(i*2)][(j*2)]     = image[i][j+128];
//                    enlarged_image[(i*2)+1][(j*2)]   = image[i][j+128];
//                    enlarged_image[(i*2)][(j*2)+1]   = image[i][j+128];
//                    enlarged_image[(i*2)+1][(j*2)+1] = image[i][j+128];
//                }
//            }for(int i = 0;i <SIZE;i++){
//        for(int j = 0;j < SIZE;j++ ){
//            image[i][j] = enlarged_image[i][j];
//        }
//    }
//            break;
//        case '3':
//            //put each pixel between( row 128 to row 255 && coloumn 0 to coloumn 127) in 4 pixel in shape of square 2x2
//            for (int i = 0; i < (SIZE/2); i++){
//                for (int j =0 ; j <(SIZE/2); j++){
//                    enlarged_image[(i*2)][(j*2)]     = image[i+128][j];
//                    enlarged_image[(i*2)+1][(j*2)]   = image[i+128][j];
//                    enlarged_image[(i*2)][(j*2)+1]   = image[i+128][j];
//                    enlarged_image[(i*2)+1][(j*2)+1] = image[i+128][j];
//                }
//            }for(int i = 0;i <SIZE;i++){
//        for(int j = 0;j < SIZE;j++ ){
//            image[i][j] = enlarged_image[i][j];
//        }
//    }
//            break;
//        case '4':
//            //put each pixel between( row 128 to row 255 && coloumn 128 to coloumn 255) in 4 pixel in shape of square 2x2
//            for (int i = 0; i < (SIZE/2); i++){
//                for (int j =0 ; j <(SIZE/2); j++){
//                    enlarged_image[(i*2)][(j*2)]     = image[i+128][j+128];
//                    enlarged_image[(i*2)+1][(j*2)]   = image[i+128][j+128];
//                    enlarged_image[(i*2)][(j*2)+1]   = image[i+128][j+128];
//                    enlarged_image[(i*2)+1][(j*2)+1] = image[i+128][j+128];
//                }
//            }for(int i = 0;i <SIZE;i++){
//        for(int j = 0;j < SIZE;j++ ){
//            image[i][j] = enlarged_image[i][j];
//        }
//    }
//            break;
//        default:
//            cout<<"Invalid Quarter, please choose a valid one\n";
//            filter_enlarge();
//            break;
//    }
//}
//void filter_detect_edges(){
//    for (auto &i: image) {
//        for (unsigned char &j: i) {
//            if (j >= 128)
//                j = 255;
//            else
//                j = 0;
//        }
//    }
//    for (int i = 0; i < SIZE; ++i) {
//        for (int j = 0; j < SIZE; ++j) {
//            image3[i][j] = image[i][j];
//        }
//    }
//    for (auto & i : image) {
//        for (unsigned char & j : i) {
//            j = 255;
//        }
//    }
//    for (int i = 1; i < SIZE-1; i++) {
//        for (int j = 1; j < SIZE-1; j++) {
//            if(image3[i][j]!=image3[i][j+1]&&image3[i][j]==image3[i][j-1]||image3[i][j]!=image3[i][j-1]&&image3[i][j]==image3[i][j+1]||image3[i][j]!=image3[i+1][j]&&image3[i][j]==image3[i-1][j]||image3[i][j]!=image3[i-1][j]&&image3[i][j]==image3[i+1][j]){
//                image[i][j] = 0;
//            }
//        }
//    }
//
//}
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
