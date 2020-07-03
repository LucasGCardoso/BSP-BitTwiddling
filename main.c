#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings
#include <stdbool.h>    // Para usar boolean

// SOIL é a biblioteca para leitura das imagens
#include "include/SOIL.h"

// Um pixel RGB
typedef struct
{
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct
{
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
    // Criação das imagens Base e Secreta na estrutura (struct) Img, que é composta pela struct RGB
    Img base, secreta;

    // Comparação para entrada de argumentos da execução do programa.

    // Se o tamanho do argumento for menor que 2, signfiica que é para fazer o Decode.
    if(argc < 2)
    {
        printf("loader [img base] [img secreta]\n");
        exit(1);
    }

    // Se o tamanho do argumento for igual a 2, signfiica que é para fazer o Encode
    if (argc == 2)
    {
        printf("### Starting to decode Image ### \n");

    // Criação da imagem saida
        Img saida;

    // Carrega a imagem e inicia altura e largura
        load(argv[1], &base);
        int width;
        int height;

    // Atribui os dois últimos bits da imagem base à Width e depois "empurra" para o início do byte
        width |= ((base.img[0].r) & 0b00000011);
        width = width << 2;

        width |= ((base.img[0].g) & 0b00000011);
        width = width << 2;

        width |= ((base.img[0].b) & 0b00000011);
        width = width << 2;

        width |= ((base.img[1].r) & 0b00000011);
        width = width << 2;

        width |= ((base.img[1].g) & 0b00000011);
        width = width << 2;

        width |= ((base.img[1].b) & 0b00000011);

        printf("Width of the secret image is: %d\n", width);

    // Atribui os dois últimos bits da imagem base à Height e depois "empurra" para o início do byte

        height |= ((base.img[2].r) & 0b00000011);
        height = height << 2;

        height |= ((base.img[2].g) & 0b00000011);
        height = height << 2;

        height |= ((base.img[2].b) & 0b00000011);
        height = height << 2;

        height |= ((base.img[3].r) & 0b00000011);
        height = height << 2;

        height |= ((base.img[3].g) & 0b00000011);
        height = height << 2;

        height |= ((base.img[3].b) & 0b00000011);

        printf("Height of the secret image is: %d\n", height);

    // Depois de preenchido, atribui os valores da variável temporaria para a largura e altura da imagem Saida

        saida.width = width;
        saida.height = height;

    // Atribui a imagem saída com o RGB*

        RGB* arr[width * height];
        saida.img = arr;


    // 'For' para pegar os dois últimos bits da imagem base, no RGB, atribuindo para os respectivos RGB da imagem Saida (Atribuindo 8 bits (r, g, b, r) para a imagem de saída (r)
        int y = 4;
        int i = 0;
        for (; i < (saida.width * saida.height); y ++, i ++)
        {
            //adding red color
            saida.img[i].r |= ((base.img[y].r) & 0b00000011);
            saida.img[i].r = saida.img[i].r << 2;

            saida.img[i].r |= ((base.img[y].g) & 0b00000011);
            saida.img[i].r = saida.img[i].r << 2;

            saida.img[i].r |= ((base.img[y].b) & 0b00000011);
            saida.img[i].r = saida.img[i].r << 2;

            y ++;

            saida.img[i].r |= ((base.img[y].r) & 0b00000011);

            //adding green color
            saida.img[i].g |= ((base.img[y].g) & 0b00000011);
            saida.img[i].g = saida.img[i].g << 2;

            saida.img[i].g |= ((base.img[y].b) & 0b00000011);
            saida.img[i].g = saida.img[i].g << 2;

            y ++;

            saida.img[i].g |= ((base.img[y].r) & 0b00000011);
            saida.img[i].g = saida.img[i].g << 2;

            saida.img[i].g |= ((base.img[y].g) & 0b00000011);

            //adding blue color
            saida.img[i].b |= ((base.img[y].b) & 0b00000011);
            saida.img[i].b = saida.img[i].b << 2;

            y ++;

            saida.img[i].b |= ((base.img[y].r) & 0b00000011);
            saida.img[i].b = saida.img[i].b << 2;

            saida.img[i].b |= ((base.img[y].g) & 0b00000011);
            saida.img[i].b = saida.img[i].b << 2;

            saida.img[i].b |= ((base.img[y].b) & 0b00000011);
        }

    // Cria o arquivo para a imagem através do SOIL
        printf("Saving the secret image in result.bmp\n");
        SOIL_save_image("result.bmp", SOIL_SAVE_TYPE_BMP,
        saida.width, saida.height, 3, (const unsigned char*) saida.img);

        printf("All done here :)");

        free(saida.img);
        free(base.img);
        //We use exit here, so we do not execute the recording part again
        exit(1);
    }

    load(argv[1], &base);
    load(argv[2], &secreta);

    // Pega a área da imagem Base e Secreta
    int areaBase = base.height * base.width;
    int areaSecreta = secreta.height * secreta.width;

    if(areaBase/4 < areaSecreta + 24)
    {
        printf("Invalid image. The secret image must be 1/4 - 24 pixels shorter then the base image");
        exit(1);
    }

    // Limpa (deleta) os dois últimos bits da imagem base através de máscara
    int i;
    for(i = 0; i < areaBase; i++)
    {
        base.img[i].r &= 0b11111100;
        base.img[i].g &= 0b11111100;
        base.img[i].b &= 0b11111100;
    }

    printf("\n\n");

    // Insere as dimensões da imagem Secreta nos 4 primeiros pixels (nos dois ultimos bits) da imagem base
    printf("Base Image Width: %d \n", base.width);
    printf("Base Image Height: %d \n", base.height);
    printf("Base Image Area: %d \n", base.width * base.height);
    int y = 0;
    i = 0;
    int k = 0;

    base.img[i].r |= secreta.width >> 10;
    base.img[i].g |= (secreta.width >> 8) & 0b000000000011;
    base.img[i].b |= (secreta.width >> 6) & 0b000000000011;
    base.img[i + 1].r |= (secreta.width >> 4) & 0b000000000011;
    base.img[i + 1].g |= (secreta.width >> 2) & 0b000000000011;
    base.img[i + 1].b |= (secreta.width) & 0b000000000011;

    base.img[i + 2].r |= secreta.height >> 10;
    base.img[i + 2].g |= (secreta.height >> 8) & 0b000000000011;
    base.img[i + 2].b |= (secreta.height >> 6) & 0b000000000011;
    base.img[i + 3].r |= (secreta.height >> 4) & 0b000000000011;
    base.img[i + 3].g |= (secreta.height >> 2) & 0b000000000011;
    base.img[i + 3].b |= (secreta.height) & 0b000000000011;


    i = 4;
    // Insere as cores da imagem secreta nos dois últimos bits da imagem base
    for (; y < (secreta.width * secreta.height); i += 4)
    {
        base.img[i].r |= secreta.img[y].r >> 6;
        base.img[i].g |= ((secreta.img[y].r >> 4) & 0b00000011);
        base.img[i].b |= ((secreta.img[y].r >> 2) & 0b00000011);
        base.img[i + 1].r |= ((secreta.img[y].r) & 0b00000011);

        base.img[i + 1].g |= secreta.img[y].g >> 6;
        base.img[i + 1].b |= ((secreta.img[y].g >> 4) & 0b00000011);
        base.img[i + 2].r |= ((secreta.img[y].g >> 2) & 0b00000011);
        base.img[i + 2].g |= ((secreta.img[y].g) & 0b00000011);

        base.img[i + 2].b |= secreta.img[y].b >> 6;
        base.img[i + 3].r |= ((secreta.img[y].b >> 4) & 0b00000011);
        base.img[i + 3].g |= ((secreta.img[y].b >> 2) & 0b00000011);
        base.img[i + 3].b |= ((secreta.img[y].b) & 0b00000011);
        y++;
    }

    printf("\n\n");

    printf("Saving the secret image inside base image in file: saida.bmp\n");
    SOIL_save_image("saida.bmp", SOIL_SAVE_TYPE_BMP,
                    base.width, base.height, 3, (const unsigned char*) base.img);

    free(base.img);
    free(secreta.img);
    printf("All done here :)");
}
