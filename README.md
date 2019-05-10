This is a program to convert pixel positions into real space coordinates.
Jonathan Schilling (jonathan.schilling@ipp.mpg.de)

# USEAGE

adjust geometry (see description below) in mainwindow.cpp
```
> cd /some/path/which/contains/many/png/images/
> /path/to/img_to_coord *.png
```

The program starts with a GUI and shows the first image given on the command line.
A green rectangle illustrates the region defined by ((x_start, y_start) ... (x_end, y_end)) in mainwindow.cpp .
This corresponds to a width and height given by (x_dim, y_dim) in mainwindow.cpp .
No offset of the rectangle real space location can be specified at the moment.
The transform equation is given in lines 93-94 of mainwindow.cpp .

A left-click with the mouse somewhere in the picture is recorded and transformed into real-space
coordinates and appended to the file "positions.dat" in the current working directory.
If you think you made a mistake or clicked accidentally, you can right-click somewhere in the image.
The position of that right-click is not recorded, but the previous image is loaded and you can try again.

At the end of the list of images given on the command line, the image loader wraps around and loads the first image again.

# BUILDING

```
> qmake img_to_coord.pro
> make
```

--> gives you an executable img_to_coord
