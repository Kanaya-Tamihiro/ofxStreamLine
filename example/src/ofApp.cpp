#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    option = new Option();
    option->xrange[0] = -4;
    option->xrange[1] = 4;
    option->yrange[0] = -4;
    option->yrange[1] = 4;
//    option->wideSeparation = 0.05;
//    option->narrowSeparation = 0.025;
//    option->stepsPerIteration = 1;
    option->randomSeed();
    option->vectorFunc = [](Vector point) {
        double x = point[0];
        double y = point[1];
        double a = 1.0;
        double b = 2.2;
        double dx = a - (b + 1) * x + std::pow(x, 2) * y;
        double dy = b * x - std::pow(x, 2) * y;
        return Vector(dx, dy);
    };
    option->onPointAdded = [&](Vector point, Vector prev) {
        points.push_back(point);
        points.push_back(prev);
        return false;
    };
    streamLine = new StreamLine(option);
}

//--------------------------------------------------------------
void ofApp::update() {
    streamLine->step();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    double* xrange = option->xrange;
    double* yrange = option->yrange;
    for (int i=0; i<points.size(); i=i+2) {
        Vector point = points[i];
        Vector prev = points[i+1];
        float x = (float) ((point.x-xrange[0]) / (xrange[1]-xrange[0]) * WIDTH);
        float y = (float) ((point.y-yrange[0]) / (yrange[1]-yrange[0]) * HEIGHT);
        float xx = (float) ((prev.x-xrange[0]) / (xrange[1]-xrange[0]) * WIDTH);
        float yy = (float) ((prev.y-yrange[0]) / (yrange[1]-yrange[0]) * HEIGHT);
        ofLine(x,y,xx,yy);
    }
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
