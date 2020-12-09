/*
 * project3.c
 *
 * Created: 2/13/20 12:22:30 PM
 * Author : cesar
 */ 

#include <avr/io.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "avr.h"
#include "lcd.h"



// int notes[] = {	220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 
// 				440, 466, 494, 523, 544, 587, 622, 659, 698, 740, 784, 831, 
// 				880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 
// 				1760};


char keypad[17] = {
	'1', '2', '3', 'A',
	'4', '5', '6', 'B',
	'7', '8', '9', 'C',
	'*', '0', '#', 'D'
};



int notes[] = {440, 466, 494, 523, 544, 587, 622, 659, 698, 740, 784, 831, 880};


	
struct Note  {
	int frequency;
	int duration;
};

struct Songs
{
	struct Note marry;
	struct Note happy;
};
//int FREQUENCY[] = {220, 233, 246, 261, 277, 293, 311, 329, 349, 369, 391, 415};
	
int SONG_LENGTH[] = {26, 25};
int SONG_POSITION = 0;
// 
// struct Songs
// {
// 	struct Note MARRY_HAD_A_LITTLE_LAMB[SONG_LENGTH[0]];
// 	struct Note HAPPY_BDAY[SONG_LENGTH[1]];
// };
	
struct Note MARRY_HAD_A_LITTLE_LAMB[] = { {5,1}, {3,1}, {1,1}, {3,1}, {5,1}, {5,1}, {5,0}, {3,1}, {3,1} , {3,0}, {5,1} , {8,1}, {8,0}, 
											{5,1}, {3,1}, {1,1}, {3,1}, {5,1}, {5,1}, {5,1}, {5, 1}, {3, 1}, {3, 1}, {5, 1}, {3, 1}, {1, 0} };
												
struct Note HAPPY_BDAY[] = {  {0, 2}, {0, 2}, {2, 1}, {0, 1}, {5, 1}, {4, 0}, {0, 2}, {0, 2}, {2, 1}, {0, 1}, {7, 1}, {5, 0}, 
								{0, 2}, {0, 2}, {12, 1}, {9, 1}, {5, 1}, {4, 1}, {2, 0}, {10, 2}, {10, 2}, {9, 1}, {5, 1}, {7,1}, {5, 0} };
									

struct Note* s[] = {&MARRY_HAD_A_LITTLE_LAMB, &HAPPY_BDAY};
												
struct Note FLIGHT_OF_THE_BUMBLEBEE[] = {  {36, 2}, {35, 2}, {34, 2}, {33, 2}, {34, 2}, {33, 2}, {32, 2}, {31, 2}, {32, 2}, {31, 2}, {30, 2}, {29, 2},
											{28, 2}, {27, 2}, {26, 2}, {25, 2}, {24, 2}, {23, 2}, {22, 2}, {21, 2}, {22, 2}, {21, 2}, {20, 2}, {19, 2},
											{20, 2}, {19, 2}, {18,2}, {17,2}, {16, 2}, {15,2}, {14, 2}, {13, 2}, {12, 2}, {11,2}, {10, 2}, {9, 2}, 
											{10, 2}, {9, 2}, {8,2}, {7, 2} };
												
struct Note check[] = {{36, 0}, {35, 0}, {34, 0}, {33, 0}, {32, 0}, {31, 0}, {30, 0}  };

int DURATION_MODIFIER[3] = {1,2,4};
int DURATION = 200;
int SONG_NOTE = 0;
float pitch = 1.0;
int tempo = 0;

int is_pressed(int r, int c)
{
	DDRC = 0x00;
	PORTC = 0x00;
	
	SET_BIT(DDRC, r);
	SET_BIT(PORTC, c + 4);
	avr_wait(1);
	
	if (GET_BIT(PINC,c + 4)) {
		return 0;
	}
	
	return 1;
}

