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
			*d++ = '\0;
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
	size_t i, len= strlen (dst);

	for (size_t i = 0; i < size; i++) {
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
			return str;

		if (*str++ == '\0')
			break;
	}

	return NULL;
}

char *strrchr(cosnt char *str, char c)
{
	const char *s = str + strlen(str);
	
	for (;;) {
		if (*s == c)
			return s;

		if (--s < str)
			break;
	}

	return NULL;
}

size_t strspn(char *dst, char* src)
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
