//CLASE BOLA DE FUEGO, SOLO PARA INCLUIRLA EN CLASE PLAYER
#include<sstream>
class Fireball{
	public:
	float x, y;
	float speedx, speedy;
	int in;
	int dir;
	int frameCount;
	int frameDelay;
	bool hit;
	bool active;
	bool onGround;
	bool dead;
	static ALLEGRO_BITMAP* fireball[6];
	//Constructor
	Fireball(float inx, float iny,  int dire){
		x = inx;
		y = iny+16;
		dir = dire;
		speedx = 5.0f;
		speedy = 0.3f;
		in = 0;
		frameCount = 0;
		frameDelay = 10;
		hit = false;
		active = true;
		onGround = false;
		dead = false;
	}
	//Métodos
	static void cfbassets(){
		for(int i=0; i<6; i++){
			std::stringstream str;
            str << "Sprites/" <<i+1<<"fb"<<".png";
            fireball[i] = al_load_bitmap(str.str().c_str());
		}
	}
	static void dfbassets(){
		for(int i=0; i<4; i++){
			al_destroy_bitmap(fireball[i]);
		}
	}
	void animateHit(){
    if(!hit) return;
    frameCount++;
    if(frameCount >= frameDelay/5){
        frameCount = 0;
        in++;
        if(in >= 6){
            hit = false;
            active = false;
            dead = true;
        }
    }
	}
	void fbdraw(){
		if(!active) return;
		al_draw_bitmap(fireball[in],x,y,0);
		if(hit){
			animateHit();
			return;
		}
		if(!onGround){
            speedy += 0.25f;     
            if(speedy > 3.0f) speedy = 3.0f;
        }
        else {
            speedy = -3.0f;       
            onGround = false;
        }
        x += (dir == 0 ? speedx : -speedx);
        y += speedy;
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=4) in=0;
		}
	}	
};
ALLEGRO_BITMAP* Fireball::fireball[6] = {NULL,NULL,NULL,NULL,NULL,NULL};
