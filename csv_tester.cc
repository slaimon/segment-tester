#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>
using namespace std;
/*
  Test the inputs in a .csv file on a given version of Segmento,
  logging the ones that cause an error.
*/

unsigned int width;
unsigned int height;

// ugly expand-and-stringize trick
#define STRR(x) #x
#define STR(x) STRR(x)
#ifdef FILENAME
#include STR(FILENAME)
#else
#error "Please define FILENAME with the path to the Segmento function you want tested."
#endif

inline void log(unsigned int x, unsigned int y,
                unsigned int x2, unsigned int y2)
{
    cout << x << "," << y << "," << x2 << "," << y2 << endl;
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
        cout << "Usage: " << argv[0] << " <INPUT_FILE> <WIDTH> <HEIGHT>" << endl;
        cout << "Reads inputs from a file and tests them on the " << STR(FILENAME)
            << " version of Segmento, using a canvas of the given width and height." << endl;
        
        return -1;
    }
    vector<vector<unsigned int>> tests = readCSV(argv[1]);
    width = stoul(argv[2]);
    height = stoul(argv[3]);

    for(unsigned int i = 0; i < tests.size(); i++) {
        run(tests[i]);
    }

    return 0;
}