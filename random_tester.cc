#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;
/*
  Test random values on a given version of Segmento,
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
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <NUM_TESTS> <WIDTH> <HEIGHT>" << endl;
        cout << "Run a given number of random tests on the "<< STR(FILENAME) << " version of Segmento, "
            << "on a canvas with the given width and height, and print inputs that produce errors" << endl;
        return -1;
    }
    const unsigned int samples = stoul(argv[1]);
    width = stoul(argv[2]);
    height = stoul(argv[3]);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> w(0u,width-1);
    uniform_int_distribution<> h(0u,height-1);

    for (unsigned int i = 0; i < samples; i++) {
        Segmento(w(gen), h(gen), w(gen), h(gen));
    }

    return 0;
}