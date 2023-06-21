int strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

char* strcpy(char* destination, const char* source)
{
    char* original_destination = destination;

    while (*source)
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';

    return original_destination;
}
