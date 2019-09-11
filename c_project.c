#include <stdio.h>
#include <stdlib.h>
#define N 100
#include <time.h>
#include <string.h>

typedef struct class
{
    char class[20];
    char location[20];
    char professor[20];
    char time[20];
    int grade;
	int day;
	    
}CLASS;

typedef struct home
{
    char class[20];
    int day;    
}HOME;

CLASS* add_member();
void print_members(CLASS *members[], int count);
int update_member(char class[],CLASS *members[],int count);
int delete_member(char class[], CLASS *members[],int count);
void print_out(CLASS *members[], int count);
void random(CLASS *members[],int count);
HOME* homework(CLASS *members[],int count,HOME *homework2[],int count2 );
void print_homework(HOME *homework2[], int count,int count2);
void print_grade(int count,CLASS *members[]);

int main(int argc, char *argv[])
{	srand(time(NULL));
  FILE *fp;
 fp=fopen("timetable.txt","w");

    int menu,count=0,count2=0,j;  
    CLASS *members[N];
    HOME *homework2[N];
    
    do
    {
           printf(" ***대학 생활 도우미 프로그램***\n\n");
           printf(" 1.수업 추가 \n 2.시간표 조회 \n 3.수업 삭제 \n 4.수업 수정\n 5.시간표 메모장으로 출력\n 6.오늘은 무슨과목을 공부할까?\n "); 
           printf("7.과제(할일)추가 \n 8.과제보기\n 9.학점계산\n 10.종료\n\n") ;
		   printf(" 메뉴 입력 : ");
           scanf("%d", &menu); 
           
           switch(menu)
           {
              case 1: 
                   {                   
				    if (count<N)
                       {
                          members[count]=add_member();
                          count++;
                          printf("수업이 추가되었습니다. \n");
                       }
                       else
                          printf("최대 수업을 초과하였습니다. \n"); 
                   }
                   break;
                   
              case 2:
                   {	
                       print_members(members, count);
                   }
                   break;
                   
              case 3:                   
                   {
                       int result,i;
                       char class[6];
                       
                       
                        for(i=0;i<count;i++)
					{
						printf("%d.%s\n",i+1,members[i]->class);
					}	
                       
					   printf("삭제과목명 입력\n");
					 
					   scanf("%s",class);
					   result=delete_member(class,members,count);
                   		
                   		if(result >=0)
                   		{
                   			printf("수업정보가 삭제 되었습니다.\n");
                   			count--;
                   			
						   }	
						   else printf("삭제할 수업이 없습니다.");
						   
				   }
                   break;
                   
              case 4:                   
                   {
                   	int result,i;
					char class[6];
					
                       if(count>0)
					   {
					   
					      for(i=0;i<count;i++)
					{
						printf("%d.%s\n",i+1,members[i]->class);
					}	
					   
					   
					   printf("수정할 과목명입력\n"); 
						scanf("%s",class);
						result =update_member(class,members,count);
						
						if(result >=0)
						printf("수업정보가 수정되었습니다\n");
						else
						printf("수정할 수업이 없습니다 \n");
					}
					else printf("입력된 수업이 없습니다\n");
                   }
                   break;
                   
    			case 5:{ 
					print_out(members,count);					
						}break;
				
				case 6:{
					random(members,count);									
						}break;
    																	
				case 7:{
					 
			 		 if (count2<N)
                       {
                          homework2[count2]= homework(members,count,homework2,count2);
                          count2++;

                       }
                       else
                          printf("최대 과제을 초과하였습니다. \n"); 
                   }
                   break;
                  		 	
				 case 8:
			 	 {	
                     	  print_homework(homework2,count,count2);
                   }break;
					
				case 9:{
							print_grade(count,members); 
				}	break;
				
				case 10:
					  return 0;
                   break;
					 
					 
			  default:
                      printf("잘못된 입력입니다.\n");                       
           }           
           fflush(stdin);
           getch();
           system("cls");
           
    } while (menu!=10);
    
  fclose(fp); 
  system("PAUSE");	
  return 0;
}

CLASS* add_member()
{
   CLASS *ptr = (CLASS *)malloc(sizeof(CLASS));
   
   printf("과목명  :"); scanf("%s", ptr->class);
   printf("교수님  :"); scanf("%s", ptr->professor);
   printf("장소   :"); scanf("%s", ptr->location);   
   printf("시간 :"); scanf("%s", ptr->time);
   printf("몇학점?");scanf("%d",&ptr->grade);
   return ptr;         
}

void print_members(CLASS *members[], int count)
{
   int i;
   
   if (count > 0)
   {
      printf(" 과목명   \t 교수님 \t 장소 \t       시간  \t   학점\n");
      printf(" -----------------------------------------------------------------\n");
      for (i=0; i<count; i++)
         printf("%-5s \t %-9s \t %-13s\t %s\t   %d\n", members[i]->class,  members[i]->professor, members[i]->location, members[i]->time,members[i]->grade);   
   }    
   else
       printf("등록된 수업이 없습니다.\n"); 
}

int delete_member(char class[], CLASS *members[],int count)
{	
	int i,j;
	for(i=0;i<count;i++)
	{
		if(strcmp(members[i]->class,class)==0)
		{
			free(members[i]);
			for(j=i;j<count;j++)
			{
			members[j]=members[j+1];
			}
			return i;
		}				
	}
	return -1;
}

