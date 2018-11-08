#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	sender.setup(HOST, PORT);

	video.load("countdown.mp4");
	video.setPaused(true);

	is_setting = true;
	selected = false;

	sendMessage(video.getPosition(), video.isPaused());
}

//--------------------------------------------------------------
void ofApp::update(){
	if (!selected) {
		video.update();
		if (video.getPosition() == 0) {
			sendMessage(video.getPosition(), video.isPaused());
		}
	}
	cursorPos = ofVec2f(ofGetWidth()*0.15 + ofGetWidth()*0.7*video.getPosition(), ofGetHeight()*0.9);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	video.draw(0, 0, ofGetWidth(), ofGetHeight());
	if (is_setting) {
		ofSetColor(0, 180);
		ofDrawRectangle(ofGetWidth()*0.1, ofGetHeight()*0.85, ofGetWidth()*0.8, ofGetHeight()*0.1);
		ofSetColor(255, 180);
		ofSetLineWidth(10);
		ofDrawLine(ofGetWidth()*0.15, ofGetHeight()*0.9, ofGetWidth()*0.85, ofGetHeight()*0.9);
		ofDrawCircle(cursorPos, 15);
		ofDrawBitmapString("It's sender", 20, 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'p') {
		if (video.isPaused()) {
			video.setPaused(false);
		}
		else {
			video.setPaused(true);
		}
		sendMessage(video.getPosition(), video.isPaused());
	}
	else if (key == 's') {
		is_setting = !is_setting;
		sendMessage(video.getPosition(), video.isPaused());
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (selected) {
		if (x >= ofGetWidth()*0.15 && x <= ofGetWidth()*0.85) {
			cursorPos.x = x;
			video.setPosition(((float)cursorPos.x - ofGetWidth()*0.15) / (ofGetWidth()*0.7));
		}
		else if (x < ofGetWidth()*0.15) {
			cursorPos.x = ofGetWidth()*0.15;
			video.setPosition(0.0);
		}
		else if (x > ofGetWidth()*0.85) {
			cursorPos.x = ofGetWidth()*0.85;
			video.setPosition(0.9999);
		}
		else {
			cout << "error" << endl;
		}
		sendMessage(video.getPosition(), video.isPaused());
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (is_setting) {
		cursorPos = ofVec2f(ofGetWidth()*0.15 + ofGetWidth()*0.7*video.getPosition(), ofGetHeight()*0.9);
		cout << cursorPos.distance(ofVec2f(x, y)) << endl;
		if (cursorPos.distance(ofVec2f(x, y)) < 16) {
			selected = true;
			video.setPaused(true);
			sendMessage(video.getPosition(), video.isPaused());
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	selected = false;
	sendMessage(video.getPosition(), video.isPaused());
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

void ofApp::sendMessage(float videoPos, bool isPaused) {
	ofxOscMessage m;
	
	m.setAddress("/state/isPaused");
	m.addBoolArg(video.isPaused());
	sender.sendMessage(m, false);
	m.clear();

	m.setAddress("/state/position");
	m.addFloatArg(video.getPosition());
	sender.sendMessage(m, false);
}