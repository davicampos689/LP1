#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define dia_atual (hj.tm_mday)
#define mes_atual (hj.tm_mon+1)
#define ano_atual (hj.tm_year+1900)

//variaveis
     int qtd_pessoa_global;
     int qtd_crianca_global;
     int dia_entrada_global,mes_entrada_global,ano_entrada_global;
     int dia_saida_global,mes_saida_global,ano_saida_global; 
     int quarto;
     int preco_global;
     int controle=1;

//arquivos
     FILE *reservas;
     FILE* preset; 
     FILE *contrato;

//struct

struct quartos
{
    int quartos[7][13][33];
}; 

struct admin 
{   
    int id;
    char login[15];
    char senha[15];

    float presidencial;
    
    float luxo_simples;
    float luxo_duplo;
    float luxo_triplo;

    float executivo_simples;
    float executivo_duplo;
    float executivo_triplo;

    float babysitter;
    
    float carro_luxo;
    float carro_executivo;
    float seguro;
    float tanque;

    float restaurante;

    float cama_extra;

    float multa;
    float controle_preco; 

    
    struct quartos disponivel;

};  

struct acompanhante
{
   char nome[30];
   char documento[20];
   char data[20];
   char sexo[20];
};

struct servico 
{
     int babysitter;
     float babysitter_total;

     int carro;
     int tanque;
     int seguro; 
     float carro_total;

     int cama_extra;
     float cama_extra_total;
     
     int restaurante;
     float restaurante_total;

     float total_servico;
};

struct caracteristica 
{
    char quarto[30];
    int quarto_num;
    int qtd_pessoa;
    float preco_quarto;
};

struct data
{
    int dia_entrada;
    int mes_entrada;
    int ano_entrada;

    int dia_saida;
    int mes_saida;
    int ano_saida;
};

struct cadastro 
{
   int num_reserva;

   char nome[30];
   char data_nascimento[15];
   char nacionalidade[30];
   char sexo[30];
   char endereco[50];
   char bairro[30];
   char cidade[30];
   char cpf[17];
   char rg[15];
   char email[50];
   char telefone[20];
   char estado[30]; 

   
   char cartao[15];
   
   struct servico servico;
   struct caracteristica caracteristica;
   struct acompanhante acompanhante[3];
   struct data data;
   float total_tudo;
}; 


//"Objetos"
  struct admin admin;
  struct cadastro cliente;
  struct tm hj;

//prototipos
void gotoxy (int x, int y); 
void fundo_normal();
void verde();
void vermelho();
void azul();
void limpar();
void limpar_tela();
void menu_principal();
void menu_responsavel();
void asterisco(int n);
void abertura();
void checar();
void pegar_dados();
void acompanhante(int n);
void conclusao();
void pagamento();
void cartao(int n);
void salvar();
void listar();
void usuario();
void buscar();
int existe(int t);
void editar();
void tabela_preco();
void listar_precos();
void listar_precos_admin();
char* retorna_quarto(int n,int qtd_pessoa);
int tipo_quarto(char nome[30]);
void valor_quarto(char nome[30]);
int bissexto(int ano);
int qtd_dias(int num,int ano);
int verificar(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes);
int tempo_estadia(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida);
int vagas(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int n);
void descontar_vagas(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes);
void descontar(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes);
void aumentar(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes);
void aumentar_vagas(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes);
void inicializacao_preset();
void disponibilidade();
char *retorna_nome(int num);
void menu_servicos();
void deletar();
void alterar_babysitter();
void alterar_quartos_admin();
void alterar_servicos_admin();
void menu_admin();
void alterar_taxa_admin();
void alterar_login_admin();
void login();
void login_admin();
void alterar_carro();
void alterar_restaurante();
void alterar_cama();
void controle_de_preco();
void contrato_texto(char arquivo[30]);

//funcoes
void gotoxy(int x, int y) 
{
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
} 

void fundo_normal()
{
    system("Color 07");
} 

void verde()
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
          SetConsoleTextAttribute(h,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

void vermelho()
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
          SetConsoleTextAttribute(h,FOREGROUND_RED| FOREGROUND_INTENSITY);
} 

void azul()
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void limpar()
{
    setbuf(stdin,NULL);
} 

void limpar_tela()
{
    system("cls");
}

void menu_principal()
{      
    limpar_tela();
    fundo_normal(); 
    limpar();

    int op;


       gotoxy(45,6);  printf(" **    **   ****   *    *  *    * ");
       gotoxy(45,7);  printf(" * *  * *   *      * *  *  *    * ");
       gotoxy(45,8);  printf(" *  **  *   ****   *  * *  *    * ");
       gotoxy(45,9);  printf(" *      *   *      *   **  *    * ");
       gotoxy(45,10); printf(" *      *   ****   *    *  ****** ");
       gotoxy(33,12);printf("_________________________________________________________");
       gotoxy(52,14);printf("1- Check-in");
       gotoxy(52,16);printf("2- Ver disponibilidade");
       gotoxy(52,18);printf("3- Listar hospedes");
       gotoxy(52,20);printf("4- Buscar hospede");
       gotoxy(52,22);printf("5- Alterar dados do hospede");
       gotoxy(52,24);printf("6- Check-out");
       gotoxy(52,26);printf("7- Adicionar ou remover servicos");
       gotoxy(52,28);printf("8- Tabela de precos");
       gotoxy(52,30);printf("9- Sair do programa");
       gotoxy(6,33);printf("Digite a opcao desejada: "); 
       gotoxy(34,33);scanf("%d",&op);
       
       switch(op)
       {
              case 1: 
              checar();
              break; 

              case 2:
              disponibilidade();
              break;
              
              case 3:
              listar();
              break; 

              case 4:
              buscar();
              break; 

              case 5:
              editar();
              break;
              
              case 6:
              deletar();
              break; 

              case 7:
              menu_servicos();
              break;

              case 8:
              listar_precos();
              break;

              case 9:
              return ; 

              case 456:
              login_admin();
              break;

              default:
              menu_principal();
              break;

       }

}   

void menu_responsavel()
{
   limpar_tela();
   fundo_normal();
   limpar();
    
    char escolha;
    
   gotoxy(30,3);printf("CADASTRAMENTO DO USUARIO RESPONSAVEL PELA RESERVA");
   gotoxy(4,6);printf("Dados:");
   gotoxy(4,9);printf("Nome Completo: ");
   gotoxy(70,9); printf("Data de Nascimento:");
   gotoxy(4,11); printf("Nacionalidade:");
   gotoxy(50,11); printf("Sexo:");
   gotoxy(4,13); printf("Endereco:");
   gotoxy(50,13);printf("Bairro:");
   gotoxy(90,13);printf("cidade:");
   gotoxy(115,13);printf("Estado:");
   gotoxy(4,15);printf("CPF:");
   gotoxy(40,15);printf("RG:");
   gotoxy(70,15);printf("telefone:");
   gotoxy(4,17);printf("E-mail:");
   
        pegar_dados();
 
     gotoxy(30,23);puts("Cadastramento feito com sucesso"); 
    
    limpar();

    gotoxy(50,27);printf(" (A) Avancar");
    gotoxy(20,27);printf(" (M) voltar "); 


    gotoxy(1,27); 
    escolha=getch();

    if(escolha == 'A' || escolha=='a') 
        acompanhante(cliente.caracteristica.qtd_pessoa-1);

    else if(escolha == 'M' || escolha =='m')  
        checar();

    else menu_responsavel();
} 

void asterisco(int n)
{  
     HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,FOREGROUND_RED | FOREGROUND_INTENSITY);
    for(int i=0;i<n*2;i++)
    {
        printf("%c",223);
        Sleep(50);
    }
}

void abertura()
{
        system("COLOR 0A");
        gotoxy(30,11);printf("**     **     **********  ************   ********   ***"     );       
        gotoxy(30,12);printf("**     **     **      **      ****       ********   ***"     );
        gotoxy(30,13); printf("**     **     **      **      ****       **         ***"     );
        gotoxy(30,14);printf("*********     **      **      ****       ********   ***"     );
        gotoxy(30,15);printf("*********     **      **      ****       ********   ***"     );
        gotoxy(30,16);printf("**     **     **      **      ****       **         ***"     );
        gotoxy(30,17);printf("**     **     **      **      ****       ********   ********");
        gotoxy(30,18);printf("**     **     **********      ****       ********   ********");
        gotoxy(14,23);asterisco(45);
} 

