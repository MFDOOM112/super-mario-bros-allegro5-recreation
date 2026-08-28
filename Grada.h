//Clase Gradas
#include<sstream>
class Grada{
	public:
		float x,y;
		static ALLEGRO_BITMAP *grada;
	//Constructor
	Grada(float inx, float iny){
		x = inx;
		y = iny;
	}
	//Métodos
	static void cstassets(int cases){
		std::stringstream str;
		if(cases == 1){
			str << "Sprites/"<<cases<<"st.png";
			grada = al_load_bitmap(str.str().c_str());
		}else if(cases == 2){
			str<<"Sprites/"<<cases<<"st.png";
			grada = al_load_bitmap(str.str().c_str());
		}else if(cases == 3){
			str<<"Sprites/"<<cases<<"st.png";
			grada = al_load_bitmap(str.str().c_str());
		}
	}
	static void dstassets(){
		al_destroy_bitmap(grada);
	}
	void stdraw(){
		al_draw_bitmap(grada, x, y, 0);
	}	
};
ALLEGRO_BITMAP* Grada::grada = NULL;	
