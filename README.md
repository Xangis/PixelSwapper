PixelSwapper
============

PixelSwapper is a basic image manipulation program that was originally released on 
http://zetacentauri.com

It is written in C++ and uses wxWidgets for the user interface.

![PixelSwapper Screenshot](https://github.com/Xangis/PixelSwapper/blob/master/images/PixelSwapper1.png)

A Windows installer is available in the installer folder.

Building requires that wxWidgets 2.9+ be installed.  There is a Makefile for use on Linux
and a Makefile.mac for use on OSX. If your wx-config is in a different location than that in
the Makfile, change the path in the Makefile.

This should also build on Windows, but you'll have to create your own Visual Studio project
that uses all of the .h and .cpp files. That should be easy.  Setting paths and libraries in
Visual Studio is the most annoying part of creating a project, and wxWidgets is a particular
nuisance in that respect.

PixelSwapper has been built for OSX before, but not recently since I stopped owning any Apple
hardware two years ago, so I cannot verify whether it builds there.  Chances are the makefile
needs some adjustments or the like.

Installers for Windows are under the "installer" folder.  There is one for the Nullsoft Install
System (NSIS) and one for InnoSetup.  They may or may not be up to date, but chances are good
that you'll have to fiddle with some paths (your VS project will probably put files into
different places).

This software is released under the terms of the MIT License.
