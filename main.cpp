// biblioteca para gráficos, mouse e teclado
#include <allegro.h>

// API de áudio
#include "fmod.h"

#include<math.h>
#include<string.h>
#include<stdio.h>
#include<dirent.h>
#include<time.h>

//definições de macros
#include "defines.cpp"

//funções membros
#include "funcoes.cpp"

//variável para ativar o botão close
volatile int close_button_pressed = false;

int main() {
    //variável tipo Player
    Player player;
    //clocks
    clock_t proximo;
    
    //inicializações do allegro
    init();
    
    // inicia o áudio com 5 canais
	FSOUND_Init(44100, 5, 0);
	
	//inicialização das variávies
    player.tela = create_bitmap(MAX_X, MAX_Y);
        
    //carrega a biblioteca
    player.criarbiblioteca();
    
    //desenha o layout da tela
    player.layout();
    
    //exibir a biblioteca
    player.imprimirbiblioteca();
    
    //carrega a primeira música
    player.inicializar();
    
    //configura o volume inicial em torno de 50%
    FSOUND_SetVolume(0, 127);
    
    //configuração inicial: pausada
    FSOUND_SetPaused(0, true);
	
	//atualiza a cada 0,01 seg
	proximo = clock_t(clock() * 1.01 * CLOCKS_PER_SEC);  
    
    // esc para sair do programa
    while (!key[KEY_ESC] && !close_button_pressed){
        while(clock() * CLOCKS_PER_SEC > proximo){
			//F1 para ajuda
        	if(key[KEY_F1]){
            	textout_ex(player.tela, font, "AJUDA" , 270, 80, makecol(255,255,255),-1);
            	blit(player.tela, screen, 0, 0, 0, 0, 640, 480);
        	}
        	//se apertar o botão esquerdo do mouse
        	if (mouse_b & 1){
            	player.mouseesquerdo();
        	}
        	//se apertar o botão direito do mouse
			if (mouse_b & 2){
        	//caso passe o mouse por cima de algo
        	} else {
            	player.passarmouse();
        	}
        
          	//quando acabar a música toca de novo
        	if(!FSOUND_GetPaused(0) && !FSOUND_IsPlaying(0)){
            	//a mesma música
            	if((FSOUND_Stream_GetMode(player.musica)) & FSOUND_LOOP_NORMAL){
                	player.playpause();
            	}
            	//a próxima música
            	player.backnext(true);
        	}
        
			//atualiza a tela 
       		//player.atualiza();
        	blit(player.tela, screen, 0, 0, 0, 0, 640, 480);  
			proximo = clock_t(clock() * 1.01 * CLOCKS_PER_SEC);
		}
		rest(1);
    }
    deinit();
  	
    //Fecha a API de áudio
  	FSOUND_Close();
	
    return 0;
}
END_OF_MAIN()

//para ativar o botão fechar
void close_button_handle(){
     close_button_pressed = true;
}
END_OF_FUNCTION(close_button_handle)
