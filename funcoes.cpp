//estrutura Player
typedef struct Player{
    //ponteiro para música
    FSOUND_STREAM *musica;
    
    //diretorio utilizado pelo programa
    DIR *dir;
    
    //arquivo utilizado pelo programa
    FILE *bib, *let;
    
    //número da música
    int num;
    
    //total de músicas
    int tot;
    
    //modo
    int modo;
            
    //nome do arquivo atual
    char arquivo[MAX_NAME];
    
    //bitmap para representar a tela
    BITMAP *tela, *aba1, *aba2, *aba3, *aba4, *aba5;
    
    //clocks
    clock_t refresh, button, button2;
    
    //construtor
    Player();
    
    void playpause();
    void repeat();
    void layout();
    void criarbiblioteca();
    void imprimirbiblioteca();
    void passarmouse();
    void inicializar();
    void mouseesquerdo();
    void backnext(bool next);
    void atualiza();
    void letras();
};

void init();
void deinit();
void close_button_handle();
float distponto(int x1, int y1, int x2, int y2);

//construtor
Player::Player(){
	//inicializa os clocks
	refresh = button = button2 = clock();
	
	// inicia da API FMOD, áudio com 5 canais
	FSOUND_Init(44100, 5, 0);
	
	//inicializações do allegro
    init();
	
	//inicialização das variávies BITMAP
    tela = create_bitmap(MAX_X, MAX_Y);
    aba1 = create_bitmap(MAX_X, ABA_Y);
    aba2 = create_bitmap(MAX_X, ABA_Y);
    aba3 = create_bitmap(MAX_X, ABA_Y);
    aba4 = create_bitmap(MAX_X, ABA_Y);
    aba5 = create_bitmap(MAX_X, ABA_Y);
    
	//limpa os bitmaps
	clear(tela);
	clear(aba1);
	clear(aba2);
	clear(aba3);
	clear(aba4);
	clear(aba5);
	
	//começa exibindo a biblioteca
	modo = BIBLIOTECA;
}

//botão play/pause 
void Player::playpause(){
    circlefill(tela, PLAY_X, PLAY_Y, 23, makecol(20,70,180));
    circlefill(tela, 320, 445, 20, makecol(0,50,160));
    //se não estiver pausado
    if(FSOUND_GetPaused(0)){
        //guarda a duração da música em milisegundos
        int ms = FSOUND_Stream_GetLengthMs(musica);
        rectfill(tela, 318, 440, 321, 455, makecol(255,255,255));
        rectfill(tela, 325, 440, 328, 455, makecol(255,255,255));
        rectfill(tela, 1, 381, 640, 410, makecol(20,70,180));
        rectfill(tela, 1, 411, 640, 420, makecol(0,50,160));
        //imprime o nome da música
        char nome[MAX_NAME] = "";
        strcat(nome, arquivo+9);
		textprintf_ex(tela, font, 6, 401, makecol(255,255,255),-1, "%s", nome);
        //imprime a duração da música
        textprintf_ex(tela, font, 560, 401, makecol(255,255,255), -1, "%d : %d%d", ms/60000, ((ms/1000)%60)/10, (ms/1000)%10);
        //despausa se necessário
        FSOUND_SetPaused(0, false);
		//toca a música
        FSOUND_Stream_Play(0, musica);
        letras();
    } else {
        triangle(tela, 320, 440, 332, 445, 320, 450, makecol(255,255,255));
        //pausa
        FSOUND_SetPaused(0, true);
    }
    blit(tela, screen, 0, 0, 0, 0, 640, 480);
}

