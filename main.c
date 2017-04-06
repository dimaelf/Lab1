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





int where (void* (*scan)(void*), int check(int, void*, struct list*), struct list* p)
{
    int i, f=0;
    void* sear;
    scan(&sear);
    for (i=0; i<(*p).length; i++)
    {
        f=check(i, sear, p);
        if (f==1){
            return i;
        }
    }
    return -1;
}

void scan17 (void** sear)
{
    int* d = (int*)malloc(sizeof(int));
    *d = -17;
    *sear = d;
}

void scan30 (void** sear)
{
    int* d = (int*)malloc(sizeof(int));
    *d = 30;
    *sear = d;
}

void scan85945 (void** sear)
{
    int* d = (int*)malloc(sizeof(int));
    *d = 85945;
    *sear = d;
}

int checkint (int i, void* sear, struct list* pin)
{
    if (*((int*)(*pin).pointer+i)==*(int*)sear){
            return 1;}
    return 0;
}

int checkcomp (int i, void* sear, struct list* pin)
{
    struct comp* p = (struct comp*)(*pin).pointer;
    if ((*(p+i)).im==*(int*)sear){
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
        return 1;
    }
    else
    {
        return 0;
    }
}




void sortflT()
{
    struct list* flsortT;
    flsortT->length = 7;
    flsortT->pointer = malloc(flsortT->length*sizeof(double));
    double* p;
    p = (double*)(flsortT->pointer);
    int i = 0;
    *p = 756.83;
    i++;
    *(p+i) = 763096;
    i++;
    *(p+i) = 0;
    i++;
    *(p+i) = -1024.13;
    i++;
    *(p+i) = -1;
    i++;
    *(p+i) = 1488;
    i++;
    *(p+i) = -0.228;
    i++;

    p = (double*) malloc (flsortT->length*sizeof(double));
    i=0;
    *(p+i) = -1024.13;
    i++;
     *(p+i) = -1;
    i++;
    *(p+i) = -0.228;
    i++;
    *(p+i) = 0;
    i++;
    *(p+i) = 756.83;
    i++;
    *(p+i) = 1488;
    i++;
    *(p+i) = 763096;
    i++;
    sort(changefl, flsortT);
    for (i=0; i<flsortT->length; i++)
    {
        printfl(i, flsortT);
        if (*(p+i)!= *((double*)flsortT->pointer+i))
        {
            printf("  !!Test of sort for float (int) failed!!\n\n");
            return;
        }
    }
    printf("   Success\n\n");
}


void sortcompT()
{
    struct list* sortT;
    sortT->length = 5;
    sortT->pointer = malloc(sortT->length*sizeof(struct comp));
    struct comp* p;
    p = (struct comp*)(sortT->pointer);
    int i = 0;
    p->im = 767;
    i++;
    (p+i)->im = -1;
    i++;
    (p+i)->im = 0;
    i++;
    (p+i)->im = 87;
    i++;
    (p+i)->im = -87;
    i++;
    for (i=0; i<sortT->length; i++)
    {
        (p+i)->re = i;
    }
    p = (struct comp*) malloc (sortT->length*sizeof(struct comp));
    i=0;
    (p+i)->im = -87;
    (p+i)->re = 4;
    i++;
    (p+i)->im = -1;
    (p+i)->re = 1;
    i++;
    (p+i)->im = 0;
    (p+i)->re = 2;
    i++;
    (p+i)->im = 87;
    (p+i)->re = 3;
    i++;
    (p+i)->im = 767;
    (p+i)->re = 0;
    i++;
    sort(changecomp, sortT);
    int f = 1;
    for (i=0; i<sortT->length; i++)
    {
        printcomp(i, sortT);
        if (((p+i)->im != ((struct comp*)sortT->pointer+i)->im)||(((p+i)->re != ((struct comp*)sortT->pointer+i)->re)))
        {
            printf("  !!Test of sort for comp failed!!\n\n");
            return;
        }
    }
    printf("   Success\n\n");
}


void inp (char l[30], char* p, int i)
{
    int j;
    for (j =0; l[j]!='\0'; j++)
    {
        *(p+30*i+j) = l[j];
    }
    *(p+30*i+j)='\0';
}

