#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <Lista_ListaCircular.h>


void imprime(Columna *m, WINDOW *win, int alto, int ancho, int *arreglo, int *monedas, int y, int *vidas, int *Portales, int mundo)
{
	int i, j, a = 0;
	Columna *apu = m;
 	
		bkgd( COLOR_PAIR( 1 ) | A_BOLD );      /* establece los colores */
		border( '|', '|', '-', '-', '+', '+', '+', '+' );  /* dibuja un cuadro */
		
		attron( COLOR_PAIR(8 ) );       /* activa los colores */
		mvprintw( 0,10, "MUNDO:%d", mundo );
		mvprintw( 0,20, "VIDAS:%d", *vidas );
		mvprintw( 0,30, "MONEDAS:%d", *monedas );
		mvprintw( 0, 60, "Salir F2" );
		attroff( COLOR_PAIR( 8) );      /* desactiva los colores */
		
		attron( COLOR_PAIR( 13 ) );       /* activa los colores */
		mvprintw( 0, 42, "\"MARIO BROS\"" );
		attroff( COLOR_PAIR( 13 ) );      /* desactiva los colores */
		
		attron( COLOR_PAIR( 1 ) );       /* activa los colores */
	
	for (i = 1; i < ancho/2; ++i, apu = apu->sig)
	{	
			ElementoL *apuL;

			apuL = apu->LD;		
			for (j = 1; j < alto; ++j,apuL = apuL->sig)
			{
				 move(j, i);
				switch(apuL->el.color) /* coloreamos escenario */
				{
				case 'O': init_pair( 10, COLOR_CYAN, COLOR_BLUE);attron( COLOR_PAIR( 10 ) );printw( " ");attroff( COLOR_PAIR( 10 ) );break;
				case 'B': init_pair( 2, COLOR_WHITE, COLOR_WHITE );attron( COLOR_PAIR( 2 ) );printw( " ");attroff( COLOR_PAIR( 2 ) );
					if(apuL->ant->el.simbolo != ':' && apuL->el.simbolo == ':')
					{
					arreglo[a] = j;
					a++;
					}break;
				case 'R': init_pair( 3, COLOR_MAGENTA, COLOR_MAGENTA );attron( COLOR_PAIR( 3 ) );printw( " ", apuL->el.simbolo);attroff( COLOR_PAIR( 3 ) );break;
				case 'G': init_pair( 4, COLOR_RED, COLOR_RED );attron( COLOR_PAIR( 4 ) );printw( "%c", apuL->el.simbolo);attroff( COLOR_PAIR( 4 ) );break;
				case 'Q': init_pair( 11, COLOR_GREEN, COLOR_GREEN );attron( COLOR_PAIR( 11 ) );printw( "%c", apuL->el.simbolo);attroff( COLOR_PAIR( 11 ) );break;
				case 'P': init_pair( 12, COLOR_BLACK, COLOR_BLACK );attron( COLOR_PAIR( 12 ) );printw( "%c", apuL->el.simbolo);attroff( COLOR_PAIR( 12 ) );break;
				case 'N': init_pair( 5, COLOR_WHITE, COLOR_BLACK );attron( COLOR_PAIR( 5 ) );printw(" ");attroff( COLOR_PAIR( 5 ) );break;
				case 'F': init_pair( 8, COLOR_WHITE, COLOR_BLUE );attron( COLOR_PAIR( 8 ) );printw( "%c", apuL->el.simbolo);attroff( COLOR_PAIR( 8 ) );break;				
				case 'W': init_pair( 6, COLOR_WHITE, COLOR_BLACK );attron( COLOR_PAIR( 6 ) );printw( "%c", apuL->el.simbolo);attroff( COLOR_PAIR( 6 ) );break;
				case 'Y': init_pair( 9, COLOR_YELLOW, COLOR_YELLOW );attron( COLOR_PAIR( 9 ) );printw( "%c", apuL->el.simbolo);attroff( COLOR_PAIR( 9 ) );
								if(apuL->ant->el.simbolo != ':' && apuL->el.simbolo == ':') {arreglo[a] = j; a++;}break;	
				case 'X': init_pair( 13, COLOR_WHITE, COLOR_RED );attron( COLOR_PAIR( 13 ) );printw( "%c", apuL->el.simbolo);attroff( COLOR_PAIR( 13 ) );
								if(apuL->el.simbolo == 'X') {apuL->el.portal = 1;} break;			
				case 'D': init_pair( 7, COLOR_RED, COLOR_YELLOW );attron( COLOR_PAIR( 7 ) );printw( "%c", apuL->el.simbolo);attroff( COLOR_PAIR( 7 ) );
								if(apuL->el.simbolo == 'C') {apuL->el.moneda = 1;}
								if(apuL->el.simbolo == 'W') {apuL->el.enemigo = 1;} break;
				case ':': init_pair( 15, COLOR_BLACK, COLOR_GREEN);attron( COLOR_PAIR(15));printw( "%c", apuL->el.simbolo);attroff( COLOR_PAIR(15));
					if(apuL->ant->el.simbolo != ':' && apuL->el.simbolo == ':'){ arreglo[a] = j; a++;}break;
				}		
				
				if( i == 52 && (j == y-1 || j == y-3 || j == y-2) && apuL->el.moneda == 1)
				{	
					(*monedas)++;
					apuL->el.moneda = 0;
					apuL->el.color = apuL->ant->el.color;
					apuL->el.simbolo = apuL->ant->el.simbolo;
				}
					if( i == 52 && (j == y-1 || j == y-3 || j == y-2) && apuL->el.enemigo == 1)
				{	
					(*vidas)--;
					apuL->el.enemigo = 0;
					apuL->el.color = apuL->ant->el.color;
					apuL->el.simbolo = apuL->ant->el.simbolo;
				}

				if( i == 52 && (j == y-1 || j == y-3 || j == y-2) && apuL->el.portal == 1)
				{	
					(*Portales) = 1;
				}
			}
	} 
	
}

