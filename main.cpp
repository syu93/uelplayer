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
    tela = create_bitmap(640, 480);
    //ativa o mouse
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    
    // esc para sair do programa
    while (! key[KEY_ESC]) {
        //se apertar o botão esquerdo do mouse
        if (mouse_b & 1){
          //imprime texto na tela na coordenada do mouse
          textout(screen, font, "botao esquerdo do mouse", mouse_x, mouse_y, makecol(255,0,0) );
        } 
        //se apertar o botão direito do mouse
		if (mouse_b & 2){
           textout(screen, font, "botao direito do mouse", mouse_x, mouse_y, makecol(0,0,255 ) );
       } 
       show_mouse(screen);
       //recurso para evitar o "pisca-pisca" da tela
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
