# appy
Gtk+ application launcher menu written in C++

### Requirements:
* C++14 compliant compiler
* gtkmm3

### Compiling:

`$ g++ *.cpp -std=c++14 $(pkg-config gtkmm-3.0 --cflags --libs) -o appy`

You may also want to use the -s and -Bdynamic switches to avoid a huge executable size:

`$ g++ *.cpp -std=c++14 $(pkg-config gtkmm-3.0 --cflags --libs) -s -Bdynamic appy`

### Running:

./appy
