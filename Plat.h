//Clase Plataforma 2
class Plat{
	public:
	float x, y;
		enum Type{TOP_LEFT = 0,TOP_RIGHT,BODY_LEFT,BODY_RIGHT, MIDDLE, LEFT_UNDER,RIGHT_UNDER,MIDDLE_UNDER,LEFT_ONLY,RIGHT_ONLY};
		Type type;
		int tipo;
    	static ALLEGRO_BITMAP *hloug;
    	static ALLEGRO_BITMAP *hltg;
    	static ALLEGRO_BITMAP *hlug;
    	static ALLEGRO_BITMAP *hroug;
    	static ALLEGRO_BITMAP *hrtg;
    	static ALLEGRO_BITMAP *hrug;
    	static ALLEGRO_BITMAP *htg;
    	static ALLEGRO_BITMAP *htgl;
    	static ALLEGRO_BITMAP *htgr;
    	static ALLEGRO_BITMAP *hug;
    	//Constructor
    	Plat(float x_, float y_, Type t, int tipos){
    		x = x_;
    		y = y_;
    		type = t;
    		tipo = tipos;
		}
        //Métodos
    	static void cplaassets(){
    		hloug = al_load_bitmap("Sprites/hloug.png");
        	hltg = al_load_bitmap("Sprites/hltg.png");
        	hlug = al_load_bitmap("Sprites/hlug.png");
        	hroug = al_load_bitmap("Sprites/hroug.png");
        	hrtg = al_load_bitmap("Sprites/hrtg.png");
        	hrug = al_load_bitmap("Sprites/hrug.png");
        	htg = al_load_bitmap("Sprites/htg.png");
        	htgl = al_load_bitmap("Sprites/htgl.png");
        	htgr = al_load_bitmap("Sprites/htgr.png");
        	hug = al_load_bitmap("Sprites/hug.png");
		}
		static void ccplaassets(){
			hloug = al_load_bitmap("Sprites/hloug.png");
        	hltg = al_load_bitmap("Sprites/bl.png");
        	hlug = al_load_bitmap("Sprites/hlug.png");
        	hroug = al_load_bitmap("Sprites/hroug.png");
        	hrtg = al_load_bitmap("Sprites/cbrick.png");
        	hrug = al_load_bitmap("Sprites/hrug.png");
        	htg = al_load_bitmap("Sprites/st.png");
        	htgl = al_load_bitmap("Sprites/br.png");
        	htgr = al_load_bitmap("Sprites/str.png");
        	hug = al_load_bitmap("Sprites/stu.png");
		}
		static void cmplaassets(){
			hloug = al_load_bitmap("Sprites/hloug.png");
        	hltg = al_load_bitmap("Sprites/mltg.png");
        	hlug = al_load_bitmap("Sprites/mlug.png");
        	hroug = al_load_bitmap("Sprites/hroug.png");
        	hrtg = al_load_bitmap("Sprites/mrtg.png");
        	hrug = al_load_bitmap("Sprites/hrug.png");
        	htg = al_load_bitmap("Sprites/mtg.png");
        	htgl = al_load_bitmap("Sprites/br.png");
        	htgr = al_load_bitmap("Sprites/str.png");
        	hug = al_load_bitmap("Sprites/mug.png");
		}
		static void dplaassets(){
			al_destroy_bitmap(hloug);
			al_destroy_bitmap(hltg);
			al_destroy_bitmap(hlug);
			al_destroy_bitmap(hroug);
			al_destroy_bitmap(hrtg);
			al_destroy_bitmap(hrug);
			al_destroy_bitmap(htg);
			al_destroy_bitmap(htgl);
			al_destroy_bitmap(htgr);
			al_destroy_bitmap(hug);
		}
		void pladraw(){
        ALLEGRO_BITMAP* sprite = NULL;
        switch (type){
            case TOP_LEFT:   sprite = hltg; break;
            case TOP_RIGHT:  sprite = hrtg; break;
            case BODY_LEFT:  sprite = htgl; break;
            case BODY_RIGHT: sprite = htgr; break;
            case MIDDLE: sprite = htg; break;
            case LEFT_UNDER: sprite = hlug; break;
            case RIGHT_UNDER: sprite = hrug; break;
            case MIDDLE_UNDER: sprite = hug; break;
            case LEFT_ONLY: sprite = hloug; break;
            case RIGHT_ONLY: sprite = hroug; break;
        }
        if (sprite)
            al_draw_bitmap(sprite,x,y,0);
    	}
};
ALLEGRO_BITMAP* Plat::hltg = NULL;
ALLEGRO_BITMAP* Plat::hrtg = NULL;
ALLEGRO_BITMAP* Plat::htgl = NULL;
ALLEGRO_BITMAP* Plat::htgr = NULL;
ALLEGRO_BITMAP* Plat::htg = NULL;
ALLEGRO_BITMAP* Plat::hlug = NULL;
ALLEGRO_BITMAP* Plat::hrug = NULL;
ALLEGRO_BITMAP* Plat::hug = NULL;
ALLEGRO_BITMAP* Plat::hloug = NULL;
ALLEGRO_BITMAP*	Plat::hroug = NULL;
