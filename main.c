#define REG_DISPCTL (*(unsigned short *)0x4000000)
#define MODE3 3
#define BG2_ENABLE (1<<10)

// Create a color with the specified RGB values
#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)

// Calculate the position of a pixel based on its row and column
#define OFFSET(r, c, rowlen) ((r)*(rowlen)+(c))

// Predefined colors
#define MAGENTA COLOR(31, 0, 31)
#define LIGHTBLUE COLOR(16,16,31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0
#define WHITE COLOR(31, 31, 31)

// Function Prototypes
void setPixel(int, int, unsigned short);
void delay(int);
void drawRect(int, int, int, int, unsigned short);
void goToFrown();
void goToMiddle();
void goToSmile();
void frown();
void middle();
void smile();
void initialize();

int color;
unsigned short *videoBuffer = (unsigned short *)0x6000000;

int main() {
    initialize();
    //Loops animation
    while(1) {
        switch(color) {
            case LIGHTBLUE:
                frown();
                break;
            case MAGENTA:
                middle();
                break;
            case YELLOW:
                smile();
                break;
        }
    }
}

void initialize() {
    REG_DISPCTL = MODE3 | BG2_ENABLE;

    //draw
    //eyes
    drawRect(60,20,20,20,YELLOW);
    drawRect(160,20,20,20,YELLOW);
    //smile
    drawRect(60,80,120,20,YELLOW);

    color = YELLOW;
}

void goToFrown() {
    color = LIGHTBLUE;
}
void goToMiddle() {
    color = MAGENTA;
}
void goToSmile() {
    color = YELLOW;
}
//draw, erase, draw again
void frown() {
    //eyes
    drawRect(60,20,20,20,BLACK);
    drawRect(160,20,20,20,BLACK);
    drawRect(160,20,20,20,LIGHTBLUE);
    drawRect(60,20,20,20,LIGHTBLUE);

    //frown
    drawRect(60,80,120,20,BLACK);
    drawRect(60,100,20,20,BLACK);
    drawRect(160,100,20,20,BLACK);
    drawRect(160,100,20,20,LIGHTBLUE);
    drawRect(60,80,120,20,LIGHTBLUE);
    drawRect(60,100,20,20,LIGHTBLUE);

    delay(200);
    goToSmile();
}
void middle() {
    //eyes
    drawRect(60,20,20,20,BLACK);
    drawRect(160,20,20,20,BLACK);
    drawRect(160,20,20,20,MAGENTA);
    drawRect(60,20,20,20,MAGENTA);

    //middle
    drawRect(60,60,20,20,BLACK);
    drawRect(160,60,20,20,BLACK);
    drawRect(60,80,120,20,BLACK);
    drawRect(60,80,120,20,MAGENTA);



    delay(200);
    goToFrown();
}
void smile() {
    //eyes
    drawRect(60,20,20,20,BLACK);
    drawRect(160,20,20,20,BLACK);
    drawRect(160,20,20,20,YELLOW);
    drawRect(60,20,20,20,YELLOW);
    //smile

    //erase frown
    drawRect(60,100,20,20,BLACK);
    drawRect(160,100,20,20,BLACK);
    drawRect(60,80,120,20,BLACK);
    drawRect(60,60,20,20,BLACK);
    //draw
    drawRect(160,60,20,20,BLACK);
    drawRect(60,60,20,20,YELLOW);
    drawRect(160,60,20,20,YELLOW);
    drawRect(60,80,120,20,YELLOW);

    delay(200);
    goToMiddle();
}



void setPixel(int row, int col, unsigned short color) {

    videoBuffer[OFFSET(col,row,240)] = color;

}

void delay(int amount) {
    volatile int trash = 0;
    for (int i = 0; i < amount * 1000; i++) {
        trash++;
    }
}

void drawRect(int row, int col, int height, int width, unsigned short color) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            setPixel(row + i, col + j, color);
        }
    }
}

