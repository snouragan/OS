#include <string.h>

int strcmp(const char *s1, const char *s2)
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

char *strcpy(char *dst, const char *src)
{
	int i;

	for (int i = 0; *src != '\0'; i++)
		dst[i] = *src++;

	return dst;
}
