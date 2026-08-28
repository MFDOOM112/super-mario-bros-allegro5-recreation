//Clase HUD
#include<string>
#include<sstream>
class Hud{
	public:
		ALLEGRO_BITMAP *Player_icon;
		ALLEGRO_BITMAP *T_coin[3];
		ALLEGRO_BITMAP *Time;
		ALLEGRO_BITMAP *levelPreview;
		ALLEGRO_FONT* font;
		int totalcoins;
		int tlives;
		int frameCount;
		int frameDelay;
		int in;
		std::string icon;
		std::string levelImageName;
	//Constructor
	Hud(std::string character, int timer){
		icon = character;
		frameCount = 0;
		frameDelay = 10;
		in = 0;
	}
	//Métodos
	void loadFont(){
		font = al_load_ttf_font("HUD/PressStart2P-Regular.ttf", 16, 0);
		if (!font) {
        std::cerr << "No se pudo cargar la fuente!\n";
    	}
	}
	void cHudassets(){
		Player_icon = al_load_bitmap(("HUD/" + icon + "icon.png").c_str());
		Time = al_load_bitmap("HUD/time.png");
		for(int i=0;i<3;i++){
			std::stringstream str;
            str << "HUD/" <<i + 1<<"tcoin"<<".png";
            T_coin[i] = al_load_bitmap(str.str().c_str());
		}
	}
	void loadLevelPreview(const std::string& levelID) {
    levelImageName = "HUD/" + levelID + ".png";
    levelPreview = al_load_bitmap(levelImageName.c_str());
    if (!levelPreview) {
        std::cerr << "No se pudo cargar preview del nivel: " << levelImageName << "\n";
    }
	}
	void drawLevelIntro(int baseWidth, int baseHeight, int lives) {
    float scale = baseWidth / 256.0f;
    int centerX = baseWidth / 2;
    int centerY = baseHeight / 2;
    int iconSize = int(19 * scale);
    int iconY = centerY + 5;
    if (Player_icon) {
        al_draw_scaled_bitmap(Player_icon, 0, 0, al_get_bitmap_width(Player_icon), al_get_bitmap_height(Player_icon), centerX - iconSize - 10, iconY-20, iconSize, iconSize, 0);
    }
    std::stringstream ssLives;
    ssLives << "x " << lives;
    al_draw_text(font, al_map_rgb(0,0,0), centerX + 2, iconY -20+2, 0, ssLives.str().c_str());
    al_draw_text(font, al_map_rgb(255,255,255), centerX + 1, iconY-20, 0, ssLives.str().c_str());
    if (levelPreview) {
        int prevW = al_get_bitmap_width(levelPreview);
        int prevH = al_get_bitmap_height(levelPreview);
        int previewY = centerY + 40;
        int scaledW = int(prevW * scale);
        int scaledH = int(prevH * scale);
        al_draw_scaled_bitmap(levelPreview, 0,0, prevW, prevH, centerX - scaledW/2, previewY-20, scaledW, scaledH, 0);
    }
	}
	void drawHud(int baseWidth, int baseHeight, int lives, int tcoins, int timer) {
	totalcoins = tcoins;
	tlives = lives;
    float scale = baseWidth / 256.0f; 
    int padding = int(6 * scale);     
    int fontSpacing = int(14 * scale); 
    int iconSize = int(10 * scale);   
    int coinSize = int(5 * scale);  
    std::string characterName = (icon == "m") ? "MARIO" : (icon == "l") ? "LUIGI" : "PLAYER";
    al_draw_text(font, al_map_rgb(0,0,0), padding+103, padding+1, 0, characterName.c_str());
    al_draw_text(font, al_map_rgb(255,255,255), padding+105, padding, 0, characterName.c_str());
    if (Player_icon) {
        al_draw_scaled_bitmap(Player_icon, 0, 0,al_get_bitmap_width(Player_icon), al_get_bitmap_height(Player_icon), padding+100, padding + fontSpacing -8, iconSize, iconSize, 0);
    }
    std::stringstream ssLives;
    ssLives << "x " << tlives;
    al_draw_text(font, al_map_rgb(0,0,0), padding + iconSize + 103, padding + fontSpacing + 2, 0, ssLives.str().c_str());
    al_draw_text(font, al_map_rgb(255,255,255), padding + iconSize + 105, padding + fontSpacing, 0, ssLives.str().c_str());
    int coinX = baseWidth / 2 - coinSize / 2;
    al_draw_scaled_bitmap(T_coin[in], 0, 0, al_get_bitmap_width(T_coin[0]), al_get_bitmap_height(T_coin[0]), coinX, padding + fontSpacing/2+20, coinSize, coinSize, 0);
    frameCount++;
	if(frameCount>=frameDelay){
		frameCount = 0;
		in++;
		if(in>=3){
		in = 0;
		}
	}
    al_draw_text(font, al_map_rgb(0,0,0), coinX+1, padding + fontSpacing/2 - 17, 0, "COINS");
    al_draw_text(font, al_map_rgb(255,255,255), coinX, padding + fontSpacing/2 - 19, 0, "COINS");
    std::stringstream ssCoins;
    ssCoins << "x "<<totalcoins;
    al_draw_text(font, al_map_rgb(0,0,0), coinX + coinSize + 19, padding + fontSpacing/2 +20, 0, ssCoins.str().c_str());
    al_draw_text(font, al_map_rgb(255,255,255), coinX + coinSize + 22, padding + fontSpacing/2+20, 0, ssCoins.str().c_str());
    int timeX = baseWidth - padding - 50;
    al_draw_text(font, al_map_rgb(0,0,0), timeX-89, padding + fontSpacing/2 - 17, 0, "TIME");
    al_draw_text(font, al_map_rgb(255,255,255), timeX-91, padding + fontSpacing/2 - 19, 0, "TIME");

    std::stringstream ssTime;
    ssTime << timer;
    al_draw_text(font, al_map_rgb(0,0,0), timeX -83, padding + fontSpacing/2 + 10, 0, ssTime.str().c_str());
    al_draw_text(font, al_map_rgb(255,255,255), timeX-85, padding + fontSpacing/2+12, 0, ssTime.str().c_str());
}

};
