//FELIPE BORGES BARROS 12211bsi250
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct funcionario{
        char cpf[12];
        char nome[30];
        time_t entrada;
        time_t saida;
        char status;

};
struct logf{
        char cpf[12];
        time_t horario;
        char evento;
};

void registro (FILE *funcionarios, FILE *log){
    struct funcionario temp;
    printf("digite o cpf do funcionario: \n");
    scanf("%s", temp.cpf);
    rewind(funcionarios);
    struct logf loga;
    struct funcionario a;

    while(1){
        fread (&a,sizeof(struct funcionario),1,funcionarios);
        if(feof(funcionarios)){
            break;
        }

        if (strcmp(temp.cpf,a.cpf) == 0){
            printf("o funcinario esta entrando ou saindo (E = entrando ou S = saindo)\n");
            fflush(stdin);
            scanf("%c",loga.evento);
            if (loga.evento == 'E'){
                a.entrada = time(NULL);
                a.status = 'P';
            }
            else{
                a.saida = time(NULL);
                a.status = 'A';
            }
            strcpy(temp.cpf,a.cpf);
            loga.horario = time(NULL);
            fseek(funcionarios, -1 * (int)sizeof(struct funcionario),SEEK_CUR);
            fwrite(&a, sizeof(struct funcionario),1,funcionarios);
            fwrite(&loga,sizeof(struct logf),1,log);
            return;
        }
    }
    loga.evento = 'E';
    loga.horario = time(NULL);
    strcpy(loga.cpf,temp.cpf);
    fwrite(&loga,sizeof(struct logf),1,log);
    temp.entrada = time(NULL);
    temp.status = 'P';
    printf("digite o nome do funcionario\n");
    scanf("%s",temp.nome);
    fwrite(&temp,sizeof(struct funcionario),1,funcionarios);
    return;
}

void listagem_funcionarios(FILE *funcionarios) {
    rewind(funcionarios);
    struct funcionario a;
    while(1){
        fread(&a,sizeof(struct funcionario),1,funcionarios);
        if(feof (funcionarios)){
            break;
        }
        printf("nome: %s\ncpf: %s\n",a.nome,a.cpf);
        printf("%c\n",a.status);
        if (a.status == 'P'){
            printf("%s", ctime(&a.entrada));
        }
        else{
            printf("%s", ctime(&a.saida));
        }
    }
}

void listagem_log(FILE *log) {
    rewind(log);
    struct logf loga;
    while(1){
        fread(&loga,sizeof(struct logf),1,log);
        if(feof(log)){
            break;
        }
        printf("CPF:%s\n",loga.cpf);
        printf("Evento:%c\n",loga.evento);
        printf("Horario:%s\n", ctime(&loga.horario));
        }

    }

int main() {
    // abrir arquivos (completar). Sugestão: tentar abrir com "rb+", e se não abrir, tentar abrir com "wb+",
	// e se não abrir, informar o usuário que não foi possível
    FILE *funcionarios;
    FILE *log;
    funcionarios = fopen("funcionarios.bin","rb+");
    log = fopen("log.bin","rb+");
    if(!funcionarios || !log)
    {
    funcionarios = fopen("funcionarios.bin","wb+");
    log = fopen("log.bin","wb+");
    if(!funcionarios || !log)
    {
        printf("Error\n");
        return 1;
    }
    }


    // a partir daqui nesta função main() o código não deve ser alterado
    int opcao;
    do {
        printf("\n\n 0-sair\n 1-registro entrada/saida\n 2-lista funcionarios\n 3-lista log\n");
        printf("\n Opcao: "); scanf(" %d",&opcao);
        switch(opcao) {
            case 1: registro(funcionarios,log); break;
            case 2: listagem_funcionarios(funcionarios); break;
            case 3: listagem_log(log); break;
            printf("\n\n\n");
        }
    } while (opcao != 0);

    fclose(funcionarios);
    fclose(log);
    return 0;
}
