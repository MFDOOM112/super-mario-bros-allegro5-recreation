//Clase PuenteBowser
#include <sstream>
class Bbridge{
	public:
		float x,y;
		int in;
		bool destroyed;
		bool active;
		int frameCount;
		int frameDelay;
		static ALLEGRO_BITMAP* bbridge[8];
		static ALLEGRO_SAMPLE* destroying;
	//Constructor
	Bbridge(float inx, float iny){
		x = inx;
		y = iny;
		in = 0;
		destroyed = false;
		active = true;
		frameCount = 0;
		frameDelay = 20;
	}
	//Métodos
	static void cbbassets(){
		for (int i=0;i<8; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "bb" << ".png";
            bbridge[i] = al_load_bitmap(str.str().c_str());
        }
        destroying = al_load_sample("Sounds/Destroyed.wav");
	}
	static void dbbassets(){
		for (int i=0;i<8; i++){
            al_destroy_bitmap(bbridge[i]);
        }
	}
	void bbdraw(){
		if(!destroyed && active){
			al_draw_bitmap(bbridge[0],x,y,0);
		}else if(destroyed && active){
			al_play_sample(destroying, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
			al_draw_bitmap(bbridge[in],x,y,0);
			frameCount++;
			if(frameCount>=frameDelay){
				in++;
				if(in>=8){
					active = false;
				}
			}
		}
	}
};
ALLEGRO_BITMAP* Bbridge::bbridge[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
ALLEGRO_SAMPLE* Bbridge::destroying = NULL;