void Player::repeat(){
	circlefill(tela, REPEAT_X, REPEAT_Y, 18, makecol(20,70,180));
    circlefill(tela, REPEAT_X-3, REPEAT_Y-3, 15, makecol(0,50,160));
    //seta repeat
	if(!((FSOUND_Stream_GetMode(musica)) & FSOUND_LOOP_NORMAL)){
        FSOUND_Stream_SetMode(musica, FSOUND_LOOP_NORMAL);
        circle(tela, REPEAT_X, REPEAT_Y, 8, makecol(255,255,255));
    	circle(tela, REPEAT_X, REPEAT_Y, 9, makecol(255,255,255));
    	circle(tela, REPEAT_X, REPEAT_Y, 10, makecol(255,255,255));
    	triangle(tela, REPEAT_X+5, 440, REPEAT_X+15, 445, REPEAT_X+5, 450, makecol(255,255,255));
    //cancela repeat
	} else {
        FSOUND_Stream_SetMode(musica, FSOUND_LOOP_OFF);
        rectfill(tela, REPEAT_X-8, REPEAT_Y-2, REPEAT_X+8, REPEAT_Y+1, makecol(255,255,255));
        triangle(tela, REPEAT_X+5, REPEAT_Y+5, REPEAT_X+10, REPEAT_Y, REPEAT_X+5, REPEAT_Y-5, makecol(255,255,255));
    }
    if(!FSOUND_GetPaused(0)){
        int ms = FSOUND_Stream_GetTime(musica);
		playpause();
        FSOUND_Stream_Stop(musica);
        FSOUND_Stream_SetTime(musica, ms);
        playpause();
    }
}

void Player::layout(){
     //desenha um retângulo azul em cima
    rectfill(tela, 1, 1, 640, 50, makecol(20,70,180));
    rectfill(tela, 1, 51, 640, 60, makecol(0,50,160));

    //desenha um retângulo azul em baixo
    rectfill(tela, 1, 381, 640, 410, makecol(20,70,180));
    rectfill(tela, 1, 411, 640, 420, makecol(0,50,160));

    //desenha um retângulo prata
    rectfill(tela, 1, 421, 640, 470, makecol(150,150,150));
    rectfill(tela, 1, 471, 640, 480, makecol(130,130,130));

    //botão play 
    circlefill(tela, PLAY_X, PLAY_Y, 23, makecol(20,70,180));
    circlefill(tela, PLAY_X-3, PLAY_Y-3, 20, makecol(0,50,160));
    triangle(tela, 320, 440, 332, 445, 320, 450, makecol(255,255,255));
    
    //repeat
    circlefill(tela, REPEAT_X, REPEAT_Y, 18, makecol(20,70,180));
    circlefill(tela, REPEAT_X-3, REPEAT_Y-3, 15, makecol(0,50,160));
    rectfill(tela, REPEAT_X-8, REPEAT_Y-2, REPEAT_X+8, REPEAT_Y+1, makecol(255,255,255));
    triangle(tela, REPEAT_X+5, REPEAT_Y+5, REPEAT_X+10, REPEAT_Y, REPEAT_X+5, REPEAT_Y-5, makecol(255,255,255));
    
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
    rectfill(tela, VOL_X1, VOL_Y1, VOL_X2, VOL_Y2, makecol(255,255,255));
    rectfill(tela, VOL_X1, VOL_Y1, VOL_X2-32, VOL_Y2, makecol(0,50,160));
    
    textout_ex(tela, font, "UEL PLAYER", 260, 10, makecol(255,255,255),-1);
    textout_ex(tela, font, "Biblioteca", ABA_X1-90, 40, makecol(255,255,255),-1);
    textout_ex(tela, font, "PlayList", ABA_X2-90, 40, makecol(255,255,255),-1);
    textout_ex(tela, font, "Letra", ABA_X3-90, 40, makecol(255,255,255),-1);
    textout_ex(tela, font, "Configuracoes", ABA_X4-110, 40, makecol(255,255,255),-1);
    textout_ex(tela, font, "Ajuda", ABA_X4+50, 40, makecol(255,255,255),-1);
    
    line(tela, ABA_X1, 35, ABA_X1, 55, makecol(255,255,255));
    line(tela, ABA_X2, 35, ABA_X2, 55, makecol(255,255,255));
    line(tela, ABA_X3, 35, ABA_X3, 55, makecol(255,255,255));
    line(tela, ABA_X4, 35, ABA_X4, 55, makecol(255,255,255));
            
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
    //se não houver nenhuma música
    if(tot == 0){
		allegro_message("Insira pelo menos uma musica na pasta musicas");
	}
    //fecha o diretório 
    closedir(dir);
    //fecha o arquivo
    fclose(bib);
}

void Player::letras(){
	char letra;
    int i, j;
    
	char nome[MAX_NAME]="letras\\";
	strcat(nome, arquivo+9);
	strcat(nome, ".txt\0");
	let = fopen(nome, "r");    
    clear(aba3);
	if(let != NULL){
    	for(i = 1, j = 20; !feof(let); i += 8){
        	letra = fgetc(let);
        	//escreve uma linha
        	if(letra != '\n' && letra != -1){
             	textprintf_ex(aba3, font, i, j, makecol(255,255,255), 0, "%c", letra);
        	//pula linha
        	} else {
            	//espaçamento entre linhas(2)
				j += 10;
				//volta a margem esquerda
            	i = -7;
        	}
		}
    	//Desenha a letra na aba 3 e cola na tela
    	fclose(let);
	}
	
}

