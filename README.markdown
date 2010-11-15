#Overview

Shotput image processor. This version has the ability to resize images based on 3 strategies. crop, fit, and stretch.

#Usage

To compile use  gcc -o shotput_processor shotput_processor.c -O 'GraphicsMagick-config --cppflags --ldflags --libs'

To run use   ./shotput_processor -s source-image -w width -h height -st strategy -o output.jpg

##Strategies

* crop - Centers the image within the specified crop frame.
* strecth - Ignores aspect ratio and resizes the image to the exact width and height.
* Fit - Preserves aspect ratio and resizes to a given width or height. 


#Dependencies

zlib
 
libpng

jpeg-8b 
