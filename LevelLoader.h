#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "Brick.h"
#include "Interrogation.h"
#include "Coin.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Grada.h"
#include "Tubo.h"
#include "Castle.h"
#include "Flag.h"
#include "PPlant.h"
#include "Platform.h"
#include "Plat.h"
#include "Lava.h"
#include "Bbridge.h"
#include "Bridge.h"
#include "Hacha.h"
#include "Bowser.h"
#include "filaFuego.h"
#include "Cheep.h"
#include "Blooper.h"
#include "cBlock.h"
#include "HammerBros.h"
#include "LavaBurble.h"
#include "Lakitu.h"
#include "BillBlaster.h"
#include "Toad.h"
#define WARP_DOWN 0
#define WARP_RIGHT 1
#define EXIT_DOWN 0
#define EXIT_RIGHT 1
class Ground {
public:
    float x, y;
    enum Type { TOP, BOTTOM, CORNER_LEFT_TOP, CORNER_RIGHT_TOP, CORNER_LEFT_BOTTOM, CORNER_RIGHT_BOTTOM } type;
    ALLEGRO_BITMAP* sprite;

    Ground(float x_, float y_, Type t, ALLEGRO_BITMAP* spr)
        : x(x_), y(y_), type(t), sprite(spr) {}
};
struct LevelThemeConfig {
    std::string intro;
    std::string main;
    std::string exit;
    std::string bonus;
};
struct Warp {
    int id;               
    int type;             
    int exitType;         
    bool exitAssigned;   
    float x, y;           
    float ex, ey;       
};
struct WarpExit{
	std::string section; 
    float x, y;          
    int type;            
};

