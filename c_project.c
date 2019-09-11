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
           printf(" ***���� ��Ȱ ����� ���α׷�***\n\n");
           printf(" 1.���� �߰� \n 2.�ð�ǥ ��ȸ \n 3.���� ���� \n 4.���� ����\n 5.�ð�ǥ �޸������� ���\n 6.������ ���������� �����ұ�?\n "); 
           printf("7.����(����)�߰� \n 8.��������\n 9.�������\n 10.����\n\n") ;
		   printf(" �޴� �Է� : ");
           scanf("%d", &menu); 
           
           switch(menu)
           {
              case 1: 
                   {                   
				    if (count<N)
                       {
                          members[count]=add_member();
                          count++;
                          printf("������ �߰��Ǿ����ϴ�. \n");
                       }
                       else
                          printf("�ִ� ������ �ʰ��Ͽ����ϴ�. \n"); 
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
                       
					   printf("��������� �Է�\n");
					 
					   scanf("%s",class);
					   result=delete_member(class,members,count);
                   		
                   		if(result >=0)
                   		{
                   			printf("���������� ���� �Ǿ����ϴ�.\n");
                   			count--;
                   			
						   }	
						   else printf("������ ������ �����ϴ�.");
						   
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
					   
					   
					   printf("������ ������Է�\n"); 
						scanf("%s",class);
						result =update_member(class,members,count);
						
						if(result >=0)
						printf("���������� �����Ǿ����ϴ�\n");
						else
						printf("������ ������ �����ϴ� \n");
					}
					else printf("�Էµ� ������ �����ϴ�\n");
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
                          printf("�ִ� ������ �ʰ��Ͽ����ϴ�. \n"); 
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
                      printf("�߸��� �Է��Դϴ�.\n");                       
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
   
   printf("�����  :"); scanf("%s", ptr->class);
   printf("������  :"); scanf("%s", ptr->professor);
   printf("���   :"); scanf("%s", ptr->location);   
   printf("�ð� :"); scanf("%s", ptr->time);
   printf("������?");scanf("%d",&ptr->grade);
   return ptr;         
}

void print_members(CLASS *members[], int count)
{
   int i;
   
   if (count > 0)
   {
      printf(" �����   \t ������ \t ��� \t       �ð�  \t   ����\n");
      printf(" -----------------------------------------------------------------\n");
      for (i=0; i<count; i++)
         printf("%-5s \t %-9s \t %-13s\t %s\t   %d\n", members[i]->class,  members[i]->professor, members[i]->location, members[i]->time,members[i]->grade);   
   }    
   else
       printf("��ϵ� ������ �����ϴ�.\n"); 
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
			printf("������:(%s)=>",members[i]->professor);scanf("%s",members[i]->professor);
			printf("���:(%s)=>",members[i]->location);scanf("%s",members[i]->location);
			printf("�ð�:(%s)=>",members[i]->time);scanf("%s",members[i]->time);
		    printf("����:(%d)=>",members[i]->grade);scanf("%d",&members[i]->grade);
		    
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
      printf(" �����   \t ������ \t ��� \t �ð�\n");
      fprintf(fp, "�����   \t ������ \t ��� \t �ð�\n");

      printf(" -------------------------------------------------\n");
    fprintf(fp, "------------------------------------------------------\n");
      for (i=0; i<count; i++)
       {
		  printf("%-5s \t %-9s \t %-13s \t %s\n", members[i]->class,  members[i]->professor, members[i]->location, members[i]->time); 
		fprintf(fp, "%-5s \t %-9s \t %-13s \t %s\n", members[i]->class,  members[i]->professor, members[i]->location, members[i]->time);  }
   printf("����� �Ϸ� �Ǿ����ϴ�\n");}    
   else
    {
	    printf("��ϵ� ������ �����ϴ�.\n"); 
      fprintf(fp, "��ϵ� ������ �����ϴ�\n");  }
 fclose(fp); 
}

void random(CLASS *members[],int count)
{
int random;
 
 	if(count==0)
	{
	printf("�� ���� �Էµ��� �ʾ� ��÷�� �Ҽ� �����ϴ�\n");
    }
		
	else{	 		printf("�ð�ǥ�� �Էµ� ������ �������� �Ѱ����� ���õ˴ϴ�.\n");
					srand(time(NULL));
 					random=(rand()%count+1)-1;
					printf("���� �ؾ� �� ����: %s\n",members[random]->class);	 
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
	printf("������ ������ �ִ� ������ �Է����ּ���.\n");	
	scanf("%s",ptr2->class);
	fflush(stdin);
	printf("���� �ϼ��� �Է����ּ���\n");
	scanf("%d",&ptr2->day);
	printf("����Ϸ�\n");	
}	
	else
	{
	printf("�Էµ� ������ ���� ����� ������� �ʽ��ϴ�.\n ������ �Է� ���ּ���.");	
	scanf("%s",ptr2->class);
	fflush(stdin);
	printf("���� �ϼ��� �Է����ּ���\n");
	scanf("%d",&ptr2->day);
	printf("����Ϸ�\n");		
	}
	
	return ptr2;
}

//�Լ���ü �����ʿ� 
void print_homework(HOME *homework2[], int count,int count2)
{
   int i,pass,temp;
   
   //���� ���Ѽ����� �������� 
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
    
  
   	
      printf(" �����(����)\t   �����ϼ� \n");
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
	printf("%d.%s�� ������?(�빮�ڷ� �Է��ϼ���.))\n",i+1,members[i]->class);
	scanf("%s",grade[i]);
	printf("����� �Է��� ������ %s\n",grade[i]);
		
}

//���ڿ� �� 
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
			printf("���̼�����:%d ����:%.2lf",total2,total);
	}

else 
printf("�Էµ� ������ �����ϴ�\n");

}
