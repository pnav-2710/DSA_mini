#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Linked List Creation
int num=0;
typedef struct queue
{
    int ind;
    char song[100];
    struct queue *prev;
    struct queue *next;
} player;
player *head;
player *last;
int inplaylist(char newsong[100])
{
    player *temp1 = head;
    while(temp1!=NULL)
    {
        if(strcmp(newsong,temp1->song)==0)
            return 1;
        else
            temp1 = temp1->next;
    }
    return 0;
}
//Adds song to the end of queue
void addsong(char newsong[100])
{
    if(inplaylist(newsong))
    {
        printf("Song is already in playlist\n");
    }
    else
    {
    if(num==0)
    {
        strcpy(head->song,newsong);
        head->ind = (num+1);
        num++;
        last = head;
    }
    else
    {
        player *new = (player *)malloc(sizeof(player));
        new->prev = NULL;
        new->next = NULL;
        strcpy(new->song,newsong);
        new->ind = (num+1);
        num++;
        new->prev = last;
        last->next = new;
        last = last->next;
    }
    }
}
//Deletes song from queue
void delsong(int n)
{
    player *temp = head;
    if(n==1)
    {
        head = head->next;
        free(temp);
        num--;
        int count = 1;
        player *temp1 = head;
        while (count <= num)
        {
            temp1->ind = count;
            temp1=temp1->next;
            count++;
        }
    }
    else if(n==num)
    {
        temp = last;
        last = last->prev;
        free(temp);
        num--;
        last->ind = num;
    }
    else
    {
        int count = 1;
        while(count<n)
        {
            temp = temp->next;
            count++;
        }
        player *temp1 = temp->prev;
        temp1->next= temp->next;
        temp->next->prev = temp1;
        free(temp);
        num--;
        player *temp2 = head;
        count = 1;
        while (count <= num)
        {
            temp2->ind = count;
            temp2=temp2->next;
            count++;
        }
    }
}
//Move a song from one position to another
void movesong(int a,int b)
{
    player *temp1=head;
    player *temp2=head;
    int c1 = 1;
    int c2 = 1;
    while(c1<a)
    {
        temp1=temp1->next;
        c1++;
    }
    while(c2<b)
    {
        temp2=temp2->next;
        c2++;
    }
    if(a==1)
    {
        if(b==num)
        {
            head = temp1->next;
            temp1->next->prev = NULL;
            temp2->next = temp1;
            temp1->prev = temp2;
            last = temp1;
            temp1->next = NULL;
        }
        else
        {
            head = temp1->next;
            temp1->next->prev = NULL;
            player *temp4 = temp2->next;
            temp4->prev = temp1;
            temp1->next = temp4;
            temp1->prev = temp2;
            temp2->next = temp1;
        }
    }
    else if(b==1)
    {
        if(a==num)
        {
            last = temp1->prev;
            temp1->prev->next = NULL;
            temp1->next = temp2;
            temp2->prev = temp1;
            head = temp1;
        }
        else
        {
            last = temp1->prev;
            temp1->prev->next = NULL;
            player *temp3 = temp1->prev;
            temp3->next= temp1->next;
            temp1->next->prev = temp3;
            temp1->next = temp2;
            temp2->prev = temp1;
        }
    }
    else if(b==num && a!=1)
    {
        player *temp3 = temp1->prev;
        temp3->next= temp1->next;
        temp1->next->prev = temp3;//temp1
        temp2->next = temp1;
        temp1->prev = temp2;
        temp1->next = NULL;
        last = temp1;
    }
    else if(a==num && b!=1)
    {
        temp1->prev->next = NULL;
        player *temp4 = temp2->next;
        temp4->prev = temp1;
        temp1->next = temp4;
        temp1->prev = temp2;
        temp2->next = temp1;
    }
    else
    {
        player *temp3 = temp1->prev;
        temp3->next= temp1->next;
        temp1->next->prev = temp3;//temp1
        player *temp4 = temp2->next;
        temp4->prev = temp1;
        temp1->next = temp4;
        temp1->prev = temp2;
        temp2->next = temp1;
    }
    int count = 1;
    player *temp5 = head;
    while (count <= num)
    {
        temp5->ind = count;
        temp5=temp5->next;
        count++;
    }
}
void delplaylist()
{
    player *temps = head;
    player *tempd = head;
    player *templ = last;
    
    while(temps!=templ)
    {
        if(temps==head)
        {
            temps = temps->next;
        }
        else
        {
            free(tempd);
            tempd = temps;
            temps = temps->next;
        }
    }
    free(temps);
    free(tempd);
    head = last = NULL;
    num = 0;
}
//Displays playlist
void disp()
{
    if(head==NULL && last==NULL)
    {
        printf("Empty playlist");
    }
    else
    {
    player *temp=head;
    while(temp!=last)
    {
        printf("%d  %s\n",temp->ind,temp->song);
        temp = temp->next;
    }
    printf("%d  %s\n",temp->ind,temp->song);
    }
}
void main()
{
    player *new = (player *)malloc(sizeof(player));
    head=new;
    last= new;
    head->prev=NULL;
    head->next = NULL;
    int choice;
   /* printf("To add a song to your playlist enter 1\n");
    printf("To delete a song from your playlist enter 2\n");
    scanf("%d",&choice);*/
    int op=1;
    while(op==1)
    {
        printf("To add a song to your playlist enter 1\n");
        printf("To delete a song from your playlist enter 2\n");
        printf("To move a song from 1 position to another enter 3\n");
        printf("To delete the playlist enter 4\n");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("Enter name of song\n");
            char newsong[50];
            scanf("%s", &newsong);
            addsong(newsong);
        }
        else if(choice==2)
        {
            disp();
            int srn;
            printf("Enter the sr.no of song that you want to delete\n");
            scanf("%d", &srn);
            delsong(srn);
        }
        else if(choice==3)
        {
            disp();
            int srn1, srn2;
            printf("Enter the sr.no the song and the new postion you want to move it to\n");
            scanf("%d %d", &srn1, &srn2);
            movesong(srn1, srn2);
        }
        else if(choice==4)
        {
            delplaylist();
        }
        choice = 0;
        printf("If you want to perform another action enter 1 else enter 0\n");
        scanf("%d",&op);
        if(op==0)
        {
            break;
        }
    }
    disp();
}