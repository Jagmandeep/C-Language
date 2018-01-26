#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#define M_PI 3.14159265358979

/*
STRUCTURES
*/

typedef struct {
	float r, g, b;
} colour_t;

typedef struct {
	double x;
	double y;
	double dir;
} turtle_t;

typedef struct {
	colour_t colour ;
	int down;
	int filled;
} pen_t; 

/*
PROTOTYPES
*/

void turtle_reset( turtle_t *t);
void pen_reset( pen_t *p );
int  process_comands( turtle_t *t, pen_t *p );
int  valid_colour(colour_t c);
void set_ps_header( int w, int h );
void set_ps_display( void );
void pen_set_colour( pen_t *p, colour_t c );
void turtle_goto( turtle_t *t, float x, float y );
void turtle_square( turtle_t *t, int size );
void turtle_turn( turtle_t *t, float angle );
void turtle_walk( turtle_t *t, int d );
void turtle_row( turtle_t *t, int count, int size );
void turtle_polygon( turtle_t *t,pen_t *p, int count, int size );
void pen_set_fill(pen_t *p);
void ps_stroke();
void turtle_grid( turtle_t *t, int rows, int columns, int size);
void turtle_random_walk( turtle_t *t, pen_t *p, int steps );
int  roll_dice( int min, int max );
void turtle_fractal( turtle_t *t, pen_t *p, colour_t c, int length, int depth );

int main( void ) {

	turtle_t boo;
	pen_t pen;
	
	srand(time(NULL));	
	
	turtle_reset( &boo );
	pen_reset( &pen );
	
	set_ps_header( 595, 841 );
	process_comands( &boo, &pen );
	set_ps_display();

	return 0;
}
/*
FUNCTIONS
*/

void turtle_reset( turtle_t *t ){
	t->x = t->y = 0.0;
	t->dir = 0.0;
	return;
}
void pen_reset( pen_t *p ){
	p->down = p->filled = 0;
	p->colour.r = 0.0;
	p->colour.g = 0.0;
	p->colour.b = 0.0;
	return;
}
int process_comands( turtle_t *t, pen_t *p )	{
	char cmd;
	colour_t c;
	float x, y, a;
	int d, s, i, j;
	while (( fscanf( stdin, "%c", &cmd )) != EOF ) 
	{
		switch ( cmd ) 
		{
			case 'C':
			fscanf( stdin, "%f %f %f\n", &c.r, &c.g, &c.b );
			if (valid_colour(c)==1)
				{
					pen_set_colour( p, c );
				}
			
				
			break;

			case 'G':
			fscanf( stdin, "%f %f\n", &x, &y );
			turtle_goto( t, x, y );			
			break;
			
			case 'F':
			pen_set_fill( p);
			break;
			
			case 'W':
			fscanf( stdin, "%d\n", &d );			
			turtle_walk( t, d );
			
			break;

			case 'T':
			fscanf( stdin, "%f", &a );
			turtle_turn( t, a );
			break;

			case 'S':
			fscanf( stdin, "%d", &s );
			turtle_square( t, s);
			break;

			case 'P':
			fscanf( stdin, "%d %d ", &i, &s );
			turtle_polygon(t, p, i, s );			
			ps_stroke();	
			break;
	
			case 'R':
			fscanf( stdin, "%d %d", &i, &s );
			turtle_row(t, i, s );
			break;
	
			case 'g':
		        fscanf( stdin, "%d %d %d", &i, &j, &s );
			turtle_grid(t, i, j, s);
			break;
	
			case 'r':
			fscanf( stdin, "%d", &i);
			turtle_random_walk(t, p, i);		
			break;
		
			case 'X':
			fscanf( stdin, "%d %d", &i, &j );
			turtle_fractal(t,p,c, i, j);
			break;
			
			default:
			break;		
		}
	}
return 0;
}

int valid_colour( colour_t c ){
	if( (c.r<1&&c.r>0) && (c.g<1&&c.g>0) && (c.b>0&&c.b<1) )
	{
		return 1;
	}
	return 0;
}

