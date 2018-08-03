#include "sixthStone.h"

void setCandidate(char plate[][PLATE_MAX], cord2D *cord, int turn)	{
	// Check where can turn`th player put stone.
	int candidateWeight[PLATE_MAX][PLATE_MAX] = {{0,}};
	int i, candidateNum = 0;
	int maxWeight = -1;
	int dir;

	for (i = 0; i < 4; i++) {
		if (i < 2) {
			dir = getHighestWeightDirection(plate, *cord, turn);
			findEmptyCordInDirection(plate, cord, dir, turn);
		}
	}
}

void findEmptyCordInDirection(char plate[][PLATE_MAX], cord2D *temp, int dir, int turn) {
	//find the empty Coordination in this direction...
	int i = 0;
	switch (dir) {
	case EAST:	// Y++
		if (!isOutOfPlate(*temp, 6, EAST)) {
			while (plate[temp->x][temp->y + i] == turn) {
				i++;
			}
			temp->y = temp->y + i;
		}
		break;
	case WEST:	// Y--
		if (!isOutOfPlate(*temp, 6, WEST)) {
			while (plate[temp->x][temp->y - i] == turn) {
				i++;
			}
			temp->y = temp->y - i;
		}
		break;
	case SOUTH:	// X++
		if (!isOutOfPlate(*temp, 6, SOUTH)) {
			while (plate[temp->x + i][temp->y] == turn) {
				i++;
			}
			temp->x = temp->x + i;
		}
		break;
	case NORTH:	// X--
		if (!isOutOfPlate(*temp, 6, SOUTH)) {
			while (plate[temp->x - i][temp->y] == turn) {
				i++;
			}
			temp->x = temp->x - i;
		}
		break;

	case EAST_SOUTH:	// X++ Y++
		if (!isOutOfPlate(*temp, 6, EAST_SOUTH)) {
			while (plate[temp->x + i][temp->y + i] == turn) {
				i++;
			}
			temp->x = temp->x + i;
			temp->y = temp->y + i;
		}
		break;
	case EAST_NORTH:	// X-- Y++
		if (!isOutOfPlate(*temp, 6, SOUTH)) {
			while (plate[temp->x - i][temp->y + i] == turn) {
				i++;
			}
			temp->x = temp->x - i;
			temp->y = temp->y + i;
		}
		break;
	case WEST_SOUTH:	// X++ Y--
		if (!isOutOfPlate(*temp, 6, SOUTH)) {
			while (plate[temp->x + i][temp->y - i] == turn) {
				i++;
			}
			temp->x = temp->x + i;
			temp->y = temp->y - i;
		}
		break;
	case WEST_NORTH:	// X-- Y-- 
		if (!isOutOfPlate(*temp, 6, SOUTH)) {
			while (plate[temp->x - i][temp->y - i] == turn) {
				i++;
			}
			temp->x = temp->x - i;
			temp->y = temp->y - i;
		}
		break;
	}
	if (i > 5) {
		printf("findEmptyCordInDirectionError!\n");
	}
}

