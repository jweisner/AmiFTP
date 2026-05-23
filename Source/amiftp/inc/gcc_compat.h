#ifndef GCC_COMPAT_H
#define GCC_COMPAT_H

#ifdef __GNUC__

#include <dos/dos.h>

extern STRPTR _ProgramName;
void strmfp(char *dest, const char *dir, const char *file);
void stcgfn(char *dest, const char *path);
void geta4(void);
int  getfa(const char *path);
int  getdfs(const char *path, struct InfoData *info);

#endif /* __GNUC__ */

#endif /* GCC_COMPAT_H */
