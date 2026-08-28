//Clase Bandera de meta
#include<sstream>
class Flag{
	public:
		float x,y;
		float flx, fly;
		int fl;
		float fspeed;
		int frameCount;
		int frameDelay;
		bool clear;
		static ALLEGRO_BITMAP *flag;
		static ALLEGRO_BITMAP *mflag[3];
	//Constructor
	Flag(float inx, float iny){
		x = inx;
		y = iny;
		fl = 0;
		flx = inx+15;
		fly = iny+8;
		fspeed = 4;
		frameCount = 0;
		frameDelay = 10;
		clear = false;
	}
	//Métodos
	static void cflassets(){
		flag = al_load_bitmap("Sprites/flag.png");
		for (int i=0;i<3; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "fl" << ".png";
            mflag[i] = al_load_bitmap(str.str().c_str());
        }
	}
	static void dflassets(){
		al_destroy_bitmap(flag);
		for (int i=0; i<3; i++){
			al_destroy_bitmap(mflag[i]);
		}
	}
	void fldraw(){
		al_draw_bitmap(flag, x, y, 0);
		al_draw_bitmap(mflag[fl],flx,fly,0);
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			fl++;
		if(fl>=3){
			fl = 0;
		}
		if(clear){
			fly+=fspeed;
			fspeed*2;
		}
		if(fly >= y+136){
			clear = false;
			fly = y+136;
		}
		}

	}
};
ALLEGRO_BITMAP* Flag::flag = NULL;
ALLEGRO_BITMAP* Flag::mflag[3] = {NULL, NULL, NULL}; 
