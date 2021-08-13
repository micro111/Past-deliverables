#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        ofTrueTypeFont title_f;
        ofTrueTypeFont score_f;
        ofTrueTypeFont level_f;
        int cnt,f,teki,teki_hit,color,start,color_f,on,fd,rand,g,eh,ew,pw,ph,sd,sound,level;//ofapp.cpp参照
        char str1[20];
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofImage p1,p2,p3,p4,e1,e2,e3,e4,e5;//プレーヤー、敵
        ofImage g1,g2,g3,g4,g5,g6,g7,g8,g9,g10,g11,g12,g13,g14,g15,g16,g17,g18,g19,g20;//鳥を回すよう
private:
        ofSoundPlayer s1,s2,s3,s4;//サウンド

};
