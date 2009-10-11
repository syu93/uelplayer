// biblioteca para gr�ficos, mouse e teclado
#include <allegro.h>

// API de �udio
#include "fmod.h"

#include<math.h>
#include<string.h>
#include<stdio.h>
#include<dirent.h>

//defini��es de macros
#include "defines.cpp"

//fun��es membros
#include "funcoes.cpp"

//vari�vel para ativar o bot�o close
volatile int close_button_pressed = false;

int main() {
    //vari�vel tipo Player
    Player player;
    
    //inicializa��es do allegro
    init();
    
     // inicia o �udio com 5 canais
	FSOUND_Init(44100, 5, 0);
    
    //inicializa��o das vari�vies
    player.tela = create_bitmap(MAX_X, MAX_Y);
        
    //carrega a biblioteca
    player.criarbiblioteca();
    
    //desenha o layout da tela
    player.layout();
    
    //exibir a biblioteca
    player.imprimirbiblioteca();
    
    //carrega a primeira m�sica
    player.inicializar();
    
    //configura o volume inicial em torno de 50%
    FSOUND_SetVolume(0, 127);
    
    //configura��o inicial: pausada
    FSOUND_SetPaused(0, true);  
    
    // esc para sair do programa
    while (!key[KEY_ESC] && !close_button_pressed){
        //F1 para ajuda
        if(key[KEY_F1]){
            textout_ex(player.tela, font, "AJUDA" , 270, 80, makecol(255,255,255),-1);
            blit(player.tela, screen, 0, 0, 0, 0, 640, 480);
        }
        //se apertar o bot�o esquerdo do mouse
        if (mouse_b & 1){
            player.mouseesquerdo();
        }
        //se apertar o bot�o direito do mouse
		if (mouse_b & 2){
        //caso passe o mouse por cima de algo
        } else {
            player.passarmouse();
        }
        
        //descansa 1 milisegundo para n�o usar muito cpu
        rest(1);
        
        //atualiza a tela 
        blit(player.tela, screen, 0, 0, 0, 0, 640, 480);

        rest(1);
        
        //quando acabar a m�sica toca de novo
        if(!FSOUND_GetPaused(0) && !FSOUND_IsPlaying(0)){
            //a mesma m�sica
            if((FSOUND_Stream_GetMode(player.musica)) & FSOUND_LOOP_NORMAL){
                player.playpause();
            }
            //a pr�xima m�sica
            player.backnext(true);
        }
    }
    deinit();
  	
    //Fecha a API de �udio
  	FSOUND_Close();
	
    return 0;
}
END_OF_MAIN()

//para ativar o bot�o fechar
void close_button_handle(){
     close_button_pressed = true;
}
END_OF_FUNCTION(close_button_handle)
