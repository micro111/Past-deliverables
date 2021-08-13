#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    s1.loadSound("1.mp3");//初期音
    s1.setVolume(0.8f);//音量
    s1.setMultiPlay(false);
    s2.loadSound("2.mp3");//初期音
    s2.setVolume(0.8f);
    s2.setMultiPlay(false);
    s3.loadSound("3.mp3");//打つ時の音
    s3.setVolume(0.8f);
    s3.setMultiPlay(false);
    s4.loadSound("4.mp3");//決着
    s4.setVolume(0.8f);
    s4.setMultiPlay(false);


    title_f.load("yakitori.ttf",128);//打つ時の
    if(title_f.isLoaded()){
        cout<<"title font loaded"<<endl;
    }else{
        cout<<"title font not loaded"<<endl;
    }
    level_f.load("yakitori.ttf",72);//ただしがき
    if(level_f.isLoaded()){
        cout<<"title font loaded"<<endl;
    }else{
        cout<<"title font not loaded"<<endl;
    }
    score_f.load("yakitori.ttf",72);//win loseer
    if(score_f.isLoaded()){
        cout<<"title font loaded"<<endl;
    }else{
        cout<<"title font not loaded"<<endl;
    }
    on=0;//押したかどうか
    cnt=0;//打つタイミング
    f=0;//フラグ
    sd=0;//一度のみ実行
    sound=0;//一度のみ
    fd=0;//表示用フラグ
    start=0;//スタートフラグ
    teki=120;//敵の誤差フレーム
    teki_hit=0;//実際に敵が入力するタイミング
    color_f=0;//初期化用
    color=255;//案転用
    ph=50;//プレーヤー画像の高さ
    pw=50;//プレーヤー画像の横
    level=3;//初期レベル
    eh=30;//敵よこ（順番ミス）
    ew=50;//敵高さ
    g=10;//gif用
    g1.load("1.gif");//動く鳥
    g2.load("2.gif");
    g3.load("3.gif");
    g4.load("4.gif");
    g5.load("5.gif");
    g6.load("6.gif");
    g7.load("7.gif");
    g8.load("8.gif");
    g9.load("9.gif");
    g10.load("10.gif");
    g11.load("11.gif");
    g12.load("12.gif");
    g13.load("13.gif");
    g14.load("14.gif");
    g15.load("15.gif");
    g16.load("16.gif");
    g17.load("17.gif");
    g18.load("18.gif");
    g19.load("19.gif");
    g20.load("20.gif");

    e1.load("01.png");//敵種類
    e2.load("02.png");
    e3.load("03.png");
    e4.load("04.png");
    e5.load("lo.png");
    p1.load("1.png");//プレーヤー
    p2.load("2.png");
    p3.load("3.png");
    p4.load("4.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    if(start==0){//スタートフラグ
       if(f==0){//乱数用
           s1.play();//準備音
           s2.play();//準備音
            rand=ofRandom(1,5);//敵決め
            cnt=ofRandom(60,600);//打つタイミングを１秒から１０秒の中でフレームで指定
            fd=0;//準備用テキスト
            teki_hit=cnt+teki;//敵の誤差決め
            teki=teki/2;//次のレベルの誤差を決める
            f=1;//乱数生成したので次は下へ
        }else{
           if(cnt==0){//打つ時かどうか
               fd=4;//打つ時なのでpush!!っと画面に
               if(sound==0){//いっかいのみならす
                  s3.play();//打つ時の音
                  sound=1;//次は入らないように
               }

               if(teki_hit==0){//敵が打つ時になった
                   if(sd==0){//音を一回だけ
                   teki=teki*4;//負けたのでレベルを下げて敵が打つ時間を二倍にする
                   level-=1;
                   s4.play();//音をならス
                   sd=1;//一回のみ
                   }

                   fd=2;//youlose を出す
                   start=1;//初期化させる
               }else{//敵が打つ前に
                   if(on==1){//左コントロールを押した
                       if(sd==0){//一回のみ
                           level+=1;//レベルを上げる
                       s4.play();//音なラス
                       sd=1;//一度のみ
                       }
                         fd=1;//you winをだす
                        start=1;//初期化させる
                    }else{
                        teki_hit--;//敵の猶予をなくしていく
                    }
               }
           }else{//cntが0になる前に押された（お手付き）
               if(on==1){//おされた
                   fd=3;//sofastとだす

                   if(sd==0){//一回のみ
                   s4.play();//音を鳴らす
                   teki=teki*2;//仕切りなおすため戻す
                   sd=1;//一回のみ
                   }

                   start=1;//初期化
               }
               cnt--;//打つタイミングまで減らす
               teki_hit--;//敵も減らす
           }
       }

    }else{
        if(color_f==0){//案転用
            color=0;//初期値
            color_f=1;//一回のみの初期化
        }else{
            color+=3;//どんどん透明度を上げる
            if(color>254){//完全に透明になるまで
                f=0;//初期化
                on=0;//初期化
                g=10;//初期化
                color_f=0;//初期化
                start=0;//初期化
                fd=0;//初期化
                sd=0;//初期化
                sound=0;//初期化

            }
        }

    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0,0,0,255);//黒
    level_f.drawString("Push Left Control...",30,100);//但し書き
    ofSetColor(130,120,150,255);//色変える
    sprintf(str1,"level:%d%",level);//レベルを出す配列
    level_f.drawString(str1,20,200);//表示
    ofSetColor(255,255,255,255);//色を戻す
    if(fd==0){//準備
    score_f.drawString("Stand by....",ofGetWidth()/2-60,300);
    p1.draw(ofGetWidth()/2-pw,ofGetHeight()/2-ph);
    switch(rand){//敵をランダムで決める
            case 1:
            e1.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        break;
            case 2:
            e2.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        break;
            case 3:
            e3.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        break;
            case 4:
            e4.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
    }

    }else if(fd==1){//勝ったとき
    p2.draw(ofGetWidth()/2-pw,ofGetHeight()/2-ph);
    e5.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
    ofSetColor(255,10,10,255);
    score_f.drawString("You WIN!!",ofGetWidth()/2-60,300);
    ofSetColor(255,255,255,255);
    }else if(fd==2){//負けた時
    ofSetColor(10,10,255,255);
    score_f.drawString("You lose...",ofGetWidth()/2-60,300);
    ofSetColor(255,255,255,255);
    switch(g){//gifを回すため
    case 1:
        g1.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g2.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 2:
        g2.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g3.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 3:
        g3.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g4.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 4:
        g4.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g5.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 5:
        g5.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g6.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 6:
        g6.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g7.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 7:
        g7.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g8.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 8:
        g8.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g9.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 9:
        g9.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g10.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 10:
        g10.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g11.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 11:
        g11.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g12.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 12:
        g12.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g13.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 13:
        g13.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g14.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 14:
        g14.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g15.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 15:
        g15.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g16.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 16:
        g16.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g17.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 17:
        g17.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g18.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 18:
        g18.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g19.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 19:
        g19.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g20.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
    case 20:
        g20.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        g1.draw(ofGetWidth()/2-eh+30,ofGetHeight()/2-ew);
        break;
     }
    if(g==1){//次の画像がないためループさせる
      g=19;
    }
    p3.draw(ofGetWidth()/2-pw,ofGetHeight()/2-ph);
    g--;

    }else if(fd==3){//お手付き
        switch(g){//鳥を回す
        case 1:
            g1.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 2:
            g2.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 3:
            g3.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 4:
            g4.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 5:
            g5.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 6:
            g6.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 7:
            g7.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 8:
            g8.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 9:
            g9.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 10:
            g10.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 11:
            g11.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 12:
            g12.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 13:
            g13.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 14:
            g14.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 15:
            g15.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 16:
            g16.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 17:
            g17.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 18:
            g18.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 19:
            g19.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
        case 20:
            g20.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
            break;
         }
        if(g>=20){//次の画像がないので戻す
          g=1;
        }
        g++;
    score_f.drawString("",ofGetWidth()/2-60,100);//文字を消す
    title_f.drawString("So fast..",ofGetWidth()/2,ofGetHeight()/2);//表示
    p4.draw(ofGetWidth()/2-pw,ofGetHeight()/2-ph);


    }else if(fd==4){//おせ！！の文字

    score_f.drawString("",ofGetWidth()/2-60,100);

    p1.draw(ofGetWidth()/2-pw,ofGetHeight()/2-ph);
    switch(rand){//敵をランダムに置く
            case 1:
            e1.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        break;
            case 2:
            e2.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        break;
            case 3:
            e3.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
        break;
            case 4:
            e4.draw(ofGetWidth()/2-eh,ofGetHeight()/2-ew);
    }
    title_f.drawString("PUSH!!!!!!!!!!!",450,ofGetHeight()/2);
    }


    if(start==1){//初期化
        if(color_f==0){//updateより速く動いて一瞬光ってしまうのを防ぐ

        }else{
        ofSetRectMode(OF_RECTMODE_CENTER);//画面を覆うように
        ofSetColor(0,0,0,color);//透過していく
        ofFill();
        ofDrawRectangle(ofGetWidth()/2,ofGetHeight()/2,1920,1080);
        ofSetRectMode(OF_RECTMODE_CORNER);


    }
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch(key){
     case OF_KEY_CONTROL://左CONTROLしたとき
         on=1;
         break;
     case OF_KEY_F1://強制初期化
         start=1;
         level=3;
         teki=120;
         break;
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
