#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	camWidth 		= 640;	// try to grab at this size. 
	camHeight 		= 480;
	holdingBuffer		= 0;
	differentThreshold	= 10;
	alpha			= .5;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoOut 	= new unsigned char[camWidth*camHeight*3];
	videoBuffer	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);
	bufferTexture.allocate(camWidth,camHeight, GL_RGB);

}


//--------------------------------------------------------------
void testApp::update(){

	ofBackground(100,100,100);
	
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew()){
		unsigned char * pixels = vidGrabber.getPixels();
		applyFx(pixels);
		videoTexture.loadData(videoOut, camWidth,camHeight, GL_RGB);
		bufferTexture.loadData(videoBuffer, camWidth, camHeight, GL_RGB);
	}

}

unsigned char testApp::blend(unsigned char fg, unsigned char bg, float alpha){
	return fg;
}

void testApp::applyFx(unsigned char *pixels){
	int totalPixels = camWidth*camHeight*3;
	for (int i = 0; i < totalPixels; i+= 3){
		if(holdingBuffer){
/*
			if(videoBuffer[i] > 0 || videoBuffer[i+1] > 0 || videoBuffer[i+2] > 0){
				videoOut[i] = videoBuffer[i];
				videoOut[i+1] = videoBuffer[i+1];
				videoOut[i+2] = videoBuffer[i+2];
				continue;
			}*/
			if(different(videoOut[i], videoOut[i+1], videoOut[i+2], pixels[i], pixels[i+1], pixels[i+2])){
				videoOut[i] = videoBuffer[i] = pixels[i];
				videoOut[i+1] = videoBuffer[i+1] = pixels[i+1];
				videoOut[i+2] = videoBuffer[i+2] = pixels[i+2];
				continue;
			}
		} else {
			videoOut[i] =  pixels[i];
			videoOut[i+1] = pixels[i+1];
			videoOut[i+2] = pixels[i+2];
			continue;
		}
	}
}

bool testApp::different(unsigned char r1, unsigned char g1, unsigned char b1, unsigned char r2, unsigned char g2, unsigned char b2){
	unsigned char diff = r1 > r2 ? r1 - r2 : r2 - r1;
	if(diff > differentThreshold) return true;
	diff = g1 > g2 ? g1 - g2 : g2 - g1;
	if(diff > differentThreshold) return true;
	diff = b1 > b2 ? b1 - b2 : b2 - b1;
	if(diff > differentThreshold) return true;
	return false;
}
void testApp::holdBuffer(){
	if(holdingBuffer != 1){
	  clearBuffer();
	  holdingBuffer = 1;
	}
}
void testApp::releaseBuffer(){
	if(holdingBuffer == 1){
	  clearBuffer();
	  holdingBuffer = 0;
	}
}
void testApp::clearBuffer(){
	for (int i = 0; i < (camWidth*camHeight*3); i++){
		videoBuffer[i] = 0;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
	ofNoFill();
	vidGrabber.draw(20,20);
	videoTexture.draw(20+camWidth,20,camWidth,camHeight);
	bufferTexture.draw(20,20+camHeight,camWidth,camHeight);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	if (key == 'h' || key == 'H'){
		if(holdingBuffer == 1){
			releaseBuffer();
		} else {
			holdBuffer();
		}
	}
	if (key == ']' || key == '}'){
		differentThreshold++;
	}
	if (key == '[' || key == '{'){
		differentThreshold--;
	}
	if (key == 'p' || key == 'P'){
		alpha = alpha + .1 > 1 ? 1 : alpha + .1;
	}
	if (key == 'o' || key == 'P'){
		alpha = alpha - .1 < 0 ? 0 : alpha - .1;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
