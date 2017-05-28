#include <iostream>
#include <cstdlib>
#include <string.h>
#include <sqlite3.h>
#include <stdio.h>

//A SENHA INICIAL É 123

using namespace std;

sqlite3 *db;
char *zErrMsg = 0;
int rc;
char *sql;

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
        cout<<azColName[i]<< argv[i]<<endl;
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
void inserirAluno(int idAluno)
{
    idAluno++;
    char idt[3];
    sprintf(idt,"%d",idAluno);
    char IDTURMA[2]="1",NOME[30]="lucas",IDADE[3]="20",MATRICULA[11]="2016014950";
    char EMAIL[30]="Lucas",NOTA1[5]="10",NOTA2[5]="10",NOTA3[5]="10",MEDIA[5]="10";
    char prt1[200]="INSERT INTO ALUNOS(ID,IDTURMA,NOME,IDADE,MATRICULA,EMAIL,NOTA1,NOTA2,NOTA3,MEDIA)\nVALUES (";
    strcat(prt1,idt);
    strcat(prt1,",");
    strcat(prt1,IDTURMA);
    strcat(prt1,",'");
    strcat(prt1,NOME);
    strcat(prt1,"',");
    strcat(prt1,IDADE);
    strcat(prt1,",");
    strcat(prt1,MATRICULA);
    strcat(prt1,",'");
    strcat(prt1,EMAIL);
    strcat(prt1,"',");
    strcat(prt1,NOTA1);
    strcat(prt1,",");
    strcat(prt1,NOTA2);
    strcat(prt1,",");
    strcat(prt1,NOTA3);
    strcat(prt1,",");
    strcat(prt1,MEDIA);
    sql = (char *)strcat(prt1,");");
    exec(sql);
}

void inserirTurma(char DISCIPLINA[], char QUANTALUNOS[],int idTurma)
{
    idTurma++;
    char idt[3];

    char prt1[200]="INSERT INTO TURMAS(ID,DISCIPLINA,QUANTALUNOS)\nVALUES(";
    sprintf(idt,"%d",idTurma);
    strcat(prt1,idt);
    strcat(prt1,",'");
    strcat(prt1,DISCIPLINA);
    strcat(prt1,"',");
    strcat(prt1,QUANTALUNOS);
    sql = (char *)strcat(prt1,");");
    exec(sql);
}
struct Estudante
{

    char nome[50];
    int matricula;
    int nota1, nota2, nota3;

};

struct Turmas
{
    Estudante alunos[100];
    int quantidadeAlunos;
};

bool stringIgual(char s1[], char s2[])
{

    for (int i=0; s1[i]!='\0' || s2[i]!='\0'; i++)
    {
        if (s1[i]!=s2[i])
            return false;
    }

    return true;
}

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

    system("cls");

}

int telaDeEntrada()
{

    int opcaoEntrada;

    cout<<"           SEGT         "<<endl
        <<"                        "<<endl
        <<"    1- Entrar no Sistema"<<endl
        <<"    2- Sair             "<<endl;

    cin>>opcaoEntrada;

    return opcaoEntrada;
}

int menuPrincipal()
{

    int opcao;

    cout<<"1- Acessar turmas                          "<<endl
        <<"2- Gerenciar turmas                        "<<endl
        <<"3- Pesquisar aluno(Funcao nao implementada)"<<endl
        <<"4- Sair                                    "<<endl;

    cin>> opcao;

    return opcao;
}

int telaTurmas(int quantidadeTurmas)
{

    int numTurma, i;

    system("cls");

    cout<<"0-Voltar"<<endl;

    for(i=0; i<quantidadeTurmas; i++)
    {

        cout<<i+1<<"-Turma "<< i+1<< endl;
    }

    cin>>numTurma;

    return numTurma-1;
}

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

void listaAlunos(Turmas Classe[],int numeroTurma)
{

    system("cls");

    cout<<"              Nome                  \tMatricula"<<endl;

    for(int i=0; i<Classe[numeroTurma].quantidadeAlunos; i++)
    {

        cout<<"\t"<<Classe[numeroTurma].alunos[i].nome<<"           \t"<<Classe[numeroTurma].alunos[i].matricula << endl;

    }

}

int main()
{

    int opcaoEntrada, opcaoPrincipal;
    int quantidadeTurmas, numeroTurma;
    int opcaoGerenciamento;
    int idTurma=0,idAlunos=0;

    connect("test.db");



    sql = (char *)"CREATE TABLE IF NOT EXISTS TURMAS("\
          "ID INT PRIMARY KEY     NOT NULL,"\
          "DISCIPLINA           TEXT    NOT NULL,"\
          "QUANTALUNOS            INT     NOT NULL);";

    exec(sql);

    sql = (char *)"CREATE TABLE IF NOT EXISTS ALUNOS("  \
          "ID INT PRIMARY KEY     NOT NULL," \
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


    inserirAluno(idAlunos);

    inserirTurma("Logica", "100",idTurma);

    exec(sql);

    quantidadeTurmas=1;

    Turmas Classe[quantidadeTurmas];

    Classe[0].quantidadeAlunos=3;

    strcpy(Classe[0].alunos[0].nome, "Italo Barbosa Alcantara");
    Classe[0].alunos[0].matricula=0001;
    Classe[0].alunos[0].nota1=7;
    Classe[0].alunos[0].nota2=7;
    Classe[0].alunos[0].nota3=7;

    strcpy(Classe[0].alunos[1].nome, "Lucas Marinho Freitas");
    Classe[0].alunos[1].matricula=0002;
    Classe[0].alunos[1].nota1=7;
    Classe[0].alunos[1].nota2=7;
    Classe[0].alunos[1].nota3=7;

    strcpy(Classe[0].alunos[2].nome, "Gabriel Oliveira de Azevedo");
    Classe[0].alunos[2].matricula=0003;
    Classe[0].alunos[2].nota1=7;
    Classe[0].alunos[2].nota2=7;
    Classe[0].alunos[2].nota3=7;

backEntrada:

    opcaoEntrada=telaDeEntrada();

    switch(opcaoEntrada)
    {

    case 1:

        system("cls");

        senhaAcesso();

backPrincipal:

        opcaoPrincipal=menuPrincipal();

        switch(opcaoPrincipal)
        {

        case 1:

            numeroTurma=telaTurmas(quantidadeTurmas);

            listaAlunos(Classe,numeroTurma);

            break;

        case 2:

backGerenciamento:

            opcaoGerenciamento=telaGerenciamento();

            if(opcaoGerenciamento==6)
            {

                system("cls");

                goto backPrincipal;
            }
            else
                goto backGerenciamento;
            break;

        case 3:

            system("cls");

            goto backPrincipal;

            break;

        case 4:

            system("cls");

            goto backEntrada;

            break;
        }

        break;

    case 2:
        break;
    }

    return 0;
}
