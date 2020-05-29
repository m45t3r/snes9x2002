#include <SDL/SDL.h>
#include "main.h"
#include "snes9x.h"
#include "soundux.h"
#include "memmap.h"
#include "apu.h"
#include "cheats.h"
#include "display.h"
#include "gfx.h"
#include "cpuexec.h"
// #include "spc7110.h"
#include "srtc.h"
#include "sa1.h"
#include "scaler.h"

bool8 ROMAPUEnabled = 0;

const char* S9xGetFilename(const char* in)
{
   static char filename [PATH_MAX + 1];
   char drive [_MAX_DRIVE + 1];
   char dir [_MAX_DIR + 1];
   char fname [_MAX_FNAME + 1];
   char ext [_MAX_EXT + 1];
   _splitpath(Memory.ROMFilename, drive, dir, fname, ext);
   _makepath(filename, drive, dir, fname, in);
   return filename;
}

void S9xMessage(int a, int b, const char* msg)
{
   //printf("%s\n", msg);
}

const char* S9xGetDirectory(uint32_t dirtype) { return NULL; }

void _splitpath (const char *path, char *drive, char *dir, char *fname, char *ext)
{
    char *slash = strrchr ((char *) path, SLASH_CHAR);
    char *dot   = strrchr ((char *) path, '.');

    *drive = '\0';

    if (dot && slash && dot < slash)
    {
        dot = 0;
    }

    if (!slash)
    {
        *dir = '\0';
        strcpy (fname, path);

        if (dot)
        {
            fname[dot - path] = '\0';
            strcpy (ext, dot + 1);
        }
        else
        {
            *ext = '\0';
        }
    }
    else
    {
        strcpy (dir, path);
        dir[slash - path] = '\0';
        strcpy (fname, slash + 1);

        if (dot)
        {
            fname[(dot - slash) - 1] = '\0';
            strcpy (ext, dot + 1);
        }
        else
        {
            *ext = '\0';
        }
    }

    return;
}

void _makepath (char *path, const char *drive, const char *dir, const char *fname,const char *ext)
{
    if (dir && *dir)
    {
        strcpy (path, dir);
        strcat (path, "/");
    }
    else
        *path = '\0';

    strcat (path, fname);

    if (ext && *ext)
    {
        strcat (path, ".");
        strcat (path, ext);
    }

    return;
}


bool8_32 S9xReadMousePosition(int which1, int* x, int* y, uint32* buttons)
{
   (void) which1;
   (void) x;
   (void) y;
   (void) buttons;
   return false;
}

bool8_32 S9xReadSuperScopePosition(int* x, int* y, uint32* buttons)
{
   (void) x;
   (void) y;
   (void) buttons;
   return true;
}

// S9x function stubs
const char* S9xGetFilenameInc(const char* in) { return in; }
const char *S9xGetHomeDirectory() { return NULL; }
const char *S9xGetSnapshotDirectory() { return NULL; }
const char *S9xGetROMDirectory() { return NULL; }

int s_open(const char *fname, const char *mode) { return 0; }
int s_read(void *p, int l) { return 0; }
int s_write(void *p, int l) { return 0; }
void s_close(void) {}

int  (*statef_open)(const char *fname, const char *mode) = s_open;
int  (*statef_read)(void *p, int l) = s_read;
int  (*statef_write)(void *p, int l) = s_write;
void (*statef_close)(void) = s_close;

const char *S9xBasename (const char *filename) {
   const char *emptyString = "";
   return emptyString;
}

void S9xSetPalette() {}

void S9xLoadSDD1Data(void) {}

void S9xExit(void) {
   exit(1);
}

bool8 S9xInitUpdate() {
   return true;
};

bool8 S9xContinueUpdate(int width, int height) { return true; }

bool8 S9xDeinitUpdate(int width, int height, bool8 sixteen_bit)
{
   // TODO: Do not call if !IPPU.RenderThisFrame?
   Update_Video_Ingame();

   return true;
}

void S9xToggleSoundChannel (int channel) {}

const char *S9xStringInput(const char *message) { return NULL; }

bool JustifierOffscreen(void)
{
   return false;
}

void JustifierButtons(uint32_t* justifiers)
{
   (void) justifiers;
}
