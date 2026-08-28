#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "Player.h"
#include "Hongo.h"
#include "VidaExtra.h"
#include "Flor.h"
#include "Star.h"
#include "LevelLoader.h"
#include "GameManager.h"
#include "Hud.h"
#include "Menu.h"
#include "GameOver.h"
#include "Winner2P.h"
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
enum GameState { MENU, PREVIEW, PLAY, PLAY_2P, PREVIEW_2P, FADE_OUT, GAMEOVER, FINAL_2P};
struct PlayerState {
    int lives;
    int tcoin;
    int powerup;  
};
PlayerControls marioControls = {
    ALLEGRO_KEY_LEFT,
    ALLEGRO_KEY_RIGHT,
    ALLEGRO_KEY_DOWN,
    ALLEGRO_KEY_M,
    ALLEGRO_KEY_N
};
PlayerControls luigiControls = {
    ALLEGRO_KEY_A,
    ALLEGRO_KEY_D,
    ALLEGRO_KEY_S,
    ALLEGRO_KEY_V,
    ALLEGRO_KEY_C
};
int main() {
    al_init();
    al_install_audio();
    al_init_acodec_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_reserve_samples(5);
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    srand(time(NULL));
    float FPS = 60;
    int ScreenWidth = 800, ScreenHeight = 600;
    int BaseWidth = 256;
    int BaseHeight = 240;
    int hudTimer = 300;
    bool fullscreen = true;
    if(fullscreen) al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    ALLEGRO_DISPLAY* display = al_create_display(ScreenWidth, ScreenHeight);
    ScreenWidth = al_get_display_width(display);
    ScreenHeight = al_get_display_height(display);
    al_set_window_position(display,0,0);
    ALLEGRO_TIMER* timer = al_create_timer(1.0/FPS);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    al_start_timer(timer);
    double lastTime = al_get_time();
    double deltaTime = 0;
    std::vector<int> levelsToPlay = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
    std::vector<int> levelsToPlay2P;
	std::vector<int> allLevels;
	for (int i = 1; i <= 32; i++) allLevels.push_back(i);
	std::random_shuffle(allLevels.begin(), allLevels.end());
	for (int i = 0; i < 4; i++) levelsToPlay2P.push_back(allLevels[i]);
    Hud hud("m", 300);
    hud.loadFont();
    hud.cHudassets();
    Menu menu(0,0);
    GameOver gameover(0,0);
    Winner2P winner2p(0,0);
    menu.menassets();
    gameover.goassets();
    winner2p.cwassets();
    std::vector<Player*> players;
    ALLEGRO_BITMAP* gameBuffer = al_create_bitmap(BaseWidth, BaseHeight);
    float scaleX = (float)ScreenWidth / (float)BaseWidth;
    float scaleY = (float)ScreenHeight / (float)BaseHeight;
    float finalScale = std::min(scaleX, scaleY);
    bool done = false;
    const float PREVIEW_SECONDS = 3.0f;     
    const float FADE_SECONDS = 1.0f;        
    GameState state = MENU;
    int currentLevelIndex = 0;
    int currentLevelIndex2P = 0; 
    int marioWins = 0;
	int luigiWins = 0;
	bool levelEnded = false;   
    float stateTimer = 0.0f;     
    float fadeAlpha = 0.0f;
	double hudElapsedTime = 0;
	float deathTimer2P = 0.0f;
	const float DEATH_DELAY = 1.5f;
	ALLEGRO_SAMPLE* letsgo = al_load_sample("Sounds/letsgo.wav");
	ALLEGRO_SAMPLE* goagain = al_load_sample("Sounds/goagain.wav");
	ALLEGRO_SAMPLE* battlemode = al_load_sample("Sounds/Battlemode.wav");      
    LevelLoader level;
    Player* mario = NULL;
    Player* luigi = NULL;
    GameManager* gm = NULL;
    auto loadLevelAndPlayer = [&](int levelId, bool preserveState, bool isdead) {
    	PlayerState savedState;
    	if (mario && preserveState) {
        savedState.lives = mario->lives;
        savedState.tcoin = mario->tcoin;
        savedState.powerup = mario->live;
    	}
    	if(mario && isdead){
    		savedState.lives = mario->lives;
		}
        level.destroy();
        level = LevelLoader(16); 
        level.loadFullLevel(levelId);
        level.detectWarpSections();
        level.assignWarpExits(levelId);
        gameover.cont = false;
        gameover.gomenu = false;
        if (mario) { delete mario; mario = NULL; }
        mario = new Player(level.inPosX, level.inPosY, "m", marioControls);
        mario->crearAssets("m");
        if (preserveState && savedState.lives > 0) {
        mario->lives = savedState.lives;
        mario->tcoin = savedState.tcoin;
        mario->live = savedState.powerup;
		mario->setPower(mario->live);
		if(mario->live>=2){
			mario->y-=16;
		}
    	}
    	if(isdead){
    		mario->lives = savedState.lives;
		}
        level.player = mario;
        mario->vely = 0;
        mario->onGround = true;
        if (gm) { delete gm; gm = NULL; }
        gm = new GameManager();
        gm->currentSection = level.getSection(mario->y);
        std::stringstream ss; ss << levelId;
        hud.loadLevelPreview(ss.str());
        stateTimer = PREVIEW_SECONDS;
        fadeAlpha = 0.0f;
        state = PREVIEW;
    };
    auto loadLevel2P = [&](int levelId) {
    level.destroy();
    level = LevelLoader(16);
    level.loadFullLevel(levelId);
    level.detectWarpSections();
    level.assignWarpExits(levelId);
    if (mario) { delete mario; mario = NULL; }
    if (luigi) { delete luigi; luigi = NULL; }
    mario = new Player(level.inPosX, level.inPosY, "m", marioControls);
    luigi = new Player(level.inPosX + 32, level.inPosY, "l", luigiControls);
    mario->crearAssets("m");
    luigi->crearAssets("l");
    mario->onGround = true;
    luigi->onGround = true;
    players.clear();
    players.push_back(mario);
	players.push_back(luigi);
	if (gm) delete gm;
    gm = new GameManager();
    gm->currentSection = level.getSection(mario->y);
    std::stringstream ss;
	ss << levelId;
	hud.loadLevelPreview(ss.str());
    stateTimer = PREVIEW_SECONDS;
    level.player = mario;
    state = PREVIEW_2P;
	};
    ALLEGRO_KEYBOARD_STATE keyState;
    while (!done) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { done = true; break; }
        if (ev.type == ALLEGRO_EVENT_KEY_UP && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { done = true; break; }
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            al_get_keyboard_state(&keyState);
            double currentTime = al_get_time();
            deltaTime = currentTime - lastTime;
            lastTime = currentTime;
            if(state == FINAL_2P){
            	level.stopTrack();
            	al_set_target_bitmap(gameBuffer);
    			al_clear_to_color(al_map_rgb(0,0,0));
    			ALLEGRO_TRANSFORM cam;
    			al_identity_transform(&cam);
    			al_use_transform(&cam);
            	winner2p.wdraw(keyState);
            	al_set_target_backbuffer(display);
    			al_clear_to_color(al_map_rgb(0,0,0));
    			float scaledW = BaseWidth * finalScale;
    			float scaledH = BaseHeight * finalScale;
    			float offsetX = (ScreenWidth - scaledW) / 2;
    			float offsetY = (ScreenHeight - scaledH) / 2;
    			al_draw_scaled_bitmap( gameBuffer, 0, 0, BaseWidth, BaseHeight, offsetX, offsetY, scaledW, scaledH,	0);
    			al_flip_display();
    			if (winner2p.gomenu) {
    				players.clear();
        			state = MENU;
        			menu.song = false;
        			winner2p.gomenu = false;
        			winner2p.played = false;
					winner2p.mcount = 0;
					winner2p.lcount = 0;
					winner2p.mwin = false;
					winner2p.lwin = false;
        			al_get_keyboard_state(&keyState);  
    				menu.onEnter(keyState);
    			}
    			continue;
			}else if(state == GAMEOVER){
            	level.stopTrack();
            	al_set_target_bitmap(gameBuffer);
    			al_clear_to_color(al_map_rgb(0,0,0));
    			ALLEGRO_TRANSFORM cam;
    			al_identity_transform(&cam);
    			al_use_transform(&cam);
            	gameover.draw(keyState);
            	al_set_target_backbuffer(display);
    			al_clear_to_color(al_map_rgb(0,0,0));
    			float scaledW = BaseWidth * finalScale;
    			float scaledH = BaseHeight * finalScale;
    			float offsetX = (ScreenWidth - scaledW) / 2;
    			float offsetY = (ScreenHeight - scaledH) / 2;
    			al_draw_scaled_bitmap( gameBuffer, 0, 0, BaseWidth, BaseHeight, offsetX, offsetY, scaledW, scaledH,	0);
    			al_flip_display();
    				if(gameover.cont){
    				al_play_sample(goagain, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    				gameover.stopMusic();
    				state = PREVIEW;
    				loadLevelAndPlayer(levelsToPlay[currentLevelIndex],false,false);
					}else if(gameover.gomenu){
						gameover.stopMusic();
						menu.song = false;
    					state = MENU;
    					al_get_keyboard_state(&keyState);  
    					menu.onEnter(keyState);
    					if (mario) mario->dead = false;
					}
    			continue;
			}else if (state == MENU){
            	al_set_target_bitmap(gameBuffer);
    			al_clear_to_color(al_map_rgb(0,0,0));
    			ALLEGRO_TRANSFORM cam;
    			al_identity_transform(&cam);
    			al_use_transform(&cam);
            	menu.draw(keyState);
            	al_set_target_backbuffer(display);
    			al_clear_to_color(al_map_rgb(0,0,0));
    			float scaledW = BaseWidth * finalScale;
    			float scaledH = BaseHeight * finalScale;
    			float offsetX = (ScreenWidth - scaledW) / 2;
    			float offsetY = (ScreenHeight - scaledH) / 2;
    			al_draw_scaled_bitmap( gameBuffer, 0, 0, BaseWidth, BaseHeight, offsetX, offsetY, scaledW, scaledH,	0);
    			al_flip_display();
    			if(menu.play1){
    				 al_play_sample(letsgo, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
    				 menu.stopMusic();
    				state = PREVIEW;
    				loadLevelAndPlayer(levelsToPlay[currentLevelIndex],false,false);
    				menu.play1 = false;
				}else if(menu.play2){
					al_play_sample(battlemode, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					menu.stopMusic();
					loadLevel2P(levelsToPlay2P[currentLevelIndex2P]);
					currentLevelIndex = 0;
				}
    			continue;
			}else if (state == PREVIEW) {
                stateTimer -= deltaTime;
                if (stateTimer <= 0.0f) {
                    state = PLAY;
                }
            } else if (state == FADE_OUT) {
                stateTimer -= deltaTime;
                fadeAlpha = 1.0f - (stateTimer / FADE_SECONDS); 
                if (stateTimer <= 0.0f) {
                    currentLevelIndex++;
                    if (currentLevelIndex >= (int)levelsToPlay.size()) {
                        done = true;
                        continue;
                    }
                    loadLevelAndPlayer(levelsToPlay[currentLevelIndex], true, false);
                }
            }else if (state == PREVIEW_2P) {
    			stateTimer -= deltaTime;
    			if (stateTimer <= 0.0f)
        			state = PLAY_2P;
			}
            if (state == PLAY) {
            	hudElapsedTime += 1.0 / FPS;
    			if (hudElapsedTime >= 1.0) {
        		hudElapsedTime -= 1.0;
        		if (hudTimer > 0) hudTimer--;
    			}
                if (level.theme != "underwater") mario->update(keyState, deltaTime);
                else mario->updateSwim(keyState, deltaTime);
                level.update();
                gm->verifColision(level,mario);
                if (state == PLAY && mario->dead) {
    			if (mario->y >640) {
        			int levelId = levelsToPlay[currentLevelIndex];
        			loadLevelAndPlayer(levelId,false,true);
        			state = (mario->lives <= 0) ? GAMEOVER : PREVIEW;
        			if(mario->lives <= 0) gameover.song = false;
        			continue;
    			}
    			}
                float top = level.getSectionTop(level.getSection(mario->y));
                if (!mario->dead && !gm->isFading && mario->onGround) {
                    gm->currentSection = level.getSection(mario->y);
                }
                level.applyTheme(levelsToPlay[currentLevelIndex], gm->currentSection);
                gm->updateCamera(BaseWidth, BaseHeight, level.levelWidth, level.levelHeight, &level, mario);
                gm->checkWarp(level,mario,NULL);
                gm->updateFade(level,mario, NULL);
                if (mario->endanim) {
                	level.stopTrack();
                    state = FADE_OUT;
                    stateTimer = FADE_SECONDS;
                    fadeAlpha = 0.0f;
                }
            }else if(state == PLAY_2P){
            	for (size_t i=0; i<players.size(); i++){
            		Player* p = players[i];
    				if (level.theme != "underwater")
        				p->update(keyState, deltaTime);
    				else
        				p->updateSwim(keyState, deltaTime);
        			if (p->dead){		
        				continue;
					} 
    				gm->verifColision(level, p);
				}
				level.update();
				gm->checkWarp(level, mario, luigi);
				gm->updateFade(level, mario, luigi); 
				if (!mario->dead && !luigi->dead && mario->onGround && luigi->onGround) {
        			gm->currentSection = level.getSection(mario->y);;
				}
				level.applyTheme(levelsToPlay2P[currentLevelIndex2P], gm->currentSection);
				if (!levelEnded) {
					if (mario->endanim && !luigi->endanim){
        				marioWins++;
        				deathTimer2P = DEATH_DELAY;
        				levelEnded = true;
    				}else if (luigi->endanim && !mario->endanim){
        				luigiWins++;
        				deathTimer2P = DEATH_DELAY;
        				levelEnded = true;
    				}else if (mario->dead && !luigi->dead){
        				luigiWins++;
        				deathTimer2P = DEATH_DELAY;
        				levelEnded = true;
					}else if (luigi->dead && !mario->dead){
        				marioWins++;
        				deathTimer2P = DEATH_DELAY;
        				levelEnded = true;
    				}else if (mario->dead && luigi->dead){
        				deathTimer2P = DEATH_DELAY;
        				levelEnded = true;
    				}
				}
				if (levelEnded) {
					deathTimer2P -= deltaTime;
    				if(deathTimer2P <= 0.0f){
        				level.stopTrack();
        				currentLevelIndex2P++;
        			if (currentLevelIndex2P >= (int)levelsToPlay2P.size()) {
        				players.clear();
            			winner2p.mcount = marioWins;
            			winner2p.lcount = luigiWins;
            			if(marioWins>luigiWins){
            				winner2p.mwin = true;
            				winner2p.lwin = false;
						}else if(luigiWins>marioWins){
							winner2p.lwin = true;
							winner2p.mwin = false;
						}
            			state = FINAL_2P;
        			} else {
            			loadLevel2P(levelsToPlay2P[currentLevelIndex2P]);
        			}
        			levelEnded = false;
    				}
				}	
				gm->updateCamera2P(BaseWidth, BaseHeight, &level, mario, luigi);
			}
            al_set_target_bitmap(gameBuffer);
            al_clear_to_color(al_map_rgb(0,0,0));
            ALLEGRO_TRANSFORM camera;
            al_identity_transform(&camera);
            if (gm) { al_translate_transform(&camera, -gm->cameraX, -gm->cameraY);}
            al_use_transform(&camera);
            if (state == PREVIEW) {
                al_clear_to_color(al_map_rgb(0,0,0));
                hud.drawLevelIntro(BaseWidth, BaseHeight, mario->lives);
            } else if (state == PLAY || state == FADE_OUT) {
                level.drawBackgrounds(levelsToPlay[currentLevelIndex]);
                if (mario->warp || mario->exitWarp) {
                    mario->draw();
                    level.draw();
                } else {
                    level.draw();
                    mario->draw();
                }
            }else if(state == PLAY_2P){
            	    level.drawBackgrounds(levelsToPlay2P[currentLevelIndex2P]);
            	    level.draw();
    				for(size_t i=0; i<players.size(); i++){
    					Player* p = players[i];
    					p->draw();
					}
			}
			if (state == PREVIEW_2P) {
    			al_clear_to_color(al_map_rgb(0,0,0));
    			hud.drawLevelIntro(BaseWidth, BaseHeight, -1);
			}
            al_set_target_backbuffer(display);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_identity_transform(&camera);
            al_use_transform(&camera);
            float scaledW = BaseWidth * finalScale;
            float scaledH = BaseHeight * finalScale;
            float offsetX = (ScreenWidth - scaledW) / 2;
            float offsetY = (ScreenHeight - scaledH) / 2;
            al_draw_scaled_bitmap(gameBuffer, 0, 0, BaseWidth, BaseHeight, offsetX, offsetY, scaledW, scaledH, 0);
            if (state == PLAY) {
                hud.drawHud(ScreenWidth, ScreenHeight, mario->lives, mario->tcoin, hudTimer);
            }
            if (state == FADE_OUT) {
                float a = fadeAlpha;
                if (a < 0) a = 0; if (a > 1) a = 1;
                al_draw_filled_rectangle(0, 0, ScreenWidth, ScreenHeight, al_map_rgba_f(0,0,0,a));
            }
            al_flip_display();
        }
    }
    if (mario) { mario->destruirAssets(); delete mario; }
    if (gm) delete gm;
    level.destroy();
    hud.cHudassets();
    al_destroy_bitmap(gameBuffer);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}
