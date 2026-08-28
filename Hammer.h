//Clase Hammer!
#include <sstream>
class Hammer{
	public:
		float x,y;
		float vx,vy;
		float gravity;
		int in;
		int frameCount;
		int frameDelay;
		static ALLEGRO_BITMAP* hammer[2];
	//Constructor
	Hammer(float inx, float iny){
		x = inx;
		y = iny;
		vy = -7.0;
		vx = 1.2;
		gravity = 0.3;
		in = 0;
		frameCount = 0;
		frameDelay = 10;
	}
	//Métodos
	static void chmassets(){
		for(int i=0;i<2;i++){
			std::stringstream str;
            str << "Sprites/" <<i + 1<<"hammer"<<".png";
            hammer[i] = al_load_bitmap(str.str().c_str());
		}
	}
	static void dhmassets(){
		for(int i=0;i<2;i++){
  			al_destroy_bitmap(hammer[i]);
		}
	}
	void draw(){
		al_draw_bitmap(hammer[in],x,y,0);
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=2){
				in = 0;
			}
		}
		x-=vx;
		y+=vy;
		vy+=gravity;
	}
};
ALLEGRO_BITMAP* Hammer::hammer[2] = {NULL, NULL};
