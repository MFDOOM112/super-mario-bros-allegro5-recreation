//CLASE LADRILLO!!!
#include<vector>
#include<sstream>
#include "BrickFragment.h"
class Brick{
	public:
		float bx, by;
		float icx, icy;
		float jumpOffset;
		int in;
    	bool movingUp;
    	bool bactive;
    	bool coinup;
    	bool ucactive;
    	bool pbig;
    	bool broken;
    	int Case;
    	int inc;
    	int frameDelaycoin;
    	int frameCountcoin;
    	int frameDelay;
   	    int frameCount;
   	    int countCoin;
   	    Hongo *hongo;
    	Flor *flor;
    	Star *estrella;
    	VidaExtra *vida;
    	std::vector<BrickFragment*> fragments;
    	    static ALLEGRO_BITMAP *brick[2];
    		static ALLEGRO_BITMAP *uCoin[4];
    		static ALLEGRO_BITMAP *b1;
    		static ALLEGRO_BITMAP *b2;
    		static ALLEGRO_BITMAP *b3;
    		static ALLEGRO_BITMAP *b4;
    		static ALLEGRO_SAMPLE *iCoin;
    		static ALLEGRO_SAMPLE *sBreak;
    		static ALLEGRO_SAMPLE *sAppear;
    	//Constructor
    	Brick(float bix, float biy, int cases){
    		bx = bix;
    		by = biy;
    		icx = bix+4;
        	icy = biy;
        	jumpOffset = 0;
        	movingUp = false;
        	bactive = true;
        	ucactive = true;
        	broken = false;
        	in = 0;
        	inc = 0;
        	frameDelay = 10;
        	frameCount = 0;
        	frameDelaycoin = 10;
        	frameCountcoin = 0;
        	countCoin = 15;
        	Case = cases;
        	coinup = false;
        	pbig = false;
			hongo = NULL;
        	flor = NULL;
        	estrella = NULL;
        	vida = NULL;
        	if (Case == 3) {
        	hongo = new Hongo(bx, by);
        	hongo->chassets();
        	hongo->emerging = false;
    		}
			if(Case == 4){
    		flor = new Flor(bx, by);
			flor->cfassets();
			flor->emerging = false; 	
			}
			if(Case == 5){
			estrella = new Star(bx, by);
			estrella->csassets();
			estrella->emerging = false;
			}
			if(Case == 6){
			vida = new VidaExtra(bx,by);
			vida->cvassets();
			vida->emerging = false;
			}
		}
		//Métodos
		static void cbassets() {
        for (int i=0;i<2; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "b" << ".png";
            brick[i] = al_load_bitmap(str.str().c_str());
        }
        for(int j=0;j<4;j++){
        	std::stringstream str;
            str << "Sprites/" <<j+1<<"uc"<<".png";
            uCoin[j] = al_load_bitmap(str.str().c_str());
		}
		b1 = al_load_bitmap("Sprites/r1.png");
		b2 = al_load_bitmap("Sprites/r2.png");
		b3 = al_load_bitmap("Sprites/r3.png");
		b4 = al_load_bitmap("Sprites/r4.png");
		iCoin = al_load_sample("Sounds/Coin.wav");
        sBreak = al_load_sample("Sounds/Break.wav");
        sAppear = al_load_sample("Sounds/Appear.wav");
    	}
    	static void ucbassets(){
    	for (int i=0;i<2; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "ub" << ".png";
            brick[i] = al_load_bitmap(str.str().c_str());
        }
        for(int j=0;j<9;j++){
        	std::stringstream str;
            str << "Sprites/" <<j+1<<"uc"<<".png";
            uCoin[j] = al_load_bitmap(str.str().c_str());
		}
		b1 = al_load_bitmap("Sprites/ur1.png");
		b2 = al_load_bitmap("Sprites/ur2.png");
		b3 = al_load_bitmap("Sprites/ur3.png");
		b4 = al_load_bitmap("Sprites/ur4.png");
		iCoin = al_load_sample("Sounds/Coin.wav");
        sBreak = al_load_sample("Sounds/Break.wav");
        sAppear = al_load_sample("Sounds/Appear.wav");
		}
		static void ccbassets(){
    	for (int i=0;i<2; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "cb" << ".png";
            brick[i] = al_load_bitmap(str.str().c_str());
        }
        for(int j=0;j<9;j++){
        	std::stringstream str;
            str << "Sprites/" <<j+1<<"uc"<<".png";
            uCoin[j] = al_load_bitmap(str.str().c_str());
		}
		b1 = al_load_bitmap("Sprites/cr1.png");
		b2 = al_load_bitmap("Sprites/cr2.png");
		b3 = al_load_bitmap("Sprites/cr3.png");
		b4 = al_load_bitmap("Sprites/cr4.png");
		iCoin = al_load_sample("Sounds/Coin.wav");
        sBreak = al_load_sample("Sounds/Break.wav");
        sAppear = al_load_sample("Sounds/Appear.wav");
		}
    static void desbassets() {
        for (int i = 0; i < 2; i++) {
            al_destroy_bitmap(brick[i]);
        }
        for(int i=0;i<4;i++){
        	al_destroy_bitmap(uCoin[i]);
		}
		if (b1) al_destroy_bitmap(b1);
    	if (b2) al_destroy_bitmap(b2);
    	if (b3) al_destroy_bitmap(b3);
    	if (b4) al_destroy_bitmap(b4);
		if (iCoin) al_destroy_sample(iCoin);
        if (sBreak) al_destroy_sample(sBreak);
        if (sAppear) al_destroy_sample(sAppear);
	}
	~Brick() {
    	if(hongo){
        	hongo->deshassets();
		}
		if(flor){
			flor->desfassets();
		}
		if(estrella){
			estrella->dessassets();
		}
		if(vida){
			vida->desvassets();
		}
    for (size_t i = 0; i < fragments.size(); i++) {
        delete fragments[i];
    }
    fragments.clear();
	}
	void breakBrick(){
		if (broken) return;
    	al_play_sample(sBreak, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    	fragments.push_back(new BrickFragment(bx, by, -3, -6, b1));
    	fragments.push_back(new BrickFragment(bx, by, -2, -3, b3)); 
    	fragments.push_back(new BrickFragment(bx, by,  2, -3, b2)); 
    	fragments.push_back(new BrickFragment(bx, by,  3, -6, b4));
    	frameCount = 0;
    	frameDelay = 25;
    	broken = true;
	}
	void bdraw() {
		if(hongo && (hongo->hactive || hongo->emerging)) hongo->hdraw();
		if(flor && (flor->factive || flor->emerging)) flor->fdraw();
		if(estrella && (estrella->sactive || estrella->emerging)) estrella->sdraw();
		if(vida && (vida->vactive || vida->emerging)) vida->vdraw();
	   	if(!broken){
	   		al_draw_bitmap(brick[in], bx, by - jumpOffset, 0);
		}
        if(!bactive){
        	in = 1;
		}
	for (size_t i = 0; i < fragments.size(); i++) {
    fragments[i]->draw();
		}
        if (movingUp) {
            jumpOffset += 1.5;
            if (jumpOffset >= 6) {
                movingUp = false;
            }
        } else if (jumpOffset > 0) {
            jumpOffset -= 1.5;
            if (jumpOffset < 0) jumpOffset = 0;
        }
        if(coinup && ucactive){
        	icy-=3;
        	al_draw_bitmap(uCoin[inc],icx,icy,0);
        	if(icy>=18){
        		frameCountcoin++;
        		if(frameCountcoin>=frameDelaycoin){
        			frameCountcoin = 0;
        			inc++;
        			if(inc>=3){
        				in = 0;
        				ucactive = false;
					}
				}
			}
		}
		}
		void bupdate(){
			if(vida && (vida->vactive || vida->emerging)){
			vida->vupdate();
			}
			if (hongo && (hongo->hactive||hongo->emerging)) {
        	hongo->hupdate();
    		}
    		if(flor && (flor->factive||flor->emerging)){
    		flor->fupdate();
			}
			if(estrella && (estrella->sactive || estrella->emerging)){
			estrella->supdate();
			}
			for (size_t i = 0; i < fragments.size(); i++) {
    		fragments[i]->update();
			}
		}
		bool readytoRemove(){
			if (!broken) return false;
    		if (frameCount < frameDelay) {
        		frameCount++;
        		return false;
    		}
    		return true;
		}
		void bobject() {
		    if (!bactive){
        	return;
			}
        switch (Case) {
        	case 1:
        		if (pbig) {
        		breakBrick();
    			}
        		break;
            case 2:
                al_play_sample(iCoin, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                countCoin--;
                if(countCoin>=0){
                	coinup = true;
				}else{
					coinup = false;
					bactive = false;
				}
                break;
          	case 3:
            	al_play_sample(sAppear, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            	hongo->emerging = true;
            	break;
            case 4:
            	al_play_sample(sAppear, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            	flor->emerging = true;
            	break;
            case 5:
            	al_play_sample(sAppear, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            	estrella->emerging = true;
            	break;
            case 6:
            	al_play_sample(sAppear, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            	vida->emerging = true;
            	break;
            case 7: break;
        }
        movingUp = true;
		if(Case == 3 || Case == 4 || Case == 5 || Case == 6){
			bactive = false;
		} 
    }
};
ALLEGRO_BITMAP* Brick::brick[2] = { NULL, NULL };
ALLEGRO_BITMAP* Brick::uCoin[4] = { NULL, NULL, NULL, NULL };
ALLEGRO_BITMAP* Brick::b1 = NULL;
ALLEGRO_BITMAP* Brick::b2 = NULL;
ALLEGRO_BITMAP* Brick::b3 = NULL;
ALLEGRO_BITMAP* Brick::b4 = NULL;
ALLEGRO_SAMPLE* Brick::iCoin = NULL;
ALLEGRO_SAMPLE* Brick::sBreak = NULL;
ALLEGRO_SAMPLE* Brick::sAppear = NULL;

