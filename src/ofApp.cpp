#include "ofApp.h"


vector<ofVbo> vbos;
ofVboMesh voroMesh;
vector<int> counters;
int counter;
//ofFloatColor c;
vector<ofFloatColor> colors;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofxVoronoi / example_basic");
    ofBackground(255);
    
    ofRectangle bounds = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
    
    int pointCount = ofRandom(100,200);
    int seed = ofRandom(33);
    
    vector<ofPoint> points = generateRandomPoints(pointCount, seed, bounds);
    
    voronoi.setBounds(bounds);
    voronoi.setPoints(points);
    
    voronoi.generate();
    vector <ofxVoronoiCell> cells = voronoi.getCells();

    for (int i = 0; i < cells.size(); i++) {
        ofFloatColor c = ofFloatColor( ofRandom(0.0,1.0), ofRandom(0.0,1.0), ofRandom(0.0,1.0) );
        colors.push_back(c);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vector <ofxVoronoiCell> cells = voronoi.getCells();
    ofRectangle bounds = voronoi.getBounds();
    
    ofSetLineWidth(0);
    ofFill();
    
    for(int i=0; i<cells.size(); i++) {
        // Draw cell borders
        ofVbo vbo;
        int counter = 0;
        for(int j=0; j<cells[i].pts.size(); j++) {
            ofPoint lastPt = cells[i].pts[cells[i].pts.size()-1];
            if(j > 0) {
                lastPt = cells[i].pts[j-1];
            }
            ofPoint thisPt = cells[i].pts[j];
            
            if(!isBorder(lastPt) || !isBorder(thisPt)) {
                voroMesh.addVertex(lastPt);
                voroMesh.addColor(colors[i]);
                counter++;
                voroMesh.addVertex(thisPt);
                voroMesh.addColor(colors[i]);
                counter++;
            }
            
            
            vbo.setMesh(voroMesh, GL_DYNAMIC_DRAW);
            vbos.push_back(vbo);
            counters.push_back(counter);
            
        }
        vbo.clear();
        voroMesh.clear();
        counter = 0;
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    for (int i = 0; i < vbos.size(); i++) {
        vbos[i].draw(GL_POLYGON, 0, counters[i]);
    }
}

//--------------------------------------------------------------
vector <ofPoint> ofApp::generateRandomPoints(int count, int seed, ofRectangle bounds) {
    vector <ofPoint> points;
    ofSeedRandom(seed);
    
    for(int i=0; i<count; i++) {
        ofPoint newPoint = ofPoint(
                                   ofRandom(bounds.x, bounds.width),
                                   ofRandom(bounds.y, bounds.height)
                                   );
        
        points.push_back(newPoint);
    }
    
    return points;
}

//--------------------------------------------------------------
bool ofApp::isBorder(ofPoint _pt){
    ofRectangle bounds = voronoi.getBounds();
    
    return (_pt.x == bounds.x || _pt.x == bounds.x+bounds.width
            || _pt.y == bounds.y || _pt.y == bounds.y+bounds.height);
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
    vbos.clear();
    voroMesh.clear();
    counters.clear();
    colors.clear();
    counter = 0;
    //c = ofFloatColor(0,0,0);
    ofRectangle bounds = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
    
    int pointCount = ofRandom(100,200);
    int seed = ofRandom(33);
    
    vector<ofPoint> points = generateRandomPoints(pointCount, seed, bounds);
    
    voronoi.setBounds(bounds);
    voronoi.setPoints(points);
    
    voronoi.generate();
    
    vector <ofxVoronoiCell> cells = voronoi.getCells();
    
    for (int i = 0; i < cells.size(); i++) {
        ofFloatColor c = ofFloatColor( ofRandom(0.0,1.0), ofRandom(0.0,1.0), ofRandom(0.0,1.0) );
        colors.push_back(c);
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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