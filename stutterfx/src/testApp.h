#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		unsigned char blend(unsigned char fg, unsigned char bg, float alpha);
		void applyFx(unsigned char *pixels);
		bool different(unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2);
		void holdBuffer();
		void releaseBuffer();
		void clearBuffer();
		
		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoOut;
		unsigned char * 	videoBuffer;
		ofTexture		videoTexture;
		ofTexture		bufferTexture;
		int 			camWidth;
		int 			camHeight;
		int			holdingBuffer;
		unsigned char		differentThreshold;
		float			alpha;
		
};
