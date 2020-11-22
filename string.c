#include <string.h>

size_t strlen(const char *str) 
{
        size_t len = 0;
        while (str[len])
                len++;
        return len;
}
size_t strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2) {
		if (*s1 == '\0')
			return 0;

		s1++, s2++;
	}

	if (*s1 > *s2)
		return 1;

	return -1;
}
size_t strncmp(const char *s1, const char *s2, size_t size)
{
	size_t i=0;
	while (*s1 == *s2 && i < size) {
		if(*s1 == '\0')
			return 0;
		s1++, s2++, i++;
	}
	if(*s1 > *s2)
		return 1;
	return -1;
}
char *strcpy(char *dst, const char *src)
{
	for (int i = 0; *src != '\0'; i++)
		*dst++ = *src++;

	return dst;
}
char *strncpy(char *dst, const char *src, size_t size)
{
	for(size_t i = 0; i < size; i++)
		*dst++ = *src++;
	return dst;
}
char *strcat(char *dst, const char *src)
{
	size_t len;
	len = strlen (dst);
	for(size_t i = 0; i <= strlen(src); i++)
		dst[len + i] = src[i];
	return dst;
}
char *strncat(char *dst, const char *src, size_t size)
{
	size_t len;
	len = strlen (dst);
	for(size_t i = 0; i < size; i++)
		dst[len +i] = src[i];
	dst[len+size] = '\0';
	return dst;
}
char *strchr(char *str, char c)
{
	size_t from = 0;
	for(size_t i = 0; i < strlen(str); i++)
		if(str[i] == c) {
			from = i;
			break;
		}
	for(size_t i = 0; i < strlen(str); i++)
		str[i] = str[from + i];
	if(from == 0) return "\0";
	else return str;
}
char *strrchr(char *str, char c)
{
	size_t from = 0;
        for(size_t i = 0; i < strlen(str); i++)
                if(str[i] == c) {
                        from = i;
                }       
        for(size_t i = 0; i < strlen(str); i++)       
                str[i] = str[from + 1 + i];
        if(from == 0) return "\0"; 
        else return str;
}
size_t strspn(char *dst, char* src)
{
	size_t c = 0;
	for(size_t i = 0; i < strlen(dst); i++)
		for(size_t j = 0; j < strlen(src); j++)
			if(src[j] == dst[i]) {
				c++;
				continue;
			}
			else if(j == strlen(src) - 1) 
				break;
	return c;

}
size_t strcspn(char *dst, char* src)
{
        size_t c = 0;
        for(size_t i = 0; i < strlen(dst); i++)
                for(size_t j = 0; j < strlen(src); j++)
                        if(src[j] == dst[i]) {
                                c++;
                                break;
                        }
                        else if(j == strlen(src) - 1)
                                c++;
        return c;

}

