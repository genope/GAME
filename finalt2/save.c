#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"





//*********************************************************************************************************************************************************************************************************


personnage initperso (personnage c,int posx,int posy,int posw,int posh,int direction,int posviex , int posviey ,int nbre_de_vie,int score,int spritex, int spritey , int spritew,int spriteh,int numr,int numl , int posscorex, int posscorey , double velocity , double acceleration,int moving , int i) // i c'est le joueur 1 ou 2 
{char scoree[100];
 char spriteright[100];
 char spriteleft[100];

	TTF_Init();

	//chargement du spritesheet 
        sprintf(spriteright,"spriteright%d.png",i);
        c.spriteright= IMG_Load(spriteright);
        sprintf(spriteleft,"spriteleft%d.png",i);     
	c.spriteleft= IMG_Load(spriteleft);  
	

	//Définition des différentes positions du personnage par rapport au background 
	c.position_perso.x = posx;
  	c.position_perso.y = posy;
	c.position_perso.w= posw;
	c.position_perso.h= posh;

	c.direction=direction;    //1 à droite et 0 à gauche 

	//chargement des images de la structure vie en les stockant dans un tableau 
	c.vie_perso.vie[1]=IMG_Load("image_de_vie1.jpg");
	c.vie_perso.vie[2]=IMG_Load("image_de_vie2.jpg");
	c.vie_perso.vie[3]=IMG_Load("image_de_vie3.jpg");
	c.vie_perso.vie[0]=IMG_Load("image_de_vie0.jpg");

	//Définition de la position de ces images par rapport au background
	c.vie_perso.position_de_vie.x=posviex ; 
	c.vie_perso.position_de_vie.y=posviey ; 
	
	//initialisation de nbre de vie 
	c.vie_perso.nbredevie=nbre_de_vie;

	//initialisation du score 
	c.score_perso.score_atteint=score;
	
	//Définition de la position de frame
	c.position_sprite.x=spritex;
	c.position_sprite.y=spritey;
	c.position_sprite.w=spritew;
	c.position_sprite.h=spriteh;

		
	//initialisation des compteurs	
	c.numr=numr;
	c.numl=numl;
	
	//Définition de la couleur noire 	
	SDL_Color policeNoire={0,0,0};

	//ouverture de la police 
	c.score_perso.police_score= TTF_OpenFont("angelina.TTF" , 40);

	//j'ai effectué l'écriture de texte selon le format que j'en aurais besoin 
	sprintf(scoree,"Score: %d",c.score_perso.score_atteint);

	//écriture dans le champ sdl surface* le score 
        c.score_perso.score_texte= TTF_RenderText_Blended(c.score_perso.police_score,scoree,policeNoire);	

	//Définition de la position du texte du score 
	c.score_perso.position_score.x=posscorex ;
	c.score_perso.position_score.y=posscorey ;

	c.velocity=velocity ; 
	c.acceleration=acceleration ; 
	c.moving=moving;
	
  return c;
}

//*********************************************************************************************************************************************************************************************************

background initialiser_background(background b,int posbgx,int posbgy, int dx,int fx, int fy, int dy,int i)
{
char fond[20];

	sprintf(fond,"fond%d.png",i);
        b.background= IMG_Load(fond);
	b.posbg.x=posbgx;
	b.posbg.y=posbgy;
	b.dx=dx;
	b.fx=fx;
	b.fy=fy;
	b.dy=dy;

return b ;
}
//*********************************************************************************************************************************************************************************************************

ennemi initialiser_ennemi(ennemi e,int eposition_ennemix ,int eposition_ennemiy,int epos1x,int epos1y,int epos2x,int epos2y,int eposition_spritex ,int eposition_spritey ,int eposition_spritew ,int eposition_spriteh,int edirection,int i)
{

	char spriteright[100];
        char spriteleft[100];


        sprintf(spriteright,"spriteright%d.png",i);
        e.spriteright= IMG_Load(spriteright);
        sprintf(spriteleft,"spriteleft%d.png",i);     
	e.spriteleft= IMG_Load(spriteleft); 
 
 	e.position_ennemi.x=eposition_ennemix;
	e.position_ennemi.y=eposition_ennemiy;
	e.pos1.x=epos1x;
	e.pos1.y=epos1y;
	e.pos2.x=epos2x;
	e.pos2.y=epos2y;
	e.position_sprite.x=eposition_spritex;
	e.position_sprite.y=eposition_spritey;
	e.position_sprite.w=eposition_spritew;
	e.position_sprite.h=eposition_spriteh;
	e.direction=edirection;
	
return e ;
}


