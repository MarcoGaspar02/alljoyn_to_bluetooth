#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

// Função para enviar mensagem para o dispositivo Arduino
void sendMessage(int fd, char *message) {
    write(fd, message, strlen(message));
    usleep(100000); // Pequeno atraso para garantir que a mensagem seja enviada completamente
}

// Função para ler e exibir resposta do dispositivo Arduino
void readResponse(int fd) {
    char response[255];
    int bytes_read = read(fd, response, sizeof(response));
    if (bytes_read > 0) {
        response[bytes_read] = '\0'; // Adiciona terminador de string
        printf("Resposta do dispositivo Arduino: %s\n", response);
    }
}

int main() {
    printf("\n Waiting for connections \n");
    sleep(10);
    int fd;
    char *port = "/dev/rfcomm1"; // Porta do dispositivo Bluetooth
    struct termios options;

    // Abrir a porta serial
    fd = open(port, O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("Erro ao abrir a porta serial");
        return 1;
    }

    // Configurações da porta serial
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600); // Velocidade de transmissão (baud rate)
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD); // Habilita leitura e escrita
    options.c_cflag &= ~PARENB; // Sem paridade
    options.c_cflag &= ~CSTOPB; // 1 stop bit
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8; // 8 bits de dados
    tcsetattr(fd, TCSANOW, &options);

    // Menu
    char choice;
    do {
        printf("Menu:\n");
        printf("y - Enviar mensagem 'yes'\n");
        printf("n - Enviar mensagem 'no'\n");
        printf("s - Enviar mensagem 'status'\n");
        printf("e - Sair\n");
        printf("Escolha uma opção: ");

        scanf(" %c", &choice);
        // Enviar mensagem com base na escolha do usuário
        switch (choice) {
            case 'y':
                sendMessage(fd, "yes\n");
                break;
            case 'n':
                sendMessage(fd, "no\n");
                break;
            case 's':
                sendMessage(fd, "status\n");
                break;
            case 'e':
                printf("Closing the application\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
        // Ler e exibir resposta do dispositivo Arduino
        if (choice!='e') {
            sleep(4);
            readResponse(fd);
        }
    } while (choice != 'e');

    // Fechar a porta serial
    close(fd);

    return 0;
}
