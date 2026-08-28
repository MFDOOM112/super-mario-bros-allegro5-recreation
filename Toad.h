//Clase Toad en bolsa
#include <sstream>
class Toad{
	public:
	float x,y;
	static ALLEGRO_BITMAP* toad[8];
	int frameCount;
	int frameDelay;
	int in;
	bool active;
	bool anim;
	//Constructor
	Toad(float inx, float iny){
		x = inx;
		y = iny;
		in = 0;
		frameCount = 0;
		frameDelay = 30;
		active = true;
		anim = false;
	}
	//Métodos
	static void ctoassets(){
		for(int i=0;i<8;i++){
			std::stringstream str;
            str << "Sprites/" <<i + 1<<"t"<<".png";
            toad[i] = al_load_bitmap(str.str().c_str());
		}
	}
	static void dtoassets(){
		for(int i=0;i<8;i++){
			al_destroy_bitmap(toad[i]);
		}
	}
	void draw(){
		al_draw_bitmap(toad[in],x,y,0);
		if(!anim) return;
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=8){
				in = 7;
			}
		}
	}
};
ALLEGRO_BITMAP* Toad::toad[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
