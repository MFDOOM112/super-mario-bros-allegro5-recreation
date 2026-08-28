//Clase Mario y Luigi!!!!
#include<string>
#include<sstream>
#include<math.h>
#include<vector>
#include "Fireball.h"
struct PlayerControls{
	int left;
	int right;
	int down;
	int jump;
	int run;
};
class Player{
	public:
	float x, y;
    float velx, vely;
    float moveSpeed, maxSpeed, acceleration, deceleration, jumpSpeed;
    float gravity, limit;
    float deathVel;
    float yPrev;
    float damageCooldown; 
    int height;
    int wide;
    int tcoin;
    int w;
    double tpoints;
    std::string p;
    bool jump;      
    bool onGround; 
    bool active;      
    bool crouch;    
    bool dead;		 
    bool invincible; 
    bool transforming; 
    bool starPower; 
    bool cclear; 
    bool automov;
    bool endanim;
    bool saveToad;
    bool warp;
    bool exitWarp;
    bool down;
    bool wasDown;
    bool shootPressed;
    bool shooting;
    bool dieFalling;
    bool canShoot;
    bool sOnce;
    float transformTimer;
    float flagY;
    float castleX;
    float shootTimer;
    int comp;
	int transformType;
	int frameCount;
	int frameDelay;
	float starTimer;
	float starDuration;
	float invincibleTime;
	float invincibleDuration;
	float jumpHoldTime;
    int dir;        
    int prevDir;      
    int index;       
    int brakeFrames;  
    int lives;		  
    int live;		  
    std::vector<Fireball*> fireballs;
    ALLEGRO_BITMAP* playerWalk[29];
    ALLEGRO_BITMAP* walkSmall[29];
	ALLEGRO_BITMAP* walkBig[29];
	ALLEGRO_BITMAP* walkFire[29];
    ALLEGRO_SAMPLE *sJump;
    ALLEGRO_SAMPLE *sDamage;
	ALLEGRO_SAMPLE *sFireball;
	ALLEGRO_SAMPLE *sSwim;
	ALLEGRO_COLOR transformColor;
    int RIGHT;
    int LEFT;
    int maxBrakeFrames;
    PlayerControls controls;
    //Constructor
    Player(float inx, float iny, std::string m, PlayerControls c){
    	RIGHT = 0;
    	LEFT = 3;
    	controls = c;
    	maxBrakeFrames = 30;
    	x = inx;
        y = iny;
        velx = 0;
        vely = 0;
        moveSpeed = 3;
        maxSpeed = 6;
        acceleration = 0.4;
        deceleration = 0.3;
        jumpSpeed = 15;
        gravity = 1;
        active = false;
        dir = RIGHT;
        prevDir = RIGHT;
        index = 0;
        brakeFrames = 0;
        lives = 5;
        live = 1;
        height = 16;
        wide = 16;
        limit = 16;
        crouch = false;
        dead = false;
        deathVel = 0;
        invincible = false;
        invincibleTime = 0;
        invincibleDuration = 1.0;
        tcoin = 0;
        starPower = false;
        starTimer = 0;
        starDuration = 7.0;
        transformTimer = 0;
        transformType = 0;
        p = m;
        onGround = false;
        cclear = false;
        automov = false;
        frameCount = 0;
        frameDelay = 5;
        flagY = 0;
        comp = 0;
        endanim = false;
        tpoints = 0;
        damageCooldown = 0;
        warp = false;
        exitWarp = false;
        down = false;
        dieFalling = false;
        canShoot = false;
        shootPressed = false;
        shooting = false;
        shootTimer = 0;
        wasDown = false;
        sOnce = false;
        saveToad = false;
        jumpHoldTime = 0;
	}
	//Métodos
	void crearAssets(std::string m) {
    for (int i = 0; i < 29; i++) {
        std::stringstream s;
        s << "Sprites/" << i+1 << m << ".png";
        walkSmall[i] = al_load_bitmap(s.str().c_str());
    }
    for (int i = 0; i < 29; i++) {
        std::stringstream s;
        s << "Sprites/" << i+1 << m << "g" << ".png";
        walkBig[i] = al_load_bitmap(s.str().c_str());
    }
    for (int i = 0; i < 29; i++) {
        std::stringstream s;
        s << "Sprites/" << i+1 << m << "f" << ".png";
        walkFire[i] = al_load_bitmap(s.str().c_str());
    }
    for (int i = 0; i < 29; i++) {
        playerWalk[i] = walkSmall[i];
    }
        sJump = al_load_sample("Sounds/Jump.wav");
        sDamage = al_load_sample("Sounds/Damage.wav");
		sFireball = al_load_sample("Sounds/Fireball.wav");
		sSwim = al_load_sample("Sounds/Swim.wav");
		Fireball::cfbassets();
    }
//Destructor
    void destruirAssets() {
        for (int i = 0; i < 29; i++) {
            al_destroy_bitmap(playerWalk[i]);
        }
        al_destroy_sample(sJump);
        al_destroy_sample(sDamage);
        Fireball::dfbassets();
    }
    void muerte() {
        if (!dead) {
        	index = 18;
            dead = true;
            lives--;
            vely = -10;       
            deathVel = vely;
            velx = 0;          
        }
        fireballs.clear();
		shooting = false;
		canShoot = false;
    }
	void update(ALLEGRO_KEYBOARD_STATE &keyState, float deltaTime){
	if(exitWarp){
		if(onGround){
		frameCount++;
		x+=2;
		if (frameCount >= frameDelay) {
        frameCount = 0;
        index++;
        if (index > 2) index = 0;
    	}
		return;
		}
	}
	if(warp){
		if(w == 1){
			frameCount++;
		y+=1;
		if(frameCount>=frameDelay){
			frameCount = 0;
			if(index>28) index = 27;
		}else{
			index = 27;
		}
		}else if(w == 2){
			
		}
		return; 
	}
	if(cclear){
		frameCount++;
		y+=1;
		if(frameCount>=frameDelay){
			frameCount = 0;
			index++;
			if(index>21) index = 20;
		}else{
			index = 20;
		}
		if(y>=flagY){
			y = flagY;
			cclear = false;
			comp = 1;
			index = 0;
			frameCount = 0;
			x+=7;
			automov = true;
		}
		return;
	}
	if(saveToad){
		automov = true;
	}
	if(automov){
		if(onGround){
		frameCount++;
		if(!saveToad){
			x+=2;
		}else{
			x+=0.6;
		}		
		if (frameCount >= frameDelay) {
        frameCount = 0;
        index++;
        if (index > 2) index = 0;
    	}
    	if(x>=castleX){
    		x = castleX-8;
    		endanim = true;
    		automov = false;
    		frameCount = 0;
    		index = 24;
		}
		return;
		}
	}
	if(endanim){
		frameCount++;
		if (frameCount >= frameDelay * 3) {
        frameCount = 0;
        index++;
        if (index > 26) index = 24;
    	}
    	return;
	}
	if (starPower) {
    starTimer -= deltaTime;
    float t = fmod(al_get_time() * 4, 6);
    if (t < 1) transformColor = al_map_rgb(255, 0, 0);
    else if (t < 2) transformColor = al_map_rgb(255, 165, 0);
    else if (t < 3) transformColor = al_map_rgb(255, 255, 0);
    else if (t < 4) transformColor = al_map_rgb(0, 255, 0);
    else if (t < 5) transformColor = al_map_rgb(0, 0, 255);
    else transformColor = al_map_rgb(255, 0, 255);
    invincible = true;
    if (starTimer <= 0) {
        starPower = false;
        invincible = false;
    }
	}
	if (transforming) {
	velx = 0;
    vely = 0;
    transformTimer -= deltaTime;
    if (transformType == 1) {
    	if (onGround) y-=16;
        if (fmod(transformTimer * 10, 2) < 1){
        	for (int i = 0; i < 29; i++)
            	playerWalk[i] = walkSmall[i];
            if(onGround) y+=16;
		}else{
			for (int i = 0; i < 29; i++)
                playerWalk[i] = walkBig[i];
		}
		if(transformTimer<=0){
			if(onGround) y-=16;
		}

    }else if (transformType == 2) {
        float t = fmod(al_get_time() * 4, 6); 
        if (t < 1) transformColor = al_map_rgb(255, 0, 0);       
        else if (t < 2) transformColor = al_map_rgb(255, 165, 0);
        else if (t < 3) transformColor = al_map_rgb(255, 255, 0); 
        else if (t < 4) transformColor = al_map_rgb(0, 255, 0);   
        else if (t < 5) transformColor = al_map_rgb(0, 0, 255);   
        else transformColor = al_map_rgb(255, 0, 255);            
        for (int i = 0; i < 29; i++)
            playerWalk[i] = walkFire[i];
    }

    if (transformTimer <= 0) {
        transforming = false;
        if (transformType == 1){
        	for (int i = 0; i < 29; i++)
                playerWalk[i] = walkBig[i];
		}else if (transformType == 2){
			for (int i = 0; i < 29; i++)
                playerWalk[i] = walkFire[i];
		}
        transformType = 0;
        height = (live == 1 ? 16 : 32);
        wide = 16;
        limit = height;
        invincible = false;
    }
    return;
	}
	if (invincible) {
    invincibleTime -= deltaTime;
    if (invincibleTime <= 0) {
        invincible = false;
    }
	}
	if (dead) {
			if(!dieFalling){
			vely += gravity/2;
            y += vely/1.9;
			}else{
			if(dir == RIGHT){
				index = 6;
			}else if (dir == LEFT){
				index = 7;
			}
			y += 0.7;
			}
            return;
    }
    if (damageCooldown > 0) {
    damageCooldown -= deltaTime;
	}
	float dt = deltaTime * 60;
    bool holdRun = al_key_down(&keyState, controls.run);
    float walkSpeed = 2.0f;
    float runSpeed = 3.5f;
    float targetSpeed;
    if(holdRun){
    	targetSpeed = runSpeed;
	}else{
		targetSpeed = walkSpeed;
	}
    float targetVelX = 0;
    if (al_key_down(&keyState, controls.right)) targetVelX += targetSpeed;
    if (al_key_down(&keyState, controls.left))  targetVelX -= targetSpeed;
    if (al_key_down(&keyState, controls.down)){
    	down = true;
    	if(live>=2 && onGround){
    		if(!wasDown){
    			y += 10;
			}
    		height = 22;
    		if(dir == RIGHT){
    			index = 16;
			}else if(dir == LEFT){
				index = 17;
			}
			wasDown = true;
			return;
		}
	}else{
		if(live>=2){
		if (wasDown) {
        y -= 16;
        }
        height = 32;
		}
		down = false;
		wasDown = false;
	}
    if (targetVelX > 0) dir = RIGHT;
    else if (targetVelX < 0) dir = LEFT;
    if ((velx > 0 && targetVelX < 0) || (velx < 0 && targetVelX > 0)) {
        brakeFrames = maxBrakeFrames;
    }
    if (brakeFrames > 0) {
        float brakeDecel = deceleration * dt;
        if (velx > 0) { velx -= brakeDecel; if (velx < 0) velx = 0; }
        else if (velx < 0) { velx += brakeDecel; if (velx > 0) velx = 0; }
        brakeFrames -= dt;
    } else {
        if (velx < targetVelX) { velx += acceleration * dt; if (velx > targetVelX) velx = targetVelX; }
        else if (velx > targetVelX) { velx -= acceleration * dt; if (velx < targetVelX) velx = targetVelX; }
    }
    const float maxJumpHold = 0.15f;
    const float jumpShort = 3.0f;
    const float jumpMedium = 6.0f;
    const float jumpMax = holdRun ? 10.0f : 9.0f;
    if (al_key_down(&keyState, controls.jump)) {
        if (onGround && jumpHoldTime == 0) {
            vely = -jumpShort;
            jumpHoldTime = 0.01f;
            onGround = false;
            if (sJump) al_play_sample(sJump, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        } else if (jumpHoldTime > 0 && jumpHoldTime < maxJumpHold) {
            float factor = jumpHoldTime / maxJumpHold;
            float targetVel = jumpShort + factor * (jumpMax - jumpShort);
            if (vely > -targetVel) vely = -targetVel;
            jumpHoldTime += dt / 60.0f;
        }
    } else jumpHoldTime = 0;
    yPrev = y;
    if (!onGround) vely += gravity * dt;
    x += velx * dt;
    y += vely * dt;
    active = (velx != 0);
    bool keyShoot = al_key_down(&keyState, controls.run);
    bool shootNow = (keyShoot && !shootPressed);
    shootPressed = keyShoot;
    if (!canShoot || !shootNow) {
    } else {
    if (fireballs.size() < 2) {
    	 index = (dir == RIGHT ? 28 : 19);
		shooting = true;
    	shootTimer = 0.12f;
        al_play_sample(sFireball, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        fireballs.push_back(new Fireball(x+10, y-5, dir));
    }
	}
	if (shooting) {
    	shootTimer -= deltaTime;
    	if (shootTimer <= 0) {
        shooting = false;
    	} else {
        index = (dir == RIGHT ? 28 : 19);
        return;
    	}
	} 
    if (!onGround) {
        index = (dir == RIGHT) ? 6 : 7;
    } else if (brakeFrames > 0) {
        index = (dir == RIGHT) ? 8 : 9;
    } else if (active) {
        frameCount++;
        if (frameCount >= frameDelay) {
            frameCount = 0;
            index++;
            if (index > dir + 2) index = dir;
        }
    } else index = dir;
}
void updateSwim(ALLEGRO_KEYBOARD_STATE &keyState, float deltaTime){
    float dt = deltaTime * 60;
    if (dead || transforming || starPower || warp || exitWarp || automov || endanim || cclear || shooting) {
        update(keyState, deltaTime);
        return;
    }
    float swimGravity = 0.15f;
    float maxFall = 1.8f;
    bool holdRun = al_key_down(&keyState, controls.run);
    float swimSpeed = holdRun ? 2.0f : 1.0f;
    float targetVelX = 0;
    if (al_key_down(&keyState, controls.right))  targetVelX += swimSpeed;
    if (al_key_down(&keyState, controls.left))   targetVelX -= swimSpeed;
    if (al_key_down(&keyState, controls.down))   down = true;
    else                                            down = false;
    if (targetVelX > 0) dir = RIGHT;
    else if (targetVelX < 0) dir = LEFT;
    if (onGround) {
        if (targetVelX > 0) velx = 0.6;
        else if (targetVelX < 0) velx = -0.6;
        else velx = 0;
    }
    else {
        if (velx < targetVelX) {
            velx += 0.1f * dt;
            if (velx > targetVelX) velx = targetVelX;
        }
        else if (velx > targetVelX) {
            velx -= 0.1f * dt;
            if (velx < targetVelX) velx = targetVelX;
        }
    }
    static bool swimPressed = false;
    bool swimKey = al_key_down(&keyState, controls.jump);
    if (swimKey && !swimPressed) {
    	al_play_sample(sSwim, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        vely = -2.5f;
        frameCount = 0;
        if(dir==RIGHT){
        	index = 10;
		}else if(dir == LEFT){
			index = 13;
		}
    }
    swimPressed = swimKey;
    if (!onGround) {
        vely += swimGravity * dt;
        if (vely > maxFall) vely = maxFall;
    }
    x += velx * dt;
    y += vely * dt;
    active = (velx != 0);
    if (!onGround) {
        frameCount++;
        if (frameCount >= 7) {
            frameCount = 0;
            index++;
            if (dir == RIGHT) {
                if(index>=13 || index<10){
                	index = 10;
				}
            } else {
                if (index>=16 || index <13){
                	index = 13;	
				}
            }
        }
    } else {
        frameCount++;
        if(active){
        	if(frameCount>=frameDelay){
        	frameCount = 0;
        	index++;
        	if(dir == RIGHT){
        		if(index>=3){
        			index = 0;
				}
			}else{
				if(index>=6){
					index = 3;
				}
			}
		}
		}else{
			index = dir;
		}
    }
}
	void draw(){
	if (invincible && !transforming && !starPower) {
        if (fmod(al_get_time() * 10, 2) < 1) return;
    }
    if (transforming && transformType == 2) {
        al_draw_tinted_bitmap(playerWalk[index], transformColor, x, y, 0);
    }else if(starPower){
    	 al_draw_tinted_bitmap(playerWalk[index], transformColor, x, y, 0);
	} else {
        al_draw_bitmap(playerWalk[index], x, y, 0);
    }
    for (size_t i = 0; i < fireballs.size(); i++) {
    	fireballs[i]->fbdraw();
    	if (fireballs[i]->dead || fireballs[i]->x < 0 || fireballs[i]->x > 5000) {
        delete fireballs[i];
        fireballs.erase(fireballs.begin() + i);
        i--;
    	}
	}
	}
	void damage(){
		if (dead||invincible) return;
    switch(live){
    	case 1:
        muerte();
        break;
        case 2:
        live = 1;
        al_play_sample(sDamage, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        for (int i = 0; i < 29; i++)
                playerWalk[i] = walkSmall[i];
        height = 16; wide = 16; limit = 16;
        invincible = true;
        canShoot = false;
        break;
        case 3:
        live = 2;
        al_play_sample(sDamage, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        for (int i = 0; i < 29; i++)
                playerWalk[i] = walkBig[i];
        height = 32; wide = 16; 
		limit = height; 
        invincible = true;
        canShoot = false;
		break;  
	}
	invincibleTime = invincibleDuration; 
    }
	void powerup(int change){
	if (dead) return;
    if (change == 2 && live < 2) {
        transforming = true;
        transformType = 1;
        transformTimer = 1.0;
        live = 2;
    } 
    else if (change == 3 && live < 3) {
        transforming = true;
        transformType = 2;
        transformTimer = 1.0;
        canShoot = true;
        live = 3;
    }else if(change == 4){
    	starPower = true;
    	starTimer = starDuration;
    	invincible = true;
    	invincibleTime = starDuration;
    	transformColor = al_map_rgb(255, 255, 0);
    	return;
	}
    invincible = true;
    invincibleTime = 1.0;
	}
	void setPower(int live){
		if(live == 1){
			for (int i = 0; i < 29; i++)
                playerWalk[i] = walkSmall[i];
		}else if(live == 2){
			for (int i = 0; i < 29; i++)
                playerWalk[i] = walkBig[i];
		}else if(live == 3){
			for (int i = 0; i < 29; i++)
                playerWalk[i] = walkFire[i];
		}
	}
};