void sortlineT()
{
    struct list T;
    T.length = 10;
    int lett = 30;
    T.pointer = malloc(T.length*lett*sizeof(char));
    char* p;
    p = (char*)(T.pointer);
    char t1[30]= "strings";
    char t2[30]= "string";
    char t3[30]= "stri";
    char t4[30]= "str1";
    char t5[30]= "stri ngs";
    char t6[30]= "stringuhjfkcvbhfivjddjv";
    char t7[30]= "astrings";
    char t8[30]= "zstri";
    char t9[30]= "3strings";
    char t10[30]= "2strings";
    int j, i = 0;
    inp(t1, p, i);
    i++;
    inp(t2, p, i);
    i++;
    inp(t3, p, i);
    i++;
    inp(t4, p, i);
    i++;
    inp(t5, p, i);
    i++;
    inp(t6, p, i);
    i++;
    inp(t7, p, i);
    i++;
    inp(t8, p, i);
    i++;
    inp(t9, p, i);
    i++;
    inp(t10, p, i);

    sort(changeline, &T);

    p = (char*)malloc(T.length*lett*sizeof(char));
    i = 0;
    inp(t10, p, i);
    i++;
    inp(t9, p, i);
    i++;
    inp(t7, p, i);
    i++;
    inp(t4, p, i);
    i++;
    inp(t3, p, i);
    i++;
    inp(t5, p, i);
    i++;
    inp(t2, p, i);
    i++;
    inp(t1, p, i);
    i++;
    inp(t6, p, i);
    i++;
    inp(t8, p, i);
    int f = 1;
    for (i=0; i<T.length; i++)
    {
        printline(i, &T);
        for (j=0; *(p+lett*i+j)!='\0'; j++)
        {
            if (*(p+i*lett+j)!= *((char*)T.pointer+i*lett+j))
            {
                printf("  !!Test of sort for lines failed!!\n\n");
                return;
            }
        }
    if (*((char*)T.pointer+i*lett+j)!='\0')
        {
            printf("  !!Test of sort for lines failed!!\n\n");
            return;
        }
    }
    printf("   Success\n\n");
}


void trans (char s[], struct stud* p)
{
    int i;
    for (i=0; s[i]!='\0'; i++)
    {
        p->sname[i] = s[i];
    }
    p->sname[i] = '\0';
}

void tran (char s[], struct stud* p)
{
    int i;
    for (i=0; s[i]!='\0'; i++)
    {
        p->name[i] = s[i];
    }
    p->name[i] = '\0';
}

void sortstudT()
{
    struct list T;
    T.length = 6;
    T.pointer = malloc(T.length*sizeof(struct stud));
    struct stud* p = (struct stud*)T.pointer;
    int f, j, i = 0;
    trans ("Herzzz", p+i);
    tran ("A", p+i);
    (p+i)->yed = 1;
    i++;
    trans ("Herz", p+i);
    tran ("B", p+i);
    (p+i)->yed = 3;
    i++;
    trans ("Her", p+i);
    tran ("C", p+i);
    (p+i)->yed = 1;
    i++;
    trans ("Herz", p+i);
    tran ("D", p+i);
    (p+i)->yed = 2;
    i++;
    trans ("BHerz", p+i);
    tran ("E", p+i);
    (p+i)->yed = 1;
    i++;
    trans ("ZHerz", p+i);
    tran ("F", p+i);
    (p+i)->yed = 1;

    sort(changestud, &T);{

}   p = (struct stud*) malloc(T.length*sizeof(struct stud));
    i = 0;
    trans ("BHerz", p+i);
    tran ("E", p);
    (p+i)->yed = 1;
    i++;
    trans ("Her", p+i);
    tran ("C", p);
    (p+i)->yed = 1;
    i++;
    trans ("Herzzz", p+i);
    tran ("A", p);
    (p+i)->yed = 1;
    i++;
    trans ("ZHerz", p+i);
    tran ("F", p+i);
    (p+i)->yed = 1;
    i++;
    trans ("Herz", p+i);
    tran ("D", p);
    (p+i)->yed = 2;
    i++;
    trans ("Herz", p+i);
    tran ("B", p);
    (p+i)->yed = 3;
    for (i=0; i<T.length; i++)
    {
        printstud(i, &T);
        if ((p+i)->yed !=((struct stud*)T.pointer+i)->yed)
        {
            printf("  !!Test of sort for stud failed!!\n\n");
            return;
        }
        for (j = 0; (p+i)->sname[j]!='\0'; j++)
        {
            if (((struct stud*)T.pointer+i)->sname[j] != (p+i)->sname[j])
                {
                    printf("  !!Test of sort for stud failed!!\n\n");
                    return;
                }
        }
        if (((struct stud*)T.pointer+i)->sname[j] != '\0')
        {
            printf("  !!Test of sort for stud failed!!\n\n");
            return;
        }
    }
    printf("   Success\n\n");
}



