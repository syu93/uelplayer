//estrutura Player
typedef struct Player{
    //ponteiro para m�sica
    FSOUND_STREAM *musica;
    
    //diretorio utilizado pelo programa
    DIR *dir;
    
    //arquivo utilizado pelo programa
    FILE *bib;
    
    //n�mero da m�sica
    int num;
    
    //total de m�sicas
    int tot;
        
    //nome do arquivo atual
    char arquivo[MAX_NAME];
    
    //bitmap para representar a tela
    BITMAP *tela;
    
    void playpause();
    void layout();
    void criarbiblioteca();
    void imprimirbiblioteca();
    void passarmouse();
    void inicializar();
    void mouseesquerdo();
    void backnext(bool next);
};

void init();
void deinit();
void close_button_handle();
float distponto(int x1, int y1, int x2, int y2);

//bot�o play/pause 
void Player::playpause(){
    circlefill(tela, PLAY_X, PLAY_Y, 23, makecol(20,70,180));
    circlefill(tela, 320, 445, 20, makecol(0,50,160));
    //se n�o estiver pausado
    if(FSOUND_GetPaused(0)){
        //guarda a dura��o da m�sica em milisegundos
        int ms = FSOUND_Stream_GetLengthMs(musica);
        rectfill(tela, 318, 440, 321, 455, makecol(255,255,255));
        rectfill(tela, 325, 440, 328, 455, makecol(255,255,255));
        rectfill(tela, 1, 381, 640, 410, makecol(20,70,180));
        rectfill(tela, 1, 411, 640, 420, makecol(0,50,160));
        //imprime o nome da m�sica
        textprintf_ex(tela, font, 10, 401, makecol(255,255,255),-1, "%s", arquivo);
        //imprime a dura��o da m�sica
        textprintf_ex(tela, font, 560, 401, makecol(255,255,255), -1, "%d : %d%d", ms/60000, ((ms/1000)%60)/10, (ms/1000)%10);
        //despausa se necess�rio
        FSOUND_SetPaused(0, false);
		//toca a m�sica
        FSOUND_Stream_Play(0, musica);
    } else {
        triangle(tela, 320, 440, 332, 445, 320, 450, makecol(255,255,255));
        //pausa
        FSOUND_SetPaused(0, true);
    }
    blit(tela, screen, 0, 0, 0, 0, 640, 480);
}

