#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

//Cabeçalhos de funções
void menuIniciar();

void limpa_tela(){
    system("CLS");
}

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]){
    int i, j;
    //Popula o tabuleiro com agua
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            tabuleiro[i][j] = 'A';
            mascara[i][j] = '~';
        }
    }
}
void exibeMapa(){
   //Mapa indicador de colunas
   for(int i=0;i<10;i++){
        if(i == 0){
            cout << "     ";
        }
        cout << i << " ";
   }
   cout << "\n";
   for(int i=0;i<10;i++){
        if(i == 0){
            cout << "     ";
        }
        cout << "|" << " ";
   }
   cout << "\n";
}

void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], bool mostraGabarito){

   char blue[] = {0x1b, '[', '1', ';', '3', '4', 'm', 0};
   char white[] = {0x1b, '[', '1', ';', '3', '9', 'm', 0};
   char green[] = {0x1b, '[', '1', ';', '3', '2', 'm', 0};

   //Exibe o tabuleiro
   int l, c;
   for(l=0;l<10;l++){
        cout << l << " - ";
        for(c=0;c<10;c++){
            switch(mascara[l][c]){
                case 'A':
                    cout << blue << " " << mascara[l][c] << white;
                    break;
                case 'P':
                    cout << green << " " << mascara[l][c] << white;
                    break;
                default:
                    cout << " " << mascara[l][c];
            }

        }
        cout << "\n";
    }
        cout << "\n";
    if(mostraGabarito){
        for(l=0;l<10;l++){
            for(c=0;c<10;c++){
                cout << " " << tabuleiro[l][c];
            }
            cout << "\n";
        }
    }

}

void posicionaBarcos(char tabuleiro[10][10]){
    //Coloca 10 barcos no tabuleiro e inicializa o posicionamento com zero
    int qntd = 10, qtdPos = 0;                  //qntd = quantidade, qtdPos = quantidade posicionada

    do{

        int linhaAlea = rand() % 10; //Gera numero aleatorio da linha de 0 a 9
        int colunaAlea = rand() % 10; //Gera numero aleatorio da coluna de 0 a 9

        if(tabuleiro[linhaAlea][colunaAlea] == 'A'){
            //Posiciona 10 barcos aleatoriamente
            tabuleiro[linhaAlea][colunaAlea] = 'P';
            //Aumenta o contador de barcos posicionados
            qtdPos++;
        }

    }
    while(qtdPos < qntd);

}
void verificaTiro(char tabuleiro[10][10], int linhaJogada, int colunaJogada, int *pontos, string *mensagem){
    //Verifica quantos pontos adicionar
    switch(tabuleiro[linhaJogada][colunaJogada]){
        case 'P':
            *pontos += 10;
            *mensagem = "Voce acertou um barco pequeno! (10 pontos)";
            break;
        case 'A':
            *mensagem = "Voce errou";
            break;

    }
}
void jogo(string nomeJogador){
    ///VARIAVEIS GERAIS
    char tabuleiro[10][10], mascara[10][10];                 //Tabuleiro do jogo
    int i,j;                                                 //Auxiliares de navegação (i = linhas, j = colunas)
    int linhaJogada, colunaJogada;                           //Posicao escolhida pelo jogador
    int estadoJogo = 1;                                      //1 - Jogo acontecendo; 0 = Fim de jogo
    int pontos = 0;                                          //Pontuação do jogador
    int tentativas = 0, maxTentativas = 5;                   //Tentativas do jogador
    int op;                                                  //Opcao de fim de jogo
    string mensagem = "Bem vindo ao jogo";                   //Mensagem de feedback

    //Inicia otabuleiro com água
    iniciaTabuleiro(tabuleiro,mascara);

    //Posiciona os barcos aleatoriamente
    posicionaBarcos(tabuleiro);

    do{
        limpa_tela();
        //Exibe o mapa de indicações das colunas
        exibeMapa();
        //Exibe o tabuleiro
        exibeTabuleiro(tabuleiro,mascara, false);

        cout << mensagem;
        cout << "\nPontos: " <<pontos <<", Tentativas Restantes: " <<maxTentativas-tentativas<<endl;
        //Verificacao de dados
        linhaJogada = -1;
        colunaJogada = -1;

        while((linhaJogada < 0 || colunaJogada < 0) || (linhaJogada > 9 || linhaJogada > 9)){
            cout <<"\n" << nomeJogador <<", digite uma linha: "<< endl;
            cin >> linhaJogada;
            cout <<"\n" << nomeJogador <<", digite uma coluna: "<< endl;
            cin >> colunaJogada;
        }

        //Verifica o que acontece
        verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, &mensagem);
        //Revela o que está no tabuleiro
        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;

    }
    while(tentativas < maxTentativas);

    cout << "\n\nTotal de pontos: " << pontos <<endl;

    cout << "\nFim de jogo, o que deseja fazer?" <<endl;
    cout << "1 - Jogar Novamente" <<endl;
    cout << "2 - Ir para o menu" <<endl;
    cout << "Qualquer Numero - Sair" <<endl;
    cout << ": ";
    cin >> op;

    switch(op){
        case 1:
            jogo(nomeJogador);
            break;
        case 2:
            menuIniciar();
            break;
        default:
            cout << "\n\nObrigado por jogar! :D"<<endl;
    }

}

void sobre_jogo(){
    //O Usuario escolhe a opção depois de ler sobre o jogo
    int op;
    //Lendo o arquivo sobre o jogo
    ifstream input("Sobre.txt");
    //String que recebera o texto lido
    string sobre;
    //Armazena o nome do jogador
    string nomeJogador;
    //O arquivo de texe passa para string
    for(string line; getline(input, line);){
        sobre += line;
    }
    //Mostrar o conteudo
    cout << sobre;
    cout << "\nJogo desenvolvido por Antony e John ✌"<<endl;
    cout << "\n";
    cout << "1 - Ir para o jogo" <<endl;
    cout << "2 - Ir para o menu" <<endl;
    cout << "Qualquer Numero - Sair" <<endl;
    cout << ": ";
    cin >> op;

    switch(op){
        case 1:
            cout << "Digite seu nome: ";
            cin >> nomeJogador;
            jogo(nomeJogador);
            break;
        case 2:
            menuIniciar();
            break;
        default:
            cout << "\n\nAte mais! :D"<<endl;
    }

}


void menuIniciar(){
    //Opção escolhida pelo usuario
    int op = 0;
    //Um arquivo que le as informações do jogo

    //Nome do jogador
    string nomeJogador;
    //Enquanto o jogador não digita uma opcao valida, mostra o menu novamente
    while (op < 1 || op > 3){
        limpa_tela();
        cout << "=============== B A T A L H A  N A V A L ===============" << endl;
        cout << "1 - Jogar" << endl;
        cout << "2 - Sobre" << endl;
        cout << "3 - Sair" << endl;
        cout << "Escolha uma opcao e tecle ENTER: ";
        //Faz a leitura da opcao
        cin >> op;
        //Faz algo de acordo com a opcao escolhida
        switch(op){
            case 1:
                cout << "Digite seu nome: ";
                cin >> nomeJogador;
                jogo(nomeJogador);
                break;
            case 2:
                //Sobre o Jogo
                cout << "\nInformacoes do jogo"<<endl;
                sobre_jogo();
                break;
            case 3:
                //Sai do jogo
                cout << "\nAte a proxima! :D"<<endl;
                break;
        }

    }

}

int main()
{
    //Para gerar numeros realmente aleatorios
    srand ((unsigned)time(NULL));

    menuIniciar();
    return 0;
}
