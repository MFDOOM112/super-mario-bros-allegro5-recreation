//CLASE KOOPA!!!
class Koopa{
	public:
		float kx,ky;
		float kspeed;
		float gravity;
		float inposy;
		float topY;
		float vdir;
		int flyTimer;
		int flyDuration;
		bool konground;
		bool kactive;
		bool stomped;
		bool hasWings;
		int in;
		int kdir;
		bool inShell;
    	bool shellMoving;
    	float shellTimer;
		int frameDelay;        
    	int frameCount;       
    	bool starKilled;     
		float dy;            
		float rotation;     
		float starTimer;
		float klimit;
		int safeTimer;
		int type;	     
    	static ALLEGRO_BITMAP *koopa[9];
    	static ALLEGRO_BITMAP *redkoopa[9];
    	static ALLEGRO_BITMAP *redflykoopa[9];
    	static ALLEGRO_BITMAP *flykoopa[9];
    //Constructor
    	Koopa(float ikx, float iky, int types){
    		kx = ikx;
    		ky = iky;
    		inposy = iky;
    		topY = iky - 50; 
    		vdir = -1;
    		flyTimer = 0;
    		flyDuration = 30;
    		kspeed = 0.8;
    		gravity = 1.0;
    		konground = false;
    		kactive = false;
    		stomped = false;
    		in = 0;
    		inShell = false;
    		shellMoving = false;
    		shellTimer = 0;
    		frameDelay = 10;
        	frameCount = 0;
        	starKilled = false;
        	dy = 0;
        	kdir = 1;
    		rotation = 0;
    		starTimer = 0;
    		klimit = 23;
    		safeTimer = 0;
    		type = types;
    		if(type == 3 || type == 4){
    			hasWings = true;
			}else{
				hasWings = false;
			}
		}
		//Métodos
		static void ckassets() {
			for(int i = 0; i < 9; i++) {
            std::stringstream str;
            str << "Sprites/"<< i + 1 <<"k"<<".png";
            koopa[i] = al_load_bitmap(str.str().c_str());
        	}
   			for(int i = 0; i < 9; i++) {
            std::stringstream str;
            str << "Sprites/"<< i + 1 <<"kr"<<".png";
            redkoopa[i] = al_load_bitmap(str.str().c_str());
        	}
        	for (int i = 0; i < 9; i++){
        	std::stringstream str;
        	if(i<4){
        		str << "Sprites/"<< i + 1 <<"kvr"<<".png";
            	redflykoopa[i] = al_load_bitmap(str.str().c_str());
			}else{
				str << "Sprites/"<< i + 1 <<"kr"<<".png";
				redflykoopa[i] = al_load_bitmap(str.str().c_str());
			}
			}
			for (int i = 0; i < 9; i++){
        	std::stringstream str;
        	if(i<4){
        		str << "Sprites/"<< i + 1 <<"kv"<<".png";
            	flykoopa[i] = al_load_bitmap(str.str().c_str());
			}else{
				str << "Sprites/"<< i + 1 <<"k"<<".png";
				flykoopa[i] = al_load_bitmap(str.str().c_str());
			}
			}
    	}
    	static void deskassets() {
        for(int i = 0; i < 9; i++) {
            al_destroy_bitmap(koopa[i]);
        }
          for(int i = 0; i < 9; i++) {
            al_destroy_bitmap(redkoopa[i]);
        }
          for(int i = 0; i < 9; i++) {
            al_destroy_bitmap(redflykoopa[i]);
        }
        for (int i = 0; i < 9; i++){
        	al_destroy_bitmap(flykoopa[i]);
		}
    	}
		void kupdate(){
		if(!kactive) return; 
		if (safeTimer > 0){
			safeTimer--;  
		} 	
        if (starKilled) {
        ky += dy;
        kx += kspeed;
        dy += 0.6;
        starTimer--;
        if (starTimer <= 0 || ky > 640) {
           kactive = false;
        }
        return;
    	}
		if (inShell && !shellMoving) {
            shellTimer--;
            if (shellTimer <= 0) {
                in = 8;
                frameCount++;
                if (frameCount >= frameDelay * 5) {
                    inShell = false;
                    stomped = false;
  					klimit = 23;
  					ky-=8;
                    kspeed = 0.8;
                    kdir = 0;
                    in = 3;
                    frameCount = 0;
                }
            }
            return;
        }
        if (inShell && shellMoving) {
            if (kdir == 0) kx += kspeed;
            else if(kdir==1) kx -= kspeed;
            frameCount++;
            if (frameCount >= frameDelay) {
                frameCount = 0;
                in++;
                if (in > 7) in = 6;
            }
            if(!konground) {
            ky += gravity;
        	if (gravity < 4.0) gravity *= 1.05;
			if(kdir==1){
				kx -= 0.3f;  
			}else if(kdir == 0){
				kx += 0.3f;     
			} 
        	}
            return;
        }
        if (type == 3 && !inShell && !starKilled) {
    		if (flyTimer > 0) {
        		flyTimer--;
    		} else {
        		ky += vdir *0.9f;
        	if (ky <= topY) {
            	vdir = 1;              
            	flyTimer = flyDuration;
        	}if (ky >= inposy) {
            ky = inposy;          
            vdir = -1;              
            flyTimer = flyDuration;
        	}
    	}
    	frameCount++;
            if(frameCount >= frameDelay) {
                frameCount = 0;
                in++;
                if(in >= 2) in = 0;
        }
    	gravity = 0;
    	konground = false;
    	return;
		}
		if (type == 4 && !inShell && !starKilled) {
    		frameCount++;
    		if (frameCount >= frameDelay) {
        		frameCount = 0;
        		in++;
        	if (in >= 2) in = 0;
    		}
    	if (!konground) {
        if (kdir == 1) kx -= kspeed;
        else           kx += kspeed;
    	}
    	if (!konground) {
        dy += 0.25f;
        if (dy > 3.0f) dy = 3.0f;
    	}
    	else {
        dy = -4.0f;      
        konground = false;  
    	}
    		ky += dy;
    		return;
		}
        if(!konground) {
            ky += gravity;
        	if (gravity < 4.0) gravity *= 1.05;
			if(kdir==1){
				kx -= 0.3f;  
			}else if(kdir == 0){
				kx += 0.3f;     
			} 
        }
        if(konground) {
        	gravity = 1;
        	if(kdir==1){
        	kx -= kspeed;
            frameCount++;
            if(frameCount >= frameDelay) {
                frameCount = 0;
                in++;
                if(in >= 2) in = 0;
            }
			}else if(kdir==0){
				kx+=kspeed;
				frameCount++;
				if(frameCount>=frameDelay){
					frameCount = 0;
					in++;
					if(in>=4) in=2;
				}
			} 
        }
		}
	void stomp(int dir) {
		if (hasWings && !inShell) {
        loseWings();
        return;
    	}
		if (!inShell) {
        inShell = true;
        shellMoving = false;
        stomped = true;
        klimit = 16;
        in = 5;
        kspeed = 0;
        shellTimer = 300;
        frameCount = 0;
        ky += 7;
        safeTimer = 50; 
        return;
    	}
    if (inShell && !shellMoving) {
        shellMoving = true;
        stomped = false;
        klimit = 16;
        in = 6;
        kspeed = 3;
        if (dir == 0)
            kdir = 0;
        else if (dir == 3)
            kdir = 1; 
		safeTimer = 50;  
        return;
    }
    if (shellMoving) {
        shellMoving = false;
        inShell = true;
        stomped = false;
        klimit = 16;
        in = 5; 
        kspeed = 0;
        safeTimer = 500; 
        return;
    }
    }
    void starHit() {
    if (starKilled || !kactive) return;
    starKilled = true;
    dy = -4;             
    rotation = ALLEGRO_PI;
    starTimer = 120;
	}
	void loseWings() {
    if (!hasWings) return;
    hasWings = false;
	if(type == 3){
		type = 2;  
	}  else if(type == 4){
		type = 1;
	} 
    gravity = 1;       
    konground = false;   
    vdir = 0;            
	}
    void kdraw() {
    	if(type == 1){
    	if(starKilled){
    		al_draw_rotated_bitmap(koopa[in], 8, 8, kx + 8, ky + 8, rotation, 0);
		}else if(kactive) {
            al_draw_bitmap(koopa[in], kx, ky, 0);
        }
		}else if(type == 2){
		if(starKilled){
    		al_draw_rotated_bitmap(redkoopa[in], 8, 8, kx + 8, ky + 8, rotation, 0);
		}else if(kactive) {
            al_draw_bitmap(redkoopa[in], kx, ky, 0);
        }	
		}else if(type == 3){
		if(starKilled){
    		al_draw_rotated_bitmap(redflykoopa[in], 8, 8, kx + 8, ky + 8, rotation, 0);
		}else if(kactive) {
            al_draw_bitmap(redflykoopa[in], kx, ky, 0);
        }
		}else if(type == 4){
		if(starKilled){
    		al_draw_rotated_bitmap(flykoopa[in], 8, 8, kx + 8, ky + 8, rotation, 0);
		}else if(kactive) {
            al_draw_bitmap(flykoopa[in], kx, ky, 0);
        }
		}
		
    }    		
};
ALLEGRO_BITMAP* Koopa::koopa[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
ALLEGRO_BITMAP* Koopa::redkoopa[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
ALLEGRO_BITMAP* Koopa::redflykoopa[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
ALLEGRO_BITMAP* Koopa::flykoopa[9] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
