//Clase LAVA!!!
#include <sstream>
class Lava{
	public:
		float x,y;
		enum Type{LAVA_UP = 0, LAVA_DOWN};
		Type type;
		int in;
		static ALLEGRO_BITMAP* lavau[8];
		static ALLEGRO_BITMAP* lavad;
		int frameCount;
		int frameDelay;
	//Constructor
	Lava(float inx, float iny, Type types){
		x = inx;
		y = iny;
		type = types;
		in = 0;
		frameCount = 0;
		frameDelay = 10;
	}
	static void claassets(){
		for (int i=0;i<8; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "la" << ".png";
            lavau[i] = al_load_bitmap(str.str().c_str());
        }
        lavad = al_load_bitmap("Sprites/lad.png");
	}
	static void cslaassets(){
		for (int i=0;i<8; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "lake" << ".png";
            lavau[i] = al_load_bitmap(str.str().c_str());
        }
        lavad = al_load_bitmap("Sprites/laked.png");
	}
	static void dclaassets(){
		for(int i=0; i<8; i++){
			al_destroy_bitmap(lavau[i]);
		}
		al_destroy_bitmap(lavad);
	}
	void ladraw(){
		if(type==LAVA_UP){
			al_draw_bitmap(lavau[in],x,y,0);
			frameCount++;
			if(frameCount>=frameDelay){
				frameCount = 0;
				in++;
				if(in>=8){
					in = 0;
				}
			}
		}else if(type == LAVA_DOWN){
			al_draw_bitmap(lavad,x,y,0);
		}
	}
};
ALLEGRO_BITMAP* Lava::lavau[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
ALLEGRO_BITMAP* Lava::lavad = NULL;
