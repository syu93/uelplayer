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
	
    // esc para sair do programa	
    while (!key[KEY_ESC]) {
        //se apertar o botão esquerdo do mouse  
        if (mouse_b & 1){
          //imprime texto na tela na coordenada do mouse
          textout(screen, font, "botao esquerdo do mouse", mouse_x, mouse_y, makecol(255,0,0) );
        }
		if (mouse_b & 2){
          textout(screen, font, "botao direito do mouse", mouse_x, mouse_y, makecol(0,0,255 ) );
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
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
}

// limpa o buffer de teclado
void deinit() {
	clear_keybuf();
}
