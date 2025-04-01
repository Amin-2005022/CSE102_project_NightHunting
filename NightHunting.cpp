                          /**************************************************************
                           *                                                            *
                           *                         NIGHT HUNTING                      *
                           *                                                            *
                           **************************************************************/

# include "iGraphics.h"
# include <stdlib.h>
# include <conio.h>

# define JUMP_HEIGHT 160
# define SCREEN_WIDTH 1300
# define SCREEN_HEIGHT 700
# define MAX_BULLET 30
# define misfired_range 5
# define bird_dx 75
# define bird_dy 50
# define pistol_dx 55
# define pistol_dy 35
# define live_dx 50
# define live_dy 45


int height_selection();
void hunter_move_cycle();
void animl_selection();
void animl_move_cycle();
void bird1_selection();
void bird1_move_cycle();
void bird2_selection();
void bird2_move_cycle();
void animal_collision();
void initialize_all();
void bird1_collision();
void bird2_collision();
void pistol_collision();
void live_collision();

struct character{
    int x, y, position_indx, move_indx, time, time_counter, selected, on_screen;
    float acceleration;
}animl, bird1, bird2;

struct Bullet{
    float x, y, initial_x, initial_y;
    int position_indx, fired;
}bulet;

struct hunter{
    int x, y, jump_y, move_index, position_index, initial_position, no_key_press, stand, landed, live;
}hunter;

struct collection{
    int x, y, timer;
}pistol, live;

struct LIVE{
    int x;
    int y;
} LiveCoord[3];


FILE *file;
FILE *HighScore;

char score_array[10];
char bullet_array[10];
char high_score_array[10];

int score, bullet_count, high_score, Game_state, SavedGame, misfired, animal_collision_count, bird_not_hunted, bullet_Off_screen;

char bird1_left[8][25]={"bird1//left//1.bmp", "bird1//left//2.bmp", "bird1//left//3.bmp", "bird1//left//4.bmp", "bird1//left//5.bmp", "bird1//left//6.bmp", "bird1//left//7.bmp", "bird1//left//8.bmp"};
char bird1_right[8][25]={"bird1//right//1.bmp", "bird1//right//2.bmp", "bird1//right//3.bmp", "bird1//right//4.bmp", "bird1//right//5.bmp", "bird1//right//6.bmp", "bird1//right//7.bmp", "bird1//right//8.bmp"};
char bird2_left[8][25]={"bird2//left//1.bmp", "bird2//left//2.bmp", "bird2//left//3.bmp", "bird2//left//4.bmp", "bird2//left//5.bmp", "bird2//left//6.bmp", "bird2//left//7.bmp", "bird2//left//8.bmp"};
char bird2_right[8][25]={"bird2//right//1.bmp", "bird2//right//2.bmp", "bird2//right//3.bmp", "bird2//right//4.bmp", "bird2//right//5.bmp", "bird2//right//6.bmp", "bird2//right//7.bmp", "bird2//right//8.bmp"};
char bird3_left[8][25]={"bird3//left//1.bmp", "bird3//left//2.bmp", "bird3//left//3.bmp", "bird3//left//4.bmp", "bird3//left//5.bmp", "bird3//left//6.bmp", "bird3//left//7.bmp", "bird3//left//8.bmp"};
char bird3_right[8][25]={"bird3//right//1.bmp", "bird3//right//2.bmp", "bird3//right//3.bmp", "bird3//right//4.bmp", "bird3//right//5.bmp", "bird3//right//6.bmp", "bird3//right//7.bmp", "bird3//right//8.bmp"};
char animal1_left[11][25]={"animal1//left//1.bmp", "animal1//left//2.bmp", "animal1//left//3.bmp", "animal1//left//4.bmp", "animal1//left//5.bmp", "animal1//left//6.bmp", "animal1//left//7.bmp", "animal1//left//8.bmp", "animal1//left//9.bmp", "animal1//left//10.bmp", "animal1//left//11.bmp"};
char animal1_right[11][25]={"animal1//right//1.bmp", "animal1//right//2.bmp", "animal1//right//3.bmp", "animal1//right//4.bmp", "animal1//right//5.bmp", "animal1//right//6.bmp", "animal1//right//7.bmp", "animal1//right//8.bmp", "animal1//right//9.bmp", "animal1//right//10.bmp", "animal1//right//11.bmp"};
char animal2_left[11][25]={"animal2//left//1.bmp", "animal2//left//2.bmp", "animal2//left//3.bmp", "animal2//left//4.bmp", "animal2//left//5.bmp", "animal2//left//6.bmp", "animal2//left//7.bmp", "animal2//left//8.bmp", "animal2//left//9.bmp", "animal2//left//10.bmp", "animal2//left//11.bmp"};
char animal2_right[11][25]={"animal2//right//1.bmp", "animal2//right//2.bmp", "animal2//right//3.bmp", "animal2//right//4.bmp", "animal2//right//5.bmp", "animal2//right//6.bmp", "animal2//right//7.bmp", "animal2//right//8.bmp", "animal2//right//9.bmp", "animal2//right//10.bmp", "animal2//right//11.bmp"};
char run_right[9][25]={"hunter//right1.bmp", "hunter//right2.bmp", "hunter//right3.bmp", "hunter//right4.bmp", "hunter//right5.bmp", "hunter//right6.bmp", "hunter//right7.bmp", "hunter//right8.bmp", "hunter//right9.bmp"};
char run_left[9][25]={"hunter//left1.bmp", "hunter//left2.bmp", "hunter//left3.bmp", "hunter//left4.bmp", "hunter//left5.bmp", "hunter//left6.bmp", "hunter//left7.bmp", "hunter//left8.bmp", "hunter//left9.bmp"};
char hunter_position[6][25]={"hunter//stand.bmp", "hunter//left_low.bmp", "hunter//left_high.bmp", "hunter//middle_high.bmp", "hunter//right_high.bmp", "hunter//right_low.bmp"};
char background[4][25]={"background//0.bmp", "background//1.bmp", "background//2.bmp", "background//3.bmp"};

