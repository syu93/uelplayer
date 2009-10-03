// biblioteca para gráficos, mouse e teclado
#include <allegro.h>

// API de áudio
#include "fmod.h"

void init();
void deinit();

int main() {
	init();
	// inicia o áudio com 10 canais
	FSOUND_Init (44100, 10, 0);

    BITMAP *tela;
    BITMAP *img;
    tela = create_bitmap(640, 480);
    //ativa o mouse
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    show_mouse(screen);
    
    //desenha um retângulo azul
    rect(tela, 1,1,640,50, makecol(0,0,170));
    rectfill(tela, 2,2,639,49, makecol(0,0,170));
    rect(tela, 1,51,640,60, makecol(0,100,200));
    rectfill(tela, 2,52,639,59, makecol(0,100,200));
    
    //desenha um retângulo prata
    rect(tela, 1,421,640,470, makecol(150,150,150));
    rectfill(tela, 2,422,639,469, makecol(150,150,150));
    rect(tela, 1,471,640,480, makecol(120,120,120));
    rectfill(tela, 2,472,639,479, makecol(120,120,120));
    
    
    //desenha um círculo azul de raio 23 (botão play)
    circle(tela, 323,448,23, makecol(0,100,250) );
    circlefill(tela, 323,448,23,makecol(0,100,250) );
    circle(tela, 320,445,20, makecol(0,70,150) );
    circlefill(tela, 320,445,20,makecol(0,70,150) );
    triangle(tela, 320,440, 332,445, 320,450, makecol(250,250,250));
    
    //outros círculos
    circle(tela, 123,448,18, makecol(0,100,250));
    circlefill(tela, 123,448,18,makecol(0,100,250));
    circle(tela, 120,445,15, makecol(0,70,150));
    circlefill(tela, 120,445,15,makecol(0,70,150));
    
    //stop
    circle(tela, 223,448,18, makecol(0,100,250));
    circlefill(tela, 223,448,18,makecol(0,100,250));
    circle(tela, 220,445,15, makecol(0,70,150));
    circlefill(tela, 220,445,15,makecol(0,70,150));
    rect(tela, 220,440,225,450, makecol(250,250,250));
    rectfill(tela, 221,441,224,449, makecol(250,250,250));
    
    //backward
    circle(tela, 423,448,18, makecol(0,100,250));
    circlefill(tela, 423,448,18,makecol(0,100,250));
    circle(tela, 420,445,15, makecol(0,70,150));
    circlefill(tela, 420,445,15,makecol(0,70,150));
    triangle(tela, 320,440, 332,445, 320,450, makecol(250,250,250));
    triangle(tela, 422,440, 410,445, 422,450, makecol(250,250,250));
    triangle(tela, 432,440, 420,445, 432,450, makecol(250,250,250));
    
    //foreword
    circle(tela, 523,448,18, makecol(0,100,250));
    circlefill(tela, 523,448,18,makecol(0,100,250));
    circle(tela, 520,445,15, makecol(0,70,150));
    circlefill(tela, 520,445,15,makecol(0,70,150));
    triangle(tela, 510,440, 522,445, 510,450, makecol(250,250,250));
    triangle(tela, 520,440, 532,445, 520,450, makecol(250,250,250));
    
    // esc para sair do programa
    while (! key[KEY_ESC]) {
        //se apertar o botão esquerdo do mouse
        if (mouse_b & 1){
          //imprime texto na tela na coordenada do mouse
          textout_ex(screen, font, "botao esquerdo do mouse", mouse_x, mouse_y, makecol(255,0,0),-1);
        } 
        //se apertar o botão direito do mouse
		if (mouse_b & 2){
           textout_ex(screen, font, "botao direito do mouse", mouse_x, mouse_y, makecol(0,0,255),-1);
       } 
       //recurso para evitar o "pisca-pisca" da tela, copiando tela em screen
       textout_ex(tela, font, "UEL PLAYER", 260, 10, makecol(200,200,200),-1);
       blit(tela, screen, 0, 0, 0, 0, 640, 480);
  }
	deinit();
	return 0;
}
END_OF_MAIN()

// inicialização do allegro
void init() {
	int depth, res;
	allegro_init();
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
}

// limpa o buffer de teclado
void deinit() {
	clear_keybuf();
}
