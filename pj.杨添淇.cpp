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
	        	printf("***��ӡ��ǰ��ͼ***\n");
                print_map(m,row,col);
	        	break;
	        case LOAD:
		        printf("***�����ͼ***\n");
		        load_map(m,r,c); 
		        break;
	        case SAVE:
	        	printf("****�����ͼ****\n");
	        	save_map(m,row,col);
	        	break;
	        case DESIGN:
		    	printf("***�����ͼ���ģʽ***\n");
                design_map(m,r,c);
                welcome();
		        break;
	        case EXIT:
	        	printf("**���ڵ�ͼ���ģʽ��ʹ�ô�ָ�**\n");
	        	break;
	        case GENERATE:
	        	printf("**���ڽ���������Ϸ��ʹ�ô�ָ�**\n");
	        	break;
	        case RUN:
		        printf("***��ʼ������Ϸ***\n");
                game_start(m,row,col);
		    	break;
	        case QUIT:
	        	printf("**���ڽ���������Ϸ��ʹ�ô�ָ�**\n"); 
	        	break;
	        case MENU:
	        	welcome();
	        	break;
	        case END:
	        	printf("***�˳���Ϸ***\n");
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
	puts("\n       ��    ��   ��    Ϸ\n");
    puts("\n         ��ӭ����������Ϸ        \n");
    puts(" �������㽫���鵽Ԫ���Զ����Ŀ���\n");
    puts("\n           ׼��������");
	puts("\n*********************************\n*********************************");
	printf("\t[\\r]\t��ʼ������Ϸ\n");
	printf("\t[\\l]\t�����ͼ\n");
	printf("\t[\\p]\t��ӡ��ǰ��ͼ\n");
	printf("\t[\\d]\t�����ͼ���ģʽ\n");
	printf("\t[\\h]\t��ӡ������ʾ\n");
	printf("\t[end]\t�˳���Ϸ\n");
}
void print_help(){
    printf("\t[\\h]\t��ӡ������ʾ\n");
	printf("\t[\\p]\t��ӡ��ǰ��ͼ\n");
 	printf("\t[\\l]\t�����ͼ\n");
    printf("\t[\\s]\t�����ͼ\n");
	printf("\t[\\d]\t�����ͼ���ģʽ\n");
	printf("\t[\\q]\t�˳���ͼ���ģʽ\n");
	printf("\t[\\g]\t������һ������\n");
    printf("\t[\\r]\t��ʼ������Ϸ\n");
	printf("\t[\\e]\tֹͣ������Ϸ\n");
	printf("\t[menu]\t�������˵�\n");
	printf("\t[end]\t�˳���Ϸ\n");
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
            printf(*(map+i*COL_MAX+j)>0?"��":"��");
        }
        printf("\n");
    }
}

