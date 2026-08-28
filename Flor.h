//CLASE FLOR DE FUEGO
#include<sstream>
class Flor{
	public:
		float fx, fy;
		float yemerg;
		bool factive;
		int in;
		int frameDelay;
    	int frameCount;
    	bool canBeEaten;
		bool emerging;
		ALLEGRO_BITMAP *flor[4];
		ALLEGRO_SAMPLE *fb;
		//Constructor
		Flor(float fix, float fiy){
			fx = fix;
			fy = fiy;
			factive = false;
			in = 0;
			frameDelay = 10;
			frameCount = 0;
			canBeEaten = false;
    		emerging = false;
    		yemerg = fiy-16;
			fb = al_load_sample("Sounds/Fireball.wav");
		}
		//Métodos
		void cfassets(){
			for(int i=0;i<4;i++){
			std::stringstream str;
            str << "Sprites/" <<i + 1<<"f"<<".png";
            flor[i] = al_load_bitmap(str.str().c_str());
			}
		}
		void desfassets(){
			for(int i=0;i<4;i++){
			al_destroy_bitmap(flor[i]);
			}
		}
		void fupdate(){
			if (emerging) {
            fy -= 1.5;
            if (fy <= yemerg) {
                emerging = false;
                factive = true;   
                canBeEaten = true;
            }
            return;
        	}
        	if(factive){
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
		void fdraw(){
			if(factive || emerging){
			al_draw_bitmap(flor[in],fx,fy,0);
			}
		}
		
};
