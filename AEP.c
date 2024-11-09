#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int ValidacaoDeSenha(char *senha) {
    int maiusc = 0;
    int num = 0;
    int tamanho = strlen(senha);

    if (tamanho < 8) {
        printf("\nA senha deve conter pelo menos 8 dígitos.\n");
        return 0;
    }

    for (int i = 0; i < tamanho; i++) {
        if (isupper(senha[i])) {
            maiusc = 1;
        }
        if (isdigit(senha[i])) {
            num++;
        }
        if (maiusc && num >= 3) break;
    }

    if (maiusc == 0) {
        printf("\nA senha deve conter pelo menos uma letra MAIÚSCULA.\n");
        return 0;
    }

    if (num < 3) {
        printf("\nA senha deve conter pelo menos 3 números.\n");
        return 0;
    }

    return 1;
}

// Função de cifra de César para criptografar mensagens.
void CifraDeCesar(char *mensagem, int deslocamento) {
    for (int i = 0; mensagem[i] != '\0'; i++) {
        char ch = mensagem[i];

        if (isalpha(ch)) {
            char limite = isupper(ch) ? 'A' : 'a';
            mensagem[i] = (ch - limite + deslocamento) % 26 + limite;
        }
    }
}

int main() {
    char Cadastrousuario[100], Cadastrosenha[100], usuario[100], senha[100];
    char nivelAcesso[10], mensagem[200];

    setlocale(LC_ALL, "Portuguese");

    // Escopo principal do cadastro
    printf("Para se cadastrar, deve-se digitar o nome de usuário, senha e nível de acesso.\n");
    printf("-------------------------------------------------------------\n");

    printf("\nDigite o seu nome de usuário: ");
    if (fgets(Cadastrousuario, sizeof(Cadastrousuario), stdin) != NULL) {
        Cadastrousuario[strcspn(Cadastrousuario, "\n")] = '\0';
    }

    printf("\nDigite sua senha (Deve conter pelo menos 8 dígitos, 3 números e pelo menos uma letra MAIÚSCULA): ");
    if (fgets(Cadastrosenha, sizeof(Cadastrosenha), stdin) != NULL) {
        Cadastrosenha[strcspn(Cadastrosenha, "\n")] = '\0';
    }

    if (!ValidacaoDeSenha(Cadastrosenha)) {
        printf("Senha inválida! Tente novamente.\n");
        return 1;
    }

    printf("\nEscolha o nível de acesso (funcionario, gerente, CEO): ");
    if (fgets(nivelAcesso, sizeof(nivelAcesso), stdin) != NULL) {
        nivelAcesso[strcspn(nivelAcesso, "\n")] = '\0';
        for (int i = 0; nivelAcesso[i]; i++) {
            nivelAcesso[i] = tolower(nivelAcesso[i]);
        }
    }

    printf("\n-----------------------------------------------------------\n");
    printf("Cadastro efetuado com sucesso!\n");

    // Escopo do login
    printf("\nFaça o login.\n");
    printf("Digite o seu nome de usuário: ");
    if (fgets(usuario, sizeof(usuario), stdin) != NULL) {
        usuario[strcspn(usuario, "\n")] = '\0';
    }

    printf("Digite a sua senha: ");
    if (fgets(senha, sizeof(senha), stdin) != NULL) {
        senha[strcspn(senha, "\n")] = '\0';
    }

    // Validação se o login corresponde ao cadastro
    if (strcmp(usuario, Cadastrousuario) == 0 && strcmp(senha, Cadastrosenha) == 0) {
        printf("LOGIN bem-sucedido.\n");

        printf("Digite uma mensagem para registrar no arquivo de acesso: ");
        if (fgets(mensagem, sizeof(mensagem), stdin) != NULL) {
            mensagem[strcspn(mensagem, "\n")] = '\0';
        }

        FILE *arquivo = NULL;
        if (strcmp(nivelAcesso, "funcionario") == 0) {
            printf("Acesso ao arquivo: funcionario.txt\n");
            arquivo = fopen("funcionario.txt", "a");
            if (arquivo != NULL) {
                // Criptografa a mensagem antes de escrever
                CifraDeCesar(mensagem, 3);
                fprintf(arquivo, "Usuário %s acessou como FUNCIONÁRIO.\nMensagem criptografada: %s\n", usuario, mensagem);
            }
        } else if (strcmp(nivelAcesso, "gerente") == 0) {
            printf("Acesso ao arquivo: gerente.txt\n");
            arquivo = fopen("gerente.txt", "a");
            if (arquivo != NULL) {
                fprintf(arquivo, "Usuário %s acessou como GERENTE.\nMensagem: %s\n", usuario, mensagem);
            }
        } else if (strcmp(nivelAcesso, "ceo") == 0) {
            printf("Acesso ao arquivo: CEO.txt\n");
            arquivo = fopen("CEO.txt", "a");
            if (arquivo != NULL) {
                fprintf(arquivo, "Usuário %s acessou como CEO.\nMensagem: %s\n", usuario, mensagem);
            }
        } else {
            printf("Nível de acesso inválido.\n");
        }

        if (arquivo != NULL) {
            fclose(arquivo);
            printf("Mensagem registrada com sucesso no arquivo.\n");
        } else {
            printf("Erro ao abrir o arquivo correspondente.\n");
        }
    } else {
        printf("Falha ao logar. Verifique se o usuário ou a senha foram digitados corretamente.\n");
    }

    return 0;
}
