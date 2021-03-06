#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// ---------------------------------------------------------------------------
// matrix.c
// ---------------------------------------------------------------------------

void matrixTranslation(float matrix[4][4], float x, float y, float z);
void matrixScale(float matrix[4][4], float x, float y, float z);
void matrixRotationZ(float matrix[4][4], float angle);
void matrixProduct(float ab[4][4], const float a[4][4], const float b[4][4]);
void matrixVectorProduct(float v[4], const float m[4][4], const float x[4]);

// ---------------------------------------------------------------------------
// cam.c
// ---------------------------------------------------------------------------

typedef struct {
    float center[2], focus[2], zoom, angle, ar;
} Cam;
Cam cam(float ar);
float camGetW(const Cam *c);
void camSetW(Cam *c, float w);
float camGetH(const Cam *c);
void camSetH(Cam *c, float h);
void camGetSize(const Cam *c, float size[2]);
void camSetMinSize(Cam *c, float w, float h);
void camSetMaxSize(Cam *c, float w, float h);
void camSetMinRect(Cam *c, float x, float y, float w, float h);
void camSetMaxRect(Cam *c, float x, float y, float w, float h);
void camGetRect(const Cam *c, float rect[4]);
void camMatrix(const Cam *c, float m[4][4]);

// ---------------------------------------------------------------------------
// bmp.c
// ---------------------------------------------------------------------------

typedef struct {
    size_t w, h, l;
    uint8_t *b;
} Bmp;

Bmp *bmpNew(size_t w, size_t h, size_t l, Bmp *b);
Bmp *bmpDup(const Bmp *s, Bmp *d);
Bmp *bmpDel(Bmp *bmp, bool freeHandle);
bool bmpGet(const Bmp *bmp, size_t x, size_t y, size_t z);
void bmpSet(Bmp *bmp, size_t x, size_t y, size_t z, bool b);

// ---------------------------------------------------------------------------
// coll.c
// ---------------------------------------------------------------------------

typedef struct {
    float x, y, w, h;
} CollRect;

typedef struct {
    bool is;
    float south, north, west, east;
} CollPen;

typedef struct {
    float x, y, angle;
} CollRay;

typedef struct {
    float x, y, angle, len;
} CollLine;

CollPen collBmpRect(const Bmp b, CollRect r);
CollPen collRect(CollRect a, CollRect b);
float collRayLine(CollRay r, CollLine line);
float collRayRect(CollRay r, CollRect rect);

// ---------------------------------------------------------------------------
// r.c
// ---------------------------------------------------------------------------

typedef enum {
    R_CAPABILITY_DEPTH_TEST,
    R_CAPABILITY_TRANSPARENCY
} RCapability;

typedef enum {
    R_DRAW_MODE_POINTS,
    R_DRAW_MODE_LINES,
    R_DRAW_MODE_LINE_LOOP,
    R_DRAW_MODE_TRIANGLES,
    R_DRAW_MODE_TRIANGLE_STRIP,
    R_DRAW_MODE_TRIANGLE_FAN
} RDrawMode;

typedef struct {
    float x, y, z;
    unsigned char r, g, b, a;
} RVertex;

void rInit(void);
void rExit(void);
bool rCapability(RCapability capability, bool enabled);
void rPipeModel(const float m[4][4],const float c[4],float M[4][4],float C[4]);
void rPipeSpace(const float m[4][4],const float c[4],float M[4][4],float C[4]);
void rPipeWorld(const float m[4][4],const float c[4],float M[4][4],float C[4]);
void rClear(const float c[4]);
void rDraw(RDrawMode mode, size_t n, const RVertex *v);
void rDrawIndexed(RDrawMode mode,size_t ni,const uint16_t *i,const RVertex *v);
void rViewport(int x, int y, int w, int h);

// ---------------------------------------------------------------------------
// batch.c
// ---------------------------------------------------------------------------

typedef struct {
    float w, h, l;
    size_t ni, mi, nv, mv;
    uint16_t *i;
    RVertex *v;
} Batch;

Batch *batchDup(const Batch *s, Batch *d);
Batch *batchDel(Batch *b, bool freeHandle);
void batch(Batch *b, size_t ni, const uint16_t *i, size_t nv, const RVertex *v);
void batchClear(Batch *b);
void batchRect(Batch *b, CollRect r, const uint8_t rgba[4]);
void batchLine(Batch *b, CollLine l, float t, const uint8_t rgba[4]);
void batchRectLine(Batch *b, CollRect r, float ti, float to, const uint8_t rgba[4]);

// ---------------------------------------------------------------------------
// audio.c
// ---------------------------------------------------------------------------

typedef struct AudioSound AudioSound;
typedef struct AudioMusic AudioMusic;

void audioInit(void);
void audioExit(void);
AudioSound *audioSoundLoad(const char *path);
void audioSoundFree(AudioSound *sound);
void audioSoundPlay(const AudioSound *sound);
void audioSoundStop(const AudioSound *sound);
bool audioSoundPlaying(const AudioSound *sound);
AudioMusic *audioMusicLoad(const char *path);
void audioMusicFree(AudioMusic *music);
void audioMusicPlay(AudioMusic *music, bool repeat);
void audioMusicStream(AudioMusic *music);
void audioMusicPause(const AudioMusic *music);
void audioMusicStop(const AudioMusic *music);
bool audioMusicPlaying(const AudioMusic *music);