void personaje (int y)
{
	
	init_pair( 5, COLOR_GREEN, COLOR_BLACK );
	attron( COLOR_PAIR( 5 )  );       /* activa los colores */
    mvprintw( y-2,52, "O" );
    mvprintw( y-1,52, "|" );		/* dibujamos personaje */
    mvprintw( y,52, "m" );
	attroff( COLOR_PAIR( 5 )  );
	
	
}

void pantallaInicio(void)
{
	  
		
		attron( COLOR_PAIR( 13 ) | A_BOLD | A_UNDERLINE);       /* activa los colores */
		mvprintw( 5, 45, "--SUPER MARIO BROS VERSION CHINA--");
		border( '|', '|', '-', '-', '+', '+', '+', '+' );  /* dibuja un cuadro */
		
		mvprintw( 10,40, "___PULSA LA TECLA ESPACIO PARA COMENZAR___" );
		mvprintw( 19,30, "___CONSIGUE MAS DE 100 MONEDAS PARA GANAR Y PULSA F2 PARA TERMINAR___" );		
		mvprintw( 22,31, "CUIDADO LAS MONEDAS CON 'W' SON FALSAS, PIERDES VIDAS SI LAS TOCAS" );

		attroff( COLOR_PAIR( 13 ) | A_BOLD | A_UNDERLINE);
			

}