int get_key(void)
{
	int r, c;
	for (r = 0; r < 4; ++r)
	{
		for(c = 0; c < 4; ++c)
		{
			if(is_pressed(r,c))
			return (r *4) + c + 1;
		}
	}
	return 0;
}

void t_on(void)
{
// 	DDRB = 0x08;
// 	PORTB = 0x08;
	SET_BIT(DDRB, 3);
	SET_BIT(PORTB, 3);
}

void t_off(void)
{
// 	DDRB = 0x00;
// 	PORTB = 0x00;
	CLR_BIT(DDRB, 3);
	CLR_BIT(PORTB, 3);
}

void play_note(int freq, int dur)
{
	//int half = freq / 2;
	int total_time = ceil(20000/freq);
	int half = total_time / 2;
	int duration = (dur * 80/ (total_time + tempo));
	

	//printf("%d", duration);
	for (int i = 0; i < duration; i++)
	{
		t_on();
		avr_wait(half);
		t_off();
		avr_wait(half);
	}
}

int main(void)
{
    /* Replace with your application code */
	//lcd_init();
	//lcd_clr();
	//SET_BIT(DDRB, 3);
	
	lcd_init();
	lcd_clr();
	char buf1[16];
	char buf2[16];

    while (1) 
    {
		//lcd_init();
		lcd_clr();
		
		if (SONG_POSITION == 0)
		{
			//char buf1[] = "MARY HAD A  100%";
			strcpy(buf1, "MARY HAD A  100%");
			//char buf2[] = "LITTLE LAMB";
			strcpy(buf2, "LITTLE LAMB");
		}
		if (SONG_POSITION == 1)
		{
			//char buf1[] = "HAPPY       100%";
			strcpy(buf1, "HAPPY       100%");
			//char buf2[] = "BIRTHDAY";
			strcpy(buf2, "BIRTHDAY");
		}
		
				
		if (keypad[get_key() - 1] == '2')
		{
			//lcd_init();
			lcd_clr();
			lcd_puts2("PAUSE");	
			while(1)
			{
				
				if (keypad[get_key() - 1] == '1')
				{
					lcd_clr();
					break;
				}
				if (keypad[get_key() - 1] == '3')
				{
					SONG_NOTE = 0;
					break;
				}
			}
		}
		if (keypad[get_key() - 1] == '3')
		{
			SONG_NOTE = 0;
		}
		
		if (keypad[get_key() - 1] == '7')
		{
			tempo += 30;
		}
		
		if (keypad[get_key() - 1] == '*')
		{
			if (tempo >= 30)
				tempo -= 30;
		}
		
		if (keypad[get_key() - 1] == '8')
		{
			if (pitch < 1.2)
			{
				pitch += .2;
			}
		}
		
		if (keypad[get_key() - 1] == '0')
		{
			if (pitch > .8)
			{
				pitch -= .2;
			}
		}
		if (keypad[get_key() - 1] == 'C')
		{
			if (SONG_POSITION == 0)
			{
				SONG_POSITION += 1;
				SONG_NOTE = 0;
			}
		}
		if (keypad[get_key() - 1] == 'D')
		{
			if (SONG_POSITION == 1)
			{
				SONG_POSITION -= 1;
				SONG_NOTE = 0;
			}
		}
		if (SONG_NOTE < SONG_LENGTH[SONG_POSITION])
		{
			lcd_puts2(buf1);
			lcd_pos(1, 0);
			lcd_puts2(buf2);
			//struct Note note = MARRY_HAD_A_LITTLE_LAMB[SONG_NOTE];
			struct Note note = s[SONG_POSITION][SONG_NOTE];
			//struct Note note = FLIGHT_OF_THE_BUMBLEBEE[SONG_NOTE];
			//struct Note note = check[SONG_NOTE];
			play_note(notes[note.frequency] * pitch, DURATION / DURATION_MODIFIER[note.duration]);
			SONG_NOTE ++;
			
		}


    }
}