void design_map(int *map,int *r,int *c){ 
    float i,j;   char buf;
    printf("���趨��ͼ������(1~%d):\n",ROW_MAX);
    while(1){
        printf("row=");
        scanf("%f",&i);  buf=getchar();  fflush(stdin);
        if(i<1|i>ROW_MAX|i-(int)i>0|buf!='\n') printf("���벻�Ϸ������������룡\n");
        else break;
    }   *r=(int)i;
    printf("���趨��ͼ������(1~%d):\n",COL_MAX);
    while(1){
        printf("col=");
        scanf("%f",&j);  buf=getchar();  fflush(stdin);
        if(j<1|j>COL_MAX|j-(int)j>0|buf!='\n') printf("���벻�Ϸ������������룡\n");
        else   break;
   }    *c=(int)j;
    int row=*r,col=*c;
	generate_map(map);
    print_map(map,row,col);
    do{
        printf("�����û�ϸ��λ��:\n");
        printf("(Tips: Ҳ������һ����ϸ����λ����ʹ֮��Ϊ��ϸ��)\n"); 
        while(1){
            printf("the row of the cell is:  ");
            scanf("%f",&i);  buf=getchar();  fflush(stdin);
            if(i<0|i>row-1|i-(int)i>0|buf!='\n') printf("���벻�Ϸ������������룡\n");
          else break;
        }
        while(1){
            printf("the col of the cell is:  ");
            scanf("%f",&j);  buf=getchar();  fflush(stdin);
            if(j<0|j>col-1|j-(int)j>0|buf!='\n') printf("���벻�Ϸ������������룡\n");
           else break;
        }  
    *(map+(int)i*COL_MAX+(int)j)=*(map+(int)i*COL_MAX+(int)j)==0?1:0;
    print_map(map,row,col);
    printf("(����ѡ������\\q�˳���ͼ���ģʽ���������ø����ϸ��)\n");
    char buf[5];
    fgets(buf,5,stdin);
    if(strncmp(buf, "\\q\n", strlen("\\q\n"))==0){
        printf("Tips��\n����δ�����ͼ��\n�����ͼ������\\s,���򽫸õ�ͼ�����ᱣ�浽���أ�\n");
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
    printf("��ѡ������ģʽ��\n�Զ����С�����1/�������С�����2/�˳�����ģʽ������3\n");
    float order;  char buf;
    while(1){
        scanf("%f",&order);  buf=getchar();  fflush(stdin);
        if((order==1.0|order==2.0|order==3.0)&&buf=='\n') break;
        else printf("���벻�Ϸ������������룡\n");
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
        	printf("����?������Ϸ?�̼�");
        	for(i=0;i<row/2-4;i++){
            	printf("*");
        	}
        	printf("\n(���������ͣ)\n");
        	update_map(map,row,col);
        	print_map(map,row,col);
        	Sleep(2000);
    	}   getch();
    	printf("Tips: ���س��������Զ����У�����\\e�����Զ�����ģʽ\n");
    	while(1){
			fflush(stdin); 
    		char order[5];
    		fgets(order,5,stdin);
        	if(strncmp(order, "\\e\n", strlen("\\e\n"))==0) { start=0;  break; }
    	   	else if(strcmp(order, "\n")==0) break;
    	        else printf("���벻�Ϸ������������룡\n");
    	}
	}
    system("cls");
}

void single_step(int *map,int row,int col){
	system("cls");	int start=1;
	print_map(map,row,col);
	while(start){
		fflush(stdin);
		printf("Tips:\n����\\g����ϸ��ͼ\n����\\e������������ģʽ\n");
		while(1){
			fflush(stdin); 
    		char order[5];
    		fgets(order,5,stdin);
        	if(strncmp(order, "\\e\n", strlen("\\e\n"))==0) { start=0;  break; }
    		else if(strncmp(order, "\\g\n", strlen("\\g\n"))==0) break;
    	        else printf("���벻�Ϸ������������룡\n");
    	}	system("cls");
    	int i;
        for(i=0;i<row/2-5;i++){
           	printf("*");
    	}
    	printf("*����?������Ϸ?�̼�*");
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
	printf("�������ļ�����\n"); 
	scanf("%s",&name);  fflush(stdin);
	FILE *fp=fopen(name,"r");
	if(fp==NULL){
		printf("��ȡʧ�ܣ�������Ϸ����ļ�����\n"); goto loop;
	}	
	fscanf(fp,"%d",r);  fscanf(fp,"%d",c);
	if(*r<0|*c<0|*r>=ROW_MAX|*c>=COL_MAX){
		printf("���ļ���ʽ�������������������Ϲ涨���޷�������ȡ��\n"); 
		*r=row; *c=col;  
		goto loop;
	}
	generate_map(map);
	int i,j;
	for(i=0;i<*r;i++){
		for(j=0;j<*c;j++){
			if(fscanf(fp,"%d",map+i*COL_MAX+j)==EOF){
				printf("���ļ���ʽ����ȱ��������ݣ��޷�������ȡ��\n"); goto loop; 
			}
			if(*(map+i*COL_MAX+j)!=1&&*(map+i*COL_MAX+j)!=0){
				printf("���ļ���ʽ����ϸ�����ݲ����Ϲ涨���޷�������ȡ��\n"); goto loop;	
			} 
		}
	}
	if(fscanf(fp,"%d",&i)!=EOF){
		printf("���ļ���ʽ���󣬼�⵽�ж������ݣ��޷�������ȡ��\n"); goto loop; 
	} 
	print_map(map,*r,*c);
	loop: fclose(fp);
}

void save_map(int *map,int row,int col){
	char name[100];
	FILE *fp;
	printf("�������ļ�����\n"); 
	while(1){
		scanf("%s",&name);  fflush(stdin);
		fp=fopen(name,"r");
		if(fp==NULL){
			fp=fopen(name,"w"); break;
		}
		else printf("���ļ��Ѵ���,�����������ļ�����\n");	
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
	printf("����ɹ���\n");
	Sleep(1000); 
}
