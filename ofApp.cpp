#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(0.25);
	ofEnableDepthTest();
	
	ofIcoSpherePrimitive ico_sphere = ofIcoSpherePrimitive(230, 4);
	this->mesh = ico_sphere.getMesh();

	ofSetSmoothLighting(true);
	r_light.setSpecularColor(ofColor(255, 0, 0));
	r_light.setDiffuseColor(ofColor(172, 0, 0));
	r_light.setAmbientColor(ofColor(39));
	r_light.enable();

	g_light.setSpecularColor(ofColor(0, 255, 0));
	g_light.setDiffuseColor(ofColor(0, 172, 0));
	g_light.setAmbientColor(ofColor(39));
	g_light.enable();

	b_light.setSpecularColor(ofColor(0, 0, 255));
	b_light.setDiffuseColor(ofColor(0, 0, 172));
	b_light.setAmbientColor(ofColor(39));
	b_light.enable();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	auto r_location = glm::vec3(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -300, 300),
		ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -300, 300),
		ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, 300));
	r_light.setPosition(glm::normalize(r_location) * 300);

	auto g_location = glm::vec3(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -300, 300),
		ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -300, 300),
		ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, 300));
	g_light.setPosition(glm::normalize(g_location) * 300);

	auto b_location = glm::vec3(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -300, 300),
		ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -300, 300),
		ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, 300));
	b_light.setPosition(glm::normalize(b_location) * 300);

	this->draw_mesh = this->mesh;
	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		auto vertex = this->mesh.getVertex(i);
		auto noise_value = ofNoise(glm::vec4(vertex * 0.03, ofGetFrameNum() * 0.005));
		auto noise_vertex = glm::normalize(vertex) * (230 * noise_value);

		this->draw_mesh.setVertex(i, noise_vertex);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(255, 0, 0);
	ofDrawSphere(this->r_light.getPosition(), 10);

	ofSetColor(0, 255, 0);
	ofDrawSphere(this->g_light.getPosition(), 10);

	ofSetColor(0, 0, 255);
	ofDrawSphere(this->b_light.getPosition(), 10);

	ofSetColor(255);
	this->draw_mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}