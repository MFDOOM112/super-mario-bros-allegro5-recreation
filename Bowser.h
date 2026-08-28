//CLASE BOWSER!!!
#include <sstream>
#include "Llama.h"
class Bowser{
	public:
	float x,y;
	float lx, ly;
	float speedx;
	float speedy;
	float xmax;
	float gravity;
	float inposx;
	float jumpSpeed;
	int in;
	int ind;
	int dir;
	int dCount;
	int frameCount;
	int frameDelay;
	int fireCount;
	int fireDelay;
	int restCount;
	int restDelay;
	bool onGround;
	bool active;
	bool shoot;
	bool dead;
	bool battle;
	int jumpCounter;
	int jumpIntervalFrames;
	static ALLEGRO_BITMAP* bowser[14];
	static ALLEGRO_SAMPLE* shooting;
	std::vector<Llama*> llamas;
	//Constructor
	Bowser(float inx, float iny){
		x = inx;
		y = iny;
		inposx = inx+30;
		xmax = x-150;
		in = 0;
		frameCount = 0;
		frameDelay = 10;
		dir = -1;
		fireCount = 0;
		fireDelay = 120;
		restCount = 0;
		dCount = 0;
		restDelay = 50;
		speedx = 0.8f;
		speedy = 0.4f;
		gravity = 1;
		onGround = false;
		active = true;
		shoot = false;
		dead = false;
		battle = false;
		jumpSpeed = -5.0f;
		jumpCounter = 0;
    	jumpIntervalFrames = 90;
    	
	}
	//Métodos
	static void cbowassets(){
		for (int i=0;i<14; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "BOWSER" << ".png";
            bowser[i] = al_load_bitmap(str.str().c_str());
        }
        Llama::cllassets();
        shooting = al_load_sample("Sounds/shooting.wav");
	}
	static void dbowassets(){
		for (int i=0;i<14; i++) {
            al_destroy_bitmap(bowser[i]);
        }
        al_destroy_sample(shooting);
	}
	void bowupdate(){
		if(dead){
			BowserDead();
			return;
		}
		if(active){
		if (!onGround) {
        y += speedy;
        speedy += 0.3f;
    	} else {
        	speedy = 0;
        jumpCounter++;
        if(jumpCounter >= jumpIntervalFrames){
            speedy = jumpSpeed;
            onGround = false;    
            jumpCounter = 0;     
        }
    	}
    	if (shoot) {
        Bowserflame();  
        return; 
    	}
    	fireCount++;
    	if (fireCount >= fireDelay) {
        fireCount = 0;
        shoot = true;
        restCount = 0;         
    	}
		frameCount++;
        if (frameCount >= frameDelay) {
            frameCount = 0;
            in++;
            ind++;
            if (in >= 3) in = 0;
            if(ind>=3) ind = 0;
        }
		x+=dir*speedx;
		if (x < xmax) {
            x = xmax;      
            dir = 1;
        }
        else if (x > inposx) {
            x = inposx;
            dir = -1;
        }	
		}	
	}
	void Bowserflame(){
	restCount++;
    if (restCount >= restDelay) {
    	lx = x-14;
    	ly = y+5;
    	in = 6; 
    	llamas.push_back(new Llama(lx,ly));
    	al_play_sample(shooting, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        shoot = false;
        return;
    }
	}
	void BowserDead(){
		dCount++;
		speedx = 0;
		y+=0.4;
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=14) in = 10;
		}
	}
	void bowdraw(){
		al_draw_bitmap(bowser[in],x,y,0);
		for (size_t i = 0; i < llamas.size(); i++) {
    		llamas[i]->lldraw();
		}
	}
};
ALLEGRO_BITMAP* Bowser::bowser[14] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
ALLEGRO_SAMPLE* Bowser::shooting = NULL;
