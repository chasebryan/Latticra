#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720
#define FPS 30
#define DEFAULT_SECONDS 84
#define SCENES 7
#define TAU 6.28318530717958647692f
#define PI_REC 3.141519f

typedef struct { float r, g, b; } Color;

static unsigned char *fb;

static const Color C_BLACK  = {  2,   1,   8};
static const Color C_RED    = {255,  35,  64};
static const Color C_PINK   = {255,  48, 210};
static const Color C_PURPLE = {178,  62, 255};
static const Color C_BLUE   = { 45, 190, 255};
static const Color C_GREEN  = { 70, 255, 155};
static const Color C_GOLD   = {255, 205,  55};
static const Color C_WHITE  = {255, 245, 250};

static float clampf(float v, float lo, float hi) { return v < lo ? lo : (v > hi ? hi : v); }
static float mixf(float a, float b, float t) { return a + (b - a) * t; }
static float smoothstepf(float e0, float e1, float x) {
    float t = clampf((x - e0) / (e1 - e0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}
static Color cmix(Color a, Color b, float t) {
    t = clampf(t, 0.0f, 1.0f);
    Color c = { mixf(a.r,b.r,t), mixf(a.g,b.g,t), mixf(a.b,b.b,t) };
    return c;
}
static uint32_t hash_u32(uint32_t x) {
    x ^= x >> 16; x *= 0x7feb352dU; x ^= x >> 15; x *= 0x846ca68bU; x ^= x >> 16;
    return x;
}
static float rnd01(uint32_t n) { return (hash_u32(n) & 0xFFFFFF) / 16777215.0f; }

static inline void blend_px(int x, int y, float r, float g, float b, float a) {
    if ((unsigned)x >= WIDTH || (unsigned)y >= HEIGHT) return;
    a = clampf(a, 0.0f, 1.0f);
    int k = (y * WIDTH + x) * 3;
    fb[k+0] = (unsigned char)clampf(fb[k+0]*(1.0f-a) + r*a, 0, 255);
    fb[k+1] = (unsigned char)clampf(fb[k+1]*(1.0f-a) + g*a, 0, 255);
    fb[k+2] = (unsigned char)clampf(fb[k+2]*(1.0f-a) + b*a, 0, 255);
}
static inline void add_px(int x, int y, float r, float g, float b, float a) {
    if ((unsigned)x >= WIDTH || (unsigned)y >= HEIGHT) return;
    int k = (y * WIDTH + x) * 3;
    int nr = fb[k+0] + (int)(r * a);
    int ng = fb[k+1] + (int)(g * a);
    int nb = fb[k+2] + (int)(b * a);
    fb[k+0] = (unsigned char)(nr > 255 ? 255 : nr);
    fb[k+1] = (unsigned char)(ng > 255 ? 255 : ng);
    fb[k+2] = (unsigned char)(nb > 255 ? 255 : nb);
}

static void clear_frame(float t) {
    for (int y = 0; y < HEIGHT; ++y) {
        float fy = (float)y / (float)HEIGHT;
        for (int x = 0; x < WIDTH; ++x) {
            float fx = (float)x / (float)WIDTH;
            float vignette = 1.0f - 0.72f * hypotf(fx - 0.5f, fy - 0.5f);
            float wave = 0.5f + 0.5f * sinf(8.0f*fx + 5.0f*fy + 0.25f*t);
            int k = (y * WIDTH + x) * 3;
            fb[k+0] = (unsigned char)clampf((5.0f + 14.0f*wave) * vignette, 0, 255);
            fb[k+1] = (unsigned char)clampf((1.0f +  4.0f*wave) * vignette, 0, 255);
            fb[k+2] = (unsigned char)clampf((14.0f + 30.0f*wave) * vignette, 0, 255);
        }
    }
    for (int i = 0; i < 800; ++i) {
        int x = (int)(rnd01(i*29u + 3u) * WIDTH);
        int y = (int)fmodf(rnd01(i*41u + 9u) * HEIGHT + t*(8.0f + 12.0f*rnd01(i)), (float)HEIGHT);
        float tw = 0.25f + 0.75f * sinf(t*2.7f + i*0.91f);
        add_px(x, y, 55, 20, 75, 0.18f + 0.20f*tw);
    }
}

static void rect_blend(int x0, int y0, int x1, int y1, Color c, float a) {
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > WIDTH) x1 = WIDTH;
    if (y1 > HEIGHT) y1 = HEIGHT;
    for (int y = y0; y < y1; ++y) for (int x = x0; x < x1; ++x) blend_px(x, y, c.r, c.g, c.b, a);
}
static void disc_add(float cx, float cy, float rad, Color c, float p) {
    int x0 = (int)floorf(cx - rad), x1 = (int)ceilf(cx + rad);
    int y0 = (int)floorf(cy - rad), y1 = (int)ceilf(cy + rad);
    float rr = rad * rad;
    for (int y = y0; y <= y1; ++y) for (int x = x0; x <= x1; ++x) {
        float dx = x + 0.5f - cx, dy = y + 0.5f - cy;
        float d2 = dx*dx + dy*dy;
        if (d2 <= rr) {
            float f = 1.0f - d2 / rr;
            add_px(x, y, c.r, c.g, c.b, p*f*f);
        }
    }
}
static void line_add(float x0, float y0, float x1, float y1, Color c, float p) {
    float dx = x1 - x0, dy = y1 - y0;
    int steps = (int)fmaxf(fabsf(dx), fabsf(dy));
    if (steps < 1) steps = 1;
    for (int i = 0; i <= steps; ++i) {
        float u = (float)i / (float)steps;
        add_px((int)(x0 + dx*u), (int)(y0 + dy*u), c.r, c.g, c.b, p);
    }
}
static void line_glow(float x0, float y0, float x1, float y1, Color c, float thick, float p) {
    float dx = x1 - x0, dy = y1 - y0;
    int steps = (int)(hypotf(dx, dy) / 2.2f) + 1;
    for (int i = 0; i <= steps; ++i) {
        float u = (float)i / (float)steps;
        disc_add(x0 + dx*u, y0 + dy*u, thick, c, p);
    }
}
static void circle_glow(float cx, float cy, float r, Color c, float thick, float p) {
    int seg = (int)clampf(r * 1.35f, 72, 280);
    float px = cx + r, py = cy;
    for (int i = 1; i <= seg; ++i) {
        float a = TAU * i / (float)seg;
        float x = cx + cosf(a)*r, y = cy + sinf(a)*r;
        line_glow(px, py, x, y, c, thick, p);
        px = x; py = y;
    }
}
static void ellipse_glow(float cx, float cy, float rx, float ry, Color c, float thick, float p) {
    int seg = 240;
    float px = cx + rx, py = cy;
    for (int i = 1; i <= seg; ++i) {
        float a = TAU * i / (float)seg;
        float x = cx + cosf(a)*rx, y = cy + sinf(a)*ry;
        line_glow(px, py, x, y, c, thick, p);
        px = x; py = y;
    }
}
static void poly_glow(float cx, float cy, float r, int n, float rot, Color c, float thick, float p) {
    float px = cx + cosf(rot)*r, py = cy + sinf(rot)*r;
    for (int i = 1; i <= n; ++i) {
        float a = rot + TAU*i/(float)n;
        float x = cx + cosf(a)*r, y = cy + sinf(a)*r;
        line_glow(px, py, x, y, c, thick, p);
        px = x; py = y;
    }
}

/* 5x7 built-in font. */
static const unsigned char *glyph(char ch) {
    static const unsigned char BL[7]={0,0,0,0,0,0,0};
    static const unsigned char A[7]={14,17,17,31,17,17,17}; static const unsigned char B[7]={30,17,17,30,17,17,30};
    static const unsigned char C[7]={15,16,16,16,16,16,15}; static const unsigned char D[7]={30,17,17,17,17,17,30};
    static const unsigned char E[7]={31,16,16,30,16,16,31}; static const unsigned char F[7]={31,16,16,30,16,16,16};
    static const unsigned char G[7]={15,16,16,23,17,17,15}; static const unsigned char HH[7]={17,17,17,31,17,17,17};
    static const unsigned char I[7]={31,4,4,4,4,4,31};     static const unsigned char J[7]={1,1,1,1,17,17,14};
    static const unsigned char K[7]={17,18,20,24,20,18,17}; static const unsigned char L[7]={16,16,16,16,16,16,31};
    static const unsigned char M[7]={17,27,21,21,17,17,17}; static const unsigned char N[7]={17,25,21,19,17,17,17};
    static const unsigned char O[7]={14,17,17,17,17,17,14}; static const unsigned char P[7]={30,17,17,30,16,16,16};
    static const unsigned char Q[7]={14,17,17,17,21,18,13}; static const unsigned char R[7]={30,17,17,30,20,18,17};
    static const unsigned char S[7]={15,16,16,14,1,1,30};   static const unsigned char T[7]={31,4,4,4,4,4,4};
    static const unsigned char U[7]={17,17,17,17,17,17,14}; static const unsigned char V[7]={17,17,17,17,17,10,4};
    static const unsigned char WW[7]={17,17,17,21,21,21,10};static const unsigned char X[7]={17,17,10,4,10,17,17};
    static const unsigned char Y[7]={17,17,10,4,4,4,4};     static const unsigned char Z[7]={31,1,2,4,8,16,31};
    static const unsigned char N0[7]={31,17,19,21,25,17,31}; static const unsigned char N1[7]={4,12,4,4,4,4,14};
    static const unsigned char N2[7]={30,1,1,30,16,16,31};  static const unsigned char N3[7]={30,1,1,14,1,1,30};
    static const unsigned char N4[7]={18,18,18,31,2,2,2};   static const unsigned char N5[7]={31,16,16,30,1,1,30};
    static const unsigned char N6[7]={15,16,16,30,17,17,14}; static const unsigned char N7[7]={31,1,2,4,8,8,8};
    static const unsigned char N8[7]={14,17,17,14,17,17,14}; static const unsigned char N9[7]={14,17,17,15,1,1,30};
    static const unsigned char DASH[7]={0,0,0,31,0,0,0}; static const unsigned char UND[7]={0,0,0,0,0,0,31};
    static const unsigned char EQ[7]={0,31,0,0,31,0,0};  static const unsigned char PLUS[7]={0,4,4,31,4,4,0};
    static const unsigned char GT[7]={16,8,4,2,4,8,16};  static const unsigned char LT[7]={1,2,4,8,4,2,1};
    static const unsigned char SL[7]={1,2,4,8,16,0,0};   static const unsigned char LP[7]={2,4,8,8,8,4,2};
    static const unsigned char RP[7]={8,4,2,2,2,4,8};    static const unsigned char LB[7]={14,8,8,8,8,8,14};
    static const unsigned char RB[7]={14,2,2,2,2,2,14};  static const unsigned char COL[7]={0,4,4,0,4,4,0};
    static const unsigned char DOT[7]={0,0,0,0,0,12,12}; static const unsigned char COM[7]={0,0,0,0,0,4,8};
    static const unsigned char STAR[7]={0,21,14,31,14,21,0}; static const unsigned char HASH[7]={10,31,10,10,31,10,0};
    static const unsigned char BAR[7]={4,4,4,4,4,4,4};   static const unsigned char APOS[7]={4,4,8,0,0,0,0};
    static const unsigned char CARET[7]={4,10,17,0,0,0,0}; static const unsigned char AMP[7]={12,18,20,8,21,18,13};
    if (ch >= 'a' && ch <= 'z') ch = (char)(ch - 32);
    switch (ch) {
        case 'A':return A; case 'B':return B; case 'C':return C; case 'D':return D; case 'E':return E; case 'F':return F;
        case 'G':return G; case 'H':return HH; case 'I':return I; case 'J':return J; case 'K':return K; case 'L':return L;
        case 'M':return M; case 'N':return N; case 'O':return O; case 'P':return P; case 'Q':return Q; case 'R':return R;
        case 'S':return S; case 'T':return T; case 'U':return U; case 'V':return V; case 'W':return WW; case 'X':return X;
        case 'Y':return Y; case 'Z':return Z; case '0':return N0; case '1':return N1; case '2':return N2; case '3':return N3;
        case '4':return N4; case '5':return N5; case '6':return N6; case '7':return N7; case '8':return N8; case '9':return N9;
        case '-':return DASH; case '_':return UND; case '=':return EQ; case '+':return PLUS; case '>':return GT; case '<':return LT;
        case '/':return SL; case '(':return LP; case ')':return RP; case '[':return LB; case ']':return RB; case ':':return COL;
        case '.':return DOT; case ',':return COM; case '*':return STAR; case '#':return HASH; case '|':return BAR;
        case '\'':return APOS; case '^':return CARET; case '&':return AMP;
        default:return BL;
    }
}
static void draw_char(int x, int y, char ch, int s, Color c, float p) {
    const unsigned char *g = glyph(ch);
    for (int row = 0; row < 7; ++row) for (int col = 0; col < 5; ++col) {
        if (g[row] & (1 << (4-col))) {
            int px = x + col*s, py = y + row*s;
            for (int yy = 0; yy < s; ++yy) for (int xx = 0; xx < s; ++xx)
                add_px(px+xx, py+yy, c.r, c.g, c.b, p);
        }
    }
}
static int text_width(const char *s, int scale) { return (int)strlen(s) * 6 * scale - scale; }
static void draw_text(int x, int y, const char *s, int scale, Color c, float p) {
    for (int i = 0; s[i]; ++i) draw_char(x + i*6*scale, y, s[i], scale, c, p);
}
static void draw_text_glow(int x, int y, const char *s, int scale, Color c, float p) {
    Color dim = {c.r*0.45f, c.g*0.45f, c.b*0.45f};
    draw_text(x-1, y, s, scale, dim, p*0.24f);
    draw_text(x+1, y, s, scale, dim, p*0.24f);
    draw_text(x, y-1, s, scale, dim, p*0.24f);
    draw_text(x, y+1, s, scale, dim, p*0.24f);
    draw_text(x, y, s, scale, c, p);
}
static void draw_text_center(int cx, int y, const char *s, int scale, Color c, float p) {
    draw_text_glow(cx - text_width(s, scale)/2, y, s, scale, c, p);
}

static void draw_border(float t) {
    Color a = cmix(C_RED, C_PINK, 0.5f + 0.5f*sinf(t*1.7f));
    Color b = cmix(C_BLUE, C_GREEN, 0.5f + 0.5f*sinf(t*1.3f));
    int m = 16;
    line_glow(m,m,WIDTH-m,m,a,1.1f,0.36f);
    line_glow(WIDTH-m,m,WIDTH-m,HEIGHT-m,b,1.1f,0.36f);
    line_glow(WIDTH-m,HEIGHT-m,m,HEIGHT-m,a,1.1f,0.36f);
    line_glow(m,HEIGHT-m,m,m,b,1.1f,0.36f);
    for (int i=0;i<4;i++) {
        float s = 38.0f + i*12.0f;
        line_glow(m,m,m+s,m+s,a,1.0f,0.30f);
        line_glow(WIDTH-m,m,WIDTH-m-s,m+s,a,1.0f,0.30f);
        line_glow(m,HEIGHT-m,m+s,HEIGHT-m-s,b,1.0f,0.30f);
        line_glow(WIDTH-m,HEIGHT-m,WIDTH-m-s,HEIGHT-m-s,b,1.0f,0.30f);
    }
}

static void draw_lattice_plane(float t, Color c, float p) {
    float cx = WIDTH*0.5f, cy = HEIGHT*0.64f;
    for (int i=-10;i<=10;i++) {
        float a = i / 10.0f;
        line_glow(cx, cy-70, cx + a*650, HEIGHT-86, c, 0.8f, p*0.48f);
    }
    for (int j=0;j<12;j++) {
        float z = j/11.0f;
        float y = mixf(cy-68, HEIGHT-88, z*z);
        float rx = mixf(55, 650, z);
        line_glow(cx-rx, y, cx+rx, y, c, 0.65f, p*0.38f);
    }
    for (int r=1;r<=5;r++) ellipse_glow(cx, cy, r*78.0f + 12*sinf(t+r), r*20.0f, c, 0.7f, p*0.28f);
}

static void draw_mini_matrix(float cx, float cy, float size, float t, Color c, float p, int id) {
    float step = size / 3.0f;
    for (int yy=0; yy<4; ++yy) for (int xx=0; xx<4; ++xx) {
        float x = cx - size*0.5f + xx*step + 3.0f*sinf(t + id + xx);
        float y = cy - size*0.5f + yy*step + 3.0f*cosf(t*1.1f + id + yy);
        disc_add(x, y, 1.8f, c, p);
        if (xx < 3) line_add(x, y, x + step, y, c, p*0.12f);
        if (yy < 3) line_add(x, y, x, y + step, c, p*0.12f);
    }
    line_glow(cx-size*0.62f, cy-size*0.62f, cx+size*0.62f, cy-size*0.62f, c, 0.7f, p*0.45f);
    line_glow(cx+size*0.62f, cy-size*0.62f, cx+size*0.62f, cy+size*0.62f, c, 0.7f, p*0.45f);
    line_glow(cx+size*0.62f, cy+size*0.62f, cx-size*0.62f, cy+size*0.62f, c, 0.7f, p*0.45f);
    line_glow(cx-size*0.62f, cy+size*0.62f, cx-size*0.62f, cy-size*0.62f, c, 0.7f, p*0.45f);
}
static void draw_sigma_curve(float t, float u, Color c, float p) {
    float x0 = WIDTH*0.16f, x1 = WIDTH*0.84f;
    float y0 = HEIGHT*0.46f;
    float lastx = x0, lasty = y0;
    for (int i=1; i<=260; ++i) {
        float x = mixf(x0, x1, i/260.0f);
        float q = i/260.0f;
        float y = y0 + 72.0f*sinf(PI_REC*3.0f*q + t*0.7f) * expf(-1.15f*q) + 44.0f*sinf(14.0f*q + t);
        line_glow(lastx, lasty, x, y, c, 1.2f, p);
        lastx = x; lasty = y;
    }
    for (int k=1;k<=9;k++) {
        float q = k/10.0f;
        float x = mixf(x0, x1, q);
        float y = y0 + 72.0f*sinf(PI_REC*3.0f*q + t*0.7f) * expf(-1.15f*q) + 44.0f*sinf(14.0f*q + t);
        char s[2] = {(char)('0'+k),0};
        disc_add(x,y,7.0f,c,p*0.65f);
        draw_text((int)x-4,(int)y-24,s,1,C_WHITE,p*0.95f);
    }
}

static void scene_nuclear_recursion(float t, float u) {
    float cx = WIDTH*0.5f, cy = HEIGHT*0.42f;
    draw_lattice_plane(t, cmix(C_PURPLE, C_BLUE, 0.25f), 0.55f);
    for (int r=0; r<7; ++r) {
        float rr = 32.0f + r*34.0f + 14.0f*sinf(t*0.8f + r);
        Color c = cmix(C_RED, C_GOLD, r/7.0f);
        circle_glow(cx, cy, rr, c, 0.9f, 0.25f);
    }
    for (int i=0;i<110;i++) {
        float layer = 1.0f + (i % 7);
        float a = TAU*rnd01(i*17u) + t*(0.45f + 0.12f*layer);
        float rr = 34.0f + layer*34.0f + 16.0f*sinf(t + i);
        float x = cx + cosf(a)*rr;
        float y = cy + sinf(a)*rr*0.74f;
        Color c = cmix(C_PINK, C_GOLD, rnd01(i));
        disc_add(x, y, 2.2f + 2.2f*rnd01(i*3u), c, 0.55f);
        if (i % 4 == 0) line_add(cx, cy, x, y, c, 0.032f);
    }
    for (int branch=0; branch<12; ++branch) {
        float a = TAU*branch/12.0f + 0.2f*sinf(t);
        float x1 = cx + cosf(a) * (75.0f + 120.0f*u);
        float y1 = cy + sinf(a) * (55.0f + 90.0f*u);
        float x2 = cx + cosf(a+0.22f*sinf(t+branch)) * (255.0f + 40.0f*sinf(t+branch));
        float y2 = cy + sinf(a+0.22f*sinf(t+branch)) * (185.0f + 20.0f*cosf(t+branch));
        line_glow(x1,y1,x2,y2,cmix(C_RED,C_PINK,0.45f),1.1f,0.35f);
    }
    disc_add(cx, cy, 25.0f + 7.0f*sinf(t*2.0f), C_WHITE, 0.42f);
    draw_text_center((int)cx, (int)cy+92, "R_NUCLEAR(K+1) = F(R_K, M_OF_M, K_SIGMA)", 2, C_WHITE, 0.68f);
}

static void scene_matrix_of_matrices(float t, float u) {
    float cx = WIDTH*0.5f, cy = HEIGHT*0.42f;
    draw_lattice_plane(t, cmix(C_RED, C_BLUE, 0.45f), 0.50f);
    Color c = cmix(C_BLUE, C_PINK, 0.5f + 0.25f*sinf(t));
    float startx = cx - 315, starty = cy - 165;
    for (int row=0; row<3; ++row) for (int col=0; col<4; ++col) {
        int id = row*4 + col;
        float x = startx + col*210.0f;
        float y = starty + row*130.0f;
        draw_mini_matrix(x, y, 54.0f + 6.0f*sinf(t + id), t, cmix(c, C_GOLD, (id%4)/5.0f), 0.70f, id);
        line_glow(x, y, cx, cy, cmix(C_PINK, C_BLUE, id/12.0f), 0.75f, 0.20f);
    }
    for (int i=0;i<12;i++) {
        float a = TAU*i/12.0f + t*0.16f;
        float x = cx + cosf(a)*84.0f;
        float y = cy + sinf(a)*58.0f;
        disc_add(x, y, 5.0f, C_GOLD, 0.55f);
    }
    circle_glow(cx, cy, 92.0f + 12.0f*sinf(t), C_GOLD, 1.0f, 0.28f);
    draw_text_center((int)cx, (int)cy-16, "PRODUCT P*", 2, C_WHITE, 0.80f);
    draw_text_center((int)cx, (int)cy+112, "M = [ M_11 ... M_34 ]  EACH CELL IS A PARTICLE RELATION", 2, C_WHITE, 0.64f);
}

static void scene_game_knuth_sigma(float t, float u) {
    float cx = WIDTH*0.5f, cy = HEIGHT*0.43f;
    Color c = cmix(C_GREEN, C_GOLD, 0.45f + 0.25f*sinf(t));
    rect_blend(120, 130, 520, 420, C_BLACK, 0.44f);
    rect_blend(760, 130, 1160, 420, C_BLACK, 0.44f);
    draw_text_center(320, 152, "GAME MATRIX", 2, C_WHITE, 0.65f);
    draw_text_center(960, 152, "KNUTHIAN SIGMA", 2, C_WHITE, 0.65f);
    for (int i=0;i<4;i++) {
        float y = 205 + i*46;
        line_glow(170,y,470,y,c,0.8f,0.35f);
        line_glow(170+i*75,190,170+i*75,375,c,0.8f,0.35f);
    }
    for (int i=0;i<12;i++) {
        float x = 205 + (i%4)*75;
        float y = 222 + (i/4)*46;
        float val = sinf(t + i*1.7f + u*4.0f);
        Color pc = val > 0 ? C_GREEN : C_RED;
        disc_add(x,y,6.5f,pc,0.45f);
        if (val > 0.45f) draw_text((int)x-4,(int)y-4,"+",1,C_WHITE,0.70f);
    }
    draw_sigma_curve(t, u, C_GOLD, 0.30f);
    for (int i=0;i<9;i++) {
        float y = 205 + i*21.0f;
        float x0 = 805 + 20.0f*sinf(t+i);
        float x1 = 1115 - 20.0f*cosf(t*0.7f+i);
        line_glow(x0,y,x1,y+34.0f*sinf(i+t),cmix(C_GOLD,C_GREEN,rnd01(i)),0.8f,0.26f);
        char lab[10]; snprintf(lab,sizeof(lab),"S%d",i+1);
        draw_text((int)x0-24,(int)y-6,lab,1,C_WHITE,0.62f);
    }
    for (int i=0;i<120;i++) {
        float q = fmodf(rnd01(i*53u) + u + t*0.025f, 1.0f);
        float x = mixf(520, 760, q);
        float y = cy + 70.0f*sinf(PI_REC*q*4.0f + i);
        disc_add(x,y,2.0f,cmix(C_BLUE,C_GOLD,rnd01(i)),0.38f);
    }
    draw_text_center((int)cx, 456, "PI_STAR = ARGMAX U_I(S)  AND  K_SIGMA = SUM I XOR H(I)", 2, C_WHITE, 0.68f);
}

static void scene_time_acceleration(float t, float u) {
    float cx = WIDTH*0.5f, cy = HEIGHT*0.42f;
    Color accel = cmix(C_PINK, C_RED, 0.55f);
    Color timec = cmix(C_BLUE, C_GREEN, 0.55f);
    for (int i=0;i<620;i++) {
        float seed = rnd01(i*71u);
        float a = TAU*seed + t*(0.55f + 2.4f*u + 1.2f*rnd01(i));
        float rr = 45.0f + 500.0f*powf(rnd01(i*13u), 0.72f) * (0.35f + 0.75f*u);
        float spiral = a + 3.0f*logf(1.0f + rr/60.0f);
        float x = cx + cosf(spiral) * rr;
        float y = cy + sinf(spiral) * rr * 0.63f;
        disc_add(x,y,1.3f+2.0f*rnd01(i*3u),accel,0.35f);
        if (i%13==0) line_add(cx,cy,x,y,accel,0.035f);
    }
    for (int i=0;i<180;i++) {
        float a = TAU*i/180.0f + 0.25f*sinf(t + i);
        float rr = 190.0f + 46.0f*sinf(t*0.7f+i);
        float slow = 1.0f - smoothstepf(0.0f, 1.0f, u);
        float x = cx + cosf(a + t*0.15f*slow) * rr;
        float y = cy + sinf(a + t*0.15f*slow) * rr * 0.48f;
        disc_add(x,y,2.0f,timec,0.42f);
    }
    for (int r=0;r<7;r++) {
        float rr = 70.0f + r*42.0f;
        ellipse_glow(cx, cy, rr, rr*0.54f, cmix(timec, accel, r/7.0f), 0.8f, 0.17f);
    }
    disc_add(cx,cy,22.0f + 13.0f*sinf(t*3),C_WHITE,0.38f);
    draw_text_center((int)cx, (int)cy+96, "ACCELERATION REWRITES TIME PARTICLE TRAJECTORIES", 2, C_WHITE, 0.66f);
    draw_text_center((int)cx, (int)cy+124, "TAU_REC = 3.141519", 3, C_GOLD, 0.72f);
}

static void scene_acential_plane(float t, float u) {
    float cx = WIDTH*0.5f, cy = HEIGHT*0.61f;
    Color c = cmix(C_BLUE, C_PURPLE, 0.45f + 0.25f*sinf(t));
    draw_lattice_plane(t, c, 0.90f);
    float w = 620.0f, h = 185.0f;
    line_glow(cx-w/2,cy,cx,cy-h/2,c,1.8f,0.56f);
    line_glow(cx,cy-h/2,cx+w/2,cy,c,1.8f,0.56f);
    line_glow(cx+w/2,cy,cx,cy+h/2,c,1.8f,0.56f);
    line_glow(cx,cy+h/2,cx-w/2,cy,c,1.8f,0.56f);
    for (int i=0;i<9;i++) {
        float a = TAU*i/9.0f + 0.08f*sinf(t);
        float x = cx + cosf(a)*250.0f;
        float y = cy + sinf(a)*72.0f;
        disc_add(x,y,8.0f,cmix(C_GOLD,C_BLUE,i/9.0f),0.55f);
        char lab[5]; snprintf(lab,sizeof(lab),"A%d",i+1);
        draw_text((int)x-10,(int)y-27,lab,1,C_WHITE,0.70f);
        line_add(cx,cy,x,y,c,0.06f);
    }
    for (int i=0;i<360;i++) {
        float a = TAU*rnd01(i*3u) + t*0.28f;
        float r = (1.0f - smoothstepf(0.0f,1.0f,u))*480.0f*rnd01(i*17u) + 40.0f;
        float x = cx + cosf(a)*r;
        float y = cy + sinf(a)*r*0.30f;
        disc_add(x,y,1.6f,cmix(C_BLUE,C_GREEN,rnd01(i)),0.38f);
    }
    draw_text_center((int)cx, (int)cy-12, "ACENTIAL PLANE OF AXIOMS", 2, C_WHITE, 0.70f);
    draw_text_center((int)cx, 256, "CONTAINMENT MAPS RECURSION INTO A STABLE 2D AXIOM FIELD", 2, C_WHITE, 0.62f);
}

static void scene_unified_product(float t, float u) {
    float cx = WIDTH*0.5f, cy = HEIGHT*0.42f;
    draw_lattice_plane(t, cmix(C_GREEN, C_BLUE, 0.45f), 0.62f);
    for (int i=0;i<6;i++) {
        float rr = 60.0f + i*50.0f;
        poly_glow(cx, cy, rr + 8*sinf(t+i), 6, t*0.13f+i*0.2f, cmix(C_GREEN,C_PINK,i/6.0f), 0.9f, 0.21f);
    }
    for (int i=0;i<15;i++) {
        float a = TAU*i/15.0f + t*0.12f;
        float x = cx + cosf(a)*275.0f;
        float y = cy + sinf(a)*164.0f;
        draw_mini_matrix(x, y, 30.0f + 4.0f*sinf(t+i), t, cmix(C_BLUE,C_GOLD,rnd01(i)), 0.48f, i);
        line_glow(x,y,cx,cy,cmix(C_BLUE,C_GREEN,i/15.0f),0.7f,0.18f);
    }
    draw_sigma_curve(t, u, C_GOLD, 0.22f);
    for (int i=0;i<400;i++) {
        float q = rnd01(i*31u);
        float a = TAU*q + t*(0.3f + u);
        float r = 36.0f + 245.0f*rnd01(i*13u);
        float x = cx + cosf(a + sinf(t+i)*0.7f)*r;
        float y = cy + sinf(a + sinf(t+i)*0.7f)*r*0.56f;
        disc_add(x,y,1.4f+1.4f*rnd01(i),cmix(C_RED,C_GREEN,rnd01(i*7u)),0.35f);
    }
    disc_add(cx,cy,30.0f + 12.0f*sinf(t*2.0f),C_WHITE,0.42f);
    draw_text_center((int)cx, (int)cy-12, "SINGLE PRODUCT P* = MATRIX X GAME X K_SIGMA X TIME", 2, C_WHITE, 0.74f);
    draw_text_center((int)cx, (int)cy+112, "CORPOREAL COMBINATION LOCKED INTO ONE RECURSIVE OUTPUT", 2, C_WHITE, 0.62f);
}

static void scene_final(float t, float u) {
    float cx = WIDTH*0.5f, cy = HEIGHT*0.42f;
    Color c = cmix(C_GREEN, C_PINK, 0.5f + 0.5f*sinf(t*2.0f));
    for (int i=0;i<980;i++) {
        float a = TAU*rnd01(i*19u) + t*(0.08f + 0.7f*rnd01(i*5u));
        float rr = 20.0f + 640.0f*rnd01(i*7u) * (1.0f-smoothstepf(0.78f,1.0f,u));
        float x = cx + cosf(a + 2.0f*u)*rr;
        float y = cy + sinf(a + 2.0f*u)*rr*0.68f;
        Color pc = cmix(C_BLUE, c, rnd01(i*11u));
        disc_add(x,y,1.1f+2.4f*rnd01(i),pc,0.38f);
        if (i%33==0) line_add(cx,cy,x,y,pc,0.035f);
    }
    for (int r=0;r<9;r++) {
        circle_glow(cx,cy,42.0f + r*34.0f + u*28.0f,cmix(C_GREEN,C_PINK,r/9.0f),0.9f,0.16f);
    }
    draw_text_center((int)cx, (int)cy-26, "NUCLEAR RECURSION FIELD COMPLETE", 4, c, 0.86f);
    draw_text_center((int)cx, (int)cy+30, "TIME PARTICLES STABILIZED AT 3.141519", 3, C_WHITE, 0.72f);
    draw_text_center((int)cx, (int)cy+74, "LATTICRA MATRIX OF MATRICES", 3, C_GOLD, 0.70f);
}

static const char *scene_name(int s) {
    switch(s) {
        case 0: return "NUCLEAR RECURSION";
        case 1: return "MATRIX OF MATRICES";
        case 2: return "GAME K_SIGMA";
        case 3: return "TIME ACCELERATION";
        case 4: return "ACENTIAL AXIOM PLANE";
        case 5: return "SINGLE PRODUCT FIELD";
        default:return "FIELD COMPLETION";
    }
}
static const char *theorem_title(int s) {
    switch(s) {
        case 0: return "NUCLEAR RECURSION THEOREM";
        case 1: return "MATRIX OF MATRICES PARTICLE THEOREM";
        case 2: return "GAME THEORETIC K_SIGMA ALGORITHM";
        case 3: return "RECURSIVE TIME PARTICLE ACCELERATION";
        case 4: return "ACENTIAL PLANE OF AXIOMS";
        case 5: return "CORPOREAL SINGLE PRODUCT COMBINATION";
        default:return "LATTICRA FIELD COMPLETION";
    }
}
static const char *eq1(int s) {
    switch(s) {
        case 0: return "R_N(K+1)=F_N(R_N(K), M[M_IJ], K_SIGMA, TAU_REC)";
        case 1: return "M[M_IJ] : EACH MATRIX CELL STORES PARTICLE RELATION P_IJ";
        case 2: return "P_STAR=ARGMAX U_I(S) ; K_SIGMA=SUM(I=1..N) I XOR H(I)";
        case 3: return "A_P UP  =>  D(T_PARTICLE)/DT DOWN  AT  TAU_REC=3.141519";
        case 4: return "PI_2D(R_N) <= A_FIELD ; AXIOMS A1..A9 BECOME PLANE NODES";
        case 5: return "P_SINGLE = M[M_IJ] X GAME(S) X K_SIGMA X T_PARTICLE";
        default:return "LIMIT FIELD => PRODUCT STABLE ; RECURSION CLOSED ; TIME LOCKED";
    }
}
static const char *eq2(int s) {
    switch(s) {
        case 0: return "NUCLEAR STATES RECURSE OUTWARD AS A DETERMINISTIC SUBSTRATE";
        case 1: return "A MATRIX CONTAINS MATRICES AND EACH SUBMATRIX BINDS PARTICLE PAIRS";
        case 2: return "STRATEGIC EQUILIBRIUM FEEDS A KNUTHIAN SIGMA STYLE UPDATE LOOP";
        case 3: return "SYMBOLIC ACCELERATION CURVES TIME PARTICLES INTO THE RECURSIVE CONSTANT";
        case 4: return "THE ACENTIAL PLANE CONTAINS AXIOMS AS 2D FIELD CONSTRAINTS";
        case 5: return "THE PRODUCT IS A CORPOREAL COMBINATION OF STRUCTURE, STRATEGY, AND TIME";
        default:return "THE DEMO IS SYMBOLIC COMPUTATION ART, NOT A CLAIM OF PHYSICAL PROOF";
    }
}
static Color scene_color(int s, float t) {
    switch(s) {
        case 0: return cmix(C_RED,C_GOLD,0.5f+0.25f*sinf(t));
        case 1: return cmix(C_BLUE,C_PINK,0.5f+0.25f*sinf(t));
        case 2: return cmix(C_GREEN,C_GOLD,0.5f+0.25f*sinf(t));
        case 3: return cmix(C_RED,C_BLUE,0.5f+0.25f*sinf(t));
        case 4: return cmix(C_PURPLE,C_BLUE,0.5f+0.25f*sinf(t));
        case 5: return cmix(C_GREEN,C_PINK,0.5f+0.25f*sinf(t));
        default:return cmix(C_WHITE,C_GREEN,0.5f+0.25f*sinf(t));
    }
}

static void draw_panel(float t, int scene, float u, int frame, int total_seconds) {
    Color c = scene_color(scene, t);
    int x0 = 70, y0 = HEIGHT - 205, x1 = WIDTH - 70, y1 = HEIGHT - 66;
    rect_blend(x0, y0, x1, y1, C_BLACK, 0.75f);
    line_glow(x0,y0,x1,y0,c,1.3f,0.45f);
    line_glow(x1,y0,x1,y1,c,1.3f,0.45f);
    line_glow(x1,y1,x0,y1,c,1.3f,0.45f);
    line_glow(x0,y1,x0,y0,c,1.3f,0.45f);
    draw_text_center(WIDTH/2, y0+16, theorem_title(scene), 2, C_WHITE, 0.86f);
    line_glow(x0+44,y0+42,x1-44,y0+42,c,0.85f,0.34f);
    draw_text_center(WIDTH/2, y0+56, eq1(scene), 2, cmix(C_WHITE,c,0.42f), 0.80f);
    draw_text_center(WIDTH/2, y0+91, eq2(scene), 2, C_WHITE, 0.62f);
    char b[160];
    int elapsed = frame / FPS;
    int remain = total_seconds - elapsed;
    if (remain < 0) remain = 0;
    snprintf(b,sizeof(b),"MODEL %d/%d  -  %s  -  LOCAL RECURSION %02d%%  -  T-%03d",
             scene+1, SCENES, scene_name(scene), (int)(u*100.0f), remain);
    draw_text_center(WIDTH/2, HEIGHT-48, b, 2, C_GOLD, 0.67f);
}

static void draw_side_meter(float t, int scene, float u) {
    Color c = scene_color(scene, t);
    rect_blend(42, 138, 330, 292, C_BLACK, 0.52f);
    rect_blend(WIDTH-330, 138, WIDTH-42, 292, C_BLACK, 0.52f);
    line_glow(42,138,330,138,c,0.9f,0.30f); line_glow(42,292,330,292,c,0.9f,0.30f);
    line_glow(WIDTH-330,138,WIDTH-42,138,c,0.9f,0.30f); line_glow(WIDTH-330,292,WIDTH-42,292,c,0.9f,0.30f);
    draw_text(58, 158, "LATTICRA OPS", 2, C_WHITE, 0.58f);
    draw_text(58, 192, "NUCLEAR RECUR", 2, c, 0.55f);
    draw_text(58, 222, "MATRIX PRODUCT", 2, c, 0.55f);
    draw_text(58, 252, "TIME PARTICLES", 2, C_WHITE, 0.53f);

    draw_text(WIDTH-312, 158, "SIGMA STATE", 2, C_WHITE, 0.58f);
    draw_text(WIDTH-312, 192, "TAU=3.141519", 2, c, 0.55f);
    draw_text(WIDTH-312, 222, "GAME PAYOFFS", 2, c, 0.55f);
    draw_text(WIDTH-312, 252, "AXIOM PLANE", 2, C_WHITE, 0.53f);

    int barx = 58, bary = 314, barw = 214, barh = 14;
    rect_blend(barx,bary,barx+barw,bary+barh,C_BLACK,0.70f);
    line_glow(barx,bary,barx+barw,bary,c,0.7f,0.28f);
    rect_blend(barx,bary,barx+(int)(barw*u),bary+barh,c,0.55f);
}

static void draw_scene(int scene, float t, float u) {
    switch(scene) {
        case 0: scene_nuclear_recursion(t,u); break;
        case 1: scene_matrix_of_matrices(t,u); break;
        case 2: scene_game_knuth_sigma(t,u); break;
        case 3: scene_time_acceleration(t,u); break;
        case 4: scene_acential_plane(t,u); break;
        case 5: scene_unified_product(t,u); break;
        default: scene_final(t,u); break;
    }
}

static void render_frame(int frame, int total_frames, int total_seconds) {
    float t = (float)frame / FPS;
    float global = (float)frame / (float)(total_frames - 1);
    int scene = (int)floorf(global * SCENES);
    if (scene > SCENES - 1) scene = SCENES - 1;
    float u = clampf(global * SCENES - scene, 0.0f, 1.0f);

    clear_frame(t);
    draw_border(t);
    draw_scene(scene, t, u);
    draw_side_meter(t, scene, u);

    Color title = scene_color(scene, t);
    draw_text_center(WIDTH/2, 29, "LATTICRA NUCLEAR RECURSION ENGINE", 4, title, 0.64f);
    draw_text_center(WIDTH/2, 76, "MATRIX OF MATRICES  -  GAME THEORETICS  -  K_SIGMA  -  TIME PARTICLES  -  3.141519", 2, C_WHITE, 0.58f);
    draw_panel(t, scene, u, frame, total_seconds);
}

int main(int argc, char **argv) {
    const char *out = (argc > 1) ? argv[1] : "latticra-nuclear-recursion-engine.mp4";
    int seconds = (argc > 2) ? atoi(argv[2]) : DEFAULT_SECONDS;
    if (seconds < 14) seconds = 14;

    fb = (unsigned char*)malloc((size_t)WIDTH * HEIGHT * 3);
    if (!fb) {
        fprintf(stderr, "Could not allocate framebuffer.\n");
        return 1;
    }

    char cmd[2048];
    snprintf(cmd, sizeof(cmd),
        "ffmpeg -y -f rawvideo -pix_fmt rgb24 -s %dx%d -r %d -i - "
        "-f lavfi -i anullsrc=channel_layout=stereo:sample_rate=44100 "
        "-shortest -c:v libx264 -profile:v high -level:v 4.0 "
        "-preset veryfast -crf 20 -pix_fmt yuv420p "
        "-c:a aac -b:a 128k -movflags +faststart \"%s\"",
        WIDTH, HEIGHT, FPS, out);

    FILE *pipe = popen(cmd, "w");
    if (!pipe) {
        fprintf(stderr, "Could not open ffmpeg pipe. Is ffmpeg installed?\n");
        free(fb);
        return 1;
    }

    int total = seconds * FPS;
    for (int f = 0; f < total; ++f) {
        render_frame(f, total, seconds);
        size_t wrote = fwrite(fb, 1, (size_t)WIDTH * HEIGHT * 3, pipe);
        if (wrote != (size_t)WIDTH * HEIGHT * 3) {
            fprintf(stderr, "Short write to ffmpeg.\n");
            break;
        }
        if (f % FPS == 0) fprintf(stderr, "rendering %02d/%02d seconds\r", f/FPS, seconds);
    }

    fprintf(stderr, "\nfinalizing mp4...\n");
    int rc = pclose(pipe);
    free(fb);
    if (rc != 0) {
        fprintf(stderr, "ffmpeg exited with code %d. If libx264 is missing, install full ffmpeg or change -c:v libx264 to -c:v mpeg4.\n", rc);
        return 1;
    }
    fprintf(stderr, "done: %s\n", out);
    return 0;
}
