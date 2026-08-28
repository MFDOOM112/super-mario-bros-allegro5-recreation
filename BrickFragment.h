//Fragmentos de ladrillo, animación
class BrickFragment{
	public:
    float x, y;
    float vx, vy;
    float gravity;
    bool active;
    ALLEGRO_BITMAP* sprite;

    BrickFragment(float ix, float iy, float ivx, float ivy, ALLEGRO_BITMAP* img) {
        x = ix;
        y = iy;
        vx = ivx;
        vy = ivy;
        gravity = 0.5;
        sprite = img;
        active = true;
    }

    void update() {
        if (!active) return;
        x += vx;
        y += vy;
        vy += gravity;
        if (y > 600) active = false; // cae fuera de pantalla
    }

    void draw() {
        if (active) al_draw_bitmap(sprite, x, y, 0);
    }
};
