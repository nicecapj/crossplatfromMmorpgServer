#pragma once

#ifndef __STDC_WANT_SECURE_LIB__
#define vsprintf_s(buf, size, fmt, ...)  vsprintf(buf, fmt, ##__VA_ARGS__)
#define strcpy_s(dst, size, src)         strcpy(dst, src)
#define scanf_s(fmt, size, ...)          scanf(fmt, ##__VA_ARGS__)
#define memmove_s(dst, size, src, count) memmove(dst, src, count)
#define gets_s(buf, size)                gets(buf)
#endif // __STDC_WANT_SECURE_LIB__