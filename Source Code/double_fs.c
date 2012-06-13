#include <stdio.h>
#include <string.h>

struct FCB
{
    char Flag;
	char name[16];
	int size;
	int block[10];
};

struct Sector
{
	char Flag;
	char Data[512];
	char ECC[16];
};

int init_FS(struct FCB *InFCB,struct Sector *InSector,char *InBitMap)
{
    int i;
	printf("Disk Formatted\t\t[OK]\n*************************\n");
	for(i=0;i<=255;i++)
	{
        InFCB[i].Flag=0;
        InFCB[i].size=0;
	}
    for(i=0;i<=2559;i++)
	{
        InSector[i].Flag=0;
	}
    for(i=0;i<=2559;i++)
	{
        InBitMap[i]=0;
	}
	return (0);
}

int Create(struct FCB *InFCB,struct Sector *InSector,char *InBitMap)
{
    int i;
    char buffer[16];
    printf("InPut the file name:\n");
    gets(buffer);
	for(i=0;i<=255;i++)
	{
        if(InFCB[i].Flag==127)
        {
            if(strcmp(InFCB[i].name,buffer)==0)
            {
                printf("Already Have Same Name\n");
                return (1);
            }
        }
	}
	for(i=0;i<=255;i++)
	{
        if(InFCB[i].Flag==0)
        {
            InFCB[i].Flag=127;
            strcpy(InFCB[i].name,buffer);
            break;
        }
	}
    printf("Create File\t\t[OK]\n*************************\n");
	return (0);
}

int Write(struct FCB *InFCB,struct Sector *InSector,char *InBitMap)
{
    int i;
    char buffer[16];
    printf("InPut the file name:\n");
    gets(buffer);
	for(i=0;i<=255;i++)
	{
        if(InFCB[i].Flag==127)
        {
            if(strcmp(InFCB[i].name,buffer)==0)
            {
                if(InFCB[i].size==10)
                {
                    printf("Data Full\n");
                    return(1);
                }
                else
                {
                    printf("File Found:%s\nPlease InPut The String\n",InFCB[i].name);
                    char buffer_string[512];
                    gets(buffer_string);
                    int j;
                    for(j=0;j<=2559;j++)
                    {
                        if(InBitMap[j]==0)
                        {
                            InBitMap[j]=127;
                            InFCB[i].block[InFCB[i].size]=j;
                            InFCB[i].size++;
                            strcpy(InSector[j].Data,buffer_string);
                            break;
                        }
                    }
                }
            }
        }
	}
    printf("Wire To File\t\t[OK]\n*************************\n");
	return (0);
}

int Read(struct FCB *InFCB,struct Sector *InSector,char *InBitMap)
{
    int i;
    char buffer[16];
    printf("InPut the file name:\n");
    gets(buffer);
	for(i=0;i<=255;i++)
	{
        if(InFCB[i].Flag==127)
        {
            if(strcmp(InFCB[i].name,buffer)==0)
            {
                if(InFCB[i].size==0)
                {
                    printf("No String\n");
                    return(1);
                }
                else
                {
                    int j;
                    for(j=0;j<InFCB[i].size;j++)
                    {
                        puts(InSector[InFCB[i].block[j]].Data);
                    }
                }
            }
        }
	}
    printf("Read From File\t\t[OK]\n*************************\n");
	return (0);
}

int Delete(struct FCB *InFCB,struct Sector *InSector,char *InBitMap)
{
    int i;
    char buffer[16];
    printf("InPut the file name:\n");
    gets(buffer);
	for(i=0;i<=255;i++)
	{
        if(InFCB[i].Flag==127)
        {
            if(strcmp(InFCB[i].name,buffer)==0)
            {
                int j;
                for(j=0;j<InFCB[i].size;j++)
                {
                    InBitMap[InFCB[i].block[j]]=0;
                }
                InFCB[i].size=0;
                InFCB[i].Flag=0;
                printf("Delete File\t\t[OK]\n*************************\n");
                return(0);
            }
        }
	}
    printf("No Such FIle\t\t[OK]\n*************************\n");
	return (1);
}

int List(struct FCB *InFCB,struct Sector *InSector,char *InBitMap)
{
    int i;
	for(i=0;i<=255;i++)
	{
        if(InFCB[i].Flag==127)
        {
            printf("%s\t\t%d\n",InFCB[i].name,InFCB[i].size);
        }
	}
	printf("List Files\t\t[OK]\n*************************\n");
	return (0);
}

int Console(struct FCB *InFCB,struct Sector *InSector,char *InBitMap,char *InUser)
{
    for(;;)
    {
        char inc[10];
        int choice=0;
        printf("%s>?",InUser);
        gets(inc);
        if(strcmp(inc,"format")==0)
        {
            choice=1;
        }
        if(strcmp(inc,"ls")==0)
        {
            choice=2;
        }
        if(strcmp(inc,"touch")==0)
        {
            choice=3;
        }
        if(strcmp(inc,"rm")==0)
        {
            choice=4;
        }
        if(strcmp(inc,"write")==0)
        {
            choice=5;
        }
        if(strcmp(inc,"read")==0)
        {
            choice=6;
        }
        if(strcmp(inc,"exit")==0)
        {
            choice=10;
        }
        switch(choice)
        {
            case (1):
            {
                init_FS(InFCB,InSector,InBitMap);
                break;
            }
            case (2):
            {
                List(InFCB,InSector,InBitMap);
                break;
            }
            case (3):
            {
                Create(InFCB,InSector,InBitMap);
                break;
            }
            case (4):
            {
                Delete(InFCB,InSector,InBitMap);
                break;
            }
            case (5):
            {
                Write(InFCB,InSector,InBitMap);
                break;
            }
            case (6):
            {
                Read(InFCB,InSector,InBitMap);
                break;
            }
            case (10):
            {
                return(0);
                break;
            }
            default:
            {
                printf("Can't find Console\n");
                break;
            }
        }
    }
}

int main(void)
{
	struct FCB HEAD1[256];
	struct Sector HDD1[2560];
	char BitMap1[2560];

	struct FCB HEAD2[256];
	struct Sector HDD2[2560];
	char BitMap2[2560];

	printf("*************************\nHello This is shaneFS.\nYou can\n*************************\nFormat\nList\nCreate\nDelete\nWrite\nRead\n*************************\n");

	for(;;)
	{
	    printf("Welcome!Please InPut Your Name:\n");
	    char inc[10];
	    gets(inc);
	    if(strcmp(inc,"shane")==0)
	    {
	        Console(HEAD1,HDD1,BitMap1,inc);
	    }
	    else if(strcmp(inc,"en")==0)
	    {
	        Console(HEAD2,HDD2,BitMap2,inc);
	    }
	    else if((strcmp(inc,"exit")==0))
	    {
	        break;
	    }
	    else
	    {
	        printf("Command Not Found!\n");
	    }
	}
	return (0);
}
