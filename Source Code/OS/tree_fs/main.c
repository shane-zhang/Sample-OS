#include <stdio.h>
#include <string.h>

struct FCB
{
    char Flag;
	char name[16];
	int size;
	int block[10];
	int parent;
};

struct Sector
{
	char Flag;
	char Data[512];
	char ECC[16];
};

int init_FS(struct FCB *InFCB,struct Sector *InSector,char *InBitMap)
{
    InFCB[0].Flag=63;
    strcpy(InFCB[0].name,"Root");
    InFCB[0].parent=0;
    printf("Root Created\n");
    int i;
	printf("Disk Formatted\t\t[OK]\n*************************\n");
	for(i=1;i<=255;i++)
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

int Create_File(struct FCB *InFCB,struct Sector *InSector,char *InBitMap,int PWD)
{
    if(InFCB[PWD].size==10)
    {
        printf("PWD_DIR Already Full!\n");
        return(2);
    }
    int i;
    char buffer[16];
    printf("InPut the file name:\n");
    gets(buffer);
	for(i=0;i<InFCB[PWD].size;i++)
	{
        if(strcmp(InFCB[InFCB[PWD].block[i]].name,buffer)==0)
        {
            printf("Already Have Same Name\n");
            return (1);
        }
	}
	for(i=0;i<=255;i++)
	{
        if(InFCB[i].Flag==0)
        {
            InFCB[i].Flag=127;
            strcpy(InFCB[i].name,buffer);
            InFCB[PWD].block[InFCB[PWD].size]=i;
            InFCB[PWD].size++;
            break;
        }
	}
    printf("Create File\t\t[OK]\n*************************\n");
	return (0);
}

int Create_DIR(struct FCB *InFCB,struct Sector *InSector,char *InBitMap,int PWD)
{
    if(InFCB[PWD].size==10)
    {
        printf("PWD_DIR Already Full!\n");
        return(2);
    }
    int i;
    char buffer[16];
    printf("InPut the dirctory name:\n");
    gets(buffer);
	for(i=0;i<InFCB[PWD].size;i++)
	{
        if(strcmp(InFCB[InFCB[PWD].block[i]].name,buffer)==0)
        {
            printf("Already Have Same Name DIR\n");
            return (1);
        }
	}
	for(i=0;i<=255;i++)
	{
        if(InFCB[i].Flag==0)
        {
            InFCB[i].Flag=63;
            InFCB[i].parent=PWD;
            strcpy(InFCB[i].name,buffer);
            InFCB[PWD].block[InFCB[PWD].size]=i;
            InFCB[PWD].size++;
            break;
        }
	}
    printf("Create DIR\t\t[OK]\n*************************\n");
	return (0);
}

int Write(struct FCB *InFCB,struct Sector *InSector,char *InBitMap,int PWD)
{
    int i;
    char buffer[16];
    printf("InPut the file name:\n");
    gets(buffer);
	for(i=0;i<InFCB[PWD].size;i++)
	{
        if(InFCB[InFCB[PWD].block[i]].Flag==127)
        {
            if(strcmp(InFCB[InFCB[PWD].block[i]].name,buffer)==0)
            {
                if(InFCB[InFCB[PWD].block[i]].size==10)
                {
                    printf("Data Full\n");
                    return(1);
                }
                else
                {
                    printf("File Found:%s\nPlease InPut The String\n",InFCB[InFCB[PWD].block[i]].name);
                    char buffer_string[512];
                    gets(buffer_string);
                    int j;
                    for(j=0;j<=2559;j++)
                    {
                        if(InBitMap[j]==0)
                        {
                            InBitMap[j]=127;
                            InFCB[InFCB[PWD].block[i]].block[InFCB[InFCB[PWD].block[i]].size]=j;
                            InFCB[InFCB[PWD].block[i]].size++;
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

int Read(struct FCB *InFCB,struct Sector *InSector,char *InBitMap,int PWD)
{
    int i;
    char buffer[16];
    printf("InPut the file name:\n");
    gets(buffer);
	for(i=0;i<InFCB[PWD].size;i++)
	{
        if(InFCB[InFCB[PWD].block[i]].Flag==127)
        {
            if(strcmp(InFCB[InFCB[PWD].block[i]].name,buffer)==0)
            {
                if(InFCB[InFCB[PWD].block[i]].size==0)
                {
                    printf("No String\n");
                    return(1);
                }
                else
                {
                    int j;
                    for(j=0;j<InFCB[InFCB[PWD].block[i]].size;j++)
                    {
                        puts(InSector[InFCB[InFCB[PWD].block[i]].block[j]].Data);
                    }
                }
            }
        }
	}
    printf("Read From File\t\t[OK]\n*************************\n");
	return (0);
}

int Delete_File(struct FCB *InFCB,struct Sector *InSector,char *InBitMap,int PWD)
{
    int i;
    char buffer[16];
    printf("InPut the file name:\n");
    gets(buffer);
	for(i=0;i<InFCB[PWD].size;i++)
	{
        if(strcmp(InFCB[InFCB[PWD].block[i]].name,buffer)==0)
        {
            if(InFCB[InFCB[PWD].block[i]].Flag==127)
            {
                int j;
                for(j=0;j<InFCB[InFCB[PWD].block[i]].size;j++)
                {
                    InBitMap[InFCB[InFCB[PWD].block[i]].block[j]]=0;
                }
                InFCB[InFCB[PWD].block[i]].size=0;
                InFCB[InFCB[PWD].block[i]].Flag=0;
                for(j=i+1;j<=InFCB[PWD].size;j++)
                {
                    InFCB[PWD].block[j-1]=InFCB[PWD].block[j];
                }
                InFCB[PWD].size--;
                printf("Delete File\t\t[OK]\n*************************\n");
                return(0);
            }
            else if(InFCB[InFCB[PWD].block[i]].Flag==63)
            {
                if(InFCB[InFCB[PWD].block[i]].size!=0)
                {
                    printf("DIR NOT EMPTY!\n");
                    return(1);
                }
                else
                {
                    int j;
                    InFCB[InFCB[PWD].block[i]].size=0;
                    InFCB[InFCB[PWD].block[i]].Flag=0;
                    for(j=i+1;j<=InFCB[PWD].size;j++)
                    {
                        InFCB[PWD].block[j-1]=InFCB[PWD].block[j];
                    }
                    InFCB[PWD].size--;
                    printf("Delete DIR\t\t[OK]\n*************************\n");
                    return(0);
                }
            }
        }
	}
    printf("No Such FIle\t\t[OK]\n*************************\n");
	return (1);
}

int List(struct FCB *InFCB,struct Sector *InSector,char *InBitMap,int PWD)
{
    if(InFCB[PWD].size==0)
    {
        printf("%s Is Empty!\n",InFCB[PWD].name);
        return (1);
    }
    else
    {
        int i;
        for(i=0;i<InFCB[PWD].size;i++)
        {
            if(InFCB[InFCB[PWD].block[i]].Flag==127)
            {
                printf("%s\tFILE\t%d\n",InFCB[InFCB[PWD].block[i]].name,InFCB[InFCB[PWD].block[i]].size);
            }
            else if(InFCB[InFCB[PWD].block[i]].Flag==63)
            {
                printf("%s\tDIR\t%d\n",InFCB[InFCB[PWD].block[i]].name,InFCB[InFCB[PWD].block[i]].size);
            }
        }
        printf("List Files\t\t[OK]\n*************************\n");
        return (0);
    }
}

int Change_DIR(struct FCB *InFCB,struct Sector *InSector,char *InBitMap,int PWD,int *Out)
{
    int i;
    char buffer[16];
    printf("InPut the DIR name:\n");
    gets(buffer);
    if(strcmp(buffer,"..")==0)
    {
        printf("Return to %s\n",InFCB[PWD].name);
        *Out=InFCB[PWD].parent;
        return(0);
    }
	for(i=0;i<InFCB[PWD].size;i++)
	{
        if(InFCB[InFCB[PWD].block[i]].Flag==63)
        {
            if(strcmp(InFCB[InFCB[PWD].block[i]].name,buffer)==0)
            {
                *Out=InFCB[PWD].block[i];
                printf("Change To %s\t\t[OK]\n*************************\n",InFCB[InFCB[PWD].block[i]].name);
                return(0);
            }
        }
	}
    printf("No Such DIR\t\t[OK]\n*************************\n");
	return (1);
}

int Console(struct FCB *InFCB,struct Sector *InSector,char *InBitMap)
{
    int pwd=0;
    for(;;)
    {
        char inc[10];
        int choice=0;
        printf(">?");
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
        if(strcmp(inc,"mkdir")==0)
        {
            choice=7;
        }
        if(strcmp(inc,"cd")==0)
        {
            choice=8;
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
                List(InFCB,InSector,InBitMap,pwd);
                break;
            }
            case (3):
            {
                Create_File(InFCB,InSector,InBitMap,pwd);
                break;
            }
            case (4):
            {
                Delete_File(InFCB,InSector,InBitMap,pwd);
                break;
            }
            case (5):
            {
                Write(InFCB,InSector,InBitMap,pwd);
                break;
            }
            case (6):
            {
                Read(InFCB,InSector,InBitMap,pwd);
                break;
            }
            case (7):
            {
                Create_DIR(InFCB,InSector,InBitMap,pwd);
                break;
            }
            case (8):
            {
                Change_DIR(InFCB,InSector,InBitMap,pwd,&pwd);
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
	struct FCB HEAD[256];
	struct Sector HDD[2560];
	char BitMap[2560];
	printf("*************************\nHello This is shaneFS.\nYou can\n*************************\nFormat\nList\nCreate\nDelete\nWrite\nRead\n*************************\n");
    Console(HEAD,HDD,BitMap);
	return (0);
}