void mapintT ()
{
    struct list T;
    T.length = 5;
    T.pointer = malloc(T.length*sizeof(int));
    int* p;
    p = (int*)(T.pointer);
    int i = 0;
    *p = -17;
    i++;
    *(p+i) = 0;
    i++;
    *(p+i) = -16485;
    i++;
    *(p+i) = -8;
    i++;
    *(p+i) = 85945;
    p = (int*) malloc (T.length*sizeof(int));
    i=0;
    *p = 0;
    i++;
    *(p+i) = 17;
    i++;
    *(p+i) = -16468;
    i++;
    *(p+i) = 9;
    i++;
    *(p+i) = 85962;
    map(funint, &T);
    int f = 1;
    for (i=0; i<T.length; i++)
    {
        printint(i, &T);
        if (*(p+i)!= *((int*)T.pointer+i))
        {
            printf("  !!Test of map for int (float) failed!!\n\n");
            return;
        }
    }
    printf("   Success\n\n");
}


void mapcomp()
{
    struct list T;
    T.length = 3;
    T.pointer = malloc(T.length*sizeof(struct comp));
    struct comp* p;
    p = (struct comp*)(T.pointer);
    int i = 0;
    p->im = 767;
    i++;
    (p+i)->im = -1;
    i++;
    (p+i)->im = 0;
    i++;
    for (i=0; i<T.length; i++)
    {
        (p+i)->re = i;
    }
    p = (struct comp*) malloc (T.length*sizeof(struct comp));
    i=0;
    (p+i)->im = 780;
    i++;
    (p+i)->im = 12;
    i++;
    (p+i)->im = 13;
    map(funcomp, &T);
    int f = 1;
    for (i=0; i<T.length; i++)
    {
        printcomp(i, &T);
        if (((p+i)->im != ((struct comp*)T.pointer+i)->im)||((i != ((struct comp*)T.pointer+i)->re)))
        {
            printf("  !!Test of map for comp failed!!\n\n");
            return;
        }
    }
    printf("   Success\n\n");
}


void tranl(char s[30], char* p)
{
    int i;
    for (i=0; s[i]!='\0'; i++)
    {
        *(p+i) = s[i];
    }
    *(p+i)='\0';
}

void maplineT ()
{
    int lett = 30;
    int j, i = 0;
    struct list T;
    T.length = 5;
    T.pointer = malloc(T.length*lett*sizeof(char));
    char* p = (char*)T.pointer;
    tranl("My string", p+i*lett);
    i++;
    tranl("My string is big, my string i", p+i*lett);
    i++;
    tranl("My string is big, my string ", p+i*lett);
    i++;
    tranl("My string is big, my strin", p+i*lett);
    i++;
    tranl("My string is big, my stri", p+i*lett);

    map(funline, &T);

    p = (char*)malloc(T.length*lett*sizeof(char));
    i=0;
    tranl("My string ;)", p+i*lett);
    i++;
    tranl("My string is big, my strin ;)", p+i*lett);
    i++;
    tranl("My string is big, my stri ;)", p+i*lett);
    i++;
    tranl("My string is big, my strin ;)", p+i*lett);
    i++;
    tranl("My string is big, my stri ;)", p+i*lett);
    for (i=0; i<T.length; i++)
    {
        printline(i, &T);
        for (j=0; *(p+lett*i+j)!='\0'; j++)
        {
            if (*(p+i*lett+j)!= *((char*)T.pointer+i*lett+j))
            {
                printf("  !!Test of sort for lines failed!!\n\n");
                return;
            }
        }
    if (*((char*)T.pointer+i*lett+j)!='\0')
        {
            printf("  !!Test of sort for lines failed!!\n\n");
            return;
        }
    }
    printf("   Success\n\n");

}



void whereintT()
{
    struct list T;
    T.length = 5;
    T.pointer = malloc(T.length*sizeof(int));
    int* p;
    p = (int*)(T.pointer);
    int i = 0;
    *p = -17;
    i++;
    *(p+i) = 0;
    i++;
    *(p+i) = -16485;
    i++;
    *(p+i) = -8;
    i++;
    *(p+i) = 85945;
    printf ("-17 ");
    if (where(scan17, checkint, &T) != 0)
    {
        printf("  !!Test for where of int failed!!\n\n");
        return;
    }
    printf("30 ");
    if (where(scan30, checkint, &T) != -1)
    {
        printf("  !!Test for where of int failed!!\n\n");
        return;
    }
        printf("85945 ");
    if (where(scan85945, checkint, &T) != 4)
    {
        printf("  !!Test for where of int failed!!\n\n");
        return;
    }
    printf ("  Success\n\n");
}


int main()
{
    sortflT();
    sortcompT();
    sortlineT();
    sortstudT();
    mapintT();
    mapcomp();
    maplineT();
    whereintT();

    return 0;
}