void pantallaFinal(int vidas, int monedas)
{
	  
		
		attron( COLOR_PAIR( 13 ) | A_BOLD | A_UNDERLINE);       /* activa los colores */
		if(monedas > 100)
		mvprintw( 5, 39, "--¡ ¡ ¡ ¡ G A N A S T E ! ! ! !--");
		else if( vidas <= 0 && monedas < 100)
		mvprintw( 5, 45, "--P E R D I S T E--");
		else
		mvprintw( 5, 45, "--G A M E  O V E R--");
		border( '|', '|', '-', '-', '+', '+', '+', '+' );  /* dibuja un cuadro */
		
		mvprintw( 10,40, "___MONEDAS CONSEGUIDAS: %d ___", monedas );
		mvprintw( 15,45, "___ VIDAS: %d ___", vidas );
		attroff( COLOR_PAIR( 13 ) | A_BOLD | A_UNDERLINE);
	
}
//----------------------------------------------------------------------------------//
int main(void)
{

	 Mapa M[5];
	 arreglo M1; 
	 Columna *aux;
	 WINDOW *win;
    float y = 0., t, dt, g, vo;
	 int key, *suelo, monedas = 0, vidas = 10, Portales = 0, i, mundo = 0, next[] = {9, 8, 7, 6, 1, 0, 5, 4, 3, 2};
	 char Salta, buffer[64], nombres[10][32] = {"Mapa1.txt", "Mapa2.txt" ,"Mapa3.txt", "Mapa4.txt", "Mapa5.txt", "Mapa6.txt", "Mapa7.txt" ,"Mapa8.txt", "Mapa9.txt", "Mapa10.txt"};
	 
	for(i = 0; i < 10; i++)
	{
	leeMapaArreglo(nombres[i], &M1);
   creaMapa (&(M[i]), &M1);
	leeMapaCircular(&(M[i]), &M1);
	M[i].next = next[i];
	}

//__________________________//

	win=initscr();

	clearok(win,TRUE);
	keypad(win,TRUE);
	curs_set( FALSE );      /* hace invisible el cursor fisico */
	
	

		if( has_colors()	/* verifica si la terminal tiene soporte o no */ ) {
		
			start_color();	/* inicia el modo de colores */
			init_pair( 1, COLOR_BLUE, COLOR_BLACK);	/* establece los colores */
			init_pair( 8, COLOR_WHITE, COLOR_BLACK );	/* establece los colores */
			init_pair( 13, COLOR_WHITE, COLOR_BLUE );	/* establece los colores */
		
		} /* fin de if colores */
		
		else {
		
		   endwin();
		   puts( "¡No tienes soporte para usar colores!" );
		   return 0;
		
		} /* fin de else */
		

		
		aux = M[mundo].LC;
		suelo = malloc(M[mundo].col * sizeof(int));

	   imprime(aux, win, M[mundo].ren, M[mundo].col, suelo, &monedas, y, &vidas, &Portales, mundo); 
		pantallaInicio();
		getch();

		Salta = 0; 
      dt = 0.2; //cantidad del incremento del tiempo en cada iteración.
      g = 9.8;  //Constante de la gravedad.
      vo = 10;  //Velocidad inicial.
		
		halfdelay(1);
 

		do 
		{
		   key = wgetch(win);
		  
		   if (key == ' ' && !Salta)
        	{
            Salta = 1;
            t = 0.;
            y = suelo[51];
        	}
        	if (Salta)
        	 {
            y = suelo[51]-(vo*t - 0.5*g*t*t);
            t =t + dt;
            if (y > suelo[51])
             {
                Salta = 0;
                y = suelo[51];
					 
             }
        	 }

			if( key == KEY_RIGHT )
		    { 
				if(y <= suelo[52])
				aux = aux->sig;
				
		    }
		   else if( key == KEY_LEFT )
		     {
				if(y <= suelo[50])
				aux = aux->ant;
				
			  }

	   	imprime(aux, win, M[mundo].ren, M[mundo].col, suelo, &monedas, y, &vidas, &Portales, mundo); 
		
			if(!Salta && y < suelo[51])
				y = y+2;
			if(y > suelo[51])
				y = suelo[51];
	
		   personaje(y-1);

			if(Portales == 1)
			{
			mundo = M[mundo].next;
			aux = M[mundo].LC;
			Portales = 0;
			y = 0;	
			}
	 	
		  snprintf(buffer, 63, "y = %06.3f", y);
        wmove(win, 2, 5);
        waddstr (win, buffer);

	
		} while( key != KEY_F(2) && vidas > 0 && monedas <= 100);
		
		pantallaFinal(vidas, monedas);
		cbreak();
 		getch();
		refresh();
		nocbreak();
		endwin();
   return 0;
}
