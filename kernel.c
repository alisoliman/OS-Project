void PrintString(char* string);
void readString (char* line);
void readSector(char* buffer, int sector);
void executeProgram(char* name, int segment);
void terminate();
int MOD(int x, int y);
int DIV(int x, int y);
void readFile(char* s,char* buf);
void writeSector(char* buffer, int sector);
void deleteFile(char* name);
void writeFile(char* name, char* buffer,int secnum);
main()
{

/*putInMemory(0xB000, 0x8000, 'H');
putInMemory(0xB000, 0x8001, 0x7);
putInMemory(0xB000, 0x8002, 'E');
putInMemory(0xB000, 0x8003, 0x7);
putInMemory(0xB000, 0x8004, 'L');
putInMemory(0xB000, 0x8005, 0x7);
putInMemory(0xB000, 0x8006, 'L');
putInMemory(0xB000, 0x8007, 0x7);
putInMemory(0xB000, 0x8008, 'O');
putInMemory(0xB000, 0x8009, 0x7);
putInMemory(0xB000, 0x800A, ' ');
putInMemory(0xB000, 0x800B, 0x7);
putInMemory(0xB000, 0x800C, 'W');
putInMemory(0xB000, 0x800D, 0x7);
putInMemory(0xB000, 0x800E, 'O');
putInMemory(0xB000, 0x800F, 0x7);
putInMemory(0xB000, 0x8010, 'R');
putInMemory(0xB000, 0x8011, 0x7);
putInMemory(0xB000, 0x8012, 'L');
putInMemory(0xB000, 0x8013, 0x7);
putInMemory(0xB000, 0x8014, 'D');
putInMemory(0xB000, 0x8015, 0x7);
putInMemory(0xB000, 0x8016, '!');
putInMemory(0xB000, 0x8017, 0x7);*/

//PrintString("HELLO WORLD!\0");

// char line[80];
// interrupt(0x10,0xE*256 + 0xa,0,0,0);
// PrintString("Enter a new line :");
// readString(line);
// PrintString(line);

//char buffer[512];
// readSector(buffer, 30);
// printString(buffer);

//makeInterrupt21();
//interrupt(0x21,0,0,0,0);

// char line[80];
// makeInterrupt21();
// interrupt(0x21,2,buffer,30,0);
// interrupt(0x21,0,buffer,0,0);

// char buffer[13312] ;/*this is the maximum size of a file*/
// makeInterrupt21();
// interrupt(0x21, 3, "messag\0", buffer, 0); /*read the file into buffer*/
// interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/
// makeInterrupt21();
// interrupt(0x21,4,"tstprgex/0",0x2000,0);


char buffer[13312];
makeInterrupt21();
interrupt(0x21, 7, "messag\0", 0, 0); //delete messag
interrupt(0x21, 3, "messag\0", buffer, 0); // try to read messag
interrupt(0x21, 0, buffer, 0, 0); //print out the contents of buffer


// int i=0;
// char buffer1[13312];
// char buffer2[13312];
// buffer2[0]='h'; buffer2[1]='e'; buffer2[2]='l'; buffer2[3]='l';
// buffer2[4]='o';
// for(i=5; i<13312; i++) buffer2[i]=0x0;
// makeInterrupt21();
// interrupt(0x21,8, "testW\0", buffer2, 1); //write file testW
// interrupt(0x21,3, "testW\0", buffer1, 0); //read file testW
// interrupt(0x21,0, buffer1, 0, 0); // print out contents of testW
while(1);

//terminate();

}

void PrintString(char* string)
{
int i = 0;
 while (string[i] != '\0')
   {
    char al = string[i];
    char ah = 0xE;
    int ax = ah * 256 + al;
    interrupt(0x10,0xE * 256 + string[i],0,0,0);
    i++;
   }
}

void readString(char* line)
{
int i = 0;
int x;
while (x != 0xd)
		{
			x = interrupt(0x16,0,0,0,0);
			
				
			if (x != 0x8) //backspace
				{
				interrupt(0x10,0xE*256 + x,0,0,0);
				line[i] = x;
				i++;
				}
			else 
			{
				if(i != 0){
			 interrupt(0x10,0xE*256 + x,0,0,0);
		         interrupt(0x10,0xE*256 + 0x20,0,0,0); 
			 interrupt(0x10,0xE*256 + 0x8,0,0,0);
			 line[i] = 0x0;
			 i--;		
					}
			}

		}
line[i] = 0x0;
line[i + 1] = 0xd;
line[i + 2] = 0xa;
interrupt(0x10,0xE*256 + 0x0,0,0,0);
interrupt(0x10,0xE*256 + 0xd,0,0,0);
interrupt(0x10,0xE*256 + 0xa,0,0,0);
}

int MOD(int x , int y)
{
	int result = x;
		while( result >= y){
		result -= y;	
		}
}

int DIV(int a,int b)
{
 int result = 0;
    while (a >= 0) {
        a -= b;
        result++;
    }
return result-1 ;
}

void readSector(char* buffer, int sector)
{  


	int ah = 2;
	int al= 1;
	char* bx= buffer;
	int ch= DIV(sector,36);
	int cl= (MOD(sector,18))+1;
	int dh = MOD((DIV(sector,18)) , 2);
	int dl = 0;
	int cx = ch*256	+cl;
	int dx = dh*256 +dl;
	interrupt(0x13,2*256+1,bx,cx,dx,0);

}

