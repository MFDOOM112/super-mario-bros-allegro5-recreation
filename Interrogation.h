// CLASE BLOQUE DE INTERROGACIÓN!!!!
class Interrogation {
public:
    float ix, iy, iiiy;
    float icx,icy;
	float jumpOffset;
    bool movingUp;
    bool iactive;
    bool coinup;
    bool ucactive;
    int in;
    int inc;
    int frameDelaycoin;
    int frameCountcoin;
    int frameDelay;
    int frameCount;
    int Case;
    Hongo *hongo;
    Flor *flor;
    Star *estrella;
    VidaExtra *vida;
    bool mushup;
    bool onlyOne;
    static ALLEGRO_BITMAP *interrogation[4];
    static ALLEGRO_BITMAP *uCoin[9];
    static ALLEGRO_SAMPLE *iCoin;
    static ALLEGRO_SAMPLE *sAppear;

    // Constructor
    Interrogation(float iix, float iiy, int cases) {
        ix = iix;
        iy = iiy;
        icx = iix+3.5;
        icy = iiy-8;
        iiiy = iiy;
        jumpOffset = 0;
        movingUp = false;
        iactive = true;
        ucactive = true;
        in = 0;
        inc = 0;
        frameDelay = 10;
        frameCount = 0;
        frameDelaycoin = 10;
        frameCountcoin = 0;
        Case = cases;
        coinup = false;
        onlyOne = false;
        hongo = NULL;
        flor = NULL;
        estrella = NULL;
        vida = NULL;
        if (Case == 2) {
        hongo = new Hongo(ix, iy);
        hongo->chassets();
        hongo->emerging = false;
    	}
		if(Case == 3){
    	flor = new Flor(ix, iy);
		flor->cfassets();
		flor->emerging = false; 	
		}
		if(Case == 4){
			estrella = new Star(ix, iy);
			estrella->csassets();
			estrella->emerging = false;
		}
		if(Case == 5){
			vida = new VidaExtra(ix,iy);
			vida->cvassets();
			vida->emerging = false;
		}
    }
	//Métodos
    static void ciassets() {
        for (int i=0;i<4; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "i" << ".png";
            interrogation[i] = al_load_bitmap(str.str().c_str());
        }
        for(int j=0;j<9;j++){
        	std::stringstream str;
            str << "Sprites/" <<j+1<<"uc"<<".png";
            uCoin[j] = al_load_bitmap(str.str().c_str());
		}
		iCoin = al_load_sample("Sounds/Coin.wav");
        sAppear = al_load_sample("Sounds/Appear.wav");
    }
	static void uciassets(){
		for (int i=0;i<4; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "ui" << ".png";
            interrogation[i] = al_load_bitmap(str.str().c_str());
        }
        for(int j=0;j<9;j++){
        	std::stringstream str;
            str << "Sprites/" <<j+1<<"uc"<<".png";
            uCoin[j] = al_load_bitmap(str.str().c_str());
		}
		iCoin = al_load_sample("Sounds/Coin.wav");
        sAppear = al_load_sample("Sounds/Appear.wav");
	}
	static void cciassets(){
		for (int i=0;i<4; i++) {
            std::stringstream str;
            str << "Sprites/" << i + 1 << "ci" << ".png";
            interrogation[i] = al_load_bitmap(str.str().c_str());
        }
        for(int j=0;j<9;j++){
        	std::stringstream str;
            str << "Sprites/" <<j+1<<"uc"<<".png";
            uCoin[j] = al_load_bitmap(str.str().c_str());
		}
		iCoin = al_load_sample("Sounds/Coin.wav");
        sAppear = al_load_sample("Sounds/Appear.wav");
	}
    static void desiassets() {
        for (int i = 0; i < 4; i++) {
            al_destroy_bitmap(interrogation[i]);
        }
        for(int i=0; i<9; i++){
        	al_destroy_bitmap(uCoin[i]);
		}
    }
    ~Interrogation() {
    	if(hongo){
        	hongo->deshassets();
		}
		if(flor){
			flor->desfassets();
		}
		if(estrella){
			estrella->dessassets();
		}
		if(vida){
			vida->desvassets();
		}
	}
    void idraw() {
    	if(hongo && (hongo->hactive || hongo->emerging)) hongo->hdraw();
		if(flor && (flor->factive || flor->emerging)) flor->fdraw();
		if(estrella && (estrella->sactive || estrella->emerging)) estrella->sdraw();
		if(vida && (vida->vactive || vida->emerging)) vida->vdraw();
    	if(Case != 6){
    		al_draw_bitmap(interrogation[in], ix, iy - jumpOffset, 0);
		}else{
			al_draw_bitmap(interrogation[3], ix, iy - jumpOffset, 0);
		}
        if (iactive) {
            frameCount++;
            if (frameCount >= frameDelay) {
                frameCount = 0;
                in++;
                if (in >= 2) in = 0;
            }
        } else {
            in = 3;
        }

        if (movingUp) {
            jumpOffset += 1.5;
            if (jumpOffset >= 6) {
                movingUp = false;
                in = 3;
            }
        } else if (jumpOffset > 0) {
            jumpOffset -= 1.5;
            if (jumpOffset < 0) jumpOffset = 0;
        }
        if(coinup && ucactive){
        	icy-=2;
        	al_draw_bitmap(uCoin[inc],icx,icy,0);
        	if(icy>=6){
        		frameCountcoin+=3;
        		if(frameCountcoin>=frameDelaycoin){
        			frameCountcoin = 0;
        			inc++;
        			if(inc>=9){
        				ucactive = false;
					}
				}
			}
		}
	}
	void iupdate() {
    if (hongo && (hongo->hactive||hongo->emerging)) {
        hongo->hupdate();
    }
    if(flor && (flor->factive||flor->emerging)){
    	flor->fupdate();
	}
	if(estrella && (estrella->sactive || estrella->emerging)){
		estrella->supdate();
	}
	if(vida && (vida->vactive || vida->emerging)){
		vida->vupdate();
	}
	}
    void iobject() {
        if (!iactive){	
        	return;
		}
        switch (Case) {
            case 1:
                al_play_sample(iCoin, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                coinup = true;
                break;
            case 2:
            	al_play_sample(sAppear, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            	hongo->emerging = true;
            	break;
            case 3:
            	al_play_sample(sAppear, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            	flor->emerging = true;
            	break;
            case 4:
            	al_play_sample(sAppear, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            	estrella->emerging = true;
            	break;
            case 5:
            	al_play_sample(sAppear, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
            	vida->emerging = true;
            	break;
            case 6: break; 
        }
        iactive = false;
        if(Case != 6){
        	movingUp = true; 
		}
    }
};
ALLEGRO_BITMAP* Interrogation::interrogation[4] = {NULL, NULL, NULL, NULL};
ALLEGRO_BITMAP* Interrogation::uCoin[9] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
ALLEGRO_SAMPLE* Interrogation::iCoin = NULL;
ALLEGRO_SAMPLE* Interrogation::sAppear = NULL;
