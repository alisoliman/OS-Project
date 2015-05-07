	void readIN(char line[80]);
int comp(char* s1, char* s2);

int main(){



while(1)
{
char line [80];
interrupt(0x21,0,"SHELL>",0,0);
interrupt(0x21,1,line,0,0);
readIN(line);
}

}

void readIN(char line[80])
{
	char s[80];
	int i ;
	int flag;
	i = 0;
	// while (line[i] != ' ')
	// {
	// 	s[i] =s[i] + line[i];
	// 	i++;
	// }

	// s[i+1] += '\0';
	// //interrupt(0x21,0,s,0,0);
	// flag = comp(s,"view\0");

	if(line[0] == 'v' && line[1]=='i' && line[2] =='e' && line[3] =='w' && line[4] == ' ')
	{
		char* file;
		char buffer[13312];
		
		file = &line[5];
	
		interrupt(0x21,3,file,buffer,0);
		interrupt(0x21,0,buffer,0,0);
	}
	else
	{

		if(line[0] == 'e' && line[1] == 'x' && line[2] == 'e' && line[3] == 'c' && line[4] == 'u' && line[5] == 't' && line[6] == 'e' && line[7] == ' ')
		{
			char* file;
			file = &line[8];	
			interrupt(0x21,4,file,0x2000,0);
		}
		else 
		{
			if(line[0] == 'd' && line[1] == 'e' && line[2] == 'l' && line[3] == 'e' && line[4] == 't' && line[5] == 'e' && line[6] == ' ')
			{
				char* name;
				name = &line[7];
				interrupt(0x21,7,name,0,0);
			}

			else 
			{
				if(line[0] == 'c' && line[1] == 'o' && line[2] == 'p' && line[3] == 'y' && line[4] == ' ')
				{
					int i;
					int j = 0;
					char* file1;
					char* file2;
					char file1Buffer[13312];
					char* command;

					command = &line[5];
					for(i = 0; command[i] != 0x20;i++)
					{
						file1[i] == command[i];
					}

					for(i = i+1;command[i] != 0x20;i++)
					{
						file2[j] == command[i];
						j++;
					}

					interrupt(0x21,3,file1,file1Buffer,0);


				}

				else 
				{
					interrupt(0x21,0,"Bad command!",0,0);
				}
			}
		}
	}
	
}