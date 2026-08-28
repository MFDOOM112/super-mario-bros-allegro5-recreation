//CLASE PLANTA PIRAÑA
#include <sstream>
class PPlant{
	public:
		float x;
		float y;
		int in;
		static ALLEGRO_BITMAP* pplant[2];
		bool active;
		bool alive;
		bool playerOn;
		int frameCount;
		int frameDelay;
		float topY;
		float pspeed;
		float inposy;
		int direction;
		int pauseTimer;
	//Constructor
	PPlant(float inx, float iny){
		x = inx;
		y = iny;
		inposy = iny;
		in = 0;
		pspeed = 0.3f;
		active = false;
		frameCount = 0;
		frameDelay = 10;
		direction = -1;
		topY = inposy - 32;
		pauseTimer = 0;
		alive = true; 
		playerOn = false;
	}
	//Nétodos
	static void cppassets(){
		for(int i=0; i<2; i++){
			std::stringstream str;
            str << "Sprites/" << i + 1 << "pp" << ".png";
            pplant[i] = al_load_bitmap(str.str().c_str());
		}
	}
	static void dppassets(){
		for(int i=0; i<2; i++){
			al_destroy_bitmap(pplant[i]);
		}
	}
	void pupdate(Player *p){
		if(p->y + 16 < y && y >= inposy){
        playerOn = true;
    	}else{
    		playerOn = false;
		}
	}
	void ppdraw(){
        if (!active || !alive) return;
        if(playerOn){
        	return;
		}
        	al_draw_bitmap(pplant[in], x, y, 0);
            frameCount++;
            if (frameCount >= frameDelay) {
                frameCount = 0;
                in++;
                if (in >= 2) in = 0;
            }
			if (pauseTimer > 0) {
            pauseTimer--;
        	} else {
            y += pspeed * direction;
            if (y <= topY) {
                y = topY;      
                direction = 1;
                pauseTimer = 60;
            }
            else if (y >= inposy) {
                y = inposy;
                direction = -1;
                pauseTimer = 90;
            }
        }
	}
};
ALLEGRO_BITMAP* PPlant::pplant[2] = {NULL, NULL};
