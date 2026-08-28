//Clase llama
class Llama{
	public:
		float x,y;
		int in;
		int frameCount;
		int frameDelay;
		static ALLEGRO_BITMAP* llama[3];
	//Constructor
	Llama(float inx, float iny){
		x = inx;
		y = iny;
		frameCount = 0;
		frameDelay = 10;
		in = 0;
	}
	//Métodos
	static void cllassets(){
		for (int i=0; i<3; i++){
        	std::stringstream str;
        	str << "Sprites/" << i + 1 << "llama.png";
        	llama[i] = al_load_bitmap(str.str().c_str());
		}
	}
	static void dllassets(){
		for (int i=0; i<3; i++){
			al_destroy_bitmap(llama[i]);
		}
	}
	void lldraw(){
		al_draw_bitmap(llama[in], x, y, 0);
		x-=1.7;
		frameCount++;
		if(frameCount>=frameDelay){
			frameCount = 0;
			in++;
			if(in>=3) in = 0;
		}
	}
};
ALLEGRO_BITMAP* Llama::llama[3] = {NULL, NULL, NULL};