void checar()
{
    limpar_tela();
    fundo_normal();


     //int qtd_pessoa_global;
     //int qtd_crianca_global;
    //int dia_entrada_global,mes_entrada_global,ano_entrada_global;
     //int dia_saida_global,mes_saida_global,ano_saida_global; 
    int op_quarto;
    int idade_crianca;
    int vaga;
    char  escolha;
    
     
     
     gotoxy(40,3);printf("SISTEMA DE RESERVA");
 
          gotoxy(6,5);printf("_____________________________________________________________________________________________________");
          gotoxy(6,7);printf("Data da entrada: ");
          gotoxy(6,8);printf("Data da Saida: ");
          gotoxy(6,9);printf("_____________________________________________________________________________________________________");
          gotoxy(6,11);printf("Modelo do quarto: "); 
          gotoxy(15,13);printf("1- Presidencial");
          gotoxy(35,13);printf("2- Executivo");
          gotoxy(50,13);printf("3- Luxo");
          gotoxy(6,15);printf("_____________________________________________________________________________________________________");
          gotoxy(6,17);printf("Quantidade de pessoas: ");
          gotoxy(45,17);printf("crianca: ");
          gotoxy(75,17);printf("Idade da crianca: ");
          gotoxy(6,19);printf("_____________________________________________________________________________________________________");
    
            azul();
          
          gotoxy(23,7);scanf("%d-%d-%d",&cliente.data.dia_entrada,&cliente.data.mes_entrada,&cliente.data.ano_entrada);
          gotoxy(21,8);scanf("%d-%d-%d",&cliente.data.dia_saida,&cliente.data.mes_saida,&cliente.data.ano_saida); 
          gotoxy(24,11);scanf("%d",&op_quarto);
          gotoxy(29,17);scanf("%d",&qtd_pessoa_global);
          gotoxy(54,17);scanf("%d",&qtd_crianca_global);
          gotoxy(95,17);scanf("%d",&idade_crianca); 
          
          strcpy(cliente.caracteristica.quarto,retorna_quarto(op_quarto,qtd_pessoa_global+qtd_crianca_global));
          cliente.caracteristica.qtd_pessoa=qtd_crianca_global+qtd_pessoa_global;
          quarto=tipo_quarto(cliente.caracteristica.quarto);
         
          
           vaga=vagas(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida,quarto);
           
                
                if(vaga==1) 
                {    verde();
                     gotoxy(40,25);printf("QUARTO DISPONIVEL NO MOMENTO"); 
                     gotoxy(90,30);printf(" (A) Avancar");
                } 

                else 
                {    
                    vermelho();
                     gotoxy(40,25);printf("QUARTO INDISPONIVEL NO MOMENTO"); 
                     
                }
          
       
          gotoxy(20,30);printf(" (M) voltar ao menu");
          gotoxy(50,30);printf(" (D) Digitar novas entradas");
          
          gotoxy(1,40); 
          limpar();
          escolha=getch(); 
          

          if(vaga == 1)
          {
              if(escolha=='M' || escolha=='m') menu_principal();

              else if(escolha == 'A' || escolha=='a') menu_responsavel();

              else 
               checar();
          } 

          else
          {
              if(escolha=='M' || escolha=='m') menu_principal();


              else
                checar(); 
          }
               
}  

void pegar_dados()
{  
     verde();  
     
     srand( (unsigned) time(NULL)); 

     cliente.num_reserva= rand()%100000;

     gotoxy(19,9);   limpar();    gets(cliente.nome);
     gotoxy(90,9);   limpar();    gets(cliente.data_nascimento); 
     gotoxy(19,11);  limpar();    gets(cliente.nacionalidade);
     gotoxy(56,11);  limpar();    gets(cliente.sexo);
     gotoxy(14,13);  limpar();    gets(cliente.endereco);
     gotoxy(58,13);  limpar();    gets(cliente.bairro);
     gotoxy(98,13);  limpar();    gets(cliente.cidade);
     gotoxy(123,13); limpar();    gets(cliente.estado);
     gotoxy(9,15);  limpar();     gets(cliente.cpf);
     gotoxy(44,15); limpar();     gets(cliente.rg);
     gotoxy(81,15); limpar();     gets(cliente.telefone);
     gotoxy(13,17); limpar();     gets(cliente.email);

     limpar();
     
} 

void acompanhante(int n)
{
    int i; 
    char op; 

    limpar(); 

    if(n==0) pagamento();

    for(i=0;i<n;i++)
    {   
        limpar_tela();
        fundo_normal();

        gotoxy(40,3);printf("Cadastro do acompanhante %d",i+1);
        
        limpar();
        gotoxy(20,5);printf("Nome:");
        gotoxy(27,5);scanf("%s",cliente.acompanhante[i].nome);
        
        limpar();
        gotoxy(20,7);printf("Data de nascimento:");
        gotoxy(41,7);scanf("%s",cliente.acompanhante[i].data);
        
        limpar();
        gotoxy(20,9);printf("Sexo:");
        gotoxy(28,9);scanf("%s",cliente.acompanhante[i].sexo);
        
        limpar();
        gotoxy(20,11);printf("Documento numero:");
        gotoxy(36,11);scanf("%s",cliente.acompanhante[i].documento);
    }
    
    verde();
     
    gotoxy(30,23);puts("Cadastramento feito com sucesso"); 
    

    gotoxy(50,25);printf(" (A) Avancar");
    gotoxy(30,25);printf(" (M) voltar "); 

   
     limpar(); 
     
     op=getch();

    if(op=='A' || op=='a') pagamento();

    else  menu_responsavel(); 

}  

void conclusao()
{
    verde();
    limpar_tela();
     
    gotoxy(50,7);puts("RESERVA FEITA COM SUCESSO"); 
    gotoxy(27,11);printf("Numero da reserva: %d",cliente.num_reserva); 
    gotoxy(27,13);printf("Nome do responsavel: %s",cliente.nome); 
    gotoxy(27,15);printf("Data da entrada: %d-%d-%d",cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada); 
    gotoxy(27,17);printf("Data da Saida: %d-%d-%d",cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida);
    gotoxy(27,19);printf("Modelo do quarto: %s",cliente.caracteristica.quarto); 
    gotoxy(27,21);printf("Acompanhante(s): %d",cliente.caracteristica.qtd_pessoa-1);
    gotoxy(50,24);printf("  SEJA BEM VINDO AO HOTEL");
    gotoxy(42,27);system("pause"); 
    
    cliente.total_tudo=0.0; 
    valor_quarto(cliente.caracteristica.quarto);
    descontar_vagas(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida,tipo_quarto(cliente.caracteristica.quarto));
    salvar(); 


    menu_principal();

} 

void pagamento()
{
   fundo_normal();
   limpar_tela();
   
      int op;


  gotoxy(50,7);puts("ADICIONAR PAGAMENTO");
  gotoxy(22,11);puts("1- Pagamento em dinheiro:");
  gotoxy(22,13);puts("2- Cartao de credito:");
  gotoxy(22,15);puts("3- Cartao de debito:");
  gotoxy(5,19);puts("Digite a opcao desejada:");
  gotoxy(30,19);scanf("%d",&op);
  
  if(op<=0 || op>4)
     pagamento();

  switch(op)
  {
       case 1: 
           gotoxy(45,21);system("pause");
           conclusao();
           break;

        case 2:
            cartao(2);
            gotoxy(45,21);system("pause");
            conclusao();
           break; 

        case 3:
            cartao(3);
            gotoxy(45,21);system("pause");
            conclusao();
            break;
  }

}

void cartao(int n)
{   
    limpar_tela();


    char operacao[15];

    if(n==2)
       strcpy(operacao,"credito");
       else 
         strcpy(operacao,"debito");

      gotoxy(50,7);puts("ADICIONAR CARTAO VALIDO");
      gotoxy(22,11);printf("Operacao a ser realizada: %s ",operacao);
      gotoxy(27,14);printf("Digite o numero do cartao:");
      
      limpar();
      
      gotoxy(54,14);gets(cliente.cartao); 
      gotoxy(50,17);puts("CARTAO ADICIONADO COM SUCESSO");

}

void salvar()    
{
	reservas=fopen("nomes.dat","ab+");
			
	fseek(reservas,0,SEEK_END);			
	fwrite(&cliente,sizeof(cliente),1,reservas);
	fclose(reservas);
} 

