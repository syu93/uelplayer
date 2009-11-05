// biblioteca para gr�ficos, mouse e teclado
#include <allegro.h>

// API de �udio
#include "fmod.h"

#include<math.h>
#include<string.h>
#include<stdio.h>
#include<dirent.h>
#include<time.h>

//defini��es de macros
#include "defines.cpp"

//fun��es membros
#include "funcoes.cpp"

//vari�vel para ativar o bot�o close
volatile int close_button_pressed = false;

int main() {
    //vari�vel tipo Player
    Player player;
        
    //carrega a biblioteca
    player.criarbiblioteca();
    
    //exibir a biblioteca
    player.imprimirbiblioteca();
    
    //carrega a primeira m�sica
    player.inicializar();
    
	//desenha o layout da tela
    player.layout();
    
	// esc para sair do programa ou bot�o X
    while (!key[KEY_ESC] && !close_button_pressed){
        //se apertar o bot�o esquerdo do mouse
        if (mouse_b & 1){
            player.mouseesquerdo();
		}
        //se apertar o bot�o direito do mouse
		if (mouse_b & 2){
        //caso passe o mouse por cima de algo
        } 
        
		player.passarmouse();
                
        //quando acabar a m�sica toca de novo
        if(!FSOUND_GetPaused(0) && !FSOUND_IsPlaying(0)){
            //a mesma m�sica
            if((FSOUND_Stream_GetMode(player.musica)) & FSOUND_LOOP_NORMAL){
                player.playpause();
            }
            //a pr�xima m�sica
            player.backnext(true);
        }
        //hor�rio atual da m�sica
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
    //Esvazia a mem�ria utilizada
  	destroy_bitmap(player.tela);
  	destroy_bitmap(player.aba1);
  	destroy_bitmap(player.aba2);
  	destroy_bitmap(player.aba3);
  	destroy_bitmap(player.aba4);
  	//Esvazia mem�ria da m�sica
  	FSOUND_Stream_Close(player.musica);
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