//*********************************************************************************************************************************************************************************************************


void mouvement (personnage *c )
{
if(c->direction ==1)
{
c->position_perso.x+=5; 

if(c->position_perso.x +c->position_sprite.w >1280)
c->position_perso.x=1280-c->position_sprite.w ;

}
else if (c->direction ==0)
{

c->position_perso.x-=5;

if(c->position_perso.x +c->position_sprite.w <0)
c->position_perso.x=10;
}
}

//*********************************************************************************************************************************************************************************************************


void animperso (personnage *c, SDL_Surface *screen)
{
		if (c->direction ==1)
                {	c->numr++; //le compteur de droite augmente 

			if(c->numr==6)//si on arrive à la fin du spritesheet on reprend  
				{
				c->numr=0;
				c->position_sprite.x=0;
				}
			else 		//si non on avance vers la frame suivante on multipliant la largeur de frame par le compteur  
				{
				c->position_sprite.x=c->numr*106;
				}
				c->position_sprite.y=0;
                }
                else if (c->direction ==0)   
		{	c->numl++;
			if(c->numl==6)
			{
				c->numl=0;
				c->position_sprite.x=0;
		   	}
			else 
			{
				c->position_sprite.x=c->numl*106;
			}
				c->position_sprite.y=0;
                 }		
					
}


//*********************************************************************************************************************************************************************************************************


void affichageperso(personnage c, SDL_Surface * screen)

{
	SDL_BlitSurface(c.vie_perso.vie[c.vie_perso.nbredevie], NULL, screen, &c.vie_perso.position_de_vie);
	SDL_BlitSurface(c.score_perso.score_texte, NULL, screen, &c.score_perso.position_score);
	if(c.direction ==1)
 	SDL_BlitSurface(c.spriteright,&c.position_sprite, screen, &c.position_perso);
	else if(c.direction ==0)
 	SDL_BlitSurface(c.spriteleft,&c.position_sprite, screen, &c.position_perso);

	else if(c.direction==-1)
	SDL_BlitSurface(c.spriteright,&c.position_sprite, screen, &c.position_perso);
}


//*********************************************************************************************************************************************************************************************************