void set_ps_header( int w, int h )	{
	fprintf( stdout, "%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf( stdout, "%%%%BoundingBox: 0 0 %d %d\n\n",w ,h);
	return;
}
void set_ps_display( ){
	fprintf( stdout, "\n stroke \nshowpage\n");
}
void pen_set_colour( pen_t *p, colour_t c )	{
	p->colour.r = c.r;
	p->colour.g = c.g;
	p->colour.b = c.b;
	fprintf( stdout, "%.2f %.2f %.2f setrgbcolor\n", c.r, c.g, c.b);	
	return;
}
void turtle_goto( turtle_t *t, float x, float y )	{
	t->x = x;
	t->y = y;

	fprintf( stdout, "%f %f moveto\n", x, y);
}
void turtle_square( turtle_t *t, int size )	{

    float x2 = t->x-(size/2);
    float y2 = t->y-(size/2);
    fprintf(stdout,"%f %f %d %d ",x2,y2,size,size);
    fprintf(stdout,"rectfill\n\n" );

}
void turtle_turn( turtle_t *t, float angle )	{
	t->dir += angle;
}
void turtle_walk( turtle_t *t, int d )	{
	double x2,y2;
	x2 = t->x  + d * cos(t->dir * M_PI/180);
	y2 = t->y  + d * sin(t->dir * M_PI/180);
	fprintf(stdout, "%f %f lineto\n", x2, y2);
	t->x = x2;
	t->y = y2;
}

void turtle_row( turtle_t *t, int count, int size )	{
	int i;	
	for (i=0; i<count ; i++)
	{
		turtle_square( t, size);
		t->x +=  size * 1.5;
	}

}

void turtle_polygon( turtle_t *t,pen_t *p, int count, int size )
{
	int i;	
	for (i=0; i<count ; i++)
	{
		turtle_walk( t, size );
		turtle_turn( t, 360/count );
	}

	fprintf(stdout, "closepath\n");
	if(p->filled==1){
		fprintf(stdout,"fill\n" );
	}
	

}

void pen_set_fill(pen_t *p){
	if (p->filled == 0) {
		p->filled=1;		
	}
	else if (p->filled == 1){
		 p->filled=0;
	}
}

void ps_stroke(){	

	fprintf(stdout,"\nstroke\n" );
	
}

void turtle_grid( turtle_t *t, int rows, int columns, int size){
	int i;
	for (i=0; i<columns ; i++)
	{
		turtle_row( t, rows, size );
		t->x -= rows * size * 1.5;
		t->y +=  size * 1.5;		
	}
	
}

void turtle_random_walk( turtle_t *t, pen_t *p, int steps ){
	colour_t c;
	int i;
	int rand;
	c.r = c.g = c.b = 0.1;
	pen_set_colour(p,c);
	for (i=0; i<steps ; i++)
	{
		int cmd = roll_dice(1,6);
		switch(cmd)
		{
			case 1:
				fprintf(stdout,"newpath\n" );
				turtle_goto(t, t->x, t->y);
				turtle_walk(t, 10);
				ps_stroke();
				break;
			case 2:
				turtle_turn(t,-90);
				break;
			case 3:
				turtle_turn(t,90);
				break;
			case 4:
				rand = roll_dice(1,2);
				if (rand == 1 && c.g < 1)
				{
					c.g = c.g + 0.2;
					pen_set_colour(p, c);
				}
				else if (rand == 1 && c.g > 0)
				{
					c.g = c.g - 0.2;
					pen_set_colour(p, c);
				}
				break;
			case 5:
				rand = roll_dice(1,2);
				if (rand == 1 && c.g < 1)
				{
					c.b = c.b + 0.2;
					pen_set_colour(p, c);
				}
				else if (rand == 1 && c.g > 0)
				{
					c.b = c.b - 0.2;
					pen_set_colour(p, c);
				}
				break;
			case 6:
				rand = roll_dice(1,2);
				if (rand == 1 && c.g < 1)
				{
					c.r = c.r + 0.2;
					pen_set_colour(p, c);
				}
				else if (rand == 1 && c.g > 0)
				{
					c.r = c.r - 0.2;
					pen_set_colour(p, c);
				}
				break;
			default:
				break;
		}
	}
}

int  roll_dice( int min, int max ){
	
	return min+( rand() % max );

}
void turtle_fractal( turtle_t *t, pen_t *p, colour_t c,int length, int depth ) {

	if (depth == 0)
		turtle_walk(t, length);
	else {
		turtle_fractal( t,p,c, length/2, depth-1 );
		turtle_walk( t, length );
		turtle_turn(t, 60);
		c.g = 0.10;
		c.r = 0.85;
		c.b = 0.10;
		pen_set_colour(p, c);
		turtle_walk( t, length );
		turtle_fractal( t,p,c, length/2, depth-1 );
		turtle_turn(t, -120);
		c.g = 0.85;
		c.r = 0.10;
		c.b = 0.10;
		pen_set_colour(p, c);
		turtle_walk( t, length );
		turtle_fractal( t,p,c, length/2, depth-1 );
		turtle_turn(t, 60);
		c.g = 0.10;
		c.r = 0.10;
		c.b = 0.85;
		pen_set_colour(p, c);
		turtle_walk( t, length );
		turtle_fractal( t,p,c, length/2, depth-1 );
		turtle_turn(t, 60);
		c.g = 0.80;
		c.r = 0.85;
		c.b = 0.10;
		pen_set_colour(p, c);
		turtle_walk( t, length );
		turtle_fractal( t,p,c, length/2, depth-1 );
	}

}

