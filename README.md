# :chart_with_upwards_trend: Project Goal
To make a C graphing utility that is capable of graphing functions.

![image](./docs/figures/test.png)


The above is an example graph made by this graphing utility.  It is the example
file provided and shows the graph of:
- sin(x^2 + 1)
- cos(x)
- tan(x)
- (x + 1)^(x + 1)
- (x - 1)^2 + 1
- (x + 1)^3 - 1
- log(x)

# :zap: Current Features
This graphing utility is capable of making [netpbm](https://en.wikipedia.org/wiki/Netpbm)
image files of the function(s) that the user specifies in any color in the rgb
channel.

The user can specify a set of functions and graph window parameters via an input
file that this  utility reads then produces an output file. See the
[Use](https://github.com/millipedes/C-Netpbm-Function-Grapher#exclamation-use)
and
[Installation/Building](https://github.com/millipedes/C-Netpbm-Function-Grapher#minidisc-installationbuilding)
sections for more details.

This program is free of memory leaks when fed an expected input file as verified
using several test input files and valgrind.

# :minidisc: Installation/Building
The following commands can be used for most users to build the project:
```
  git clone https://github.com/millipedes/C-Netpbm-Function-Grapher.git
  cd C-Netpbm-Function-Grapher/
  mkdir bin
  make
```
This will put an executable file called `main` in `bin/`. This is how to build
the project.

### Optional
As the image output format is netpbm which is rather uncommon, I would
recommend either:
1) Installing a netpbm image viewer
2) Installing ImageMagick to be able to convert the output file to a .png file.

If you would like to install a viewer:
```
  sudo apt install feh     (For Debian based i.e. Ubuntu, mint, etc.)
  sudo pacman -S feh       (For arch based i.e. Manjaro, Endevour, Garuda etc.)
  sudo xbps-install -S feh (Void)
```
And if you aren't on one of those distros I would imagine you are familiar with
your package manager (alpine, kiss, etc.).

If you want to install ImageMagick:
```
  sudo apt install imagemagick
  sudo pacman -S imagemagick
  sudo xbps-install -S imagemagick
```
etc.

And it is worth noting that to use ImageMagick to convert a netpbm file to a
.png it would be:
```
  convert example.ppm output_png_file.png
```

# :exclamation: Use
The program expects only one thing from the user and that is the input file.  So
once you build the executable you would run the program via:
```
  ./path_to/executable path_to/input_file.txt
```

Currently only one output file can be produced by one input file but that is on
the immediate list of features to be implemented.

An example input file is as follows with comments. Note that comments cannot be
in the file when sent into the utility.

One line is used to define each parameter to the given output file and always
needs to be prefaced with `FILE_NAME` followed with a space by the output file
name.  This file will need to be terminated with an `END`. Within this block


In the input file, there are two types of parameters, blocks (i.e. a name that
defines a block ended with `END`, for example `FUNC` terminated by `END`) and
single line assignments (just one line). The following shows custom parameters
for all acceped inputs 
```
  FILE_NAME :: test.ppm  // This line specifies the file name
    X_MIN   :: -10       // This line specifies the minimum x value that the
                         // graph will show
    Y_MIN   :: -10       // This line specifies the minimum y value that the
                         // graph will show
    X_MAX   ::  10       // This line specifies the maximum x value that the
                         // graph will show
    Y_MAX   ::  10       // This line specifies the maximum y value that the
                         // graph will show
    /**
     * There are two color options
     * 1) specify 1 color and all functions will be of that color, OR
     * 2) specify 1 color for each function and each function will be its
     *    corresponding color sequentially
     * In this example the second option was chosen
     */
    COLOR   :: 0,35,66
    COLOR   :: 255,0,0
    COLOR   :: 0,255,0
    COLOR   :: 0,0,255
    COLOR   :: 255,0,255
  END   // Necessary Tag
  FUNCS // Necessary Tag
    /**
     * In this block any number of functions can be specified.
     * The valid operators are +, -, *, /, sin, cos, tan, arcsin, arccos,
       arctan, log (log is only base 2 at the moment)
     * The variable is whatever (minus functions above) the user specifies so
     * long as it contains english Latin characters or `_`'s
     */
    (x - 1)^2 + 1
    (x + 1)^3 - 1
    x^4
    x^5
    2 * x + 1
  END // Necessary Tag
```
The above example without comments can be found in
`docs/example_graph_set/example_graph.txt`.  Additionally by running the
command:
```
  make run
```
After the project is built, it will take in the example file as input and output
in the current directory the file test.ppm corresponding to the example input
file.

# :mag: Technical Notes
This program uses the following context free grammar in BNF (I have left
factored it for readability with respect to the parser) via an LL(1) parser to
achieve the ability of reading in arbitrary user functions:
```
  E  -> T E'
  E' -> (+|-) T E' | $\epsilon$
  T  -> F T'
  T' -> (*|/) F T' | $\epsilon$
  F  -> (sin|cos|tan|arcsin|arccos|arctan|log)* (E) | id
  
  id -> Variable | Double
```

# :turtle: Currently Needed Improvements
The following features I will be implementing in the future:
- Accept Points as Input.
- Make support for calculus functions (`der`/`int`) for trancendental functions
  in the context free grammar.
- Relationships
- Vector Fields
- Write a better file I/O to include the ability for one input file to write to
  several output files.
- 3d support (very bottom of the list).

# :fireworks: Credits
- Compilers: Principles, Techniques, & Tools Second Edition Aho, Lam, Sethi,
  Ullman.  This book has been instrumental in my learning about interpreters,
  additionally I used one of their CFG's as a basic building block for the CFG
  used in this project.