void Player::imprimirbiblioteca(){
    char letra;
    int i, j;
        
    bib = fopen("data\\biblioteca.txt", "r");
    for(i = 1, j = 20; !feof(bib); i += 8){
        letra = fgetc(bib);
        //escreve uma linha
        if(letra != '\n' && letra != -1){
             textprintf_ex(aba1, font, i, j, makecol(255,255,255), -1, "%c", letra);
        //pula linha
        } else {
            //espaçamento entre linhas(2)
			j += 10;
			//volta a margem esquerda
            i = -7;
        }
    }
    //Desenha a biblioteca na aba 1 e cola na tela
    blit(aba1, tela, 0, 0, 0, ABA_Y1, MAX_X, ABA_Y);
}

void Player::passarmouse(){
    if(mouse_y >= ABA_Y1+20 && mouse_y <= (ABA_Y1+20+ 10*tot-3)){
		if(modo == BIBLIOTECA){
			char nome[MAX_NAME];
			int cont;
			bib = fopen("data\\biblioteca.txt", "r");
			cont = int((mouse_y-ABA_Y1-20+1)/10);
			//copia o nome do arquivo cont
			for(int i = 0; i <= cont; i++){
        		for(int j = 0; j < MAX_NAME; j++){ 
            		nome[j] = getc(bib);
            		if (nome[j] == '\n'){
                		nome[j] = '\0';
                		break;
					}
            	}
        	}
        	fclose(bib);
    		//escreve o nome da música em amarelo
			textout_ex(screen, font, nome, 0, mouse_y-mouse_y%10+1, makecol(255,255,0),0);
		}   
	} else if((distponto(mouse_x, mouse_y, PLAY_X, PLAY_Y)) <= 25){
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
    } else if(mouse_x >= VOL_X1 && mouse_y >= VOL_Y1 && mouse_y <= VOL_Y2 && mouse_x <= VOL_X2){
        textprintf_ex(screen, font, mouse_x-20, mouse_y-8, makecol(255,255,255),0, "%Vol %d", ((mouse_x-VOL_X1)*4+3)*100/255);
	}
}

void Player::mouseesquerdo(){
    if(mouse_y <= 55 && mouse_y >= 35){
		if(mouse_x <= ABA_X1){
		
		} if(mouse_x <= ABA_X1){
			modo = BIBLIOTECA;
		} else if(mouse_x <= ABA_X2){
			modo = PLAYLIST;
		} else if(mouse_x <= ABA_X3){
			modo = LETRA;
		} else if(mouse_x <= ABA_X4){
			modo = CONFIG;
		} else{
			modo = AJUDA;
		}
	}
	//se apertar a região de uma música
	if (mouse_y >= ABA_Y1+20 && mouse_y <= (ABA_Y1+20+10*tot-2)){
		FSOUND_Stream_Stop(musica);
		num = int((mouse_y-ABA_Y1-20)/10);
		backnext(true);
    //play/pause
    } else if((distponto(mouse_x, mouse_y, PLAY_X, PLAY_Y)) <= 25){
        if(clock() - button >= BUTTON * CLOCKS_PER_SEC){
			playpause();
			button = clock();
		}
    //stop
    } else if ((distponto(mouse_x, mouse_y, STOP_X, STOP_Y)) <= 18){
        FSOUND_Stream_Stop(musica);
        FSOUND_SetPaused(0, false);
        playpause();
        //imprime 0 seg/min
        textprintf_ex(tela, font, 560, 391, makecol(255,255,255), makecol(20,70,180), "%d : %d%d", 0, 0, 0);
    //ativa/desativa o modo mudo
    } else if ((distponto(mouse_x, mouse_y, MUTE_X, MUTE_Y)) <= 18){
		if(clock() - button >= BUTTON * CLOCKS_PER_SEC){
        	FSOUND_SetMute(0, !FSOUND_GetMute(0));
        	button = clock();
		}
    //ativa desativa repeat      
    } else if ((distponto(mouse_x, mouse_y, REPEAT_X, REPEAT_Y)) <= 18){
        if(clock() - button >= BUTTON * CLOCKS_PER_SEC){
			repeat();
        	button = clock();
		}
    //próxima música    
    } else if ((distponto(mouse_x, mouse_y, FWARD_X, FWARD_Y)) <= 18){
        if(clock() - button2 >= BUTTON2 * CLOCKS_PER_SEC){
			backnext(true);
			button2 = clock();
		}
    //música anterior
    } else if ((distponto(mouse_x, mouse_y, BWARD_X, BWARD_Y)) <= 18){
        if(clock() - button2 >= BUTTON2 * CLOCKS_PER_SEC){
			backnext(false);
			button2 = clock();
		}
    //ajusta o volume
    } else if (mouse_x >= VOL_X1 && mouse_y >= VOL_Y1 && mouse_y <= VOL_Y2 && mouse_x <= VOL_X2){
         FSOUND_SetVolumeAbsolute(0, (mouse_x-VOL_X1) * 4 + 1);
         rectfill(tela, VOL_X1, VOL_Y1, VOL_X2, VOL_Y2, makecol(255,255,255));
         rectfill(tela, VOL_X1, VOL_Y1, mouse_x, VOL_Y2, makecol(0,50,160));
    }
}

