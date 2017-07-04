# PixelSwapper

A simple image editor for Windows, Linux, and OSX.

PixelSwapper is a basic image manipulation program that was originally released on 
http://zetacentauri.com. It was downloaded more than 30,000 times before being
open-sourced.

It is written in C++ and uses wxWidgets for the user interface.

![PixelSwapper Screenshot](https://github.com/Xangis/PixelSwapper/blob/master/images/PixelSwapper1.png)

A pre-built Windows installer is available in the installer folder:

https://github.com/Xangis/PixelSwapper/blob/master/installer/PixelSwapper1.21Setup.exe

This software is released under the terms of the MIT License. See License.txt for
details.

## Features

- Supports BMP, GIF, ICO, IFF*, JPG, PCX, PNG, PNM, TGA, TIF, and XPM images.
-  Crop to any portion of the image.
-  Rotate clockwise and counterclockwise.
-  Mirror vertically and horizontally.
-  Resize to any dimension.
-  File format conversion.
-  Convert images to grayscale.
-  Easy-to-use interface makes image manipulation simple.
-  Allows paste from clipboard and drag-and-drop.
-  Printing and print preview of images.
-  Auto-scales images to fit on screen.

*IFF images are load-only.*

# Building

Building requires that wxWidgets 2.9+ be installed (3.0 preferred).  

## Linux

There is a Makefile for use on Linux and building should be as simple as running "make".

If your wx-config is in a different location than that in the Makfile, change the path 
in the Makefile.

To get the required wxWidgets development libraries on an Ubuntu or Debian-based 
system, run:

sudo apt-get install libwxgtk3.0-dev

## OSX

PixelSwapper has been built on OSX, but has not been tested extensively.

There is a Makefile.mac for use on OSX. Assuming you have a command-line C++ 
compiler installed, you can build the program by running "make -f Makefile.mac".

If your wx-config is in a different location than that in the Makfile, change 
the path in the Makefile.

Creating an application bundle requires some additional work and not everything
necessary is included. I expect to improve the process as I have time and
motivation.

## Windows

This should also build on Windows, after all, it was originally a Windows app, 
but you'll have to create your own Visual Studio project that uses all of the 
.h and .cpp files. That should be easy.  Setting paths and libraries in Visual 
Studio is the most annoying part of creating a project, and wxWidgets is a 
particular nuisance in that respect.

To get wxWidgets for Windows, download it here:

http://wxwidgets.org/downloads/

Installer scripts for Windows are under the "installer" folder.  There is one 
for the Nullsoft Install System (NSIS) and one for InnoSetup.  They may or may 
not be up to date, but chances are good that you'll have to fiddle with some 
paths (your VS project will probably put files into different places).

# Changelog

### Changes in version 1.21:

- Fixed a bug with file type selection in the "Save As" dialog.
- Filename now shows up in the window title when a file is opened.
- A thumbnail of the currently open file is now used as the window icon.

### Changes in version 1.2:

- Added support for saving GIF images.
- Added support for saving TGA images.
- Added support for saving and loading PNM images.
- Added support for loading IFF images.
- Changed some keyboard shortcuts to more closely match common Windows application shortcuts

### Changes in version 1.11:

- Improved spacing of size indicators on the status bar.

### Changes in version 1.1:

- Added support for loading and saving PCX images.
- Added support for loading TGA images.
- Added ability to convert an image to grayscale.
- Some user interface improvements.

# Development Status

I consider this application to be feature complete and am not actively developing new 
features for it. However, it does need some improvements to make it work and/or build 
better on some platforms (OSX and Windows, for example). This is something I may work 
on as I have time.

I do still maintain this application and will accept pull requests if you have improvements 
to contribute.
