#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

#define ROW_MAX 30
#define COL_MAX 30
#define HELP 13404      // hash value for \h
#define LOAD 13916      // hash value for \l
#define SAVE 14812      // hash value for \s
#define DESIGN 12892    // hash value for \d
#define GENERATE 13276  // hash value for \g
#define RUN 14684       // hash value for \r
#define EXIT 13020      // hash value for \e
#define QUIT 14556      // hash value for \q
#define PRINT 14428     // hash value for \p
#define MENU 247182061  // hash value for menu   
#define END 1652581     // hash value for end

void welcome();
void print_help();
long hash(char * a);
void getInput(char * buf);
void generate_map(int *map);
void print_map(int *map,int row,int col);
void design_map(int *map,int *r,int *c);
int count_aliveNeighbors(int *map,int row,int col,int x, int y);
void update_map(int *map,int row,int col);
void game_start(int *map,int row,int col);
void automatic_run(int *map,int row,int col);
void single_step(int *map,int row,int col);
void load_map(int *map,int *r,int *c); 
void save_map(int *map,int row,int col);

int main(){
    char buf[1024];
    int end_order=1;
    int map[ROW_MAX][COL_MAX];
    int row=ROW_MAX,col=COL_MAX;
    int *r=&row,*c=&col,*m=&map[0][0];
    generate_map(*map);
    welcome();
    while(end_order){
        // Get the input string.
        printf("Please input the command: \n");
        getInput(buf);
        // The hash function is to convert a string into a hash value.
        long hashCode = hash(buf);
        system("cls");
        switch(hashCode){
        	case HELP:
        		print_help();
		    	break;
		    case PRINT:
	        	printf("***打印当前地图***\n");
                print_map(m,row,col);
	        	break;
	        case LOAD:
		        printf("***导入地图***\n");
		        load_map(m,r,c); 
		        break;
	        case SAVE:
	        	printf("****保存地图****\n");
	        	save_map(m,row,col);
	        	break;
	        case DESIGN:
		    	printf("***进入地图设计模式***\n");
                design_map(m,r,c);
                welcome();
		        break;
	        case EXIT:
	        	printf("**请在地图设计模式中使用此指令！**\n");
	        	break;
	        case GENERATE:
	        	printf("**请在进行生命游戏中使用此指令！**\n");
	        	break;
	        case RUN:
		        printf("***开始生命游戏***\n");
                game_start(m,row,col);
		    	break;
	        case QUIT:
	        	printf("**请在进行生命游戏中使用此指令！**\n"); 
	        	break;
	        case MENU:
	        	welcome();
	        	break;
	        case END:
	        	printf("***退出游戏***\n");
                end_order=0;
	        	break;
	       default:
	        	printf("error\n");
	        	break;
		}
    }
    return 0;
}

void welcome(){
	puts("*********************************\n*********************************");
	puts("\n       生    命   游    戏\n");
    puts("\n         欢迎来到生命游戏        \n");
    puts(" 在这里你将体验到元胞自动机的快乐\n");
    puts("\n           准备好了吗");
	puts("\n*********************************\n*********************************");
	printf("\t[\\r]\t开始生命游戏\n");
	printf("\t[\\l]\t导入地图\n");
	printf("\t[\\p]\t打印当前地图\n");
	printf("\t[\\d]\t进入地图设计模式\n");
	printf("\t[\\h]\t打印命令提示\n");
	printf("\t[end]\t退出游戏\n");
}
void print_help(){
    printf("\t[\\h]\t打印命令提示\n");
	printf("\t[\\p]\t打印当前地图\n");
 	printf("\t[\\l]\t导入地图\n");
    printf("\t[\\s]\t保存地图\n");
	printf("\t[\\d]\t进入地图设计模式\n");
	printf("\t[\\q]\t退出地图设计模式\n");
	printf("\t[\\g]\t生成下一代生命\n");
    printf("\t[\\r]\t开始生命游戏\n");
	printf("\t[\\e]\t停止生命游戏\n");
	printf("\t[menu]\t返回主菜单\n");
	printf("\t[end]\t退出游戏\n");
}
long hash(char * a){
    long result = 0;
	int index = 0;
    for(; index < strlen(a); index++){
        result +=  a[index] * pow(128,index);
    }
    return result;
}

void getInput(char * buf){
    fgets(buf,1024,stdin);
    buf[strlen(buf) - 1] = '\0';
}