void Player::layout(){
     //desenha um ret�ngulo azul em cima
    rectfill(tela, 1, 1, 640, 50, makecol(20,70,180));
    rectfill(tela, 1, 51, 640, 60, makecol(0,50,160));

    //desenha um ret�ngulo azul em baixo
    rectfill(tela, 1, 381, 640, 410, makecol(20,70,180));
    rectfill(tela, 1, 411, 640, 420, makecol(0,50,160));

    //desenha um ret�ngulo prata
    rectfill(tela, 1, 421, 640, 470, makecol(150,150,150));
    rectfill(tela, 1, 471, 640, 480, makecol(130,130,130));

    //bot�o play 
    circlefill(tela, PLAY_X, PLAY_Y, 23, makecol(20,70,180));
    circlefill(tela, PLAY_X-3, PLAY_Y-3, 20, makecol(0,50,160));
    triangle(tela, 320, 440, 332, 445, 320, 450, makecol(255,255,255));
    
    //repeat
    circlefill(tela, REPEAT_X, REPEAT_Y, 18, makecol(20,70,180));
    circlefill(tela, REPEAT_X-3, REPEAT_Y-3, 15, makecol(0,50,160));
    circle(tela, REPEAT_X, REPEAT_Y, 8, makecol(255,255,255));
    circle(tela, REPEAT_X, REPEAT_Y, 9, makecol(255,255,255));
    circle(tela, REPEAT_X, REPEAT_Y, 10, makecol(255,255,255));
    triangle(tela, REPEAT_X+5, 440, REPEAT_X+15, 445, REPEAT_X+5, 450, makecol(255,255,255));
    
    //stop 
    circlefill(tela, STOP_X, STOP_Y,18,makecol(20,70,180));
    circlefill(tela, STOP_X-3, STOP_Y-3, 15, makecol(0,50,160));
    rectfill(tela, STOP_X-4, 440, STOP_X+4, 450, makecol(255,255,255));

    //backward 
    circlefill(tela, BWARD_X, BWARD_Y, 18, makecol(20,70,180));
    circlefill(tela, BWARD_X-3, BWARD_Y-3, 15, makecol(0,50,160));
    triangle(tela, BWARD_X, 440, BWARD_X-10, 445, BWARD_X, 450, makecol(255,255,255));
    triangle(tela, BWARD_X+10, 440, BWARD_X, 445, BWARD_X+10, 450, makecol(255,255,255));

    //forward 
    circlefill(tela, FWARD_X, FWARD_Y, 18, makecol(20,70,180));
    circlefill(tela, FWARD_X-3, FWARD_Y-3, 15, makecol(0,50,160));
    triangle(tela, FWARD_X, 440, FWARD_X+10, 445, FWARD_X, 450, makecol(255,255,255));
    triangle(tela, FWARD_X-10, 440, FWARD_X, 445, FWARD_X-10, 450, makecol(255,255,255));
    
    //mudo
    circlefill(tela, MUTE_X, MUTE_Y, 15, makecol(20,70,180));
    circlefill(tela, MUTE_X-3, MUTE_Y-3, 12, makecol(0,50,160));
    line(tela, MUTE_X-8, MUTE_Y+8, MUTE_X+8, MUTE_Y-8, makecol(255,255,255));
    line(tela, MUTE_X-7, MUTE_Y+8, MUTE_X+9, MUTE_Y-8, makecol(255,255,255));
    line(tela, MUTE_X-8, MUTE_Y-8, MUTE_X+8, MUTE_Y+8, makecol(255,255,255));
    line(tela, MUTE_X-7, MUTE_Y-8, MUTE_X+9, MUTE_Y+8, makecol(255,255,255));
    
    //volume
    triangle(tela, VOL_X2, VOL_Y1, VOL_X1, VOL_Y2, VOL_X2, VOL_Y2, makecol(255,255,255));
    triangle(tela, VOL_X2-50, VOL_Y1+12, VOL_X1, VOL_Y2, VOL_X2-50, VOL_Y2, makecol(0,50,160));
    
    textout_ex(tela, font, "UEL PLAYER", 260, 10, makecol(255,255,255),-1);
    
    textout_ex(tela, font, "F1 para AJUDA ", 270, 70, makecol(255,255,255),-1);
    
    blit(tela, screen, 0, 0, 0, 0, 640, 480);     
}