void listar()
{    
    limpar_tela();

    int i=0;


    gotoxy(50,6);puts("HOSPEDES QUE ESTAO AGORA NO HOTEL"); 
    gotoxy(10,10);puts("Num da reserva");
    gotoxy(35,10);puts("Nome");
    gotoxy(60,10);puts("Data de nascimento");
    gotoxy(86,10);puts("CPF");
    gotoxy(100,10);puts("Modelo do quarto");
    gotoxy(125,10);puts("Pessoas");
         

	reservas=fopen("nomes.dat","rb"); 
    
    while(fread(&cliente,sizeof(cliente),1,reservas)==1)
       {	
	        gotoxy(14,12+i);printf("%d",cliente.num_reserva);
        	gotoxy(30,12+i);printf("%s",cliente.nome);
	        gotoxy(63,12+i);printf("%s",cliente.data_nascimento);
        	gotoxy(80,12+i);printf("%s ",cliente.cpf);
	        gotoxy(99,12+i);printf("%s ",cliente.caracteristica.quarto);
	        gotoxy(127,12+i);printf("%d ",cliente.caracteristica.qtd_pessoa);
	   i+=2;
     }   

     fclose(reservas);
     
     limpar();
     verde();
     gotoxy(30,16+i);printf("( M ) Menu principal" );
     getch();
     menu_principal();

} 

void usuario()
{         
          limpar_tela();

          gotoxy(30,2);printf("RELATORIO DA RESERVA");
          
          gotoxy(6,4);printf("Dados pessoais:");
          gotoxy(6,5);printf("_____________________________________________________________________________________________________");
          gotoxy(6,6);printf("Numero da reserva: ");
          gotoxy(6,7);printf("_____________________________________________________________________________________________________");
          gotoxy(6,8);printf("Nome completo: ");
          gotoxy(75,8);printf("Data:");
          gotoxy(6,9);printf("_____________________________________________________________________________________________________");
          gotoxy(6,10);printf("Endereco: ");
          gotoxy(50,10);printf("Bairro: ");
          gotoxy(84,10);printf("cidade:"); 
          gotoxy(6,11);printf("_____________________________________________________________________________________________________");
          gotoxy(6,12);printf("Nacionalidade: ");
          gotoxy(55,12);printf("Sexo:");
          gotoxy(6,13);printf("_____________________________________________________________________________________________________");
          gotoxy(6,14);printf("Registro Geral: ");
          gotoxy(50,14);printf("Cpf:");
          gotoxy(75,14);printf("Telefone:");
          gotoxy(6,15);printf("_____________________________________________________________________________________________________");
          gotoxy(6,16);printf("E-mail:");
          gotoxy(6,17);printf("_____________________________________________________________________________________________________");
          gotoxy(6,19);printf("Dados da reserva:");
          gotoxy(6,20);printf("_____________________________________________________________________________________________________");
          gotoxy(6,21);printf("Data da entrada: ");
          gotoxy(40,21);printf("Data de saida:");
          gotoxy(72,21);printf("modelo do quarto:");
          gotoxy(6,22);printf("_____________________________________________________________________________________________________");
          gotoxy(6,23);printf("Responsavel: "); 
          gotoxy(65,23);printf("Registro Geral:");
          gotoxy(6,24);printf("_____________________________________________________________________________________________________");
          gotoxy(6,25);printf("Acompanhante 1: ");  
          gotoxy(65,25);printf("Registro Geral:");
          gotoxy(6,26);printf("_____________________________________________________________________________________________________");
          gotoxy(6,27);printf("Acompanhante 2: "); 
          gotoxy(65,27);printf("Registro Geral:");
          gotoxy(6,28);printf("_____________________________________________________________________________________________________");
          gotoxy(6,29);printf("acompanhante 3: "); 
          gotoxy(65,29);printf("Registro Geral:");
          gotoxy(6,30);printf("_____________________________________________________________________________________________________");
          gotoxy(6,32);printf("Servicos:");
          gotoxy(6,33);printf("_____________________________________________________________________________________________________");
          gotoxy(6,34);printf("Automovel:");
          gotoxy(40,34);printf("Tanque cheio:");
          gotoxy(65,34);printf("Seguro:");
          gotoxy(85,34);printf("total:");
          gotoxy(6,35);printf("_____________________________________________________________________________________________________");
          gotoxy(6,36);printf("Babysitter:");
          gotoxy(40,36);printf("Horas:");
          gotoxy(80,36);printf("Total:");
          gotoxy(6,37);printf("_____________________________________________________________________________________________________");
          gotoxy(6,38);printf("restaurante:");
          gotoxy(40,38);printf("refeicoes:");
          gotoxy(80,38);printf("Total:");
          gotoxy(6,39);printf("_____________________________________________________________________________________________________");
          gotoxy(6,40);printf("Cama extra:");
          gotoxy(40,40);printf("Quantidade:");
          gotoxy(80,40);printf("Total:");
          gotoxy(6,41);printf("_____________________________________________________________________________________________________"); 

          gotoxy(6,43);printf("Total a ser pago:");

           //mostrar
       
          verde();

        gotoxy(26,6);printf("%d",cliente.num_reserva);
        gotoxy(21,8);printf("%s",cliente.nome);
        gotoxy(82,8);printf("%s",cliente.data_nascimento);
        gotoxy(17,10);printf("%s",cliente.endereco);
        gotoxy(59,10);printf("%s",cliente.bairro);
        gotoxy(92,10);printf("%s-%s",cliente.cidade,cliente.estado);
        gotoxy(21,12);printf("%s",cliente.nacionalidade);
        gotoxy(61,12);printf("%s",cliente.sexo);
        gotoxy(22,14);printf("%s",cliente.rg);
        gotoxy(55,14);printf("%s",cliente.cpf);
        gotoxy(85,14);printf("%s",cliente.telefone);
        gotoxy(14,16);printf("%s",cliente.telefone);
        gotoxy(23,21);printf("%d-%d-%d",cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada);
        gotoxy(55,21);printf("%d-%d-%d",cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida);
        gotoxy(90,21);printf("%s",cliente.caracteristica.quarto);
        gotoxy(19,23);printf("%s",cliente.nome);
        gotoxy(81,23);printf("%s",cliente.cpf);
        gotoxy(22,25);printf("%s",cliente.acompanhante[0].nome);
        gotoxy(81,25);printf("%s",cliente.acompanhante[0].documento);
        gotoxy(22,27);printf("%s",cliente.acompanhante[1].nome);
        gotoxy(81,27);printf("%s",cliente.acompanhante[1].documento);
        gotoxy(22,29);printf("%s",cliente.acompanhante[2].nome);
        gotoxy(81,29);printf("%s",cliente.acompanhante[2].documento);
        gotoxy(54,34);printf("%d",cliente.servico.tanque);
        gotoxy(73,34);printf("%d",cliente.servico.seguro);
        gotoxy(92,34);printf("Rs %.1f",cliente.servico.carro_total);
        gotoxy(47,36);printf("%d",cliente.servico.babysitter);
        gotoxy(87,36);printf("Rs %.1f",cliente.servico.babysitter_total);
        gotoxy(51,38);printf("%d",cliente.servico.restaurante);
        gotoxy(87,38);printf("Rs %.1f",cliente.servico.restaurante_total);
        gotoxy(52,40);printf("%d",cliente.servico.cama_extra);
        gotoxy(87,40);printf("Rs %.1f",cliente.servico.cama_extra_total);
        gotoxy(24,43);printf("Rs %.1f",cliente.total_tudo);

       limpar();

       gotoxy(30,45);getch();

        
} 

void buscar()
{   
    
    limpar_tela();
    fundo_normal();

    int op;
    int reserva;
    char busca[15]; 
    char resultado;
    int resultado2=0; 
    


       gotoxy(50,7);puts("BUSCAR RESERVA");
       gotoxy(22,11);puts("1- Buscar pela numero da reserva:");
       gotoxy(22,13);puts("2- Buscar pelo nome:");
       gotoxy(5,17);puts("Digite a opcao desejada:");
       gotoxy(32,17);scanf("%d",&op); 

       reservas=fopen("nomes.dat","rb+");
       rewind(reservas);
       limpar();
       
       switch(op)
       {
           case 1:
               
               gotoxy(22,22);printf("Digite o numero da reserva:");
               gotoxy(51,22);scanf("%d",&reserva);
               
                while(fread(&cliente,sizeof(cliente),1,reservas)==1)
                     {
                        if(cliente.num_reserva == reserva)
                                {   
                                    limpar();
                                    usuario(); 
                                    resultado='S';  
                                    
                                    menu_principal();               
                                }
                    } 
                    fclose(reservas);

                
                  
                   if(resultado!='S') 
                   {
                         gotoxy(50,25);puts("Nenhum hospede encontrado");
                         getch();
                         menu_principal();

                   } 

                  break; 

           case 2: 
              limpar();
              gotoxy(22,22);printf("Digite o nome do responsavel:");
              gotoxy(53,22);
              gets(busca);
             

                 while(fread(&cliente,sizeof(cliente),1,reservas)==1)
                   {
                        if(strcmp(cliente.nome , (busca))==0 )
                            {   
                                limpar();
                                usuario();
                                resultado2++;
                                
                                menu_principal();
                                   break;
                            
                            } 
                    } 

                    fclose(reservas);

                
                      if(resultado2 == 0) 
                      {
                          gotoxy(50,25);puts("Nenhum hospede encontrado");
                          getch();
                          menu_principal();
                    } 

                break;

                default:
                    menu_principal();
               
       }
} 

