#include<string>
#include<algorithm>
class GameManager{
	public:
		float cameraX;
		float cameraY;
		float scale;
		ALLEGRO_SAMPLE* sPowerup;
		ALLEGRO_SAMPLE* sExtralife;
		ALLEGRO_SAMPLE *sStomp;
		ALLEGRO_SAMPLE *sCoin;
		ALLEGRO_SAMPLE *soHit;
		ALLEGRO_SAMPLE *sWarp;
		ALLEGRO_SAMPLE *sNothing;
		ALLEGRO_SAMPLE* dying;
		ALLEGRO_SAMPLE* sBattle;
		ALLEGRO_SAMPLE_INSTANCE* sfxInstance;
		bool waitingForSFX;
		std::string currentSection;
		bool starPlaying;
		double lastStompTime;
		double lastHitTime;
		double lastStarHitTime;
		float ENEMY_ACTIVATE_DIST;
		bool isFading;
		bool fadeIn;
		bool warped;
		float fadeAlpha;
		float fadeSpeed;
		float warpTargetX;
		float warpTargetY;	
	//Constructor
	GameManager(){
		scale = 1.0;
		cameraX = cameraY = 0;
		sPowerup = al_load_sample("Sounds/Powerup.wav");
		sExtralife = al_load_sample("Sounds/ExtraLife.wav");
		sStomp = al_load_sample("Sounds/Stomp.wav");
		sCoin = al_load_sample("Sounds/Coin.wav");
		soHit = al_load_sample("Sounds/Hit.wav");
		sWarp = al_load_sample("Sounds/Warp.wav");
		sNothing = al_load_sample("Sounds/Nothing.wav");
		dying = al_load_sample("Sounds/Dying.wav");
		sBattle = al_load_sample("Sounds/battle.wav");
		lastStompTime = lastHitTime = lastStarHitTime = 0;
		ENEMY_ACTIVATE_DIST = 200.0f;
		isFading = false;
		fadeIn = false;
		fadeAlpha = 0.0f;
		warpTargetX = 0;
		warpTargetY = 0;
		warped = false;
		sfxInstance = NULL;
		waitingForSFX = false;
	}
	//Métodos públicos y privados
	void updateCamera(float screenWidth, float screenHeight, float levelWidth, float levelHeight,LevelLoader* loader, Player* player){
    std::string sec = currentSection;
    float halfW = screenWidth / (2 * scale);
    float halfH = screenHeight / (2 * scale);
    if (sec == "bonus"){
        cameraX = (loader->levelBonusWidth - screenWidth / scale) / 2;
        cameraY = loader->bonusStartY;
        return;
    }
    if (sec == "intro"){
        cameraX = 0;                        
        cameraY = loader->introStartY;     
        return;
    }
    if (sec == "exit"){
        cameraX = player->x + player->wide/2 - halfW;
        if (cameraX < 0) cameraX = 0;
        float maxX = loader->levelWidth - screenWidth/scale;
        if (cameraX > maxX) cameraX = maxX;
        cameraY = loader->exitStartY;
        return;
    }
    if (sec == "main"){
        cameraX = player->x + player->wide/2 - halfW;
        if (cameraX < 0) cameraX = 0;
        float maxX = loader->levelWidth - screenWidth/scale;
        if (cameraX > maxX) cameraX = maxX;
        cameraY = loader->mainStartY;
        return;
    }
    cameraX = 0;
    cameraY = 0;
	}
	void updateCamera2P(float screenWidth, float screenHeight, LevelLoader* loader, Player* p1, Player* p2){
        float halfW = screenWidth / (2 * scale);
    std::string sec = currentSection;
    if (sec == "bonus") {
        cameraX = (loader->levelBonusWidth - screenWidth / scale) / 2;
        cameraY = loader->bonusStartY;
        return;
    }
    if (sec == "intro") {
        cameraX = 0;
        cameraY = loader->introStartY;
        return;
    }
    if (sec == "exit") {
        float centerX = (p1->x + p1->wide/2 + p2->x + p2->wide/2) / 2.0f;
        cameraX = centerX - halfW;
        if (cameraX < 0) cameraX = 0;
        float maxX = loader->levelWidth - screenWidth / scale;
        if (cameraX > maxX) cameraX = maxX;
        cameraY = loader->exitStartY;
        return;
    }
    if (sec == "main") {
        float centerX = (p1->x + p1->wide/2 + p2->x + p2->wide/2) / 2.0f;
        cameraX = centerX - halfW;
        if (cameraX < 0) cameraX = 0;
        float maxX = loader->levelWidth - screenWidth / scale;
        if (cameraX > maxX) cameraX = maxX;
        cameraY = loader->mainStartY;
        return;
    }
    cameraX = 0;
    cameraY = 0;
	}
	void playSFXAndPauseMusic(const std::string& name, LevelLoader &l) {
 	if (!l.sfx.count(name)) return;
    al_stop_sample_instance(l.currentInstance);
    if (sfxInstance)
        al_destroy_sample_instance(sfxInstance);
    sfxInstance = al_create_sample_instance(l.sfx[name]);
    al_attach_sample_instance_to_mixer(sfxInstance, al_get_default_mixer());
    al_set_sample_instance_playmode(sfxInstance, ALLEGRO_PLAYMODE_ONCE);
    al_play_sample_instance(sfxInstance);
    waitingForSFX = true;
	}
	void updateFade(LevelLoader &loader, Player *player, Player* luigi){
	if (!isFading) return;
    if (fadeIn) {
        fadeAlpha += fadeSpeed;
        if (fadeAlpha >= 2.0f) {
            fadeIn = false;
            fadeSpeed = 0.03f;
        }
    } else {
        fadeAlpha -= fadeSpeed;
        if (fadeAlpha <= 0.8f) {
            fadeAlpha = 0.0f;
            player->x = warpTargetX;
            player->y = warpTargetY;
            if(luigi){
            	luigi->x = warpTargetX;
            	luigi->y = warpTargetY;
            	luigi->warp = false;
			}
            isFading = false;
            bool wasExitWarp = player->exitWarp;
 			player->warp = false;
 			player->exitWarp = false;
			warped = !wasExitWarp;
			currentSection = loader.getSection(player->y);
			al_play_sample(sWarp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        }
    }
	}
	void verifColision(LevelLoader &level, Player* player){
		if (waitingForSFX) {
 			if (!al_get_sample_instance_playing(sfxInstance)){
        	waitingForSFX = false;
        	al_play_sample_instance(level.currentInstance);
    		}
    	}
    	if(player->dead){
    		if(!player->sOnce){
    				player->sOnce = true;
        			playSFXAndPauseMusic("dead", level);		
			}
			return;
		}
		float bottom = level.getSectionBottom(level.getSection(player->y));
		std::string sec = level.getSection(player->y);
		player->onGround = false;
		if (!isFading && !player->warp && !player->exitWarp && !player->dead && sec== "main") {
    	if (player->y > bottom-16 && player->vely>0) {
		player->dieFalling = true; 
        player->live = 1;
        player->damage();   
        return;
    	}
		}
		for (size_t i = 0; i < level.grounds.size(); i++) {
        Ground* gr = level.grounds[i];
        if (colisionSuelo(player, gr->x, gr->y, level.tileSize, level.tileSize)) {
        	player->y = gr->y - player->height;
        	player->vely = 0;
        	player->onGround = true;
    		}
    	for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, gr->x, gr->y, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = gr->y - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
		}
    	colisionLateral(player, gr->x, gr->y, level.tileSize, level.tileSize);
    	}
    	for (size_t i = 0; i < level.plats.size(); i++) {
        Plat* pl = level.plats[i];
        if (colisionSuelo(player, pl->x, pl->y, level.tileSize, level.tileSize) && pl->tipo == 1) {
        	player->y = pl->y - player->height;
        	player->vely = 0;
        	player->onGround = true;
    		}
    		if(verifColisiones(player->x,player->y,player->wide,player->height,pl->x,pl->y,16,16) && pl->tipo == 1){
    			if (player->vely < 0 && (player->y > pl->y + 4)) {
    				if (canPlay(lastHitTime, 0.3)) {
        				al_play_sample(sNothing, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    				}
    				if (player->vely < 0) {
        				player->y = pl->y + 16;
        				player->vely = 0;
					}
    			}
			}
			for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, pl->x, pl->y, level.tileSize, level.tileSize, fb->speedy) && pl->tipo == 1){
				fb->y = pl->y - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, pl->x, pl->y, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
		if(pl->tipo == 1){
			colisionLateral(player, pl->x, pl->y, level.tileSize, level.tileSize);	
		}
    	}
    	for (size_t i=0; i<level.gradas.size(); i++){
    		Grada* st = level.gradas[i];
    		if(colisionSuelo(player, st->x, st->y, level.tileSize, level.tileSize)){
    			player->y = st->y - player->height;
        		player->vely = 0;
        		player->onGround = true;
			}
			for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, st->x, st->y, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = st->y - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, st->x, st->y, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
			colisionLateral(player, st->x, st->y, level.tileSize, level.tileSize);
		}
		for(size_t i=0; i<level.cblocks.size(); i++){
			cBlock* cb = level.cblocks[i];
			if (colisionSuelo(player, cb->x, cb->y, level.tileSize, level.tileSize)) {
        	player->y = cb->y - player->height;
        	player->vely = 0;
        	player->onGround = true;
    		}
    		if(colisionLateral(player, cb->x, cb->y, 16,16));
    		if(verifColisiones(player->x,player->y,player->wide,player->height,cb->x,cb->y,16,16)){
    			if (player->vely < 0 && (player->y > cb->y + 4)) {
    				if (canPlay(lastHitTime, 0.3)) {
        				al_play_sample(sNothing, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    				}
    				if (player->vely < 0) {
        				player->y = cb->y + 16;
        				player->vely = 0;
					}
    			}
			}
			for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, cb->x, cb->y, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = fb->y - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, cb->x, cb->y, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
		}
		for(size_t i=0; i<level.billblasters.size(); i++){
			BillBlaster* bbl = level.billblasters[i];
			float dx = fabs(player->x - bbl->x);
    		float dy = fabs(player->y - bbl->y);
    		if(dx <= ENEMY_ACTIVATE_DIST && dy <= 300){
        		bbl->active = true;
    		}
    		else if(dx >= ENEMY_ACTIVATE_DIST + 80 || dy >= 450){
        		bbl->active = false;
    		}
			if (colisionSuelo(player, bbl->x, bbl->y, level.tileSize, level.tileSize)) {
        	player->y = bbl->y - player->height;
        	player->vely = 0;
        	player->onGround = true;
    		}
    		if(colisionLateral(player, bbl->x, bbl->y, 16,32));
    		for(size_t j=0; j<bbl->bulletbills.size(); j++){
    		BulletBill* bbi = bbl->bulletbills[j];
    		if(bbi->active && verifColisiones(player->x,player->y,player->wide,player->height,bbi->x,bbi->y,16,14)){
			float playerBottom = player->y + player->height;
			float playerBottomPrev = player->yPrev + player->height;
    		float bulletTop = bbi->y;
			if (player->starPower){
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		bbi->starHit();
    		}else if((playerBottomPrev <= bulletTop && playerBottom >= bulletTop)){
				al_play_sample(sStomp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        		bbi->starHit();
        		player->vely = -6;	
			}else if(!bbi->starKilled){
				player->damage();   
			}
			}
			}
			for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, bbl->x, bbl->y, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = bbl->y - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, bbl->x, bbl->y, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
		}
		for(size_t i=0; i<level.filafuegos.size(); i++){
			filaFuego* ff = level.filafuegos[i];
			if (colisionSuelo(player, ff->x, ff->y, level.tileSize, level.tileSize)) {
        	player->y = ff->y - player->height;
        	player->vely = 0;
        	player->onGround = true;
    		}
    		if(colisionLateral(player, ff->x, ff->y, 16,16));
    		for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, ff->x, ff->y, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = ff->y - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, ff->x, ff->y, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
    		if(verifColisiones(player->x,player->y,player->wide,player->height,ff->x,ff->y,16,16)){
    			if (player->vely < 0 && (player->y > ff->y + 4)) {
    				if (canPlay(lastHitTime, 0.3)) {
        				al_play_sample(sNothing, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    				}
    				if (player->vely < 0) {
        				player->y = ff->y + 16;
        				player->vely = 0;
					}
    			}
			}
			    float cx = ff->x + 8;
    			float cy = ff->y + 8;
    			float barW = 43;
    			float barH = 8;
    			float halfW = barW / 2.0f;
    			float halfH = barH / 2.0f;
    			float mx = player->x + player->wide / 2.0f;
    			float my = player->y + player->height / 2.0f;
    			float dx = mx - cx;
    			float dy = my - cy;
    			float cosA = cos(ff->angle);
    			float sinA = sin(ff->angle);
    			float localX = dx * cosA + dy * sinA;
    			float localY = -dx * sinA + dy * cosA;
    			float start = ff->radius - halfW;
    			float end   = ff->radius + halfW;
    			if(localX >= start && localX <= end &&
       			localY >= -halfH && localY <= halfH)
    			{
        		player->damage();
    		}
		}
		for (size_t i = 0; i < level.tubos.size(); i++){
			Tubo* t = level.tubos[i];
			if(!player->warp && !player->exitWarp){
				if (colisionSuelo(player, t->x,t->y, level.tileSize, level.tileSize)){
				player->y = t->y - player->height;
        		player->vely = 0;
        		player->onGround = true;
				}
				colisionLateral(player, t->x, t->y, level.tileSize, level.tileSize);	
			}
			for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, t->x, t->y, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = t->y - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, t->x, t->y, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
		}
    	for(size_t i=0; i<level.bricks.size();i++){
    		Brick* b = level.bricks[i];
    		if (colisionSuelo(player, b->bx, b->by, 16, 16)) {
        		player->y = b->by - player->height;
       		 	player->vely = 0;
        		player->onGround = true;
    		}
    		if(colisionLateral(player, b->bx, b->by, 16,16));
    		for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, b->bx, b->by, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = b->by - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, b->bx, b->by, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
    		if(verifColisiones(player->x,player->y,player->wide,player->height,b->bx,b->by,8,16)){
			if (player->vely < 0 && (player->y > b->by + 4)) {
			if(!b->bactive){
				if (canPlay(lastHitTime, 0.3)) {
        			al_play_sample(sNothing, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
			}
			if(player->live>1){
				b->pbig = true;	
			} 
        	b->bobject();
        	if(b->Case == 2){
        		if(b->coinup){
        			player->tcoin++;
				}
			}
    		}
    		if (player->vely < 0) {
        	player->y = b->by + 16;
        	player->vely = 0;
			}
			}
			if (b->hongo && b->hongo->hactive && b->hongo->canBeEaten && verifColisiones(player->x, player->y, player->wide, player->height, b->hongo->hx, b->hongo->hy, 16, 16)) {
                al_play_sample(sPowerup, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                b->hongo->hactive = false;
                player->powerup(2);
            }
            if(b->hongo && b->hongo->hactive){
            	b->hongo->hjump = false;
            	for(size_t j=0; j<level.grounds.size();j++){
				Ground* gr = level.grounds[j];
				if(icolisionSuelo(b->hongo->hx, b->hongo->hy, 16, 16, gr->x, gr->y, level.tileSize, level.tileSize, b->hongo->vspeed)){
					b->hongo->landOn(gr->y);
				}
				if(icolisionLateral(b->hongo->hx, b->hongo->hy, 16,16, gr->x, gr->y, level.tileSize, level.tileSize)){
					b->hongo->changeDirection();	
				}
				}
				for(size_t j=0; j<level.bricks.size();j++){
				Brick* br = level.bricks[j];
				if(icolisionSuelo(b->hongo->hx, b->hongo->hy, 16, 16, br->bx, br->by, level.tileSize, level.tileSize, b->hongo->vspeed)){
					b->hongo->landOn(br->by);
				}
				if(icolisionLateral(b->hongo->hx, b->hongo->hy, 16,16, br->bx, br->by, level.tileSize, level.tileSize)){
					b->hongo->changeDirection();	
				}
				}
				for(size_t j=0; j<level.interrogations.size();j++){
				Interrogation* it = level.interrogations[j];
				if(icolisionSuelo(b->hongo->hx, b->hongo->hy, 16, 16, it->ix, it->iy, level.tileSize, level.tileSize, b->hongo->vspeed)){
					b->hongo->landOn(it->iy);
				}
				if(icolisionLateral(b->hongo->hx, b->hongo->hy, 16,16, it->ix, it->iy, level.tileSize, level.tileSize)){
					b->hongo->changeDirection();	
				}
				}
				for(size_t j=0; j<level.gradas.size();j++){
					Grada* gra = level.gradas[j];
					if(icolisionSuelo(b->hongo->hx, b->hongo->hy, 16, 16, gra->x, gra->y, level.tileSize, level.tileSize, b->hongo->vspeed)){
					b->hongo->landOn(gra->y);
					}
					if(icolisionLateral(b->hongo->hx, b->hongo->hy, 16,16, gra->x, gra->y, level.tileSize, level.tileSize)){
					b->hongo->changeDirection();	
					}
				}
				for(size_t j=0; j<level.tubos.size();j++){
					Tubo* t = level.tubos[j];
					if(icolisionSuelo(b->hongo->hx, b->hongo->hy, 16, 16, t->x, t->y, level.tileSize, level.tileSize, b->hongo->vspeed)){
					b->hongo->landOn(t->y);
					}
					if(icolisionLateral(b->hongo->hx, b->hongo->hy, 16,16, t->x, t->y, level.tileSize, level.tileSize)){
					b->hongo->changeDirection();	
					}
				}
			}
            if (b->vida && b->vida->vactive && b->vida->canBeEaten && verifColisiones(player->x, player->y, player->wide, player->height, b->vida->vx, b->vida->vy, 16, 16)) {
                al_play_sample(sExtralife, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                b->vida->vactive = false;
                player->lives++;
            }
                if(b->vida && b->vida->vactive){
            	b->vida->vjump = false;
            	for(size_t j=0; j<level.grounds.size();j++){
				Ground* gr = level.grounds[j];
				if(icolisionSuelo(b->vida->vx, b->vida->vy, 16, 16, gr->x, gr->y, level.tileSize, level.tileSize, b->vida->vspeed)){
					b->vida->landOn(gr->y);
				}
				if(icolisionLateral(b->vida->vx, b->vida->vy, 16,16, gr->x, gr->y, level.tileSize, level.tileSize)){
					b->vida->changeDirection();	
				}
				}
				for(size_t j=0; j<level.bricks.size();j++){
				Brick* br = level.bricks[j];
				if(icolisionSuelo(b->vida->vx, b->vida->vy, 16, 16, br->bx, br->by, level.tileSize, level.tileSize, b->vida->vspeed)){
					b->vida->landOn(br->by);
				}
				if(icolisionLateral(b->vida->vx, b->vida->vy, 16,16, br->bx, br->by, level.tileSize, level.tileSize)){
					b->vida->changeDirection();	
				}
				}
				for(size_t j=0; j<level.interrogations.size();j++){
				Interrogation* it = level.interrogations[j];
				if(icolisionSuelo(b->vida->vx, b->vida->vy, 16, 16, it->ix, it->iy, level.tileSize, level.tileSize, b->vida->vspeed)){
					b->vida->landOn(it->iy);
				}
				if(icolisionLateral(b->vida->vx, b->vida->vy, 16,16, it->ix, it->iy, level.tileSize, level.tileSize)){
					b->vida->changeDirection();	
				}
				}
				for(size_t j=0; j<level.gradas.size();j++){
					Grada* gra = level.gradas[j];
					if(icolisionSuelo(b->vida->vx, b->vida->vy, 16, 16, gra->x, gra->y, level.tileSize, level.tileSize, b->vida->vspeed)){
					b->vida->landOn(gra->y);
					}
					if(icolisionLateral(b->vida->vx, b->vida->vy, 16,16, gra->x, gra->y, level.tileSize, level.tileSize)){
					b->vida->changeDirection();	
					}
				}
				for(size_t j=0; j<level.tubos.size();j++){
					Tubo* t = level.tubos[j];
					if(icolisionSuelo(b->vida->vx, b->vida->vy, 16, 16, t->x, t->y, level.tileSize, level.tileSize, b->vida->vspeed)){
					b->vida->landOn(t->y);
					}
					if(icolisionLateral(b->vida->vx, b->vida->vy, 16,16, t->x, t->y, level.tileSize, level.tileSize)){
					b->vida->changeDirection();	
					}
				}
			}

            if (b->flor && b->flor->factive && b->flor->canBeEaten && verifColisiones(player->x, player->y, player->wide, player->height, b->flor->fx, b->flor->fy, 16, 16)) {
                al_play_sample(sPowerup, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                b->flor->factive = false;
                player->powerup(3);
            }

            if (b->estrella && b->estrella->sactive && b->estrella->canBeEaten && verifColisiones(player->x, player->y, player->wide, player->height, b->estrella->sx, b->estrella->sy, 16, 16)) {
       			playSFXAndPauseMusic("star", level);
                b->estrella->sactive = false;
                player->powerup(4);
            }
             if(b->estrella && b->estrella->sactive){
            	b->estrella->songround = false;
            	float nextY = b->estrella->sy + b->estrella->sjumpspeed;
            	for(size_t j=0; j<level.grounds.size();j++){
				Ground* gr = level.grounds[j];
				if(icolisionSuelo(b->estrella->sx, b->estrella->sy, 16, 16, gr->x, gr->y, level.tileSize, level.tileSize, b->estrella->sspeed) || (b->estrella->sy + 16 < gr->y && nextY + 16 >= gr->y)){
					       b->estrella->landOn(gr->y);
				}
				if(icolisionLateral(b->estrella->sx, b->estrella->sy, 16,16, gr->x, gr->y, level.tileSize, level.tileSize)){
					b->estrella->changeDirection();	
				}
				}
				for(size_t j=0; j<level.bricks.size();j++){
				Brick* br = level.bricks[j];
				if(icolisionSuelo(b->estrella->sx, b->estrella->sy, 16, 16, br->bx, br->by, level.tileSize, level.tileSize, b->estrella->sspeed) ){
					b->estrella->landOn(br->by);
				}
				if(icolisionLateral(b->estrella->sx, b->estrella->sy, 16,16, br->bx, br->by, level.tileSize, level.tileSize)){
					b->estrella->changeDirection();	
				}
				}
				for(size_t j=0; j<level.interrogations.size();j++){
				Interrogation* it = level.interrogations[j];
				if(icolisionSuelo(b->estrella->sx, b->estrella->sy, 16, 16, it->ix, it->iy, level.tileSize, level.tileSize, b->estrella->sspeed)){
					b->estrella->landOn(it->iy);
				}
				if(icolisionLateral(b->estrella->sx, b->estrella->sy, 16,16, it->ix, it->iy, level.tileSize, level.tileSize)){
					b->estrella->changeDirection();	
				}
				}
				for(size_t j=0; j<level.gradas.size();j++){
					Grada* gra = level.gradas[j];
					if(icolisionSuelo(b->estrella->sx, b->estrella->sy, 16, 16, gra->x, gra->y, level.tileSize, level.tileSize, b->estrella->sspeed)){
					b->estrella->landOn(gra->y);
					}
					if(icolisionLateral(b->estrella->sx, b->estrella->sy, 16,16, gra->x, gra->y, level.tileSize, level.tileSize)){
					b->estrella->changeDirection();	
					}
				}
				for(size_t j=0; j<level.tubos.size();j++){
					Tubo* t = level.tubos[j];
					if(icolisionSuelo(b->estrella->sx, b->estrella->sy, 16, 16, t->x, t->y, level.tileSize, level.tileSize, b->estrella->sspeed)){
					b->estrella->landOn(t->y);
					}
					if(icolisionLateral(b->estrella->sx, b->estrella->sy, 16,16, t->x, t->y, level.tileSize, level.tileSize)){
					b->estrella->changeDirection();	
					}
				}
			}
		}
		for (size_t it = 0; it < level.bricks.size();) {
    		Brick* b = level.bricks[it];
    		if (b->readytoRemove()) {
        	delete b;
        	level.bricks.erase(level.bricks.begin() + it);
    	} else {
        	it++;
    	}
		}
		for (size_t i=0; i<level.lavas.size();i++){
			Lava* la = level.lavas[i];
			 if (verifColisiones(player->x, player->y, player->wide, player->height, la->x, la->y, level.tileSize, level.tileSize)){
			 	player->live = 1;
			 	player->damage();
			 	return;
			 }
		}
		for(size_t i=0; i<level.bbridges.size(); i++){
			Bbridge* bb = level.bbridges[i];
			if (colisionSuelo(player, bb->x, bb->y, 16, 16) && bb->active) {
        		player->y = bb->y - player->height;
       		 	player->vely = 0;
        		player->onGround = true;
    		}
    		for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, bb->x, bb->y, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = bb->y - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, bb->x, bb->y, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
    		for (size_t i=0; i<level.hachas.size(); i++){
			Hacha* hh = level.hachas[i];
			if(verifColisiones(player->x, player->y, player->wide, player->height, hh->x, hh->y, level.tileSize, level.tileSize)){
				bb->destroyed = true;
				player->saveToad = true;
        		playSFXAndPauseMusic("victoryCastle", level);
				for(size_t j=0; j<level.bowsers.size(); j++){
					Bowser* b = level.bowsers[j];
					al_play_sample(dying, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					b->dead = true;
				}	
			}
			}
		}
		for (size_t i=0; i<level.bridges.size(); i++){
				Bridge* bri = level.bridges[i];
				if (colisionSuelo(player, bri->x, bri->y, 16, 8)) {
        		player->y = bri->y - player->height;
       		 	player->vely = 0;
        		player->onGround = true;
    		}
    		for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, bri->x, bri->y, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = bri->y - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, bri->x, bri->y, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
		}
		for (size_t i = 0; i < level.interrogations.size(); i++) {
            Interrogation* in = level.interrogations[i];
            if (colisionSuelo(player, in->ix, in->iy, 16, 16)) {
        		player->y = in->iy - player->height;
        		player->vely = 0;
        		player->onGround = true;
    		}
    		if(colisionLateral(player, in->ix, in->iy, 16,16));
            if (verifColisiones(player->x, player->y, player->wide, player->height, in->ix, in->iy, 8, 16)) {
                if (player->vely < 0 && player->y > in->iy + 4) {
                	if(!in->iactive){
					if (canPlay(lastHitTime, 0.3)) {
        			al_play_sample(sNothing, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    				}
					}
                    in->iobject();
                    if (in->Case == 1){
                    if(!in->onlyOne){
        				player->tcoin++;
        				in->onlyOne = true;
					}
					}
                }
                if (player->vely < 0) {
                    player->y = in->iy + 16;
                    player->vely = 0;
                }
            }
            for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(icolisionSuelo(fb->x, fb->y, 8, 8, in->ix, in->iy, level.tileSize, level.tileSize, fb->speedy)){
				fb->y = in->iy - 8;
				fb->speedy = 0;
				fb->onGround = true;
			}
			if(icolisionLateral(fb->x, fb->y, 8,8, in->ix, in->iy, level.tileSize, level.tileSize)){
				fb->hit = true;	
			}
			}
            if (in->hongo && in->hongo->hactive && in->hongo->canBeEaten && verifColisiones(player->x, player->y, player->wide, player->height, in->hongo->hx, in->hongo->hy, 16, 16)) {
                al_play_sample(sPowerup, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                in->hongo->hactive = false;
                player->powerup(2);
            }
            if(in->hongo && in->hongo->hactive){
            	in->hongo->hjump = false;
            	for(size_t j=0; j<level.grounds.size();j++){
				Ground* gr = level.grounds[j];
				if(icolisionSuelo(in->hongo->hx, in->hongo->hy, 16, 16, gr->x, gr->y, level.tileSize, level.tileSize, in->hongo->vspeed)){
					in->hongo->landOn(gr->y);
				}
				if(icolisionLateral(in->hongo->hx, in->hongo->hy, 16,16, gr->x, gr->y, level.tileSize, level.tileSize)){
					in->hongo->changeDirection();	
				}
				}
				for(size_t j=0; j<level.bricks.size();j++){
				Brick* b = level.bricks[j];
				if(icolisionSuelo(in->hongo->hx, in->hongo->hy, 16, 16, b->bx, b->by, level.tileSize, level.tileSize, in->hongo->vspeed)){
					in->hongo->landOn(b->by);
				}
				if(icolisionLateral(in->hongo->hx, in->hongo->hy, 16,16, b->bx, b->by, level.tileSize, level.tileSize)){
					in->hongo->changeDirection();	
				}
				}
				for(size_t j=0; j<level.interrogations.size();j++){
				Interrogation* it = level.interrogations[j];
				if(icolisionSuelo(in->hongo->hx, in->hongo->hy, 16, 16, it->ix, it->iy, level.tileSize, level.tileSize, in->hongo->vspeed)){
					in->hongo->landOn(it->iy);
				}
				if(icolisionLateral(in->hongo->hx, in->hongo->hy, 16,16, it->ix, it->iy, level.tileSize, level.tileSize)){
					in->hongo->changeDirection();	
				}
				}
				for(size_t j=0; j<level.gradas.size();j++){
					Grada* gra = level.gradas[j];
					if(icolisionSuelo(in->hongo->hx, in->hongo->hy, 16, 16, gra->x, gra->y, level.tileSize, level.tileSize, in->hongo->vspeed)){
					in->hongo->landOn(gra->y);
					}
					if(icolisionLateral(in->hongo->hx, in->hongo->hy, 16,16, gra->x, gra->y, level.tileSize, level.tileSize)){
					in->hongo->changeDirection();	
					}
				}
				for(size_t j=0; j<level.tubos.size();j++){
					Tubo* t = level.tubos[j];
					if(icolisionSuelo(in->hongo->hx, in->hongo->hy, 16, 16, t->x, t->y, level.tileSize, level.tileSize, in->hongo->vspeed)){
					in->hongo->landOn(t->y);
					}
					if(icolisionLateral(in->hongo->hx, in->hongo->hy, 16,16, t->x, t->y, level.tileSize, level.tileSize)){
					in->hongo->changeDirection();	
					}
				}
			}
            if (in->vida && in->vida->vactive && in->vida->canBeEaten && verifColisiones(player->x, player->y, player->wide, player->height, in->vida->vx, in->vida->vy, 16, 16)) {
                al_play_sample(sExtralife, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                in->vida->vactive = false;
                player->lives++;
            }
                if(in->vida && in->vida->vactive){
            	in->vida->vjump = false;
            	for(size_t j=0; j<level.grounds.size();j++){
				Ground* gr = level.grounds[j];
				if(icolisionSuelo(in->vida->vx, in->vida->vy, 16, 16, gr->x, gr->y, level.tileSize, level.tileSize, in->vida->vspeed)){
					in->vida->landOn(gr->y);
				}
				if(icolisionLateral(in->vida->vx, in->vida->vy, 16,16, gr->x, gr->y, level.tileSize, level.tileSize)){
					in->vida->changeDirection();	
				}
				}
				for(size_t j=0; j<level.bricks.size();j++){
				Brick* b = level.bricks[j];
				if(icolisionSuelo(in->vida->vx, in->vida->vy, 16, 16, b->bx, b->by, level.tileSize, level.tileSize, in->vida->vspeed)){
					in->vida->landOn(b->by);
				}
				if(icolisionLateral(in->vida->vx, in->vida->vy, 16,16, b->bx, b->by, level.tileSize, level.tileSize)){
					in->vida->changeDirection();	
				}
				}
				for(size_t j=0; j<level.interrogations.size();j++){
				Interrogation* it = level.interrogations[j];
				if(icolisionSuelo(in->vida->vx, in->vida->vy, 16, 16, it->ix, it->iy, level.tileSize, level.tileSize, in->vida->vspeed)){
					in->vida->landOn(it->iy);
				}
				if(icolisionLateral(in->vida->vx, in->vida->vy, 16,16, it->ix, it->iy, level.tileSize, level.tileSize)){
					in->vida->changeDirection();	
				}
				}
				for(size_t j=0; j<level.gradas.size();j++){
					Grada* gra = level.gradas[j];
					if(icolisionSuelo(in->vida->vx, in->vida->vy, 16, 16, gra->x, gra->y, level.tileSize, level.tileSize, in->vida->vspeed)){
					in->vida->landOn(gra->y);
					}
					if(icolisionLateral(in->vida->vx, in->vida->vy, 16,16, gra->x, gra->y, level.tileSize, level.tileSize)){
					in->vida->changeDirection();	
					}
				}
				for(size_t j=0; j<level.tubos.size();j++){
					Tubo* t = level.tubos[j];
					if(icolisionSuelo(in->vida->vx, in->vida->vy, 16, 16, t->x, t->y, level.tileSize, level.tileSize, in->vida->vspeed)){
					in->vida->landOn(t->y);
					}
					if(icolisionLateral(in->vida->vx, in->vida->vy, 16,16, t->x, t->y, level.tileSize, level.tileSize)){
					in->vida->changeDirection();	
					}
				}
			}

            if (in->flor && in->flor->factive && in->flor->canBeEaten && verifColisiones(player->x, player->y, player->wide, player->height, in->flor->fx, in->flor->fy, 16, 16)) {
                al_play_sample(sPowerup, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                in->flor->factive = false;
                player->powerup(3);
            }

            if (in->estrella && in->estrella->sactive && in->estrella->canBeEaten && verifColisiones(player->x, player->y, player->wide, player->height, in->estrella->sx, in->estrella->sy, 16, 16)) {
        		playSFXAndPauseMusic("star", level);
                in->estrella->sactive = false;
                player->powerup(4);
            }
             if(in->estrella && in->estrella->sactive){
            	in->estrella->songround = false;
            	float nextY = in->estrella->sy + in->estrella->sjumpspeed;
            	for(size_t j=0; j<level.grounds.size();j++){
				Ground* gr = level.grounds[j];
				if(icolisionSuelo(in->estrella->sx, in->estrella->sy, 16, 16, gr->x, gr->y, level.tileSize, level.tileSize, in->estrella->sspeed) || (in->estrella->sy + 16 < gr->y && nextY + 16 >= gr->y)){
					       in->estrella->landOn(gr->y);
				}
				if(icolisionLateral(in->estrella->sx, in->estrella->sy, 16,16, gr->x, gr->y, level.tileSize, level.tileSize)){
					in->estrella->changeDirection();	
				}
				}
				for(size_t j=0; j<level.bricks.size();j++){
				Brick* b = level.bricks[j];
				if(icolisionSuelo(in->estrella->sx, in->estrella->sy, 16, 16, b->bx, b->by, level.tileSize, level.tileSize, in->estrella->sspeed) ){
					in->estrella->landOn(b->by);
				}
				if(icolisionLateral(in->estrella->sx, in->estrella->sy, 16,16, b->bx, b->by, level.tileSize, level.tileSize)){
					in->estrella->changeDirection();	
				}
				}
				for(size_t j=0; j<level.interrogations.size();j++){
				Interrogation* it = level.interrogations[j];
				if(icolisionSuelo(in->estrella->sx, in->estrella->sy, 16, 16, it->ix, it->iy, level.tileSize, level.tileSize, in->estrella->sspeed)){
					in->estrella->landOn(it->iy);
				}
				if(icolisionLateral(in->estrella->sx, in->estrella->sy, 16,16, it->ix, it->iy, level.tileSize, level.tileSize)){
					in->estrella->changeDirection();	
				}
				}
				for(size_t j=0; j<level.gradas.size();j++){
					Grada* gra = level.gradas[j];
					if(icolisionSuelo(in->estrella->sx, in->estrella->sy, 16, 16, gra->x, gra->y, level.tileSize, level.tileSize, in->estrella->sspeed)){
					in->estrella->landOn(gra->y);
					}
					if(icolisionLateral(in->estrella->sx, in->estrella->sy, 16,16, gra->x, gra->y, level.tileSize, level.tileSize)){
					in->estrella->changeDirection();	
					}
				}
				for(size_t j=0; j<level.tubos.size();j++){
					Tubo* t = level.tubos[j];
					if(icolisionSuelo(in->estrella->sx, in->estrella->sy, 16, 16, t->x, t->y, level.tileSize, level.tileSize, in->estrella->sspeed)){
					in->estrella->landOn(t->y);
					}
					if(icolisionLateral(in->estrella->sx, in->estrella->sy, 16,16, t->x, t->y, level.tileSize, level.tileSize)){
					in->estrella->changeDirection();	
					}
				}
			}
        }
        for (size_t i=0; i<level.koopas.size(); i++){
        	Koopa* k = level.koopas[i];
        	if (!k->kactive && !k->starKilled) {
        	if (fabs(player->x - k->kx) <= ENEMY_ACTIVATE_DIST) k->kactive = true;
        	else continue;
    		}
    		k->konground = false;
        	for (size_t j = 0; j < level.grounds.size(); j++) {
        		Ground* gr = level.grounds[j];
        	if (k->kactive && icolisionSuelo(k->kx, k->ky, 16, k->klimit, gr->x, gr->y, level.tileSize, level.tileSize, k->gravity)) {
            k->ky = gr->y - k->klimit;
            k->gravity = 1;
            k->konground = true;
        	}
        	if(k->kactive && icolisionLateral(k->kx, k->ky, 16, k->klimit, gr->x, gr->y, level.tileSize, level.tileSize)){
        		if(k->kdir == 1){
        			k->kdir = 0;
				}else if(k->kdir == 0){
					k->kdir = 1;
				}
			}
    	}
    	for (size_t j = 0; j < level.bricks.size(); j++) {
        	Brick* b = level.bricks[j];
        	if (k->kactive && icolisionSuelo(k->kx, k->ky, 16, k->klimit, b->bx, b->by, level.tileSize, level.tileSize, k->gravity)) {
            k->ky = b->by - k->klimit;
            k->gravity = 1;
            k->konground = true;
        	}
        	if(k->kactive && icolisionLateral(k->kx, k->ky, 16, k->klimit, b->bx, b->by, level.tileSize, level.tileSize)){
        		if(k->kdir == 1){
        			k->kdir = 0;
				}else if(k->kdir == 0){
					k->kdir = 1;
				}
			}
    	}
    	for (size_t j = 0; j < level.interrogations.size(); j++) {
        		Interrogation* in = level.interrogations[j];
        	if (k->kactive && icolisionSuelo(k->kx, k->ky, 16, k->klimit, in->ix, in->iy, level.tileSize, level.tileSize, k->gravity)) {
            k->ky = in->iy - k->klimit;
            k->gravity = 1;
            k->konground = true;
        	}
        	if(k->kactive && icolisionLateral(k->kx, k->ky, 16, k->klimit, in->ix, in->iy, level.tileSize, level.tileSize)){
        		if(k->kdir == 1){
        			k->kdir = 0;
				}else if(k->kdir == 0){
					k->kdir = 1;
				}
			}
    	}
    	for (size_t j = 0; j < level.gradas.size(); j++) {
        		Grada* gra = level.gradas[j];
        	if (k->kactive && icolisionSuelo(k->kx, k->ky, 16, k->klimit, gra->x, gra->y, level.tileSize, level.tileSize, k->gravity)) {
            k->ky = gra->y - k->klimit;
            k->gravity = 1;
            k->konground = true;
        	}
  			colisionLateralKoopa(k, gra->x, gra->y, level.tileSize, level.tileSize);
    	}
    	for (size_t j = 0; j < level.tubos.size(); j++) {
        Tubo* t = level.tubos[j];
        	if (k->kactive && icolisionSuelo(k->kx, k->ky, 16, k->klimit, t->x, t->y, level.tileSize, level.tileSize, k->gravity)) {
            k->ky = t->y - k->klimit;
            k->gravity = 1;
            k->konground = true;
        	}
        	colisionLateralKoopa(k, t->x, t->y, level.tileSize, level.tileSize);
    	}
    	for (size_t i = 0; i < level.plats.size(); i++) {
        Plat* pl = level.plats[i];
        if (k->kactive && icolisionSuelo(k->kx, k->ky, 16, k->klimit, pl->x, pl->y, level.tileSize, level.tileSize, k->gravity) && pl->tipo == 1) {
            k->ky = pl->y - k->klimit;
            k->gravity = 1;
            k->konground = true;
    		}
    	}
 	if (k->type == 2 && k->konground && !k->inShell) {
    float checkX = (k->kdir == 0 ? k->kx + 16 : k->kx - 1);
    float checkY = k->ky + k->klimit + 1;
    if (!isGroundAhead(checkX, checkY, level)) {
        k->kdir = 1 - k->kdir;
    }
	}
    	if(k->kactive && verifColisiones(player->x,player->y,player->wide,player->height,k->kx,k->ky,16,k->klimit)){
		float playerBottom = player->y + player->height;
    	float koopaTop = k->ky;
    	if (player->starPower){
        if (canPlay(lastHitTime, 0.2)) {
            al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        }
        k->starHit();
    	}
    	else if (playerBottom <= koopaTop + 12) {
        if (canPlay(lastStompTime, 0.15)) {
            al_play_sample(sStomp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        }
        k->stomp(player->dir);
        player->vely = -6;
   	 	}
    	else {
    	if (k->shellMoving && k->safeTimer <= 0){
            player->damage();
        }
        else if (k->inShell && !k->shellMoving){
            if (canPlay(lastHitTime, 0.3)) al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            k->stomp(player->dir);
        }
        else if (k->safeTimer > 0){
        	//Protección para Mario o Luigi
        }
        else{
            player->damage();
        }
    	}
		}
		for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(k->kactive && verifColisiones(fb->x, fb->y, 8, 8, k->kx, k->ky, 16, k->klimit)){
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		k->starHit();
        		fb->hit = true;
			}
			}
	}
        for (size_t i=0; i<level.goombas.size();i++){
        	Goomba* g = level.goombas[i];
        	float gox = g->gx;
    		float goy = g->gy;
    		float gow = 16;
    		float goh = 16;
    		if (!g->gactive && !g->squashed && !g->starKilled) {
        	if (fabs(player->x - g->gx) <= ENEMY_ACTIVATE_DIST) g->gactive = true;
        	else continue;
    		}
    		g->gonground = false;
    		    for (size_t j = 0; j < level.grounds.size(); j++) {
        			Ground* gr = level.grounds[j];
        			float gx = gr->x;
        			float gy = gr->y;
        			float gw = level.tileSize;
        			float gh = level.tileSize;
        		if (g->gx + gow > gx && g->gx < gx + gw && g->gy + goh <= gy + g->gravity && g->gy + goh + g->gravity >= gy) {
            		g->gy = gy - goh;
            		g->gravity = 1;
            		g->gonground = true;
        		}
    			}
    			for (size_t j = 0; j < level.bricks.size(); j++) {
        			Brick* b = level.bricks[j];
        			float bx = b->bx;
        			float by = b->by;
        			float bw = level.tileSize;
        			float bh = level.tileSize;
        		if (g->gx + gow > bx && g->gx < bx + bw && g->gy + goh <= by + g->gravity && g->gy + goh + g->gravity >= by) {
            		g->gy = by - goh;
            		g->gravity = 1;
            		g->gonground = true;
        		}
        		if (verifColisiones(g->gx, g->gy, gow, goh, b->bx, b->by, bw, bh)) {
       		 	if (g->gx + gow > b->bx && g->gx < b->bx && g->dir == 0) {
            	g->gx = b->bx - gow;
            	g->dir = 1;
        		}
        		else if (g->gx < b->bx + bw && g->gx + gow > b->bx + bw && g->dir == 1) {
            	g->gx = b->bx + bw;
            	g->dir = 0;
        		}
				}
    			}
    			for (size_t i = 0; i < level.plats.size(); i++) {
        				Plat* pl = level.plats[i];
        			if (g->gactive && icolisionSuelo(g->gx, g->gy, 16, 16, pl->x, pl->y, level.tileSize, level.tileSize, g->gravity) && pl->tipo == 1) {
            		g->gy = pl->y - 16;
            		g->gravity = 1;
            		g->gonground = true;
    				}
    			}
    			for (size_t j = 0; j < level.gradas.size(); j++) {
        			Grada* gra = level.gradas[j];
        			float grax = gra->x;
        			float gray = gra->y;
        			float graw = level.tileSize;
        			float grah = level.tileSize;
        		if (g->gx + gow > grax && g->gx < grax + graw && g->gy + goh <= gray + g->gravity && g->gy + goh + g->gravity >= gray) {
            		g->gy = gray - goh;
            		g->gravity = 1;
            		g->gonground = true;
        		}
        		if (verifColisiones(g->gx, g->gy, gow, goh, gra->x, gra->y, graw, grah)) {
       		 	if (g->gx + gow > gra->x && g->gx < gra->x && g->dir == 0) {
            	g->gx = gra->x - gow;
            	g->dir = 1;
        		}
        		else if (g->gx < gra->x + graw && g->gx + gow > gra->x + graw && g->dir == 1) {
            	g->gx = gra->x + graw;
            	g->dir = 0;
        		}
    			}
				}
    		    for (size_t q = 0; q < level.tubos.size(); q++) {
 				Tubo* t = level.tubos[q];
    			float tw = 16, th = 16;
    			if (verifColisiones(g->gx, g->gy, gow, goh, t->x, t->y, tw, th)) {
       		 	if (g->gx + gow > t->x && g->gx < t->x && g->dir == 0) {
            	g->gx = t->x - gow;
            	g->dir = 1;
        		}
        		else if (g->gx < t->x + tw && g->gx + gow > t->x + tw && g->dir == 1) {
            	g->gx = t->x + tw;
            	g->dir = 0;
        		}
    			}
    		}
    		for (size_t i =0; i<level.bridges.size(); i++){
    			Bridge* bri = level.bridges[i];
    			if (g->gactive && icolisionSuelo(g->gx, g->gy, 16, 16, bri->x, bri->y, level.tileSize, level.tileSize, g->gravity)) {
            		g->gy = bri->y - 16;
            		g->gravity = 1;
            		g->gonground = true;
    			}
			}
    		if(g->gactive && verifColisiones(player->x,player->y,player->wide,player->height,gox,goy,gow,goh)){
			float playerBottom = player->y + player->height;
			float playerBottomPrev = player->yPrev + player->height;
    		float goombaTop = g->gy;
			if (player->starPower) {
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		g->starHit();
    		}else if((playerBottomPrev <= goombaTop && playerBottom >= goombaTop)){
				al_play_sample(sStomp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        		g->stomp();
        		player->vely = -6;	
			}else if(player->onGround){
			if(!g->starKilled){
				player->damage();   
			}
			}
			}
			for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(g->gactive && verifColisiones(fb->x, fb->y, 8, 8, gox, goy, 16, 16)){
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		g->starHit();
        		fb->hit = true;
			}
			}
		for(size_t j=0; j<level.koopas.size();j++){
			Koopa* k = level.koopas[j];
			if(g->gactive && k->shellMoving && verifColisiones(g->gx,g->gy,16,16,k->kx,k->ky,16,16)){
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
				g->starHit();
			}
		}
		}
		for(size_t i=0; i<level.pplants.size();i++){
			PPlant* pp = level.pplants[i];
			if (!pp->active && pp->alive) {
        	if (fabs(player->x - pp->x) <= ENEMY_ACTIVATE_DIST) pp->active = true;
        	else continue;
    		}
    		if(pp->active && verifColisiones(player->x,player->y,player->wide,player->height,pp->x,pp->y,16,24)){
    			if (player->starPower) {
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		pp->active = false;
        		pp->alive = false;
    			}else{
    				player->damage();
				}
    			
			}
			for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(pp->active && verifColisiones(fb->x, fb->y, 8, 8, pp->x, pp->y, 16, 24)){
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		pp->active = false;
        		pp->alive = false;
        		fb->hit = true;
			}
			}
			
		}
		for(size_t i=0; i<level.bowsers.size(); i++){
			Bowser* bow = level.bowsers[i];
			bow->onGround = false;
			for(size_t j=0; j<level.bbridges.size(); j++){
				Bbridge* bb = level.bbridges[j];
				if (bow->active && icolisionSuelo(bow->x, bow->y, 32, 35, bb->x, bb->y, level.tileSize, level.tileSize, bow->speedy) && bb->active) {
            		bow->y = bb->y - 35;
           	 		bow->speedy = 0;
            		bow->onGround = true; 
    			}
			}
			if(verifColisiones(player->x, player->y, player->wide, player->height, bow->x, bow->y, 32, 35)){
				player->damage();
			}
			colisionLateral(player, bow->x, bow->y, 32, 35);
			for(size_t z=0; z<bow->llamas.size(); z++){
				Llama* ll = bow->llamas[z];
				if(verifColisiones(player->x, player->y, player->wide, player->height, ll->x, ll->y, 24, 12)){
				player->damage();
				}
			}
		}
		for(size_t i=0; i<level.hammerbros.size(); i++){
			HammerBros* hb = level.hammerbros[i];
			if (fabs(player->x - hb->x) <= ENEMY_ACTIVATE_DIST) hb->active = true;
        	else continue;
			hb->onGround = false;
			if(hb->active && verifColisiones(player->x,player->y,player->wide,player->height,hb->x,hb->y,16,23)){
			float playerBottom = player->y + player->height;
			float playerBottomPrev = player->yPrev + player->height;
    		float hammerTop = hb->y;
			if (player->starPower) {
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		hb->starHit();
    		}else if((playerBottomPrev <= hammerTop && playerBottom >= hammerTop)){
				al_play_sample(sStomp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        		hb->starHit();
        		player->vely = -6;	
			}else if(player->onGround){
			if(!hb->starKilled){
				player->damage();   
			}
			}
			}
			for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(hb->active && verifColisiones(fb->x, fb->y, 8, 8, hb->x, hb->y, 16, 23)){
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		hb->starHit();
        		fb->hit = true;
			}
			}
			for(size_t j=0; j<level.grounds.size(); j++){
				Ground* gr = level.grounds[j];
				if (hb->active && icolisionSuelo(hb->x, hb->y, 16, 24, gr->x, gr->y, level.tileSize, level.tileSize, hb->vy)) {
            		if(hb->throwingnow){
            		hb->y = gr->y - 36;
					}else{
						hb->y = gr->y - 24;
					}
           	 		hb->vy = 0;
            		hb->onGround = true; 
    		}
		}
		for (size_t z = 0; z < level.gradas.size(); z++) {
        			Grada* g = level.gradas[z];
        		if (hb->active && icolisionSuelo(hb->x, hb->y, 16, 24, g->x, g->y, level.tileSize, level.tileSize, hb->vy)) {
            		if(hb->throwingnow){
            		hb->y = g->y - 35;
					}else{
						hb->y = g->y - 24;
					}
           	 		hb->vy = 0;
            		hb->onGround = true; 
    		}		
    	}
    	for (size_t z = 0; z < level.interrogations.size(); z++) {
        			Interrogation* in = level.interrogations[z];
        		if (hb->active && icolisionSuelo(hb->x, hb->y, 16, 24, in->ix, in->iy, level.tileSize, level.tileSize, hb->vy)) {
            		if(hb->throwingnow){
            		hb->y = in->iy - 37;
					}else{
						hb->y = in->iy - 24;
					}
           	 		hb->vy = 0;
            		hb->onGround = true; 
    		}		
    	}
    	for (size_t z = 0; z < level.tubos.size(); z++) {
        			Tubo* t = level.tubos[z];
        		if (hb->active && icolisionSuelo(hb->x, hb->y, 16, 24, t->x, t->y, level.tileSize, level.tileSize, hb->vy)) {
            		if(hb->throwingnow){
            		hb->y = t->y - 37;
					}else{
						hb->y = t->y - 24;
					}
           	 		hb->vy = 0;
            		hb->onGround = true; 
    		}		
    	}
    	for(size_t a=0; a<hb->hammers.size(); a++){
				Hammer* hm = hb->hammers[a];
				if(verifColisiones(player->x, player->y, player->wide, player->height, hm->x, hm->y, 10, 16) && !player->invincible){
				player->damage();
				}
			}
	}
	for(size_t i=0; i<level.lavaburbles.size(); i++){
		LavaBurble* lb = level.lavaburbles[i];
	    float dx = fabs(player->x - lb->x);
    	float dy = fabs(player->y - lb->y);
    	if(dx <= ENEMY_ACTIVATE_DIST && dy <= 300){
        lb->active = true;
    	}
    	else if(dx >= ENEMY_ACTIVATE_DIST + 80 || dy >= 450){
        lb->active = false;
    	}
		if(verifColisiones(player->x, player->y, player->wide, player->height, lb->x, lb->y, 14, 16) && !player->invincible){
			player->damage();
		}
	}
	for(size_t i=0; i<level.lakitus.size(); i++){
		Lakitu* lak = level.lakitus[i];
		if (fabs(player->x - lak->x) <= ENEMY_ACTIVATE_DIST) lak->active = true;
        else continue;
        if(player->endanim || player->automov || player->cclear){
        	lak->active = false;
		}
        if(lak->active && verifColisiones(player->x,player->y,player->wide,player->height,lak->x,lak->y,16,23)){
			float playerBottom = player->y + player->height;
			float playerBottomPrev = player->yPrev + player->height;
    		float lakituTop = lak->y;
			if (player->starPower) {
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		lak->starHit();
    		}else if((playerBottomPrev <= lakituTop && playerBottom >= lakituTop)){
				al_play_sample(sStomp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        		lak->starHit();
        		player->vely = -6;	
			}else{
			if(!lak->starKilled){
				player->damage();   
			}
			}
			}
		for (size_t a=0; a<lak->spinies.size();a++){
			Spinie* spi = lak->spinies[a];
			spi->onGround = false;
			if(verifColisiones(player->x, player->y, player->wide, player->height, spi->x, spi->y, 16, 13) && !player->invincible){
				player->damage();
			}
			for(size_t j=0; j<level.grounds.size(); j++){
				Ground* gr = level.grounds[j];
				if (spi->active && icolisionSuelo(spi->x, spi->y, 16, 16, gr->x, gr->y, level.tileSize, level.tileSize, spi->vy)) {
					spi->y = gr->y - 16;
           	 		spi->vy = 0;
            		spi->onGround = true; 
            		spi->wasBefore = true;
    		}
    		if(icolisionLateral(spi->x, spi->y, 16,16, gr->x, gr->y, level.tileSize, level.tileSize)){
					spi->direc*=-1 ;	
			}
			}
			for(size_t j=0; j<level.gradas.size(); j++){
				Grada* g = level.gradas[j];
				if (spi->active && icolisionSuelo(spi->x, spi->y, 16, 16, g->x, g->y, level.tileSize, level.tileSize, spi->vy)) {
					spi->y = g->y - 16;
           	 		spi->vy = 0;
            		spi->onGround = true; 
            		spi->wasBefore = true;
    		}
    			if(icolisionLateral(spi->x, spi->y, 16,16, g->x, g->y, level.tileSize, level.tileSize)){
				spi->direc*=-1 ;	
			}
			}
			for(size_t j=0; j<level.tubos.size(); j++){
				Tubo* t = level.tubos[j];
				if (spi->active && icolisionSuelo(spi->x, spi->y, 16, 16, t->x, t->y, level.tileSize, level.tileSize, spi->vy)) {
					spi->y = t->y - 16;
           	 		spi->vy = 0;
            		spi->onGround = true; 
            		spi->wasBefore = true;
    		}
    		if(icolisionLateral(spi->x, spi->y, 16,16, t->x, t->y, level.tileSize, level.tileSize)){
				spi->direc*=-1 ;	
			}
			}
			for(size_t j=0; j<level.bricks.size(); j++){
				Brick* b = level.bricks[j];
				if (spi->active && icolisionSuelo(spi->x, spi->y, 16, 16, b->bx, b->by, level.tileSize, level.tileSize, spi->vy)) {
					spi->y = b->by - 16;
           	 		spi->vy = 0;
            		spi->onGround = true; 
            		spi->wasBefore = true;
    		}
    		if(icolisionLateral(spi->x, spi->y, 16,16, b->bx, b->by, level.tileSize, level.tileSize)){
				spi->direc*=-1 ;	
			}
			}
			for(size_t j=0; j<level.interrogations.size(); j++){
				Interrogation* in = level.interrogations[j];
				if (spi->active && icolisionSuelo(spi->x, spi->y, 16, 16, in->ix, in->iy, level.tileSize, level.tileSize, spi->vy)) {
					spi->y = in->iy - 16;
           	 		spi->vy = 0;
            		spi->onGround = true; 
            		spi->wasBefore = true;
    		}
    		if(icolisionLateral(spi->x, spi->y, 16,16, in->ix, in->iy, level.tileSize, level.tileSize)){
				spi->direc*=-1 ;	
			}
			}
		}
		for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
    		if(lak->active && verifColisiones(fb->x, fb->y, 8, 8, lak->x, lak->y, 16, 23)){
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		lak->starHit();
        		fb->hit = true;
			}
			}
	}
		for(size_t i=0; i<level.platforms.size();i++){
			Platform* p = level.platforms[i];
			if(colisionSuelo(player, p->x, p->y, 48, 5)){
    			player->y = p->y - player->height;
        		player->vely = 0;
        		player->onGround = true;
			}
		}
        for(size_t i=0; i<level.flags.size(); i++){
        	Flag* f = level.flags[i];
        	if(verifColisiones(player->x, player->y, player->wide, player->height, f->x, f->y, 5, 152) && player->comp == 0){
        		player->cclear = true;
        		if (canPlay(lastHitTime, 6.5) && player->cclear) {
        			playSFXAndPauseMusic("victory", level);
    			}
        		f->clear = true;
        		if(player->live>1){
        			player->flagY = f->y + 128;
				}else{
					player->flagY = f->y + 136;
				}
        		player->x = f->x - player->wide + 18;	
			}
		}
		for(size_t i=0; i<level.castillos.size(); i++){
			Castle* c = level.castillos[i];
			player->castleX = c->x + c->wide/2;
		}
		for(size_t i=0; i<level.coins.size(); i++){
			Coin* co = level.coins[i];
			if(verifColisiones(player->x, player->y, player->wide, player->height, co->cx, co->cy, 10, 14)){
				if(co->cactive){
				al_play_sample(sCoin, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            	co->cactive = false;
            	player->tcoin++;	
				}
			}
		}
		for (size_t i = 0; i < level.cheeps.size(); i++) {
    	Cheep* che = level.cheeps[i];
    	if (!che->active) {
        if (fabs(player->x - che->x) <= ENEMY_ACTIVATE_DIST)
            che->active = true;
        else
            continue;
    	}
    	if (verifColisiones(player->x, player->y, player->wide, player->height,che->x, che->y, 16, 16)){
        if (che->type == 3){
            float playerBottom     = player->y + player->height;
            float playerBottomPrev = player->yPrev + player->height;
            float cheepTop         = che->y;
            if (playerBottomPrev <= cheepTop && playerBottom >= cheepTop)
            {
                al_play_sample(sStomp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                che->stomp();
                player->vely = -6;
            }
            else
            {
            	if(!che->stomped){
            		 player->damage();
				}
            }
        }
    	}
    	for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
  	    	if(che->active && verifColisiones(fb->x, fb->y, 8, 8, che->x, che->y, 16, 16)){
			if (canPlay(lastHitTime, 0.2)) {
        	al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    		}
        	che->stomp();
        	fb->hit = true;
			}
			}
		}
		for(size_t i=0; i<level.bloopers.size(); i++){
			Blooper* bloo = level.bloopers[i];
			if(!bloo->active){
				if (fabs(player->x - bloo->x) <= ENEMY_ACTIVATE_DIST) bloo->active = true;
        		else continue;
			}
				if(verifColisiones(player->x, player->y, player->wide, player->height, bloo->x, bloo->y, 16, bloo->bLimit) && !bloo->starKilled){
				player->damage();
			}
			for(size_t i=0; i<player->fireballs.size(); i++){
    		Fireball* fb = player->fireballs[i];
  	    	if(bloo->active && verifColisiones(fb->x, fb->y, 8, 8, bloo->x, bloo->y, 16, 16)){
			if (canPlay(lastHitTime, 0.2)) {
        	al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    		}
        	bloo->starHit();
        	fb->hit = true;
			}
			}
		}
		for(size_t i=0; i<level.bulletbills.size(); i++){
    		BulletBill* bbi = level.bulletbills[i];
    		if(!bbi->active){
				if (fabs(player->x - bbi->x) <= ENEMY_ACTIVATE_DIST) bbi->active = true;
        		else continue;
			}
    		if(bbi->active && verifColisiones(player->x,player->y,player->wide,player->height,bbi->x,bbi->y,16,14)){
			float playerBottom = player->y + player->height;
			float playerBottomPrev = player->yPrev + player->height;
    		float bulletTop = bbi->y;
			if (player->starPower){
				if (canPlay(lastHitTime, 0.2)) {
        		al_play_sample(soHit, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    			}
        		bbi->starHit();
    		}else if((playerBottomPrev <= bulletTop && playerBottom >= bulletTop)){
				al_play_sample(sStomp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        		bbi->starHit();
        		player->vely = -6;	
			}else if(!bbi->starKilled){
				player->damage();   
			}
			}
		}
		for(size_t i=0; i<level.toads.size(); i++){
			Toad* t = level.toads[i];
				if (fabs(player->x - t->x) <= ENEMY_ACTIVATE_DIST) t->anim = true;
        		else continue;
			player->castleX = t->x-10;
		}
		}
void checkWarp(LevelLoader &level, Player *player, Player *luigi) {
    if (isFading || player->warp || player->exitWarp || player->dead) return;
    for (size_t i = 0; i < level.warps.size(); i++) {
        Warp &w = level.warps[i];
        if (w.type == WARP_DOWN && verifColisiones(player->x, player->y, player->wide, player->height, w.x+14, w.y, 2, 2) && player->down && player->onGround) {
            for (size_t j = 0; j < level.warps.size(); j++) {
                if (level.warps[j].id == w.id &&
                    level.warps[j].exitAssigned &&
                    level.warps[j].exitType == EXIT_DOWN) {
                    warpTargetX = level.warps[j].ex;
                    warpTargetY = level.warps[j].ey;
                    player->warp = true;
                     if (luigi && !luigi->dead) {
                        luigi->warp = true;
                        luigi->velx = 0;
                        luigi->vely = 0;
                    }
                    fadeAlpha = 0.0f;
                    fadeSpeed = 0.04f;
                    fadeIn = true;
                    isFading = true;
                    al_play_sample(sWarp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    return;
                }
            }
        }
        if (w.type == WARP_RIGHT && verifColisiones(player->x, player->y, player->wide, player->height, w.x+14, w.y, 2, 2)){
            for (size_t j = 0; j < level.warps.size(); j++) {
                if (level.warps[j].id == w.id &&
                    level.warps[j].exitAssigned &&
                    level.warps[j].exitType == EXIT_RIGHT) {
                    warpTargetX = level.warps[j].ex;
                    warpTargetY = level.warps[j].ey;
                    player->warp = true;
                     if (luigi && !luigi->dead) {
                        luigi->warp = true;
                        luigi->velx = 0;
                        luigi->vely = 0;
                    }
                    fadeAlpha = 0.0f;
                    fadeSpeed = 0.04f;
                    fadeIn = true;
                    isFading = true;
                    al_play_sample(sWarp, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    return;
                }
            }
        }
    }
}
	private:
		bool verifColisiones(float x1, float y1, float w1, float h1,float x2, float y2, float w2, float h2) {
        return (x1 < x2 + w2 && x1 + w1 > x2 &&
                y1 < y2 + h2 && y1 + h1 > y2);
    	}
    	bool canPlay(double &lastTime, double delay) {
    	double now = al_get_time();
    	if (now - lastTime >= delay) {
        lastTime = now;
        return true;
    	}
   		return false;	
	   }
	   bool colisionSuelo(Player* p, float bx, float by, float bw, float bh){
	   	return (p->x + p->wide > bx && p->x < bx + bw && p->y + p->height <= by + p->vely && p->y + p->height + p->vely >= by);
	   }
	   bool colisionLateral(Player* player, float bx, float by, int bwidth, int bheight) {
    	if (player->x + player->wide > bx && player->x < bx + bwidth &&
        player->y + player->height > by && player->y < by + bheight) {
        float overlapXRight = (player->x + player->wide) - bx;       
        float overlapXLeft  = (bx + bwidth) - player->x;              
        float overlapYDown  = (player->y + player->height) - by;      
        float overlapYUp    = (by + bheight) - player->y; 
        if (std::min(overlapXRight, overlapXLeft) < std::min(overlapYDown, overlapYUp)) {
            if (overlapXRight < overlapXLeft) {
                player->x = bx - player->wide;
            } else {
                player->x = bx + bwidth;
            }
            player->velx = 0;
            return true;
        }
        else {
            return false;
        }
    }
    return false;
	}
	bool icolisionSuelo(float x, float y, float w, float h, float bx, float by, float bw, float bh, float vely) {
    return (x + w > bx && x < bx + bw && y + h <= by + vely && y + h + vely >= by);
	}
	bool icolisionLateral(float x, float y, float w, float h,float bx, float by, float bw, float bh) {
    bool overlapX = (x + w > bx) && (x < bx + bw);
    bool overlapY = (y + h > by) && (y < by + bh);
    if (overlapX && overlapY) {
        return true;
    }
    return false;
	}
	bool isGroundAhead(float x, float y, LevelLoader &level) {
    for (size_t i = 0; i < level.grounds.size(); i++) {
        Ground* g = level.grounds[i];
        if (x >= g->x && x < g->x + level.tileSize &&
            y >= g->y && y < g->y + level.tileSize) {
            return true;
        }
    }
    for (size_t i = 0; i < level.plats.size(); i++) {
        Plat* pl = level.plats[i];
		if (x >= pl->x && x < pl->x + level.tileSize &&
            y >= pl->y && y < pl->y + level.tileSize) {
            return true;
        }
    }
    return false;
	}
	bool colisionLateralKoopa(Koopa* k, float bx, float by, int bwidth, int bheight) {
    float kwidth = 16;
    float kheight = k->klimit;
    if (k->kx + kwidth > bx && k->kx < bx + bwidth && k->ky + kheight > by && k->ky < by + bheight) {
        float overlapXRight = (k->kx + kwidth) - bx;
        float overlapXLeft  = (bx + bwidth) - k->kx;
        float overlapYDown  = (k->ky + kheight) - by;
        float overlapYUp    = (by + bheight) - k->ky;
        if (std::min(overlapXRight, overlapXLeft) < std::min(overlapYDown, overlapYUp)) {
            if (overlapXRight < overlapXLeft) {
                k->kx = bx - kwidth;
                k->kdir = 1;
            } else {
                k->kx = bx + bwidth;
                k->kdir = 0;
            }
            return true;
        }
        else {
            return false;
        }
    }
    return false;
	}
};