void Player::criarbiblioteca(){
    dirent* item_dir;
    int i;

	//cria pasta
    mkdir("data");
    //cria biblioteca
    bib = fopen("data\\biblioteca.txt", "w");
    //aponta para o diretorio de musicas
    dir = opendir("musicas.");
    //se houver erro ao abrir diretorio
    if(!dir){
        perror("opendir");
    } else{
        //l� os arquivos dos diretorios
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
    //atribui o total de m�sicas na pasta
    tot = i;
    //fecha o diret�rio 
    closedir(dir);
    //fecha o arquivo
    fclose(bib);
}

void Player::imprimirbiblioteca(){
    char letra;
    int i, j;
        
    bib = fopen("data\\biblioteca.txt", "r");
    for(i = 1, j = MAX_NAME; !feof(bib); i += 8){
        letra = fgetc(bib);
        //escreve uma linha
        if(letra != '\n' && letra != -1){
             textprintf_ex(tela, font, i, j-50, makecol(255,255,255), -1, "%c", letra);
        //pula linha
        } else {
            //epa�amento entre linhas(2)
			j += 10;
			//volta a margem esquerda
            i = -7;
        }
    }
}

void Player::passarmouse(){
    if((distponto(mouse_x, mouse_y, PLAY_X, PLAY_Y)) <= 25){
        if(FSOUND_GetPaused(0)){
            textout_ex(screen, font, "Play", mouse_x-8, mouse_y-8, makecol(255,255,255),0);  
        } else {
            textout_ex(screen, font, "Pause", mouse_x-8, mouse_y-8, makecol(255,255,255),0);  
        }     
    } else if ((distponto(mouse_x, mouse_y, STOP_X, STOP_Y)) <= 18){
        textout_ex(screen, font, "Stop", mouse_x-8, mouse_y-8, makecol(255,255,255),0);  
    } else if ((distponto(mouse_x, mouse_y, MUTE_X, MUTE_Y)) <= 18){
        if(FSOUND_GetMute(0)){
            textout_ex(screen, font, "Mute On", mouse_x-30, mouse_y-8, makecol(255,255,255),0);
        } else{
            textout_ex(screen, font, "Mute Off", mouse_x-30, mouse_y-8, makecol(255,255,255),0);
        }  
    } else if ((distponto(mouse_x, mouse_y, REPEAT_X, REPEAT_Y)) <= 18){
         if((FSOUND_Stream_GetMode(musica)) & FSOUND_LOOP_NORMAL){
            textout_ex(screen, font, "Repeat On", mouse_x-30, mouse_y-8, makecol(255,255,255),0);
        } else{
            textout_ex(screen, font, "Repeat Off", mouse_x-30, mouse_y-8, makecol(255,255,255),0);
        } 
    } else if ((distponto(mouse_x, mouse_y, BWARD_X, BWARD_Y)) <= 18){
        textout_ex(screen, font, "Anterior", mouse_x-8, mouse_y-8, makecol(255,255,255),0);  
    } else if ((distponto(mouse_x, mouse_y, FWARD_X, FWARD_Y)) <= 18){
        textout_ex(screen, font, "Proxima", mouse_x-8, mouse_y-8, makecol(255,255,255),0);  
    } else if (mouse_y <= VOL_Y2 && mouse_x <= VOL_X2){
        if((VOL_Y2-mouse_y) <= (mouse_x-VOL_X1)/4){
            textprintf_ex(screen, font, mouse_x-20, mouse_y-8, makecol(255,255,255),0, "%Vol %d",mouse_x-VOL_X1);  
        }
    }
}

void Player::mouseesquerdo(){
    //play/pause
    if((distponto(mouse_x, mouse_y, PLAY_X, PLAY_Y)) <= 25){
        playpause();
    //stop
    } else if ((distponto(mouse_x, mouse_y, STOP_X, STOP_Y)) <= 18){
        FSOUND_Stream_Stop(musica);
        FSOUND_SetPaused(0, false);
        playpause();
    //ativa/desativa o modo mudo
    } else if ((distponto(mouse_x, mouse_y, MUTE_X, MUTE_Y)) <= 18){
        FSOUND_SetMute(0, !FSOUND_GetMute(0));
    //ativa desativa repeat      
    } else if ((distponto(mouse_x, mouse_y, REPEAT_X, REPEAT_Y)) <= 18){
        if(!((FSOUND_Stream_GetMode(musica)) & FSOUND_LOOP_NORMAL)){
            FSOUND_Stream_SetMode(musica, FSOUND_LOOP_NORMAL);
        } else {
            FSOUND_Stream_SetMode(musica, FSOUND_LOOP_OFF);
        }
        if(!FSOUND_GetPaused(0)){
            playpause();
            FSOUND_Stream_Stop(musica);
        }
    //pr�xima m�sica    
    } else if ((distponto(mouse_x, mouse_y, FWARD_X, FWARD_Y)) <= 18){
        backnext(true);
    //m�sica anterior
    } else if ((distponto(mouse_x, mouse_y, BWARD_X, BWARD_Y)) <= 18){
        backnext(false);
    //ajusta o volume
    } else if (mouse_y <= VOL_Y2 && mouse_x <= VOL_X2){
        if ((VOL_Y2-mouse_y) <= (mouse_x-VOL_X1)/4){
            FSOUND_SetVolumeAbsolute(0, int((mouse_x-VOL_X1) * 2.55));
            triangle(tela, VOL_X2, VOL_Y1, VOL_X1, VOL_Y2, VOL_X2, VOL_Y2, makecol(255,255,255));
            triangle(tela, mouse_x, VOL_Y2-(mouse_x-VOL_X1)/4, VOL_X1, VOL_Y2, mouse_x, VOL_Y2, makecol(0,50,160));
        }
    }
}

void Player::backnext(bool next){
    int i, j;
    char nome[MAX_NAME]; 
                        
    //limpa a string com o nome do diretorio
    strcpy(arquivo, "musicas\\\\");
    
    bib = fopen("data\\biblioteca.txt", "r");
    
    //avan�a
    if(next){
        //n�o avan�a quando estiver na �ltima m�sica
        if(num != tot){
            num++;
        }
    //retrocede
    } else {
        //n�o retrocede quando estiver na primeira m�sica
        if(num != 1){
            num--;
        }
    }
    
    //abre o arquivo de n�mero num
    for(i = 0; i < num; i++){
        for(j = 0; j < MAX_NAME; j++){ 
            nome[j] = getc(bib);
            if (nome[j] == '\n'){
                nome[j] = '\0';
                break;
            }
        }
    }
        
    //concatena o nome do arquivo
    strcat(arquivo, nome); 
                    
    //para a m�sica antiga
    FSOUND_Stream_Close(musica);
    //para o canal de �udio
    FSOUND_StopSound(0);
	
	//muda o �cone
    playpause();
    
    //Esvazia o epa�o alocado na mem�ria
	FSOUND_Stream_Close(musica);
	            
    //abre o arquivo de a�dio do nome inserido
    musica = FSOUND_Stream_Open(arquivo, 0, 0, 0);
    
    //toca a m�sica nova
    playpause();
}

void Player::inicializar(){
    int i, j;
    char nome[MAX_NAME]; 
                        
    //limpa a string com o nome do diretorio
    strcpy(arquivo, "musicas\\\\");
    
    //toca a primeira m�sica
    num = 1;
    
    bib = fopen("data\\biblioteca.txt", "r");
    //abre o arquivo de n�mero num
    for(int i = 0; i < num; i++){
        for(j = 0; j < MAX_NAME; j++){ 
            nome[j] = getc(bib);
            if (nome[j] == '\n'){
                nome[j] = '\0';
                break;
            }
        }
    }
    
    //concatena o nome do arquivo
    strcat(arquivo, nome); 
    
	//abre o arquivo de a�dio do nome inserido
    musica = FSOUND_Stream_Open(arquivo, 0, 0, 0);
	//configura��o inicial: pausada
    FSOUND_SetPaused(0, true);
	//configura o volume inicial em torno de 50%
    FSOUND_SetSFXMasterVolume(127);	 
}

// inicializa��o do allegro
void init() {
	int depth, res;
	allegro_init();

	//ativa o bot�o de fechar
	LOCK_FUNCTION(close_button_handle);
	set_close_button_callback(close_button_handle);

    //sele��o da profundidade das cores (em bits)
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);

    //sele��o da resolu��o com janela
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, MAX_X, MAX_Y, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

    //funciona sem estar ativo
    set_display_switch_mode(SWITCH_BACKGROUND);
    
    //instala o timer, teclado e mouse
	install_timer();
	install_keyboard();
	install_mouse();

	//ativa o mouse
    enable_hardware_cursor();
    select_mouse_cursor(MOUSE_CURSOR_ARROW);
    show_mouse(screen);
}

// limpa o buffer de teclado
void deinit() {
	clear_keybuf();
}

//calcula dist�ncia entre dois pontos
float distponto(int x1, int y1, int x2, int y2){
    int a = (x1 - x2)*(x1 - x2);
    int b = (y1 - y2)*(y1 - y2);
    float z = sqrt(a+b);
    return z;
}
