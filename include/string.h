#include <stddef.h>
size_t strlen(const char *);
size_t strcmp(const char *, const char *);
size_t strncmp(const char *, const char *, size_t);
char *strcpy(char *, const char *);
char *strncpy(char *, const char *, size_t);
char *strcat(char *, const char *);
char *strncat(char *, const char *, size_t);
char *strchr(const char *, char);
char *strrchr(const char *, char);
size_t strspn(const char *, const char *);
size_t strcspn(const char *, const char *);
void *memcpy(void *, const void*, size_t);
void *memccpy(void *, const void *, int, size_t);
void *memmove(void *, const void *, size_t);
int memcmp(const void *, const void *, size_t);
void *memchr(void *, int, size_t);
void *memset(void *, int, size_t);
char *strstr(const char *, const char *);
