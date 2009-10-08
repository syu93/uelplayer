//resolução
#define MAX_X   640
#define MAX_Y   480

//botões
#define PLAY_X  323
#define PLAY_Y  448
#define STOP_X  203
#define STOP_Y  448
#define FWARD_X 373
#define FWARD_Y 448
#define BWARD_X 273
#define BWARD_Y 448
#define MUTE_X  603
#define MUTE_Y  448

//volume
#define VOL_X1  470
#define VOL_X2  570
#define VOL_Y1  435
#define VOL_Y2  460

// biblioteca para gráficos, mouse e teclado
#include <allegro.h>

// API de áudio
#include "fmod.h"

#include<math.h>
#include<string.h>

//estrutura Player
typedef struct Player{
    //ponteiro para música
    FSOUND_STREAM *musica;
    
    //vetor de caracteres para nome do arquivo
    char arquivo[100];
    
    void playpause(BITMAP *tela);
};

void init();
void deinit();
float distponto(int x1, int y1, int x2, int y2);
void close_button_handle();

//variável para ativar o botão close
volatile int close_button_pressed = false;

int main() {
	init();
	
    // inicia o áudio com 10 canais
	FSOUND_Init(44100, 10, 0);
	
    //cria um bitmap para representar a tela
    BITMAP *tela;

	//variável tipo Player
    Player player;
    
    strcpy(player.arquivo, "arquivo.mp3");
        
    //inicialização das variávies
    tela = create_bitmap(MAX_X, MAX_Y);
    
    //abre o arquivo de aúdio
    player.musica = FSOUND_Stream_Open(player.arquivo, 0, 0, 0);
    
    //configura o volume
    FSOUND_SetVolume(0, 125);
    
    //configuração inicial: pausada
    FSOUND_SetPaused(0, true);
        
    //desenha um retângulo azul em cima
    rectfill(tela, 1, 1, 640, 50, makecol(20,70,180));
    rectfill(tela, 1, 51, 640, 60, makecol(0,50,160));

    //desenha um retângulo azul em baixo
    rectfill(tela, 1, 381, 640, 410, makecol(20,70,180));
    rectfill(tela, 1, 411, 640, 420, makecol(0,50,160));

    //desenha um retângulo prata
    rectfill(tela, 1, 421, 640, 470, makecol(150,150,150));
    rectfill(tela, 1, 471, 640, 480, makecol(130,130,130));

    //botão play 
    circlefill(tela, PLAY_X, PLAY_Y, 23, makecol(20,70,180));
    circlefill(tela, PLAY_X-3, PLAY_Y-3, 20, makecol(0,50,160));
    triangle(tela, 320, 440, 332, 445, 320, 450, makecol(255,255,255));
    
    //outros círculos
    circlefill(tela, 123, 448, 18, makecol(20,70,180));
    circlefill(tela, 120, 445, 15, makecol(0,50,160));

    //stop 
    circlefill(tela, STOP_X, STOP_Y,18,makecol(20,70,180));
    circlefill(tela, STOP_X-3, STOP_Y-3, 15, makecol(0,50,160));
    rectfill(tela, STOP_X-4, 440, STOP_X+4, 450, makecol(255,255,255));

    //backward 
    circlefill(tela, BWARD_X, BWARD_Y, 18, makecol(20,70,180));
    circlefill(tela, BWARD_X-3, BWARD_Y-3, 15, makecol(0,50,160));
    triangle(tela, BWARD_X, 440, BWARD_X-10, 445, BWARD_X, 450, makecol(255,255,255));
    triangle(tela, BWARD_X+10, 440, BWARD_X, 445, BWARD_X+10, 450, makecol(255,255,255));

    //forward 
    circlefill(tela, FWARD_X, FWARD_Y, 18, makecol(20,70,180));
    circlefill(tela, FWARD_X-3, FWARD_Y-3, 15, makecol(0,50,160));
    triangle(tela, FWARD_X, 440, FWARD_X+10, 445, FWARD_X, 450, makecol(255,255,255));
    triangle(tela, FWARD_X-10, 440, FWARD_X, 445, FWARD_X-10, 450, makecol(255,255,255));
    
    //mudo
    circlefill(tela, MUTE_X, MUTE_Y, 15, makecol(20,70,180));
    circlefill(tela, MUTE_X-3, MUTE_Y-3, 12, makecol(0,50,160));
    line(tela, MUTE_X-8, MUTE_Y+8, MUTE_X+8, MUTE_Y-8, makecol(255,255,255));
    line(tela, MUTE_X-7, MUTE_Y+8, MUTE_X+9, MUTE_Y-8, makecol(255,255,255));
    line(tela, MUTE_X-8, MUTE_Y-8, MUTE_X+8, MUTE_Y+8, makecol(255,255,255));
    line(tela, MUTE_X-7, MUTE_Y-8, MUTE_X+9, MUTE_Y+8, makecol(255,255,255));
    
    //volume
    triangle(tela, VOL_X2, VOL_Y1, VOL_X1, VOL_Y2, VOL_X2, VOL_Y2, makecol(255,255,255));
    triangle(tela, VOL_X2-50, VOL_Y1+12, VOL_X1, VOL_Y2, VOL_X2-50, VOL_Y2, makecol(0,50,160));
    
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
            if((distponto(mouse_x, mouse_y, PLAY_X, PLAY_Y)) <= 25){
                 player.playpause(tela);
            //stop
            } else if ((distponto(mouse_x, mouse_y, STOP_X, STOP_Y)) <= 18){
                 FSOUND_Stream_Stop(player.musica);
                 FSOUND_SetPaused(0, false);
                 player.playpause(tela);
            //ativa/desativa o modo mudo
            } else if ((distponto(mouse_x, mouse_y, MUTE_X, MUTE_Y)) <= 18){
                  FSOUND_SetMute(0, !FSOUND_GetMute(0));
                  rest(100);
            //ajusta o volume
            }  else if (mouse_y <= VOL_Y2 && mouse_x <= VOL_X2){
                 if ((VOL_Y2-mouse_y) <= (mouse_x-VOL_X1)/4){
                    FSOUND_SetVolume(0, int((mouse_x-VOL_X1) * 2.55));
                    triangle(tela, VOL_X2, VOL_Y1, VOL_X1, VOL_Y2, VOL_X2, VOL_Y2, makecol(255,255,255));
                    triangle(tela, mouse_x, VOL_Y2-(mouse_x-VOL_X1)/4, VOL_X1, VOL_Y2, mouse_x, VOL_Y2, makecol(0,50,160));
                 }
             }
        }
        //se apertar o botão direito do mouse
		if (mouse_b & 2){
            textout_ex(screen, font, "Propriedades", mouse_x-8, mouse_y-8, makecol(0,0,255),-1);
        //caso passe o mouse por cima de algo
        } else {
             if((distponto(mouse_x, mouse_y, PLAY_X, PLAY_Y)) <= 25){
                 if(FSOUND_GetPaused(0)){
                       textout_ex(screen, font, "Play", mouse_x-8, mouse_y-8, makecol(255,255,255),0);  
                 } else {
                       textout_ex(screen, font, "Pause", mouse_x-8, mouse_y-8, makecol(255,255,255),0);  
                 }     
             } else if ((distponto(mouse_x, mouse_y, STOP_X, STOP_Y)) <= 18){
                 textout_ex(screen, font, "Stop", mouse_x-8, mouse_y-8, makecol(255,255,255),0);  
             } else if ((distponto(mouse_x, mouse_y, MUTE_X, MUTE_Y)) <= 18){
                 textout_ex(screen, font, "Mute", mouse_x-8, mouse_y-8, makecol(255,255,255),0);  
             } else if (mouse_y <= VOL_Y2 && mouse_x <= VOL_X2){
                 if ((VOL_Y2-mouse_y) <= (mouse_x-VOL_X1)/4){
                    textprintf_ex(screen, font, mouse_x-20, mouse_y-8, makecol(255,255,255),0, "%Vol %d",mouse_x-VOL_X1);  
                }
             }
        }
        //atualiza a tela 
        blit(tela, screen, 0, 0, 0, 0, 640, 480);
        //descansa 1 milisegundo para não usar muito cpu
        rest(1);
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

//calcula distância entre dois pontos
float distponto(int x1, int y1, int x2, int y2){
    int a = (x1 - x2)*(x1 - x2);
    int b = (y1 - y2)*(y1 - y2);
    float z = sqrt(a+b);
    return z;
}

//botão play/pause (323, 448)
void Player::playpause(BITMAP *tela){
    circlefill(tela, PLAY_X, PLAY_Y, 23, makecol(20,70,180));
    circlefill(tela, 320, 445, 20, makecol(0,50,160));
    //se não estiver pausado
    if(FSOUND_GetPaused(0)){
             rectfill(tela, 318, 440, 321, 455, makecol(255,255,255));
             rectfill(tela, 325, 440, 328, 455, makecol(255,255,255));
             textprintf_ex(tela, font, 10, 401, makecol(255,255,255),-1, "%s", arquivo);
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
    rest(100);
}

//para ativar o botão fechar
void close_button_handle(){
     close_button_pressed = true;
}
END_OF_FUNCTION(close_button_handle)
