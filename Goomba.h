//Clase Goomba
class Goomba{
	public:
    float gx, gy;          
    float gspeed;          
    float gravity; 
    bool gonground;        
    bool gactive;          
    bool squashed;        
    int in;               
    int frameDelay;       
    int frameCount;       
    bool starKilled;    
	float dy;            
	float rotation;     
	float starTimer;    
	int dir;
	static ALLEGRO_BITMAP *goomba[3];
    // Constructor
    Goomba(float igx, float igy) {
    	gravity = 1.0;
        gx = igx;
        gy = igy;
        gspeed = 0.8;
        dir = 1;
        gonground = false;
        gactive = false;
        squashed = false;
        in = 0;
        frameDelay = 10;
        frameCount = 0;
        starKilled = false;
        dy = 0;
    	rotation = 0;
    	starTimer = 0;
    }
	//Métodos
    static void cgassets() {
        for(int i = 0; i < 3; i++) {
            std::stringstream str;
            str << "Sprites/gc" << i + 1 << ".png";
            goomba[i] = al_load_bitmap(str.str().c_str());
        }
    }
    static void ucgassets(){
    	for(int i = 0; i < 3; i++) {
            std::stringstream str;
            str << "Sprites/ugc" << i + 1 << ".png";
            goomba[i] = al_load_bitmap(str.str().c_str());
        }
	}
	static void ccgassets(){
		for(int i = 0; i < 3; i++) {
            std::stringstream str;
            str << "Sprites/gcc" << i + 1 << ".png";
            goomba[i] = al_load_bitmap(str.str().c_str());
        }
	}
    static void desgassets() {
        for(int i = 0; i < 3; i++) {
            al_destroy_bitmap(goomba[i]);
        }
    }
    void gupdate() {
        if(!gactive) return;
        if (starKilled) {
        gy += dy;
        gx += gspeed;
        dy += 0.6;
        starTimer--;
        if (starTimer <= 0 || gy > 640) {
            gactive = false;
        }
        return;
    	}
        if(squashed) {
            frameCount++;
            if(frameCount >= frameDelay) {
                gactive = false;
            }
            return;
        }
        if(!gonground) {
          gy += gravity;
        	if (gravity < 4.0) gravity *= 1.05; 
        	gx += 0.3f * dir*-1;                    
        }
        if(gonground) {
        	gravity = 1;
        	if(dir==1){
        		gx -= gspeed;
			}else if(dir==0){
				gx += gspeed;
			}
            frameCount++;
            if(frameCount >= frameDelay) {
                frameCount = 0;
                in++;
                if(in >= 2) in = 0;
            }
        }
    }
    void stomp() {
        if(!squashed) {
            squashed = true;
            in = 2;        
            frameCount = 0;
            gy += 8;       
        }
    }
    void starHit() {
    if (starKilled || !gactive) return;
    starKilled = true;
    dy = -4;             
    rotation = ALLEGRO_PI;
    starTimer = 120;
	}
    void gdraw() {
    	if(starKilled){
    		al_draw_rotated_bitmap(goomba[in], 8, 8, gx + 8, gy + 8, rotation, 0);
		}else if(gactive) {
            al_draw_bitmap(goomba[in], gx, gy, 0);
        }
    }
};
ALLEGRO_BITMAP* Goomba::goomba[3] = {NULL, NULL, NULL};
