#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	video.load("countdown.mp4");
	video.setPaused(true);

	current_msg_string = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	video.update();
	
	// hide old messages
	for (int i = 0; i < NUM_MSG_STRINGS; i++) {
		if (timers[i] < ofGetElapsedTimef()) {
			msg_strings[i] = "";
		}
	}
	
	while (receiver.hasWaitingMessages()) {
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);
		if (m.getAddress() == "/state/isPaused") {
			video.setPaused(m.getArgAsBool(0));
		}

		// check for mouse moved message
		if (m.getAddress() == "/state/position") {
			video.setPosition(m.getArgAsFloat(0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	video.draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
