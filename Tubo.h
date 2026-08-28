//CLASE TUBOS!!!
class Tubo{
	public:
		float x, y;
		enum Type{TOP_LEFT = 0,TOP_RIGHT,BODY_LEFT,BODY_RIGHT,LAID_LEFT,LAID_RIGHT,LAID_BASE_LEFT,LAID_BASE_RIGHT,LAID_TOP_LEFT,LAID_TOP_RIGHT};
		Type type;
    	static ALLEGRO_BITMAP *tubotl;
    	static ALLEGRO_BITMAP *tubotr;
    	static ALLEGRO_BITMAP *tubobl;
    	static ALLEGRO_BITMAP *tubobr;
    	static ALLEGRO_BITMAP *tuboll;
    	static ALLEGRO_BITMAP *tubolr;
    	static ALLEGRO_BITMAP *tubolbl;
    	static ALLEGRO_BITMAP *tubolbr;
    	static ALLEGRO_BITMAP *tuboltl;
    	static ALLEGRO_BITMAP *tuboltr;
    	//Constructor
    	Tubo(float x_, float y_, Type t)
        : x(x_), y(y_), type(t) {}
        //Métodos
    	static void ctassets(){
    		tubotl = al_load_bitmap("Sprites/tubo1.png");
        	tubotr = al_load_bitmap("Sprites/tubo2.png");
        	tubobl = al_load_bitmap("Sprites/tubo3.png");
        	tubobr = al_load_bitmap("Sprites/tubo4.png");
        	tuboll = al_load_bitmap("Sprites/tubo5.png");
        	tubolr = al_load_bitmap("Sprites/tubo6.png");
        	tubolbl = al_load_bitmap("Sprites/tubo7.png");
        	tubolbr = al_load_bitmap("Sprites/tubo8.png");
        	tuboltl = al_load_bitmap("Sprites/tubo9.png");
        	tuboltr = al_load_bitmap("Sprites/tubo10.png");
		}
		static void cstassets(){
    		tubotl = al_load_bitmap("Sprites/stubo1.png");
        	tubotr = al_load_bitmap("Sprites/stubo2.png");
        	tubobl = al_load_bitmap("Sprites/stubo3.png");
        	tubobr = al_load_bitmap("Sprites/stubo4.png");
        	tuboll = al_load_bitmap("Sprites/tubo5.png");
        	tubolr = al_load_bitmap("Sprites/tubo6.png");
        	tubolbl = al_load_bitmap("Sprites/tubo7.png");
        	tubolbr = al_load_bitmap("Sprites/tubo8.png");
        	tuboltl = al_load_bitmap("Sprites/tubo9.png");
        	tuboltr = al_load_bitmap("Sprites/tubo10.png");
		}
		static void dtassets(){
			al_destroy_bitmap(tubotl);
			al_destroy_bitmap(tubotr);
			al_destroy_bitmap(tubobl);
			al_destroy_bitmap(tubobr);
			al_destroy_bitmap(tuboll);
			al_destroy_bitmap(tubolr);
			al_destroy_bitmap(tubolbl);
			al_destroy_bitmap(tubolbr);
			al_destroy_bitmap(tuboltl);
			al_destroy_bitmap(tuboltr);
		}
		void tdraw(){
        ALLEGRO_BITMAP* sprite = NULL;
        switch (type){
            case TOP_LEFT:   sprite = tubotl; break;
            case TOP_RIGHT:  sprite = tubotr; break;
            case BODY_LEFT:  sprite = tubobl; break;
            case BODY_RIGHT: sprite = tubobr; break;
            case LAID_LEFT: sprite = tuboll; break;
            case LAID_RIGHT: sprite = tubolr; break;
            case LAID_BASE_LEFT: sprite = tubolbl; break;
            case LAID_BASE_RIGHT: sprite = tubolbr; break;
            case LAID_TOP_LEFT: sprite = tuboltl; break;
            case LAID_TOP_RIGHT: sprite = tuboltr; break;
        }
        if (sprite)
            al_draw_bitmap(sprite,x,y,0);
    	}
};
ALLEGRO_BITMAP* Tubo::tubotl = NULL;
ALLEGRO_BITMAP* Tubo::tubotr = NULL;
ALLEGRO_BITMAP* Tubo::tubobl = NULL;
ALLEGRO_BITMAP* Tubo::tubobr = NULL;
ALLEGRO_BITMAP* Tubo::tuboll = NULL;
ALLEGRO_BITMAP* Tubo::tubolr = NULL;
ALLEGRO_BITMAP* Tubo::tubolbl = NULL;
ALLEGRO_BITMAP* Tubo::tubolbr = NULL;
ALLEGRO_BITMAP* Tubo::tuboltl = NULL;
ALLEGRO_BITMAP* Tubo::tuboltr = NULL;
