#define PLAY_X  323
#define PLAY_Y  448
#define STOP_X  203
#define STOP_Y  448
#define FWARD_X 373
#define FWARD_Y 448
#define BWARD_X 273
#define BWARD_Y 448
#define MAX_X 640
#define MAX_Y 480

// biblioteca para gr�ficos, mouse e teclado
#include <allegro.h>

// API de �udio
#include "fmod.h"

#include<math.h>

void init();
void deinit();
float distponto(int x1, int y1, int x2, int y2);
void close_button_handle();
bool playpause(BITMAP *tela, bool play, FSOUND_STREAM *musica);

volatile int close_button_pressed = false;

int main() {
	init();
	
    // inicia o �udio com 10 canais
	FSOUND_Init(44100, 10, 0);
    //cria um bitmap para representar a tela
    BITMAP *tela;
    //ponteiro para m�sica
    FSOUND_STREAM *musica;

    bool play;
    
    //inicializa��o das vari�vies
    play = false;
    tela = create_bitmap(MAX_X, MAX_Y);

    musica = FSOUND_Stream_Open("arquivo.mp3", 0, 0, 0);
    FSOUND_SetVolume(0, 200);
    
    //desenha um ret�ngulo azul
    rectfill(tela, 1, 1, 640, 50, makecol(20,70,180));
    rectfill(tela, 1, 51, 640, 60, makecol(0,50,160));

    //desenha um ret�ngulo prata
    rectfill(tela, 1, 421, 640, 470, makecol(150,150,150));
    rectfill(tela, 1, 471, 640, 480, makecol(130,130,130));

    //bot�o play (323, 448)
    circlefill(tela, PLAY_X, PLAY_Y, 23, makecol(20,70,180));
    circlefill(tela, PLAY_X-3, PLAY_Y-3, 20, makecol(0,50,160));
    triangle(tela, 320, 440, 332, 445, 320, 450, makecol(255,255,255));
    
    //outros c�rculos
    circlefill(tela, 123, 448, 18, makecol(20,70,180));
    circlefill(tela, 120, 445, 15, makecol(0,50,160));

    //stop (203, 448)
    circlefill(tela, STOP_X, STOP_Y,18,makecol(20,70,180));
    circlefill(tela, STOP_X-3, STOP_Y-3, 15, makecol(0,50,160));
    rectfill(tela, STOP_X-4, 440, STOP_X+4, 450, makecol(255,255,255));

    //backward (273,448)
    circlefill(tela, BWARD_X, BWARD_Y, 18, makecol(20,70,180));
    circlefill(tela, BWARD_X-3, BWARD_Y-3, 15, makecol(0,50,160));
    triangle(tela, BWARD_X, 440, BWARD_X-10, 445, BWARD_X, 450, makecol(255,255,255));
    triangle(tela, BWARD_X+10, 440, BWARD_X, 445, BWARD_X+10, 450, makecol(255,255,255));

    //foreward (373, 448)
    circlefill(tela, FWARD_X, FWARD_Y, 18, makecol(20,70,180));
    circlefill(tela, FWARD_X-3, FWARD_Y-3, 15, makecol(0,50,160));
    triangle(tela, FWARD_X, 440, FWARD_X+10, 445, FWARD_X, 450, makecol(255,255,255));
    triangle(tela, FWARD_X-10, 440, FWARD_X, 445, FWARD_X-10, 450, makecol(255,255,255));
    
    textout_ex(tela, font, "UEL PLAYER", 260, 10, makecol(200,200,200),-1);
    textout_ex(tela, font, "F1 para AJUDA", 270, 150, makecol(200,200,200),-1);
    
    blit(tela, screen, 0, 0, 0, 0, 640, 480);

    // esc para sair do programa
    while (! key[KEY_ESC] & ! close_button_pressed) {
        //F1 para ajuda
        if(key[KEY_F1]){
          textout_ex(tela, font, "AJUDA", 270, 80, makecol(200,200,200),-1);
          blit(tela, screen, 0, 0, 0, 0, 640, 480);
        }
        //se apertar o bot�o esquerdo do mouse
        if (mouse_b & 1){
            //play/pause
            if((distponto(mouse_x, mouse_y, PLAY_X, PLAY_Y)) <= 25){
               play = playpause(tela, play, musica);
            //stop
            } else if ((distponto(mouse_x, mouse_y, STOP_X, STOP_Y)) <= 18){
                 FSOUND_Stream_Stop(musica);
                 play = true;
                 play = playpause(tela, play, musica);
                 FSOUND_SetPaused(0, false);
            }
        }
        //se apertar o bot�o direito do mouse
		if (mouse_b & 2){
            textout_ex(screen, font, "botao direito do mouse", mouse_x, mouse_y, makecol(0,0,255),-1);
        }
        //descansa 1 milisegundo para n�o usar muito cpu
        rest(1);
  }
  	deinit();
	return 0;
}
END_OF_MAIN()

// inicializa��o do allegro
void init() {
	int depth, res;
	allegro_init();

	//ativa o bot�o de fechar
	LOCK_FUNCTION(close_button_handle);
	set_close_button_callback(close_button_handle);

    //sele��o da profundidade das cores (em bits)
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);

    //sele��o da resolu��o com janela
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, MAX_X, MAX_Y, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

    //instala o timer, teclado e mouse
	install_timer();
	install_keyboard();
	install_mouse();

	//ativa o mouse
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    show_mouse(screen);
 }

// limpa o buffer de teclado
void deinit() {
	clear_keybuf();
}

//calcula dist�ncia entre dois pontos
float distponto(int x1, int y1, int x2, int y2){
    int a = (x1 - x2)*(x1 - x2);
    int b = (y1 - y2)*(y1 - y2);
    float z = sqrt(a+b);
    return z;
}

//bot�o play/pause (323, 448)
bool playpause(BITMAP *tela, bool play, FSOUND_STREAM *musica){
    circlefill(tela, PLAY_X, PLAY_Y, 23, makecol(20,70,180));
    circlefill(tela, 320, 445, 20, makecol(0,50,160));
    if(!play){
             rectfill(tela, 318, 440, 321, 455, makecol(255,255,255));
             rectfill(tela, 325, 440, 328, 455, makecol(255,255,255));
             //despausa se necess�rio
             FSOUND_SetPaused(0, false);
             //toca a m�sica
             FSOUND_Stream_Play(0, musica);
    } else {
            triangle(tela, 320, 440, 332, 445, 320, 450, makecol(255,255,255));
            //pausa
            FSOUND_SetPaused(0, true);
    }
    blit(tela, screen, 0, 0, 0, 0, 640, 480);
    //aguarda um intervalo para poder pausar/despausar
    rest(150);
    return !play;
}

//para ativar o bot�o fechar
void close_button_handle(){
     close_button_pressed = true;
}
END_OF_FUNCTION(close_button_handle)
