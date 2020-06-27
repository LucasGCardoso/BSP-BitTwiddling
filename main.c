#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "include/SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
void load(char* name, Img* pic);

// Carrega uma imagem para a struct Img
void load(char* name, Img* pic)
{
    int chan;
    pic->img = (RGB*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: %s (%s)\n", SOIL_last_result(), name);
        exit(1);
    }
    printf("Load: %s (%d x %d x %d)\n", name, pic->width, pic->height, chan);
}

int main(int argc, char** argv)

{
    Img base, secreta;
    if(argc < 3) {
        printf("loader [img base] [img secreta]\n");
        exit(1);
    }
    load(argv[1], &base);
    load(argv[2], &secreta);

    int i;
    printf("Primeiros 10 pixels da imagem base:\n");
    for(i=0; i<10; i++)
        printf("[%02X %02X %02X] ", base.img[i].r, base.img[i].g, base.img[i].b);
    printf("\n\n");

    int j;
    printf("Primeiros 10 pixels da imagem secreta:\n");
    for(j=0; j<10; j++)
        printf("[%02X %02X %02X] ", secreta.img[i].r, secreta.img[i].g, secreta.img[i].b);
    printf("\n\n");


    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ENCODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        O codificador deverá:
            Ler a imagem base e a imagem secreta;
            Aplicar a técnica de esteganografia, incorporando a imagem secreta na base;
            Salvar o resultado (imagem codificada) em formato BMP (formato de saída suportado pela biblioteca SOIL).

    É preciso armazenar o tamanho da imagem secreta nos primeiros pixels da imagem resultante - caso contrário será impossível recuperá-la
    Você pode, por exemplo, armazenar as dimensões em 24 bits: 12 para largura e 12 para altura. Dessa forma, os valores máximos podem ir até 4095 (212−1)*/



    // Removendo os dois últimos bits da imagem base (Em teste)
    int k;
    for(k=0; k<base.width * base.height; k++){
        base.img[i].r &= 0b11111100;
        base.img[i].g &= 0b11111100;
        base.img[i].b &= 0b11111100;
    }


//Armazenando os bits da imagem secreta na imagem base (EM TESTE)
    for(i=0; i<base.width*base.height; i++){
        base.img[i].r |= secreta.img[i].r;
        base.img[i].g |= secreta.img[i].g;
        base.img[i].b |= secreta.img[i].b;
    }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // teste para ver se os pixels das imagens foram alterados
    printf("Primeiros 10 pixels da imagem base:\n");
    for(i=0; i<10; i++)
        printf("[%02X %02X %02X] ", base.img[i].r, base.img[i].g, base.img[i].b);
    printf("\n\n");

    printf("Primeiros 10 pixels da imagem secreta:\n");
    for(j=0; j<10; j++)
        printf("[%02X %02X %02X] ", secreta.img[i].r, secreta.img[i].g, secreta.img[i].b);
    printf("\n\n");


    printf("Teste: gravando imagem base em saida.bmp\n");
    SOIL_save_image("saida.bmp", SOIL_SAVE_TYPE_BMP,
     base.width, base.height, 3, (const unsigned char*) base.img);

        /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ DECODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        O decodificador deverá:
            Ler a imagem codificada em formato BMP;
            Recuperar os bytes a partir do conteúdo da imagem carregada (reverter o processo de estaganografia);
            Gravar o resultado em outro arquivo de saída. */








    free(base.img);
    free(secreta.img);
}
