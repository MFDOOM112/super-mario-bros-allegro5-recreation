//Clase vida extra
class VidaExtra{
	public:
		float vx,vy;
		float gravityv;
		float yemerg;
		float hspeed;
		float vspeed;
		int direction; 
		bool vjump;
		bool vactive;
		bool canBeEaten;
		bool emerging;
		ALLEGRO_BITMAP *vmov;
		//Constructor
		VidaExtra(float ihx, float ihy){
			vx = ihx;
			vy = ihy;
			hspeed = 1.2f;       
        	vspeed = 0.0f;
        	gravityv = 0.35f; 
			vjump = false;
			vactive = false;
			canBeEaten = false;
    		emerging = false;
    		yemerg = ihy-16;
    		direction = 1;
		}
		//Métodos
		void cvassets(){
			vmov = al_load_bitmap("Sprites/v.png");
		}
		void desvassets(){
			al_destroy_bitmap(vmov);
		}
		void vupdate(){
		if (emerging) {
            vy -= 1.2f; 
            if (vy <= yemerg) {
                emerging = false;
                vactive = true;
                canBeEaten = true;
                vspeed = 0;
                vjump = false;
            }
            return;
        }
        if (!vactive) return;
        if (!vjump) {
            vspeed += gravityv;     
            if (vspeed > 5.0f) vspeed = 5.0f;
        } else {
            vspeed = 0;
        }
        vx += hspeed * direction;
        vy += vspeed;
        if (!vjump) {
            vx += 0.3f * direction;
        }
		}
		void vdraw(){
		if(vactive || emerging){
			al_draw_bitmap(vmov, vx, vy, 0);	
		}
		}
		void changeDirection() {
        direction *= -1;
    }
    void landOn(float groundY) {
        vy = groundY - 16; 
        vspeed = 0;
        vjump = true;
    }	
};
