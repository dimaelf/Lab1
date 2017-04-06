#include <stdio.h>
#include <stdlib.h>


struct list
{
    void* pointer;
    int length;
};


struct comp
{
  int re, im;
};

struct stud
{
    char sname[20];
    char name[20];
    int yed;
};







void choosekind(int* actd)
{
    printf ("Chose kind of data:\n0-intenger\n1-float\n2-Comp\n3-lines\n4-students\n7-qiut\n");
    scanf ("%d", actd);
}




void sort(int (*change)(int, struct list*), struct list* p)
{
    int i,j,f;
    int N = (*p).length;
    for (j=0; j< N-1; j++)
    {
        f=0;
        for (i=N-1; i>j; i--)
        {
            f = f+change(i, p);
        }
        if (f==0){return;}
    }
}

int changeint (int i, struct list* pin)
{
    int* p = (int*)(*pin).pointer;
    if (*(p+i)< *(p+i-1))
            {
                int ch;
                ch=*(p+i);
                *(p+i)= *(p+i-1);
                *(p+i-1)=ch;
                return 1;
            }
    return 0;
}

int changefl (int i, struct list* pin)
{
    double* p = (double*) (*pin).pointer;
    if (*(p+i)< *(p+i-1))
            {
                double ch;
                ch=*(p+i);
                *(p+i)= *(p+i-1);
                *(p+i-1)=ch;
                return 1;
            }
    return 0;
}

int changecomp(int i, struct list* pin)
{
    struct comp* p = (struct comp*) (*pin).pointer;
    if ((*(p+i)).im< (*(p+i-1)).im)
            {
                int ch;
                ch=(*(p+i)).im;
                (*(p+i)).im= (*(p+i-1)).im;
                (*(p+i-1)).im=ch;
                ch=(*(p+i)).re;
                (*(p+i)).re= (*(p+i-1)).re;
                (*(p+i-1)).re=ch;
                return 1;
            }
    return 0;
}

int changeline (int i, struct list* pin)
{
    int lett = 30;
    int j, k;
    char temp;
    char* p = (char*)(*pin).pointer;
    for (j=0; *(p+(i-1)*lett+j)!='\0'; j++)
    {
        if (*(p+i*lett+j)=='\0')
        {
            for(k=0; k<lett; k++)
            {
                temp= *(p+i*lett+k);
                *(p+i*lett+k)=*(p+(i-1)*lett+k);
                *(p+(i-1)*lett+k)=temp;
            }
            return 1;
        }
        if (*(p+i*lett+j)<*(p+(i-1)*lett+j))
        {
            for(k=0; k<lett; k++)
            {
                temp= *(p+i*lett+k);
                *(p+i*lett+k)=*(p+(i-1)*lett+k);
                *(p+(i-1)*lett+k)=temp;
            }
            return 1;
        }
        if (*(p+i*lett+j)>*(p+(i-1)*lett+j))
        {
            return 0;
        }
    }
    return 0;
}

int changestud (int i, struct list* pin)
{
    int j;
    struct stud temp;
    struct stud* p  = (struct stud*)(*pin).pointer;
    if ((p+i)->yed > (p+i-1)->yed)
    {
        return 0;
    }
    if ((p+i)->yed < (p+i-1)->yed)
    {
        temp = *(p+i);
        *(p+i) = *(p+i-1);
        *(p+i-1) = temp;
        return 1;
    }
    for (j=0; (p+i-1)->sname[j]!='\0'; j++)
        {
            if ((p+i)->sname[j]=='\0')
            {
                temp = *(p+i);
                *(p+i) = *(p+i-1);
                *(p+i-1) = temp;
                return 1;
            }
            if ((p+i)->sname[j]<(p+i-1)->sname[j])
            {
                temp = *(p+i);
                *(p+i) = *(p+i-1);
                *(p+i-1) = temp;
                return 1;
            }
            if ((p+i)->sname[j]>(p+i-1)->sname[j])
            {
                return 0;
            }
        }
    return 0;
}




void map (void (*fun)(int, struct list*), struct list* p)
{
    int i;
    for (i=0; i<(*p).length; i++)
    {
        fun(i, p);
    }
}

void funint (int i, struct list* pin)
{
    int ch=17;
    int* p = (int*)(*pin).pointer;
    *(p+i)=*(p+i)+ch;
}

void funfl (int i, struct list* pin)
{
    double ch=17.013;
    double* p = (double*) (*pin).pointer;
    *(p+i)=*(p+i)+ch;
}

void funcomp (int i, struct list* pin)
{
    int ch=13;
    struct comp* p = (struct comp*)(*pin).pointer;
    (*(p+i)).im=(*(p+i)).im+ch;
}

void funline (int i, struct list* pin)
{
    int lett = 30;
    int j;
    char* p = (char*)(*pin).pointer;
    for (j=0; *(p+i*lett+j)!='\0'; j++){}
    if (j<lett-3)
    {
        *(p+i*lett+j)=' ';
        *(p+i*lett+j+1)=';';
        *(p+i*lett+j+2)=')';
        *(p+i*lett+j+3)='\0';
    }
    else
    {
        *(p+i*lett+j-3)=' ';
        *(p+i*lett+j-2)=';';
        *(p+i*lett+j-1)=')';
        *(p+i*lett+j)='\0';
    }
}