int existe(int t)  	
{
	rewind(reservas);
	while(fread(&cliente,sizeof(cliente),1,reservas)==1)	
        if(cliente.num_reserva==t)
	         return 0;
               		
      return 1; 	

} 

void editar()
{   

    limpar_tela();

    int busca;
    int resultado=0;

    gotoxy(30,3);puts("EDITAR DADOS DO USUARIO");
    gotoxy(10,6);printf("Digite o numero da reserva:");
    scanf("%d",&busca);  
    
    limpar();

    reservas=fopen("nomes.dat","rb+");
		while(fread(&cliente,sizeof(cliente),1,reservas)==1)
		{
			if(existe(busca)==0)  
			{
				
				gotoxy(40,8);printf("Hospede encontrado");
            
			
				gotoxy(20,11);printf("O Numero da reserva:%d",cliente.num_reserva);
                
                limpar();
				gotoxy(20,13);printf("Nome( %s ): ",cliente.nome); gets(cliente.nome);

                limpar();
				gotoxy(20,15);printf("Data de nascimento ( %s ): ",cliente.data_nascimento);gets(cliente.data_nascimento);
				
                limpar();
				gotoxy(20,17);printf("Endereco (%s): ",cliente.endereco);gets(cliente.endereco);
                
				resultado++;

		
				gotoxy(40,20);printf("Alterado com sucesso");

				fseek(reservas,ftell(reservas)-sizeof(cliente),0);	 
				fwrite(&cliente,sizeof(cliente),1,reservas);	
				fclose(reservas);
               
			}

			
		}  

        if(resultado==0)
			{
				gotoxy(40,8);printf("Nada encontrado");
			}
        
        limpar();
        getch();
        menu_principal();


} 

void tabela_preco()
{   
    gotoxy(35,3);printf("TABELA DE PRECOS");
    gotoxy(15,5);printf("MODELO DE QUARTOS");
    gotoxy(4,7);printf("Executivo simples: %.2f ",admin.executivo_simples);
    gotoxy(4,9);printf("Executivo duplo: %.2f ",admin.executivo_duplo);
    gotoxy(4,11);printf("Executivo triplo: %.2f ",admin.executivo_triplo);
    gotoxy(4,13);printf("Luxo simples: %.2f ",admin.luxo_simples);
    gotoxy(4,15);printf("Luxo duplo: %.2f ",admin.luxo_duplo);
    gotoxy(4,17);printf("Luxo triplo: %.2f",admin.luxo_triplo);
    gotoxy(4,19);printf("Presidencial: %.2f ",admin.presidencial);
    gotoxy(50,5);printf("SERVICOS");
    gotoxy(55,7);printf("Cama adicional: %.2f ",admin.cama_extra);
    gotoxy(55,9);printf("Babysitter: %.2f ",admin.babysitter);
    gotoxy(55,11);printf("Automovel de luxo: %.2f ",admin.carro_luxo);
    gotoxy(55,13);printf("Automovel executivo: %.2f ",admin.carro_executivo);
    gotoxy(55,15);printf("tanque cheio: %.2f ",admin.tanque);
    gotoxy(55,17);printf("Seguro: %.2f ",admin.seguro);
    gotoxy(55,19);printf("Refeicao: %.2f ",admin.restaurante);
     
     gotoxy(15,30);printf("OBS: Precos podem variar de acordo com o periodo");
} 

void listar_precos()
{    
    limpar_tela();

     preset=fopen("Preset.dat","rb+");

		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
			tabela_preco();
		}
				
        fclose(preset); 

                limpar();
                getch();
                menu_principal();
} 

void listar_precos_admin()
{    
    limpar_tela();

     preset=fopen("Preset.dat","rb+");

		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
			tabela_preco();
		}
				
        fclose(preset); 

                limpar();
                getch();
                menu_admin();
}

char* retorna_quarto(int n,int qtd_pessoa)
{
     
     if(n==1) return "presidencial";

     else if(n==2)
     {
            if(qtd_pessoa ==  1) return "Executivo_Simples"; 

             if(qtd_pessoa  == 2) return "Executivo_Duplo"; 

             else return "Executivo_Triplo";
     } 

     else 
     {
         if(qtd_pessoa ==  1) return "Luxo_Simples"; 

             if(qtd_pessoa  == 2) return "Luxo_Duplo"; 

             else return "Luxo_Triplo";

     }

}

int tipo_quarto(char nome[30])
{
   if(strcmp(nome,"presidencial")==0) return 0;

   else if(strcmp(nome,"Luxo_Simples")==0) return 1;

   else if(strcmp(nome,"Luxo_Duplo")==0) return 2;

   else if(strcmp(nome,"Luxo_Triplo")==0) return 3;
   
   else if(strcmp(nome,"Executivo_Simples")==0) return 4; 

   else if(strcmp(nome,"Executivo_Duplo")==0) return 5;

   else 
      
        return 6;  
}

void valor_quarto(char nome[30])
{
     if(strcmp(nome,"presidencial")==0)    
     { 
       cliente.total_tudo+=(admin.presidencial*controle * tempo_estadia(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida));
       cliente.caracteristica.preco_quarto=cliente.total_tudo;
     }
     
   else if(strcmp(nome,"Luxo_Simples")==0)  
      {  
          cliente.total_tudo+=(admin.luxo_simples *controle *tempo_estadia(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida));
           cliente.caracteristica.preco_quarto=cliente.total_tudo;
      }
   else if(strcmp(nome,"Luxo_Duplo")==0)  
       {
           cliente.total_tudo+=(admin.luxo_duplo *controle * tempo_estadia(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida));
            cliente.caracteristica.preco_quarto=cliente.total_tudo;
       }
   else if(strcmp(nome,"Luxo_Triplo")==0) 
        { 
            cliente.total_tudo+=(admin.luxo_triplo *controle * tempo_estadia(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida));
             cliente.caracteristica.preco_quarto=cliente.total_tudo;
        }
   else if(strcmp(nome,"Executivo_Simples")==0) 
        { 
            cliente.total_tudo+=(admin.executivo_simples *controle* tempo_estadia(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida));
             cliente.caracteristica.preco_quarto=cliente.total_tudo;
        }
   else if(strcmp(nome,"Executivo_Duplo")==0)  
        {
            cliente.total_tudo+=(admin.executivo_duplo *controle*tempo_estadia(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida)); 
             cliente.caracteristica.preco_quarto=cliente.total_tudo;
        }
   else 
   {
       cliente.total_tudo+=(admin.executivo_triplo *controle* tempo_estadia(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida));
        cliente.caracteristica.preco_quarto=cliente.total_tudo;
   }
}
int bissexto(int ano)
{ 
  if (ano % 4 == 0 && (ano % 400 == 0 || ano % 100 != 0)) 
    return 1;
  
    else 
      return 0;
} 

int qtd_dias(int num,int ano)
{

    ano=bissexto(ano);

    switch(num)
    {
        case 1:
        num=31;
        break;

        case 2: 
        num=28;
        break;

        case 3:
        num=31;
        break;

        case 4:
        num=30;
        break;

        case 5:
        num=31;
        break;

        case 6:
        num=30;
        break;

        case 7:
        num=31;
        break;

       case 8:
       num=31;
       break;

      case 9:
      num=30;
      break;
                
      case 10:
      num=31;
      break;

      case 11:
      num=30;
      break;
                
     case 12:
     num=31;
     break;
                          
    } 
    
    if(ano==1 && num==2)  
    {
        num=29;
    }

  return num;

} 

