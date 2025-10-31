# Segment Tester

This package provides a crude testing harness for the various segment-drawing functions in Crystal
Pixels.

The function to be tested should have signature:

```c
void Segmento (unsigned int x, unsigned int y, unsigned int x2, unsigned int y2);
```

Place its definition in any file, let's call it `./testee/myfunc.cc`. Then compile with:

```bash
g++ random_tester.cc -DFILENAME="./testee/myfunc.cc" -o random_myfunc
```

And call it with, e.g., `./random_myfunc 1000 1280 800`. This will test your implementation of
Segmento on a thousand random pairs of points on a canvas of size 1280x800. When an error condition
is encountered, Segmento should call `log(x,y,x2,y2)` to print the problematic input to `stdout`.

## Examples

This package already includes two testable functions: they are a newer and an older version of
Segmento, contained in `forloop.cc` and `dowhile.cc`, respectively. After running the test
functions, it becomes clear that the older version has many critical inputs while `forloop.cc`
never seems to encounter any.

In particular, the version of Segmento defined in `dowhile.cc` crashes when trying to draw very
steep lines, like `880,364,881,0` which has $\Delta y = 364 \gg \Delta x = 1$. This explains in
part why the crashes never happened in the original resolution: a line can only be so steep if the
window is only 200 pixels tall.

## Testing against critical inputs

Try the following:

```bash
g++ random_tester.cc -DFILENAME="testee/dowhile.cc" -o random_dowhile
./random_dowhile 500000 1280 800 > err_1280_800.csv
```

This will produce a file with some critical inputs for the old version of Segmento. How do we find
out whether the new version is immune to the same bug? Use `csv_tester`:

```bash
g++ csv_tester.cc -DFILENAME="testee/forloop.cc" -o csv_forloop
./csv_forloop err_1280_800.csv 1280 800
```

This will test the for-loop version of the function on all the critical inputs found. If nothing is
printed, it means that this new version can handle all those inputs.

## Old version vs. new

The file `testee/dowhile.cc` contains a refactored version of the original Segmento found in
Crystal Pixels version M1.0.4. It should be equivalent and, in fact, seems to crash just as often
as the original when the game renders in 1280x800 resolution.

The file `testee/forloop.cc` contains a modified version of the do-while Segmento. In it, the
`do-while` loop is replaced with a `for` loop that *should* run the same number of iterations;
however, in practice it seems that this version is much more stable and doesn't risk passing
invalid input to `Dot_3x3`.

The fact that the do-while-loop should run `L` times is proven by observing that the do-while guard
becomes false after `N` iterations, as soon as `N` satisfies the inequalty:

```text
brush_x + N*dx >= end
```

We then use the following identities to simplify:

```text
brush_x = x * 2^16
dx = (x2-x) * 2^16 / L
end = x2 * 2^16
```

After some algebra, we come to the conclusion that N >= L. So, why aren't the two versions
equivalent in practice? I don't know :)

But what's important is that the for-loop version is more readable, doesn't crash and draws decent
lines.
