#include <iostream>
#include <cstdlib>
#include <string.h>
#include <sqlite3.h>
#include <stdio.h>

//A SENHA INICIAL É 123

using namespace std;

int idTurma=0;
//Variáveis Globais do Banco de Dados SQL
sqlite3 *db;
char *zErrMsg = 0;
int rc;
char *sql;

// Funções Pricipais do Banco de Dados SQL (Início)
void connect(const char *db_file)
{
    rc = sqlite3_open(db_file, &db);

    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i=0; i<argc; i++)
    {
        cout<<"\t"<<azColName[i]<<" \t";
    }
    cout<<endl;

    for(i=0; i<argc; i++)
    {
        cout<<"\t"<<argv[i]<<" ";
    }
    cout<<endl;

    return 0;
}

void exec(char *sql)
{
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Instruction executed successfully\n");
    }
}
void criarTabelaBanco()
{
    sql = (char *)"CREATE TABLE IF NOT EXISTS TURMAS("\
          "ID INTEGER PRIMARY KEY     AUTOINCREMENT,"\
          "DISCIPLINA           TEXT    NOT NULL,"\
          "NUMERO               INT     NOT NULL,"\
          "QUANTALUNOS            INT     NOT NULL);";

    exec(sql);

    sql = (char *)"CREATE TABLE IF NOT EXISTS ALUNOS("  \
          "ID INTEGER PRIMARY KEY     AUTOINCREMENT," \
          "IDTURMA        INT     NOT NULL,"\
          "NOME           TEXT    NOT NULL," \
          "IDADE          INT     NOT NULL," \
          "MATRICULA      INT     NOT NULL," \
          "EMAIL          CHAR(100)," \
          "NOTA1          REAL     NOT NULL,"\
          "NOTA2          REAL     NOT NULL,"\
          "NOTA3          REAL     NOT NULL,"\
          "MEDIA          REAL     NOT NULL);";
    exec(sql);

}

// Funções Pricipais do Banco de Dados SQL (Fim)

// Função que compara que verifica se duas strings são iguais
bool stringIgual(char s1[], char s2[])
{

    for (int i=0; s1[i]!='\0' || s2[i]!='\0'; i++)
    {
        if (s1[i]!=s2[i])
            return false;
    }

    return true;
}

// Função com senha para acessar o programa
void senhaAcesso()
{

    char senha[11];

    system("cls");

    cin.ignore();
    cout<<"Senha de acesso:";
    cin.getline(senha,11);

    while(!stringIgual(senha,"123"))
    {
        system("cls");

        cout<< "Senha inválida. Tente novamente:";
        cin.getline(senha,11);
    }
f    system("cls");

}

void inserirAluno()
{
    system("cls");
    char *sql;

    sql = (char *) "SELECT disciplina, id from TURMAS";
    exec(sql);
    cout<<"Em qual turma deseja adcionar? ";

    int IDTURMA;
    char NOME[30];
    int IDADE,MATRICULA;
    char EMAIL[30];
    float NOTA1=0,NOTA2=0,NOTA3=0;
    float MEDIA=0.0;
    char FRASE[200];

    cin>>IDTURMA;
    cout<<"Nome do Aluno(a)? ";
    cin.ignore();
    cin.getline(NOME,30);
    cout<<"Idade? ";
    cin>>IDADE;
    cout<<"Matricula? ";
    cin>>MATRICULA;
    cout<<"Email do Aluno(a)? ";
    cin.ignore();
    cin.getline(EMAIL,30);

    sprintf(FRASE,"INSERT INTO ALUNOS(IDTURMA,NOME,IDADE,MATRICULA,EMAIL,NOTA1,NOTA2,NOTA3,MEDIA)\nVALUES (%d,'%s',%d,%d,'%s',%f,%f,%f,%f);",IDTURMA,NOME,IDADE,MATRICULA,EMAIL,NOTA1,NOTA2,NOTA3,MEDIA);
    sql = (char *)FRASE;
    exec(sql);

}

void deletarTurma(int ID)
{
    char frase[150];
    sprintf(frase,"DELETE from TURMAS where ID=%d;",ID);
    sql=(char *)frase;
    exec(sql);

    sprintf(frase,"DELETE from ALUNOS where IDTURMA=%d;",ID);
    sql=(char *)frase;
    exec(sql);
}
void deletarAluno()
{
    int id;
    system("cls");
    char *sql;

    sql = (char *) "SELECT disciplina, id from TURMAS";
    exec(sql);

    cout<<"Em qual turma deseja remover o aluno? ";
    cin>>id;
    char frase[50];
    sprintf(frase,"DELETE from ALUNOS where IDTURMA=%d;",id);

    sql=(char *)frase;
    exec(sql);
}

