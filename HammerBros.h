//Clase Hammer Bros!
#include <sstream>
#include <vector>
#include "Hammer.h"
class HammerBros{
	public:
	float x,y;
	float inposx;
	float vx, vy;
    float gravity;
    float xMin, xMax;
	int in;
	int frameCount;
	int frameDelay;
	int jumpTimer;
    int throwTimer;
    int throwCount;
    int throwDelay;
	float dy;            // velocidad vertical (para el salto de muerte)
	float rotation;      // dibujarlo de cabeza
	float starTimer;     // tiempo hasta desaparecer después del golpe
	bool onGround;
	bool starKilled;     //True si es golpeado por estrella
	bool throwingnow;
	bool active;
	static ALLEGRO_BITMAP* hammerbros[12];
	static ALLEGRO_SAMPLE* throwing;
	std::vector<Hammer*> hammers;
	//Constructor
	HammerBros(float inx, float iny){
		x = inx;
		inposx = inx;
		y = iny;
		vx = 1.0;
        vy = 0;
        gravity = 0.3;
        xMin = inx - 40;
        xMax = inx + 40;
		in = 0;
		dy = 0;
    	rotation = 0;
    	starTimer = 0;
		frameCount = 0;
		frameDelay = 10;
		throwCount = 0;
		throwDelay = 10;
		jumpTimer = 60 + rand()%60; 
        throwTimer = 90 + rand()%60;  
		active = false;
		onGround = false;
		throwingnow = false;
		starKilled = false;
	}
	//Métodos
	static void chbassets(){
		for(int i=0;i<12;i++){
		std::stringstream str;
        str << "Sprites/" <<i + 1<<"hb"<<".png";
        hammerbros[i] = al_load_bitmap(str.str().c_str());
		}
		throwing = al_load_sample("Sounds/throwing.wav");
		Hammer::chmassets();
	}
	static void descassets(){
		for(int i=0;i<12;i++){
		al_destroy_bitmap(hammerbros[i]);
		}
		Hammer::dhmassets();
	}
	void update(){
		if(!active){
			return;
		}
		if (starKilled) {
        y += dy;
        x += vx;
        dy += 0.6;
        starTimer--;
        if (starTimer <= 0 || y > 640) {
            active = false;
        }
        return;
    	}
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=3){
				in = 0;
			}
		}
		x += vx;
        if(x <= xMin){
            x = xMin;
            vx = 1.0;
        }
        if(x >= xMax){
            x = xMax;
            vx = -1.0;
        }
        jumpTimer--;
        if(jumpTimer <= 0 && onGround){
            onGround = false;
            if(rand()%2 == 0){
            	vy = -5;
			} 
            else{
            	vy = -8; 	
			}                 
            jumpTimer = 60 + rand()%80;
        }
     	if(!onGround){
    		vy += gravity;   
    		y += vy;
		} else {
    		vy = 0; 
		}
        throwTimer--;
        if(throwTimer <= 0){
            hammerthrow();
			throwTimer = 90 + rand()%60;
            return;
        }
        if(throwingnow){
        	throwCount++;
        	if(throwCount>=throwDelay){
        		throwCount = 0;
        		throwingnow = false;
			}else{
			if(onGround){
            	in = 8;
			}else{
				in = 10;
			}
			}
		}
	}
	void hammerthrow(){
		al_play_sample(throwing, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
		hammers.push_back(new Hammer(x,y-24));
		throwingnow = true;
	}
	void starHit() {
    if (starKilled || !active) return;
    starKilled = true;
    dy = -4;             
    rotation = ALLEGRO_PI;
    starTimer = 120;
	}
	void hbdraw(){
		if(starKilled){
    		al_draw_rotated_bitmap(hammerbros[in], 8, 8, x + 8, y + 8, rotation, 0);
		}else if(active){
		al_draw_bitmap(hammerbros[in],x,y,0);
		for(size_t i=0; i<hammers.size(); i++){
			hammers[i]->draw();
		}
		}
	}
};
ALLEGRO_BITMAP* HammerBros::hammerbros[12] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
ALLEGRO_SAMPLE* HammerBros::throwing = NULL;
