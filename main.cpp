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
        
    //carrega a biblioteca
    player.criarbiblioteca();
    
    //exibir a biblioteca
    player.imprimirbiblioteca();
    
    //carrega a primeira música
    player.inicializar();
    
	//desenha o layout da tela
    player.layout();
    
	// esc para sair do programa ou botão X
    while (!key[KEY_ESC] && !close_button_pressed){
        //se apertar o botão esquerdo do mouse
        if (mouse_b & 1){
            player.mouseesquerdo();
		}
        //se apertar o botão direito do mouse
		if (mouse_b & 2){
        //caso passe o mouse por cima de algo
        } 
        
		player.passarmouse();
                
        //quando acabar a música toca de novo
        if(!FSOUND_GetPaused(0) && !FSOUND_IsPlaying(0)){
            //a mesma música
            if((FSOUND_Stream_GetMode(player.musica)) & FSOUND_LOOP_NORMAL){
                player.playpause();
            }
            //a próxima música
            player.backnext(true);
        }
        //horário atual da música
        if(FSOUND_IsPlaying(0)){
			int ms = FSOUND_Stream_GetTime(player.musica);
			int time = FSOUND_Stream_GetLengthMs(player.musica);
			int dur = ms*500/time;
			rectfill(player.tela, POS_X1, POS_Y1, POS_X2, POS_Y2, makecol(0,0,0));
			rectfill(player.tela, POS_X1, POS_Y1, POS_X1+dur, POS_Y2, makecol(255,255,0));
			textprintf_ex(player.tela, font, 560, 391, makecol(255,255,255), player.cor, "%d : %d%d", ms/60000, ((ms/1000)%60)/10, (ms/1000)%10);
		} 
		player.atualiza();
	}
    deinit();
    //Esvazia a memória utilizada
  	destroy_bitmap(player.tela);
  	destroy_bitmap(player.aba1);
  	destroy_bitmap(player.aba2);
  	destroy_bitmap(player.aba3);
  	destroy_bitmap(player.aba4);
  	//Esvazia memória da música
  	FSOUND_Stream_Close(player.musica);
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
