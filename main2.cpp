// API de áudio
#include "fmod.h"

#include<math.h>
#include<string.h>
#include<stdio.h>
#include<dirent.h>
#include<time.h>
#include<conio.h>

//definições de macros
#include "defines.cpp"

//funções membros
#include "funcoes2.cpp"

int main() {
    //variável tipo Player
    Player player;
    //clocks
    clock_t proximo;
    
    // inicia o áudio com 5 canais
	FSOUND_Init(44100, 5, 0);

	//carrega a biblioteca
    player.criarbiblioteca();
    
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
    while (player.key != 0){
        while(clock() * CLOCKS_PER_SEC > proximo){
			player.teclado();
        
          	//quando acabar a música toca de novo
        	if(!FSOUND_GetPaused(0) && !FSOUND_IsPlaying(0)){
            	//a mesma música
            	if((FSOUND_Stream_GetMode(player.musica)) & FSOUND_LOOP_NORMAL){
                	player.playpause();
            	}
            	//a próxima música
            	player.backnext(true);
        	}
        
			proximo = clock_t(clock() * 1.01 * CLOCKS_PER_SEC);
		}
	}
      	
    //Fecha a API de áudio
  	FSOUND_Close();
	
    return 0;
}