int getCandWeight(char plate[][PLATE_MAX], cord2D temp, int turn)	{
	int weight = 0;
	int w, b, i, dir;
	w = 0; b = 0;

	if(!isOutOfPlate(temp, 2, EAST))	{
		if(plate[temp.x][temp.y + 1] == WHITE) w++;
		else if(plate[temp.x][temp.y + 1] == BLACK) b++;
	}
	if(!isOutOfPlate(temp, 2, WEST))	{
		if(plate[temp.x][temp.y - 1] == WHITE) w++;
		else if(plate[temp.x][temp.y - 1] == BLACK) b++;
	}
	if(!isOutOfPlate(temp, 2, SOUTH))	{
		if(plate[temp.x + 1][temp.y] == WHITE) w++;
		else if(plate[temp.x + 1][temp.y] == BLACK) b++;
	}
	if(!isOutOfPlate(temp, 2, NORTH))	{
		if(plate[temp.x - 1][temp.y] == WHITE) w++;
		else if(plate[temp.x - 1][temp.y] == BLACK) b++;
	}

	if(!isOutOfPlate(temp, 2, EAST_SOUTH))	{
		if(plate[temp.x + 1][temp.y] + 1 == WHITE) w++;
		else if(plate[temp.x + 1][temp.y + 1] == BLACK) b++;
	}
	if(!isOutOfPlate(temp, 2, EAST_NORTH))	{
		if(plate[temp.x - 1][temp.y + 1] == WHITE) w++;
		else if(plate[temp.x - 1][temp.y + 1] == BLACK) b++;
	}
	if(!isOutOfPlate(temp, 2, WEST_SOUTH))	{
		if(plate[temp.x + 1][temp.y - 1] == WHITE) w++;
		else if(plate[temp.x + 1][temp.y - 1] == BLACK) b++;
	}
	if(!isOutOfPlate(temp, 2, WEST_NORTH))	{
		if(plate[temp.x - 1][temp.y - 1] == WHITE) w++;
		else if(plate[temp.x - 1][temp.y - 1] == BLACK) b++;
	}

	if(turn == WHITE)	{
		for(i = 1; i <= w; i++)	{
			weight += i;
		}
		for(i = 1; i <= b; i++)	{
			weight -= i;
		}
		for (dir = 1; dir <= 8; dir++) {
			if (isWinState(plate, temp, WHITE, dir, 3) == YES)		weight += 6;
			else if (isWinState(plate, temp, WHITE, dir, 2) == YES)	weight += 3;
			else if (isWinState(plate, temp, WHITE, dir, 1) == YES)	weight += 1;
		}
		for (dir = 1; dir <= 8; dir++) {
			if (isWinState(plate, temp, BLACK, dir, 3) == YES)		weight -= 6;
			else if (isWinState(plate, temp, BLACK, dir, 2) == YES)	weight -= 3;
			else if (isWinState(plate, temp, BLACK, dir, 1) == YES)	weight -= 1;
		}
	}
	else if(turn == BLACK)	{
		for(i = 1; i <= w; i++)	{
			weight -= i;
		}
		for(i = 1; i <= b; i++)	{
			weight += i;
		}
		for (dir = 1; dir <= 8; dir++) {
			if (isWinState(plate, temp, WHITE, dir, 3) == YES)		weight -= 6;
			else if (isWinState(plate, temp, WHITE, dir, 2) == YES)	weight -= 3;
			else if (isWinState(plate, temp, WHITE, dir, 1) == YES)	weight -= 1;
		}
		for (dir = 1; dir <= 8; dir++) {
			if (isWinState(plate, temp, BLACK, dir, 3) == YES)		weight += 6;
			else if (isWinState(plate, temp, BLACK, dir, 2) == YES)	weight += 3;
			else if (isWinState(plate, temp, BLACK, dir, 1) == YES)	weight += 1;
		}
	}
	return weight;
}

int getWinState(char plate[][PLATE_MAX], cord2D cord, int turn)	{
	// Find is plate have win state. If exist, return dir. Else, return "NO";
	int i, j, k, dir = NO;
	cord2D temp;

	for (i = 0; i < PLATE_MAX; i++) {
		for (j = 0; j < PLATE_MAX; j++) {
			for (k = 1; k <= 8; k++) {
				temp.x = i;	temp.y = j;
				if (isWinState(plate, cord, turn, k, 4) == YES || isWinState(plate, cord, turn, k, 5) == YES) {
					memcpy(&cord, &temp, sizeof(cord2D));
					return k;
				}
			}
		}
	}

	/*
	// TODO: Need to check 8 / 7 stone including last doing stone location.
	for (int i = 0; i < MEMORIZED_SIZE / 2; i++) {
		for (k = 1; k <= 8; k++) {
			if (isWinState(plate, cord, turn, k, 4) == YES || isWinState(plate, cord, turn, k, 5) == YES) {
				return k;
			}
		}
	}
	*/
	return dir;
}

