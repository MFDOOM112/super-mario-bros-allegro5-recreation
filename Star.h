//CLASE ESTRELLA!!!
#include <sstream>
class Star{
	public:
		float sx, sy;
		float gravitys;
		float sspeed;
		float yemerg;
		float sjumpspeed;
		bool songround;
		bool sactive;
		bool canBeEaten;
		bool emerging;
		int in;
		int frameDelay;
		int frameCount;
		ALLEGRO_BITMAP *star[4];
		//Constructor
		Star(float isx, float isy){
			sx = isx;
			sy = isy;
			gravitys = 0.35f;
			songround = false;
			sactive = false;
			in = 0;
			frameDelay = 10;
			frameCount = 0;
			sspeed = 1.0f;
			sjumpspeed = -5.0;
			canBeEaten = false;
    		emerging = false;
    		yemerg = isy-16;
		}
		//Métodos
		void csassets(){
			for(int i=0;i<4;i++){
			std::stringstream str;
            str << "Sprites/" <<i + 1<<"s"<<".png";
            star[i] = al_load_bitmap(str.str().c_str());
			}
		}
		void dessassets(){
			for(int i=0;i<4;i++){
			al_destroy_bitmap(star[i]);
			}
		}
		void supdate(){
	 if (emerging) {
        sy -= 1.2;
        if (sy <= yemerg) {
            emerging = false;
            sactive = true;
            canBeEaten = true;
        }
        return;
    }
        sx += sspeed;

        // Gravedad vertical
        sjumpspeed += gravitys;
        if (sjumpspeed > 5.0f) sjumpspeed = 5.0f; // limite de caída

        sy += sjumpspeed;
    }
		void sdraw(){
			if(sactive || emerging){
				al_draw_bitmap(star[in],sx,sy,0);
				frameCount++;
				if(frameCount>=frameDelay){
					frameCount = 0;
					in++;
					if(in>=3){
						in = 0;
					}
				}
			}
		}
		void changeDirection() {
        sspeed *= -1;
    	}
    	void landOn(float groundY) {
    		sy = groundY-16;
            sjumpspeed = -4.5f;
            songround = true;
    }
};