int update_member(char class[],CLASS *members[],int count)
{
	int i,j;
	CLASS *temp;
			
	for(i=0;i<count;i++)
	{
		if(strcmp(members[i]->class,class)==0)
		{
			printf("교수명:(%s)=>",members[i]->professor);scanf("%s",members[i]->professor);
			printf("장소:(%s)=>",members[i]->location);scanf("%s",members[i]->location);
			printf("시간:(%s)=>",members[i]->time);scanf("%s",members[i]->time);
		    printf("학점:(%d)=>",members[i]->grade);scanf("%d",&members[i]->grade);
		    
			return i;
		}
	}
}
	

void print_out(CLASS *members[], int count)
{FILE *fp;
 fp=fopen("timetable.txt","w");
   int i;
   
   if (count > 0)
   {
      printf(" 과목명   \t 교수님 \t 장소 \t 시간\n");
      fprintf(fp, "과목명   \t 교수님 \t 장소 \t 시간\n");

      printf(" -------------------------------------------------\n");
    fprintf(fp, "------------------------------------------------------\n");
      for (i=0; i<count; i++)
       {
		  printf("%-5s \t %-9s \t %-13s \t %s\n", members[i]->class,  members[i]->professor, members[i]->location, members[i]->time); 
		fprintf(fp, "%-5s \t %-9s \t %-13s \t %s\n", members[i]->class,  members[i]->professor, members[i]->location, members[i]->time);  }
   printf("출력이 완료 되었습니다\n");}    
   else
    {
	    printf("등록된 수업이 없습니다.\n"); 
      fprintf(fp, "등록된 수업이 없습니다\n");  }
 fclose(fp); 
}

void random(CLASS *members[],int count)
{
int random;
 
 	if(count==0)
	{
	printf("한 과목도 입력되지 않아 추첨을 할수 없습니다\n");
    }
		
	else{	 		printf("시간표에 입력된 수업중 랜덤으로 한과목이 선택됩니다.\n");
					srand(time(NULL));
 					random=(rand()%count+1)-1;
					printf("공부 해야 할 과목: %s\n",members[random]->class);	 
	}
}

HOME* homework(CLASS *members[],int count,HOME *homework2[],int count2 )

{	 CLASS *ptr = (CLASS *)malloc(sizeof(CLASS));
 	HOME *ptr2 = (HOME *)malloc(sizeof(HOME));
 	
	int i,j,number=0;
	
	if(count!=0)
	{	
	for(i=0;i<count;i++)
	{
	printf("%d.%s\n",i+1,members[i]->class);
}	
	printf("다음중 과제가 있는 과목을 입력해주세요.\n");	
	scanf("%s",ptr2->class);
	fflush(stdin);
	printf("남은 일수를 입력해주세요\n");
	scanf("%d",&ptr2->day);
	printf("저장완료\n");	
}	
	else
	{
	printf("입력된 수업이 없어 목록을 출력하지 않습니다.\n 할일을 입력 해주세요.");	
	scanf("%s",ptr2->class);
	fflush(stdin);
	printf("남은 일수를 입력해주세요\n");
	scanf("%d",&ptr2->day);
	printf("저장완료\n");		
	}
	
	return ptr2;
}

//함수전체 수정필요 
void print_homework(HOME *homework2[], int count,int count2)
{
   int i,pass,temp;
   
   //남은 기한순으로 버블정렬 
  	 for (pass=1; pass<count2; pass++)
  	{
	   
		 for (i=0; i<count2-pass; i++)
 	{
	 if (homework2[i]->day>homework2[i+1]->day)
	 {
 			temp=homework2[i];
 			homework2[i]=homework2[i+1];
			homework2[i+1]=temp;
		 }	 
		}	
		}
    
  
   	
      printf(" 과목명(할일)\t   남은일수 \n");
      printf(" -------------------------------------------------\n");
      for (i=0; i<count2; i++)
         printf("%-5s\t %-9d\n",homework2[i]->class, homework2[i]->day);   
  
}

void print_grade(int count,CLASS *members[])
{
char grade[20][20];
int total2=0;
int i;
double grade2[20],total=0;
char grade3[20][10]={"A+","A","B+","B","C+","C","D+","D","F"};

if(count>0) 
{

for(i=0;i<count;i++)
{		
	printf("%d.%s의 학점은?(대문자로 입력하세요.))\n",i+1,members[i]->class);
	scanf("%s",grade[i]);
	printf("당신이 입력한 학점은 %s\n",grade[i]);
		
}

//문자열 비교 
		for(i=0;i<count;i++)
	{	
		if(strcmp(grade[i],grade3[0])==0)
		{grade2[i]=4.5;
		} 
		else if(strcmp(grade[i],grade3[1])==0)	
		{grade2[i]=4.0;
		}
		else if(strcmp(grade[i],grade3[2])==0)
		{grade2[i]=3.5;
		}
		else if(strcmp(grade[i],grade3[3])==0)
		{grade2[i]=3.0;
		}
		else if(strcmp(grade[i],grade3[4])==0)
		{grade2[i]=2.5;	
		}
		else if(strcmp(grade[i],grade3[5])==0)
		{grade2[i]=2.0;	
		}
		else if(strcmp(grade[i],grade3[6])==0)
		{grade2[i]=1.5;
		}
		else if(strcmp(grade[i],grade3[7])==0)
		{grade2[i]=1.0;		
		}
		else if(strcmp(grade[i],grade3[8])==0)
		{grade2[i]=0.0;
		}	
		}
		
	for(i=0;i<count;i++)
    { total2=total2+members[i]->grade;
	  grade2[i]=grade2[i]*members[i]->grade;
	}

	for(i=0;i<count;i++)
	{ total=total+grade2[i];
	}
	total=total/(double)total2;
			printf("총이수학점:%d 성적:%.2lf",total2,total);
	}

else 
printf("입력된 수업이 없습니다\n");

}
