//Clase GROUND
#include <iostream>
class Ground {
public:
    enum Type { TOP, BOTTOM, CORNER_LEFT_TOP, CORNER_RIGHT_TOP, CORNER_LEFT_BOTTOM, CORNER_RIGHT_BOTTOM };
    float x, y;
    Type type;

    static ALLEGRO_BITMAP* tg;
    static ALLEGRO_BITMAP* ug;
    static ALLEGRO_BITMAP* crtg;
    static ALLEGRO_BITMAP* cltg;
    static ALLEGRO_BITMAP* crug;
    static ALLEGRO_BITMAP* clug;
    Ground(float x_, float y_, Type t) : x(x_), y(y_), type(t) {}

    static bool loadAssets() {
        tg = al_load_bitmap("Sprites/tg.png");
        ug = al_load_bitmap("Sprites/ug.png");
        crtg = al_load_bitmap("Sprites/crtg.png");
        cltg = al_load_bitmap("Sprites/cltg.png");
        crug = al_load_bitmap("Sprites/crug.png");
        clug = al_load_bitmap("Sprites/clug.png");

        if (!tg || !ug || !crtg || !cltg || !crug || !clug) {
            std::cerr << "Error: no se pudieron cargar los sprites de Ground.\n";
            return false;
        }
        return true;
    }

    static void destroyAssets() {
        if (tg) al_destroy_bitmap(tg);
        if (ug) al_destroy_bitmap(ug);
        if (crtg) al_destroy_bitmap(crtg);
        if (cltg) al_destroy_bitmap(cltg);
        if (crug) al_destroy_bitmap(crug);
        if (clug) al_destroy_bitmap(clug);

        tg = 0;
        ug = 0;
        crtg = 0;
        cltg = 0;
        crug = 0;
        clug = 0;
    }

    void draw() {
        ALLEGRO_BITMAP* bmp = 0;
        switch(type) {
            case TOP: bmp = tg; break;
            case BOTTOM: bmp = ug; break;
            case CORNER_LEFT_TOP: bmp = cltg; break;
            case CORNER_RIGHT_TOP: bmp = crtg; break;
            case CORNER_LEFT_BOTTOM: bmp = clug; break;
            case CORNER_RIGHT_BOTTOM: bmp = crug; break;
        }
        if (bmp)
            al_draw_bitmap(bmp, x, y, 0); // dibuja absoluto, sin cámara
    }
};

