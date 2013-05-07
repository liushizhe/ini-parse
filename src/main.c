#include <stdio.h>
#include "ini_parse.h"

#define STR_LEN 6

void main()
{
	char *buf = (char*)malloc(STR_LEN);

	printf("sect1,key1 = %d\n", ini_get_int("sect1", "key1", 0, "test.ini"));
	printf("sect1,key2 = %d\n", ini_get_int("sect1", "key2", 0, "test.ini"));
	printf("sect1,key3 = %d\n", ini_get_int("sect1", "key3", 0, "test.ini"));
	printf("sect1,key4 = %d\n", ini_get_int("sect1", "key4", 0, "test.ini"));
	printf("sect1,key5 = %d\n", ini_get_int("sect1", "key5", 0, "test.ini"));
	printf("sect1,key6 = %d\n", ini_get_int("sect1", "key6", 0, "test.ini"));
	printf("sect1,key7 = %d\n", ini_get_int("sect1", "key7", 0, "test.ini"));

	printf("sect2,key1 = %d\n", ini_get_int("sect2", "key1", 0, "test.ini"));
	printf("sect2,key2 = %d\n", ini_get_int("sect2", "key2", 0, "test.ini"));
	printf("sect2,key3 = %d\n", ini_get_int("sect2", "key3", 0, "test.ini"));

	printf("sect3,key1 = %d\n", ini_get_int("sect3", "key1", 0, "test.ini"));
	printf("sect3,key2 = %d\n", ini_get_int("sect3", "key2", 0, "test.ini"));
	printf("sect3,key3 = %d\n", ini_get_int("sect3", "key3", 0, "test.ini"));

	printf("\n");
	
	memset(buf, 0, STR_LEN);
	ini_get_string("sect4", "key1", "1", buf, STR_LEN, "test.ini");
	printf("sect4,key1 = %s\n", buf);

	memset(buf, 0, STR_LEN);
	ini_get_string("sect4", "key2", "2", buf, STR_LEN, "test.ini");
	printf("sect4,key2 = %s\n", buf);

	memset(buf, 0, STR_LEN);
	ini_get_string("sect4", "key3", "3", buf, STR_LEN, "test.ini");
	printf("sect4,key3 = %s\n", buf);

	memset(buf, 0, STR_LEN);
	ini_get_string("sect4", "key4", "4", buf, STR_LEN, "test.ini");
	printf("sect4,key4 = %s\n", buf);

	memset(buf, 0, STR_LEN);
	ini_get_string("sect4", "key5", "5", buf, STR_LEN, "test.ini");
	printf("sect4,key5 = %s\n", buf);

	memset(buf, 0, STR_LEN);
	ini_get_string("sect4", "key6", "6", buf, STR_LEN, "test.ini");
	printf("sect4,key6 = %s\n", buf);

	memset(buf, 0, STR_LEN);
	ini_get_string("sect4", "key7", "7", buf, STR_LEN, "test.ini");
	printf("sect4,key7 = %s\n", buf);

	free(buf);
}