void SaveGame(personnage c1, personnage c2, background b ,char* file , ennemi e,int niveau)
{
    FILE * f = fopen(file,"w+") ;
	if (f==NULL)
	{
	   
		printf("erreur, le fichier de sauvegarde ne peut pas etre ouvert\n");
	}
	
	else
	{

	//sauvegarde des donnees du niveau  
    fprintf(f, "%d\n",niveau);

	//sauvegarde des donnees du 1er personnage 
    fprintf(f,"%d\n",c1.position_perso.x);
    fprintf(f,"%d\n",c1.position_perso.y);
    fprintf(f,"%d\n",c1.position_perso.w);
    fprintf(f,"%d\n",c1.position_perso.h);
    fprintf(f,"%d\n",c1.vie_perso.position_de_vie.x);
    fprintf(f,"%d\n",c1.vie_perso.position_de_vie.y);
    fprintf(f,"%d\n",c1.vie_perso.nbredevie);
    fprintf(f,"%d\n",c1.score_perso.score_atteint);
    fprintf(f,"%d\n",c1.position_sprite.x);
    fprintf(f,"%d\n",c1.position_sprite.y);
    fprintf(f,"%d\n",c1.position_sprite.w);
    fprintf(f,"%d\n",c1.position_sprite.h);
    fprintf(f,"%d\n",c1.score_perso.position_score.x);
    fprintf(f,"%d\n",c1.score_perso.position_score.y);
    fprintf(f,"%d\n",c1.numr);
    fprintf(f,"%d\n",c1.numl);
    fprintf(f,"%d\n",c1.direction);
    fprintf(f,"%lf\n",c1.velocity);
    fprintf(f,"%lf\n",c1.acceleration);
    fprintf(f,"%d\n",c1.moving);



       //sauvegarde des donnees du 2eme personnage 
    fprintf(f,"%d\n",c2.position_perso.x);
    fprintf(f,"%d\n",c2.position_perso.y);
    fprintf(f,"%d\n",c2.position_perso.w);
    fprintf(f,"%d\n",c2.position_perso.h);
    fprintf(f,"%d\n",c2.vie_perso.position_de_vie.x);
    fprintf(f,"%d\n",c2.vie_perso.position_de_vie.y);
    fprintf(f,"%d\n",c2.score_perso.score_atteint);
    fprintf(f,"%d\n",c2.vie_perso.nbredevie);
    fprintf(f,"%d\n",c2.position_sprite.x);
    fprintf(f,"%d\n",c2.position_sprite.y);
    fprintf(f,"%d\n",c2.position_sprite.w);
    fprintf(f,"%d\n",c2.position_sprite.h);
    fprintf(f,"%d\n",c2.score_perso.position_score.x);
    fprintf(f,"%d\n",c2.score_perso.position_score.y);
    fprintf(f,"%d\n",c2.numr);
    fprintf(f,"%d\n",c2.numl);
    fprintf(f,"%d\n",c2.direction);
    fprintf(f,"%lf\n",c2.velocity);
    fprintf(f,"%lf\n",c2.acceleration);
    fprintf(f,"%d\n",c2.moving);
	//sauvegarde des donnees du background 
    fprintf(f,"%d\n",b.posbg.x);
    fprintf(f,"%d\n",b.posbg.y);
    fprintf(f,"%d\n",b.dx);
    fprintf(f,"%d\n",b.fx);
    fprintf(f,"%d\n",b.fy);
    fprintf(f,"%d\n",b.dy);


	//sauvegarde des donnees de l'ennemi 
    fprintf(f,"%d\n",e.position_ennemi.x);
    fprintf(f,"%d\n",e.position_ennemi.y);
    fprintf(f,"%d\n",e.pos2.x);
    fprintf(f,"%d\n",e.pos2.y);
    fprintf(f,"%d\n",e.pos1.x);
    fprintf(f,"%d\n",e.pos1.y);
    fprintf(f,"%d\n",e.position_sprite.x);
    fprintf(f,"%d\n",e.position_sprite.y);
    fprintf(f,"%d\n",e.direction);
    fprintf(f,"%d\n",e.numennemi);


    fclose(f);
	}
}

//*********************************************************************************************************************************************************************************************************


void initialiser_save(Objet *sauv,Objet *sauvy,Objet *sauvn)
{
	sauv->img=IMG_Load("save.png") ;
	sauv->pos.x=0;
	sauv->pos.y=0;
	sauvy->img=IMG_Load("savey.png") ;
	sauvy->pos.x=0;
	sauvy->pos.y=0;
	sauvn->img=IMG_Load("saven.png");
	sauvn->pos.x=0;
	sauvn->pos.y=0;
}

//**********************************************************************************************************************************************************************************************************

int verif_motion_save (SDL_Event event,Objet surface)
{
  int pos=0 ;

  if (event.motion.x > surface.pos_text.x && event.motion.x < (surface.pos_text.w + surface.pos_text.x) && event.motion.y > surface.pos_text.y && event.motion.y < (surface.pos_text.h + surface.pos_text.y)) 
    pos=1 ;

    return pos ;
}


//*********************************************************************************************************************************************************************************************************



void clic_souris_save(SDL_Surface *screen,SDL_Event event, int curseur ,Objet sauvn,Objet sauvy,personnage c1, personnage c2, background b,char* file , ennemi e,int niveau)
{
            if (event.button.button == SDL_BUTTON_LEFT && (curseur)==1 )
           {
            if(verif_motion_save (event,sauvy)) 
            {
                SDL_BlitSurface(sauvy.img, NULL, screen, &(sauvy.pos));
		SDL_Flip(screen);
		SaveGame(c1,c2,b,file,e,niveau);
            }     
           }

           if (event.button.button == SDL_BUTTON_LEFT && (curseur)==2 )
           {
            if(verif_motion_save (event,sauvn)) 
            {
                SDL_BlitSurface(sauvn.img, NULL, screen, &(sauvn.pos));
		SDL_Flip(screen);
            }                            
           }
}

