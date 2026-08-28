//Clase Bridge-normal
class Bridge{
	public:
		float x,y;
		float ux,uy;
		static ALLEGRO_BITMAP* bridgeup;
		static ALLEGRO_BITMAP* bridge;
	//Constructor
	Bridge(float inx, float iny){
		x = inx;
		y = iny;
		ux = inx;
		uy = iny-8;
	}
	//Métodos
	static void cbrassets(){
		bridgeup = al_load_bitmap("Sprites/bridgeup.png");
		bridge = al_load_bitmap("Sprites/bridge.png");
	}
	static void dbrassets(){
		al_destroy_bitmap(bridgeup);
		al_destroy_bitmap(bridge);
	}
	void draw(){
		al_draw_bitmap(bridgeup, ux, uy, 0);
		al_draw_bitmap(bridge, x, y, 0);
	}	
};
ALLEGRO_BITMAP* Bridge::bridgeup = NULL;
ALLEGRO_BITMAP* Bridge::bridge = NULL;
