#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LINE 128	//the max characters in one line for ini file

typedef enum _StatusRet{
	ERR_NON = 0,
	ERR_MEM,
	ERR_FILE,
	ERR_INI,
	ERR_NON_EXIST,
}StatusRet;

enum STATE{
	STATE_IDLE,
	STATE_COMMEMT,
	STATE_SECT,
	STATE_KEY,
	STATE_VALUE,
};
static void str_remove_bound_space(char *str)
{
	int i;
	char *ps = str;
	int len = strlen(str);

	if (ps == NULL)
	{
		return;
	}
	i = 0;
	while ((*ps == ' ') && (*ps != '\0'))
	{		
		ps++;
		i++;
	}
	if (len - i > 0)
	{
		memmove(str, ps, len-i+1);//remove the left space
	}
	
	while (((len - i) > 0) && (*(str+len-i-1) == ' '))//remove the right space
	{
		i++;
	}
	*(str+len-i) = '\0';
}
static StatusRet find_string(char *buf, const char* sect, const char *key, const char *file)
{
	char *text, *p, *ps, *ptemp;
	char first_flg = 0;//indicate that have been read from key line
	int lentext;//the read line length,wipe off 0x0a
	FILE *fd;
	enum STATE state = STATE_IDLE;
	StatusRet ret = ERR_NON;

	if ((fd = fopen(file,"rt")) == NULL)
	{
		return ERR_FILE;
	}
	if ((text = (char*)malloc(MAX_LINE + 1)) == NULL)
	{
		fclose(fd);
		return ERR_MEM;
	}
	ptemp = (char*)malloc(32);

	fseek(fd, 0, SEEK_SET);
	while (fgets(text, MAX_LINE, fd) != NULL)
	{
		lentext = strlen(text);//wipe off the LF character for ini_get_string
		if (*(text+lentext-1) == 0x0a)//
		{
			*(text+lentext-1) = '\0';
		}
		
		p = text;
		while (*p != '\0')
		{
			switch(state)
			{
			case STATE_IDLE:
				if (*p == '[')
				{
					state = STATE_SECT;
					ps = p + 1;
				} 
				else
				{
					*p = '\0';
					continue;//skip the current line
				}
				break;
			case STATE_SECT:
				if (*p == ']')
				{
					*p = '\0';
					if (strcmp(ps, sect))//not identical
					{
						state = STATE_IDLE;
					} 
					else
					{
						state = STATE_KEY;
					}
					continue;//skip the current line
				} 
				else
				{
					if (*(p+1) == '\0')
					{
						ret = ERR_INI;
						goto out;
					}
				}
				break;
			case STATE_KEY:
				if ((*p == ';') || (*(p+1) == '\0'))//exit before '='
				{
					*p = '\0';
					if(first_flg)//handle the found key which has not '='&value
					{
						first_flg = 0;
						str_remove_bound_space(ps);
						if (!strcmp(ps, key))//identical
						{
							*buf = '\0';
							ret =  ERR_INI;
							goto out;
						}
						else
						{
							ret = ERR_NON_EXIST;
						}
					}
					else//if hasn't found key,regard as none exist
					{
						ret = ERR_NON_EXIST;
					}
					*p = '\0';
					continue;//skip the current line
				}
				else
					if ((*p == '[') && (first_flg == 0))//the section doesn't have key
					{
						*buf = '\0';
						ret =  ERR_INI;
						goto out;
					}
					else
						if (*p == '=')
						{
							first_flg = 0;
							strcpy(ptemp,p+1);
							*p = '\0';
							str_remove_bound_space(ps);
							if (strcmp(ps, key))//not identical
							{
								continue;//skip the current line
							} 
							else//get the value
							{
								p = ps = ptemp;
								while (*p != '\0' && (*p != ';'))
								{
									p++;
								}
								*p = '\0';
								str_remove_bound_space(ps);
								strcpy(buf, ps);
								ret = ERR_NON;
								goto out;
							}
						}
						else 
							if(!first_flg)//first key character in the key line
							{
								first_flg = 1;
								ps = p;
							}
				break;
			default:
				break;
			}
			p++;
		}
	}
out:
	free(ptemp);
	free(text);
	fclose(fd);

	return ret;
}
int ini_get_int(const char* sect, const char *key, int defa, const char *file)
{
	int ret;
	char *buf = malloc(32);
	memset(buf, 0, 32);

	if(find_string(buf, sect, key, file))
	{
		ret = defa;//something wrong in ini file ,not section ,not key and so on
	}
	else
	{
		ret = atoi(buf);
	}
	free(buf);

	return ret;
}
int ini_get_string(const char* sect, const char *key, char *strdefa, char * buf, int size, const char *file)
{
	char * tempbuf = malloc(32);
	int lendefa,retlen;

	memset(tempbuf, 0, 32);

	if(find_string(tempbuf, sect, key, file))
	{
		lendefa = strlen(strdefa);
		retlen = lendefa < size ? lendefa:size;
		strncpy(buf,strdefa,retlen);//something wrong in ini file ,not section ,not key and so on
	}
	else
	{
		retlen = 32 < size ? 32:size;
		strncpy(buf,tempbuf,retlen);
	}
	*(buf+retlen) = '\0';
	free(tempbuf);
	
	return retlen;
}