//*********************************************************************************************************************************************************************************************************

void clic_entrer_save(SDL_Surface *screen ,Mix_Chunk *effect, int curseur,Objet sauvn,Objet sauvy,personnage c1, personnage c2, background b,char* file , ennemi e,int niveau)
{
               switch ((curseur))
             {
               case 1:
                SDL_BlitSurface(sauvy.img, NULL, screen, &(sauvy.pos));
		SDL_Flip(screen);
		SaveGame(c1,c2,b ,file,e,niveau);
               break;
               case 2:
                SDL_BlitSurface(sauvn.img, NULL, screen, &(sauvn.pos));
		SDL_Flip(screen); 
               break;                                      
             }
}

//*********************************************************************************************************************************************************************************************************

void mouse_motion_save (SDL_Surface *screen ,SDL_Event event,Mix_Chunk *effect,int *curseur,Objet sauvn,Objet sauvy )
{
          if(verif_motion_save (event,sauvy)) 
            {
              if((*curseur)==1)
              return;
              *curseur=1 ;
              SDL_BlitSurface(sauvy.img, NULL, screen, &(sauvy.pos));
	      SDL_Flip(screen);
              Mix_PlayChannel(1,effect,0);              
            }
         
          if(verif_motion_save (event,sauvn)) 
            {
              if((*curseur)==2)
              return;              
              *curseur=2 ;
              SDL_BlitSurface(sauvn.img, NULL, screen, &(sauvn.pos));
	      SDL_Flip(screen); 
              Mix_PlayChannel(1,effect,0);              
            }                        
}


//*********************************************************************************************************************************************************************************************************


void deplacement_down_save (SDL_Surface *screen ,Mix_Chunk *effect,int *curseur,Objet sauvn,Objet sauvy )
{
               (*curseur)++ ;
               if((*curseur)<3)
                switch ((*curseur))
                  {
                    case 1:
                       SDL_BlitSurface(sauvy.img, NULL, screen, &(sauvy.pos));
	      	       SDL_Flip(screen); 
                       Mix_PlayChannel(1,effect,0);
                    break;
                    case 2 :
                       SDL_BlitSurface(sauvn.img, NULL, screen, &(sauvn.pos));
	      	       SDL_Flip(screen); 
                       Mix_PlayChannel(1,effect,0);
                    break;
                  }
                else
                {
                  SDL_BlitSurface(sauvy.img, NULL, screen, &(sauvy.pos));
	      	  SDL_Flip(screen); 
                  Mix_PlayChannel(1,effect,0);
                  (*curseur)=1 ;
                }
}

//*********************************************************************************************************************************************************************************************************


void deplacement_up_save (SDL_Surface *screen ,Mix_Chunk *effect,int *curseur,Objet sauvn,Objet sauvy,int *firsttime)
{
              if((*curseur)==0 && (*firsttime)==0)
               {
                 SDL_BlitSurface(sauvy.img, NULL, screen, &(sauvy.pos));
	      	 SDL_Flip(screen);
                 Mix_PlayChannel(1,effect,0);
                 (*curseur)=1 ;
                 (*firsttime)=1 ;
               }
             else
               {
                 (*curseur)-- ;
                 if((*curseur)!=0)
                 {
                  switch ((*curseur))
                  {
                    case 1:
                       SDL_BlitSurface(sauvy.img, NULL, screen, &(sauvy.pos));
	      	       SDL_Flip(screen); 
                       Mix_PlayChannel(1,effect,0);
                    break;
                    case 2 :
                       SDL_BlitSurface(sauvn.img, NULL, screen, &(sauvn.pos));
	      	       SDL_Flip(screen); 
                       Mix_PlayChannel(1,effect,0);
                    break;
                  }//fin switch (*curseur)
                 }
                 else 
                 {
                       SDL_BlitSurface(sauvn.img, NULL, screen, &(sauvn.pos));
	      	       SDL_Flip(screen); 
                       Mix_PlayChannel(1,effect,0); 
                       (*curseur)=3 ;                  
                 }
                 
               } 
}

//*********************************************************************************************************************************************************************************************************


