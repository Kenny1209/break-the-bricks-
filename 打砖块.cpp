#include <cstdio>
#include <Windows.h>
#include <time.h>
#include <ctime>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 
using namespace std;

char map[9][13] = {"------------",//x=0
			   	   "|..........|",//x=1
				   "|..........|",//x=2
				   "|..........|",//x=3
				   "|..........|",//x=4
				   "|..........|",//x=5
			       "|..........|",//x=6
				   "|..........|",//x=7
				   "############",//x=8
			  	};//y:0~11 
int y = 5, x = 7;//板子的坐标 
int ball_y = 5, ball_x = 6;//球的坐标 

int main(){
	
	int score = 0;//分数 
	int clocktime = clock();//控制刷新率 
	int fps;
	bool alive = true;//判断是否还存活 
	int press;//板子移动冷却时间 
	int dir = 3;// 1^\  2^/  3v\  4v/ 球方向 
	bool ballmove = true;//球下次是否移动 
	int nums; //用于判断是否还有砖块剩余 
	int balltime = clock();//球移动时间间隔 
	bool ballif = true;//转向后再判断一次 
	
	//生成砖块
	srand(std::time(0));//设置随机数种子
	for(int o=3; o>0; o--){
		for(int p=1; p<11; p++){
			map[o][p] = rand()%9+49;
		}
	} 
	
	while (alive){
		
		//控制板子移动 
		if (KEY_DOWN('A') && y > 1 && clock() - press >= 100){//左移 
			y -= 1;
			press = clock();
		} else if (KEY_DOWN('D') && y < 9 && clock() - press >= 100){//右移 
			y += 1;
			press = clock();
		}
		
		//球移动
		if (clock() - balltime >= 500) {//球每隔0.5s移动一次 
			balltime = clock();
			while (ballif){
				if (dir == 1){
					if (map[ball_x-1][ball_y] != 46) {
						if (map[ball_x-1][ball_y] >= 49 && map[ball_x-1][ball_y] <= 57){
							map[ball_x-1][ball_y]--;
							score++; 
				       }dir = 4;
					} else if (map[ball_x][ball_y-1] != 46) {
						if (map[ball_x][ball_y-1] >= 49 && map[ball_x][ball_y-1] <= 57){
							map[ball_x][ball_y-1]--;
							score++;
				       }dir = 2;
					} else if (map[ball_x-1][ball_y-1] != 46){
						ballmove = false;
						srand(std::time(0));//设置随机数种子
						if (rand()%2){
							ball_y--;
						} else {
							ball_x--;
						}
					} else {
						ballif = false;
					}
				} else if (dir == 2){
					if (map[ball_x-1][ball_y] != 46) {
						if (map[ball_x-1][ball_y] >= 49 && map[ball_x-1][ball_y] <= 57){
							map[ball_x-1][ball_y]--;
							score++;
				       }dir = 3;
				    } else if (map[ball_x][ball_y+1] != 46) {
						if (map[ball_x][ball_y+1] >= 49 && map[ball_x][ball_y+1] <= 57){
							map[ball_x][ball_y+1]--;
							score++;
				       }dir = 1;
					} else if (map[ball_x-1][ball_y+1] != 46){
						ballmove = false;
						srand(std::time(0));//设置随机数种子
						if (rand()%2){
							ball_y++;
						} else {
							ball_x--;
						}
					} else {
						ballif = false;
					}
				} else if (dir == 3){
					if ((map[ball_x+1][ball_y] != 46 || ((ball_x+1 == x && ball_y == y) || (ball_x+1 == x && ball_y == y+1)))) {
						if (map[ball_x+1][ball_y] >= 49 && map[ball_x+1][ball_y] <= 57){
							map[ball_x+1][ball_y]--;
							score++;
				       }dir = 2;
				    } else if (map[ball_x][ball_y+1] != 46 || ((ball_x == x && ball_y+1 == y) || (ball_x == x && ball_y+1 == y+1))) {
						if (map[ball_x][ball_y+1] >= 49 && map[ball_x][ball_y+1] <= 57){
							map[ball_x][ball_y+1]--;
							score++;
				       }dir = 4;
					} else if ((map[ball_x+1][ball_y+1] != 46 || ((ball_x+1 == x && ball_y+1 == y) || (ball_x+1 == x && ball_y+1 == y+1)))){
						ballmove = false;
						srand(std::time(0));//设置随机数种子
						if (rand()%2){
							ball_y++;
						} else {
							ball_x++;
						}
					} else {
						ballif = false;
					}
				} else if (dir == 4){
					if ((map[ball_x+1][ball_y] != 46 || ((ball_x+1 == x && ball_y == y) || (ball_x+1 == x && ball_y == y+1)))) {
						if (map[ball_x+1][ball_y] >= 49 && map[ball_x-1][ball_y] <= 57){
							map[ball_x+1][ball_y]--;
							score++;
				       }dir = 1;
					} else if (map[ball_x][ball_y-1] != 46 || ((ball_x == x && ball_y-1 == y) || (ball_x == x && ball_y-1 == y+1))) {
						if (map[ball_x][ball_y-1] >= 49 && map[ball_x][ball_y-1] <= 57){
							map[ball_x][ball_y-1]--;
							score++;
				       }dir = 3;
					} else if ((map[ball_x+1][ball_y-1] != 46 || ((ball_x+1 == x && ball_y-1 == y) || (ball_x+1 == x && ball_y-1 == y+1)))){
						ballmove = false;
						srand(std::time(0));//设置随机数种子
						if (rand()%2){
							ball_y--;
						} else {
							ball_x++;
						}
					} else {
						ballif = false;
					}	
				}
			}ballif = true; 
			if (ballmove){
				if (dir == 1){
					ball_x -= 1;
					ball_y -= 1;
				} else if (dir == 2){
					ball_x -= 1;
					ball_y += 1;
				} else if (dir == 3){
					ball_x += 1;
					ball_y += 1;
				} else if (dir == 4){
					ball_x += 1;
					ball_y -= 1;
				}
			} else {
				ballmove = true;
			}
		}
		
		if (clock() - clocktime >= 50){//锁20刷新率
			fps = 1000 / (clock() - clocktime); 
			clocktime = clock();
			
			//输出画面
			nums = 0;//用于判断是否还有砖块剩余 
			system("cls");
			for(int i=0;i<=8;i++){
				for(int j=0;j<=12;j++){
					if((i==x && j==y || i==x && j==y+1) && (i==ball_x && j==ball_y) == false){
						printf("=");
					}else if(i==ball_x && j==ball_y){
						printf("o");
					}else if(map[i][j] == 48){
						map[i][j] = '.';
						printf("."); 
					}else{
						printf("%c", map[i][j]);
					}if(map[i][j] >= 49 && map[i][j] <= 57){
							nums ++;
					}
				}
				printf("\n");
			}printf("score:%d\n", score);
			 printf("fps:%d\n", fps);	
				  
			//判断死亡或胜利
			if (nums == 0 || ball_x == 7){
				alive = false;
			} 
		}
	}if (nums){
		printf("GAME OVER");
	} else {
		printf("YOU WIN!");
	}Sleep(2000);
}

