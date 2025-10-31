inline void log(unsigned int x, unsigned int y,
                unsigned int x2, unsigned int y2);
inline bool Dot_3x3(unsigned int x, unsigned int y);

void Segmento (unsigned int x, unsigned int y,
              unsigned int x2, unsigned int y2)
{
    // Special case: vertical segment
    if (x == x2) {
        unsigned int y_min = std::min(y,y2);
        unsigned int y_max = std::max(y,y2) + 1;
        for (unsigned int y = y_min; y < y_max; y++) {
            if (!Dot_3x3(x,y)) {
                log(x, y, x2, y2);
                return;
            }
        }
        return;
    }

    // In the following, we will assume x < x2
    if (x2 < x) {
        std::swap(x, x2);
        std::swap(y, y2);
    }
    int dx = x2 - x; // dx > 0
    int dy = y2 - y;
    int L = std::max(dx, std::abs(dy)) + 1;
    
    // simulate fixed-point arithmetic with bitshifts
    dx <<= 16; dx /= L;
    dy <<= 16; dy /= L;

    // brush position (with 16 bits of fractional precision)
    unsigned int brush_x = x << 16;
    unsigned int brush_y = y << 16;

    // stop when you reach column x2
    unsigned int end = x2 << 16;
    do {
        // truncate brush coords and place a dot there
        if (!Dot_3x3(brush_x >> 16, brush_y >> 16)) {
            log(x, y, x2, y2);
            return;
        }

        // move to the next sample point
        brush_y += dy;
        brush_x += dx;
    } while (brush_x < end);
}