#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height): width(width), height(height) {
  	d = XOpenDisplay(NULL);
  	if (d == NULL) {
    	cerr << "Cannot open display" << endl;
   		exit(1);
  	}
 	s = DefaultScreen(d);
  	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
     	                     BlackPixel(d, s), WhitePixel(d, s));
  	XSelectInput(d, w, ExposureMask | KeyPressMask);

  	Pixmap pix = XCreatePixmap(d,w,width,
        	height,DefaultDepth(d,DefaultScreen(d)));
	gc = XCreateGC(d, pix, 0, 0);

  	// Set up colours.
	const size_t numColours = 19;
  	XColor xcolour;
  	Colormap cmap;
  	char color_vals[numColours][15] = { // 15 is the max len between all c strings in the array
		"black", "white", "red", 
		"green", "blue", "cyan", 
		"yellow", "magenta", "orange", 
		"brown", "papayawhip", "tomato", 
		"darkorange", "lightsalmon", "yellowgreen", 
		"powderblue", "cadetblue", "darkslategray", 
		"grey19"
	};

  	cmap=DefaultColormap(d,DefaultScreen(d));
  	for(unsigned int i = 0; i < numColours; ++i) {
     	 if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         	cerr << "Bad colour: " << color_vals[i] << endl;
      	}
      	if (!XAllocColor(d,cmap,&xcolour)) {
        	 cerr << "Bad colour: " << color_vals[i] << endl;
      	}
      	colours[i] = xcolour.pixel;
  	}

  	// Make window non-resizeable.
  	XSizeHints hints;
  	hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  	XSetNormalHints(d, w, &hints);


	// display window and flush buffer
	XMapRaised(d,w);
	XFlush(d);

	// sleep to give server time to setup
	// must map window before sleep
	// 1000 is not enough on Linux systems
	// 10*1000 also occasionally does not work
	// 50*1000 should be safe
	// 100*1000 is extra safe, but delay is noticeable
	// sleep(1) (which is equivalent to usleep(1000*1000)) for maximum stability (but slow)
	usleep(50*1000);
}

Xwindow::~Xwindow() {
  	XFreeGC(d, gc);
  	XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
	XSetForeground(d, gc, colours[colour]);

	XFillRectangle(d, w, gc, x, y, width, height);

	// without even handling, always flush buffer after drawing
	XFlush(d);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);

    Font f = XLoadFont(d, "6x13");

    XTextItem ti;
    ti.chars = const_cast<char*>(msg.c_str());
    ti.nchars = msg.length();
    ti.delta = 0;
    ti.font = f;

    XDrawText(d, w, gc, x, y, &ti, 1);

	// without even handling, always flush buffer after drawing
    XFlush(d);
}

void Xwindow::drawBigString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);

    ostringstream name;
    name << "-*-helvetica-bold-r-*-*-*-240-"<< 60 << "-" << 60 << "-*-*-*-*";
    XFontStruct * f = XLoadQueryFont(d, name.str().c_str());

    XTextItem ti;
    ti.chars = const_cast<char*>(msg.c_str());
    ti.nchars = msg.length();
    ti.delta = 0;
    ti.font = f->fid;

    XDrawText(d, w, gc, x, y, &ti, 1);

	// without even handling, always flush buffer after drawing
    XFlush(d);

	// XLoadQueryFont heap allocates a XFontStruct, must free it
    XFreeFont(d, f);
}

void Xwindow::showAvailableFonts() {
	int count;
	char** fnts = XListFonts(d, "*", 10000, &count);

	for (int i = 0; i < count; ++i) cout << fnts[i] << endl;
}