int verificar(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes)
{
     int fim_mes; 
     int i,j;
     int vaga=1;
     int qtd_mes;  
     int aux=mes;
     
    

      if( mes_entrada == mes_saida)
  { 
      fim_mes=dia_saida;
  } 
  
  if(mes_entrada == 12 && mes_saida==1)
  {
       
      
       fim_mes=qtd_dias(12,ano_entrada);

    
 
 for(int k=mes;k<aux+1;k++) 
 { 
     for(int i=0;i<=1;i++)
         {
            for(int j=dia_entrada;j<=fim_mes;j++)
                {   

                    if(i==0)
                    {
                       
                        if( admin.disponivel.quartos[k][i+12][j] <= 0) vaga--; 

                    } 

                    else 
                    {
                       
                        if( admin.disponivel.quartos[k][i][j] <= 0) vaga--; 
                    }
                    
                        

                 }        
        
           dia_entrada=1;
        fim_mes=dia_saida;
       
    
        } 

        
 } 

      mes_entrada=12; 

    goto especial;

  } 


  else 
  { 
      fim_mes=qtd_dias(mes_entrada,ano_entrada);
  
  } 
   

  
   

  for(int k=mes;k ==aux ;k++)
  {
     for(i=mes_entrada;i<=mes_saida ;i++)
       {
          for(j=dia_entrada;j<=fim_mes;j++)
             {  
                
                 if( admin.disponivel.quartos[k][i][j] <= 0) vaga--;
             }   
          
           dia_entrada=1;
           fim_mes=dia_saida; 

        }
  } 
  
 especial:
  

   if(vaga <=0) 
       return 0;

       else 
          return 1;
} 

int tempo_estadia(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida)
{
   int fim_mes;
   int dias=-1;
   int meses=1;

   if(mes_entrada == mes_saida)
   {
     fim_mes=dia_saida;
     meses=0;
   }
   
   else
     fim_mes=qtd_dias(mes_entrada,ano_entrada);
   
  
  
        for(int i=0;i<=meses;i++)
       {
         for(int j=dia_entrada;j<=fim_mes;j++)
          {
            
            dias++;
          } 
       
           dia_entrada=1;
          fim_mes=dia_saida;
       }
     

   
   return dias;
} 
int vagas(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int n)
{
     preset=fopen("Preset.dat","rb+");
    
     int x;

		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
					x=verificar(dia_entrada,mes_entrada,ano_entrada,dia_saida,mes_saida,ano_entrada,n);
		}
				fclose(preset); 

                if(x==0) 
                   return 0;
                
                 else 
                 return 1; 

}

void descontar_vagas(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes)
{
     preset=fopen("Preset.dat","rb+");
		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
				descontar(dia_entrada,mes_entrada,ano_entrada,dia_saida,mes_saida,ano_saida,mes);
				
				fseek(preset,ftell(preset)-sizeof(struct admin),0);	
				fwrite(&admin,sizeof(struct admin),1,preset);	
				fclose(preset);
			}
} 

void descontar(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes)
{
     int fim_mes; 
     int i,j;
     int vaga=1;
     int qtd_mes;  
     int aux=mes;
     
    

      if( mes_entrada == mes_saida)
  { 
      fim_mes=dia_saida;
  } 
  
  if(mes_entrada == 12 && mes_saida==1)
  {
       
      
       fim_mes=qtd_dias(12,ano_entrada);

    
 
 for(int k=mes;k<aux+1;k++) 
 { 
     for(int i=0;i<=1;i++)
         {
            for(int j=dia_entrada;j<=fim_mes;j++)
                {   

                    if(i==0)
                    {
                       
                        admin.disponivel.quartos[k][i+12][j]--; 

                    } 

                    else 
                    {
                       
                        admin.disponivel.quartos[k][i][j]--;
                    }
                    
                        

                 }        
        
           dia_entrada=1;
        fim_mes=dia_saida;
       
    
        } 

        
 } 

      mes_entrada=12; 

    goto especial;

  } 


  else 
  { 
      fim_mes=qtd_dias(mes_entrada,ano_entrada);
  
  } 
   

  
   

  for(int k=mes;k ==aux ;k++)
  {
     for(i=mes_entrada;i<=mes_saida ;i++)
       {
          for(j=dia_entrada;j<=fim_mes;j++)
             {  
                
                admin.disponivel.quartos[k][i][j]--;
             }   
          
           dia_entrada=1;
           fim_mes=dia_saida; 

        }
  } 
  
    especial:
  

  return;
} 

void aumentar(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes)
{
     int fim_mes; 
     int i,j;
     int vaga=1;
     int qtd_mes;  
     int aux=mes;
     
    

      if( mes_entrada == mes_saida)
      { 
         fim_mes=dia_saida;
      } 
  
  if(mes_entrada == 12 && mes_saida==1)
  {
       
      
       fim_mes=qtd_dias(12,ano_entrada);

    
 
 for(int k=mes;k<aux+1;k++) 
 { 
     for(int i=0;i<=1;i++)
         {
            for(int j=dia_entrada;j<=fim_mes;j++)
                {   

                    if(i==0)
                    {
                       
                        admin.disponivel.quartos[k][i+12][j]++; 

                    } 

                    else 
                    {
                       
                        admin.disponivel.quartos[k][i][j]++;
                    }
                    
                        

                 }        
        
           dia_entrada=1;
        fim_mes=dia_saida;
       
    
        } 

        
 } 

      mes_entrada=12; 

    goto especial;

  } 


  else 
  { 
      fim_mes=qtd_dias(mes_entrada,ano_entrada);
  
  } 
   

  
   

  for(int k=mes;k ==aux ;k++)
  {
     for(i=mes_entrada;i<=mes_saida ;i++)
       {
          for(j=dia_entrada;j<=fim_mes;j++)
             {  
                
                admin.disponivel.quartos[k][i][j]++;
             }   
          
           dia_entrada=1;
           fim_mes=dia_saida; 

        }
  } 
  
    especial:
  

  return;
} 

void aumentar_vagas(int dia_entrada,int mes_entrada,int ano_entrada,int dia_saida,int mes_saida,int ano_saida,int mes)
{
     preset=fopen("Preset.dat","rb+");
		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
				aumentar(dia_entrada,mes_entrada,ano_entrada,dia_saida,mes_saida,ano_saida,mes);
				
				fseek(preset,ftell(preset)-sizeof(struct admin),0);	
				fwrite(&admin,sizeof(struct admin),1,preset);	
				fclose(preset);
		}
} 

void inicializacao_preset()
{
     preset=fopen("Preset.dat","rb+");

		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
					
		}
			fclose(preset);
}

void disponibilidade()
{   

    limpar_tela();
    fundo_normal();

    int dia_entrada_global,mes_entrada_global,ano_entrada_global;
     int dia_saida_global,mes_saida_global,ano_saida_global; 
    int op_quarto;
    int idade_crianca;
    int vaga;
    char  escolha;
    int j=0;
    char op;
     
     
     gotoxy(40,3);printf("SISTEMA DE RESERVA");
 
          gotoxy(6,5);printf("_____________________________________________________________________________________________________");
          gotoxy(6,7);printf("Data da entrada: ");
          gotoxy(6,8);printf("Data da Saida: ");
          gotoxy(6,9);printf("_____________________________________________________________________________________________________");
          gotoxy(6,11);printf("Modelo do quarto: "); 
          gotoxy(15,13);printf("1- Presidencial");
          gotoxy(35,13);printf("2- Executivo");
          gotoxy(50,13);printf("3- Luxo");
          gotoxy(6,15);printf("_____________________________________________________________________________________________________");
          gotoxy(6,17);printf("Quantidade de pessoas: ");
          gotoxy(45,17);printf("crianca: ");
          gotoxy(75,17);printf("Idade da crianca: ");
          gotoxy(6,19);printf("_____________________________________________________________________________________________________");
    
          azul();

          gotoxy(23,7);scanf("%d-%d-%d",&dia_entrada_global,&mes_entrada_global,&ano_entrada_global);
          gotoxy(21,8);scanf("%d-%d-%d",&dia_saida_global,&mes_saida_global,&ano_saida_global); 
          gotoxy(24,11);scanf("%d",&op_quarto);
          gotoxy(29,17);scanf("%d",&qtd_pessoa_global);
          gotoxy(54,17);scanf("%d",&qtd_crianca_global);
          gotoxy(95,17);scanf("%d",&idade_crianca); 
          strcpy(cliente.caracteristica.quarto,retorna_quarto(op_quarto,qtd_pessoa_global+qtd_crianca_global));
          
           quarto=tipo_quarto(cliente.caracteristica.quarto);
          
           vaga=vagas(dia_entrada_global,mes_entrada_global,ano_entrada_global,dia_saida_global,mes_saida_global,ano_saida_global,quarto);
            
            verde();
           
           if(vaga==1) 
           {
               gotoxy(45,22);printf("Seu modelo esta disponivel");
           } 

           gotoxy(40,25);printf("Temos esses modelos tambem disponiveis para essa data");
          
          verde();
           
           for(int i=0;i<7 ;i++)
           {
              vaga=vagas(dia_entrada_global,mes_entrada_global,ano_entrada_global,dia_saida_global,mes_saida_global,ano_saida_global,i); 
              
              if(vaga==1);gotoxy(60,26+j);
              {
                  printf("%s",retorna_nome(i));
                  j++;
              }
           } 

           gotoxy(35,37);printf("( M ) voltar ao menu                ( V ) Para realizar outra consulta");

          limpar();
           
           op=getch();

           if(op =='M' || op=='m') menu_principal();

           else disponibilidade();


           
}

