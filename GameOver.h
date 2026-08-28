//CLASE GAMEOVER
class GameOver{
	public:
	float x,y;
	float cx, cy;
	float qx, qy;
	float ox,oy;
	int selected;
	bool song;
	bool cont;
	bool gomenu;
	ALLEGRO_BITMAP* gameoversc;
	ALLEGRO_BITMAP* continuel;
	ALLEGRO_BITMAP* quit;
	ALLEGRO_BITMAP* opt;
	ALLEGRO_SAMPLE* mopt;
	ALLEGRO_SAMPLE* sGameover;
	ALLEGRO_SAMPLE_INSTANCE* Gameoverinst;
	//Constructor
	GameOver(float inx, float iny){
		x = inx;
		y = iny;
		cx = inx+80;
		cy = iny+100;
		qx = inx+80;
		qy = iny+120;
		ox = inx+60;
		oy = cy;
		song = false;
		cont = false;
		gomenu = false;
	}
	//Métodos
	void goassets(){
		gameoversc = al_load_bitmap("Menu/M1.png");
		continuel = al_load_bitmap("Menu/continue.png");
		quit = al_load_bitmap("Menu/quit.png");
		opt = al_load_bitmap("Menu/hand.png");
		mopt = al_load_sample("Sounds/Select.wav");
		sGameover = al_load_sample("Sounds/GameOver.wav");
		Gameoverinst = al_create_sample_instance(sGameover);
		al_set_sample_instance_playmode(Gameoverinst, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(Gameoverinst, al_get_default_mixer());
	}
	void draw(ALLEGRO_KEYBOARD_STATE &keyState){
		if(!song){
    		al_play_sample_instance(Gameoverinst);
    		song = true;
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
    		if (selected != 0) {
            selected = 0;
            oy = cy;
            al_play_sample(mopt, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        	}
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
    		if (selected != 1) {
            selected = 1;
            oy = qy;
            al_play_sample(mopt, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        	}
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_ENTER)){
			if(oy == cy){
				cont = true;
				gomenu = false;
			}else{
				gomenu = true;
				cont = false;
			}
		}
		al_draw_bitmap(continuel,cx,cy,0);
		al_draw_bitmap(quit,qx,qy,0);
		al_draw_bitmap(opt,ox,oy,0);
		al_draw_bitmap(gameoversc,x,y+30,0);
	}
	void stopMusic(){
    if(Gameoverinst){
        al_stop_sample_instance(Gameoverinst);
    }
	} 
};
