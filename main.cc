#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>
using namespace std;
/*
Test the values in err.csv on the for-loop version
of Segmento to see if they still cause a problem 
*/

unsigned int width = 1280;
unsigned int height = 800;

#include "forloop.cc"

inline void log(unsigned int x, unsigned int y,
                unsigned int x2, unsigned int y2)
{
    cout << x << "," << y << "," << x2 << "," << y2 << endl;
}

inline bool Dot_3x3(unsigned int x, unsigned int y) {
    if (x > width || y > height)
        return false;
    return true;
}

vector<vector<unsigned int>> readCSV(const string& filename) {
    vector<vector<unsigned int>> data;
    ifstream file(filename);
    assert(file.is_open());

    string line;
    while (getline(file, line)) {
        vector<unsigned int> args;
        stringstream ss(line);
        string value;

        while(getline(ss, value, ',')) {
            args.push_back(stoul(value));
        }
        data.push_back(args);
    }

    return data;
}

void run(vector<unsigned int> args) {
    assert(args.size() == 4);
    Segmento(args[0], args[1], args[2], args[3]);
}

int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <WIDTH> <HEIGHT> <INPUT_FILE>" << endl;
        cout << "Reads inputs from a file and tests them on the for-loop version of Segmento, "
            << "using a canvas of the given width and height." << endl;
    }
    width = stoul(argv[1]);
    height = stoul(argv[2]);
    vector<vector<unsigned int>> tests = readCSV(argv[3]);

    for(int i = 0; i < tests.size(); i++) {
        run(tests[i]);
    }
    cout << "success!" << endl;

    return 0;
}