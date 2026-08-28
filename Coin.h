//CLASE MONEDA
class Coin{
	public:
		float cx, cy;
		bool cactive;
		int in;
		int frameDelay;
		int frameCount;
		static ALLEGRO_BITMAP *coin[3];
	//Constructor
		Coin(float cix, float ciy){
			cx = cix;
			cy = ciy;
			cactive = true;
			in = 0;
			frameDelay = 10;
			frameCount = 0;
		}
	//Métodos
		static void ccassets(){
			for(int i=0;i<3;i++){
			std::stringstream str;
            str << "Sprites/" <<i + 1<<"c"<<".png";
            coin[i] = al_load_bitmap(str.str().c_str());
			}
		}
		static void descassets(){
			for(int i=0;i<3;i++){
			al_destroy_bitmap(coin[i]);
			}
		}
		void cdraw(){
			if(cactive){
				al_draw_bitmap(coin[in],cx,cy,0);
				frameCount++;
				if(frameCount>=frameDelay){
					frameCount = 0;
					in++;
					if(in>=2){
						in = 0;
					}
				}
			}
		}
};
ALLEGRO_BITMAP* Coin::coin[3] = {NULL, NULL, NULL};