void generate_map(int *map){
    int i,j;
    for(i=0;i<ROW_MAX;i++){
        for(j=0;j<COL_MAX;j++){
           *(map+i*COL_MAX+j)=0;
        }
    }
}

void print_map(int *map,int row,int col){
    int i,j;
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            printf(*(map+i*COL_MAX+j)>0?"■":"□");
        }
        printf("\n");
    }
}

void design_map(int *map,int *r,int *c){ 
    float i,j;   char buf;
    printf("请设定地图的行数(1~%d):\n",ROW_MAX);
    while(1){
        printf("row=");
        scanf("%f",&i);  buf=getchar();  fflush(stdin);
        if(i<1|i>ROW_MAX|i-(int)i>0|buf!='\n') printf("输入不合法，请重新输入！\n");
        else break;
    }   *r=(int)i;
    printf("请设定地图的列数(1~%d):\n",COL_MAX);
    while(1){
        printf("col=");
        scanf("%f",&j);  buf=getchar();  fflush(stdin);
        if(j<1|j>COL_MAX|j-(int)j>0|buf!='\n') printf("输入不合法，请重新输入！\n");
        else   break;
   }    *c=(int)j;
    int row=*r,col=*c;
	generate_map(map);
    print_map(map,row,col);
    do{
        printf("请设置活细胞位置:\n");
        printf("(Tips: 也可输入一个活细胞的位置以使之变为死细胞)\n"); 
        while(1){
            printf("the row of the cell is:  ");
            scanf("%f",&i);  buf=getchar();  fflush(stdin);
            if(i<0|i>row-1|i-(int)i>0|buf!='\n') printf("输入不合法，请重新输入！\n");
          else break;
        }
        while(1){
            printf("the col of the cell is:  ");
            scanf("%f",&j);  buf=getchar();  fflush(stdin);
            if(j<0|j>col-1|j-(int)j>0|buf!='\n') printf("输入不合法，请重新输入！\n");
           else break;
        }  
    *(map+(int)i*COL_MAX+(int)j)=*(map+(int)i*COL_MAX+(int)j)==0?1:0;
    print_map(map,row,col);
    printf("(可以选择输入\\q退出地图设计模式，否则将设置更多活细胞)\n");
    char buf[5];
    fgets(buf,5,stdin);
    if(strncmp(buf, "\\q\n", strlen("\\q\n"))==0){
        printf("Tips：\n您还未保存地图！\n保存地图请输入\\s,否则将该地图将不会保存到本地！\n");
        fgets(buf,5,stdin);
        if(strncmp(buf, "\\s\n", strlen("\\s\n"))==0){
			save_map(map,row,col);
        }       
    break;
    }    
    }while(1);
    system("cls");
}

int count_aliveNeighbors(int *map,int row,int col,int x, int y){
    int count=0,m,n;
		for(m=-1;m<2;m++){
			for(n=-1;n<2;n++){
				if(!(m==0&&n==0))
				if(x+m>=0&&x+m<row&&y+n>=0&&y+n<col&&*(map+(x+m)*COL_MAX+(y+n))==1) count++;
			}
		}
	return count;
}

void update_map(int *map,int row,int col){
    int aliveNeighbors[row][col];
    int i,j;
    for(i = 0; i < row; i++){
    	for(j = 0; j < col; j++){
        	aliveNeighbors[i][j] = count_aliveNeighbors(map, row, col, i, j);
		}
	}      
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
        	if(*(map+i*COL_MAX+j)==1){
				if(aliveNeighbors[i][j]<2||aliveNeighbors[i][j]>3)   *(map+i*COL_MAX+j)=0;
				if(aliveNeighbors[i][j]==2||aliveNeighbors[i][j]==3) *(map+i*COL_MAX+j)=1;
			}
			else{
				if(aliveNeighbors[i][j]==3)  *(map+i*COL_MAX+j)=1;
				else  *(map+i*COL_MAX+j)=0;
			}
		} 
	}
}

void game_start(int *map,int row,int col){
    print_map(map,row,col);
    printf("请选择运行模式：\n自动运行···1/单步运行···2/退出运行模式···3\n");
    float order;  char buf;
    while(1){
        scanf("%f",&order);  buf=getchar();  fflush(stdin);
        if((order==1.0|order==2.0|order==3.0)&&buf=='\n') break;
        else printf("输入不合法，请重新输入！\n");
    }
    switch((int)order){
        case 1:
            automatic_run(map,row,col);
            break;
        case 2:
        	single_step(map,row,col);
            break;
		case 3:
			break; 
        default: break;
    }
}

