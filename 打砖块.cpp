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
int y = 5, x = 7;//���ӵ����� 
int ball_y = 5, ball_x = 6;//������� 

int main(){
	
	int score = 0;//���� 
	int clocktime = clock();//����ˢ���� 
	int fps;
	bool alive = true;//�ж��Ƿ񻹴�� 
	int press;//�����ƶ���ȴʱ�� 
	int dir = 3;// 1^\  2^/  3v\  4v/ ���� 
	bool ballmove = true;//���´��Ƿ��ƶ� 
	int nums; //�����ж��Ƿ���ש��ʣ�� 
	int balltime = clock();//���ƶ�ʱ���� 
	bool ballif = true;//ת������ж�һ�� 
	
	//����ש��
	srand(std::time(0));//�������������
	for(int o=3; o>0; o--){
		for(int p=1; p<11; p++){
			map[o][p] = rand()%9+49;
		}
	} 
	
	while (alive){
		
		//���ư����ƶ� 
		if (KEY_DOWN('A') && y > 1 && clock() - press >= 100){//���� 
			y -= 1;
			press = clock();
		} else if (KEY_DOWN('D') && y < 9 && clock() - press >= 100){//���� 
			y += 1;
			press = clock();
		}
		
		//���ƶ�
		if (clock() - balltime >= 500) {//��ÿ��0.5s�ƶ�һ�� 
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
						srand(std::time(0));//�������������
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
						srand(std::time(0));//�������������
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
						srand(std::time(0));//�������������
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
						srand(std::time(0));//�������������
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
		
		if (clock() - clocktime >= 50){//��20ˢ����
			fps = 1000 / (clock() - clocktime); 
			clocktime = clock();
			
			//�������
			nums = 0;//�����ж��Ƿ���ש��ʣ�� 
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
				  
			//�ж�������ʤ��
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

