Brady Messer (wmesser@clemson.edu)

The code reads in an image from a file and displays it centered in a window.
The user can then choose a new image to display, write the image to a file, or quit.

To run the code compile imgview.cpp, then run the executable either with no command
line arguments or with one argument which should be the name of the image file to display.
Running `make` will compile the program, then running `make test` will run the program
multiple times with all of the provided test images as command line arguments, and
one run without a command line argument.

Keyboard controls:
  q, Q, escape - closes the image window
  r, R - read in a new image and display it
  w, W - write the displayed image to a file

Errors:
  Trying to write an image to file without an extension will cause the program to exit
  Example: Typing in "out" as the name of the output file exits, typing "out.png" works

  Trying to read a file that doesn't exist will cause the program to exit

  Trying to write to a file without an image will create the file but it will be empty
  Example: Running ./imgview without command line arguments then writing to file
