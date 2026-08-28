//Clase Castillo!!
class Castle{
	public:
		float x,y;
		float wide;
		int type;
		static ALLEGRO_BITMAP* castle;
		static ALLEGRO_BITMAP* BigCastle;
		//Constructor
		Castle(float inx, float iny, int types){
			x = inx;
			y = iny;
			type = types;
			wide = 93;
		}
		//Métodos
		static void ccassets(){
			castle = al_load_bitmap("Sprites/castle.png");
			BigCastle = al_load_bitmap("Sprites/Bigcastle.png");
		}
		static void cscassets(){
			castle = al_load_bitmap("Sprites/castle.png");
			BigCastle = al_load_bitmap("Sprites/sBigcastle.png");
		}
		static void dcassets(){
			al_destroy_bitmap(castle);
			al_destroy_bitmap(BigCastle);
		}
		void cdraw(){
			if(type == 1){
				al_draw_bitmap(castle,x,y,0);
			}else if(type == 2){
				al_draw_bitmap(BigCastle,x,y,0);
			}
		}
};
ALLEGRO_BITMAP* Castle::castle = NULL;
ALLEGRO_BITMAP* Castle::BigCastle = NULL;