class LevelLoader {
public:
    std::vector<Ground*> grounds;
    std::vector<Brick*> bricks;
 	std::vector<Interrogation*> interrogations;
 	std::vector<Goomba*> goombas;
 	std::vector<Koopa*> koopas;
 	std::vector<Grada*> gradas;
 	std::vector<Tubo*> tubos;
 	std::vector<Castle*> castillos;
 	std::vector<Flag*> flags;
 	std::vector<Coin*> coins;
 	std::vector<PPlant*> pplants;
 	std::vector<Platform*> platforms;
 	std::vector<Plat*> plats;
 	std::vector<Lava*> lavas;
 	std::vector<Bbridge*> bbridges;
 	std::vector<Hacha*> hachas;
 	std::vector<Bowser*> bowsers;
 	std::vector<filaFuego*> filafuegos;
 	std::vector<Cheep*> cheeps;
 	std::vector<Blooper*> bloopers;
 	std::vector<Bridge*> bridges;
 	std::vector<cBlock*> cblocks;
 	std::vector<HammerBros*> hammerbros;
 	std::vector<LavaBurble*> lavaburbles;
 	std::vector<Lakitu*> lakitus;
 	std::vector<BillBlaster*> billblasters;
 	std::vector<BulletBill*> bulletbills;
 	std::vector<Toad*> toads;
 	std::vector<Warp> warps;
 	std::vector<WarpExit> detectedExits;
 	std::map<int, std::vector<std::string>> warpConfig;
 	std::vector<ALLEGRO_SAMPLE*> soundtracks;
 	std::map<int, LevelThemeConfig> themeConfig;
 	std::map<std::string, ALLEGRO_SAMPLE*> music;
 	std::map<std::string, ALLEGRO_SAMPLE*> sfx;
 	ALLEGRO_SAMPLE_INSTANCE* currentInstance;
	std::string currentTrack;
	int nextWarpID;
    int tileSize;
	int levelWidth, levelHeight;
	int levelBonusWidth;
	int cases;
	bool bonus;
	float visibleMax;
	float inPosX, inPosY;
	float introStartY;
	float mainStartY;
	float exitStartY;
	float bonusStartY;
	float offsetY;
	int frameCount;
	int frameDelay;
	int ind;
	int actLevel;
	Player* player;
	std::string theme;
    // Sprites
    ALLEGRO_BITMAP *tg, *ug, *crtg, *cltg, *crug, *clug;
	ALLEGRO_BITMAP *clouds;
	ALLEGRO_BITMAP *hills;
	ALLEGRO_BITMAP *Bonus;
	ALLEGRO_BITMAP *underground[7];
	ALLEGRO_BITMAP *waterfalls[8];
	ALLEGRO_BITMAP *castle;
	ALLEGRO_BITMAP *greenhills;
	ALLEGRO_BITMAP *underwaterHills;
	ALLEGRO_BITMAP *pillars;
	ALLEGRO_BITMAP *night;
	ALLEGRO_BITMAP *forest;
	ALLEGRO_BITMAP *mushrooms;
	ALLEGRO_BITMAP *snow;
	ALLEGRO_BITMAP *brownHills;
	ALLEGRO_BITMAP *fortress;
	ALLEGRO_BITMAP *stars[8];
	ALLEGRO_BITMAP *underwater[12];
    LevelLoader(int tile_size = 16){
    	tileSize = tile_size;
    	tg = NULL;
    	ug = NULL;
    	crtg = NULL;
    	cltg = NULL;
    	crug = NULL;
    	clug = NULL;
    	clouds = NULL;
    	hills = NULL;
    	cases = 1;
    	theme = "overworld";
    	bonus = false;
    	visibleMax = 0;
    	nextWarpID = 0;
    	frameCount = 0;
    	frameDelay = 10;
    	player = NULL;
    	ind = 0;
    	themeConfig[1] = {"null", "overworld", "null", "bonus"};
		themeConfig[2] = {"overworld", "underground", "overworld", "bonus"};
		themeConfig[3] = {"null", "waterfalls", "null", "null"};
		themeConfig[4] = {"null", "castle", "null", "null"};
		themeConfig[5] = {"null", "hills","null", "bonus"};
		themeConfig[6] = {"overworld","underwater","overworld","null"};
		themeConfig[7] = {"null", "pillars", "null", "null"};
		themeConfig[8] = {"null", "castle", "null", "null"};
		themeConfig[9] = {"null", "snownight", "null", "bonus"};
		themeConfig[10] =  {"null", "snownight", "null", "bonus"};
		themeConfig[11] =  {"null", "overworldnight", "null", "null"};
		themeConfig[12] = {"null", "castle", "null", "null"};
		themeConfig[13] = {"null", "forest", "null", "null"};
		themeConfig[14] = {"overworld", "underground", "overworld", "bonus"};
		themeConfig[15] = {"null", "mushrooms", "null", "null"};
		themeConfig[16] = {"null", "castle", "null", "null"};
		themeConfig[17] = {"null", "snow", "null", "bonus"};
		themeConfig[18] = {"null", "snow", "null", "null"};
		themeConfig[19] = {"null", "waterfalls", "null", "null"};
		themeConfig[20] = {"null", "castle", "null", "null"};
		themeConfig[21] =  {"null", "overworldnight", "null", "null"};
		themeConfig[22] = {"null", "overworldnight", "null", "null"};
		themeConfig[23] = {"null", "overworldnight", "null", "null"};
		themeConfig[24] = {"null", "castle", "null", "null"};
		themeConfig[25] = {"null", "snow", "null", "bonus"};
		themeConfig[26] = {"overworld","underwater","overworld","null"};
		themeConfig[27] = {"null", "pillars", "null", "null"};
		themeConfig[28] = {"null", "castle", "null", "null"};
		themeConfig[29] = {"null", "overworld", "null", "bonus"};
		themeConfig[30] = {"null", "brownHills", "null", "bonus"};
		themeConfig[31] = {"null", "fortress", "null", "null"};
		themeConfig[32] = {"null", "castle", "null", "null"};
		warpConfig[1] = {"bonus", "main"};
		warpConfig[2] = {"main", "bonus", "exit", "main"};
		warpConfig[5] = {"bonus", "main"};
		warpConfig[6] = {"main", "exit"};
		warpConfig[9] = {"bonus", "main"};
		warpConfig[14] = {"main", "bonus", "exit", "main"};
		warpConfig[17] = {"bonus", "main"};
		warpConfig[25] = {"bonus", "main"};
		warpConfig[26] = {"main", "exit"};
		warpConfig[29] = {"bonus", "main"};
		warpConfig[30] = {"bonus", "main"};
		warpConfig[32] = {"main", "main", "main"};
		currentTrack = "";
		currentInstance = NULL;
	}
    bool loadSprites() {
    	if (theme == "underground" || theme == "bonus") {
            tg = al_load_bitmap("Sprites/utg.png");
            ug = al_load_bitmap("Sprites/uug.png");
            crtg = al_load_bitmap("Sprites/ucrtg.png");
            cltg = al_load_bitmap("Sprites/ucltg.png");
            crug = al_load_bitmap("Sprites/ucrug.png");
            clug = al_load_bitmap("Sprites/uclug.png");
        } else if(theme == "overworld" || theme == "waterfalls" || theme == "hills" || theme == "pillars" || theme == "overworldnight" || theme == "forest" || theme == "mushrooms" || theme == "brownHills" || theme == "fortress"){
            tg = al_load_bitmap("Sprites/tg.png");
            ug = al_load_bitmap("Sprites/ug.png");
            crtg = al_load_bitmap("Sprites/crtg.png");
            cltg = al_load_bitmap("Sprites/cltg.png");
            crug = al_load_bitmap("Sprites/crug.png");
            clug = al_load_bitmap("Sprites/clug.png");
        } else if(theme == "castle"){
        	tg = al_load_bitmap("Sprites/ctg.png");
        	ug = al_load_bitmap("Sprites/cug.png");
            crtg = al_load_bitmap("Sprites/ccrtg.png");
            cltg = al_load_bitmap("Sprites/ccltg.png");
            crug = al_load_bitmap("Sprites/ccrug.png");
            clug = al_load_bitmap("Sprites/cclug.png");
		} else if(theme == "underwater"){
			tg = al_load_bitmap("Sprites/stg.png");
			ug = al_load_bitmap("Sprites/sug.png");
			crtg = al_load_bitmap("Sprites/scrtg.png");
			cltg = al_load_bitmap("Sprites/scltg.png");
			crug = al_load_bitmap("Sprites/ucrug.png");
            clug = al_load_bitmap("Sprites/uclug.png");
		} else if(theme == "snownight" || theme == "snow"){
			tg = al_load_bitmap("Sprites/sstg.png");
			ug = al_load_bitmap("Sprites/ssug.png");
			crtg = al_load_bitmap("Sprites/sscrtg.png");
			cltg = al_load_bitmap("Sprites/sscltg.png");
			crug = al_load_bitmap("Sprites/sscrug.png");
            clug = al_load_bitmap("Sprites/ssclug.png");
		}
        if (!tg || !ug || !crtg || !cltg || !crug || !clug) {
            std::cerr << "Error: No se pudieron cargar todos los bitmaps de tierra.\n";
            return false;
        }
        if(theme == "overworld" || theme == "waterfalls" || theme == "hills" || theme == "pillars" || theme == "overworldnight" || theme == "forest" || theme == "brownHills" || theme == "fortress"){
        	cases = 1;
        	Brick::cbassets();
        	Interrogation::ciassets();
        	Grada::cstassets(cases);
        	Goomba::cgassets();
        	Plat::cplaassets();
        	Tubo::ctassets();
        	Castle::ccassets();
		}else if(theme == "underground" || theme == "bonus"){
			cases = 2;
        	Brick::ucbassets();
        	Interrogation::uciassets();
        	Grada::cstassets(cases);
        	Goomba::ucgassets();
		}else if(theme == "castle"){
			cases = 3;
			Interrogation::cciassets();
			Grada::cstassets(cases);
			Brick::ccbassets();
			Plat::ccplaassets();
			Lava::claassets();
			Tubo::cstassets();
			Goomba::ccgassets();
		}else if(theme == "snownight" || theme == "snow"){
			cases = 1;
        	Brick::cbassets();
        	Interrogation::ciassets();
        	Grada::cstassets(cases);
        	Goomba::cgassets();
        	Plat::cplaassets();
        	Tubo::cstassets();
        	Castle::cscassets();
        	Lava::cslaassets();
		}else if(theme == "mushrooms"){
			cases = 1;
        	Brick::cbassets();
        	Interrogation::ciassets();
        	Grada::cstassets(cases);
        	Goomba::cgassets();
        	Plat::cmplaassets();
        	Tubo::ctassets();
        	Castle::ccassets();
		}
        Koopa::ckassets();
        Flag::cflassets();
        Coin::ccassets();
        PPlant::cppassets();
        Platform::cpassets();
       	Bbridge::cbbassets();
       	Hacha::chhassets();
       	Bowser::cbowassets();
       	filaFuego::cffbassets();
       	Cheep::ccheassets();
       	Blooper::cbloassets();
       	Bridge::cbrassets();
       	cBlock::ccbassets();
       	HammerBros::chbassets();
       	LavaBurble::clbassets();
       	Lakitu::clakassets();
       	BillBlaster::cbblassets();
       	Toad::ctoassets();
        return true;
    }
    void updateGroundSprites() {
    for (int i = 0; i < (int)grounds.size(); i++) {
        Ground* g = grounds[i];
        switch (g->type) {
            case Ground::TOP:
                g->sprite = tg;
                break;
            case Ground::BOTTOM:
                g->sprite = ug;
                break;
            case Ground::CORNER_LEFT_TOP:
                g->sprite = cltg;
                break;
            case Ground::CORNER_RIGHT_TOP:
                g->sprite = crtg;
                break;
            case Ground::CORNER_LEFT_BOTTOM:
                g->sprite = clug;
                break;
            case Ground::CORNER_RIGHT_BOTTOM:
                g->sprite = crug;
                break;
        }
    }
	}
    void loadBackgrounds(){
    	clouds = al_load_bitmap("Fonts/overworldC.png");     
        hills = al_load_bitmap("Fonts/overworldH.png"); 
        Bonus = al_load_bitmap("Fonts/MBonus.png");
        castle = al_load_bitmap("Fonts/castle.png");
        greenhills = al_load_bitmap("Fonts/greenHills.png");
        underwaterHills = al_load_bitmap("Fonts/underwaterHills.png");
        forest = al_load_bitmap("Fonts/overworldE.png");
        pillars = al_load_bitmap("Fonts/pillars.png");
        night = al_load_bitmap("Fonts/night.png");
        mushrooms = al_load_bitmap("Fonts/mushrooms.png");
        snow = al_load_bitmap("Fonts/snow.png");
        brownHills = al_load_bitmap("Fonts/brownHills.png");
        fortress = al_load_bitmap("Fonts/fortress.png");
		for(size_t i=0; i<7; i++){
			std::stringstream str;
            str << "Fonts/" << i + 1 << "underground" << ".png";
            underground[i] = al_load_bitmap(str.str().c_str());
		}
		for(size_t i=0; i<8; i++){
			std::stringstream str;
            str << "Fonts/" << i + 1 << "waterfalls" << ".png";
            waterfalls[i] = al_load_bitmap(str.str().c_str());
		}
		for(size_t i=0; i<12; i++){
			std::stringstream str;
			str << "Fonts/" << i + 1 << "underwater" << ".png";
			underwater[i] = al_load_bitmap(str.str().c_str());
		}
		for(size_t i=0; i<8; i++){
			std::stringstream str;
            str << "Fonts/" << "stars" << i+1 << ".png";
        	stars[i] = al_load_bitmap(str.str().c_str());
		}
    }
	bool fileExists(const std::string& path) {
    std::ifstream f(path.c_str());
    return f.good();
	}
	std::string getSection(float py) {
    if (py < mainStartY) return "intro";
    if (py < exitStartY) return "main";
    if (py < bonusStartY) return "exit";
    return "bonus";
	}
	void loadSFX() {
    	sfx["star"]    = al_load_sample("Sounds/Star.wav");
    	sfx["victory"] = al_load_sample("Sounds/Courseclear.wav");
    	sfx["hurry"]   = al_load_sample("Sounds/Hurry-up.wav");
    	sfx["dead"]    = al_load_sample("Sounds/Lose.wav");
    	sfx["victoryCastle"] = al_load_sample("Sounds/CastleClear.wav");
	}
	void loadSoundtracks(){
  	    music["overworld"]= al_load_sample("Soundtrack/overworld.wav");
    	music["overworldH"]= al_load_sample("Soundtrack/overworldH.wav");
    	music["underground"]= al_load_sample("Soundtrack/underground.wav");
    	music["undergroundH"]= al_load_sample("Soundtrack/undergroundH.wav");
    	music["waterfalls"] = al_load_sample("Soundtrack/overworld.wav");
    	music["waterfallsH"] = al_load_sample("Soundtrack/overworldH.wav");
    	music["hills"] = al_load_sample("Soundtrack/overworld.wav");
    	music["hillsH"] = al_load_sample("Soundtrack/overworldH.wav");
    	music["bonus"] = al_load_sample("Soundtrack/Bonus.wav");
    	music["castle"] = al_load_sample("Soundtrack/castle.wav");
    	music["castleH"] = al_load_sample("Soundtrack/castleH.wav");
    	music["underwater"] = al_load_sample("Soundtrack/underwater.wav");
    	music["underwaterH"] = al_load_sample("Soundtrack/underwaterH.wav");
    	music["pillars"] = al_load_sample("Soundtrack/overworld.wav");
    	music["pillarsH"]= al_load_sample("Soundtrack/overworldH.wav");
    	music["snownight"] = al_load_sample("Soundtrack/overworld.wav");
    	music["snownightH"] = al_load_sample("Soundtrack/overworldH.wav");
    	music["overworldnight"] = al_load_sample("Soundtrack/overworld.wav");
    	music["overworldnightH"] = al_load_sample("Soundtrack/overworldH.wav");
    	music["forest"] = al_load_sample("Soundtrack/overworld.wav");
    	music["forestH"] = al_load_sample("Soundtrack/overworldH.wav");
    	music["mushrooms"] = al_load_sample("Soundtrack/overworld.wav");
    	music["mushroomsH"] = al_load_sample("Soundtrack/overworldH.wav");
    	music["snow"] = al_load_sample("Soundtrack/overworld.wav");
    	music["snowH"] = al_load_sample("Soundtrack/overworldH.wav");
    	music["brownHills"] = al_load_sample("Soundtrack/overworld.wav");
    	music["brownHillsH"] = al_load_sample("Soundtrack/overworldH.wav");
    	currentInstance = al_create_sample_instance(NULL);
    	al_attach_sample_instance_to_mixer(currentInstance, al_get_default_mixer());
	}
	void autoSelectTheme(int world){
    loadSprites();
    updateGroundSprites();
    loadBackgrounds();
    loadSoundtracks();
    playTrack(theme);
	}
	void applyTheme(int level, const std::string& section) {
    std::string newTheme;
    if (section == "intro") newTheme = themeConfig[level].intro;
    else if (section == "main") newTheme = themeConfig[level].main;
    else if (section == "exit") newTheme = themeConfig[level].exit;
    else if (section == "bonus") newTheme = themeConfig[level].bonus;
    if (newTheme != theme) {
        theme = newTheme;
        loadSprites();
        updateGroundSprites();
        applyMusic(theme);
    }
	}
	int sectionHeight(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) return 0;
    std::string line;
    int rows = 0;
    while (std::getline(file, line)) {
        rows++;
    }
    return rows * tileSize;
	}
	int sectionWidth(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) return 0;

    int maxWidth = 0;
    std::string line;

    while (std::getline(file, line)) {
        if ((int)line.length() > maxWidth)
            maxWidth = line.length();
    }

    return maxWidth * tileSize;
	}
	float getSectionBottom(std::string sec) {
    if (sec == "intro") return mainStartY;
    if (sec == "main")  return exitStartY;
    if (sec == "exit")  return bonusStartY;
    if (sec == "bonus") return bonusStartY + 245;
    return 99999;
	}
	float getSectionTop(const std::string& section) {
    if(section == "main") return mainStartY;    
    if(section == "bonus") return bonusStartY; 
    if(section == "intro") return introStartY;  
    if(section == "exit") return exitStartY;    
    return 0.0f;
	}
	void loadSection(const std::string& filename, float offsetY) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) return;
    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        for (int col = 0; col < line.size(); col++) {
            char c = line[col];
            float x = col * tileSize;
            float y = row * tileSize + offsetY;
            loadTile(c, x, y); 
        }
        row++;
    }
	}
    void loadTile(char c, float x, float y) {
                if (c == 't') grounds.push_back(new Ground(x, y, Ground::TOP, tg));
                else if (c == 'u') grounds.push_back(new Ground(x, y, Ground::BOTTOM, ug));
                else if (c == 'L') grounds.push_back(new Ground(x, y, Ground::CORNER_LEFT_TOP, cltg));
                else if (c == 'R') grounds.push_back(new Ground(x, y, Ground::CORNER_RIGHT_TOP, crtg));
                else if (c == 'l') grounds.push_back(new Ground(x, y, Ground::CORNER_LEFT_BOTTOM, clug));
                else if (c == 'r') grounds.push_back(new Ground(x, y, Ground::CORNER_RIGHT_BOTTOM, crug));
 				if (c == 'b') bricks.push_back(new Brick(x,y,1));
 				if (c == '1') interrogations.push_back(new Interrogation(x,y,1));
 				if (c == '2') interrogations.push_back(new Interrogation(x,y,2));
 				if (c == '3') interrogations.push_back(new Interrogation(x,y,3));
 				if (c == '4') interrogations.push_back(new Interrogation(x,y,4));
 				if (c == '5') interrogations.push_back(new Interrogation(x,y,5));
 				if (c == '6') interrogations.push_back(new Interrogation(x,y,6));
 				if (c == 'C') gradas.push_back(new Grada(x,y));
 				if (c == 'o') bricks.push_back(new Brick(x,y,2));
 				if (c == '/') bricks.push_back(new Brick(x,y,3));
 				if (c == '\\') bricks.push_back(new Brick(x,y,4));
				if (c == '|') bricks.push_back(new Brick(x,y,5));
				if (c == ':') bricks.push_back(new Brick(x,y,6));  
 				if (c == 'G') goombas.push_back(new Goomba(x,y));
 				if (c == 'T') koopas.push_back(new Koopa(x,y-8,1));
 				if (c == '´' || c == '-') koopas.push_back(new Koopa(x,y-8,2));
 				if (c == 'F') koopas.push_back(new Koopa(x,y-8,3));
 				if (c == 'S') koopas.push_back(new Koopa(x,y-16,4));
 				if (c == 'M') platforms.push_back(new Platform(x,y));
 				if (c == '[') tubos.push_back(new Tubo(x,y,Tubo::TOP_LEFT));
 				if (c == ']') tubos.push_back(new Tubo(x,y,Tubo::TOP_RIGHT));
 				if (c == '{') tubos.push_back(new Tubo(x+2,y,Tubo::BODY_LEFT));
 				if (c == '}') tubos.push_back(new Tubo(x,y,Tubo::BODY_RIGHT));
 				if (c == 'h') flags.push_back(new Flag(x-8,y-136));
 				if (c == '?') castillos.push_back(new Castle(x-50,y-64,1));
 				if (c == '8') castillos.push_back(new Castle(x-35,y-160,2));
 				if (c == '@') coins.push_back(new Coin(x,y));
 				if (c == 'p') pplants.push_back(new PPlant(x-8,y+24));
 				if (c == '(') tubos.push_back(new Tubo(x,y, Tubo::LAID_TOP_LEFT)); 
				if (c == ')') tubos.push_back(new Tubo(x,y, Tubo::LAID_TOP_RIGHT)); 
				if (c == '&') tubos.push_back(new Tubo(x,y, Tubo::LAID_BASE_LEFT)); 
				if (c == '$') tubos.push_back(new Tubo(x,y, Tubo::LAID_BASE_RIGHT)); 
				if (c == '!') tubos.push_back(new Tubo(x,y, Tubo::LAID_LEFT)); 
				if (c == '¿' || c == '7') tubos.push_back(new Tubo(x,y, Tubo::LAID_RIGHT));
				if (c == 'a') plats.push_back(new Plat(x,y, Plat::TOP_LEFT, 1));
				if (c == 's') plats.push_back(new Plat(x,y, Plat::BODY_LEFT, 1));
				if (c == 'd') plats.push_back(new Plat(x,y, Plat::MIDDLE, 1));
				if (c == 'f') plats.push_back(new Plat(x,y, Plat::BODY_RIGHT, 1));
				if (c == 'g') plats.push_back(new Plat(x,y, Plat::TOP_RIGHT, 1));
				if (c == 'j') plats.push_back(new Plat(x,y, Plat::LEFT_UNDER, 2));
				if (c == 'k') plats.push_back(new Plat(x,y, Plat::MIDDLE_UNDER, 2));
				if (c == 'n') plats.push_back(new Plat(x,y, Plat::RIGHT_UNDER, 2));
				if (c == 'y') bridges.push_back(new Bridge(x,y));
				if (c == '+') lavas.push_back(new Lava(x,y, Lava::LAVA_UP));
				if (c == '*') lavas.push_back(new Lava(x,y, Lava::LAVA_DOWN));
				if (c == 'P') cheeps.push_back(new Cheep(x,y,1));
				if (c == 'q') cheeps.push_back(new Cheep(x,y,2));
				if (c == 'w') cheeps.push_back(new Cheep(x,240,3));
				if (c == 'c') bloopers.push_back(new Blooper(x,y));
				if (c == '^') hammerbros.push_back(new HammerBros(x,y-16));
				if (c == 'Q') lakitus.push_back(new Lakitu(x,y));
				if (c == '~') lavaburbles.push_back(new LavaBurble(x,y));
				if (c == '=') bbridges.push_back(new Bbridge(x,y));
				if (c == 'H') hachas.push_back(new Hacha(x,y));
				if (c == '"') cblocks.push_back(new cBlock(x,y));
				if (c == ';') filafuegos.push_back(new filaFuego(x,y));
				if (c == '9') billblasters.push_back(new BillBlaster(x,y)); 
				if (c == 'O') bulletbills.push_back(new BulletBill(x,y,-1));
				if (c == 'B') bowsers.push_back(new Bowser(x,y-35));
				if( c == 'v') toads.push_back(new Toad(x,y-12));
				if (c == 'm') {inPosX = x; inPosY = y;}
				if (c == 'W') {
					Warp w;
					w.id = nextWarpID++;
					w.type = WARP_DOWN;
					w.x = x;
					w.y = y;
					w.exitAssigned = false;
					warps.push_back(w);
				}
				if(c == '>'){
					Warp w;
    				w.id = nextWarpID++;
    				w.type = WARP_RIGHT;
    				w.x = x;
    				w.y = y;
    				w.exitAssigned = false;
    				warps.push_back(w);
				}
				if(c == '#'){
					WarpExit we;
					we.section = getSection(y);
					we.x = x;
					we.y = y;
					we.type = EXIT_DOWN;
					detectedExits.push_back(we);
				}
				if(c == '<'){
					WarpExit we;
    				we.section = getSection(y);
    				we.x = x;
    				we.y = y;
    				we.type = EXIT_RIGHT;
    				detectedExits.push_back(we);
				}
    }
    void detectWarpSections() {
    for (size_t i = 0; i < detectedExits.size(); i++) {
        WarpExit& we = detectedExits[i];
        we.section = getSection(we.y);  // ahora sí getSection sabe la Y correcta
    }
	}
    void assignWarpExits(int level) {
	    for (size_t i = 0; i < warps.size(); i++) {
        Warp& w = warps[i];
        std::string targetSection = warpConfig[level][i];
        size_t j = 0;
        bool exitFound = false;
        while (j < detectedExits.size() && !exitFound) {
            WarpExit& we = detectedExits[j];
            if (we.section == targetSection && w.type == we.type) {
                w.ex = we.x;
                w.ey = we.y;
                w.exitType = we.type;
                w.exitAssigned = true;
                exitFound = true;
            }
            j++;
        }
        if (!exitFound) {
            std::cerr << "Warning: No se encontró salida para warp " << i << " en sección " << targetSection << "\n";
        }
    }
	}
	void loadFullLevel(int levelNumber){
    autoSelectTheme(levelNumber);
    offsetY = 0;
    levelWidth = 0;
    introStartY = offsetY;
	loadSFX();
    // INTRO
    std::stringstream ssIntro;
    ssIntro << "Levels/level_" << levelNumber << "intro.txt";
    std::string introFile = ssIntro.str();
    if (fileExists(introFile.c_str())) {
        loadSection(introFile, offsetY);
        offsetY += sectionHeight(introFile);
        int w = sectionWidth(introFile);
        if (w > levelWidth) levelWidth = w;
    }
	mainStartY = offsetY;
    // MAIN
    std::stringstream ssMain;
    ssMain << "Levels/level_" << levelNumber << ".txt";
    std::string mainFile = ssMain.str();
    if (fileExists(mainFile.c_str())) {
        loadSection(mainFile, offsetY);
        offsetY += sectionHeight(mainFile);
        int w = sectionWidth(mainFile);
        if (w > levelWidth) levelWidth = w;
    }
	
   
	exitStartY = offsetY;
    // EXIT
    std::stringstream ssExit;
    ssExit << "Levels/level_" << levelNumber << "exit.txt";
    std::string exitFile = ssExit.str();
    if (fileExists(exitFile.c_str())) {
        loadSection(exitFile, offsetY);
        offsetY += sectionHeight(exitFile);
        int w = sectionWidth(exitFile);
        if (w > levelWidth) levelWidth = w;
    }

  

    // BONUS
    std::stringstream ssBonus;
    ssBonus << "Levels/level_" << levelNumber << "bonus.txt";
    std::string bonusFile = ssBonus.str();
    if (fileExists(bonusFile.c_str())) {
    	bonus = true;
        loadSection(bonusFile, offsetY);
        int w = sectionWidth(bonusFile);
        levelBonusWidth = w;
        if (w > levelWidth) levelWidth = w;
    }

    bonusStartY = offsetY;
    levelHeight = offsetY;
	}
    void update(){
    	for (size_t i = 0; i < bricks.size(); i++) {
            bricks[i]->bupdate();
        }
        for (size_t i=0; i<interrogations.size(); i++){
        	interrogations[i]->iupdate();
		}
		for (size_t i=0; i<goombas.size(); i++){
			goombas[i]->gupdate();
		}
		for (size_t i=0; i<koopas.size(); i++){
			koopas[i]->kupdate();
		}
		for(size_t i=0; i<bowsers.size(); i++){
			bowsers[i]->bowupdate();
		}
		for(size_t i=0; i<bloopers.size(); i++){
			bloopers[i]->update();
		}
		for(size_t i=0; i<hammerbros.size(); i++){
			hammerbros[i]->update();
		}
		for(size_t i=0; i<lakitus.size(); i++){
			lakitus[i]->update(player);
		}
		for(size_t i=0; i<billblasters.size(); i++){
			billblasters[i]->update(player);
		}
		for(size_t i=0; i<pplants.size(); i++){
			pplants[i]->pupdate(player);
		}
	}
    void drawBackgrounds(int l) {
 	    if (themeConfig[l].intro == "overworld") {
        if (clouds) al_draw_bitmap(clouds, 0, introStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, introStartY - 25, 0);
        if (hills) al_draw_bitmap(hills, 0, introStartY + 31, 0);
        if (hills) al_draw_bitmap(hills, 1789, introStartY + 31, 0);
    } else if (themeConfig[l].intro == "underground") {
     		for (int i = 0; i < levelWidth; i += 512) {
            al_draw_bitmap(underground[ind], i, introStartY, 0);
			frameCount++;
			if(frameCount>=frameDelay){
				frameCount = 0;
				ind++;
				if(ind>=7){
				ind = 0;
				}
				} 
        }
    } else if (themeConfig[l].intro == "bonus") {
        if (Bonus) al_draw_bitmap(Bonus, 0, introStartY, 0);
    }else if (themeConfig[l].intro == "waterfalls") {
    	if (clouds) al_draw_bitmap(clouds, 0, introStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, introStartY - 25, 0);
        for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(waterfalls[ind], i, introStartY + 87, 0);
				frameCount++;
				if(frameCount>=frameDelay){
					frameCount = 0;
					ind++;
					if(ind>=8){
						ind = 0;
					}
				} 
        }
    }else if (themeConfig[l].intro == "castle") {
    	for (int i = 0; i < levelWidth; i += 512) {
        if (castle) al_draw_bitmap(castle, i, introStartY-32, 0);
    	}
    }else if (themeConfig[l].intro == "hills"){
    	if (clouds) al_draw_bitmap(clouds, 0, introStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, introStartY - 25, 0);
    		for (int i = 0; i < levelWidth; i += 768) {
        if (greenhills) al_draw_bitmap(greenhills, i, introStartY, 0);
    	}
	}else if (themeConfig[l].intro == "underwater"){
		   for (int i = 0; i < levelWidth; i += 256) {
            	al_draw_bitmap(underwater[ind], i, introStartY, 0);
				frameCount++;
				if(frameCount>=frameDelay*10){
					frameCount = 0;
					ind++;
					if(ind>=12){
						ind = 0;
					}
			} 
        }
        for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(underwaterHills, i, introStartY+100, 0); 
        }
	}else if (themeConfig[l].intro == "pillars"){
		if (clouds) al_draw_bitmap(clouds, 0, introStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, introStartY - 25, 0);
		for (int i = 0; i < levelWidth; i += 2301) {
            	al_draw_bitmap(pillars, i, introStartY+26, 0);
		} 
	}else if (themeConfig[l].intro == "snownight"){
		for (int i = 0; i < levelWidth; i += 256) {
        if (night) al_draw_bitmap(night, i, introStartY, 0);
    	}
    	for (int i = 0; i < levelWidth; i += 512) {
            al_draw_bitmap(stars[ind], i, introStartY, 0);
			frameCount++;
			if(frameCount>=frameDelay){
				frameCount = 0;
				ind++;
				if(ind>=7){
				ind = 0;
				}
				} 
        }
	}else if (themeConfig[l].intro == "overworldnight"){
		for (int i = 0; i < levelWidth; i += 256) {
        if (night) al_draw_bitmap(night, i, introStartY, 0);
    	}
	}else if(themeConfig[l].intro == "snow"){
			if (clouds) al_draw_bitmap(clouds, 0, introStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, introStartY - 25, 0);
		    for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(snow, i, introStartY+64, 0); 
        }
	}
    // MAIN
    if (themeConfig[l].main == "overworld") {
        if (clouds) al_draw_bitmap(clouds, 0, mainStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, mainStartY - 25, 0);
        if (hills) al_draw_bitmap(hills, 0, mainStartY + 31, 0);
        if (hills) al_draw_bitmap(hills, 1789, mainStartY + 31, 0);
    } else if (themeConfig[l].main == "underground") {
   		for (int i = 0; i < levelWidth; i += 512) {
            al_draw_bitmap(underground[ind], i, mainStartY, 0);
			frameCount++;
			if(frameCount>=frameDelay){
				frameCount = 0;
				ind++;
				if(ind>=7){
				ind = 0;
				}
				} 
        }
    } else if (themeConfig[l].main == "bonus") {
        if (Bonus) al_draw_bitmap(Bonus, 0, mainStartY, 0);
    }else if (themeConfig[l].main == "waterfalls") {
    	if (clouds) al_draw_bitmap(clouds, 0, mainStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, mainStartY - 25, 0);
        for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(waterfalls[ind], i, mainStartY + 87, 0);
				frameCount++;
				if(frameCount>=frameDelay){
					frameCount = 0;
					ind++;
					if(ind>=8){
						ind = 0;
					}
				} 
        }
    }else if (themeConfig[l].main == "castle") {
    	for (int i = 0; i < levelWidth; i += 512) {
        if (castle) al_draw_bitmap(castle, i, mainStartY-32, 0);
    	}
    }else if (themeConfig[l].main == "hills"){
    	if (clouds) al_draw_bitmap(clouds, 0, mainStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, mainStartY - 25, 0);
    		for (int i = 0; i < levelWidth; i += 768) {
        if (greenhills) al_draw_bitmap(greenhills, i, mainStartY, 0);
    	}
	}else if (themeConfig[l].main == "underwater"){
		   for (int i = 0; i < levelWidth; i += 256) {
            	al_draw_bitmap(underwater[ind], i, mainStartY, 0);
				frameCount++;
				if(frameCount>=frameDelay*10){
					frameCount = 0;
					ind++;
					if(ind>=12){
						ind = 0;
					}
				} 
        }
             for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(underwaterHills, i, mainStartY+108, 0); 
        }
	}else if (themeConfig[l].main == "pillars"){
		if (clouds) al_draw_bitmap(clouds, 0, mainStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, mainStartY - 25, 0);
		for (int i = 0; i < levelWidth; i += 2301) {
            	al_draw_bitmap(pillars, i, mainStartY+26, 0);
		} 
	}else if (themeConfig[l].main == "snownight"){
		for (int i = 0; i < levelWidth; i += 256) {
        if (night) al_draw_bitmap(night, i, mainStartY, 0);
    	}
    	for (int i = 0; i < levelWidth; i += 512) {
            al_draw_bitmap(stars[ind], i, mainStartY, 0);
			frameCount++;
			if(frameCount>=frameDelay*10){
				frameCount = 0;
				ind++;
				if(ind>=7){
				ind = 0;
				}
				} 
        }
	}else if (themeConfig[l].main == "overworldnight"){
		for (int i = 0; i < levelWidth; i += 256) {
        if (night) al_draw_bitmap(night, i, mainStartY, 0);
    	}
    	for (int i = 0; i < levelWidth; i += 512) {
            al_draw_bitmap(stars[ind], i, mainStartY, 0);
			frameCount++;
			if(frameCount>=frameDelay*10){
				frameCount = 0;
				ind++;
				if(ind>=7){
				ind = 0;
				}
				} 
        }
    }else if(themeConfig[l].main == "forest"){
    	if (clouds) al_draw_bitmap(clouds, 0, mainStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, mainStartY - 25, 0);
        if (forest) al_draw_bitmap(forest, 0, mainStartY + 47, 0);
        if (forest) al_draw_bitmap(forest, 1534, mainStartY + 46, 0);
        if (forest) al_draw_bitmap(forest, 3068, mainStartY + 40, 0);
	}else if(themeConfig[l].main == "mushrooms"){
		if (clouds) al_draw_bitmap(clouds, 0, mainStartY, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, mainStartY, 0);
        if (mushrooms) al_draw_bitmap(mushrooms, 0, mainStartY+24, 0);
        if (mushrooms) al_draw_bitmap(mushrooms, 1534, mainStartY+24, 0);
	}else if(themeConfig[l].main == "snow"){
		if (clouds) al_draw_bitmap(clouds, 0, mainStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, mainStartY - 25, 0);
		    for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(snow, i, mainStartY+84, 0); 
        }
	}else if(themeConfig[l].main == "brownHills"){
		if (clouds) al_draw_bitmap(clouds, 0, mainStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, mainStartY - 25, 0);
		    for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(brownHills, i, mainStartY+118, 0); 
        }
	}else if(themeConfig[l].main == "fortress"){
		if (clouds) al_draw_bitmap(clouds, 0, mainStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, mainStartY - 25, 0);
		    for (int i = 0; i < levelWidth; i += 2301) {
            	al_draw_bitmap(fortress, i, mainStartY+34, 0); 
        }
	}

    // EXIT
    if (themeConfig[l].exit == "overworld") {
        if (clouds) al_draw_bitmap(clouds, 0, exitStartY, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, exitStartY, 0);
        if (hills) al_draw_bitmap(hills, 0, exitStartY + 31, 0);
        if (hills) al_draw_bitmap(hills, 1789, exitStartY + 31, 0);
    } else if (themeConfig[l].exit == "underground") {
       		for (int i = 0; i < levelWidth; i += 512) {
            al_draw_bitmap(underground[ind], i, exitStartY, 0);
			frameCount++;
			if(frameCount>=frameDelay){
				frameCount = 0;
				ind++;
				if(ind>=7){
				ind = 0;
				}
				} 
        }
    } else if (themeConfig[l].exit == "bonus") {
        if (Bonus) al_draw_bitmap(Bonus, 0, exitStartY, 0);
    }else if (themeConfig[l].exit == "waterfalls") {
   	  	if (clouds) al_draw_bitmap(clouds, 0, exitStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, exitStartY - 25, 0);
        for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(waterfalls[ind], i, exitStartY + 87, 0);
				frameCount++;
				if(frameCount>=frameDelay){
					frameCount = 0;
					ind++;
					if(ind>=8){
						ind = 0;
					}
				} 
        }
    }else if (themeConfig[l].exit == "castle") {
    	for (int i = 0; i < levelWidth; i += 512) {
        if (castle) al_draw_bitmap(castle, i, exitStartY-32, 0);
    	}
    }else if (themeConfig[l].exit == "hills"){
    	if (clouds) al_draw_bitmap(clouds, 0, exitStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, exitStartY - 25, 0);
    		for (int i = 0; i < levelWidth; i += 768) {
        if (greenhills) al_draw_bitmap(greenhills, i, exitStartY, 0);
    	}
	}else if (themeConfig[l].exit == "underwater"){
		   for (int i = 0; i < levelWidth; i += 256) {
            	al_draw_bitmap(underwater[ind], i, exitStartY, 0);
				frameCount++;
				if(frameCount>=frameDelay*10){
					frameCount = 0;
					ind++;
					if(ind>=12){
						ind = 0;
					}
				} 
        }
             for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(underwaterHills, i, exitStartY+108, 0); 
        }
	}else if (themeConfig[l].exit == "pillars"){
		if (clouds) al_draw_bitmap(clouds, 0, exitStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, exitStartY - 25, 0);
		for (int i = 0; i < levelWidth; i += 2301) {
            	al_draw_bitmap(pillars, i, exitStartY, 0);
		} 
	}else if (themeConfig[l].exit == "snownight"){
		for (int i = 0; i < levelWidth; i += 256) {
        if (night) al_draw_bitmap(night, i, exitStartY, 0);
    	}
    	for (int i = 0; i < levelWidth; i += 512) {
            al_draw_bitmap(stars[ind], i, exitStartY, 0);
			frameCount++;
			if(frameCount>=frameDelay){
				frameCount = 0;
				ind++;
				if(ind>=7){
				ind = 0;
				}
				} 
        }
	}else if (themeConfig[l].exit == "overworldnight"){
		for (int i = 0; i < levelWidth; i += 256) {
        if (night) al_draw_bitmap(night, i, exitStartY, 0);
    	}
    }
    // BONUS
    if (themeConfig[l].bonus == "overworld") {
        if (clouds) al_draw_bitmap(clouds, 0, bonusStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, bonusStartY - 25, 0);
        if (hills) al_draw_bitmap(hills, 0, bonusStartY + 31, 0);
        if (hills) al_draw_bitmap(hills, 1789, bonusStartY + 31, 0);
    } else if (themeConfig[l].bonus == "underground") {
     	for (int i = 0; i < levelWidth; i += 512) {
            al_draw_bitmap(underground[ind], i, bonusStartY, 0);
			frameCount++;
			if(frameCount>=frameDelay){
				frameCount = 0;
				ind++;
				if(ind>=7){
				ind = 0;
				}
				} 
        }
    } else if (themeConfig[l].bonus == "bonus") {
        if (Bonus) al_draw_bitmap(Bonus, 0, bonusStartY, 0);
    }else if (themeConfig[l].bonus == "waterfalls") {
		if (clouds) al_draw_bitmap(clouds, 0, bonusStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, bonusStartY - 25, 0);
        for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(waterfalls[ind], i, bonusStartY + 87, 0);
				frameCount++;
				if(frameCount>=frameDelay){
					frameCount = 0;
					ind++;
					if(ind>=8){
						ind = 0;
					}
			} 
        }
    }else if (themeConfig[l].bonus == "castle") {
    	for (int i = 0; i < levelWidth; i += 512) {
        if (castle) al_draw_bitmap(castle, i, bonusStartY-32, 0);
    	}
    }else if (themeConfig[l].bonus == "hills"){
    	if (clouds) al_draw_bitmap(clouds, 0, bonusStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, bonusStartY - 25, 0);
    		for (int i = 0; i < levelWidth; i += 768) {
        if (greenhills) al_draw_bitmap(greenhills, i, bonusStartY, 0);
    	}
	}else if (themeConfig[l].bonus == "underwater"){
		   for (int i = 0; i < levelWidth; i += 256) {
            	al_draw_bitmap(underwater[ind], i, bonusStartY, 0);
				frameCount++;
				if(frameCount>=frameDelay*10){
					frameCount = 0;
					ind++;
					if(ind>=12){
						ind = 0;
					}
				} 
        }
             for (int i = 0; i < levelWidth; i += 1000) {
            	al_draw_bitmap(underwaterHills, i, bonusStartY, 0); 
        }
	}else if (themeConfig[l].bonus == "pillars"){
		if (clouds) al_draw_bitmap(clouds, 0, bonusStartY - 25, 0);
        if (clouds) al_draw_bitmap(clouds, 3070, bonusStartY - 25, 0);
		for (int i = 0; i < levelWidth; i += 2301) {
            	al_draw_bitmap(pillars, i, bonusStartY, 0);
		} 
	}else if (themeConfig[l].bonus == "snownight"){
		for (int i = 0; i < levelWidth; i += 256) {
        if (night) al_draw_bitmap(night, i, bonusStartY, 0);
    	}
    	for (int i = 0; i < levelWidth; i += 512) {
            al_draw_bitmap(stars[ind], i, bonusStartY, 0);
			frameCount++;
			if(frameCount>=frameDelay){
				frameCount = 0;
				ind++;
				if(ind>=7){
				ind = 0;
				}
				} 
        }
	}else if (themeConfig[l].bonus == "overworldnight"){
		for (int i = 0; i < levelWidth; i += 256) {
        if (night) al_draw_bitmap(night, i, bonusStartY, 0);
    	}
	}
    }
	void playTrack(std::string& trackName) {
		if (currentTrack == trackName) return;
		al_stop_sample_instance(currentInstance);
		al_set_sample(currentInstance, music[trackName]);
		al_set_sample_instance_playmode(currentInstance, ALLEGRO_PLAYMODE_LOOP);
		al_play_sample_instance(currentInstance);
		currentTrack = trackName;
    }
    void stopTrack() {
    al_stop_sample_instance(currentInstance);
    currentTrack = "";
	}
    void applyMusic(std::string& theme){
    if (theme == "overworld") {
        playTrack(theme);
    }
    else if (theme == "underground") {
        playTrack(theme);
    }else if(theme == "bonus"){
    	playTrack(theme);
	}else if(theme == "waterfalls"){
		playTrack(theme);
	}else if(theme == "castle"){
		playTrack(theme);
	}else if(theme == "hills"){
		playTrack(theme);
	}else if(theme == "underwater"){
		playTrack(theme);
	}else if(theme == "pillars"){
		playTrack(theme);
	}else if(theme == "snownight"){
		playTrack(theme);
	}else if(theme == "overworldnight"){
		playTrack(theme);
	}
	}
    void draw() {
    	for(size_t i = 0; i<billblasters.size(); i++){
        	BillBlaster* bbl = billblasters[i];
        	bbl->draw();
		}
        for (size_t i = 0; i < grounds.size(); i++) {
            Ground* g = grounds[i];
            al_draw_bitmap(g->sprite, g->x, g->y, 0);
        }
        for(size_t i = 0; i<bricks.size(); i++){
        	Brick* b = bricks[i];
        	b->bdraw();
		}
		for(size_t i=0; i<interrogations.size(); i++){
			Interrogation* in = interrogations[i];
			in->idraw();
		}
		for (size_t i=0; i<goombas.size(); i++){
			Goomba* g = goombas[i];
			g->gdraw();
		}
		for (size_t i=0; i<koopas.size(); i++){
			Koopa* k = koopas[i];
			k->kdraw();
		}
		for(size_t i=0; i<gradas.size(); i++){
			Grada* gr = gradas[i];
			gr->stdraw();
		}
		for(size_t i=0; i<pplants.size(); i++){
			PPlant* pp = pplants[i];
			pp->ppdraw();
		}
		for(size_t i=0; i<tubos.size(); i++){
			Tubo* t = tubos[i];
			t->tdraw();
		}
		for(size_t i=0; i<castillos.size(); i++){
			Castle* c = castillos[i];
			c->cdraw();
		}
		for(size_t i=0; i<flags.size(); i++){
			Flag* f = flags[i];
			f->fldraw();
		}
		for(size_t i=0; i<coins.size(); i++){
			Coin* co = coins[i];
			co->cdraw();
		}
		for(size_t i=0; i<platforms.size(); i++){
			Platform* p = platforms[i];
			p->pdraw();
		}
		for(size_t i=0; i<plats.size(); i++){
			Plat *pl = plats[i];
			pl->pladraw();
		}
		for(size_t i=0; i<bowsers.size(); i++){
			Bowser* bow = bowsers[i];
			bow->bowdraw();
		}
		for(size_t i=0; i<lavaburbles.size(); i++){
			LavaBurble* lb = lavaburbles[i];
			lb->draw();
		}
		for(size_t i=0; i<lavas.size(); i++){
			Lava *la = lavas[i];
			la->ladraw();
		}
		for(size_t i=0; i<bbridges.size(); i++){
			Bbridge *bb = bbridges[i];
			bb->bbdraw();
		}
		for(size_t i=0; i<hachas.size(); i++){
			Hacha* hh = hachas[i];
			hh->hhdraw();
		}
		for(size_t i=0; i<cblocks.size();i++){
			cBlock* ccb = cblocks[i];
			ccb->cbdraw();
		}
		for(size_t i=0; i<filafuegos.size(); i++){
			filaFuego* fl = filafuegos[i];
			fl->ffbdraw();
		}
		for(size_t i=0; i<cheeps.size(); i++){
			Cheep* che = cheeps[i];
			che->chdraw();
		}
		for(size_t i=0; i<bloopers.size(); i++){
			Blooper* bloo = bloopers[i];
			bloo->bloodraw();
		}
		for(size_t i=0; i<bridges.size(); i++){
			Bridge* brid = bridges[i];
			brid->draw();
		}
		for(size_t i=0; i<hammerbros.size(); i++){
			HammerBros* hb = hammerbros[i];
			hb->hbdraw();
		}
		for(size_t i=0; i<lakitus.size(); i++){
			Lakitu* lak = lakitus[i];
			lak->draw();
		}
		for(size_t i=0; i<bulletbills.size(); i++){
			BulletBill* bbi = bulletbills[i];
			bbi->draw();
		}
		for(size_t i=0; i<toads.size(); i++){
			Toad* bt = toads[i];
			bt->draw();
		}
    }
    void destroy() {
        for (size_t i = 0; i < grounds.size(); i++)
            delete grounds[i];
        grounds.clear();
        for (size_t i=0; i < bricks.size(); i++)
        	delete bricks[i];
        bricks.clear();
        for (size_t i=0; i < interrogations.size(); i++)
        	delete interrogations[i];
        interrogations.clear();
        for (size_t i = 0; i < goombas.size(); i++)
            delete goombas[i];
        goombas.clear();
        for (size_t i=0; i < koopas.size(); i++)
        	delete koopas[i];
        koopas.clear();
        for (size_t i=0; i < gradas.size(); i++)
        	delete gradas[i];
        gradas.clear();
        for (size_t i=0; i < tubos.size(); i++)
        	delete tubos[i];
        tubos.clear();
        for (size_t i=0; i < castillos.size(); i++)
        	delete castillos[i];
        castillos.clear();
        for (size_t i=0; i < flags.size(); i++)
        	delete flags[i];
        flags.clear();
        for (size_t i=0; i<coins.size(); i++)
        	delete coins[i];
        coins.clear();
         for (size_t i=0; i<pplants.size(); i++)
        	delete pplants[i];
        pplants.clear();
           for (size_t i=0; i<platforms.size(); i++)
        	delete platforms[i];
        platforms.clear();
        for (size_t i=0; i<plats.size(); i++)
        	delete plats[i];
        plats.clear();
        for (size_t i=0; i<lavas.size(); i++)
        	delete lavas[i];
        lavas.clear();
        for (size_t i=0; i<bbridges.size(); i++)
        	delete bbridges[i];
        bbridges.clear();
        for (size_t i=0; i<hachas.size(); i++)
        	delete hachas[i];
        hachas.clear();
         for (size_t i=0; i<bowsers.size(); i++)
        	delete bowsers[i];
        bowsers.clear();
        for (size_t i=0; i<filafuegos.size(); i++)
        	delete filafuegos[i];
        filafuegos.clear();
        for (size_t i=0; i<cheeps.size(); i++)
        	delete cheeps[i];
        cheeps.clear();
        for (size_t i=0; i<bloopers.size(); i++)
        	delete bloopers[i];
        bloopers.clear();
        for (size_t i=0; i<bridges.size(); i++)
        	delete bridges[i];
        bridges.clear();
        for (size_t i=0; i<cblocks.size(); i++)
        	delete cblocks[i];
        cblocks.clear();
        for (size_t i=0; i<hammerbros.size(); i++)
        	delete hammerbros[i];
        hammerbros.clear();
        for (size_t i=0; i<lavaburbles.size(); i++)
        	delete lavaburbles[i];
        lavaburbles.clear();
        for (size_t i=0; i<lakitus.size(); i++)
        	delete lakitus[i];
        lakitus.clear();
        for (size_t i=0; i<billblasters.size(); i++){
        	delete billblasters[i];
		}
		billblasters.clear();
		for (size_t i=0; i<bulletbills.size(); i++){
        	delete bulletbills[i];
		}
		bulletbills.clear();
		for(size_t i=0; i<toads.size(); i++){
			delete toads[i];
		}
		toads.clear();
        if (tg) al_destroy_bitmap(tg);
        if (ug) al_destroy_bitmap(ug);
        if (crtg) al_destroy_bitmap(crtg);
        if (cltg) al_destroy_bitmap(cltg);
        if (crug) al_destroy_bitmap(crug);
        if (clug) al_destroy_bitmap(clug);
        if (clouds) al_destroy_bitmap(clouds);
        if (hills) al_destroy_bitmap(hills);
    }
    ~LevelLoader() {
        destroy();
    }
};