void funstud (int i, struct list* pin)
{
    struct stud* p = (struct stud*)(*pin).pointer;
    (p+i)->yed++;
}



void addint (struct list* p)
{
    int n, i=0;
    int N = (*p).length;
    int* pnew = (int*)((*p).pointer);
    printf("How many numbers is it?\n");
    scanf ("%d", &n);
    pnew = (int*)realloc(pnew, (N+n)*sizeof(int));
    while (i<n){
        scanf("%d", (pnew+N+i));
        i++;
    }
    (*p).pointer=(void*) pnew;
    (*p).length=N+n;
}

void addfl (struct list* p)
{
    int n, i=0;
    int N = (*p).length;
    double* pnew = (double*)((*p).pointer);
    printf("How many numbers is it?\n");
    scanf ("%d", &n);
    pnew = (double*)realloc(pnew, (N+n)*sizeof(double));
    while (i<n){
        scanf("%lf", (pnew+N+i));
        i++;
    }
    (*p).pointer= (double*) pnew;
    (*p).length=N+n;
}

void addcomp (struct list* p)
{
    int n, i=0;
    int N = (*p).length;
    struct comp* pnew = (struct comp*)((*p).pointer);
    printf("How many numbers is it?\n");
    scanf ("%d", &n);
    pnew = (struct comp*)realloc(pnew, (N+n)*sizeof(struct comp));
    while (i<n){
        scanf("%d%d", &((*(pnew+N+i)).re), &((*(pnew+N+i)).im));
        i++;
    }
    (*p).pointer=pnew;
    (*p).length=N+n;
}

void addline(struct list* p)
{
    int lett = 30;
    int n, j, i=0;
    char temp[lett];
    int N = (*p).length;
    char* pnew = (char*)((*p).pointer);
    printf("How many lines is it?\n");
    scanf ("%d", &n);
    pnew = (char*)realloc(pnew, ((N+n)*lett)*sizeof(char));
    fgets(temp, lett, stdin); //?!??
    while (i<n){
        fgets(temp, lett, stdin);
        for ( j = 0; temp[j]!='\n'; j++ ){}
        temp[j]='\0';
        j=0;
        while (temp[j]!='\0')
        {
           *(pnew+(N+i)*lett+j) = temp[j];
           j++;
        }
        *(pnew+(N+i)*lett+j)=temp[j];
        i++;
    }
    (*p).pointer=pnew;
    (*p).length=N+n;
}

void addstud(struct list* p)
{
    int n, i=0;
    int N = (*p).length;
    struct stud* pnew = (struct stud*)((*p).pointer);
    printf("How many students is it?\n");
    scanf ("%d", &n);
    pnew = (struct stud*)realloc(pnew, (N+n)*sizeof(struct stud));
    while (i<n){
        printf("Write student's sername\n");
        scanf ("%20s", (pnew+N+i)->sname);
        printf("Write student's name\n");
        scanf ("%20s", ((pnew+N+i)->name));
        printf("Write year of education\n");
        scanf("%d", &((*(pnew+N+i)).yed));
        printf("\n");
        i++;
    }
    (*p).pointer=pnew;
    (*p).length=N+n;
}



void where (void* (*scan)(void*), int check(int, void*, struct list*), struct list* p)
{
    int i, f=0;
    void* sear;
    printf("What do you want to find?\n");
    scan(&sear);
    for (i=0; i<(*p).length; i++)
    {
        f=check(i, sear, p);
        if (f==1){
            return;
        }
    }
    printf (" wasn't found\n");
}

void scanint (void** sear)
{
    *sear = malloc(sizeof(int));
    scanf("%d", *(int*)sear);
    printf("%d", *(int*)*sear);
}

void scanfl (void** sear)
{
    *sear = malloc(sizeof(double));
    scanf("%lf", *(double*)sear);
    printf("%lf", *(double*)*sear);
}

void scanline (void** sear)
{
    int lett = 30;
    int i;
    char temp[lett];
    *sear = &temp;
    fgets( temp, 2, stdin );   //?!!!!
    fgets(temp, lett, stdin);
    for ( i = 0; temp[i]!='\n'; i++ ){}
    temp[i]='\0';
    printf("%s", temp);
}

int checkint (int i, void* sear, struct list* pin)
{
    if (*((int*)(*pin).pointer+i)==*(int*)sear){
            printf (": index=%d\n", i+1);
            return 1;}
    return 0;
}

int checkfl (int i, void* sear, struct list* pin)
{
    if (*((double*)(*pin).pointer+i)==*(double*)sear){
            printf (": index=%d\n", i+1);
            return 1;}
        return 0;
}

int checkcomp (int i, void* sear, struct list* pin)
{
    struct comp* p = (struct comp*)(*pin).pointer;
    if ((*(p+i)).im==*(int*)sear){
            printf (": index=%d\n", i+1);
            return 1;}
    return 0;
}

