#Currency Converter#
This is a simple currency calculator written in C. It updates its database from the European Central Bank's API.

##How To Use##
![Usage GIF](https://i.imgur.com/AsF86cz.gif)

##Dependencies##
Currency Converter only needs `libxml2`.

##Compiling##
1. Running `make` or `make compile` will compile the code and leave an executable called _currency_.
2. Running `make run` will compile the code and run the executable in one step.
3. Running `make test` will compile the code and perform memory tests using _valgrind_.
4. Running `make clean` will remove the executable and only leave the code files.
5. Running `make install` will install Currency Converter to _usr/local/bin_ and running `make uninstall` will remove it.
