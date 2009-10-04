// biblioteca para gráficos, mouse e teclado
#include <allegro.h>

// API de áudio
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
	
	 // inicia o áudio com 10 canais
	FSOUND_Init (44100, 10, 0);
    //cria um bitmap para representar a tela
    BITMAP *tela;
    //ponteiro para música
    FSOUND_STREAM *musica;

    bool play;
    
    //inicialização das variávies
    play = false;
    tela = create_bitmap(640, 480);

    musica = FSOUND_Stream_Open("arquivo.mp3", 0, 0, 0);
    FSOUND_SetVolume(0, 200);
    
    //desenha um retângulo azul
    rectfill(tela, 1,1,640,50, makecol(20,70,180));
    rectfill(tela, 1,51,640,60, makecol(0,50,160));

    //desenha um retângulo prata
    rectfill(tela, 1, 421, 640, 470, makecol(150,150,150));
    rectfill(tela, 1, 471, 640, 480, makecol(130,130,130));

    //botão play
    circlefill(tela, 323, 448, 23, makecol(20,70,180));
    circlefill(tela, 320, 445, 20, makecol(0,50,160));
    triangle(tela, 320, 440, 332, 445, 320, 450, makecol(255,255,255));
    
    //outros círculos
    circlefill(tela, 123, 448, 18, makecol(20,70,180));
    circlefill(tela, 120, 445, 15, makecol(0,50,160));

    //stop (223, 448)
    circlefill(tela, 223,448,18,makecol(20,70,180));
    circlefill(tela, 220,445,15,makecol(0,50,160));
    rectfill(tela, 220,440,225,450, makecol(255,255,255));

    //backward (423,448)
    circlefill(tela, 423, 448, 18, makecol(20,70,180));
    circlefill(tela, 420, 445, 15, makecol(0,50,160));
    triangle(tela, 422, 440, 410, 445, 422, 450, makecol(255,255,255));
    triangle(tela, 432, 440, 420, 445, 432, 450, makecol(255,255,255));

    //foreward (523, 448)
    circlefill(tela, 523, 448, 18, makecol(20,70,180));
    circlefill(tela, 520, 445, 15, makecol(0,50,160));
    triangle(tela, 510, 440, 522, 445, 510, 450, makecol(255,255,255));
    triangle(tela, 520, 440, 532, 445, 520, 450, makecol(255,255,255));
    
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
        //se apertar o botão esquerdo do mouse
        if (mouse_b & 1){
            //play/pause
            if((distponto(mouse_x, mouse_y, 323, 448)) <= 25){
               play = playpause(tela, play, musica);
            //stop
            } else if ((distponto(mouse_x, mouse_y, 223, 448)) <= 18){
                 FSOUND_Stream_Stop(musica);
                 playpause(tela, play, musica);
                 FSOUND_SetPaused(0, false);
            }
        }
        //se apertar o botão direito do mouse
		if (mouse_b & 2){
            textout_ex(screen, font, "botao direito do mouse", mouse_x, mouse_y, makecol(0,0,255),-1);
        }
  }
	deinit();
	return 0;
}
END_OF_MAIN()

// inicialização do allegro
void init() {
	int depth, res;
	allegro_init();

	//ativa o botão de fechar
	LOCK_FUNCTION(close_button_handle);
	set_close_button_callback(close_button_handle);

    //seleção da profundidade das cores (em bits)
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);

    //seleção da resolução com janela
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
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

//calcula distância entre dois pontos
float distponto(int x1, int y1, int x2, int y2){
    int a = (x1 - x2)*(x1 - x2);
    int b = (y1 - y2)*(y1 - y2);
    float z = sqrt(a+b);
    return z;
}

//botão play/pause (323, 448)
bool playpause(BITMAP *tela, bool play, FSOUND_STREAM *musica){
    circlefill(tela, 323, 448, 23, makecol(20,70,180));
    circlefill(tela, 320, 445, 20, makecol(0,50,160));
    if(play){
             rectfill(tela, 318, 440, 321, 455, makecol(255,255,255));
             rectfill(tela, 325, 440, 328, 455, makecol(255,255,255));
             //despausa se necessário
             FSOUND_SetPaused(0, false);
             //toca a música
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

//para ativar o botão fechar
void close_button_handle(){
     close_button_pressed = true;
}
END_OF_FUNCTION(close_button_handle)
