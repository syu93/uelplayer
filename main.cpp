// biblioteca para gr�ficos, mouse e teclado
#include <allegro.h>

// API de �udio
#include "fmod.h"

void init();
void deinit();

int main() {
	init();
	// inicia o �udio com 10 canais
	FSOUND_Init (44100, 10, 0);

    BITMAP *tela;
    BITMAP *img;
    tela = create_bitmap(640, 480);
    //ativa o mouse
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    
    //desenha um ret�ngulo azul
    rect(tela, 1,1,640,50, makecol(0,0,170));
    rectfill(tela, 2,2,639,49, makecol(0,0,170));
    rect(tela, 1,51,640,60, makecol(0,100,200));
    rectfill(tela, 2,52,639,59, makecol(0,100,200));
    
    //desenha um ret�ngulo prata
    rect(tela, 1,421,640,470, makecol(150,150,150));
    rectfill(tela, 2,422,639,469, makecol(150,150,150));
    rect(tela, 1,471,640,480, makecol(120,120,120));
    rectfill(tela, 2,472,639,479, makecol(120,120,120));
    
    //desenha um c�rculo azul de raio 23
    circle(tela, 323,448,23, makecol(0,100,250) );
    circlefill(tela, 323,448,23,makecol(0,100,250) );
    circle(tela, 320,445,20, makecol(0,70,150) );
    circlefill(tela, 320,445,20,makecol(0,70,150) );
    
    //outros c�rculos
    circle(tela, 123,448,18, makecol(0,100,250) );
    circlefill(tela, 123,448,18,makecol(0,100,250) );
    circle(tela, 120,445,15, makecol(0,70,150) );
    circlefill(tela, 120,445,15,makecol(0,70,150) );
    circle(tela, 223,448,18, makecol(0,100,250) );
    circlefill(tela, 223,448,18,makecol(0,100,250) );
    circle(tela, 220,445,15, makecol(0,70,150) );
    circlefill(tela, 220,445,15,makecol(0,70,150) );
    circle(tela, 423,448,18, makecol(0,100,250) );
    circlefill(tela, 423,448,18,makecol(0,100,250) );
    circle(tela, 420,445,15, makecol(0,70,150) );
    circlefill(tela, 420,445,15,makecol(0,70,150) );
    circle(tela, 523,448,18, makecol(0,100,250) );
    circlefill(tela, 523,448,18,makecol(0,100,250) );
    circle(tela, 520,445,15, makecol(0,70,150) );
    circlefill(tela, 520,445,15,makecol(0,70,150) );
    
    // esc para sair do programa
    while (! key[KEY_ESC]) {
        //se apertar o bot�o esquerdo do mouse
        if (mouse_b & 1){
          //imprime texto na tela na coordenada do mouse
          textout(screen, font, "botao esquerdo do mouse", mouse_x, mouse_y, makecol(255,0,0) );
        } 
        //se apertar o bot�o direito do mouse
		if (mouse_b & 2){
           textout(screen, font, "botao direito do mouse", mouse_x, mouse_y, makecol(0,0,255 ) );
       } 
       show_mouse(screen);
       //recurso para evitar o "pisca-pisca" da tela, copiando tela em screen
       textout(tela, font, "UEL PLAYER", 260, 5, makecol(200,200,200) );
       blit(tela, screen, 0, 0, 0, 0, 640, 480);
  }

	deinit();
	return 0;
}
END_OF_MAIN()

// inicializa��o do allegro
void init() {
	int depth, res;
	allegro_init();
	//sele��o da profundidade das cores (em bits)
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	//sele��o da resolu��o com janela
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