void writeSector(char* buffer, int sector)
{  


	int ah = 3;
	int al= 1;
	char* bx= buffer;
	int ch= DIV(sector,36);
	int cl= (MOD(sector,18))+1;
	int dh = MOD((DIV(sector,18)) , 2);
	int dl = 0;
	int cx = ch*256	+cl;
	int dx = dh*256 +dl;
	interrupt(0x13,3*256+1,bx,cx,dx,0);

}

void handleInterrupt21(int ax, int bx, int cx, int dx)
{
	//PrintString("Hello World!\0");
	
if(ax == 0 )
{
PrintString(bx);
}
else if (ax == 1 )
{
//char line[80];
interrupt(0x10,0xE*256 + 0xa,0,0,0);
PrintString("Enter a new line :");
readString(bx);
PrintString(bx);
}
else if (ax == 2)
{
readSector(bx, cx);
}
else if (ax == 3)
{
	readFile(bx,cx);

}
else if (ax == 4)
{
	executeProgram(bx,cx);
}

else if (ax == 5){

    terminate();
}
else if (ax == 6)
{
	writeSector(bx,cx);
}
else if (ax == 7)
{
	deleteFile(bx);
}
else if(ax == 8)
{
	writeFile(bx,cx,dx);
}
}


void readFile(char* fileName , char* buf)
{

//char buffer[512];	
int i=0;
int j=0;
int k=0;
int m=0;
int l=0;
int flag = 0;
int strIndex = 0;
char directory[512];
readSector(directory,2);

	for(i = 0;i<=512;i += 32)
	{
		strIndex = 0;
		
		for (j = i ; j < i + 5 ; j ++)
		{
			if(fileName[strIndex] == directory[j] )
			{
				strIndex++;
			}
			else 
			{
				break;
			}

			if(strIndex == 5 )
			{
				flag = 1;
			}
		}

		if (flag == 1)
		{
			for (k = i + 6 ; i <= i +31  ; k++ )
			{
				if(directory[k] == 00 )
				{
					break;
				}
				
				readSector(buf,directory[k]);
				buf += 512;
			}
		}
	}
	if (flag == 0)
	{
		PrintString("file does not exist\0");
	}
}
void executeProgram(char* name, int segment){
int i;
char readingBuffer[13312];
readFile(name, readingBuffer);
for (i=0; i<13312;i++){
putInMemory(segment,i,readingBuffer[i]);
}
launchProgram(segment);
}


void terminate()
{

	char shell[6];
	shell[0] = 's';
	shell[1] = 'h';
	shell[2] = 'e';
	shell[3] = 'l';
	shell[4] = 'l';
	shell[5] = 0x0;
	makeInterrupt21();
	interrupt(0x21,4,shell,0x2000,0);
}


void deleteFile(char* name)
{
	int flag = 0;
	int strIndex = 0;	
	int firstChar = 0;
	int j = 0;
	int sector;
	char directory[512];
	char map[512];

	readSector(directory,2);	
	readSector(map,1);

	for(firstChar = 0;firstChar<512;firstChar += 32)
	{
		strIndex = 0;
		
		for (j = firstChar ; j < firstChar + 6 ; j++)
		{
				
			if(name[strIndex] == directory[j] )
			{
				strIndex++;
			}
			else 
			{
				
				break;
			}
		}
		if(strIndex == 6 )
			{
				flag = 1;
				break;
			}
	}

	if(flag == 1)
	{
		directory[firstChar] = 0x00;

		firstChar += 6;
		for (j = 0 ; j < 26 ; j++)
		{
			if(directory[firstChar + j] != 0x00)
			{
				sector = directory[firstChar+j];
				map[sector + 1] = 0x00;
			}
			else 
			{
				break;
			}
		}

		writeSector(directory,2);
		writeSector(map,1);
	}
}


void writeFile(char* name, char* buffer, int secNum)
	{
		int j;
		int i;
		int diff;
		int k;
		int secCount;
		int secCheck;
		char directory[512];
		char map[512];
		char temp[512];

		readSector(directory,2);
		readSector(map,1);


			for(i = 0; i<512; i += 32)    // i is the first byte in a file new in directory
			{
				if(directory[i] == 0x00)
				{
					break;
				}
			}
			for(j = i; j <i + 32; j++)
			{
				directory[i+j] = 00;
			}


			for(j = 0; j < 6; j++)
			{
				if(name[j] != '\0')
				{
					directory[i +j] = name[j];
				}
				else
				{
					break;
				}
			}
			for(secCount = 0;secCount < 512;secCount++)
			{
				if(map[secCount] == 0x00)
				{
					secCheck++;
				}
			}

		for(secCount = 0; secCount < secNum && secCheck >= secNum ; secCount ++)
		{ 
			for(k = 3 ; k < 512 ; k++)
			{
				if(map[k] == 0x00)
				{
					map[k] == 0xFF;
					directory[secCount + i + 6] = k - 1;
					writeSector(buffer , k); 
					buffer = &buffer[512];
					break;
				}	
			}
		}

		writeSector(directory,2);
		writeSector(map,1);
		
	}