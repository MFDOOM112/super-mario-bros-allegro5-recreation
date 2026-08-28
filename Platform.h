//CLASE PLATAFORMA
class Platform{
	public:
		float x;
		float y;
		float count;
		float maxy;
		float inposy;
		bool active;
		static ALLEGRO_BITMAP* platform;
	//Constructor
	Platform(float inx, float iny){
		x = inx;
		y = iny;
		inposy = iny;
		maxy = 500;
		count = 0;
		active = true;
	}
	static void cpassets(){
		platform = al_load_bitmap("Sprites/platform.png");
	}
	static void dpassets(){
		al_destroy_bitmap(platform);
	}
	void pdraw(){
		if(active){
			al_draw_bitmap(platform,x,y,0);
		}
	}		
};
ALLEGRO_BITMAP* Platform::platform = NULL;
