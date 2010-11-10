#Overview

Shotput image processor... more to come.

#Usage

To compile use  gcc -o shotput_processor shotput_processor.c -O 'GraphicsMagick-config --cppflags --ldflags --libs'

To run use   ./shotput_processor -s source-image -w width -h height -o output.jpg
(Must specify at least 1 dimension)

#Dependencies

zlib
 
libpng

jpeg-8b 