int deplacement_up_down_save(SDL_Surface *screen, SDL_Event event ,int *firsttime,int *curseur,Objet sauvn,Objet sauvy, Mix_Chunk *effect,int *go,personnage c1, personnage c2, background b,char* file , ennemi e,int niveau)
{

   
      SDL_WaitEvent(&event);
    switch (event.type)
    {
      break ;
      case SDL_MOUSEBUTTONDOWN:
           clic_souris_save(screen,event,*curseur,sauvn,sauvy,c1,c2,b,file,e,niveau);       *go= 0 ;          
      break;
      case SDL_MOUSEMOTION:
	   mouse_motion_save (screen ,event,effect,curseur,sauvn,sauvy );
      break;
      case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
           break ; 
           case SDLK_RETURN:
	       clic_entrer_save(screen ,effect,*curseur,sauvn,sauvy,c1,c2,b,file ,e,niveau); *go= 0 ;
           break ;
           case SDLK_DOWN :
               deplacement_down_save (screen ,effect,curseur,sauvn,sauvy );
           break ;
           case SDLK_UP :
               deplacement_up_save (screen ,effect,curseur,sauvn,sauvy,firsttime);
           break ;
     
          }//fin switch keydown
    }//fin switch 

     return *go ;
}

//*********************************************************************************************************************************************************************************************************

int save(SDL_Surface *screen, SDL_Event event ,int *firsttime,int *curseur,Objet sauv,Objet sauvn,Objet sauvy, Mix_Chunk *effect,personnage c1, personnage c2, background b,char* file , ennemi e,int niveau,int *go)
{
SDL_BlitSurface(sauv.img, NULL, screen, &(sauv.pos));
SDL_Flip(screen);
while(*go)
*go=deplacement_up_down_save(screen,event ,firsttime,curseur,sauvn,sauvy,effect,go,c1,c2,b,file,e,niveau);

return *go ;

}

