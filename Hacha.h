//CLASE HACHA
#include <sstream>
class Hacha{
	public:
		float x,y;
		int in;
		int frameCount;
		int frameDelay;
		static ALLEGRO_BITMAP* hacha[3];
	//Constructor
	Hacha(float inx, float iny){
		x = inx;
		y = iny;
		in = 0;
		frameCount = 0;
		frameDelay = 10;
	}
	//Métodos
	static void chhassets(){
		for (int i=0;i<3; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "hh" << ".png";
            hacha[i] = al_load_bitmap(str.str().c_str());
        }
	}
	static void dhhassets(){
		for (int i = 0; i < 3; i++) {
        al_destroy_bitmap(hacha[i]);
        }
	}
	void hhdraw(){
		al_draw_bitmap(hacha[in],x,y,0);
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=3){
				in = 0;
			}
		}
	}
};
ALLEGRO_BITMAP* Hacha::hacha[3] = {NULL,NULL,NULL};
