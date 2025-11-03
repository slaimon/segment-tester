#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;
/*
  Test all possible values on a given version of Segmento,
  logging error inputs as they are found.
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

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <WIDTH> <HEIGHT>" << endl;
        cout << "Run an exhaustive test on the "<< STR(FILENAME) << " version of Segmento, "
            << "on a canvas with the given width and height, and print inputs that produce errors" << endl;
        cout << "WARNING! Time complexity is O(H^2*W^2) so runtime gets really long, really fast." << endl;
        return -1;
    }
    width = stoul(argv[1]);
    height = stoul(argv[2]);

    for (unsigned int x = 0; x < width; x++)
        for (unsigned int y = 0; y < height; y++)
            for (unsigned int x2 = 0; x2 < width; x2++)
                for (unsigned int y2 = 0; y2 < height; y2++)
                    Segmento(x, y, x2, y2);

    return 0;
}