void AtualizarAluno(int nota, int valornota, int Id)
{
    char frase[30];
    sprintf(frase,"UPDATE ALUNOS set NOTA%d=%d  where ID=%d; \n SELECT * from ALUNOS",nota,valornota,Id);
    sql=(char*)frase;
    exec(sql);
}
void AtualizarTurma(int Id, int QuantidadeAluno)
{
    char frase[31];
    sprintf(frase,"UPDATE TURMAS set QUANTALUNOS=%d where ID=%d; \n SELECT * from TURMAS", QuantidadeAluno,Id);
    sql=(char*)frase;
    exec(sql);
}

void inserirTurma(char DISCIPLINA[], int QUANTALUNOS,int Numero)
{
    char frase[200];
    sprintf(frase,"INSERT INTO TURMAS(DISCIPLINA,NUMERO,QUANTALUNOS)\nVALUES('%s',%d,%d);",DISCIPLINA,Numero,QUANTALUNOS);

    sql = (char *)frase;
    exec(sql);
}
//Menu
void telaTurmas()
{
    char *sql;

    system("cls");

    sql = (char *) "SELECT disciplina, id, quantalunos from TURMAS";
    exec(sql);
}
void buscaAluno()
{
    char *sql;

    system("cls");

    sql = (char *) "SELECT disciplina, id, quantalunos from TURMAS";
    exec(sql);
}

//Menu
int telaGerenciamento()
{

    int opcaoGerenciamento;

    system("cls");


    cout<<"AS OPCOES DESSE MENU AINDA ESTAO EM DESENVOLVIMENTO (Digite 6 para voltar) "<<endl<<endl
        <<"1-Adicionar turmas                                                         "<<endl
        <<"2-Remover turmas                                                           "<<endl
        <<"3-Adicionar alunos a uma turma                                             "<<endl
        <<"4-Remover alunos de uma turma                                              "<<endl
        <<"5-Gerenciar notas                                                          "<<endl
        <<"6-Voltar                                                                   "<<endl;

    cin>>opcaoGerenciamento;
    return opcaoGerenciamento;


}

//Menu
int menuPrincipal()
{
    system("cls");
    char opcaoPrincipal;

    cout<<"1- Acessar turmas                          "<<endl
        <<"2- Gerenciar turmas                        "<<endl
        <<"3- Pesquisar aluno(Funcao nao implementada)"<<endl
        <<"4 - Sair                                    "<<endl;

    cin>> opcaoPrincipal;


    return opcaoPrincipal;
}

//Menu
void ControledeFluxo()
{

    int opcaoEntrada;

backEntrada:
    system("cls");

    cout<<"           SEGT         "<<endl
        <<"                        "<<endl
        <<"    1- Entrar no Sistema"<<endl
        <<"    2- Sair             "<<endl
        <<" Escolha uma das opções:"<<endl;

    cin>>opcaoEntrada;

    switch(opcaoEntrada)
    {

    case 1:

menuPrincipal:

///////////////CODIGO DO MENU PRINCIPAL///////////////
        switch(menuPrincipal())
        {

        case '1':
            telaTurmas();
            system("pause");
            goto menuPrincipal;
            break;

        case '2':
///////////CODIGO DO GERENCIAR TURMAS /////////////
            switch(telaGerenciamento())
            {
            case 1:
                char turma[20];
                int quantidade;
                cin.ignore();
                cin.getline(turma,20);
                cin>>quantidade;
                inserirTurma(turma,quantidade,idTurma);
                system("pause");
                break;

            case 2:
                telaTurmas();
                cout<<"Qual quer apagar"<<endl;
                int turmadel;
                cin>>turmadel;
                deletarTurma(turmadel);
                break;
            case 3:
                inserirAluno();

                break;

            case 4:
                deletarAluno();
                break;
            case 5:
                // AtualizarAluno();
                break;
            case 6:
                goto menuPrincipal;
                break;
            default:
                // goto refresh;
                break;
            }

/////////// CODIGO DO GERENCIAR TURMAS /////////////
            break;
        case '3':

            break;
        case '4':
            break;
        default:
            goto menuPrincipal;
///////////////CODIGO DO MENU PRINCIPAL///////////////

        }
           break;
    case 2:
        break;
    default:
        goto backEntrada;
        break;
    }

}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    connect("test.db");

    criarTabelaBanco();



    ControledeFluxo();

    return 0;
}
