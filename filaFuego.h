//Clase fila de bolas de fuego
#include <sstream>
#include <math.h>
class filaFuego{
	public:
		float x,y;
		float fx,fy;
		int in;
		int frameCount;
		int frameDelay;
		float radius;
		float angle;
		float speed;
		static ALLEGRO_BITMAP* filaFire[4];
		static ALLEGRO_BITMAP* block;
	//Constructor
	filaFuego(float inx, float iny){
		x = inx;
		y = iny;
		fx = inx;
		fy = iny; 
		in = 0;
		frameCount = 0;
		frameDelay = 10;
		angle = 0;
		speed = 0.03;
		radius = 16;
	}
	//Métodos
	static void cffbassets(){
		for (int i=0;i<4; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "ffb" << ".png";
            filaFire[i] = al_load_bitmap(str.str().c_str());
        }
        block = al_load_bitmap("Sprites/4ci.png");
	}
	static void dffbassets(){
			for (int i=0;i<4; i++) {
				al_destroy_bitmap(filaFire[i]);
			}
			al_destroy_bitmap(block);
	}
	void ffbdraw(){

		al_draw_bitmap(block,x,y,0);
		    int w = al_get_bitmap_width(filaFire[in]);
    		int h = al_get_bitmap_height(filaFire[in]);
    		float cx = x + 8;
    		float cy = y + 8;
    	fx = cx + cos(angle) * radius;
    	fy = cy + sin(angle) * radius;
    	al_draw_rotated_bitmap(filaFire[in], w / 2, h / 2,fx, fy, angle,0);
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=4) in=0;
		}
		angle += speed;
    	if(angle >= 2 * ALLEGRO_PI)
        angle -= 2 * ALLEGRO_PI;
	}
};
ALLEGRO_BITMAP* filaFuego::filaFire[4] = {NULL, NULL, NULL, NULL};
ALLEGRO_BITMAP* filaFuego::block = NULL;
