#include <stdio.h>
#include <assert.h>

typedef enum {
    C_LEFT = 4,
    C_DOWN = 5,
    C_RIGHT = 6,
    C_UP = 8,
    C_ERROR = 10,
} Command;

typedef struct {
    unsigned int xPos;
    unsigned int yPos;
} PacmanPosition;

PacmanPosition initPosition() {
    PacmanPosition position;
    position.xPos = 0;
    position.yPos = 0;
    return position;
}

int checkConstraints(PacmanPosition* position, Command command, unsigned int size) {
    if(command == C_UP && position->yPos == 0) return 0;
    if(command == C_LEFT && position->xPos == 0) return 0;
    if(command == C_RIGHT && position->xPos == size - 1) return 0;
    if(command == C_DOWN && position->yPos == size - 1) return 0;
    return 1;
}

Command getUserInput() {
    printf("Input your turn:\n");
    int i = 0;
    scanf("%d", &i);
    switch(i) {
        case 4: return C_LEFT;
        case 5: return C_DOWN;
        case 6: return C_RIGHT;
        case 7: return C_UP;
        default: return C_ERROR;
    }
}

void movePacman(PacmanPosition* position, Command command, unsigned int size) {
    if(checkConstraints(position, command, size)) {
        switch(command) {
            case C_LEFT: 
                position->xPos--;
                break;
            case C_RIGHT: 
                position->xPos++;
                break;
            case C_DOWN:
                position->yPos++;
                break;
            case C_UP:
                position->yPos--;
                break;
            case C_ERROR:
                printf("something went wrong");
                break;
        }
    }
}

void render(PacmanPosition* position, unsigned int score, unsigned int size) {
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j < size; j++) {
            if(i == position->yPos && j == position->xPos) printf("C ");
            else if(i == size - 1 && j == size - 1) printf("O");
            else printf(". ");
        }
        printf("\n");
    } 
    printf("Score - %u\n", score);
}

void loop(PacmanPosition* position, unsigned int size) {
    int score = 0;
    int winCondition = 1;
    render(position, score, size);
    while(winCondition) {
        Command command = getUserInput();
        if(command == C_ERROR) {
            printf("error\n");
            return;
        }
        score++;
        movePacman(position, command, size);
        if(position->yPos == size - 1 && position->xPos == size -1) {
            winCondition = 0;
            printf("You won! Your score - %d", score);
        } else {
            render(position, score, size);
        }
    }
}

int main() {
    unsigned int x = 0;
    scanf("%u", &x);
    assert(x >= 2);
    PacmanPosition position = initPosition();
    loop(&position, x);
}
