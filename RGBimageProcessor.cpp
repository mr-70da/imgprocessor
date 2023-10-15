// Author1 and ID and Group: Mahmoud Ayman Ramadan ID:20220313 Email:man3092003city@gmail.com Group:S6.
// Author2 and ID and Group: Hassan Sherif Elkersh ID:20220112 Email:1243hassan@gmail.com     Group:S6.
// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:		RGBimageProcessor.cpp
// Last Modification Date:	1/10/2023
// Teaching Assistant:		xxxxx xxxxx
// Purpose: Adding filters to RGB BMP Images.


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][3];
unsigned char MergImage[SIZE][SIZE][3];
unsigned char TempImage[SIZE][SIZE][3];
bool isExit = false;
void filter_skew_vertical();
void loadImage();
void Image_for_Merging ();
void saveImage ();
void filter_brighten_darken();
void filter_flip();
void filters();
void filter_rotate();
void filter_invert();
void filter_merge();
void filter_detect_edges();
void filter_enlarge();
void filter_shuffle();
void filter_mirror();
void filter_crop();
void filter_blur();
void filter_shrink();
void filter_skew_horizontal();
int main(){
    cout<<"Ahlan ya user ya habibi \uF04A\n";
    loadImage();
    while (!isExit){
        filters();
    }
    return 0;
}
void saveImage () {
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}
void filter_black_white(){
    // see if each pixel is greater than or equal 128 or less
    // if greater make it 255 else make it 0
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if(image[i][j][0]<=128&&image[i][j][1]<=128&&image[i][j][2]<=128){
                image[i][j][0] = 0,image[i][j][1]=0,image[i][j][2]=0;
            }
            else{
                image[i][j][0] = 255,image[i][j][1] = 255,image[i][j][2] = 255;
            }
        }
    }
}
void filter_invert(){
    //to get the invert subtract each pixel from 255
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                image[i][j][k] = 255-image[i][j][k];
            }
        }
    }
}
void filter_merge(){
    int avreage = 0;
    //take avreage of the two pixels and put then in one.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                avreage = (image[i][j][k] + MergImage[i][j][k]) / 2;
                image[i][j][k]= avreage;
            }
        }
    }
}
void filter_flip(){
    //copying image to temp.
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                TempImage[i][j][k] = image[i][j][k];
            }
        }
    }
    //ask user where to flip he wants.
    char flip;
    cout << "Flip (h)orizontally or (v)ertically ? \n";
    cin >> flip;
    //if user input 'H'or'V' change it to lower
    flip = tolower(flip);
    //check flip.
    if (flip == 'v') {
        //to flip vertically exchange rows first row in image = last row in temp
        int newRaw = SIZE - 1, column = 0;
        for (int i = 0 ; i < SIZE; i++) {
            for (int j = 0; j<SIZE; j++) {
                for (int m = 0; m < 3; ++m) {
                    image[newRaw][column][m] = TempImage[i][j][m];
                }
                ++column;
            }
            newRaw--;
            column = 0;
        }
    } else if (flip == 'h') {
        //to flip horizontally exchange rows first column in image = last column in temp
        int raw = 0, newColumn = SIZE - 1;
        for (int i = 0;i<SIZE;i++) {
            for (int j = 0; j<SIZE;j++) {
                for (int m = 0; m < 3; ++m) {
                    image[raw][newColumn][m] = TempImage[i][j][m];
                }
                --newColumn;
            }
            raw++;
            newColumn = SIZE - 1;
        }
    }
    else{
        //if user enter unvalid char apply recuersion
        cout<<"Please choose a valid character: \n";
        filter_flip();
    }
}
void filter_brighten_darken(){
    char brightness;
    //ask user darken or lighten
    cout<<"Do you want to (d)arken or (l)ighten? \n";
    cin>>brightness;
    //if user enter uppercase letter convert to lowercase one
    brightness = tolower(brightness);
    if(brightness == 'd') {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[i][j][k] /=2;
                }
            }
        }
    }
    else if(brightness=='l'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image[i][j][k] = image[i][j][k]+(255-image[i][j][k])/2;
                }
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
    //copying to temp image
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                TempImage[i][j][k] = image[i][j][k];
            }
        }
    }
    int Rotation_Degree;
    //ask user about rotation degree he wants.
    cout << "Rotate (90), (180), (270) or (360) degrees?\n";
    cin >> Rotation_Degree;
    //check rotation degree.
    if (Rotation_Degree == 90) {
        int newRow = SIZE - 1, newColumn = 0;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int m = 0; m < 3; ++m) {
                    image[newRow][newColumn][m] = TempImage[i][j][m];
                }
                newRow++;
            }
            newColumn--;
            newRow = 0;
        }
    } else if (Rotation_Degree == 180) {
        int newColumn = SIZE - 1, newRow  = SIZE - 1;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int m = 0; m < 3; ++m) {
                    image[newRow ][newColumn][m] = TempImage[i][j][m];
                }
                newColumn--;
            }
            newRow --;
            newColumn = SIZE - 1;
        }
    } else if (Rotation_Degree == 270) {
        int newColumn = 0, newRow  = SIZE - 1;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                for (int m = 0; m < 3; ++m) {
                    image[newRow][newColumn][m] = TempImage[i][j][m];
                }
                newRow --;
            }
            newColumn++;
            newRow  = SIZE - 1;
        }
    }
    else if(Rotation_Degree==360){

    }
    else{
        cout<<"Please choose a valid character: \n";
        filter_rotate();}
}
void filter_detect_edges(){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if(image[i][j][0]<=128&&image[i][j][1]<=128&&image[i][j][2]<=128){
                image[i][j][0] = image[i][j][1] = image[i][j][2] = 0;
            }
            else{
                image[i][j][0] = image[i][j][1] = image[i][j][2] = 255;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                TempImage[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int m = 0; m < 3; ++m) {
                image[i][j][m] = 255;
            }
        }
    }
    for (int i = 1; i < SIZE-1; i++) {
        for (int j = 1; j < SIZE-1; j++) {
            for (int k = 0; k < 3; ++k) {
                if (TempImage[i][j][k] != TempImage[i][j + 1][k] && TempImage[i][j][k] == TempImage[i][j - 1][k] ||
                    TempImage[i][j][k] != TempImage[i][j - 1][k] && TempImage[i][j][k] == TempImage[i][j + 1][k] ||
                    TempImage[i][j][k] != TempImage[i + 1][j][k] && TempImage[i][j][k] == TempImage[i - 1][j][k] ||
                    TempImage[i][j][k] != TempImage[i - 1][j][k] && TempImage[i][j][k] == TempImage[i + 1][j][k])
                {
                    image[i][j][k] = 0;
                }
            }
        }
    }
}
void filter_enlarge(){
    char quarter;
    cout<<"Which quarter to enlarge 1, 2, 3 or 4?\n";
    cin>>quarter;
    unsigned char enlarged_image[SIZE][SIZE][3];
    switch (quarter) {
        case '1':
            //put each pixel between( row 0 to row 127 && column 0 to column 127) in 4 pixel in shape of square 2x2
            for (int i = 0; i < (SIZE/2); i++){
                for (int j =0 ; j < (SIZE/2); j++){
                    for (int k = 0; k < 3; ++k) {
                        enlarged_image[(i * 2)][(j * 2)][k]         = image[i][j][k];
                        enlarged_image[(i * 2) + 1][(j * 2)][k]     = image[i][j][k];
                        enlarged_image[(i * 2)][(j * 2) + 1][k]     = image[i][j][k];
                        enlarged_image[(i * 2) + 1][(j * 2) + 1][k] = image[i][j][k];
                    }
                }
            }
            for(int i = 0;i <SIZE;i++){
                for(int j = 0;j < SIZE;j++ ){
                    for (int k = 0; k < 3; ++k){
                        image[i][j][k] = enlarged_image[i][j][k];
                    }
                }
            }
            break;
        case '2':
            //put each pixel between( row 0 to row 127 && column 128 to column 255) in 4 pixel in shape of square 2x2
            for (int i = 0; i < (SIZE/2); i++){
                for (int j =0 ; j <(SIZE/2); j++){
                    for (int k = 0; k < 3; ++k){
                        enlarged_image[(i * 2)][(j * 2)][k]         = image[i][j + 128][k];
                        enlarged_image[(i * 2) + 1][(j * 2)][k]     = image[i][j + 128][k];
                        enlarged_image[(i * 2)][(j * 2) + 1][k]     = image[i][j + 128][k];
                        enlarged_image[(i * 2) + 1][(j * 2) + 1][k] = image[i][j + 128][k];
                    }
                }
            }for(int i = 0;i <SIZE;i++){
                for(int j = 0;j < SIZE;j++ ){
                     for (int k = 0; k < 3; ++k){
                         image[i][j][k] = enlarged_image[i][j][k];
                     }
                }
            }
            break;
        case '3':
            //put each pixel between( row 128 to row 255 && coloumn 0 to coloumn 127) in 4 pixel in shape of square 2x2
            for (int i = 0; i < (SIZE/2); i++){
                for (int j =0 ; j <(SIZE/2); j++){
                    for (int k = 0; k < 3; ++k){
                        enlarged_image[(i * 2)][(j * 2)][k]         = image[i + 128][j][k];
                        enlarged_image[(i * 2) + 1][(j * 2)][k]     = image[i + 128][j][k];
                        enlarged_image[(i * 2)][(j * 2) + 1][k]     = image[i + 128][j][k];
                        enlarged_image[(i * 2) + 1][(j * 2) + 1][k] = image[i + 128][j][k];
                    }
                }
            }for(int i = 0;i <SIZE;i++){
                 for(int j = 0;j < SIZE;j++ ){
                     for (int k = 0; k < 3; ++k){
                         image[i][j][k] = enlarged_image[i][j][k];
                     }
                 }
            }
            break;
        case '4':
            //put each pixel between( row 128 to row 255 && coloumn 128 to coloumn 255) in 4 pixel in shape of square 2x2
            for (int i = 0; i < (SIZE/2); i++){
                for (int j =0 ; j <(SIZE/2); j++){
                    for (int k = 0; k < 3; ++k){
                        enlarged_image[(i * 2)][(j * 2)][k]         = image[i + 128][j + 128][k];
                        enlarged_image[(i * 2) + 1][(j * 2)][k]     = image[i + 128][j + 128][k];
                        enlarged_image[(i * 2)][(j * 2) + 1][k]     = image[i + 128][j + 128][k];
                        enlarged_image[(i * 2) + 1][(j * 2) + 1][k] = image[i + 128][j + 128][k];
                    }
                }
            }for(int i = 0;i <SIZE;i++){
                for(int j = 0;j < SIZE;j++ ){
                    for (int k = 0; k < 3; ++k){
                        image[i][j][k] = enlarged_image[i][j][k];
                    }
                }
            }
            break;
        default:
            cout<<"Invalid Quarter, please choose a valid one\n";
            filter_enlarge();
            break;
    }
}
void filter_shrink(){
    string shrink_scale;
    unsigned char shrink_image[SIZE][SIZE][3];
    cout<<"Shrink to (1/2), (1/3) or (1/4)? \n";
    cin>>shrink_scale;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k){
                shrink_image[i][j][k] = 255;
            }
        }
    }
    if(shrink_scale=="1/2"){
        for (int i = 0; i < SIZE/2 - 1; i++) {
            for (int j = 0; j < SIZE/2 - 1; j++) {
                for (int x = 0; x < 3; ++x) {
                    shrink_image[i][j][x] =  (image[i * 2 + 0][j * 2 + 0][x]+image[i * 2 + 0][j * 2 + 1][x]+image[i * 2 + 1][j * 2 + 0][x]+image[i * 2 + 1][j * 2 + 1][x])/4;
                }
            }
        }
    }
    else if(shrink_scale=="1/3"){
        for (int i = 0; i < SIZE/3 - 2; i++) {
            for (int j = 0; j < SIZE/3 - 2; j++) {
                for (int k = 0; k < 3; ++k){
                    shrink_image[i][j][k] = (image[i * 3][j * 3][k] + image[i * 3][j * 3 + 1][k] + image[i * 3][j * 3 + 2][k] +
                                                                      image[i * 3 + 1][j * 3][k] + image[i * 3 + 1][j * 3 + 1][k] +
                                                                      image[i * 3 + 1][j * 3 + 2][k] + image[i * 3 + 2][j * 3][k] +
                                                                      image[i * 3 + 2][j * 3 + 1][k] + image[i * 3 + 2][j * 3 + 2][k]) / 9;
                }
            }
        }
    }
    else if(shrink_scale=="1/4"){
        for (int i = 0; i < SIZE/4 - 3; i++) {
            for (int j = 0; j < SIZE/4 - 3; j++) {
                for (int k = 0; k < 3; ++k){
                    shrink_image[i][j][k] = (image[i * 4][j * 4][k] + image[i * 4][j * 4 + 1][k] + image[i * 4][j * 4 + 2][k] +
                                                                      image[i * 4][j * 4 + 3][k] + image[i * 4 + 1][j * 4][k] +
                                                                      image[i * 4 + 1][j * 4 + 1][k] + image[i * 4 + 1][j * 4 + 2][k] +
                                                                      image[i * 4 + 1][j * 4 + 3][k] + image[i * 4 + 2][j * 4][k] +
                                                                      image[i * 4 + 2][j * 4 + 1][k] + image[i * 4 + 2][j * 4 + 2][k] +
                                                                      image[i * 4 + 2][j * 4 + 3][k] + image[i * 4 + 3][j * 4][k] +
                                                                      image[i * 4 + 3][j * 4 + 1][k] + image[i * 4 + 3][j * 4 + 2][k] +
                                                                      image[i * 4 + 3][j * 4 + 3][k]) / 16;
                }
            }
        }
    }
    else{
        cout<<"Invalid input\n";
        filter_shrink();
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k){
                image[i][j][k] = shrink_image[i][j][k];
            }
        }
    }
}
void filter_mirror(){
    char mirror_side;
    cout<<"Mirror (l)eft, (r)ight, (u)pper, (d)own side? \n";
    cin>>mirror_side;
    mirror_side = tolower(mirror_side);
    switch(mirror_side){
        case'l':
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int k = 0; k < 3; ++k){
                        image[i][SIZE - j][k] = image[i][j][k];
                    }
                }//choose where to start from and put it in reverse
            }
            break;
        case'r':
            for (int i = 0; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    {for (int k = 0; k < 3; ++k)
                        image[i][j][k] = image[i][SIZE - j][k];
                    }
                }
            }
            break;
        case'u':
            for (int i = 0; i < SIZE/2; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int k = 0; k < 3; ++k){
                        image[SIZE - i][j][k] = image[i][j][k];
                    }
                }
            }
            break;
        case'd':
            for (int i = 128; i < SIZE; ++i) {
                for (int j = 0; j < SIZE; ++j) {
                    for (int k = 0; k < 3; ++k){
                        image[SIZE - i][j][k] = image[i][j][k];
                    }
                }
            }
            break;
        default:
            cout<<"Invalid option! \n";
            filter_mirror();
            break;
    }
}
void filter_shuffle(){
    unsigned char shuffled_image[SIZE][SIZE][3];
    int newRow,newColumn,row,column;
    vector<int>order_of_shuffle(4);
    set<int>correctness;
    cout<<"New order of quarters ? ";
    for(int k=0;k<4;k++){
        cin>>order_of_shuffle[k];
        correctness.insert(order_of_shuffle[k]);
    }//check that there are diffrent four numbers else tell user to enter valid order
    if(correctness.size()==4){
        for (int k = 0; k < 4; k++) {
            //for the first & the second quarters start rows from 0 else start from 128
            newRow = k < 2 ? 0 : SIZE / 2;
            // for the first & the second quarters start rows from 0 else start from 128
            row = order_of_shuffle[k] < 3 ? 0 : SIZE / 2;
            for (int i = row; i < row + SIZE / 2; i++,newRow++) {
                // for the first & the second quarters start coloumn from 0 else start from 128
                column = order_of_shuffle[k] % 2 == 1 ? 0 : SIZE / 2;
                //for the first & the second quarters start coloumn from 0 else start from 128
                newColumn = k % 2 == 0 ? 0 : SIZE / 2;
                for (int j = column; j < column + SIZE / 2; j++,newColumn++) {
                    for (int l = 0; l < 3; ++l) {
                        shuffled_image[newRow][newColumn][l] = image[i][j][l]; }
                }

            }
        }//replace the original image with the shuffled one;
        for(int i = 0;i < SIZE; i++){
            for(int j = 0;j < SIZE;j ++ ){
                for (int k = 0; k < 3; ++k){
                    image[i][j][k] = shuffled_image[i][j][k];
                }
            }
        }
    }else{
        cout<<"Please enter a valid order\n";
        filter_shuffle();
    }
}
void filter_crop(){
    unsigned char whiteImage[SIZE][SIZE][3];
    for(auto & i : whiteImage){
        for(auto & j : i){
            for(auto& k : j){
                k = 255;
            }
        }
    }
    vector<int>v(4);
    cout<< "Please enter x y l w: ";
    for(int  i = 0; i<4 ; i++){
        cin>>v[i];
    }if(v.size()==4){
        //x-axis pos=v[0],y-axis pos=v[1],length of rect=v[2],width of rect=v[3].
        for(int i= v[0]; i < v[0]+v[2]; i++){
            for(int j =v [1]; j<v[1]+v[3]; j++){
                for (int k = 0; k < 3; ++k){
                    whiteImage[i][j][k] = image[i][j][k];
                }
            }
        }for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                for (int k = 0; k < 3; ++k){
                    image[i][j][k] = whiteImage[i][j][k];
                }
            }
        }

    }else{
        cout<<"Invalid option! \n";
        filter_crop();
    }
}
void filter_blur(){
    for(int k =0;k<5;k++){
        for (int i = 1; i <= SIZE; i++) {
            for (int j = 1; j <= SIZE; j++) {
                for (int m = 0; m < 3; ++m){
                    image[i][j][m] = (image[i + 1][j - 1][m] + image[i - 1][j + 1][m] + image[i + 1][j][m] + image[i][j + 1][m]
                                      + image[i + 1][j + 1][m] + image[i - 1][j - 1][m] + image[i - 1][j][m] + image[i][j - 1][m]) / 8;
                }
            }
        }
    }
}

