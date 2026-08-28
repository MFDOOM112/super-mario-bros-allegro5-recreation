//Clase Blooper
class Blooper {
public:
    float x, y;
    float topY;
    float speedx, speedy;
    bool active;
    bool squish;
    float dy;           
	float rotation;     
	float starTimer;
    int squishCount;
    int squishTimer;
    int jumpCount;      
    int jumpDirection;   
    int jumpTimer;
    int bLimit;
    bool starKilled;
    static ALLEGRO_BITMAP* blooper[2];
    Blooper(float inx, float iny) {
        x = inx;
        y = iny;
        topY = iny;
        active = true;
        speedx = 0.5;
        speedy = 0;
        squish = false;
        squishCount = 0;
        squishTimer = 80;
        jumpCount = 0;
        jumpDirection = 1;
        jumpTimer = 0;
        bLimit = 16;
        dy = 0;
    	rotation = 0;
    	starTimer = 0;
    	starKilled = false;
    }

    static void cbloassets() {
        for (int i = 0; i < 2; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "blo" << ".png";
            blooper[i] = al_load_bitmap(str.str().c_str());
        }
    }

    static void dbloassets() {
        for (int i = 0; i < 2; i++) {
            al_destroy_bitmap(blooper[i]);
        }
    }
    void startJump() {
        speedy = -0.4;
        speedx = 0.5 * jumpDirection;
        squish = true;
        bLimit = 16;
        squishCount = 0;
    }
	void starHit() {
    if (starKilled || !active) return;
    starKilled = true;
    dy = -4;             
    rotation = ALLEGRO_PI;
    starTimer = 120;
	}
  void update() {
    if (!active) return;
    if (starKilled) {
        y += dy;
        x += speedx;
        dy += 0.6;
        starTimer--;
        if (starTimer <= 0 || y > 640) {
            active = false;
        }
        return;
    }
    jumpTimer++;
    if (jumpTimer == 1) {
        startJump();
    }
    if (squish) {
        squishCount++;
        x += speedx;
        y += speedy;
        if (squishCount >= squishTimer) {
            squish = false;
            bLimit = 23;
            speedy = 1.0;
        }
    } else {
        y += speedy;
        if (y >= topY) { 
            y = topY;
            jumpCount++;
            if (jumpCount >= 3) {
                jumpDirection = (rand() % 2) ? 1 : -1;
                jumpCount = 0;
            }
            jumpTimer = 0; 
        }
    }
}

    void bloodraw() {
    	if(starKilled){
    		int frame = squish ? 1 : 0;
    		al_draw_rotated_bitmap(blooper[frame], 8, 8, x + 8, y + 8, rotation, 0);
		}else{
			int frame = squish ? 1 : 0;
        	al_draw_bitmap(blooper[frame], x, y, 0);
		}
    }
};

ALLEGRO_BITMAP* Blooper::blooper[2] = { NULL, NULL };
