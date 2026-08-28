//Clase Cheep-Cheep
#include <sstream>
class Cheep{
	public:
		float x,y;
		float topY;
		float dy;
		float inposy;
		float bigJump;
		float vy;       
		float vx;       
		float gravity;
		float rotation;  
		int type;
		int in;
		int direction;
		int stompedT;
		int frameCount;
		int frameDelay;
		bool active;
		bool jumping;
		bool stomped;   
		static ALLEGRO_BITMAP* redcheep[4];
		static ALLEGRO_BITMAP* greencheep[4];
	//Constructor
	Cheep(float inx, float iny, int types){
		x = inx;
		y = iny;
		inposy = iny;
		topY = iny - 24; 
		bigJump = iny + 200;
		in = 0;
		frameCount = 0;
		frameDelay = 10;
		type = types;
		active = false;
		vy = 0;
		vx = 1.0;     
		gravity = 0.12;
		jumping = false;
		stomped = false;
	}
	//Métodos
	static void ccheassets(){
		for (int i=0;i<4; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "chr" << ".png";
            redcheep[i] = al_load_bitmap(str.str().c_str());
        }
        for (int i=0;i<4; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "chv" << ".png";
            greencheep[i] = al_load_bitmap(str.str().c_str());
        }
	}
	static void dcheassets(){
			for (int i=0;i<4; i++) {
				al_destroy_bitmap(redcheep[i]);
			}
				for (int i=0;i<4; i++) {
				al_destroy_bitmap(greencheep[i]);
			}
	}
	void chdraw(){
		if(!active){
			return;
		}
		if (stomped) {
    	dy += gravity;     
    	y += dy;
    	x += 0.3;
    	stompedT--;
    	if (stompedT <= 0 || y > 640) {
        active = false;
    	}
    	al_draw_rotated_bitmap(redcheep[in], 8, 8, x + 8, y + 8, rotation, 0);
    	return;
		}
		if(type == 1){
			al_draw_bitmap(greencheep[in],x,y,0);
			frameCount++;
			x-=0.6;
			if(frameCount>=frameDelay){
				frameCount = 0;
				in++;
				if(in>=2){
					in=0;
				}
			}
		}
		if(type == 2){
			al_draw_bitmap(redcheep[in],x,y,0);
			frameCount++;
			x-=0.6;
			y+=direction*0.3;
			if (y <= topY) {
                y = topY;      
                direction = 1;
            }
            else if (y >= inposy) {
                y = inposy;
                direction = -1;
            }
			if(frameCount>=frameDelay){
				frameCount = 0;
				in++;
				if(in>=2){
					in=0;
				}
			}
		}
		if (type == 3) {
    	al_draw_bitmap(redcheep[in], x, y, 0);
    	frameCount++;
    	if (frameCount >= frameDelay) {
        frameCount = 0;
        in++;
        if (in >= 4) in = 2;
    	}
    	x += vx;
    	if (jumping) {
        vy += gravity;
        y += vy;
        if (y >= 240) {
            y = 240;
            jumping = false;
        }
    }
    else {
        if (rand() % 50 == 0) {
            jumping = true;
            vy = -(4.0 + rand() % 6);
            vx = (0.5 + rand() % 2);
            topY = inposy - (150 + rand() % 50);
        }
    }
}

	}
	void stomp() {
    if (!active) return;
    stomped = true;
    dy = -3;             
    rotation = ALLEGRO_PI;
    stompedT = 120;
	}
};
ALLEGRO_BITMAP* Cheep::redcheep[4] = {NULL, NULL, NULL, NULL};
ALLEGRO_BITMAP* Cheep::greencheep[4] = {NULL, NULL, NULL, NULL};