void iDraw()
{
	iClear();

	if(Game_state == 0)
    {
        if(SavedGame == 0)
            iShowBMP(0, 0, background[0]);
        if(SavedGame == 1)
            iShowBMP(0, 0, background[1]);
    }

    else if(Game_state == 1)
    {
        iShowBMP(0, 0, background[2]);

        /***** HUNTER MOVEMENT *****/
        if(animal_collision_count%4==0 || animal_collision_count%5==0 || animal_collision_count%6==0)
        {
            if(hunter.stand || !hunter.move_index)
            {
                iShowBMP2(hunter.x, hunter.y, hunter_position[hunter.initial_position],255);
            }

            else
            {
                if(hunter.move_index==1)
                {
                    iShowBMP2(hunter.x, hunter.y, run_right[hunter.position_index], 255);
                    hunter.no_key_press++;
                    if(hunter.no_key_press>=10)
                    {
                        hunter.move_index=0;
                        hunter.position_index=0;
                        hunter.no_key_press=0;
                    }
                }
                else if(hunter.move_index==-1)
                {
                    iShowBMP2(hunter.x, hunter.y, run_left[hunter.position_index], 255);
                    hunter.no_key_press++;
                    if(hunter.no_key_press>=10)
                    {
                        hunter.move_index=0;
                        hunter.position_index=0;
                        hunter.no_key_press=0;
                    }
                }
                else if(hunter.move_index==2 || hunter.move_index==3)
                {
                    iShowBMP2(hunter.x, hunter.y+hunter.jump_y, run_right[hunter.position_index], 255);
                }
                else if(hunter.move_index==-2 || hunter.move_index==-3)
                {
                iShowBMP2(hunter.x, hunter.y+hunter.jump_y, run_left[hunter.position_index], 255);
                }
            }
        }

        if(hunter.live==0)
            Game_state=2;

        /***** ANIMAL MOVEMENT *****/
        if(animl.selected == 0)
        {
            animl_selection();
            animl.selected = 1;
            if(animl.move_indx == 0 || animl.move_indx == 2)
            animl.x=0;

            else if(animl.move_indx==1 || animl.move_indx==3)
            animl.x=SCREEN_WIDTH-200;
        }

        animl.time_counter++;

        if(animl.time_counter == animl.time)
        {
            animl.on_screen = 1;
        }
        if(animl.on_screen)
        {
            animl_move_cycle();
        }
        animal_collision();

        /***** BIRD-1 MOVEMENT *****/
        if(bird1.selected == 0)
        {
            bird1_selection();
            bird1.selected = 1;
            if(bird1.move_indx==0 || bird1.move_indx==2 || bird1.move_indx==4)
            bird1.x=0;

            else if(bird1.move_indx==1 || bird1.move_indx==3 || bird1.move_indx==5)
            bird1.x=SCREEN_WIDTH-60;
        }

        bird1.time_counter++;

        if(bird1.time_counter==bird1.time)
        {
            bird1.on_screen = 1;
        }
        if(bird1.on_screen)
        {
            bird1_move_cycle();
        }

        /***** BIRD-2 MOVEMENT *****/
        if(bird2.selected == 0)
        {
            bird2_selection();
            bird2.selected = 1;
            if(bird2.move_indx==0 || bird2.move_indx==2 || bird1.move_indx==4)
            bird2.x=0;

            else if(bird2.move_indx==1 || bird2.move_indx==3 || bird1.move_indx==5)
            bird2.x=SCREEN_WIDTH-60;
        }

        bird2.time_counter++;

        if(bird2.time_counter==bird2.time)
        {
            bird2.on_screen = 1;
        }
        if(bird2.on_screen)
        {
            bird2_move_cycle();
        }
        if(bird_not_hunted >= 5)
        {
            bird_not_hunted = 0;
            hunter.live--;
        }

        /***** BULLET RENDERING *****/
        if(bulet.fired == 1)
        {
            iSetColor(0, 0, 0);
            iFilledCircle(bulet.x, bulet.y, 3);
            bird1_collision();
            bird2_collision();
        }
        if(misfired==5)
        {
            hunter.live--;
            misfired=0;
        }

        /***** SCORE & BULLET DISPLAY *****/
        iSetColor(0, 0, 0);
        for(int i=0; i<hunter.live; i++)
        {
            iShowBMP2(LiveCoord[i].x, LiveCoord[i].y, "live1.bmp", 0);
        }
        iText(5, SCREEN_HEIGHT-25, "SCORE: ", GLUT_BITMAP_HELVETICA_18);
        iText(90, SCREEN_HEIGHT-25, itoa(score, score_array,10), GLUT_BITMAP_HELVETICA_18);
        iText(SCREEN_WIDTH-75, SCREEN_HEIGHT-25, ":BULLET", GLUT_BITMAP_HELVETICA_18);
        iText(SCREEN_WIDTH-105, SCREEN_HEIGHT-25, itoa(bullet_count, bullet_array, 10), GLUT_BITMAP_HELVETICA_18);
        iText(5, SCREEN_HEIGHT-50, "MISFIRED: ", GLUT_BITMAP_HELVETICA_18);
        iText(5, SCREEN_HEIGHT-75, "ESCAPED: ", GLUT_BITMAP_HELVETICA_18);
        iRectangle(100, SCREEN_HEIGHT-50, 100, 12);
        iRectangle(100, SCREEN_HEIGHT-75, 100, 12);
        iFilledRectangle(100, SCREEN_HEIGHT-50, 20*misfired, 12);
        iFilledRectangle(100, SCREEN_HEIGHT-75, 20*bird_not_hunted, 12);

        /***** NEW PISTOL LAUNCHING *****/
        pistol.timer++;
        if(pistol.timer >= 500)
        {
            if(pistol.timer == 500)
            {
                pistol.x = 250 + rand() % 900;
                pistol.y = SCREEN_HEIGHT;
            }
            iShowBMP2(pistol.x, pistol.y, "pistol.bmp", 255);
            pistol.y -= 15;
            if(pistol.y < 40)
            pistol.timer = 0;
            pistol_collision();
        }

        /***** NEW LIVE LAUNCHING *****/
        live.timer++;
        if(live.timer >= 800)
        {
            if(live.timer == 800)
            {
                live.x = 250 + rand() % 900;
                live.y = SCREEN_HEIGHT;
            }
            iShowBMP2(live.x, live.y, "live2.bmp", 0);
            live.y -= 10;
            if(live.y < 40)
            live.timer = 0;
            live_collision();
        }

    }

    else if(Game_state == 2)
    {
        /***** GAME OVER PAGE *****/
        iSetColor(255,255,255);
        iText(520, 500, "YOUR SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(700, 500, itoa(score, score_array,10), GLUT_BITMAP_TIMES_ROMAN_24);

        HighScore = fopen("HighScore.txt", "r");
        fscanf(HighScore, "%d", &high_score);
        fclose(HighScore);
        if(score >= high_score)
        {
            iText(475, 400, "***NEW RECORD***", GLUT_BITMAP_TIMES_ROMAN_24);
            high_score = score;
            HighScore = fopen("HighScore.txt", "w");
            fprintf(HighScore, "%d", high_score);
            fclose(HighScore);
        }
        iText(520, 300, "HIGH SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(700, 300, itoa(high_score, high_score_array,10), GLUT_BITMAP_TIMES_ROMAN_24);

        iText(400, 200, "--- CLICK MOUSE TO CONTINUE ---", GLUT_BITMAP_TIMES_ROMAN_24);
    }

    else if(Game_state==3)
    {
        /***** HIGH SCORE MENU *****/
        iShowBMP(0, 0, background[3]);

        HighScore = fopen("HighScore.txt", "r");
        fscanf(HighScore,"%d", &high_score);
        fclose(HighScore);

        iSetColor(128,0,0);
        iText(200,320, "HIGH   SCORE : ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(390,320, itoa(high_score, high_score_array, 10), GLUT_BITMAP_TIMES_ROMAN_24);
    }

    else if(Game_state==4)
    {
        /***** INSTRUCTION MENU *****/
        iShowBMP(0, 0, background[3]);
        iSetColor(128,0,0);
        iText(180,330, "Press 'S' to go left.       Press 'A' to jump up-left", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(180,290, "Press 'D' to go right.    Press 'F' to jump up-right", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(180,250, "Press 'LEFT' 'RIGHT' 'UP' 'DOWN' key to change the gun position", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(180,210, "Press 'SPACE BAR' to Shoot the gun", GLUT_BITMAP_TIMES_ROMAN_24);

    }
}

void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        /***** HOME PAGE WITHOUT SAVED GAME *****/
        if(Game_state==0 && SavedGame == 0)
        {
            if(mx>=280 && mx<=425 && my>=355 && my<= 395)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                initialize_all();
                Game_state=1;
            }

            if(mx>=235 && mx<=470 && my>=285 && my<= 325)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                Game_state=3;
            }

            if(mx>=300 && mx<=405 && my>=220 && my<= 265)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                Game_state=4;
            }
            if(mx>=305 && mx<=405 && my>=160 && my<= 200)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                exit(0);
            }
        }

        /***** HOME PAGE WITH SAVED GAME *****/
        if(Game_state==0 && SavedGame == 1)
        {
            if(mx>=265 && mx<=405 && my>=360 && my<= 400)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                Game_state=1;
            }

            if(mx>=255 && mx<=460 && my>=295 && my<= 335)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                initialize_all();
                Game_state=1;
            }

            if(mx>=250 && mx<=465 && my>=230 && my<= 270)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                Game_state=3;
            }

            if(mx>=310 && mx<=405 && my>=165 && my<= 205)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                Game_state=4;
            }
            if(mx>=310 && mx<=405 && my>=105 && my<= 145)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                exit(0);
            }
        }

        if(Game_state==3||Game_state==4)
        {
            if(mx>=915 && mx<=1030 && my>=120 && my<= 160)
            {
                PlaySound("MouseClick.wav", NULL, SND_SYNC);
                Game_state=0;
            }
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
    }
    if(Game_state == 2)
    {
        PlaySound("MouseClick.wav", NULL, SND_SYNC);
        SavedGame = 0;

        file = fopen("SavedGame.txt", "w");
        fprintf(file, "%d", SavedGame);
        fclose(file);

        initialize_all();
        Game_state = 0;
    }
}