char *retorna_nome(int num)
{
     if(num==0) return "Presidencial";

     else if(num==1) return "Luxo simples";

     else if(num==2) return "Luxo Duplo";

     else if(num==3) return "Luxo Triplo";

     else if(num==4) return "Executivo Simples";

     else if(num==5) return "Executivo Duplo";

     else return "Executivo Triplo";

} 

void menu_servicos()
{   
    limpar_tela();

    int op;
  
    gotoxy(35,6);printf("ADICIONAR SERVICO");
    gotoxy(20,9); printf("1- Automovel");
    gotoxy(20,11);printf("2- Babysitter");
    gotoxy(20,13); printf("3- Restaurante"); 
    gotoxy(20,15);printf("4- Adicionar cama extra");
    gotoxy(20,17);printf("5- voltar ao menu principal");
    gotoxy(15,20);printf("Digite a opcao desejada: ");
    scanf("%d",&op); 

    switch(op)
    {
        case 1:
        alterar_carro();
        break;

        case 2:
        alterar_babysitter();
        break;

        case 3:
        alterar_restaurante();
        break; 

        case 4:
        alterar_cama();
        break;

        case 5:
        menu_principal();
        break;

        default:
        menu_servicos();
    }
} 

void deletar()
{     
     limpar_tela();

    int d;
    int num;
    int achou=0;
    char op;
     
     gotoxy(30,3);printf("Fechamento de reserva");
    
     gotoxy(15,5);printf("Digite o numero da reserva: ");
     scanf("%d",&num); 

     reservas=fopen("nomes.dat","rb+");
     rewind(reservas);
     limpar();

         while(fread(&cliente,sizeof(cliente),1,reservas)==1)
         {
             if(cliente.num_reserva ==num)
             {     
                 achou++;
                    gotoxy(25,7);puts("Registro encontrado");
                    gotoxy(25,8);puts("Por favor assine o acordo no balcao");
                     gotoxy(25, 11);puts("( M ) Voltar ao menu principal    ( A ) Prosseguir com encerramento da reserva");
                     
                     limpar();
                     op=getch();
                     
                     if(op=='a' || op=='A') goto fim;

                     else menu_principal();
             }
         } 

         if(achou ==0)
         {      
                gotoxy(25,7);puts("nenhum Registro encontrado");
               gotoxy(25,11);puts("( M ) Voltar ao menu principal");
               op=getch();
               menu_principal();

         } 

         fim:
   
    limpar_tela();
    gotoxy(30,3);printf("Fechamento de reserva");
    gotoxy(30,5);printf("Digite novamente o numero da reserva para continuar: ");
    gotoxy(84,5);scanf("%d",&d);
     
     cliente.total_tudo+=( tempo_estadia(cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida,dia_atual,mes_atual,ano_atual) -1   * admin.multa );
     aumentar_vagas(cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada,cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida,tipo_quarto(cliente.caracteristica.quarto));
     contrato_texto(cliente.nome); 

    rewind(reservas);
    while(fread(&cliente,sizeof(cliente),1,reservas)==1)
    {
    }
         FILE* ft=fopen("temp.dat","wb+");   
        rewind(reservas);                   
        while(fread(&cliente,sizeof(cliente),1,reservas)==1)
        {
            if(cliente.num_reserva!=d)
            {
            fseek(ft,0,SEEK_CUR);
            fwrite(&cliente,sizeof(cliente),1,ft);    
            }                              
        }

        fclose(ft);
         fclose(ft);
        fclose(reservas);  
          fclose(reservas); 
            fclose(reservas);  
          fclose(reservas); 
            fclose(reservas);  
          fclose(reservas); 
         
        
     
       
   
    remove("nomes.dat");
      system( "ren temp.dat nomes.dat" ); 
       //reservas=fopen("nomes.dat","ab+")  ;
         
    gotoxy(45,7);printf("CHECKOUT FEITO COM SUCESSO,OBRIGADO POR SUA ESTADIA ");

    getch();
    menu_principal();
    
}  

void alterar_babysitter()
{   
    limpar_tela();

    int busca;
    int resultado=0;
    int horas;
    int preco=0;

    gotoxy(30,5);printf("SESSAO ADICIONAL");
    gotoxy(15,7);printf("Digite o numero da reserva");
    gotoxy(45,7);scanf("%d",&busca); 
    limpar();

    reservas=fopen("nomes.dat","rb+");
		while(fread(&cliente,sizeof(cliente),1,reservas)==1)
		{
			if(existe(busca)==0)  //ver se existe
			{
				
			  gotoxy(40,10);printf("Cliente disponivel");
			
				gotoxy(15,12);puts("adicionar quantas horas do servico de babysitter:");
                gotoxy(66,12);scanf("%d",&horas);
                cliente.servico.babysitter+=horas;
                cliente.servico.babysitter_total+= (horas *controle * admin.babysitter) ;
                cliente.servico.total_servico+=(horas *controle* admin.babysitter) ;
                cliente.total_tudo+=(horas *controle* admin.babysitter);

                
				resultado=1;

				 gotoxy(40,15);printf("SERVICO ENCERRADO");
				fseek(reservas,ftell(reservas)-sizeof(cliente),0);	
				fwrite(&cliente,sizeof(cliente),1,reservas);	
				fclose(reservas);
			}
			if(resultado==0)
			{
			
				gotoxy(30,5);printf("Nenhum cliente registrado");
			}
		} 

        limpar();
        getch();
        menu_servicos();
        
} 
void alterar_quartos_admin()
{
     limpar_tela();
     
     preset=fopen("Preset.dat","rb+");

		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
				gotoxy(30,5);printf("ALTERAR PRECO DAS DIARIAS");
				
                limpar();
				gotoxy(15,8);printf("Presidencial (%.2f):",admin.presidencial);
                
                gotoxy(40,8);scanf("%f",&admin.presidencial);
				
                limpar();
				gotoxy(15,10);printf("luxo simples (%.2f):",admin.luxo_simples);
                
                gotoxy(39,10);scanf("%f",&admin.luxo_simples);
			    
                limpar();
				gotoxy(15,12);printf("luxo duplo (%.2f):",admin.luxo_duplo);
                
                gotoxy(39,12);scanf("%f",&admin.luxo_duplo);
	            
                limpar();
                gotoxy(15,14);printf("luxo triplo (%.2f):",admin.luxo_triplo);
                
                gotoxy(39,14);scanf("%f",&admin.luxo_triplo);
				
                limpar();
                gotoxy(15,16);printf("Executivo simples (%.2f):",admin.executivo_simples);
                
                gotoxy(44,16);scanf("%f",&admin.executivo_simples);
				
                limpar();
                gotoxy(15,18);printf("Executivo duplo (%.2f):",admin.executivo_duplo);
                
                gotoxy(42,18);scanf("%f",&admin.executivo_duplo);
                
                limpar();
                gotoxy(15,20);printf("Executivo triplo (%.2f):",admin.executivo_triplo);
                
                gotoxy(43,20);scanf("%f",&admin.executivo_triplo);
				
				
                limpar();		
				gotoxy(30,23);printf("PRECOS ALTERADOS");

				fseek(preset,ftell(preset)-sizeof(struct admin),0);	
				fwrite(&admin,sizeof(struct admin),1,preset);	
				fclose(preset);
			}
                getch();
                menu_admin();
} 

void alterar_servicos_admin()
{
     
     limpar_tela();

     preset=fopen("Preset.dat","rb+");

		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
			
				gotoxy(30,5);printf("ALTERAR PRECO DOS SERVICOS");
				
                limpar();
				gotoxy(15,8);printf("Babysitter hora (%.2f):",admin.babysitter);
                gotoxy(40,8);scanf("%f",&admin.babysitter);
                
                limpar();
                gotoxy(15,10);printf("carro luxo (%.2f):",admin.carro_luxo);
                gotoxy(37,10);scanf("%f",&admin.carro_luxo);
                
                limpar();
                gotoxy(15,12);printf("carro executivo (%.2f):",admin.carro_executivo);
                gotoxy(41,12);scanf("%f",&admin.carro_executivo);
                
                limpar();
                gotoxy(15,14);printf("Seguro (%.2f):",admin.seguro);
                gotoxy(37,14);scanf("%f",&admin.seguro);
                
                limpar();
                gotoxy(15,16);printf("Tanque cheio (%.2f):",admin.tanque);
                gotoxy(38,16);scanf("%f",&admin.tanque);
                
                limpar();
                gotoxy(15,18);printf("Refeicao (%.2f):",admin.restaurante);
                gotoxy(36,18);scanf("%f",&admin.restaurante);
                
                limpar();
                gotoxy(15,20);printf("Cama extra (%.2f):",admin.cama_extra);
                gotoxy(37,20);scanf("%f",&admin.cama_extra);
                
		
				gotoxy(30,23);printf("PRECOS ALTERADOS");
				fseek(preset,ftell(preset)-sizeof(struct admin),0);	
				fwrite(&admin,sizeof(struct admin),1,preset);	
				fclose(preset);
			} 
             limpar();
             getch();
            menu_admin();
} 

