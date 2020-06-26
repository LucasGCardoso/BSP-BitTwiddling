# BSP - Bit Twiddling
This repo is a work from college, which consists in applying techniques capable of hiding information in other files such as images, music or videos.
</br>
</br>
This repository is public in order to show the solution to the problem, __but it must not be reworked, copied, used, downloaded, disclosed or any other purpose.__ This repository is for the __private and exclusive__ use of students in the discipline of Basic Software Program of class 127 - 2020/1 of the Software Engineering course at the Polytechnic School of PUCRS college. 
</br>
</br>

# Table of Contents
- [About the repository](#bsp---bit-twiddling)
- [Proposed problem :pencil:](#proposed-problem)
- [How does it work? :question:](#how-does-it-work)
  * [Encoder](#encoder)
  * [Decoder](#decoder)
  * [Implementing Steganography](#implementing-steganography)

# Proposed problem
The aim of this work is to practice memory manipulation at a low level, implementing a simple technique of steganography in images.

Currently encryption is widely used when you want to send a confidential message. This is done in virtually all applications that involve data exchange, such as browsers, email, instant messaging, etc. However, there is another way to hide information, called steganography. It consists of applying techniques capable of hiding information within other files such as images, music or videos. The aim of this work is to practice memory manipulation at a low level, implementing a simple technique of steganography in images.

# How does it work?
A program with two features should be created:

- Encode: reads two images, the base image and the secret image (to be hidden in the first). The program encodes the secret image into the first one, and writes a new file with the result.

- Decode: reads the image resulting from the previous step and extracts the secret image, recording a new file.

To read the images we will use a simple library (integrated in the example project) called SOIL.

An image is usually represented by an array of dots (pixels) where each color is defined by 3 components: red (R), green (G) and blue (B). Each of these components is usually encoded in one byte, which produces 3 bytes per pixel (24 bits) - that is, 16 million possible colors. In other words, the intensities (R, G, B) vary from 0 to 255, where 0 is dark and 255 is light.
See below how different colors are represented in this format - each color is expressed by the RGB components in hexadecimal.

<img align="center" src="https://i.imgur.com/j56OBAk.png">


The code provided defines two structs: one to represent a pixel and another to represent the entire image. After reading the images, the pixels will be available in the base and secret variables.

```
// Um pixel RGB (24 bits)
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem RGB
typedef struct {
    int width, height;
    RGB* img;            // vetor de pixels
} Img;

// As imagens
Img base, secreta;

// Cada pixel está armazenado em base.img[i] ou secreta.img[i], onde i é o índice do pixel.
// Exemplo: acessando os dois primeiros pixels da base
RGB aux1 = base.img[0];
RGB aux2 = base.img[1];
```

## Encoder
The encoder should:
- Read the base image and the secret image;
- Apply the steganography technique, incorporating the secret image on the base;
- Save the result (encoded image) in BMP format (output format supported by the SOIL library).

## Decoder
The decoder should:
- Read the image encoded in BMP format;
- Recover the bytes from the content of the uploaded image (reverse the staganography process);
- Save the result to another output file.

## Implementing Steganography
There are several techniques for carrying out the steganography process in images, with different degrees of complexity. A simple technique is to change the least significant bits of each pixel. This technique consists of replacing one or more less significant bits of each color component of a pixel with a part of the message. Since we have 8 bits for R, G and B, this generally changes the color of each pixel very little.

For example, if we change the last two bits of a 100% red pixel (11111111) to 11111101, this implies changing the value of the red component from 255 to 253, which is practically imperceptible to the naked eye. The image below presents the idea, considering that the data to be encoded is a single pixel:

<img align="center" src="https://i.imgur.com/iFtIIZO.jpg">

In this example, the original pixel (gray rectangle) is encoded within 4 pixels of the base image: as we can only use 2 bits of each component, it is possible to store 6 bits per pixel. And since there are 3 components (RGB, that is, 24 bits), it is easy to see how the encoding occurs.

As we need 4 pixels in the base image to store the content of one pixel of the secret image, this second image must be smaller. But how much smaller? It's easy to calculate: let's imagine a base image of 1024 x 768. This gives us 1024 * 768 = 786,432 pixels. Then it is possible to store 786,432 / 4 pixels of the secret image, that is, approximately 196,608 pixels. In this situation, a 320 x 240 (76,800 pixels) image would fit easily, but a 640 x 480 (308,200 pixels) image would not be possible to store.
In addition, it will be necessary to store the dimensions of the secret image in the first few pixels of the resulting image - otherwise it will be impossible to retrieve it. You can, for example, store dimensions in 24 bits: 12 for width and 12 for height. Thus, the maximum values ​​can go up to 4095 (2¹² - 1)


By: [luizeduardomr](https://github.com/luizeduardomr) & [LucasGCardoso](https://github.com/LucasGCardoso)
