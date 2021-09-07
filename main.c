#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include "game.h"

int main(int argc, char* argv[])
{
    SDL_Surface *ecran = NULL, *square[NB_SQUARE_HAUTEUR][NB_SQUARE_LARGEUR];
    SDL_Rect positionSquare;
    SDL_Event event;
    Uint32 white, black;
    Uint32 matriceColor [NB_SQUARE_HAUTEUR][NB_SQUARE_LARGEUR];
    bool matriceState [NB_SQUARE_HAUTEUR][NB_SQUARE_LARGEUR];
    bool isRunning = true;
    int cpt_square_around;

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    SDL_WM_SetCaption("The game of life",NULL);

    white = SDL_MapRGB(ecran->format,230,230,230);
    black = SDL_MapRGB(ecran->format,25,25,25);

    for(int index_i = 0; index_i < NB_SQUARE_HAUTEUR; index_i++)
    {
        for (int index_j = 0; index_j < NB_SQUARE_LARGEUR; index_j++)
        {
            matriceColor[index_i][index_j] = white;
            matriceState[index_i][index_j] = 0;

        }
    }

    for(int index_i = 0; index_i < NB_SQUARE_HAUTEUR; index_i++)
    {
        for (int index_j = 0; index_j < NB_SQUARE_LARGEUR; index_j++)
        {
            square[index_i][index_j] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_SQUARE, TAILLE_SQUARE, 32, 0, 0, 0, 0);

            positionSquare.x = (Sint16) (index_j * TAILLE_SQUARE);
            positionSquare.y = (Sint16) (index_i * TAILLE_SQUARE);

            SDL_FillRect(square[index_i][index_j], NULL, matriceColor[index_i][index_j]);

            SDL_BlitSurface(square[index_i][index_j], NULL, ecran, &positionSquare);
        }
    }

    SDL_Flip(ecran);

    SDL_EnableKeyRepeat(100,75);
    srand(time(NULL));
    while(isRunning)
    {
        SDL_WaitEvent(&event);
        int i,j;

        switch(event.type)
        {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        isRunning = 0;
                        break;

                    case SDLK_r: //reset
                        for (int index_i = 0; index_i < NB_SQUARE_HAUTEUR; index_i++)
                        {
                            for(int index_j = 0; index_j < NB_SQUARE_LARGEUR; index_j++)
                            {
                                matriceColor[index_i][index_j] = white;
                                matriceState[index_i][index_j] = 0;

                                positionSquare.x = (Sint16) (index_j * TAILLE_SQUARE);
                                positionSquare.y = (Sint16) (index_i * TAILLE_SQUARE);

                                SDL_FillRect(square[index_i][index_j], NULL, white);
                                SDL_BlitSurface(square[index_i][index_j], NULL, ecran, &positionSquare);
                            }
                        }
                        break;

                    case SDLK_h: //remplissage ranndomisé de la matrice
                        for(int index_i=0; index_i < NB_SQUARE_HAUTEUR; index_i++)
                        {
                            for (int index_j = 0; index_j < NB_SQUARE_LARGEUR; index_j++)
                            {
                                matriceColor[index_i][index_j] = (rand() % 2) ? black : white;
                                SDL_FillRect(square[index_i][index_j], NULL, matriceColor[index_i][index_j]);

                                positionSquare.x = (Sint16) (index_j * TAILLE_SQUARE);
                                positionSquare.y = (Sint16) (index_i * TAILLE_SQUARE);

                                SDL_BlitSurface(square[index_i][index_j], NULL, ecran, &positionSquare);
                            }
                        }
                        break;

                    case SDLK_SPACE: //mise a jour de la matrice des couleurs suivant la matrice des changements d'etats

                        for (int index_i = 0; index_i < NB_SQUARE_HAUTEUR; index_i++)
                        {
                            for(int index_j = 0; index_j < NB_SQUARE_LARGEUR; index_j++)
                            {
                                cpt_square_around = 0;

                                for(int k = index_i - 1; k <= index_i + 1; k++)
                                    for(int l = index_j - 1; l <= index_j + 1; l++)
                                        if(k>=0 && l>=0 && k<NB_SQUARE_HAUTEUR && l<NB_SQUARE_LARGEUR)
                                            if(matriceColor[k][l] == black)
                                                cpt_square_around++;

                                if(matriceColor[index_i][index_j] == black)
                                {
                                    cpt_square_around--;  //On ne compte pas la cellule elle meme

                                    if(cpt_square_around == 2 || cpt_square_around == 3)    //regle de la survie
                                        matriceState[index_i][index_j] = 1;
                                    else                        //regle de la mort
                                        matriceState[index_i][index_j] = 0;
                                }

                                else
                                    if(cpt_square_around == 3)            //regle de la naissance
                                        matriceState[index_i][index_j] = 1;
                            }
                        }

                        //transposition des changements d'etats dans la matrice des couleurs

                        for(int index_i = 0; index_i < NB_SQUARE_HAUTEUR; index_i++)
                        {
                            for (int index_j = 0; index_j < NB_SQUARE_LARGEUR; index_j++)
                            {
                                matriceColor[index_i][index_j] = (matriceState[index_i][index_j] == 1) ? black : white;

                                positionSquare.x =(Sint16) (index_j * TAILLE_SQUARE);
                                positionSquare.y = (Sint16) (index_i * TAILLE_SQUARE);

                                SDL_FillRect(square[index_i][index_j], NULL, matriceColor[index_i][index_j]);
                                SDL_BlitSurface(square[index_i][index_j], NULL, ecran, &positionSquare);
                            }
                        }

                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP: //changer la couleur d'une case quand on clique dessus
                if(event.button.button == SDL_BUTTON_LEFT) {
                    int p = event.button.x;
                    int k = event.button.y;

                    //calculer les coordonnées de la case sur laquelle on a cliqué
                    j = p - (p % TAILLE_SQUARE);
                    i = k - (k % TAILLE_SQUARE);

                    //conversion de ces coordonnées de pixels en indices de cases
                    i /= TAILLE_SQUARE;
                    j /= TAILLE_SQUARE;

                    if (matriceColor[i][j] == white) {
                        SDL_FillRect(square[i][j], NULL, black);
                        matriceColor[i][j] = black;
                        matriceState[i][j] = 1;
                    } else {
                        SDL_FillRect(square[i][j], NULL, white);
                        matriceColor[i][j] = white;
                        matriceState[i][j] = 0;
                    }

                    positionSquare.x = (Sint16) (j * TAILLE_SQUARE);
                    positionSquare.y = (Sint16) (i * TAILLE_SQUARE);

                    SDL_BlitSurface(square[i][j], NULL, ecran, &positionSquare);
                }
                break;

            default:
                break;
        }

        SDL_Flip(ecran);
    }

    for(int i = 0; i < NB_SQUARE_HAUTEUR; i++)
        for (int j = 0; j < NB_SQUARE_LARGEUR; j++)
            SDL_FreeSurface(square[i][j]);

    SDL_Quit();

    return EXIT_SUCCESS;
}