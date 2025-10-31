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

This will test the for-loop version of the function on all the critical inputs found. If no
assertion is triggered, it means that this new version can handle all those inputs.
