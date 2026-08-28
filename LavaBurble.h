//Clase burbuja de lava
class LavaBurble{
	public:
	float x,y;
	float vy;
	float ymax;
	float ymin;
	int in;
	int direction;
	int frameCount;
	int frameDelay;
	int pauseTimer;
	bool active;
	bool goingDown;
	static ALLEGRO_BITMAP* lavaburble[6];
	static ALLEGRO_SAMPLE* emerging;
	//Constructor
	LavaBurble(float inx, float iny){
		x = inx;
		y = iny;
		vy = 2.3;
		direction = 1;
		ymax = iny-30;
		ymin = iny+100;
		in = 0;
		frameCount = 0;
		frameDelay = 10;
		pauseTimer = 0;
		active = false;
		goingDown = false;
	}
	//Métodos
	static void clbassets(){
		for(int i=0;i<6;i++){
			std::stringstream str;
            str << "Sprites/" <<i + 1<<"lb"<<".png";
            lavaburble[i] = al_load_bitmap(str.str().c_str());
		}
		emerging = al_load_sample("Sounds/emerging.wav");
	}
	static void dlbassets(){
		for(int i=0;i<6;i++){
			al_destroy_bitmap(lavaburble[i]);
		}
	}
	void draw(){
		if(!active) return;
		al_draw_bitmap(lavaburble[in],x,y,0);
		if (pauseTimer > 0) {
            pauseTimer--;
        } else {
        y+=direction*vy;
		if (y <= ymax) {
            y = ymax;      
            direction = 1;
            vy = 2.7;
            pauseTimer = 20;
        }else if (y >= ymin) {
        	al_play_sample(emerging, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                y = ymin;
                direction = -1;
                vy += 2;
            pauseTimer = 10+rand()%30;
        }
    	}
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			if(direction==1){
				in++;
				if(in>=6){
					in = 3;
				}
			}else if(direction==-1){
				in++;
				if(in>=3){
					in = 0;
				}
			}
		}
	}	
};
ALLEGRO_BITMAP* LavaBurble::lavaburble[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
ALLEGRO_SAMPLE* LavaBurble::emerging = NULL;