//*********************************************************************************************************************************************************************************************************
void LoadGame(personnage *c1, personnage *c2, background *b , char filename[], ennemi *e ,int *niveau,SDL_Surface *screen)
{
	TTF_Init();

	char scoree[100];
	char scoree2[100];
	char file[20];

	

    FILE* f = fopen("save.txt","r");

int c1vie_personbredevie, c2vie_personbredevie , c1positionx,c1positiony ,c1positionw,c1positionh,c2positionw,c2positionh, c2positionx , c2positiony , c1score_persoscore_atteint, c2score_persoscore_atteint, c1position_spritex, c1position_spritey, c2position_spritex, c2position_spritey ;

int c1numr, c2numr ,c1numl ,c2numl , c1direction, c2direction,c1posviey ,c1posviex ,c2posviex ,c2posviey,c1position_spritew,c1position_spriteh,c2position_spritew,c2position_spriteh , c1posscorey,c1posscorex , c2posscorex,  c2posscorey ,c1moving,c2moving; 

double c1vitesse , c2vitesse ,c1acceleration ,c2acceleration ;

int eposition_ennemix , eposition_ennemiy ,epos2x, epos2y ,epos1x ,epos1y , eposition_spritex,eposition_spritey ,eposition_spritew ,eposition_spriteh, edirection ,enumennemi ;

int bposbgx , bposbgy , bdx, bfx ,bfy , bdy , niveauu ;

int curseur = 0, firsttime = 0;

Objet sauv , sauvy, sauvn ;

Mix_Chunk *effect ;

SDL_Color policeNoire={0,0,0};

SDL_Event event ; 

strcpy(file,"save.txt");


if(f!=NULL)
{
while(!feof(f))
{

	//lecture de niveau 
	fscanf(f, "%d\n",&niveauu);

	//lecture des donnees du 1er personnage 
    fscanf(f, "%d\n",&c1positionx);
    fscanf(f, "%d\n",&c1positiony);
    fscanf(f, "%d\n",&c1positionw);
    fscanf(f, "%d\n",&c1positionh);
    fscanf(f, "%d\n",&c1posviex);
    fscanf(f, "%d\n",&c1posviey);
    fscanf(f, "%d\n",&c1vie_personbredevie);
    fscanf(f,"%d\n",&c1score_persoscore_atteint);
    fscanf(f, "%d\n",&c1position_spritex);
    fscanf(f, "%d\n",&c1position_spritey);
    fscanf(f, "%d\n",&c1position_spritew);
    fscanf(f, "%d\n",&c1position_spriteh);
    fscanf(f, "%d\n",&c1posscorex);
    fscanf(f, "%d\n",&c1posscorey);
    fscanf(f, "%d\n",&c1numr);
    fscanf(f, "%d\n",&c1numl);
    fscanf(f, "%d\n",&c1direction);
    fscanf(f, "%lf\n",&c1vitesse);
    fscanf(f, "%lf\n",&c1acceleration);
    fscanf(f, "%d\n",&c1moving);

	//lecture des donnees du 2eme personnage 
    fscanf(f, "%d\n",&c2positionx);
    fscanf(f, "%d\n",&c2positiony);
    fscanf(f, "%d\n",&c2positionw);
    fscanf(f, "%d\n",&c2positionh);
    fscanf(f, "%d\n",&c2posviex);
    fscanf(f, "%d\n",&c2posviey);
    fscanf(f, "%d\n",&c2vie_personbredevie);
    fscanf(f,"%d\n",&c2score_persoscore_atteint);
    fscanf(f, "%d\n",&c2position_spritex);
    fscanf(f, "%d\n",&c2position_spritey);
    fscanf(f, "%d\n",&c2position_spritew);
    fscanf(f, "%d\n",&c2position_spriteh);
    fscanf(f, "%d\n",&c2posscorex);
    fscanf(f, "%d\n",&c2posscorey);
    fscanf(f, "%d\n",&c2numr);
    fscanf(f, "%d\n",&c2numl);
    fscanf(f, "%d\n",&c2direction);
    fscanf(f, "%lf\n",&c2vitesse);
    fscanf(f, "%lf\n",&c2acceleration);
    fscanf(f, "%d\n",&c2moving);
	

	//lecture des donnees background 
    fscanf(f, "%d\n",&bposbgx);
    fscanf(f, "%d\n",&bposbgy);
    fscanf(f, "%d\n",&bdx);
    fscanf(f, "%d\n",&bfx);
    fscanf(f, "%d\n",&bfy);
    fscanf(f, "%d\n",&bdy);

	//lecture des donnees de l'ennemi
    fscanf(f, "%d\n",&eposition_ennemix);
    fscanf(f, "%d\n",&eposition_ennemiy);
    fscanf(f, "%d\n",&epos2x);
    fscanf(f, "%d\n",&epos2y);
    fscanf(f, "%d\n",&epos1x);
    fscanf(f, "%d\n",&epos1y);
    fscanf(f, "%d\n",&eposition_spritex);
    fscanf(f, "%d\n",&eposition_spritey);
    fscanf(f, "%d\n",&edirection);
    fscanf(f, "%d\n",&enumennemi);

} 
fclose(f);
}

else 
{
	printf("erreur, le fichier de sauvegarde ne peut pas etre ouvert\n");
}

*niveau=niveauu;

*c1=initperso (*c1,c1positionx,c1positiony,c1positionw,c1positionh,c1direction,c1posviex ,c1posviey ,c1vie_personbredevie,c1score_persoscore_atteint,c1position_spritex,c1position_spritey , c1position_spritew,c1position_spriteh,c1numr,c1numl , c1posscorex,  c1posscorey ,  c1vitesse ,c1acceleration,c1moving,1);
 
*c2=initperso (*c2,c2positionx,c2positiony,c2positionw,c2positionh,c2direction,c2posviex ,c2posviey ,c2vie_personbredevie,c2score_persoscore_atteint,c2position_spritex,c2position_spritey , c2position_spritew,c2position_spriteh,c2numr,c2numl , c2posscorex, c2posscorey ,  c2vitesse ,c2acceleration,c2moving,2);
 
*b=initialiser_background(*b,bposbgx,bposbgy,bdx,bfx,bfy,bdy,niveauu);

*e=initialiser_ennemi(*e,eposition_ennemix,eposition_ennemiy,epos1x,epos1y,epos2x,epos2y,eposition_spritex ,eposition_spritey ,eposition_spritew ,eposition_spriteh,edirection,enumennemi);
	

}
