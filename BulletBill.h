//CLASE BULLET BILL!!
#include <sstream>
class BulletBill{
	public:
	float x,y;
	int in;
	int dir;
	int frameCount;
	int frameDelay;
	float dy;            
	float rotation;      
	float starTimer;     
	bool active;
	bool newOne;
	bool anim;
	bool starKilled;     
	static ALLEGRO_BITMAP* bulletbill[6];
	static ALLEGRO_SAMPLE* bullet;
	//Constructor
	BulletBill(float inx, float iny, int idir){
		x = inx;
		y = iny;
		dir = idir;
		if(dir == -1){
			in = 0;
		}else if(dir == 1){
			in = 3;
		}
		frameCount = 0;
		frameDelay = 10;
		dy = 0;
    	rotation = 0;
    	starTimer = 0;
		active = false;
		newOne = true;
		starKilled = false;
	}
	//Métodos
	static void cbbiassets(){
		for(int i=0;i<6;i++){
			std::stringstream str;
            str << "Sprites/" <<i + 1<<"bbl"<<".png";
            bulletbill[i] = al_load_bitmap(str.str().c_str());
		}
		bullet = al_load_sample("Sounds/bullet.wav");
	}
	static void dbbiassets(){
		for(int i=0;i<6;i++){
			al_destroy_bitmap(bulletbill[i]);
		}
		al_destroy_sample(bullet);
	}
	void starHit() {
    if (starKilled || !active) return;
    starKilled = true;
    dy = -4;             
    rotation = ALLEGRO_PI;
    starTimer = 120;
	}
	void draw(){
		if(!active) return;
		if (starKilled) {
		al_draw_rotated_bitmap(bulletbill[in], 8, 8, x + 8, y + 8, rotation, 0);
        y += dy;
        x += 0.9;
        dy += 0.6;
        starTimer--;
        if (starTimer <= 0 || y > 640) {
            active = false;
        }
        return;
    	}
		al_draw_bitmap(bulletbill[in], x, y, 0);
		if(newOne){
			al_play_sample(bullet, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			newOne = false;
		}
		x+=dir*1.7;
		if(dir==1){
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=6) in = 3;
		}
		}else if(dir == -1){
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=3) in = 0;
		}
		}
	}
};
ALLEGRO_BITMAP* BulletBill::bulletbill[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
ALLEGRO_SAMPLE* BulletBill::bullet = NULL;