void menu_admin()
{
    limpar();
    limpar_tela();
    fundo_normal();

    int op;
    
       gotoxy(40,5);printf("MENU DO ADMINISTRADOR");
       gotoxy(25,8);printf("1- Ver tabela de precos");
       gotoxy(25,10);printf("2- Alterar precos das diarias");
       gotoxy(25,12);printf("3- Alterar precos dos servicos");
       gotoxy(25,14);printf("4- Alterar preco em estacoes e multas");
       gotoxy(25,16);printf("5- Alterar dados de login");
       gotoxy(25,18);printf("6- Retornar ao menu principal");
       gotoxy(10,22);printf("Digite a opcao desejada:");
       gotoxy(35,22);scanf("%d",&op); 

            switch(op)
            {

                   case 1:
                   listar_precos_admin();
                   break;

                   case 2:
                   alterar_quartos_admin();
                   break; 

                   case 3:
                   alterar_servicos_admin();
                   break;

                   case 4:
                   alterar_taxa_admin();
                   break;
                   
                   case 5:
                   alterar_login_admin();
                   break;

                   case 6:
                   menu_principal();
                   break;

                   default:
                   menu_admin();
                   break;
                   
            }

} 

void alterar_taxa_admin()
{
   limpar_tela();
   
   preset=fopen("Preset.dat","rb+");

		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
			
				gotoxy(30,5);printf("ALTERAR PRECO DAS TAXAS");
				
                limpar();
				gotoxy(15,8);printf("Controle de precos em periodos especiais (%.2f):",admin.controle_preco);
                gotoxy(65,8);scanf("%f",&admin.controle_preco);
                
                limpar();
                gotoxy(15,10);printf("Multa por dia (%.2f):",admin.multa);
                gotoxy(39,10);scanf("%f",&admin.multa);
                
				gotoxy(30,13);printf("PRECOS ALTERADOS");
				fseek(preset,ftell(preset)-sizeof(struct admin),0);	
				fwrite(&admin,sizeof(struct admin),1,preset);	
				fclose(preset);
			} 
             
             limpar();
             getch();
             menu_admin();
} 

void alterar_login_admin()
{
       limpar_tela();
              
       preset=fopen("Preset.dat","rb+");

		while(fread(&admin,sizeof(struct admin),1,preset)==1)
		{
			
				gotoxy(30,5);printf("ALTERAR DADOS DO LOGIN");
				
                limpar();
				gotoxy(15,8);printf("Novo login (%s):",admin.login);
                gotoxy(37,8);scanf("%s",admin.login);
                
                limpar();
                gotoxy(15,10);printf("Nova senha (%s):",admin.senha);
                gotoxy(35,10);scanf("%s",admin.senha);
                
				gotoxy(30,13);printf("LOGIN ALTERADO");
				fseek(preset,ftell(preset)-sizeof(struct admin),0);	
				fwrite(&admin,sizeof(struct admin),1,preset);	
				fclose(preset);
			} 
             
             limpar();
             getch();
             menu_admin();
} 

void login()
{  
    fundo_normal();
    limpar_tela();

    char nome[15];
    char senha[15];
    int i = 0;
	char letra;
       
     gotoxy(34,12);printf("************************************************");
     gotoxy(34,13);printf("***                                          ***");
     gotoxy(34,14);printf("***  USUARIO:                                ***");
     gotoxy(34,15);printf("***                                          ***");
     gotoxy(34,16);printf("***  SENHA:                                  ***");
    gotoxy(34,17); printf("***                                          ***");
     gotoxy(34,18);printf("************************************************");
     
     verde();
     gotoxy(48,14);scanf("%s",nome); 
     
     gotoxy(46,16);

	
	while(1){
		letra = getch();	

		if(letra == 13 || letra== 9){ 
			senha[i] = '\0';
			break;
		}else if(letra == 8){ 
			if(i > 0){
				i--;
				printf("\b \b");		
			}
		}else{
			senha[i++] = letra;
			printf("* \b");			
		}
	}  

    limpar();
      
      if( !strcmp( nome,admin.login) && !strcmp(senha,admin.senha)) 
      {   
          verde();
          limpar();
          gotoxy(45,22);printf("ACESSO PERMITIDO");
          getch();
          menu_principal();

      }

      else 
      {   
          vermelho();
          gotoxy(45,22);printf("ACESSO NEGADO");
          limpar();
          getch();
      }
} 
void login_admin()
{  
    fundo_normal();
    limpar_tela();

    char nome[15];
    char senha[15];
    int i = 0;
	char letra;
       
     gotoxy(34,12);printf("************************************************");
     gotoxy(34,13);printf("***                                          ***");
     gotoxy(34,14);printf("***  USUARIO:                                ***");
     gotoxy(34,15);printf("***                                          ***");
     gotoxy(34,16);printf("***  SENHA:                                  ***");
    gotoxy(34,17); printf("***                                          ***");
     gotoxy(34,18);printf("************************************************");
     
     verde();
     gotoxy(48,14);scanf("%s",nome); 
     
     gotoxy(46,16);

	
	while(1){
		letra = getch();	

		if(letra == 13 || letra== 9){ 
			senha[i] = '\0';
			break;
		}else if(letra == 8){ 
			if(i > 0){
				i--;
				printf("\b \b");		
			}
		}else{
			senha[i++] = letra;
			printf("* \b");			
		}
	}  

    limpar();
      
      if( !strcmp( nome,admin.login) && !strcmp(senha,admin.senha)) 
      {   
          verde();
          limpar();
          gotoxy(45,22);printf("ACESSO PERMITIDO");
          getch();
          menu_admin();

      }

      else 
      {   
          vermelho();
          gotoxy(45,22);printf("ACESSO NEGADO");
          limpar();
          getch();
          menu_principal();
      }
} 

void alterar_carro()
{
    limpar();
    limpar_tela();

    int busca;
    int resultado=0;
    int modelo;
    char escolha;

   gotoxy(30,5);printf("SESSAO AUTOMOVEL");
   gotoxy(15,7);printf("Digite o numero da reserva");
   gotoxy(45,7);scanf("%d",&busca);  

    reservas=fopen("nomes.dat","rb+");
		while(fread(&cliente,sizeof(cliente),1,reservas)==1)
		{
			if(existe(busca)==0)  
			{   
                resultado++;
				limpar();

				gotoxy(40,10);printf("Cliente disponivel");
			
				
				gotoxy(15,12);printf("Qual modelo de carro: ");
                gotoxy(25,14);printf("1- Executivo");
                gotoxy(25,16);printf("2- Luxo");
                gotoxy(25,18);printf("3- nenhum");
                gotoxy(40,12);scanf("%d",&modelo);

                if(modelo==1)
                {
                    cliente.servico.carro++;
                    cliente.servico.total_servico+=(admin.carro_executivo *controle);
                    cliente.total_tudo+=(admin.carro_executivo*controle);
                    
                }

                else if(modelo==2)
                {
                    cliente.servico.carro++;
                    cliente.servico.total_servico+=(admin.carro_luxo *controle);
                    cliente.total_tudo+=(admin.carro_luxo *controle);
                }
                
                limpar();
                gotoxy(15,21);printf("Adicionar seguro ( S / N ):");
                gotoxy(45,21);escolha=getchar();

               if(escolha=='S' || escolha=='s')
               {
                   cliente.servico.seguro++;
                   cliente.servico.total_servico+=(admin.seguro *controle);
                   cliente.total_tudo+=(admin.seguro *controle);
               } 

		           limpar();
                   gotoxy(15,23);printf("Adicionar tanque cheio ( S / N ):");
                   gotoxy(51,23);escolha=getchar();

                   if(escolha=='S' || escolha =='s')
                   {
                       cliente.servico.tanque++;
                       cliente.servico.total_servico+=(admin.tanque *controle);
                       cliente.total_tudo+=(admin.tanque *controle);
                   } 

				  fseek(reservas,ftell(reservas)-sizeof(cliente),0);	
				  fwrite(&cliente,sizeof(cliente),1,reservas);	
				  fclose(reservas);

                    gotoxy(40,26);printf("SERVICO ENCERRADO");
                    limpar();
                    getch();
                    menu_servicos();


		
				
			}
			if(resultado==0)
			{
			
				printf("Nenhum cliente registrado");
                limpar();
                getch();
                menu_servicos();
			}
		} 
      
} 

