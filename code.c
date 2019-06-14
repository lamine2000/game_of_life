#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "game.h"

int main(int argc, char* argv[])
{
    SDL_Surface *ecran = NULL, *square[NB_SQUARE_HAUTEUR][NB_SQUARE_LARGEUR];
    SDL_Rect positionSquare;
    SDL_Event event;
    Uint32 white, black;
    Uint32 matriceColor [NB_SQUARE_HAUTEUR][NB_SQUARE_LARGEUR];
    bool matriceState [NB_SQUARE_HAUTEUR][NB_SQUARE_LARGEUR];
    bool continuer = 1;
    int cpt;

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    SDL_WM_SetCaption("The game of life",NULL);

    white = SDL_MapRGB(ecran->format,230,230,230);
    black = SDL_MapRGB(ecran->format,25,25,25);

    for(int i = 0; i < NB_SQUARE_HAUTEUR; i++)
    {
        for (int j = 0; j < NB_SQUARE_LARGEUR; j++)
        {
            matriceColor[i][j] = white;
            matriceState[i][j] = 0;

        }
    }

   for(int i = 0; i < NB_SQUARE_HAUTEUR; i++)
    {
        for (int j = 0; j < NB_SQUARE_LARGEUR; j++)
        {
            square[i][j] = SDL_CreateRGBSurface(SDL_HWSURFACE,TAILLE_SQUARE,TAILLE_SQUARE,32,0,0,0,0);

            positionSquare.x = j * TAILLE_SQUARE;
            positionSquare.y = i * TAILLE_SQUARE;

            SDL_FillRect(square[i][j],NULL,matriceColor[i][j]);

            SDL_BlitSurface(square[i][j],NULL,ecran,&positionSquare);
        }
    }

    SDL_Flip(ecran);

   SDL_EnableKeyRepeat(100,100);
    while(continuer)
    {
        SDL_WaitEvent(&event);
        int i,j;

        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;

                    case SDLK_r: //reset
                        for (int i = 0; i< NB_SQUARE_HAUTEUR; i++)
                        {
                            for(int j = 0; j<NB_SQUARE_LARGEUR; j++)
                            {
                                matriceColor[i][j] = white;
                                matriceState[i][j] = 0;

                                positionSquare.x = j * TAILLE_SQUARE;
                                positionSquare.y = i * TAILLE_SQUARE;

                                SDL_FillRect(square[i][j],NULL,white);
                                SDL_BlitSurface(square[i][j],NULL,ecran,&positionSquare);
                            }
                        }
                        break;

                    case SDLK_SPACE: //mise a jour de la matrice des changements d'états de la génération suivante

                        for (int i = 0; i < NB_SQUARE_HAUTEUR; i++)
                        {
                            for(int j = 0; j < NB_SQUARE_LARGEUR; j++)
                            {
                                cpt = 0;

                                for(int k = i-1; k <= i+1; k++)
                                {
                                    for(int l = j-1; l <= j+1; l++)
                                    {
                                        if(k>=0 && l>=0 && k<NB_SQUARE_HAUTEUR && l<NB_SQUARE_LARGEUR)
                                            if(matriceColor[k][l] == black)
                                                cpt++;
                                    }
                                }

                                if(matriceColor[i][j] == black)
                                {
                                    cpt--;  //On ne compte pas la cellule elle meme

                                    if(cpt == 2 || cpt == 3)    //regle de la survie
                                        matriceState[i][j] = 1;
                                    else                        //regle de la mort
                                        matriceState[i][j] = 0;
                                }

                                else
                                {
                                        if(cpt == 3)            //regle de la naissance
                                            matriceState[i][j] = 1;
                                }
                            }
                        }

                        //transposition des changements d'etats dans la matrice des couleurs

                        for(int i = 0; i < NB_SQUARE_HAUTEUR; i++)
                        {
                            for (int j = 0; j < NB_SQUARE_LARGEUR; j++)
                            {
                                matriceColor[i][j] = (matriceState[i][j] == 1)? black:white;

                                /*if(matriceState[i][j] == 1)
                                    matriceColor[i][j] = black;
                                else
                                    matriceColor[i][j] = white;*/

                                positionSquare.x = j * TAILLE_SQUARE;
                                positionSquare.y = i * TAILLE_SQUARE;

                                SDL_FillRect(square[i][j],NULL,matriceColor[i][j]);
                                SDL_BlitSurface(square[i][j],NULL,ecran,&positionSquare);
                            }
                        }

                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP: //changer la couleur d'une case quand on clique dessus
                        if(event.button.button == SDL_BUTTON_LEFT)
                        {
                            int p = event.button.x;
                            int k = event.button.y;

                            do
                            {
                                j = p--;
                            }while((p%TAILLE_SQUARE) != 0); //trouver l'abscisse de la case sur laquelle on a cliqué

                            do
                            {
                                i = k--;
                            }while((k%TAILLE_SQUARE) != 0); //trouver l'ordonnée de la case sur laquelle on a cliqué
                        }
                        //conversion de ces coordonnées de pixels en indices de cases
                        i = i/TAILLE_SQUARE;
                        j = j/TAILLE_SQUARE;

                        if(matriceColor[i][j] == white)
                            {
                                SDL_FillRect(square[i][j],NULL,black);
                                matriceColor[i][j] = black;
                                matriceState[i][j] = 1;
                            }

                        else
                            {
                                SDL_FillRect(square[i][j],NULL,white);
                                matriceColor[i][j] = white;
                                matriceState[i][j] = 0;
                            }

                            positionSquare.x = j * TAILLE_SQUARE;
                            positionSquare.y = i * TAILLE_SQUARE;

                            SDL_BlitSurface(square[i][j],NULL,ecran,&positionSquare);
                        break;
        }

        SDL_Flip(ecran);
    }

    for(int i = 0; i < NB_SQUARE_HAUTEUR; i++)
    {
        for (int j = 0; j < NB_SQUARE_LARGEUR; j++)
        {
            SDL_FreeSurface(square[i][j]);
        }
    }

    SDL_Quit();


    return EXIT_SUCCESS;
}

