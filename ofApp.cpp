#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 400, true, true, true);
	string word = "A";

	auto path_list = font.getStringAsPoints(word, true, false);
	ofColor color;
	for (auto path : path_list) {

		auto outline = path.getOutline();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			outline[outline_index] = outline[outline_index].getResampledByCount(1000);
			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				this->base_location_list.push_back(glm::vec2(
					vertices[vertices_index].x - this->font.stringWidth(word) * 0.5,
					vertices[vertices_index].y + this->font.stringHeight(word) * 0.5));
			}
		}
	}
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofColor color;
	for (int i = 0; i < 5; i++) {

		auto noise_seed = ofRandom(1000);
		color.setHsb(ofMap(i, 0, 5, 0, 255), 125, 255);
		for (auto location : this->base_location_list) {

			vector<glm::vec2> vertices;
			vertices.push_back(location);
			for (int i = 0; i < 100; i++) {

				auto deg = ofMap(ofNoise(noise_seed, vertices.back().x * 0.005, vertices.back().y * 0.005, ofGetFrameNum() * 0.015), 0, 1, -360, 360);
				auto vertex = vertices.back() + glm::vec2(2 * cos(deg * DEG_TO_RAD), 2 * sin(deg * DEG_TO_RAD));
				vertices.push_back(vertex);
			}

			ofSetColor(color, 16);
			ofNoFill();

			ofBeginShape();
			ofVertices(vertices);
			ofEndShape();
		}
	}

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}