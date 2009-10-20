//estrutura Player
typedef struct Player{
    //ponteiro para música
    FSOUND_STREAM *musica;
    
    //diretorio utilizado pelo programa
    DIR *dir;
    
    //arquivo utilizado pelo programa
    FILE *bib;
    
    //número da música
    int num;
    
    //total de músicas
    int tot;
    
	char key;
	    
    //nome do arquivo atual
    char arquivo[100];
    
    void playpause();
    void criarbiblioteca();
    void imprimirbiblioteca();
    void inicializar();
    void teclado();
    void backnext(bool next);
};

float distponto(int x1, int y1, int x2, int y2);

//botão play/pause 
void Player::playpause(){
    //se não estiver pausado
    if(FSOUND_GetPaused(0)){
        //guarda a duração da música em milisegundos
        int ms = FSOUND_Stream_GetLengthMs(musica);
        FSOUND_SetPaused(0, false);
        //toca a música
        FSOUND_Stream_Play(0, musica);
    } else {
        //pausa
        FSOUND_SetPaused(0, true);
    }
}

void Player::criarbiblioteca(){
    dirent* item_dir;
    int i;

    mkdir("data");
    //cria biblioteca
    bib = fopen("data\\biblioteca.txt", "w");
    //aponta para o diretorio de musicas
    dir = opendir("musicas.");
    //se houver erro ao abrir diretorio
    if(!dir){
        perror("opendir");
    } else{
        //lê os arquivos dos diretorios
        item_dir = readdir(dir);
        //contador de itens
        i = 0;
        while(item_dir){
            if(item_dir->d_name[0] != '.'){
                //escreve os nomes dos arquivos na biblioteca
                fprintf(bib, "%s\n", item_dir -> d_name );
                i++;
            }
            item_dir = readdir(dir);
        }
    }
    //atribui o total de músicas na pasta
    tot = i;
    //fecha o diretório 
    closedir(dir);
    //fecha o arquivo
    fclose(bib);
}

void Player::imprimirbiblioteca(){
    char letra;
    int i, j;
        
    bib = fopen("data\\biblioteca.txt", "r");
    for(i = 0; i < tot; i++)
	for(j = 0; j < 100 && !feof(bib); j++){
        letra = fgetc(bib);
        //escreve uma linha
        if(letra == '\n'){
			printf("\n");
		} else {
             printf("%c", letra);
        } 
    }
}

void Player::teclado(){
    key = getche();
	//play/pause
    //if((distponto(mouse_x, mouse_y, PLAY_X, PLAY_Y)) <= 25){
    if(key == 'p'){
	    playpause();
    //stop
    //} else if ((distponto(mouse_x, mouse_y, STOP_X, STOP_Y)) <= 18){
	}else if (key == 's'){
	    FSOUND_Stream_Stop(musica);
        FSOUND_SetPaused(0, false);
        playpause();
    //ativa/desativa o modo mudo
    //} else if ((distponto(mouse_x, mouse_y, MUTE_X, MUTE_Y)) <= 18){
	} else if (key == 'm'){
	    FSOUND_SetMute(0, !FSOUND_GetMute(0));
    //ativa desativa repeat      
    //} else if ((distponto(mouse_x, mouse_y, REPEAT_X, REPEAT_Y)) <= 18){
	} else if (key == 'r'){
	    if(!((FSOUND_Stream_GetMode(musica)) & FSOUND_LOOP_NORMAL)){
            FSOUND_Stream_SetMode(musica, FSOUND_LOOP_NORMAL);
        } else {
            FSOUND_Stream_SetMode(musica, FSOUND_LOOP_OFF);
        }
        if(!FSOUND_GetPaused(0)){
            playpause();
            FSOUND_Stream_Stop(musica);
        }
    //próxima música    
   // } else if ((distponto(mouse_x, mouse_y, FWARD_X, FWARD_Y)) <= 18){
      } else if (key == 'n'){
	   backnext(true);
    //música anterior
   // } else if ((distponto(mouse_x, mouse_y, BWARD_X, BWARD_Y)) <= 18){
      }  else if (key == 'b'){
		backnext(false);
    //ajusta o volume
    }/* else if (mouse_y <= VOL_Y2 && mouse_x <= VOL_X2){
        if ((VOL_Y2-mouse_y) <= (mouse_x-VOL_X1)/4){
            FSOUND_SetVolume(0, int((mouse_x-VOL_X1) * 2.55));
            triangle(tela, VOL_X2, VOL_Y1, VOL_X1, VOL_Y2, VOL_X2, VOL_Y2, makecol(255,255,255));
            triangle(tela, mouse_x, VOL_Y2-(mouse_x-VOL_X1)/4, VOL_X1, VOL_Y2, mouse_x, VOL_Y2, makecol(0,50,160));
        }
    }*/
}

void Player::backnext(bool next){
    int i, j;
    char nome[100]; 
                        
    //limpa a string com o nome do diretorio
    strcpy(arquivo, "musicas\\\\");
    
    bib = fopen("data\\biblioteca.txt", "r");
    
    //avança
    if(next){
        //não avança quando estiver na última música
        if(num != tot){
            num++;
        }
    //retrocede
    } else {
        //não retrocede quando estiver na primeira música
        if(num != 1){
            num--;
        }
    }
    
    //abre o arquivo de número num
    for(i = 0; i < num; i++){
        for(j = 0; j < 100; j++){ 
            nome[j] = getc(bib);
            if (nome[j] == '\n'){
                nome[j] = '\0';
                break;
            }
        }
    }
        
    //concatena o nome do arquivo
    strcat(arquivo, nome); 
                    
    //para a música antiga
    FSOUND_Stream_Close(musica);
    
    //muda o ícone
    playpause();
                
    //abre o arquivo de aúdio do nome inserido
    musica = FSOUND_Stream_Open(arquivo, 0, 0, 0);
    
    //toca a música nova
    playpause();
}

void Player::inicializar(){
    int i, j;
    char nome[100]; 
                        
    //limpa a string com o nome do diretorio
    strcpy(arquivo, "musicas\\\\");
    
    //toca a primeira música
    num = 1;
    
    bib = fopen("data\\biblioteca.txt", "r");
    for(j = 0; j < 100; j++){ 
        nome[j] = getc(bib);
        if (nome[j] == '\n'){
            nome[j] = '\0';
            break;
        }
    }
    
    //concatena o nome do arquivo
    strcat(arquivo, nome); 
                    
    //para a música antiga
    FSOUND_Stream_Close(musica);
            
    //abre o arquivo de aúdio do nome inserido
    musica = FSOUND_Stream_Open(arquivo, 0, 0, 0);
}


//calcula distância entre dois pontos
float distponto(int x1, int y1, int x2, int y2){
    int a = (x1 - x2)*(x1 - x2);
    int b = (y1 - y2)*(y1 - y2);
    float z = sqrt(a+b);
    return z;
}