void filter_skew_horizontal(){
    double AngelOfSkewness ;
    cout<<"Please enter degree to skew right: \n";
    cin >> AngelOfSkewness ;
    AngelOfSkewness  = ( AngelOfSkewness  * 22 ) / ( 180 * 7 ) ;
    double move = tan(AngelOfSkewness ) * 256 ;
    double step = move / SIZE ;
    move  = floor(move);
    unsigned char SkewedImage[SIZE][SIZE+(int)move][3],shrink_image[SIZE][SIZE][3];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE+(int)move; ++j) {
            for (int k = 0; k < 3; ++k){
                SkewedImage[i][j][k] = 255;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k){
                shrink_image[i][j][k] = 255;
            }
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE; j++ ){
            for (int k = 0; k < 3; ++k){
                SkewedImage[i][j + (int) move][k] = image[i][j][k];
            }
        }
        move -= step ;
    }
    double end  = 0.0;
    for (int i = 0; i < SIZE; i++) {
        double k =0.0;
        for (int j = 0; j < SIZE-(int)end; j++) {
            for (int l = 0; l < 3; ++l) {
                shrink_image[i][j][l] = SkewedImage[i][j + (int) k][l];
            }
            k+=step;
        }
        end += step/2;
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE; j++ ){
            for (int k = 0; k < 3; ++k){
                image[i][j][k] = shrink_image[i][j][k];
            }
        }
    }
}
void filter_skew_vertical(){
    double  AngelOfSkewness ;
    cout<<"Please enter degree to skew up: \n";
    cin >> AngelOfSkewness ;
    AngelOfSkewness = ( AngelOfSkewness * 22 ) / ( 180 * 7 ) ;
    double move = tan( AngelOfSkewness) * 256 ,comp;
    double step = move / SIZE ;
    move  = floor(move),comp = move;
    unsigned char SkewedImage[SIZE+(int)move][SIZE][3],copy[SIZE][SIZE][3];
    for (int i = 0; i < SIZE+(int)move; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < 3; ++k) {
                SkewedImage[i][j][k] = 255;
            }
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j){
            for (int k = 0; k < 3; ++k){
                copy[i][j][k] = 255;
            }
        }
    }
    double scale = 0;
    double end  = 0.0;
    for ( int i = SIZE-1 ; i >=0 ; i-- ){
        for ( int j = 0 ; j <SIZE ; j++ ){
            for (int k = 0; k < 3; ++k){
                SkewedImage[i - (int) scale + (int) comp + (int) end][j][k] = image[i][j][k];
            }
            scale += step ;
        }
        scale = 0;
        end+=step/2;
    }
    for ( int i = SIZE-1 ; i >=0 ; i--){
        double k =0.0;
        for ( int j = 0 ; j <SIZE ; j++ ){
            for (int l = 0; l < 3; ++l){
                copy[i][j][l] = SkewedImage[i - (int) k + (int) comp][j][l];
            }
            k+=step/2;
        }
    }
    for ( int i = 0 ; i < SIZE ; i++ ){
        for ( int j = 0 ; j < SIZE; j++ ){
            for (int k = 0; k < 3; ++k){
                image[i][j][k] = copy[i][j][k];
            }
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
            "7-Detect Image Edges \n"
            "8-Enlarge Image\n"
            "9-Shrink Image\n"
            "a-Mirror 1/2 Image\n"
            "b-Shuffle Image\n"
            "c-Blur Image\n"
            "d-Crop Image\n"
            "e-Skew Image Right  \n"
            "f-Skew Image Up  \n"
            "s-Save the image to a file\n"
            "0-Exit\n";
    cin >> filter_Applied;
    filter_Applied = tolower(filter_Applied);
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
            filter_flip();
            break;
        case '5':
            filter_brighten_darken();
            break;
        case '6':
            filter_rotate();
            break;
        case '7':
            filter_detect_edges();
            break;
        case '8':
            filter_enlarge();
            break;
        case '9':
            filter_shrink();
            break;
        case 'a':
            filter_mirror();
            break;
        case 'b':
            filter_shuffle();
            break;
        case 'd':
            filter_crop();
            break;
        case 'c':
            filter_blur();
            break;
        case'e':
            filter_skew_horizontal();
            break;
        case'f':
            filter_skew_vertical();
            break;
        case 's':
            saveImage();
            break;
        case '0':
            isExit= true;
            break;
        default:
            cout << "Please try a vaild filter:\n";
            break;
    }
}
void loadImage () {
    char imageFileName[100];
    cout << "Please enter file name of the image to process: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
void Image_for_Merging () {
    char imageFileName[100];
    cout << "Please enter name of image file to merge with:  ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName,MergImage);
}
