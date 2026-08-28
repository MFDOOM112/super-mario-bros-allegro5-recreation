//Clase LAKITU!!!
#include <sstream>
#include <vector>
#include "Spinie.h"
class Lakitu{
	public:
	float x,y;
	float vx;
	int in;
	int ina;
	int throwCount;
	int throwDelay;
	int throwTimer;
	bool newOne;
	bool active;
	float dy;            
	float rotation;      
	float starTimer;     
	bool onGround;
	bool starKilled;
	bool moving;     
	static ALLEGRO_BITMAP* lakitu[3];
	std::vector<Spinie*> spinies;
	//Constructor
	Lakitu(float inx, float iny){
		x = inx;
		y = iny;
		vx = 1.9;
		in = 0;
		throwCount = 0;
		throwDelay = 20;
		throwTimer = 90;
		dy = 0;
    	rotation = 0;
    	starTimer = 0;
    	starKilled = false;
		newOne = false;
		active = false;
		moving = true;
	}
	//Métodos
	static void clakassets(){
		for(int i=0;i<3;i++){
		std::stringstream str;
        str << "Sprites/" <<i + 1<<"lakitu"<<".png";
        lakitu[i] = al_load_bitmap(str.str().c_str());
		}
		Spinie::cspassets();
	}
	static void dlakassets(){
		for(int i=0;i<3;i++){
			al_destroy_bitmap(lakitu[i]);
		}
		Spinie::dspassets();
	}
	void update(Player* p){
		if(!active) return;
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
		throwTimer--;
		if(throwTimer<=0){
			throwingNow();
			throwCount++;
			in = 2;
			if(throwCount>=throwDelay){
				throwCount = 0;
				throwTimer = 90;
				newOne = false;
			}
			return;
		}
    float dx = p->x - x;
    const float SLOW_SPEED = 2.4;
    if(p->velx == 0 && fabs(dx) > 5){ 
        moving = true;
        if(dx > 0){
            x += SLOW_SPEED;
            in = 1;
        } else {
            x -= SLOW_SPEED;
            in = 0;
        }
        ina = in;
    }
    else if(p->velx != 0){
        moving = true;
        if(dx > 0){
            x += vx;
            in = 1;
        } else if(dx < 0){
            x -= vx;
            in = 0;
        }
        ina = in;
    }
    else {
        moving = false;
        in = ina; // mantener animación de dirección
    }
	}
	void draw(){
		if(!active) return;
		if(starKilled){
    		al_draw_rotated_bitmap(lakitu[in], 8, 8, x + 8, y + 8, rotation, 0);
		}else if(in == 0 || in == 1){
			al_draw_bitmap(lakitu[in], x, y, 0);
		}else if(in == 2){
			al_draw_bitmap(lakitu[in], x, y+8, 0);
		}
    	for(size_t i=0; i<spinies.size(); i++){
    		Spinie* sp = spinies[i];
    		sp->draw();
		}
	}
	void throwingNow(){
		if(!newOne){
			spinies.push_back(new Spinie(x,y));
			newOne = true;
		}
	}
	void starHit() {
    if (starKilled || !active) return;
    starKilled = true;
    dy = -4;             
    rotation = ALLEGRO_PI;
    starTimer = 120;
	}
};
ALLEGRO_BITMAP* Lakitu::lakitu[3] = {NULL, NULL, NULL};
