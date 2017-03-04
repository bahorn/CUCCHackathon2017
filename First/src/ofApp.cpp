#include "ofApp.h"
#include <iostream>
//--------------------------------------------------------------
void ofApp::setup(){
    /* inital variables */
    mode = -1;
    block_id = 0;
    prevBlock = nullptr;
    prevBlock_analysed = false;
    which = -1;
    /** UI */
    ofBackground(0x000);
    ofSetWindowTitle("EEG calmness thing");
    /* fonts */
    userFont.load("AndaleMono.ttf",32);
    predictionFont.load("AndaleMono.ttf",32);
    /* Set the up the basic state */
    model = new TrainingModel();
    EEGdata = new EEGStorage(INTERVAL, mode);
    /* Connect to the fun device. */
    receiver.setup(PORT);

}

//--------------------------------------------------------------
void ofApp::update(){
    int i;
    ofxOscMessage tempMsg;
    EEGItem eegValues;
    
    /** keyboard **/
    // make it a clam one.
    if (keyDown['z']) {
        EEGdata->type = 0;
        keyDown['z'] = false;
    }
    // evaluate this cycle.
    if (keyDown['x']) {
        EEGdata->type = 2;
        keyDown['x'] = false;
    }
    // clear
    if (keyDown['c']) {
        EEGdata->type = -1;
        keyDown['c'] = false;
    }
    if (keyDown['v']) {
        delete model;
        delete EEGdata;
        model = new TrainingModel();
        EEGdata = new EEGStorage(INTERVAL, mode);
        keyDown['v'] = false;
        
    }
    
    /** handle this block of data **/
    if (EEGdata->endTime < std::time(nullptr)) {
        switch (EEGdata->type) {
            case 0:
                prevBlock_analysed = false;
                model->addTrainingData(0, EEGdata);
                mode = -1;
                which = 0;
            case 2:
                which = model->evaluateData(EEGdata);
                mode = 2;
                block_id += 1;
                prevBlock_analysed = true;
                EEGdata = new EEGStorage(INTERVAL, mode);
                prevBlock = EEGdata;
                break;
            default:
                which = -1;
                block_id += 1;
                // update draw block
                delete prevBlock;
                prevBlock = EEGdata;
                // reset and free
                EEGdata = new EEGStorage(INTERVAL, mode);
                break;
        }
    }
    
    /** deal with the messages **/
    while (receiver.hasWaitingMessages()) {
        receiver.getNextMessage(tempMsg);
        /* get the raw ECG messages */
        if (tempMsg.getAddress() == "/muse/eeg") {
            /* read the values */
            for (i = 0; i <= 3; i++) {
                /* constant comes form:
                 http://developer.choosemuse.com/research-tools/available-data#Raw_EEG
                 */
                eegValues.content[i] = tempMsg.getArgAsFloat(i)/1682.815;
            }
            eegValues.timestamp = std::time(nullptr);
            EEGdata->addItem(eegValues);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    int i;
    
    std::string message;
    std::string blockTypes[] = {"Ignored", "Calming-Training", "Not Calming - Training", "To be Analysed"};
    std::string whichthing[] = {"Unknown", "calm", "not calm"};
    /* Draw information about the current block */
    ofSetColor(255, 255, 255);
    message += "Block ID: "+std::to_string(block_id)+"\n";
    message += "Current Block type: "+blockTypes[EEGdata->type+1]+"\n";
    message += "\n";
    if (prevBlock_analysed) {
        //message += whichthing[which+1];
    }
    userFont.drawString(message, 50, 50);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    keyDown[key] = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    keyDown[key] = false;
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