int isWinState(char plate[][PLATE_MAX], cord2D cord, int turn, int dir, int continum) {
	// Does start form plate[cord.x][cord.y] to + 8 to "dir" direction is win state?
	int i, count = 0;
	if (!isOutOfPlate(cord, 8, dir)) {
		switch (dir) {
		case EAST:	// Y++
			if (plate[cord.x][cord.y + 7] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 1; i <= 6; i++) {
					if (plate[cord.x][cord.y + i] == turn) count++;
					else if (plate[cord.x][cord.y + i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case WEST:	// Y--
			if (plate[cord.x][cord.y - 7] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 1; i <= 6; i++) {
					if (plate[cord.x][cord.y - i] == turn) count++;
					else if (plate[cord.x][cord.y - i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case SOUTH:	// X++
			if (plate[cord.x + 7][cord.y] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 1; i <= 6; i++) {
					if (plate[cord.x + i][cord.y] == turn) count++;
					else if (plate[cord.x + i][cord.y] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case NORTH:	// X--
			if (plate[cord.x - 7][cord.y] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 1; i <= 6; i++) {
					if (plate[cord.x - i][cord.y] == turn) count++;
					else if (plate[cord.x - i][cord.y] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;

		case EAST_SOUTH:	// X++ Y++
			if (plate[cord.x + 7][cord.y + 7] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 1; i <= 6; i++) {
					if (plate[cord.x + i][cord.y + i] == turn) count++;
					else if (plate[cord.x + i][cord.y + i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case EAST_NORTH:	// X-- Y++
			if (plate[cord.x - 7][cord.y + 7] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 1; i <= 6; i++) {
					if (plate[cord.x - i][cord.y + i] == turn) count++;
					else if (plate[cord.x - i][cord.y + i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case WEST_SOUTH:	// X++ Y--
			if (plate[cord.x + 7][cord.y - 7] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 1; i <= 6; i++) {
					if (plate[cord.x + i][cord.y - i] == turn) count++;
					else if (plate[cord.x + i][cord.y - i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case WEST_NORTH:	// X-- Y--
			if (plate[cord.x - 7][cord.y - 7] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 1; i <= 6; i++) {
					if (plate[cord.x - i][cord.y - i] == turn) count++;
					else if (plate[cord.x - i][cord.y - i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		default:
			break;
		}
		return NO;
	}
	else if (!isOutOfPlate(cord, 7, dir)) {
		switch (dir) {
		case EAST:	// Y++
			if (plate[cord.x][cord.y + 6] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 0; i < 6; i++) {
					if (plate[cord.x][cord.y + i] == turn) count++;
					else if (plate[cord.x][cord.y + i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case WEST:	// Y--
			if (plate[cord.x][cord.y - 6] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 0; i < 6; i++) {
					if (plate[cord.x][cord.y - i] == turn) count++;
					else if (plate[cord.x][cord.y - i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case SOUTH:	// X++
			if (plate[cord.x + 6][cord.y] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 0; i < 6; i++) {
					if (plate[cord.x + i][cord.y] == turn) count++;
					else if (plate[cord.x + i][cord.y] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case NORTH:	// X--
			if (plate[cord.x - 6][cord.y] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 0; i < 6; i++) {
					if (plate[cord.x - i][cord.y] == turn) count++;
					else if (plate[cord.x - i][cord.y] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;

		case EAST_SOUTH:	// Y++ X++
			if (plate[cord.x + 6][cord.y + 6] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 0; i < 6; i++) {
					if (plate[cord.x + i][cord.y + i] == turn) count++;
					else if (plate[cord.x + i][cord.y + i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case EAST_NORTH:	// Y++ X--
			if (plate[cord.x - 6][cord.y] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 0; i < 6; i++) {
					if (plate[cord.x - i][cord.y] == turn) count++;
					else if (plate[cord.x - i][cord.y] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case WEST_SOUTH:	// Y-- X++
			if (plate[cord.x + 6][cord.y - 6] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 0; i < 6; i++) {
					if (plate[cord.x + i][cord.y - i] == turn) count++;
					else if (plate[cord.x + i][cord.y - i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		case WEST_NORTH:	//Y-- X--
			if (plate[cord.x - 6][cord.y - 6] != turn) {
				// if 4 or 5 turn`th stone exist, return true.
				for (i = 0; i < 6; i++) {
					if (plate[cord.x - i][cord.y - i] == turn) count++;
					else if (plate[cord.x - i][cord.y - i] != EMPTY) {
						count = 0;
						break;
					}
				}
				return count == continum ? YES : NO;
			}
			break;
		default:
			break;
		}
	}
	else {
		return NO;
	}
	return NO;
}

int getHighestWeightDirection(char plate[][PLATE_MAX], cord2D cord, int turn) {
	int k;
	int maxWeight = 0, result = 1;

	for (k = 1; k <= 8; k++) {
		if (isWinState(plate, cord, turn, k, 5) == YES) {
			return k;
		}
		else if (isWinState(plate, cord, turn, k, 4) == YES) {
			return k;
		}
		else if (isWinState(plate, cord, turn, k, 3) == YES) {
			if (3 > maxWeight) {
				maxWeight = 3;
				result = k;
			}
		}
		else if (isWinState(plate, cord, turn, k, 2) == YES) {
			if (2 > maxWeight) {
				maxWeight = 2;
				result = k;
			}
		}
		else if (isWinState(plate, cord, turn, k, 1) == YES) {
			if (1 > maxWeight) {
				maxWeight = 1;
				result = k;
			}
		}
	}

	return result;
}

int getHighestWeight(char plate[][PLATE_MAX], cord2D cord, int turn) {
	int k;
	int maxWeight = 0;

	for (k = 1; k <= 8; k++) {
		if (isWinState(plate, cord, turn, k, 5) == YES) {
			return 5;
		}
		else if (isWinState(plate, cord, turn, k, 4) == YES) {
			return 4;
		}
		else if (isWinState(plate, cord, turn, k, 3) == YES) {
			if (3 > maxWeight) {
				maxWeight = 3;
			}
		}
		else if (isWinState(plate, cord, turn, k, 2) == YES) {
			if (2 > maxWeight) {
				maxWeight = 2;
			}
		}
		else if (isWinState(plate, cord, turn, k, 1) == YES) {
			if (1 > maxWeight) {
				maxWeight = 1;
			}
		}
	}

	return maxWeight;
}

int getState(char plate[][PLATE_MAX], cord2D cord, int turn, int dir)	{
	int val = -1;
	/* Stone can be WHITE. BLACK, EMPTY, BLOCK <=> BLACK, WHITE
	* if XOOO___X == 2 score.	cause 3 continuos and 1 blocked.
	* if X__OO__X == 2 score.	cause 2 continuos and no blocked.
	* if XOO_____ == 1 score.	cause 2 continuos and 1 blocked.
	* if XOOX____ == 0 score.	cause 2 continuos but all blocked.
	* if XOOXOXOX == 0 score.	cause this have no-meaning. 
	*/
	if(isOutOfPlate(cord, 8, dir)) {
		return NO;
	}

	switch(dir)	{
		case EAST:	// Y++
			break;
		case WEST:	// Y--
			break;
		case SOUTH:	// X++
			break;
		case NORTH:	// X--
			break;

		case EAST_SOUTH:	// X++ Y++
			break;
		case EAST_NORTH:	// X-- Y++
			break;
		case WEST_SOUTH:	// X++ Y--
			break;
		case WEST_NORTH:	// X-- Y--
			break;
		
		default:
			break;
	}
}

void doWin(char plate[][PLATE_MAX], cord2D temp , int dir, cord2D *cord, int turn)	{
	// Start from plate[cord.x, cord.y], direction dir is winning state, so put nextX and nextY to finish game.
	int i, count = 0;

	switch (dir) {
		case EAST:	// Y++
			for (i = 1; i < 8; i++) {
				if (plate[temp.x][temp.y + i] == EMPTY) {
					cord[count].x = temp.x;
					cord[count].y = temp.y + i;
					count++;
				}
				if (count == 2) break;
			}
			break;
		case WEST:	// Y--
			for (i = 1; i < 8; i++) {
				if (plate[temp.x][temp.y - i] == EMPTY) {
					cord[count].x = temp.x;
					cord[count].y = temp.y - i;
					count++;
				}
				if (count == 2) break;
			}
			break;
		case SOUTH:	// X++
			for (i = 1; i < 8; i++) {
				if (plate[temp.x + i][temp.y] == EMPTY) {
					cord[count].x = temp.x + i;
					cord[count].y = temp.y;
					count++;
				}
				if (count == 2) break;
			}
			break;
		case NORTH: // X--
			for (i = 1; i < 8; i++) {
				if (plate[temp.x - i][temp.y] == EMPTY) {
					cord[count].x = temp.x - i;
					cord[count].y = temp.y;
					count++;
				}
				if (count == 2) break;
			}
			break;

		case EAST_SOUTH:	// X++ y++
			for (i = 1; i < 8; i++) {
				if (plate[temp.x + i][temp.y + i] == EMPTY) {
					cord[count].x = temp.x + i;
					cord[count].y = temp.y + i;
					count++;
				}
				if (count == 2) break;
			}
			break;
		case EAST_NORTH:	// X-- y++
			for (i = 1; i < 8; i++) {
				if (plate[temp.x - i][temp.y + i] == EMPTY) {
					cord[count].x = temp.x - i;
					cord[count].y = temp.y + i;
					count++;
				}
				if (count == 2) break;
			}
			break;
		case WEST_SOUTH:	// X++ y--
			for (i = 1; i < 8; i++) {
				if (plate[temp.x + i][temp.y - i] == EMPTY) {
					cord[count].x = temp.x + i;
					cord[count].y = temp.y - i;
					count++;
				}
				if (count == 2) break;
			}
			break;
		case WEST_NORTH:	// x-- y--
			for (i = 1; i < 8; i++) {
				if (plate[temp.x - i][temp.y - i] == EMPTY) {
					cord[count].x = temp.x - i;
					cord[count].y = temp.y - i;
					count++;
				}
				if (count == 2) break;
			}
			break;
		default:
			break;
	}
	if (cord[0].x == -1 || cord[1].x == -1) {
		printf("doWin_error\n");
	}
}

void doSheild(char plate[][PLATE_MAX], cord2D temp, int dir, cord2D *next, int turn) {
	// Start from plate[cord.x, cord.y], direction dir is winning state, so put nextX and nextY to finish game.
	int i, count = 0;
	// For processing ___OOOO_.
	int nonTurnIndex = 0;
	int oppo;

	oppo = turn == BLACK ? WHITE : BLACK;
	
	for (i = 0; i < 8; i++) {
		switch (dir) {
			case EAST:
				if (plate[temp.x][temp.y + i] != oppo && plate[temp.x][temp.y + i + 1] == oppo) {
					nonTurnIndex = i;
					break;
				}
				break;
			case WEST:
				if (plate[temp.x][temp.y - i] != oppo && plate[temp.x][temp.y - i - 1] == oppo) {
					nonTurnIndex = i;
					break;
				}
				break;
			case SOUTH:
				if (plate[temp.x + i][temp.y] != oppo && plate[temp.x + i + 1][temp.y] == oppo) {
					nonTurnIndex = i;
					break;
				}
				break;
			case NORTH:
				if (plate[temp.x - i][temp.y] != oppo && plate[temp.x - i - 1][temp.y] == oppo) {
					nonTurnIndex = i;
					break;
				}
				break;

			case EAST_SOUTH:
				if (plate[temp.x + i][temp.y + i] != oppo && plate[temp.x + i + 1][temp.y + i + 1] == oppo) {
					nonTurnIndex = i;
					break;
				}
				break;
			case EAST_NORTH:
				if (plate[temp.x - i][temp.y + i] != oppo && plate[temp.x - i - 1][temp.y + i + 1] == oppo) {
					nonTurnIndex = i;
					break;
				}
				break;
			case WEST_SOUTH:
				if (plate[temp.x + i][temp.y - i] != oppo && plate[temp.x + i + 1][temp.y - i - 1] == oppo) {
					nonTurnIndex = i;
					break;
				}
				break;
			case WEST_NORTH:
				if (plate[temp.x - i][temp.y - i] != oppo && plate[temp.x - i - 1][temp.y - i - 1] == oppo) {
					nonTurnIndex = i;
					break;
				}
				break;
			default:
				break;
		}
	}
	switch (dir) {
	case EAST:
		if (plate[temp.x][temp.y + nonTurnIndex] == EMPTY) {
			next[count].x = temp.x;
			next[count].y = temp.y + nonTurnIndex;
			count++;
		}
		break;
	case WEST:
		if (plate[temp.x][temp.y - nonTurnIndex] == EMPTY) {
			next[count].x = temp.x;
			next[count].y = temp.y - nonTurnIndex;
			count++;
		}
		break;
	case SOUTH:
		if (plate[temp.x + nonTurnIndex][temp.y] == EMPTY) {
			next[count].x = temp.x + nonTurnIndex;
			next[count].y = temp.y;
			count++;
		}
		break;
	case NORTH:
		if (plate[temp.x - nonTurnIndex][temp.y] == EMPTY) {
			next[count].x = temp.x - nonTurnIndex;
			next[count].y = temp.y;
			count++;
		}
		break;

	case EAST_SOUTH:
		if (plate[temp.x + nonTurnIndex][temp.y + nonTurnIndex] == EMPTY) {
			next[count].x = temp.x + nonTurnIndex;
			next[count].y = temp.y + nonTurnIndex;
			count++;
		}
		break;
	case EAST_NORTH:
		if (plate[temp.x - nonTurnIndex][temp.y + nonTurnIndex] == EMPTY) {
			next[count].x = temp.x - nonTurnIndex;
			next[count].y = temp.y + nonTurnIndex;
			count++;
		}
		break;
	case WEST_SOUTH:
		if (plate[temp.x + nonTurnIndex][temp.y - nonTurnIndex] == EMPTY) {
			next[count].x = temp.x - nonTurnIndex;
			next[count].y = temp.y - nonTurnIndex;
			count++;
		}
		break;
	case WEST_NORTH:
		if (plate[temp.x - nonTurnIndex][temp.y - nonTurnIndex] == EMPTY) {
			next[count].x = temp.x - nonTurnIndex;
			next[count].y = temp.y - nonTurnIndex;
			count++;
		}
		break;
	default:
		break;
	}

	switch (dir) {
		case EAST:	// Y++
			for (i = nonTurnIndex + 1; i < 8; i++) {
				if (plate[temp.x][temp.y + i] == EMPTY) {
					next[count].x = temp.x;
					next[count].y = temp.y + i;
					break;
				}
			}
			break;
		case WEST:	// Y--
			for (i = nonTurnIndex + 1; i < 8; i++) {
				if (plate[temp.x][temp.y - i] == EMPTY) {
					next[count].x = temp.x;
					next[count].y = temp.y - i;
					break;
				}
			}
			break;
		case SOUTH:	// X++
			for (i = nonTurnIndex + 1; i < 8; i++) {
				if (plate[temp.x + i][temp.y] == EMPTY) {
					next[count].x = temp.x + i;
					next[count].y = temp.y;
					break;
				}
			}
			break;
		case NORTH: // X--
			for (i = nonTurnIndex + 1; i < 8; i++) {
				if (plate[temp.x - i][temp.y] == EMPTY) {
					next[count].x = temp.x - i;
					next[count].y = temp.y;
					break;
				}
			}
			break;

		case EAST_SOUTH:	// X++ y++
			for (i = nonTurnIndex + 1; i < 8; i++) {
				if (plate[temp.x + i][temp.y + i] == EMPTY) {
					next[count].x = temp.x + i;
					next[count].y = temp.y + i;
					break;
				}
			}
			break;
		case EAST_NORTH:	// X-- y++
			for (i = nonTurnIndex + 1; i < 8; i++) {
				if (plate[temp.x - i][temp.y + i] == EMPTY) {
					next[count].x = temp.x - i;
					next[count].y = temp.y + i;
					break;
				}
			}
			break;
		case WEST_SOUTH:	// X++ y--
			for (i = nonTurnIndex + 1; i < 8; i++) {
				if (plate[temp.x + i][temp.y - i] == EMPTY) {
					next[count].x = temp.x + i;
					next[count].y = temp.y - i;
					break;
				}
			}
			break;
		case WEST_NORTH:	// x-- y--
			for (i = nonTurnIndex + 1; i < 8; i++) {
				if (plate[temp.x - i][temp.y - i] == EMPTY) {
					next[count].x = temp.x - i;
					next[count].y = temp.y - i;
					break;
				}
			}
			break;
		default:
			break;
	}

	if (next[0].x == -1 || next[1].x == -1) {
		printf("doSheild_error\n");
	}
}

void sixStoneBot(char plate[][PLATE_MAX], memorizedCord2D *memorizedCord, int turn) {
	// Main AI. Return at next[2].
	// Make candidate proper number ( 50 );
	// memorizedCord mine = my stone location. oppo = other`s stone location.
	cord2D oppoCandCord[PLATE_MAX * PLATE_MAX], myCandCord[PLATE_MAX * PLATE_MAX];
	cord2D cord = { 0, 0 };
	char tempPlate[PLATE_MAX][PLATE_MAX], mPlate[PLATE_MAX][PLATE_MAX], oPlate[PLATE_MAX][PLATE_MAX];
	int oppoCandNum = 0;
	int myCandNum = 0;
	int highestWeight = 0, weight = 0, highestMem = 0;
	int i, oppo, oppoWeight, myWeight, index[2], loseDir, count = 0;

	// turn mean my color, oppo mean other`s color.
	oppo = turn == BLACK ? WHITE : BLACK;

	index[0] = 0;	index[1] = 0;
	
	// Change "C" into turn`s stone.
	// mPlate mean myPlate.
	changeBlocking(plate, mPlate, turn); 

	// oPlate mean oppoPlate
	changeBlocking(plate, oPlate, oppo);
	
	memset(memorizedCord->mine, -1, sizeof(cord2D) * 2);
	if ((loseDir = getWinState(mPlate, cord, turn)) != NO)	{
		// In case AI can win.
		printf("Winning State was found at (%d, %d) with dir %d.\n", cord.x, cord.y, loseDir);
		system("pause");
		doWin(plate, cord, loseDir, memorizedCord->mine, turn);
	}
	else if ((loseDir = getWinState(oPlate, cord, oppo)) != NO) {
		// In case AI can lose.
		printf("Winning State was found at (%d, %d) with dir %d.\n", cord.x, cord.y, loseDir);
		system("pause");
		doSheild(plate, cord, loseDir, memorizedCord->mine, turn);
	}

	// Judge what have to do next.
	if (memorizedCord->mine[0].x == -1 && memorizedCord->mine[1].x == -1) {
		// if 2 cordinate is empty,

	}
	else if ((memorizedCord->mine[0].x != -1 && memorizedCord->mine[1].x == -1) || (memorizedCord->mine[0].x == -1 && memorizedCord->mine[1].x != -1)) {
		// if 1 cordinate is empty,
	}
	else {
		// if cordinate is not empty,
		// Do nothing.
	}
	
	
	/*
	//Search in case we can win.
	for (i = 0; i < 2; i++) {
		highestMem = -1;
		highestWeight = 0;

		for (int mem = 0; mem < MEMORIZED_SIZE; mem++) {
			cord = mem < 2 ? memorizedCord->mine[mem] : memorizedCord->opposite[mem - 2];
			if (cord.x == -1 || cord.y == -1) {
				// Set mine to opposite. ( AI`s turn start. )
				memorizedCord->mine[i].x = memorizedCord->opposite[i].x + 1;
				memorizedCord->mine[i].y = memorizedCord->opposite[i].y + 1;
			}
			// Find win state -> Find lose state -> Find next stone location.
			if ((loseDir = getWinState(mPlate, cord, turn)) != NO) {
				printf("Winning State was found at (%d, %d) with dir %d.\n", cord.x, cord.y, loseDir);
				system("pause");
				doWin(plate, cord, loseDir, &memorizedCord->mine[i], turn);
			}
			else {
				// Check oppo`s win state. ( 4 ~ 5 continuos state. )
				if ((loseDir = getWinState(oPlate, cord, oppo)) != NO) {
					printf("Losing State was found at (%d, %d) with dir %d.\n", cord.x, cord.y, loseDir);
					system("pause");
					doSheild(plate, cord, loseDir, &memorizedCord->mine[i], turn);
					break;
				}
				else {
					if (mem < 2) {
						weight = getHighestWeight(mPlate, cord, turn);
					}
					else {
						weight = getHighestWeight(oPlate, cord, oppo);
					}
					if (highestWeight < weight) {
						highestWeight = weight;
						highestMem = mem;
					}
				}
			}
		}
		switch (highestMem) {
		case -1:
			put(plate, memorizedCord->mine[i], turn);
			break;
		case 0:
			setCandidate(mPlate, &memorizedCord->mine[i], turn);
			put(plate, memorizedCord->mine[i], turn);
			break;
		case 1:
			setCandidate(mPlate, &memorizedCord->mine[i], turn);
			put(plate, memorizedCord->mine[i], turn);
			break;
		case 2:
			cord = memorizedCord->opposite[i];
			setCandidate(mPlate, &cord, oppo);
			memcpy(&memorizedCord->mine[i], &cord, sizeof(cord2D));
			put(plate, memorizedCord->mine[i], turn);
			break;
		case 3:
			cord = memorizedCord->opposite[i];
			setCandidate(mPlate, &cord, oppo);
			memcpy(&memorizedCord->mine[i], &cord, sizeof(cord2D));
			put(plate, memorizedCord->mine[i], turn);
			break;
			// TODO : check this plz
			// for (i = 0; i < oppoCandNum; i++) {
			// changeBlocking(plate, cPlate, turn);
			// memcpy(tempPlate, cPlate, sizeof(char) * PLATE_MAX * PLATE_MAX);
			// tempPlate[oppoCandCord[i].x][oppoCandCord[i].y] = turn;
			// myCandNum = getCandidate(tempPlate, lenCord, myCandCord, turn);
			// myWeight = getCandWeight(tempPlate, oppoCandCord[oppoCandNum - 1], turn);
			//	if (myWeight > highestWeight) index[1] = i;
			// }
			

		}
	}
	*/
}
