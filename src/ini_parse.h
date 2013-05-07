#ifndef _INI_PARSE_H
#define _INI_PARSE_H

extern int ini_get_int(const char* sect, const char *key, int defa, const char *file);
extern int ini_get_string(const char* sect, const char *key, char *strdefa, char * buf, int size, const char *file);

#endif