/* gcc_compat.c -- GCC replacements for SAS/C runtime functions used by AmiFTP.
 * Also provides global symbols that SAS/C startup provided automatically.
 *
 * SAS/C provided these as library functions; under GCC/libnix they do not exist.
 * All implementations use only AmigaDOS/exec primitives.
 */

#ifdef __GNUC__

#include <exec/types.h>
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <workbench/startup.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/arexx.h>
#include <string.h>

/* ARexxBase: strong definition so libstubs.a(arexx.o) is not pulled in.
 * libstubs tries to open "arexx.library" (OS3.5 name); on OS3.2 it's
 * "arexx.class". INIT_3_ReActionLibs() opens the correct name. */
struct Library *ARexxBase = NULL;

/* __WBenchMsg: libnix provides this as a common symbol in ncrt0.o, but linking
 * against it as 'extern' from another TU fails because common symbols don't satisfy
 * extern references without an explicit definition. Provide the definition here. */
struct WBStartup *__WBenchMsg = NULL;

/* _ProgramName: provided by SAS/C startup; used by amitcp.c for usergroup context.
 * Declare as a BSTR (first byte = length, rest = chars, no NUL needed) but
 * usergroup.library actually treats it as a plain C string for display. */
STRPTR _ProgramName = (STRPTR)"AmiFTP";

/* strmfp(dest, dir, file) -- combine directory path and filename.
 * Equivalent to SAS/C strmfp: builds "dir/file" or "dir:file" as appropriate.
 * Uses AmigaDOS AddPart() semantics. */
void strmfp(char *dest, const char *dir, const char *file)
{
    strcpy(dest, dir);
    if (dir[0] != '\0') {
        char lastc = dir[strlen(dir)-1];
        if (lastc != ':' && lastc != '/')
            strcat(dest, "/");
    }
    strcat(dest, file);
}

/* stcgfn(dest, path) -- extract filename component from a full path.
 * Equivalent to SAS/C stcgfn: finds last ':' or '/' separator. */
void stcgfn(char *dest, const char *path)
{
    const char *p = path;
    const char *last = path;
    while (*p) {
        if (*p == ':' || *p == '/')
            last = p + 1;
        p++;
    }
    strcpy(dest, last);
}

/* geta4() -- SAS/C small data base register reload.
 * Under GCC -noixemul there is no A4 small data segment; this is a no-op. */
void geta4(void)
{
}

/* getfa(path) -- return 1 if path is a directory, 0 if a file, -1 if not found.
 * Matches the SAS/C getfa() semantics used in AmiFTP: caller checks ==1 for dir. */
int getfa(const char *path)
{
    BPTR lock = Lock((CONST_STRPTR)path, ACCESS_READ);
    if (!lock)
        return -1;
    struct FileInfoBlock *fib = (struct FileInfoBlock *)AllocVec(sizeof(*fib), MEMF_CLEAR);
    int result = 0;
    if (fib) {
        if (Examine(lock, fib))
            result = (fib->fib_DirEntryType > 0) ? 1 : 0;
        FreeVec(fib);
    }
    UnLock(lock);
    return result;
}

/* getdfs(path, info) -- fill InfoData for the volume containing path.
 * Returns 1 on success, 0 on failure. */
int getdfs(const char *path, struct InfoData *info)
{
    BPTR lock = Lock((CONST_STRPTR)path, ACCESS_READ);
    if (!lock)
        return 0;
    int ok = (int)Info(lock, info);
    UnLock(lock);
    return ok;
}

#endif /* __GNUC__ */