void alterar_restaurante()
{   
    limpar();
    limpar_tela();

    int busca;
    int resultado=0;
    int qtd;
   
   gotoxy(30,5);printf("SESSAO RESTAURANTE");
    gotoxy(15,7);printf("Digite o numero da reserva");
    gotoxy(45,7);scanf("%d",&busca);  
    
    reservas=fopen("nomes.dat","rb+");
		while(fread(&cliente,sizeof(cliente),1,reservas)==1)
		{
			if(existe(busca)==0)  //ver se existe
			{   
                limpar();
                resultado++;
				
				gotoxy(40,10);printf("Cliente disponivel");
				gotoxy(15,12);printf("Quantas refeicoes: ");
                gotoxy(36,12);scanf("%d",&qtd);

                cliente.servico.restaurante+= (qtd);
                cliente.total_tudo+=(qtd *controle* admin.restaurante);
                cliente.servico.restaurante_total+=(qtd *controle* admin.restaurante);
                cliente.servico.total_servico+=(qtd *controle * admin.restaurante);

                fseek(reservas,ftell(reservas)-sizeof(cliente),0);
				fwrite(&cliente,sizeof(cliente),1,reservas);	
				fclose(reservas);

                    gotoxy(40,15);printf("SERVICO ENCERRADO");
                    limpar();
                    getch();
                    menu_servicos();


				fseek(reservas,ftell(reservas)-sizeof(cliente),0);
				fwrite(&cliente,sizeof(cliente),1,reservas);	
				fclose(reservas);
			}
			if(resultado==0)
			{
			
				gotoxy(40,10);printf("Nenhum cliente registrado");
                limpar();
                getch();
                menu_servicos();
			}
		} 
      
} 

void alterar_cama()
{
    limpar();
    limpar_tela();

    int busca;
    int resultado=0;
    char escolha;
   

   gotoxy(30,5);printf("SESSAO ADICIONAL");
    gotoxy(15,7);printf("Digite o numero da reserva");
    gotoxy(45,7);scanf("%d",&busca); 

    reservas=fopen("nomes.dat","rb+");

		while(fread(&cliente,sizeof(cliente),1,reservas)==1)
		{
			if(existe(busca)==0)  //ver se existe
			{   
                resultado++;
				
				gotoxy(40,10);printf("Cliente disponivel");
			    
                if(cliente.servico.cama_extra >=1) 
                {
                    gotoxy(41,12);printf("Nao pode adicionar cama extra pois ja possui uma cama em seu contrato");
                    limpar();
                    getch();
                    menu_servicos();
                } 
                else
                {
                 limpar();
				gotoxy(15,12); printf("Adicionar cama ( S / N ): ");
                gotoxy(42,12);escolha=getchar();

                if(escolha == 's' || escolha=='s')
                {
                   cliente.servico.cama_extra+=1;
                   cliente.total_tudo+=(admin.cama_extra *controle);
                   cliente.servico.cama_extra_total+=(admin.cama_extra *controle);
                   cliente.servico.total_servico+=(admin.cama_extra *controle);
                   	fseek(reservas,ftell(reservas)-sizeof(cliente),0);	
				fwrite(&cliente,sizeof(cliente),1,reservas);	
				fclose(reservas);
                }

                else 
                    continue;

                    gotoxy(40,15);printf("SERVICO ENCERRADO");
                    limpar();
                    getch();
                    menu_servicos();


		
				
				
                } 
			}
			if(resultado==0)
			{
			
				gotoxy(40,10);printf("Nenhum cliente registrado");
                limpar();
                getch();
                menu_servicos();
			}
		} 
      

}

void controle_de_preco()
{
   struct tm hj;
    time_t tempo_data;

    time(&tempo_data);
    hj = *localtime(&tempo_data);

    if(mes_atual==1 || mes_atual==2 || mes_atual ==6 || mes_atual==7 || mes_atual==12) 
       controle=admin.controle_preco;

}

void contrato_texto(char arquivo[30])
{   
     char nome[30];
     char endereco[50];

    struct tm hj;
    time_t tempo_data;

    time(&tempo_data);
    hj = *localtime(&tempo_data);
    
    strcpy(endereco,"/Users/Davi/Desktop/trabalho concluido/FECHADOS/");
    strcpy(nome,arquivo);
    strupr(nome);
    strcat(nome,".txt");
    strcat(endereco,nome);
    
    contrato=fopen(endereco,"ab+");

    fprintf(contrato,"\t\t\t\tHOTEL CAMPINA CONFORT PREMIUM\r\n");
    fprintf(contrato,"DADOS DO CLIENTE: \r\n\r\n");
    fprintf(contrato,"NOME DO CLIENTE:%s\r\n",cliente.nome);
    fprintf(contrato,"DATA DE NASCIMENTO:%s\r\n",cliente.data_nascimento);
    fprintf(contrato,"NACIONALIDADE:%s\r\n",cliente.nacionalidade);
    fprintf(contrato,"CPF:%s  RG:%s\r\n",cliente.cpf,cliente.rg);
    fprintf(contrato,"ENDERECO:%s  BAIRRO:%s  CIDADE:%s ESTADO:%s\r\n",cliente.endereco,cliente.bairro,cliente.cidade,cliente.estado);
    fprintf(contrato,"TELEFONE:%s\r\n",cliente.telefone);
    fprintf(contrato,"E-MAIL:%s\r\n\r\n",cliente.email);
    fprintf(contrato,"DADOS DA RESERVA\r\n\r\n");
    fprintf(contrato,"DATA DA ENTRADA:%d-%d-%d\r\n",cliente.data.dia_entrada,cliente.data.mes_entrada,cliente.data.ano_entrada);
    fprintf(contrato,"DATA DA SAIDA:%d-%d-%d\r\n",cliente.data.dia_saida,cliente.data.mes_saida,cliente.data.ano_saida);
    fprintf(contrato,"MODELO DO QUARTO:%s  TOTAL:%.2f\r\n",cliente.caracteristica.quarto,cliente.caracteristica.preco_quarto);
    fprintf(contrato,"ACOMPANHANTES:  1-%s  .%s\r\n",cliente.acompanhante[0].nome,cliente.acompanhante[0].documento);
             fprintf(contrato, "\t\t2-%s  .%s\r\n",cliente.acompanhante[1].nome,cliente.acompanhante[1].documento);
             fprintf(contrato,"\t\t3-%s  .%s\r\n",cliente.acompanhante[2].nome,cliente.acompanhante[2].documento);
    fprintf(contrato,"SERVICOS:\r\n\r\n");
    fprintf(contrato,"AUTOMOVEIS:%d    SEGURO:%d    TANQUES:%d     TOTAL:%.2f\r\n",cliente.servico.carro,cliente.servico.seguro,cliente.servico.tanque,cliente.servico.carro_total);
    fprintf(contrato,"BABYSITTER:          HORAS:%d              TOTAL:%.2f\r\n",cliente.servico.babysitter,cliente.servico.babysitter_total);
    fprintf(contrato,"RESTAURANTE:         REFEICOES:%d          TOTAL:%.2f\r\n",cliente.servico.restaurante,cliente.servico.restaurante_total);
    fprintf(contrato,"CAMA EXTRA:          QUANTIDADE:%d         TOTAL:%.2f\r\n",cliente.servico.cama_extra,cliente.servico.cama_extra_total);
    fprintf(contrato,"\r\nTOTAL DA RESERVA:R$ %.2f REAIS\r\n\r\n",cliente.total_tudo); 
    fprintf(contrato,"\t\t  CAMPINA GRANDE-PB/ FATURA GERADA NO DIA %d-%d-%d\r\n",dia_atual,mes_atual,ano_atual); 
    fprintf(contrato,"\t\t    OBRIGADO PELA PREFERENCIA,VOLTE SEMPRE!!!!!"); 

    fclose(contrato);
}
int main()
{    
    SetConsoleTitleA("HOTEL GARDEN");
    abertura();
    inicializacao_preset();
    controle_de_preco();
    login();

    
   
    
}




