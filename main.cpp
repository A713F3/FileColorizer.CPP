#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv){
    if (argc == 1){
        cerr << "Enter file name!" << endl;
        return 0;
    }

    fstream file;
    string fileName = argv[1];

    file.open(fileName, ios::in);

    if (!file.is_open()){
        cerr << "Invalid file!" << endl;
        return 0;
    }
    cerr << "File succesfully loaded" << endl;

    int width = 0, height = -1;
    string line;

    // Finding width and height of the output image
    while (file){
        getline(file, line);
        
        if (line.length() > width) width = line.length();
        height++;
    }

    if (height == 0){
        cerr << "File is empty!" << endl;
        return 0;
    }

    cerr << "Output Image Dimensions:" << endl;
    cerr << "Width:  " << width << endl;
    cerr << "Height: " << height << endl; 



    return 0;
}