void Player::backnext(bool next){
    int i, j;
    char nome[MAX_NAME]; 
                        
    //limpa a string com o nome do diretorio
    strcpy(arquivo, "musicas\\\\");
    
    bib = fopen("data\\biblioteca.txt", "r");
    
    //avança
    if(next){
        //se não for a última música avança normalmente
        if(num != tot){
            num++;
        //se for a última música avança para a primeira
        } else {
			num = 1;
		}
    //retrocede
    } else {
        //se não for a primeira música retrocede normalmente
        if(num != 1){
            num--;
        //se for a primeira retrocede para a última
		} else {
			num = tot;
		}
    }
    
    //abre o arquivo de número num
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
                    
    //para a música antiga
    FSOUND_Stream_Close(musica);
    //para o canal de áudio
    FSOUND_StopSound(0);
	
	//muda o ícone
    playpause();
    
    //Esvazia o epaço alocado na memória
	FSOUND_Stream_Close(musica);
	            
    //abre o arquivo de aúdio do nome inserido
    musica = FSOUND_Stream_Open(arquivo, 0, 0, 0);
    
    //toca a música nova
    playpause();
}

void Player::inicializar(){
    int i, j;
    char nome[MAX_NAME]; 
                        
    //limpa a string com o nome do diretorio
    strcpy(arquivo, "musicas\\\\");
    
    //toca a primeira música
    num = 1;
    
    bib = fopen("data\\biblioteca.txt", "r");
    //abre o arquivo de número num
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
    
	//abre o arquivo de aúdio do nome inserido
    musica = FSOUND_Stream_Open(arquivo, 0, 0, 0);
	//configuração inicial: pausada
    FSOUND_SetPaused(0, true);
	//configura o volume inicial em torno de 50%
    FSOUND_SetSFXMasterVolume(127);	 
}

void Player::atualiza(){
	//atualiza a cada intervalo refresh
	if(clock() - refresh >= REFRESH * CLOCKS_PER_SEC){
		//atualiza a tela 
       	acquire_screen();
       	//biblioteca
		if(modo == BIBLIOTECA){
			blit(aba1, tela, 0, 0, 0, ABA_Y1, MAX_X, ABA_Y);		   
		//letra
		}else{
			blit(aba3, tela, 0, 0, 0, ABA_Y1, MAX_X, ABA_Y);
		}
		blit(tela, screen, 0, 0, 0, 0, MAX_X, MAX_Y);
		release_screen();
		refresh = clock();
	} else {
		//descansa 1 ms para economizar CPU
		rest(1);
	}
}

// inicialização do allegro
void init() {
	int depth, res;
	allegro_init();

	//ativa o botão de fechar
	LOCK_FUNCTION(close_button_handle);
	set_close_button_callback(close_button_handle);

    //seleção da profundidade das cores (em bits)
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);

    //seleção da resolução com janela
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

//calcula distância entre dois pontos
float distponto(int x1, int y1, int x2, int y2){
    int a = (x1 - x2)*(x1 - x2);
    int b = (y1 - y2)*(y1 - y2);
    float z = sqrt(a+b);
    return z;
}
