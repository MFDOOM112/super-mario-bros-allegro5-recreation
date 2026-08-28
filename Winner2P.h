//Clase WINNER2P
#include <sstream>
class Winner2P{
	public:
	float x,y;
	float ox,oy;
	float mx,my;
	float lx,ly;
	float cx,cy;
	float qx,qy;
	float rx, ry;
	float vx,vy;
	float rnx, rny;
	int frameCount;
	int frameDelay;
	bool mwin;
	bool lwin;
	bool cont;
	bool gomenu;
	bool played;
	int mcount;
	int lcount;
	int inml;
	int inll;
	int inmf;
	int inlf;
	int inr;
	int selected;
	ALLEGRO_BITMAP* winnerscreen;
	ALLEGRO_BITMAP* winner;
	ALLEGRO_BITMAP* rounds[10];
	ALLEGRO_BITMAP* victorym[10];
	ALLEGRO_BITMAP* victoryl[10];
	ALLEGRO_BITMAP* vs;
	ALLEGRO_BITMAP* mariol[3];
	ALLEGRO_BITMAP* luigil[3];
	ALLEGRO_BITMAP* round;
	ALLEGRO_BITMAP* marioface[5];
	ALLEGRO_BITMAP* luigiface[5];
	ALLEGRO_BITMAP* continuel;
	ALLEGRO_BITMAP* quit;
	ALLEGRO_BITMAP* hand;
	ALLEGRO_SAMPLE* swinner;
	ALLEGRO_SAMPLE* draw;
	ALLEGRO_SAMPLE* mopt;
	//Constructor
	Winner2P(float inx, float iny){
		x = inx;
		y = iny;
		mx = inx+40;
		my = iny+100;
		lx = inx+180;
		ly = iny+100;
		ox = inx+100;
		oy = iny+120;
		vx = inx+123;
		vy = iny+95;
		qx = inx+110;
		qy = iny+120;
		rx = inx+80;
		ry = iny+15;
		rnx = inx+150;
		rny = ry+3;
		frameCount = 0;
		frameDelay = 10;
		mcount = 0;
		lcount = 0;
		inml = 0;
		inll = 0;
		inmf = 0;
		inlf = 0;
		selected = 0;
		cont = false;
		gomenu = false;
		played = false;
	}
	//Métodos
	void cwassets(){
		winnerscreen = al_load_bitmap("Menu/winnerscreen.png");
		winner = al_load_bitmap("Menu/winner.png");
		vs = al_load_bitmap("Menu/vs.png");
		round = al_load_bitmap("Menu/round.png");
		continuel = al_load_bitmap("Menu/continue.png");
		quit = al_load_bitmap("Menu/quit.png");
		hand = al_load_bitmap("Menu/hand.png");
		for(int i=0;i<5;i++){
			std::stringstream str;
            str << "Menu/mf" <<i + 1<<".png";
            marioface[i] = al_load_bitmap(str.str().c_str());
		}
		for(int i=0;i<5;i++){
			std::stringstream str;
            str << "Menu/lf" <<i + 1<<".png";
            luigiface[i] = al_load_bitmap(str.str().c_str());
		}
		for(int i=0;i<3;i++){
			std::stringstream str;
            str << "Menu/" <<i + 1<<"ml.png";
            mariol[i] = al_load_bitmap(str.str().c_str());
		}
		for(int i=0;i<3;i++){
			std::stringstream str;
            str << "Menu/" <<i + 1<<"ll.png";
            luigil[i] = al_load_bitmap(str.str().c_str());
		}
		for(int i=0;i<10;i++){
			std::stringstream str;
            str << "Menu/" <<i<<".png";
            rounds[i] = al_load_bitmap(str.str().c_str());
		}
		for(int i=0;i<10;i++){
			std::stringstream str;
            str << "Menu/" <<i<<".png";
            victorym[i] = al_load_bitmap(str.str().c_str());
		}
		for(int i=0;i<10;i++){
			std::stringstream str;
            str << "Menu/" <<i<<".png";
            victoryl[i] = al_load_bitmap(str.str().c_str());
		}
		swinner = al_load_sample("Sounds/winner.wav");
		mopt = al_load_sample("Sounds/Select.wav");
		draw = al_load_sample("Sounds/draw.wav");
	}
	void wdraw(ALLEGRO_KEYBOARD_STATE &keyState){
		al_draw_bitmap(winnerscreen,x,y,0);
		al_draw_bitmap(round,rx,ry,0);
		al_draw_bitmap(rounds[inr],rnx,rny,0);
		al_draw_bitmap(vs,vx,vy-30,0);
		if(mwin){
			if(!played){
				al_play_sample(swinner, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				played = true;
			}
			al_draw_bitmap(winner,mx,my-40,0);
			al_draw_bitmap(mariol[inml],mx,my-20,0);
			al_draw_bitmap(luigil[inll],lx,ly-20,0);
			al_draw_bitmap(marioface[inmf],mx,my,0);
			al_draw_bitmap(luigiface[inlf],lx,ly,0);
			frameCount++;
			if(frameCount>=frameDelay){
				inmf++;
				inlf++;
				inml++;
				inll++;
				frameCount = 0;
				if(inml>=3){
					inml = 0;
				}
				if(inll>=3){
					inll = 0;
				}
				if(inmf>=3){
					inmf = 0;
				}
				if(inlf<3||inlf>=5){
					inlf = 3;
				}
			}
		}else if(lwin){
			if(!played){
				al_play_sample(swinner, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				played = true;
			}
			al_draw_bitmap(winner,lx-10,ly-40,0);
			al_draw_bitmap(mariol[inml],mx,my-20,0);
			al_draw_bitmap(luigil[inll],lx,ly-20,0);
			al_draw_bitmap(marioface[inmf],mx,my,0);
			al_draw_bitmap(luigiface[inlf],lx,ly,0);
			frameCount++;
			if(frameCount>=frameDelay){
				inmf++;
				inlf++;
				inml++;
				inll++;
				frameCount = 0;
				if(inml>=3){
					inml = 0;
				}
				if(inll>=3){
					inll = 0;
				}
				if(inlf>=3){
					inlf = 0;
				}
				if(inmf<3||inmf>=5){
					inmf = 3;
				}
			}
		}else{
			if(!played){
				al_play_sample(draw, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				played = true;
			}
			al_draw_bitmap(mariol[inml],mx,my-20,0);
			al_draw_bitmap(luigil[inll],lx,ly-20,0);
			al_draw_bitmap(marioface[inmf],mx,my,0);
			al_draw_bitmap(luigiface[inlf],lx,ly,0);
			frameCount++;
			if(frameCount>=frameDelay){
				frameCount = 0;
				inmf++;
				inlf++;
				inml++;
				inll++;
				if(inml>=3){
					inml = 0;
				}
				if(inll>=3){
					inll = 0;
				}
				if(inlf<3||inlf>=5){
					inlf = 3;
				}
				if(inmf<3||inmf>=5){
					inmf = 3;
				}
			}
		}
		if (al_key_down(&keyState, ALLEGRO_KEY_ENTER)){
			gomenu = true;
		}
		al_draw_bitmap(hand,ox,oy,0);
		al_draw_bitmap(quit,qx,qy,0);
	}
};
