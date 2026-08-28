//Clase Menu
#include<sstream>
class Menu{
	public:
		float x,y;
		float ox, oy;
		float p1x, p1y;
		float p2x, p2y;
		int frameCount;
		int frameDelay;
		int in;
		int selected;
		bool song;
		bool play1;
		bool play2;
		bool enterPrev;
		ALLEGRO_BITMAP* title;
		ALLEGRO_BITMAP* player1;
		ALLEGRO_BITMAP* player2;
		ALLEGRO_BITMAP* opt;
		ALLEGRO_BITMAP* backmario[199];
		ALLEGRO_SAMPLE* menumusic;
		ALLEGRO_SAMPLE* menuopt;
		ALLEGRO_SAMPLE_INSTANCE* menuMusicInstance;
	//Constructor
	Menu(float inx, float iny){
		x = inx;
		y = iny;
		p1x = inx+80;
		p1y = iny+150;
		p2x = inx+80;
		p2y = iny+170;
		ox = inx+70;
		oy = p1y;
		in = 0;
		frameCount = 0;
		frameDelay = 5;
		song = false;
		play1 = false;
		play2 = false;
		enterPrev = false;
	}
	//Métodos
	void menassets(){
		for(int i=0;i<199;i++){
			std::stringstream str;
            str << "Menu/" <<i + 1<<".jpg";
            backmario[i] = al_load_bitmap(str.str().c_str());
		}
		title = al_load_bitmap("Menu/titulo.png");
		player1 = al_load_bitmap("Menu/jugador 1.png");
		player2 = al_load_bitmap("Menu/jugador 2.png");
		opt = al_load_bitmap("Menu/hongo.png");
		menuopt = al_load_sample("Sounds/Select.wav");
		menumusic = al_load_sample("Soundtrack/musicam.wav");
		menuMusicInstance = al_create_sample_instance(menumusic);
		al_set_sample_instance_playmode(menuMusicInstance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(menuMusicInstance, al_get_default_mixer());
	}
	void draw(ALLEGRO_KEYBOARD_STATE &keyState){
		if(!song){
    		al_play_sample_instance(menuMusicInstance);
    		song = true;
		}
		ALLEGRO_BITMAP* bg = backmario[in];
		int bw = al_get_bitmap_width(bg);
		int bh = al_get_bitmap_height(bg);
		al_draw_scaled_bitmap(bg, 0, 0, bw, bh,0, 0, 256, 240, 0);
		frameCount++;
		if(frameCount >= frameDelay){
			frameCount = 0;
			in++;
			if(in>=199){
				in = 0;
			}
		}
		al_draw_bitmap(title,x+40,y+50,0);
		if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
    		if (selected != 0) {
            selected = 0;
            oy = p1y;
            al_play_sample(menuopt, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        	}
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
    		if (selected != 1) {
            selected = 1;
            oy = p2y;
            al_play_sample(menuopt, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
        	}
		}
		bool enterNow = al_key_down(&keyState, ALLEGRO_KEY_ENTER);
		if (enterNow && !enterPrev) {
    		if (oy == p1y) {
        	play1 = true;
        	play2 = false;
    	} else {
        	play2 = true;
        	play1 = false;
    	}
}

enterPrev = enterNow;
		al_draw_bitmap(player1,p1x,p1y,0);
		al_draw_bitmap(player2,p2x,p2y,0);
		al_draw_bitmap(opt,ox,oy,0);
	}
	void stopMusic(){
    if(menuMusicInstance){
        al_stop_sample_instance(menuMusicInstance);
    }
	}
	void onEnter(ALLEGRO_KEYBOARD_STATE& keyState) {
    enterPrev = al_key_down(&keyState, ALLEGRO_KEY_ENTER);
    play1 = false;
    play2 = false;
} 
};
