//Clase bloque castillo
class cBlock{
	public:
	float x,y;
	static ALLEGRO_BITMAP* cblock;
	//Constructor
	cBlock(float inx, float iny){
		x = inx;
		y = iny;
	}
	//Métodos
	static void ccbassets(){
		cblock = al_load_bitmap("Sprites/cBlock.png");
	}
	static void dcbassets(){
		al_destroy_bitmap(cblock);
	}
	void cbdraw(){
		al_draw_bitmap(cblock,x,y,0);
	}
};
ALLEGRO_BITMAP* cBlock::cblock = NULL;
