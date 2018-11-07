#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    video.loadMovie("countdown.mp4");
    video.play();
	video.setLoopState(OF_LOOP_NORMAL);

	p[0].set(100, 100);
	p[1].set(100, 740);
	p[2].set(460, 740);
	p[3].set(460, 100);
	center.x = (p[0].x + p[1].x + p[2].x + p[3].x) / 4;
	center.y = (p[0].y + p[1].y + p[2].y + p[3].y) / 4;

	ofSetFrameRate(30);

	is_setting = true;
	selected = -1;
	std::cout << "setup" << endl;
}


//--------------------------------------------------------------
void ofApp::update(){

    video.update();

	mesh.addVertex(center);
	mesh.addVertex(p[0]);
	mesh.addVertex(p[1]);
	mesh.addVertex(p[2]);
	mesh.addVertex(p[3]);
	mesh.addVertex(p[0]);

	mesh.addTexCoord(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
	mesh.addTexCoord(ofVec2f(0, 0));
	mesh.addTexCoord(ofVec2f(0, ofGetHeight()));
	mesh.addTexCoord(ofVec2f(ofGetWidth(), ofGetHeight()));
	mesh.addTexCoord(ofVec2f(ofGetWidth(), 0));
	mesh.addTexCoord(ofVec2f(0, 0));
}



//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(255);
	video.draw(0, 0, ofGetWidth(), ofGetHeight());
	screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	ofBackground(0);

	ofSetColor(255);
	screen.bind();
    mesh.draw();
	screen.unbind();

	if (is_setting) {
		ofSetColor(255, 150, 150);
		ofNoFill();
		ofDrawCircle(center, 10);
		ofFill();
		for (int i = 0; i < 4; i++) {
			ofDrawCircle(p[i], 10);
		}
		ofSetColor(255);
		mesh.drawWireframe();
		ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 20, 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		is_setting = !is_setting;
	}

	if (key == 'p') {
		if (video.isPaused()) {
			video.setPaused(false);
		}
		else {
			video.setPaused(true);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (is_setting) {
		if (selected == 99) {
			center.x = x;
			center.y = y;
		}
		else if (selected != -1) {
			p[selected].x = x;
			p[selected].y = y;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	video.setPaused(true);
	for (int i = 0; i < 4; i++) {
		if (p[i].distance(ofVec3f(x, y, 0)) < 8) {
			selected = i;
			break;
		}
	}
	if (selected == -1 && center.distance(ofVec3f(x, y, 0)) < 8) {
		selected = 99;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (selected != 99 && selected != -1) {
		center.x = (p[0].x + p[1].x + p[2].x + p[3].x) / 4;
		center.y = (p[0].y + p[1].y + p[2].y + p[3].y) / 4;
	}
	selected = -1;
	mesh.clear();
	video.setPaused(false);
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