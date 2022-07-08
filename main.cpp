#include <iostream>
#include <fstream>
#include <map>
#include <random>
using namespace std;

typedef struct color{
    int r, g, b;
} color;

int main(int argc, char** argv){
    // Random Color Generator
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, 255);

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
    cerr << "File loaded successfully!" << endl;

    map<char, color> colors;

    color blank_color = {255, 255, 255};
    colors[' '] = blank_color;

    int width = 0, height = -1;
    string line;

    // Finding width and height of the output image
    // And creating random colors for each character
    //cerr << "\n-Colors:" << endl;
    while (file){
        getline(file, line);

        for (int i = 0; i < line.length(); i++){
            char c = line[i];
            if (colors.find(c) == colors.end()){
                int r = distribution(generator);
                int g = distribution(generator);
                int b = distribution(generator);

                //cerr << c << ": " << r << ',' << g << ',' << b << endl;

                color new_color = {r, g, b};

                colors[c] = new_color;
            }
        }
        
        if (line.length() > width) width = line.length();
        height++;
    }

    if (height == 0){
        cerr << "File is empty!" << endl;
        return 0;
    }

    cerr << "\n-Output Image Dimensions:" << endl;
    cerr << "Width:  " << width << endl;
    cerr << "Height: " << height << endl; 

    // Rendering output image
    file.clear();
    file.seekg(0);

    cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int i = 0; i < height; i++){
        getline(file, line);
        int len = line.length();

        for (int l = 0; l < len; l++){
            color char_color = colors[line[l]]; 

            int r = char_color.r;
            int g = char_color.g;
            int b = char_color.b;

            cout << r << ' ' << g << ' ' << b << '\n';
        }

        for (int j = 0; j < width - len; j++){
            cout << 255 << ' ' << 255 << ' ' << 255 << '\n';
        }
    }

    cerr << "\nImage rendered successfully!" << endl;

    return 0;
}