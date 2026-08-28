//Clase Spinie
#include <sstream>
class Spinie{
	public:
	float x,y;
	float vx,vy;
	float gravity;
	int in;
	int dir;
	int direc;
	int frameCount;
	int frameDelay;
	bool active;
	bool start;
	bool onGround;
	bool wasBefore;
	static ALLEGRO_BITMAP* spinie[6];
	//Constructor
	Spinie(float inx, float iny){
		x = inx;
		y = iny;
		dir = rand()%2;
		in = 4;
		frameCount = 0;
		frameDelay = 10;
		vy = 0;
		gravity = 0.4;
		vx = 0.8;
		active = true;
		onGround = false;
		wasBefore = false;
		start = false;
	}
	//Métodos
	static void cspassets(){
		for(int i=0;i<6;i++){
		std::stringstream str;
        str << "Sprites/" <<i + 1<<"spi"<<".png";
        spinie[i] = al_load_bitmap(str.str().c_str());
		}
	}
	static void dspassets(){
		for(int i=0;i<6;i++){
			al_destroy_bitmap(spinie[i]);
		}
	}
	void draw(){
		if(!active) return;
		if(!onGround && !wasBefore){
			vy += gravity;
        	y += vy;
        	frameCount++;
        	if(frameCount >= frameDelay){
            frameCount = 0;
            in++;
            if(in < 4 || in > 5) in = 4;
        	}
		}else if(!onGround){
			vy += gravity;
        	y += vy;
		}else if(onGround){
			if(dir == 0 && !start){
				direc = -1;
			}else if(dir == 1 && !start){
				direc = 1;
			}
			start = true;
			if(direc == -1){
				x -= vx;
			}else if(direc == 1){
				x += vx;	
			}
			frameCount++;
        	if(frameCount >= frameDelay){
            frameCount = 0;
            if(direc == -1){
                in++;
                if(in>=2){
                	in = 0;
				}
            }
            else if(direc == 1){
                in++;
                if(in>=4){
                	in = 2;
				}
            }         
			}	
		}
		al_draw_bitmap(spinie[in], x, y, 0);
	}
};
ALLEGRO_BITMAP* Spinie::spinie[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