void iKeyboard(unsigned char key)
{
	if(Game_state==1)
    {
        if(key == 'd' && hunter.move_index<2 &&hunter.move_index>-2 && hunter.landed)
        {
            hunter.stand=0;
            hunter.move_index = 1;
            if(hunter.x<=900)
            hunter.x+=15;
            hunter.position_index++;
            if(hunter.position_index>=8) hunter.position_index=0;
        }
        if(key == 's' && hunter.move_index<2 && hunter.move_index>-2 && hunter.landed)
        {
            hunter.stand=0;
            hunter.move_index=-1;
            if(hunter.x>=200)
            hunter.x-=15;
            hunter.position_index++;
            if(hunter.position_index>=8) hunter.position_index=0;
        }
        if(key == 'f' && hunter.move_index!=2 && hunter.move_index!=-2 && hunter.landed)
        {
            hunter.stand=0;
            hunter.move_index=2;
            hunter.landed=0;
        }
        if(key == 'a' && hunter.move_index!=-2 && hunter.move_index!=2 && hunter.landed)
        {
            hunter.stand=0;
            hunter.move_index=-2;
            hunter.landed=0;
        }
        if(key == ' ' && !bulet.fired && hunter.initial_position >= 1 && hunter.initial_position <= 5 && bullet_count>0)
        {
            if(bullet_count)
            bullet_count--;
            bullet_Off_screen=0;
            bulet.position_indx = hunter.initial_position;
            if(bulet.position_indx == 1)
            {
                bulet.initial_x = hunter.x + 34;
                bulet.initial_y = hunter.y + 175;
                bulet.fired=1;
                PlaySound("gunshot.wav", NULL, SND_ASYNC);
            }
            else if(bulet.position_indx==5)
            {
                bulet.initial_x = hunter.x + 158;
                bulet.initial_y = hunter.y + 173;
                bulet.fired=1;
                PlaySound("gunshot.wav", NULL, SND_ASYNC);
            }
            else if(bulet.position_indx==2)
            {
                bulet.initial_x = hunter.x + 84;
                bulet.initial_y = hunter.y + 194;
                bulet.fired=1;
                PlaySound("gunshot.wav", NULL, SND_ASYNC);
            }
            else if(bulet.position_indx==3)
            {
                bulet.initial_x = hunter.x + 116;
                bulet.initial_y = hunter.y + 188;
                bulet.fired=1;
                PlaySound("gunshot.wav", NULL, SND_ASYNC);
            }
            else if(bulet.position_indx==4)
            {
                bulet.initial_x = hunter.x + 106;
                bulet.initial_y = hunter.y + 194;
                bulet.fired=1;
                PlaySound("gunshot.wav", NULL, SND_ASYNC);
            }
            bulet.x=bulet.initial_x;
            bulet.y=bulet.initial_y;
        }

        if(key == 'q' && Game_state == 1)
        {
            /***** SAVING GAME *****/
            SavedGame = 1;

            file = fopen("SavedGame.txt", "w");
            fprintf(file, "%d", SavedGame);
            fclose(file);

            file = fopen("Animal.txt", "w");
            fprintf(file, "%d %d %d %d %d %d %d %d %f", animl.x, animl.y, animl.position_indx, animl.move_indx, animl.time, animl.time_counter, animl.selected, animl.on_screen, animl.acceleration);
            fclose(file);

            file = fopen("Bird1.txt", "w");
            fprintf(file, "%d %d %d %d %d %d %d %d %f", bird1.x, bird1.y, bird1.position_indx, bird1.move_indx, bird1.time, bird1.time_counter, bird1.selected, bird1.on_screen, bird1.acceleration);
            fclose(file);

            file = fopen("Bird2.txt", "w");
            fprintf(file, "%d %d %d %d %d %d %d %d %f", bird2.x, bird2.y, bird2.position_indx, bird2.move_indx, bird2.time, bird2.time_counter, bird2.selected, bird2.on_screen, bird2.acceleration);
            fclose(file);

            file = fopen("Bullet.txt", "w");
            fprintf(file, "%f %f %f %f %d %d", bulet.x, bulet.y, bulet.initial_x, bulet.initial_y, bulet.position_indx, bulet.fired);
            fclose(file);

            file = fopen("Hunter.txt", "w");
            fprintf(file, "%d %d %d %d %d %d %d %d %d %d", hunter.x, hunter.y, hunter.jump_y, hunter.move_index, hunter.position_index, hunter.initial_position, hunter.no_key_press, hunter.stand, hunter.landed, hunter.live);
            fclose(file);

            file = fopen("BulletCount.txt", "w");
            fprintf(file, "%d %d %d %d %d", bullet_count, misfired, animal_collision_count, bird_not_hunted, bullet_Off_screen);
            fclose(file);

            file = fopen("Score.txt", "w");
            fprintf(file, "%d", score);
            fclose(file);

            file = fopen("pistol.txt", "w");
            fprintf(file, "%d %d %d", pistol.x, pistol.y, pistol.timer);
            fclose(file);

            file = fopen("live.txt", "w");
            fprintf(file, "%d %d %d", live.x, live.y, live.timer);
            fclose(file);

            exit(0);
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{
    if(Game_state ==1 && hunter.move_index<2 &&hunter.move_index>-2)
    {
        hunter.stand=1;
        if(key == GLUT_KEY_LEFT)
        {
            if(hunter.initial_position > 1 && hunter.initial_position <= 5)
            hunter.initial_position-=1;
        }
        if(key == GLUT_KEY_RIGHT)
        {
            if(hunter.initial_position >= 1 && hunter.initial_position < 5)
            hunter.initial_position+=1;
        }
        if(key == GLUT_KEY_UP)
        {
            if(hunter.initial_position == 0)
            hunter.initial_position = 3;
        }
        if(key == GLUT_KEY_DOWN)
        {
            if(hunter.initial_position >= 1 && hunter.initial_position <= 5)
            hunter.initial_position = 0;
        }
    }
}

void hunter_move_cycle()
{
    if(hunter.move_index==2)
    {
        hunter.jump_y+=20;
        if(hunter.x<=900) hunter.x+= 15;
        hunter.position_index++;
        if(hunter.position_index>=8) hunter.position_index=0;
        if(hunter.jump_y>=JUMP_HEIGHT) hunter.move_index=3;
    }

    else if( hunter.move_index==3)
    {
        if(hunter.jump_y>0) hunter.jump_y-=20;
        if(hunter.x<=900) hunter.x+=15;
        hunter.position_index++;
        if(hunter.position_index>=8) hunter.position_index=0;
        if(hunter.jump_y<=20)
        {
            hunter.move_index=0;
            hunter.position_index=0;
            hunter.landed=1;
        }
    }

    else if(hunter.move_index==-2)
    {
        hunter.jump_y+=20;
        if(hunter.x>=200) hunter.x-=15;
        hunter.position_index++;
        if(hunter.position_index>=8) hunter.position_index=0;
        if(hunter.jump_y>=JUMP_HEIGHT) hunter.move_index=-3;
    }

    else if(hunter.move_index==-3)
    {
        if(hunter.jump_y>0)hunter.jump_y-=20;
        if(hunter.x>=200) hunter.x-=15;
        hunter.position_index++;
        if(hunter.position_index>=8) hunter.position_index=0;
        if(hunter.jump_y<=20)
        {
            hunter.move_index=0;
            hunter.position_index=0;
            hunter.landed=1;
        }
    }
}

void animl_selection()
{
    animl.time=rand()%500;
    animl.move_indx=rand()%4;
    animl.time_counter=0;
    animl.position_indx=0;
    animl.acceleration+=0.05;
}

void animl_move_cycle()
{
    if(animl.move_indx==0 || animl.move_indx==2)
    {
        animl.x+=20+animl.acceleration;
    }
    else if(animl.move_indx==1 || animl.move_indx==3)
    {
        animl.x-=20+animl.acceleration;
    }

    if(animl.move_indx==0)
        iShowBMP2(animl.x, animl.y, animal1_right[animl.position_indx], 255);
    else if(animl.move_indx==1)
        iShowBMP2(animl.x, animl.y, animal1_left[animl.position_indx], 255);
    else if(animl.move_indx==2)
        iShowBMP2(animl.x, animl.y, animal2_right[animl.position_indx], 255);
    else if(animl.move_indx==3)
        iShowBMP2(animl.x, animl.y, animal2_left[animl.position_indx], 255);

    animl.position_indx++;
    if(animl.position_indx>10)
        animl.position_indx=0;

    if(animl.x<0 || animl.x>SCREEN_WIDTH)
    {
        animl.on_screen=0;
        animl.selected=0;
    }
}

void bird1_selection()
{
    bird1.time=rand()%100;
    bird1.move_indx=rand()%6;
    bird1.time_counter=0;
    bird1.position_indx=0;
    bird1.y=height_selection();
    bird1.acceleration=rand()%20;
}

void bird1_move_cycle()
{
    if(bird1.move_indx==0 || bird1.move_indx==2 || bird1.move_indx==4)
        bird1.x+=20+bird1.acceleration;
    else if(bird1.move_indx==1 || bird1.move_indx==3 || bird1.move_indx==5)
        bird1.x-=20+bird1.acceleration;

    if(bird1.move_indx==0)
        iShowBMP2(bird1.x, bird1.y, bird1_right[bird1.position_indx], 255);
    else if(bird1.move_indx==1)
        iShowBMP2(bird1.x, bird1.y, bird1_left[bird1.position_indx], 255);
    else if(bird1.move_indx==2)
        iShowBMP2(bird1.x, bird1.y, bird2_right[bird1.position_indx], 255);
    else if(bird1.move_indx==3)
        iShowBMP2(bird1.x, bird1.y, bird2_left[bird1.position_indx], 255);
    else if(bird1.move_indx==4)
        iShowBMP2(bird1.x, bird1.y, bird3_right[bird1.position_indx], 255);
    else if(bird1.move_indx==5)
        iShowBMP2(bird1.x, bird1.y, bird3_left[bird1.position_indx], 255);

    bird1.position_indx++;
    if(bird1.position_indx>7)
        bird1.position_indx=0;

    if(bird1.x<0 || bird1.x>SCREEN_WIDTH)
    {
        bird1.on_screen=0;
        bird1.selected=0;
        bird_not_hunted++;
    }

}
void bird2_selection()
{
    bird2.time=rand()%200;
    bird2.move_indx=rand()%6;
    bird2.time_counter=0;
    bird2.position_indx=0;
    bird2.y=height_selection();
    bird2.acceleration= rand()%10;
}

void bird2_move_cycle()
{
    if(bird2.move_indx==0 || bird2.move_indx==2 || bird2.move_indx==4)
        bird2.x+=20+bird2.acceleration;
    else if(bird2.move_indx==1 || bird2.move_indx==3 || bird2.move_indx==5)
        bird2.x-=20+bird2.acceleration;

    if(bird2.move_indx==0)
        iShowBMP2(bird2.x, bird2.y, bird2_right[bird2.position_indx], 255);
    else if(bird2.move_indx==1)
        iShowBMP2(bird2.x, bird2.y, bird2_left[bird2.position_indx], 255);
    else if(bird2.move_indx==2)
        iShowBMP2(bird2.x, bird2.y, bird2_right[bird2.position_indx], 255);
    else if(bird2.move_indx==3)
        iShowBMP2(bird2.x, bird2.y, bird2_left[bird2.position_indx], 255);
    else if(bird2.move_indx==4)
        iShowBMP2(bird2.x, bird2.y, bird3_right[bird2.position_indx], 255);
    else if(bird2.move_indx==5)
        iShowBMP2(bird2.x, bird2.y, bird3_left[bird2.position_indx], 255);

    bird2.position_indx++;
    if(bird2.position_indx>7)
        bird2.position_indx=0;

    if(bird2.x<0 || bird2.x>SCREEN_WIDTH)
    {
        bird2.on_screen=0;
        bird2.selected=0;
        bird_not_hunted++;
    }
}

void Bullet_rendering()
{
    if(bulet.position_indx==1)
    {
        bulet.x-=50;
        bulet.y = bulet.initial_y -0.5 * (bulet.x - bulet.initial_x);
    }
    else if(bulet.position_indx==5)
    {
        bulet.x+=50;
        bulet.y = bulet.initial_y + 0.5 *(bulet.x - bulet.initial_x);
    }
    else if(bulet.position_indx==2)
    {
        bulet.x-=50;
        bulet.y = bulet.initial_y -0.8 *(bulet.x - bulet.initial_x);
    }
    else if(bulet.position_indx==3)
    {
        bulet.y +=50;
    }
    else if(bulet.position_indx==4)
    {
        bulet.x+=50;
        bulet.y = bulet.initial_y + 0.8*(bulet.x - bulet.initial_x);
    }
    if(bulet.x<0 || bulet.x>SCREEN_WIDTH || bulet.y>SCREEN_HEIGHT)
    {
        bulet.fired=0;
        bullet_Off_screen++;
        if(bullet_Off_screen==1)
        misfired++;
    }
}

void bird1_collision()
{
    if(bulet.x>bird1.x  &&  bulet.y>bird1.y  &&  bird1.x+bird_dx>bulet.x  &&  bird1.y+bird_dy>bulet.y)
    {
        score++;
        bulet.fired=0;
        bird1.on_screen=0;
        bird1.selected=0;
        bird1.time_counter = 0;
        misfired = -1;
    }
}

void bird2_collision()
{
    if(bulet.x>bird2.x  &&  bulet.y>bird2.y  &&  bird2.x+bird_dx>bulet.x  &&  bird2.y+bird_dy>bulet.y)
    {
        score++;
        bulet.fired=0;
        bird2.on_screen=0;
        bird2.selected=0;
        bird2.time_counter=0;
        misfired = -1;
    }
}

void animal_collision()
{
    if((animl.x+190>hunter.x+55 && hunter.x+125>animl.x+80 && hunter.jump_y<60) || (animl.x+30<hunter.x+125 && hunter.x+55<animl.x+140 && hunter.jump_y<6))
    {
        animal_collision_count++;
        if(animal_collision_count==1)
        {
            hunter.live--;
            PlaySound("TIGER.wav", NULL, SND_ASYNC);

        }
        if(hunter.live==0)
        {
            PlaySound("TIGER.wav", NULL, SND_SYNC);
            Game_state=2;
        }

    }
    else
        animal_collision_count=0;
}

void pistol_collision()
{
    if(hunter.x+125>pistol.x  && hunter.y+160>pistol.y  &&  pistol.x+pistol_dx>hunter.x+55  &&  pistol.y+pistol_dy>hunter.y+25)
    {
        PlaySound("GunLoad.wav", NULL, SND_ASYNC);
        bullet_count=MAX_BULLET;
        pistol.timer = 0;
    }
}

void live_collision()
{
    if(hunter.x+125>live.x  && hunter.y+160>live.y  &&  live.x+live_dx>hunter.x+55  &&  live.y+live_dy>hunter.y+25)
    {
        PlaySound("newlive.wav", NULL, SND_ASYNC);
        if(hunter.live<3)
            hunter.live++;
        live.timer = 0;
    }
}

void initialize_all()
{
    Game_state=0;
    bullet_count=MAX_BULLET;
    score=0;
    SavedGame = 0;
    misfired = 0;
    animal_collision_count=0;
    bird_not_hunted=0;
    bullet_Off_screen=0;

    animl = {0, 20, 0, 0, 0, 0, 0, 0, 0};
    bird1 = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    bird2 = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    bulet = {0, 0, 0, 0, 0, 0};
    pistol = {0, 0, 0};
    live = {0, 0, 0};

    hunter = {550, 15, 0, 0, 0, 0, 0, 1, 1, 3};
}

int height_selection()
{
    return (rand()%250)+350;
}

int main()
{
    file = fopen("SavedGame.txt", "r");
    fscanf(file, "%d", &SavedGame);
    fclose(file);

    file = fopen("Animal.txt", "r");
    fscanf(file, "%d %d %d %d %d %d %d %d %f", &animl.x, &animl.y, &animl.position_indx, &animl.move_indx, &animl.time, &animl.time_counter, &animl.selected, &animl.on_screen, &animl.acceleration);
    fclose(file);

    file = fopen("Bird1.txt", "r");
    fscanf(file, "%d %d %d %d %d %d %d %d %f", &bird1.x, &bird1.y, &bird1.position_indx, &bird1.move_indx, &bird1.time, &bird1.time_counter, &bird1.selected, &bird1.on_screen, &bird1.acceleration);
    fclose(file);

    file = fopen("Bird2.txt", "r");
    fscanf(file, "%d %d %d %d %d %d %d %d %f", &bird2.x, &bird2.y, &bird2.position_indx, &bird2.move_indx, &bird2.time, &bird2.time_counter, &bird2.selected, &bird2.on_screen, &bird2.acceleration);
    fclose(file);

    file = fopen("Bullet.txt", "r");
    fscanf(file, "%f %f %f %f %d %d", &bulet.x, &bulet.y, &bulet.initial_x, &bulet.initial_y, &bulet.position_indx, &bulet.fired);
    fclose(file);

    file = fopen("Hunter.txt", "r");
    fscanf(file, "%d %d %d %d %d %d %d %d %d %d", &hunter.x, &hunter.y, &hunter.jump_y, &hunter.move_index, &hunter.position_index, &hunter.initial_position, &hunter.no_key_press, &hunter.stand, &hunter.landed, &hunter.live);
    fclose(file);

    file = fopen("BulletCount.txt", "r");
    fscanf(file, "%d %d %d %d %d", &bullet_count, &misfired, &animal_collision_count, &bird_not_hunted, &bullet_Off_screen);
    fclose(file);

    file = fopen("Score.txt", "r");
    fscanf(file, "%d", &score);
    fclose(file);

    file = fopen("pistol.txt", "r");
    fscanf(file, "%d %d %d", &pistol.x, &pistol.y, &pistol.timer);
    fclose(file);

    file = fopen("live.txt", "r");
    fscanf(file, "%d %d %d", &live.x, &live.y, &live.timer);
    fclose(file);


    for(int i=0; i<3; i++)
    {
        LiveCoord[i].x=SCREEN_WIDTH-30*(i+1);
        LiveCoord[i].y=SCREEN_HEIGHT-60;
    }

	iSetTimer(75, *hunter_move_cycle);
	iSetTimer(10, *Bullet_rendering);
	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Night Hunting");

	return 0;
}
