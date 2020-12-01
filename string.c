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
	size_t i = 0;

	while (*s1 == *s2) {
		if (*s1 == '\0' || i == size)
			return 0;

		s1++, s2++, i++;
	}

	if (*s1 > *s2)
		return 1;

	return -1;
}

char *strcpy(char *dst, const char *src)
{
	char *d = dst;

	while (*src != '\0')
		*d++ = *src++;

	*d = '\0';

	return dst;
}

char *strncpy(char *dst, const char *src, size_t size)
{
	char *d = dst;

	for (size_t i = 0; i < size; i++) {
		if (*src != '\0')
			*dst++ = *src++;
		else
			*d++ = '\0';
	}

	return dst;
}

char *strcat(char *dst, const char *src)
{
	size_t dlen = strlen(dst), slen = strlen(src);

	for(size_t i = 0; i <= slen; i++)
		dst[dlen + i] = src[i];

	return dst;
}

char *strncat(char *dst, const char *src, size_t size)
{
	size_t i, len = strlen (dst);

	for (i = 0; i < size; i++) {
		if (src[i] == '\0')
			break;

		dst[len + i] = src[i];
	}

	dst[len + i] = '\0';

	return dst;
}

char *strchr(const char *str, char c)
{
	for (;;) {
		if (*str == c)
			return (char *) str;

		if (*str++ == '\0')
			break;
	}

	return NULL;
}

char *strrchr(const char *str, char c)
{
	const char *s = str + strlen(str);
	
	for (;;) {
		if (*s == c)
			return (char *) s;

		if (--s < str)
			break;
	}

	return NULL;
}

size_t strspn(const char *dst, const char* src)
{
	size_t c = 0, c1;

	for(size_t i = 0; i < strlen(dst); i++) {
		c1 = c;

		for (size_t j = 0; j < strlen(src); j++) {
			if (src[j] == dst[i]) {
				c++;
				break;
			}
		}

		if (c1 == c)
			break;
	}

	return c;

}

size_t strcspn(const char *dst, const char* src)
{
	size_t i = 0;

	for (size_t i = 0; i < strlen(dst); i++) {
		if (strchr(src, dst[i]))
			break;
	}

	return i;
}
void* memcpy(void * dst, const void* src, size_t count)
{
	char *dstcpy = (char *) dst, *srccpy = (char *) src;

	for(size_t i = 0; i < count; i++) 
		*dstcpy++ = *srccpy++;
	
	return dst;
}
void *memccpy(void *dst, const void * src, int c, size_t count)
{
	char *dstcpy = (char *) dst;
        char *srccpy = (char *) src;

	for(size_t i = 0; i < count; i++) {
                
		*dstcpy++ = *srccpy++;
		if(*dstcpy == c) return dst;
        }

	return NULL;
}
int memcmp(const void* lhs, const void *rhs, size_t count)
{
	char *lhscopy = (char *) lhs;
	char *rhscopy = (char *) rhs;
	
	for(size_t i = 0; i < count; i++) {
	
		if(*lhscopy++ > *rhscopy++)
			return 1;
		
		else if(*lhscopy < *rhscopy)
			return -1;
	}

	return 0;
}
void *memchr(void * ptr, int ch, size_t count)
{
	char *ptrcopy = (char *) ptr;
	
	for (size_t i = 0; i < count; i++) {
        
		if (*ptrcopy == ch)
                	return (char *) ptrcopy;
        }
        
	return NULL;
}
char *strstr(const char *str1, const char *str2)
{
	while ((str1 = strchr(str1, str2[0]))) {
		if (strncmp(str1, str2, strlen(str2)) == 0)
			return (char *) str1;

		str1++;
	}

	return NULL;
}

char *strpbrk(const char *str, const char *chars)
{
	size_t loc;

	loc = strcspn(str, chars);

	if (loc == strlen(str))
		return NULL;

	return (char *) str + loc;
}

char *strtok(char **str, const char *delim)
{
	char *v;
	size_t loc, len = strlen(*str);

	loc = strspn(*str, delim);

	if (loc == len)
		return NULL;

	v = *str += loc;
	loc = strcspn(*str, delim);

	if (loc == strlen(v))
		*str = "";
	else
		*str += loc + 1;

	return v;
}

void *memset(void *dest, int ch, size_t count)
{
	unsigned char *dst = dest, c = ch;

	for (size_t i = 0; i < count; i++)
		*dst++ = c;

	return dest;
}
