#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>

//Linked List Creation
int num=0;
typedef struct queue
{
    int ind;
    char song[50];
    struct queue *prev;
    struct queue *next;
} player;
player *head;
player *last;
int inplaylist(char newsong[50])
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

//Adds song to the end of playlist
void addsong(char newsong[50])
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

//Deletes song from playlist
void delsong(int n)
{   if(head==last && head->song[0]=='\0')
    {
        printf("Your playlist is already empty");
    }
    else
    {
        player *temp = head;
        if(n==1)
        {
            head = head->next;
            free(temp);
            head->prev = NULL;
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
            last->next = NULL;
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
}

//Move a song from one position to another
void movesong(int a,int b)
{
    if(head==last && head->song[0]=='\0')
    {
        printf("Empty playlist");
    }
    else
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
            //last = temp1->prev;
            //temp1->prev->next = NULL;
            player *temp3 = temp1->prev;
            temp3->next= temp1->next;
            temp1->next->prev = temp3;
            temp1->next = temp2;
            temp2->prev = temp1;
            temp1->prev = NULL;
            head = temp1;
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
        last = temp1->prev;
        /*player *temp4 = temp2->next;
        temp4->prev = temp1;
        temp1->next = temp4;
        temp1->prev = temp2;
        temp2->next = temp1;*/
        player *temp4 = temp2->prev;
        temp4->next = temp1;
        temp1->prev = temp4;
        temp1->next = temp2;
        temp2->prev = temp1;
        
    }
    else
    {
        if(a<b)
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
        else
        {
            player *temp3 = temp1->prev;
            temp3->next= temp1->next;
            temp1->next->prev = temp3;//temp1
            /*
            player *temp4 = temp2->next;
            temp4->prev = temp1;
            temp1->next = temp4;
            temp1->prev = temp2;
            temp2->next = temp1;
            */
           player *temp4 = temp2->prev;
           temp4->next = temp1;
           temp1->prev = temp4;
           temp1->next = temp2;
           temp2->prev = temp1;
        }
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
}
void delplaylist()
{
    player *temps = head;
    player *tempd = head;
    player *templ = last;
    if(head==last && head->song[0]=='\0')
    {
        printf("Empty Playlist");
    }
    else
    {
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
    player *new = (player *)malloc(sizeof(player));
    head = last = new;
    new->song[0] = '\0';
    num = 0;
    }
}
//Displays playlist
void disp()
{
    if(head==last && head->song[0]=='\0')
    {
        printf("Empty playlist\n");
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
    char name[50];
    printf("Enter your name:");
    scanf("%s", &name);
    char namepl[50];
    strcpy(namepl, name);
    strcat(name, ".txt");
    FILE *fp1= fopen(name, "a");
    FILE *fp= fopen(name, "r");
    player *temp = head;
    char ch;
    char st[50];
    int j = 0;
    ch = fgetc(fp);
    if(ch!=EOF)//loads song from file to playlist
    {
    while(ch!=EOF)
    {
        if(ch!=' ')
        {
        st[j] = ch;
        j++;
        }
        else
        {
            st[j] = '\0';
            player *new = (player *)malloc(sizeof(player));
            strcpy(new->song, st);
            new->ind = (num + 1);
            num++;
            new->prev = NULL;
            new->next = NULL;
            if(head==NULL)
            {
                head = new;
                temp = head;
                last = new;
                
            }
            else
            {
                temp->next = new;
                new->prev = temp;
                temp = temp->next;
                last = last->next;
            }
            j = 0;
            st[j] = '\0';
        }
        ch = fgetc(fp);
    }
    if (j > 0)
    {
        st[j-1] = '\0';

        player *new = (player *)malloc(sizeof(player));
        strcpy(new->song, st);
        new->prev = NULL;
        new->next = NULL;
        new->ind=(num+1);
        num++;
        temp->next = new;
        new->prev = temp;
        temp = temp->next;
        last = last->next;
    }
    }
    else
    {
    player *new = (player *)malloc(sizeof(player));
    head=new;
    last= new;
    head->prev=NULL;
    head->next = NULL;
    head->song[0] = '\0';
    //strcpy(head->song,'\0');
    }
    int choice;//Takes user's choice on the action he wants to perform
    int op=1;
    while(op==1)
    {
        printf("To add a song to your playlist enter 1:\n");
        printf("To delete a song from your playlist enter 2:\n");
        printf("To move a song from 1 position to another enter 3:\n");
        printf("To delete the playlist enter 4:\n");
        printf("To listen to your playlist enter 5:\n");
        scanf("%d",&choice);
        if(choice==1)
        {
            printf("Enter name of song(without space):\n");
            char newsong[50];
            scanf("%s", &newsong);
            addsong(newsong);
        }
        else if(choice==2)
        {
            disp();
            if(head!=last || head->song[0]!='\0')
            {
            int srn;
            printf("Enter the sr.no of song that you want to delete:\n");
            scanf("%d", &srn);
            if(srn<1 || srn>num)
            {
                printf("Serial number not in range\n");
            }
            else
            {
            delsong(srn);
            }
            }
        }
        else if(choice==3)
        {
            disp();
            if(head!=last || head->song[0]!='\0')
            {
            int srn1;
            int srn2;
            printf("Enter the sr.no the song and the new postion you want to move it to:\n");
            scanf("%d %d", &srn1,&srn2);
            if(srn1<1 || srn1>num || srn2<1 || srn2>num)
            {
                printf("Serial number out of range\n");
            }
            else
            {
            movesong(srn1, srn2);
            }
            }
        }
        else if(choice==4)
        {
            delplaylist();
        }
        else if(choice==5)
        {
            break;
        }
        choice = 0;
        printf("If you want to perform another action enter 1 else enter 0:\n");
        scanf("%d",&op);
        if(op==0)
        {
            break;
        }
    }
    strcat(namepl, "'s playlist");
    printf("%s\n", namepl);
    printf("***************************************\n");
    disp();
    FILE *fp2 = fopen(name,"w");
    FILE *fpf = fopen(name,"a");
    player *temp1 = head;
    while(temp1!=NULL)//loads back songs from playlist to file
    {
        if(head==last && temp1->song[0])
        {
            break;
        }
        else
        {
            fprintf(fpf, "%s ", temp1->song);
            temp1 = temp1->next;
        }
    }
    fclose(fpf);
    fclose(fp2);
    int x = 0;
    printf("If you want to exit enter 0 or if you want to listen to your playlist enter 1:\n");
    scanf(" %d",&x);
    if(x==0)
    {
        printf("Good Bye");
    }
    else
    {
        player *tempp = head;
        int play = 1;
        while(play==1)
        {
            if(head==last && head->song[0]=='\0')
                
            {
                printf("Oops!Your playlist is empty");
                play = 0;
            }
            else
            {
                printf("Happy Listening!!\n");
                printf("Song playing:%s\n", tempp->song);
                sleep(5);
                char nav;
                if(tempp==head)
                {
                    printf("To play next song enter 'n'\n");
                    printf("To shuffle enter 's'\n");
                }
                else if(tempp==last)
                {
                    printf("To play previous song enter 'p'\n");
                    printf("To shuffle enter 's'\n");
                }
                else
                {
                    printf("To play previous song enter 'p'\n");
                    printf("To play next song enter 'n'\n");
                    printf("To shuffle enter 's'\n");
                }
                printf("To stop playing enter 'N'\n");
                scanf(" %c",&nav);
                if(nav=='n')
                {
                    tempp = tempp->next;
                }
                else if(nav=='p')
                {
                    tempp = tempp->prev;
                }
                else if(nav=='s')
                {
                    srand(time(NULL));
                    // Generate a random number between 0 and num-1
                    int randomNum = rand() % (num);
                    tempp = head;
                    printf("%d", randomNum);
                    if((randomNum+1)>tempp->ind)
                    {
                    while(tempp->ind!=(randomNum+1))
                    {
                        tempp = tempp->next;
                    }
                    }
                    else if((randomNum+1)<tempp->ind)
                    {
                        while(tempp->ind!=(randomNum+1))
                        {
                            tempp = tempp->prev;
                        }
                    }
                    else
                    {
                        tempp = tempp;
                    }
                }
                else
                {
                    printf("Good Bye");
                    play = 0;
                    break;
                }
            }
        }
    }
}
