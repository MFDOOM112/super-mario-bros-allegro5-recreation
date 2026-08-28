//Clase Hongo
//Clase Hongo
class Hongo {
public:
    float hx, hy;
    float gravityh;
    float hspeed;
    float vspeed;
    float yemerg;
    bool hjump;
    bool hactive;
    bool canBeEaten;
    bool emerging;
    int direction; 
    ALLEGRO_BITMAP *hmov;

    //Constructor
    Hongo(float ihx, float ihy) {
        hx = ihx;
        hy = ihy;
        hspeed = 1.2f;       
        vspeed = 0.0f;
        gravityh = 0.35f;    
        yemerg = ihy - 16;
        hjump = false;
        hactive = false;
        canBeEaten = false;
        emerging = false;
        direction = 1;       
    }

    //Métodos
    void chassets() {
        hmov = al_load_bitmap("Sprites/h.png");
    }

    void deshassets() {
        al_destroy_bitmap(hmov);
    }

    void hupdate() {
        if (emerging) {
            hy -= 1.2f; 
            if (hy <= yemerg) {
                emerging = false;
                hactive = true;
                canBeEaten = true;
                vspeed = 0;
                hjump = false;
            }
            return;
        }

        if (!hactive) return;
        if (!hjump) {
            vspeed += gravityh;     
            if (vspeed > 5.0f) vspeed = 5.0f;
        } else {
            vspeed = 0;
        }
        hx += hspeed * direction;
        hy += vspeed;
        if (!hjump) {
            hx += 0.3f * direction;
        }
    }

    void hdraw() {
        if (hactive || emerging) {
            al_draw_bitmap(hmov, hx, hy, 0);
        }
    }
    void changeDirection() {
        direction *= -1;
    }
    void landOn(float groundY) {
        hy = groundY - 16; 
        vspeed = 0;
        hjump = true;
    }
};
