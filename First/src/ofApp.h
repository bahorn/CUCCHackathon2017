#pragma once

#include "ofMain.h"
/* my stuff */
#include "training.hpp"
#include "EEGStorage.hpp"

/* Addons */
#include "ofxOsc.h"



#include <ctime>

/* defines */
#define PORT 5001
#define INTERVAL 10

class ofApp : public ofBaseApp{

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        /* osc */
        ofxOscReceiver receiver;
        /* keyboard */
        bool keyDown[255];
    
        /* UI */
        ofTrueTypeFont userFont;
        ofTrueTypeFont predictionFont;
        /* graphs */
        ofPolyline graphs[4];
    
        /* state */
        int mode;
        int block_id;
        bool prevBlock_analysed;
        EEGStorage * EEGdata;
        EEGStorage * prevBlock;
        TrainingModel * model;
        int which;
    
};
