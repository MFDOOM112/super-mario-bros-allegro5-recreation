//Clase Bill-Blaster!!!
#include "BulletBill.h"
#include <vector>
class BillBlaster{
	public:
	float x,y;
	int bulletTimer;
	bool active;
	std::vector<BulletBill*> bulletbills;
	static ALLEGRO_BITMAP* billblaster;
	//Constructor
	BillBlaster(float inx, float iny){
		x = inx;
		y = iny;
		active = false;
		bulletTimer = 0;
	}
	//Métodos
	static void cbblassets(){
		billblaster = al_load_bitmap("Sprites/billblaster.png");
		BulletBill::cbbiassets();
	}
	static void dbblassets(){
		al_destroy_bitmap(billblaster);
		BulletBill::dbbiassets();
	}
	void update(Player* p){
		if(!active) return;
		bulletTimer++;
		float dx = p->x - x;
    	float dy = p->y - y;
    	if(p->y + 16 < y){
        return;
    	}
		if(bulletTimer < 200) return;
    	bulletTimer = 0;
    	int dir = 0;
    	if(dx < -8)      dir = -1;
    	else if(dx > 8)  dir = 1;   
    	else             return;     
    	BulletBill* b = new BulletBill(x + dir*16, y, dir);
    	b->active = true;
    	bulletbills.push_back(b);
	}
	void draw(){
		for(size_t i=0; i<bulletbills.size(); i++){
			BulletBill* bbl = bulletbills[i];
			bbl->draw();
		}
		if(!active) return;
		al_draw_bitmap(billblaster,x,y,0);
	}
};
ALLEGRO_BITMAP* BillBlaster::billblaster = NULL;
