# :chart_with_upwards_trend: Project Goal
To make a netpbm library for graphing functions in C.

# :zap: Current Features
This program has the ability to graph any mathematical function written in C.
Currently there is no real front end to speak of. An example of making a plot
would look like
1) make a `graph_scale`
2) make a `canvas`
3) write the `graph_scale` to the `canvas`
4) write your custom function to be written to the plot of the form:
```
  double my_special_func_name(double my_input);
```
5) write the custom function to the graph using `write_rel_to_canvas`


Also worth noting as currently hard coded, no memory leaks (each struct the
program uses has its free method explicitly called).

# :turtle: Currently Needed Improvements
The following features I will be implementing in the future:
- The tic marks don't mean anything currently, the center of the two axes
  represents the center of the user defined range (i.e. if the user's range is
  [-1, 10] for the x axis the center of the x axis represents 4.5). Unfortunately
  as currently programmed, the tic marks are made before any data related to
  user scale (wrt the functions being written) is entered rendering them useless
  unless the user's range is symmetrical.
- Implement a context free grammar for bulk making plots via an input file.
  Possible input file could look like:
  ```
  PLOT 1 :: name1.ppm
  (x + 1)^2 + 2x - 3
  x^3
  1, 2
  3, 4
  --
  PLOT 2 :: name2.ppm
  x^2
  1, 2
  3, 4
  --
  ```
  Allowing the user to plot multiple points/functions per file and plot multiple
  files per user input file.
- Make support for calculus functions (`der`/`int`) in the context free grammar.
- Add support for vector fields.
- 3d support (very bottom of the list).
