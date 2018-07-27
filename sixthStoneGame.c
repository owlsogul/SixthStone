#include "sixthStone.h"

int main()	{
	char plate[PLATE_MAX][PLATE_MAX];
	int turn = WHITE;
	int i;
	cord2D nextPut[2], before[2];
	cord2D lenCord;

	nextPut[0].x = -1;	lenCord.x = PLATE_MAX;
	nextPut[0].y = -1;	lenCord.y = PLATE_MAX;
	nextPut[1].x = -1;
	nextPut[1].y = -1;
	initPlate(plate);
		
	do {
		changeTurn(&turn);
		display(plate, lenCord);
		if(turn == WHITE)	{
			sixthStoneBot(plate, lenCord, nextPut, before, turn);
		}
		else {
			for(i = 0; i < 2; i++)	{
				scanf(" %d %d", &nextPut[i].x, &nextPut[i].y);
				while(canPut(plate, lenCord, nextPut[i], turn) == NO)	{
					printf("%c[1;%dm", 27, 31);
					printf("You can`t put there.\n");
					printf("%c[0m",27);
					scanf(" %d %d", &nextPut[i].x, &nextPut[i].y);
				}
				put(plate, nextPut[i], turn);
				display(plate, lenCord);
			}
		}
	}	while(whoWin(plate, lenCord, nextPut, turn) == NO);
	if(turn == WHITE) printf("White Win!\n");
	else printf("Black Win!\n");

	return 0;
}
