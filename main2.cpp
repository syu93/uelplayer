// API de �udio
#include "fmod.h"

#include<math.h>
#include<string.h>
#include<stdio.h>
#include<dirent.h>
#include<time.h>
#include<conio.h>

//defini��es de macros
#include "defines.cpp"

//fun��es membros
#include "funcoes2.cpp"

int main() {
    //vari�vel tipo Player
    Player player;
    //clocks
    clock_t proximo;
    
    // inicia o �udio com 5 canais
	FSOUND_Init(44100, 5, 0);

	//carrega a biblioteca
    player.criarbiblioteca();
    
    player.imprimirbiblioteca();
    
    //carrega a primeira m�sica
    player.inicializar();
    
    //configura o volume inicial em torno de 50%
    FSOUND_SetVolume(0, 127);
    
    //configura��o inicial: pausada
    FSOUND_SetPaused(0, true);
	
	//atualiza a cada 0,01 seg
	proximo = clock_t(clock() * 1.01 * CLOCKS_PER_SEC);  
    
    // esc para sair do programa
    while (player.key != 0){
        while(clock() * CLOCKS_PER_SEC > proximo){
			player.teclado();
        
          	//quando acabar a m�sica toca de novo
        	if(!FSOUND_GetPaused(0) && !FSOUND_IsPlaying(0)){
            	//a mesma m�sica
            	if((FSOUND_Stream_GetMode(player.musica)) & FSOUND_LOOP_NORMAL){
                	player.playpause();
            	}
            	//a pr�xima m�sica
            	player.backnext(true);
        	}
        
			proximo = clock_t(clock() * 1.01 * CLOCKS_PER_SEC);
		}
	}
      	
    //Fecha a API de �udio
  	FSOUND_Close();
	
    return 0;
}