int checkline (int i, void* sear, struct list* pin)
{
    int lett = 30;
    char* p = (char*)(*pin).pointer;
    int j, flag=1;
    for (j=0; *(p+i*lett+j)!='\0'; j++)
    {
        if (*(p+i*lett+j)!=*((char*)sear+j))
        {
            flag = 0;
        }
    }
    if (*((char*)sear+j)!='\0')
    {
        return 0;
    }
    if (flag==1)
    {
        printf (": index=%d\n", i+1);
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkstud(int i, void* sear, struct list* pin)
{
    struct stud* p = (struct stud*)(*pin).pointer;
    int j, flag=1;
    for (j=0; (p+i)->sname[j]!='\0'; j++)
    {
        if ((p+i)->sname[j]!=*((char*)sear+j))
        {
            flag = 0;
        }
    }
    if (*((char*)sear+j)!='\0')
    {
        return 0;
    }
    if (flag==1)
    {
        printf (": index=%d\n", i+1);
        return 1;
    }
    else
    {
        return 0;
    }
}



void printint (int i, struct list* p)
{
    printf ("%d ", *((int*)((*p).pointer)+i));
}

void printfl (int i, struct list* p)
{
    printf ("%lf ", *((double*)((*p).pointer)+i));
}

void printcomp (int i, struct list* p)
{
    printf ("%d+(%d)*i ", (*((struct comp*)((*p).pointer)+i)).re, (*((struct comp*)((*p).pointer)+i)).im);
}

void printline (int i, struct list* p)
{
    int lett = 30;
    int j;
    for (j=0; *((char*)((*p).pointer)+i*lett+j)!='\0'; j++)
    {
        printf("%c", *((char*)((*p).pointer)+i*lett+j));
    }
    printf("\n");
}

void printstud (int i, struct list* p)
{
    printf("%s %s: %d\n", ((struct stud*)((*p).pointer)+i)->sname, ((struct stud*)((*p).pointer)+i)->name, ((*((struct stud*)((*p).pointer)+i)).yed));
}


void choose (void (*print)(int, struct list*), int* actdata, struct list* plists)
{
    int lett = 30;
    int ch, i;
    printf("Choose operation for kind of data which number is %d\n0-choose kind of data or quit\n1-add data\n2-sort\n3-map\n4-where\n", *actdata);
    scanf ("%d",&ch);
    if (ch==0)
    {
        choosekind(actdata);
        return;
    }
    if (ch==1)
    {
        if (*actdata==0){addint(plists+*actdata);}
        if (*actdata==1){addfl(plists+*actdata);}
        if (*actdata==2){addcomp(plists+*actdata);}
        if (*actdata==3){addline(plists+*actdata);}
        if (*actdata==4){addstud(plists+*actdata);}
    }
    if (ch==2)
    {
        if (*actdata==0){sort(changeint, plists+*actdata);}
        if (*actdata==1){sort(changefl, plists+*actdata);}
        if (*actdata==2){sort(changecomp, plists+*actdata);}
        if (*actdata==3){sort(changeline, plists+*actdata);}
        if (*actdata==4){sort(changestud, plists+*actdata);}

    }
    if (ch==3)
    {
        if (*actdata==0){map(funint, plists+*actdata);}
        if (*actdata==1){map(funfl, plists+*actdata);}
        if (*actdata==2){map(funcomp, plists+*actdata);}
        if (*actdata==3){map(funline, plists+*actdata);}
        if (*actdata==4){map(funstud, plists+*actdata);}

    }
    if (ch==4)
    {
        if (*actdata==0){where(scanint, checkint, plists+*actdata);}
        if (*actdata==1){where(scanfl, checkfl, plists+*actdata);}
        if (*actdata==2){where(scanint, checkcomp, plists+*actdata);}
        if (*actdata==3){where(scanline, checkline, plists+*actdata);}
        if (*actdata==4){where(scanline, checkstud, plists+*actdata);}

    }
    for (i=0; i< ((*(plists+*actdata)).length); i++)
    {
        print(i, plists+*actdata);
    }
    printf ("\n");
}




int main()
{
    int actdata;
    struct list* plists;
    plists=(struct list*)malloc (5*sizeof (struct list));
    int i;
    for (i=0; i<5; i++)
    {
        (*(plists+i)).length = 0;
        (*(plists+i)).pointer = (void*)malloc(0);
    }
    choosekind(&actdata);
    while (1<2)
    {
        if ((actdata != 0)&&(actdata!=1)&&(actdata!=2)&&(actdata!=3)&&(actdata!=4))
        {
              return 0;
        }
        else
        {
            if (actdata==0){choose(printint, &actdata, plists);}
            if (actdata==1){choose(printfl, &actdata, plists);}
            if (actdata==2){choose(printcomp, &actdata, plists);}
            if (actdata==3){choose(printline, &actdata, plists);}
            if (actdata==4){choose(printstud, &actdata, plists);}
        }
    }
    return 0;
}