void automatic_run(int *map,int row,int col){
	int start=1;
	while(start){
		fflush(stdin);
		while(!kbhit()){
			system("cls");
        	int i;
        	for(i=0;i<row/2-4;i++){
            	printf("*");
        	}
        	printf("紧张?生命游戏?刺激");
        	for(i=0;i<row/2-4;i++){
            	printf("*");
        	}
        	printf("\n(按任意键暂停)\n");
        	update_map(map,row,col);
        	print_map(map,row,col);
        	Sleep(2000);
    	}   getch();
    	printf("Tips: 按回车键继续自动运行，输入\\e结束自动运行模式\n");
    	while(1){
			fflush(stdin); 
    		char order[5];
    		fgets(order,5,stdin);
        	if(strncmp(order, "\\e\n", strlen("\\e\n"))==0) { start=0;  break; }
    	   	else if(strcmp(order, "\n")==0) break;
    	        else printf("输入不合法，请重新输入！\n");
    	}
	}
    system("cls");
}

void single_step(int *map,int row,int col){
	system("cls");	int start=1;
	print_map(map,row,col);
	while(start){
		fflush(stdin);
		printf("Tips:\n输入\\g更新细胞图\n输入\\e结束单步运行模式\n");
		while(1){
			fflush(stdin); 
    		char order[5];
    		fgets(order,5,stdin);
        	if(strncmp(order, "\\e\n", strlen("\\e\n"))==0) { start=0;  break; }
    		else if(strncmp(order, "\\g\n", strlen("\\g\n"))==0) break;
    	        else printf("输入不合法，请重新输入！\n");
    	}	system("cls");
    	int i;
        for(i=0;i<row/2-5;i++){
           	printf("*");
    	}
    	printf("*紧张?生命游戏?刺激*");
		for(i=0;i<row/2-5;i++){
    		printf("*");
		}
		printf("\n");
		update_map(map,row,col);
        print_map(map,row,col); 
	}
	system("cls");
}

void load_map(int *map,int *r,int *c){
	char name[100];
	int row=*r,col=*c;
	printf("请输入文件名：\n"); 
	scanf("%s",&name);  fflush(stdin);
	FILE *fp=fopen(name,"r");
	if(fp==NULL){
		printf("读取失败，请输入合法的文件名！\n"); goto loop;
	}	
	fscanf(fp,"%d",r);  fscanf(fp,"%d",c);
	if(*r<0|*c<0|*r>=ROW_MAX|*c>=COL_MAX){
		printf("该文件格式错误，行数或列数不符合规定，无法正常读取！\n"); 
		*r=row; *c=col;  
		goto loop;
	}
	generate_map(map);
	int i,j;
	for(i=0;i<*r;i++){
		for(j=0;j<*c;j++){
			if(fscanf(fp,"%d",map+i*COL_MAX+j)==EOF){
				printf("该文件格式错误，缺少相关数据，无法正常读取！\n"); goto loop; 
			}
			if(*(map+i*COL_MAX+j)!=1&&*(map+i*COL_MAX+j)!=0){
				printf("该文件格式错误，细胞数据不符合规定，无法正常读取！\n"); goto loop;	
			} 
		}
	}
	if(fscanf(fp,"%d",&i)!=EOF){
		printf("该文件格式错误，检测到有多余数据，无法正常读取！\n"); goto loop; 
	} 
	print_map(map,*r,*c);
	loop: fclose(fp);
}

void save_map(int *map,int row,int col){
	char name[100];
	FILE *fp;
	printf("请输入文件名：\n"); 
	while(1){
		scanf("%s",&name);  fflush(stdin);
		fp=fopen(name,"r");
		if(fp==NULL){
			fp=fopen(name,"w"); break;
		}
		else printf("该文件已存在,请重新输入文件名：\n");	
	}
	fprintf(fp,"%d ",row);  	
	fprintf(fp,"%d\n",row);	
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			fprintf(fp,"%d ",*(map+i*COL_MAX+j)); 
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	printf("保存成功！\n");
	Sleep(1000); 
}
