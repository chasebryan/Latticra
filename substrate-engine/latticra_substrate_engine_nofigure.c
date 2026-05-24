#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define W 1280
#define H 720
#define FPS 30
#define DEFAULT_SECONDS 96
#define PI 3.14159265358979323846f
#define TAU 6.28318530717958647692f
#define SCENES 8

static unsigned char *fb;

typedef struct { float r, g, b; } Color;
static const Color C_RED    = {255,  35,  65};
static const Color C_PINK   = {255,  45, 200};
static const Color C_PURPLE = {180,  55, 255};
static const Color C_BLUE   = { 45, 190, 255};
static const Color C_GREEN  = { 60, 255, 150};
static const Color C_WHITE  = {255, 245, 250};
static const Color C_GOLD   = {255, 205,  70};
static const Color C_BLACK  = {  2,   1,   6};

static float clampf(float v, float lo, float hi) { return v < lo ? lo : (v > hi ? hi : v); }
static float mixf(float a, float b, float t) { return a + (b - a) * t; }
static float smoothstepf(float e0, float e1, float x) {
    float t = clampf((x - e0) / (e1 - e0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}
static Color cmix(Color a, Color b, float t) {
    Color c = { mixf(a.r,b.r,t), mixf(a.g,b.g,t), mixf(a.b,b.b,t) };
    return c;
}

static uint32_t hash_u32(uint32_t x) {
    x ^= x >> 16; x *= 0x7feb352dU; x ^= x >> 15; x *= 0x846ca68bU; x ^= x >> 16;
    return x;
}
static float rnd01(uint32_t n) { return (hash_u32(n) & 0xFFFFFF) / 16777215.0f; }

static void clear_frame(float t) {
    memset(fb, 0, (size_t)W * H * 3);
    for (int y = 0; y < H; ++y) {
        float fy = (float)y / (float)H;
        for (int x = 0; x < W; ++x) {
            float fx = (float)x / (float)W;
            int k = (y * W + x) * 3;
            float glow = 0.08f + 0.12f * sinf(10.0f * fx + t * 0.45f) * sinf(7.0f * fy - t * 0.4f);
            fb[k+0] = (unsigned char)clampf(4 + 22 * glow, 0, 255);
            fb[k+1] = (unsigned char)clampf(1 + 8 * glow, 0, 255);
            fb[k+2] = (unsigned char)clampf(10 + 35 * glow, 0, 255);
        }
    }
    for (int i = 0; i < 1100; ++i) {
        float x = rnd01(i*17u + 11u) * W;
        float y = fmodf(rnd01(i*31u + 7u) * H + t * (6.0f + 22.0f*rnd01(i*5u)), (float)H);
        float tw = 0.35f + 0.65f * sinf(t*3.0f + i*1.731f);
        int ix = (int)x, iy = (int)y;
        if (ix >= 0 && ix < W && iy >= 0 && iy < H) {
            int k = (iy*W + ix)*3;
            fb[k+0] = (unsigned char)clampf(fb[k+0] + 24 + 34*tw, 0, 255);
            fb[k+1] = (unsigned char)clampf(fb[k+1] + 3 + 12*tw, 0, 255);
            fb[k+2] = (unsigned char)clampf(fb[k+2] + 26 + 45*tw, 0, 255);
        }
    }
}

static inline void add_px(int x, int y, float r, float g, float b, float a) {
    if ((unsigned)x >= W || (unsigned)y >= H) return;
    int k = (y * W + x) * 3;
    int nr = fb[k+0] + (int)(r * a);
    int ng = fb[k+1] + (int)(g * a);
    int nb = fb[k+2] + (int)(b * a);
    fb[k+0] = (unsigned char)(nr > 255 ? 255 : nr);
    fb[k+1] = (unsigned char)(ng > 255 ? 255 : ng);
    fb[k+2] = (unsigned char)(nb > 255 ? 255 : nb);
}

static inline void blend_px(int x, int y, float r, float g, float b, float a) {
    if ((unsigned)x >= W || (unsigned)y >= H) return;
    a = clampf(a, 0, 1);
    int k = (y * W + x) * 3;
    fb[k+0] = (unsigned char)clampf(fb[k+0]*(1-a) + r*a, 0, 255);
    fb[k+1] = (unsigned char)clampf(fb[k+1]*(1-a) + g*a, 0, 255);
    fb[k+2] = (unsigned char)clampf(fb[k+2]*(1-a) + b*a, 0, 255);
}

static void disc_add(float cx, float cy, float rad, Color c, float power) {
    int x0 = (int)floorf(cx - rad), x1 = (int)ceilf(cx + rad);
    int y0 = (int)floorf(cy - rad), y1 = (int)ceilf(cy + rad);
    float rr = rad * rad;
    for (int y = y0; y <= y1; ++y) {
        for (int x = x0; x <= x1; ++x) {
            float dx = x + 0.5f - cx, dy = y + 0.5f - cy;
            float d2 = dx*dx + dy*dy;
            if (d2 <= rr) {
                float f = 1.0f - d2 / rr;
                f = f*f;
                add_px(x, y, c.r, c.g, c.b, power * f);
            }
        }
    }
}

static void disc_blend(float cx, float cy, float rad, Color c, float alpha) {
    int x0 = (int)floorf(cx - rad), x1 = (int)ceilf(cx + rad);
    int y0 = (int)floorf(cy - rad), y1 = (int)ceilf(cy + rad);
    float rr = rad * rad;
    for (int y = y0; y <= y1; ++y) {
        for (int x = x0; x <= x1; ++x) {
            float dx = x + 0.5f - cx, dy = y + 0.5f - cy;
            float d2 = dx*dx + dy*dy;
            if (d2 <= rr) blend_px(x, y, c.r, c.g, c.b, alpha);
        }
    }
}

static void ellipse_blend(float cx, float cy, float rx, float ry, Color c, float alpha) {
    int x0 = (int)floorf(cx - rx), x1 = (int)ceilf(cx + rx);
    int y0 = (int)floorf(cy - ry), y1 = (int)ceilf(cy + ry);
    for (int y = y0; y <= y1; ++y) {
        for (int x = x0; x <= x1; ++x) {
            float dx = (x + 0.5f - cx) / rx, dy = (y + 0.5f - cy) / ry;
            if (dx*dx + dy*dy <= 1.0f) blend_px(x, y, c.r, c.g, c.b, alpha);
        }
    }
}

static void rect_blend(int x0, int y0, int x1, int y1, Color c, float alpha) {
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > W) x1 = W;
    if (y1 > H) y1 = H;
    for (int y = y0; y < y1; ++y) for (int x = x0; x < x1; ++x) blend_px(x, y, c.r, c.g, c.b, alpha);
}

static void line_add(float x0, float y0, float x1, float y1, Color c, float power) {
    float dx = x1 - x0, dy = y1 - y0;
    int steps = (int)fmaxf(fabsf(dx), fabsf(dy));
    if (steps < 1) steps = 1;
    for (int i = 0; i <= steps; ++i) {
        float t = (float)i / steps;
        add_px((int)(x0 + dx*t), (int)(y0 + dy*t), c.r, c.g, c.b, power);
    }
}

static void line_glow(float x0, float y0, float x1, float y1, Color c, float thick, float power) {
    float dx = x1 - x0, dy = y1 - y0;
    int steps = (int)(hypotf(dx, dy) / 2.5f) + 1;
    for (int i = 0; i <= steps; ++i) {
        float t = (float)i / steps;
        disc_add(x0 + dx*t, y0 + dy*t, thick, c, power);
    }
}

static void circle_glow(float cx, float cy, float r, Color c, float thick, float power) {
    int seg = (int)clampf(r * 1.2f, 64, 240);
    float px = cx + cosf(0)*r, py = cy + sinf(0)*r;
    for (int i = 1; i <= seg; ++i) {
        float a = TAU * i / seg;
        float x = cx + cosf(a)*r, y = cy + sinf(a)*r;
        line_glow(px, py, x, y, c, thick, power);
        px = x; py = y;
    }
}

static void ellipse_glow(float cx, float cy, float rx, float ry, Color c, float thick, float power) {
    int seg = 240;
    float px = cx + rx, py = cy;
    for (int i = 1; i <= seg; ++i) {
        float a = TAU * i / seg;
        float x = cx + cosf(a)*rx, y = cy + sinf(a)*ry;
        line_glow(px, py, x, y, c, thick, power);
        px = x; py = y;
    }
}

static void polygon_glow(float cx, float cy, float r, int n, float rot, Color c, float thick, float power) {
    float px = cx + cosf(rot) * r, py = cy + sinf(rot) * r;
    for (int i = 1; i <= n; ++i) {
        float a = rot + TAU * i / n;
        float x = cx + cosf(a)*r, y = cy + sinf(a)*r;
        line_glow(px, py, x, y, c, thick, power);
        px = x; py = y;
    }
}

static void shard(float cx, float cy, float s, float a, Color c, float power) {
    float ca = cosf(a), sa = sinf(a);
    float pts[4][2] = {{0,-1.45f*s},{0.43f*s,0},{0,1.45f*s},{-0.43f*s,0}};
    float q[4][2];
    for (int i=0;i<4;i++) {
        q[i][0] = cx + pts[i][0]*ca - pts[i][1]*sa;
        q[i][1] = cy + pts[i][0]*sa + pts[i][1]*ca;
    }
    for (int i=0;i<4;i++) line_glow(q[i][0],q[i][1],q[(i+1)%4][0],q[(i+1)%4][1],c,1.1f,power);
    line_add(q[0][0],q[0][1],q[2][0],q[2][1],c,power*0.8f);
    line_add(q[1][0],q[1][1],q[3][0],q[3][1],c,power*0.8f);
}

static void draw_lattice_sigil(float cx, float cy, float s, Color c, float p) {
    for (int i=-2;i<=2;i++) {
        line_glow(cx - 2.5f*s, cy + i*s, cx + 2.5f*s, cy + i*s, c, 0.9f, p);
        line_glow(cx + i*s, cy - 2.5f*s, cx + i*s, cy + 2.5f*s, c, 0.9f, p);
    }
    circle_glow(cx, cy, 3.1f*s, c, 0.8f, p*0.45f);
}

/* 5x7 font */
static const unsigned char *glyph(char ch) {
    static const unsigned char BL[7] = {0,0,0,0,0,0,0};
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
        static const unsigned char WW[7]={17,17,17,21,21,21,10}; static const unsigned char X[7]={17,17,10,4,10,17,17};
    static const unsigned char Y[7]={17,17,10,4,4,4,4};     static const unsigned char Z[7]={31,1,2,4,8,16,31};
    static const unsigned char N0[7]={31,17,19,21,25,17,31}; static const unsigned char N1[7]={4,12,4,4,4,4,14};
    static const unsigned char N2[7]={30,1,1,30,16,16,31};  static const unsigned char N3[7]={30,1,1,14,1,1,30};
    static const unsigned char N4[7]={18,18,18,31,2,2,2};   static const unsigned char N5[7]={31,16,16,30,1,1,30};
    static const unsigned char N6[7]={15,16,16,30,17,17,14}; static const unsigned char N7[7]={31,1,2,4,8,8,8};
    static const unsigned char N8[7]={14,17,17,14,17,17,14}; static const unsigned char N9[7]={14,17,17,15,1,1,30};
    static const unsigned char DASH[7]={0,0,0,31,0,0,0}; static const unsigned char UND[7]={0,0,0,0,0,0,31};
    static const unsigned char EQ[7]={0,31,0,0,31,0,0};  static const unsigned char PLUS[7]={0,4,4,31,4,4,0};
    static const unsigned char GT[7]={16,8,4,2,4,8,16};  static const unsigned char LT[7]={1,2,4,8,4,2,1};
    static const unsigned char SL[7]={1,2,4,8,16,0,0};   static const unsigned char BS[7]={16,8,4,2,1,0,0};
    static const unsigned char LP[7]={2,4,8,8,8,4,2};    static const unsigned char RP[7]={8,4,2,2,2,4,8};
    static const unsigned char LB[7]={14,8,8,8,8,8,14};  static const unsigned char RB[7]={14,2,2,2,2,2,14};
    static const unsigned char COL[7]={0,4,4,0,4,4,0};   static const unsigned char DOT[7]={0,0,0,0,0,12,12};
    static const unsigned char COM[7]={0,0,0,0,0,4,8};   static const unsigned char EXC[7]={4,4,4,4,4,0,4};
    static const unsigned char QST[7]={14,17,1,2,4,0,4}; static const unsigned char STAR[7]={0,21,14,31,14,21,0};
    static const unsigned char HASH[7]={10,31,10,10,31,10,0}; static const unsigned char BAR[7]={4,4,4,4,4,4,4};
    static const unsigned char APOS[7]={4,4,8,0,0,0,0};  static const unsigned char CARET[7]={4,10,17,0,0,0,0};
    static const unsigned char AMP[7]={12,18,20,8,21,18,13};
    if (ch >= 'a' && ch <= 'z') ch = (char)(ch - 32);
    switch (ch) {
        case 'A':return A; case 'B':return B; case 'C':return C; case 'D':return D; case 'E':return E; case 'F':return F;
                case 'G':return G; case 'H':return HH; case 'I':return I; case 'J':return J; case 'K':return K; case 'L':return L;
        case 'M':return M; case 'N':return N; case 'O':return O; case 'P':return P; case 'Q':return Q; case 'R':return R;
                case 'S':return S; case 'T':return T; case 'U':return U; case 'V':return V; case 'W':return WW; case 'X':return X;
        case 'Y':return Y; case 'Z':return Z; case '0':return N0; case '1':return N1; case '2':return N2; case '3':return N3;
        case '4':return N4; case '5':return N5; case '6':return N6; case '7':return N7; case '8':return N8; case '9':return N9;
        case '-':return DASH; case '_':return UND; case '=':return EQ; case '+':return PLUS; case '>':return GT; case '<':return LT;
        case '/':return SL; case '\\':return BS; case '(':return LP; case ')':return RP; case '[':return LB; case ']':return RB;
        case ':':return COL; case '.':return DOT; case ',':return COM; case '!':return EXC; case '?':return QST; case '*':return STAR;
        case '#':return HASH; case '|':return BAR; case '\'':return APOS; case '^':return CARET; case '&':return AMP;
        default:return BL;
    }
}

static void draw_char(int x, int y, char ch, int s, Color c, float power) {
    const unsigned char *g = glyph(ch);
    for (int row = 0; row < 7; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (g[row] & (1 << (4-col))) {
                int px = x + col*s, py = y + row*s;
                for (int yy = 0; yy < s; ++yy) for (int xx = 0; xx < s; ++xx) add_px(px+xx, py+yy, c.r, c.g, c.b, power);
            }
        }
    }
}

static int text_w(const char *s, int scale) { return (int)strlen(s) * 6 * scale - scale; }
static void draw_text(int x, int y, const char *s, int scale, Color c, float power) {
    for (int i = 0; s[i]; ++i) draw_char(x + i*6*scale, y, s[i], scale, c, power);
}
static void draw_text_glow(int x, int y, const char *s, int scale, Color c, float power) {
    Color dim = {c.r*0.55f, c.g*0.55f, c.b*0.55f};
    draw_text(x-1, y, s, scale, dim, power*0.25f);
    draw_text(x+1, y, s, scale, dim, power*0.25f);
    draw_text(x, y-1, s, scale, dim, power*0.25f);
    draw_text(x, y+1, s, scale, dim, power*0.25f);
    draw_text(x, y, s, scale, c, power);
}
static void draw_text_center(int cx, int y, const char *s, int scale, Color c, float power) {
    draw_text_glow(cx - text_w(s, scale)/2, y, s, scale, c, power);
}

static void draw_border(float t) {
    Color c1 = cmix(C_RED, C_PINK, 0.5f + 0.5f*sinf(t*2.0f));
    Color c2 = cmix(C_BLUE, C_GREEN, 0.5f + 0.5f*sinf(t*1.7f));
    int m = 16;
    line_glow(m,m,W-m,m,c1,1.2f,0.35f); line_glow(W-m,m,W-m,H-m,c2,1.2f,0.35f);
    line_glow(W-m,H-m,m,H-m,c1,1.2f,0.35f); line_glow(m,H-m,m,m,c2,1.2f,0.35f);
    int k = 55;
    line_glow(m,m,m+k,m+k,c1,1.2f,0.45f); line_glow(W-m,m,W-m-k,m+k,c1,1.2f,0.45f);
    line_glow(m,H-m,m+k,H-m-k,c2,1.2f,0.45f); line_glow(W-m,H-m,W-m-k,H-m-k,c2,1.2f,0.45f);
}

static void draw_lattice_plane(float t, Color c, float power) {
    float cx = W*0.5f, cy = H*0.64f;
    for (int i = -10; i <= 10; ++i) {
        float a = i / 10.0f;
        float x0 = cx + a * 640.0f;
        line_glow(cx, cy-78, x0, H-88, c, 0.9f, power*0.55f);
    }
    for (int j = 0; j < 13; ++j) {
        float z = j / 12.0f;
        float y = mixf(cy - 74, H-92, z*z);
        float rx = mixf(52, 654, z);
        line_glow(cx-rx, y, cx+rx, y, c, 0.7f, power*0.35f);
    }
    for (int r=1; r<=6; ++r)
        ellipse_glow(cx, cy, r*66.0f + 16*sinf(t+r), r*18.0f + 3*sinf(t*1.3f+r), c, 0.8f, power*0.42f);
}

static void draw_digit_field(float t, int center_x, int top_y, int width, int height, Color c) {
    for (int i = 0; i < 150; ++i) {
        int digit = 1 + (i % 9);
        int x = center_x - width/2 + (int)(rnd01(i*17u) * width);
        int y = top_y + (int)fmodf(rnd01(i*13u) * height + t * (22.0f + 28.0f * rnd01(i*3u)), (float)height);
        char s[2] = {(char)('0' + digit), 0};
        draw_text(x, y, s, 1 + (i % 2), c, 0.22f + 0.10f * sinf(t + i));
    }
}

static void draw_substrate_core(float t, float u) {
    float cx = W*0.5f, cy = H*0.42f;
    Color c = cmix(C_RED, C_PINK, 0.5f + 0.5f*sinf(t*1.5f));
    draw_lattice_plane(t, cmix(C_PURPLE, C_BLUE, 0.35f), 0.55f);
    for (int r = 0; r < 5; ++r)
        polygon_glow(cx, cy, 58 + r*36 + 10*sinf(t*1.4f+r), 6, t*0.22f + r*0.13f, cmix(c, C_BLUE, r/5.0f), 1.0f, 0.30f);
    for (int i=0;i<140;i++) {
        float gx = (i % 14) - 6.5f;
        float gy = (i / 14) - 4.5f;
        float px = cx + gx * 26.0f + 10.0f*sinf(t*1.3f + i);
        float py = cy + gy * 22.0f + 7.0f*cosf(t*1.1f + i*0.7f);
        disc_add(px, py, 2.0f + 1.2f * rnd01(i), c, 0.65f);
        if (i % 14 != 13) line_add(px, py, px + 26.0f, py, c, 0.08f);
        if (i / 14 != 9) line_add(px, py, px, py + 22.0f, c, 0.08f);
    }
    draw_lattice_sigil(cx, cy, 12.0f + 2.0f*sinf(t*2), C_WHITE, 0.72f);
    draw_digit_field(t, (int)cx, 126, 630, 220, cmix(C_PINK, C_BLUE, 0.3f));
    float pulse = 0.65f + 0.35f*sinf(t*3.0f);
    circle_glow(cx, cy, 160 + 24*pulse, c, 1.2f, 0.24f + 0.08f*u);
}

static void draw_matrix_substrate(float t, float u) {
    float ox = W*0.5f, oy = H*0.43f;
    Color c = cmix(C_RED, C_PINK, 0.45f + 0.35f*sinf(t*2.0f));
    int N = 11;
    float step = 36.0f;
    for (int y=0;y<N;y++) for (int x=0;x<N;x++) {
        float px = ox + (x-(N-1)/2.0f)*step + sinf(t*1.8f+y)*7.0f;
        float py = oy + (y-(N-1)/2.0f)*step*0.62f + cosf(t*1.4f+x)*5.0f;
        disc_add(px,py,2.2f,c,0.75f);
        if (x+1<N) line_add(px,py,px+step,py,c,0.10f);
        if (y+1<N) line_add(px,py,px,py+step*0.62f,c,0.10f);
        if ((x+y)%3 == 0) line_add(px,py,ox,oy,cmix(C_BLUE, C_PINK, 0.5f),0.03f + 0.02f*u);
    }
    for (int i=0;i<95;i++) {
        float a = TAU*rnd01(i*71u) + t*0.2f;
        float r = 200 + 110*rnd01(i*13u) + 16*sinf(t + i);
        shard(ox + cosf(a)*r, oy + sinf(a)*r*0.72f, 8+16*rnd01(i*5u), a+t*0.3f, cmix(C_RED, C_PINK, rnd01(i)), 0.24f);
    }
    circle_glow(ox,oy,76+22*sinf(t*1.8f),C_WHITE,1.0f,0.22f);
    circle_glow(ox,oy,150+18*sinf(t*1.2f),c,1.0f,0.22f);
}

static void draw_sigkokilla_expansion(float t, float u) {
    float cx = W*0.5f, cy = H*0.43f;
    for (int i=0;i<520;i++) {
        float a = TAU*rnd01(i*19u) + 0.25f*sinf(t + i);
        float speed = 140 + 760*rnd01(i*23u);
        float rr = 30 + speed * powf(u,0.76f);
        float wig = sinf(t*4 + i)*18;
        float x = cx + cosf(a)*(rr+wig);
        float y = cy + sinf(a)*(rr+wig)*0.74f;
        Color pc = cmix(C_RED, C_PINK, rnd01(i*29u));
        disc_add(x,y,1.1f+3.0f*rnd01(i*31u),pc,0.34f+0.18f*u);
        if (i%5==0) line_add(cx,cy,x,y,pc,0.035f);
    }
    for (int i=0;i<48;i++) {
        float a = TAU*i/48.0f + t*0.17f;
        float r = 70 + 320*powf(u,0.52f) + 24*sinf(t+i);
        shard(cx+cosf(a)*r, cy+sinf(a)*r*0.73f, 15+9*sinf(t+i), a+t, C_PINK, 0.42f);
    }
    for (int i=0;i<5;i++) circle_glow(cx,cy,48+90*i+36*u,C_PINK,0.9f,0.18f);
    draw_lattice_sigil(cx, cy, 10.5f + 14.0f*u, cmix(C_WHITE, C_GOLD, 0.3f), 0.68f);
}

static void draw_abstraction_field(float t, float u) {
    Color c = cmix(C_PINK, C_BLUE, 0.35f + 0.25f*sinf(t));
    draw_lattice_plane(t, c, 0.88f);
    float cx = W*0.5f, cy = H*0.61f;
    float w = 560, h = 160;
    line_glow(cx-w/2,cy,cx,cy-h/2,c,1.8f,0.55f);
    line_glow(cx,cy-h/2,cx+w/2,cy,c,1.8f,0.55f);
    line_glow(cx+w/2,cy,cx,cy+h/2,c,1.8f,0.55f);
    line_glow(cx,cy+h/2,cx-w/2,cy,c,1.8f,0.55f);
    draw_lattice_sigil(cx, cy - 90, 9.0f + 1.5f*sinf(t*1.8f), cmix(C_WHITE, C_BLUE, 0.35f), 0.60f);
    for (int i=0;i<620;i++) {
        float a = TAU*rnd01(i*43u) + t*(0.4f+0.3f*rnd01(i));
        float base = 620*rnd01(i*7u);
        float decel = powf(1.0f-u, 2.2f);
        float r = 40 + base*decel;
        float x = cx + cosf(a)*r;
        float y = cy + sinf(a)*r*0.32f;
        disc_add(x,y,1.2f+2*rnd01(i*2u), cmix(C_BLUE,C_PINK,rnd01(i*3u)), 0.42f);
    }
    draw_text_center((int)cx, (int)(cy-12), "PI_2D CONTAINMENT FIELD", 2, C_WHITE, 0.65f);
}

static void draw_axiom_split(float t, float u) {
    float cx = W*0.5f, cy = H*0.42f;
    Color c = cmix(C_PURPLE,C_PINK,0.45f+0.25f*sinf(t));
    for (int i=0;i<11;i++) {
        float y = 138 + i*35 + 7*sinf(t+i);
        float x0 = cx + 18*sinf(t*1.4f+i);
        float sep = 40 + 360*smoothstepf(0.02f,0.96f,u);
        float x1 = x0 - sep*(0.48f+0.08f*sinf(i));
        float x2 = x0 + sep*(0.48f+0.08f*cosf(i));
        line_glow(x0,y,x1,y-18*sinf(t+i),c,1.0f,0.50f);
        line_glow(x0,y,x2,y+18*cosf(t+i),c,1.0f,0.50f);
        disc_add(x0,y,4.8f,c,0.55f);
        disc_add(x1,y-18*sinf(t+i),4,C_RED,0.65f);
        disc_add(x2,y+18*cosf(t+i),4,C_BLUE,0.65f);
        char lab[8]; snprintf(lab,sizeof(lab),"A%d",i+1);
        draw_text((int)x0-10,(int)y-25,lab,1,C_WHITE,0.7f);
    }
    circle_glow(cx,cy,100+60*sinf(t*1.5f),c,1.2f,0.28f);
    circle_glow(cx,cy,180+20*sinf(t*1.1f),C_PURPLE,1.0f,0.20f);
    draw_lattice_sigil(cx, cy, 10.0f, C_WHITE, 0.42f);
}

static void draw_unification_field(float t, float u) {
    float cx = W*0.5f, cy = H*0.43f;
    Color c = cmix(C_BLUE, C_GREEN, 0.5f + 0.35f*sinf(t));
    for (int ring = 0; ring < 5; ++ring) {
        float rr = 60 + ring * 70.0f;
        ellipse_glow(cx, cy, rr + 10*sinf(t+ring), 0.45f*rr + 5*cosf(t*1.4f+ring), cmix(c, C_PINK, ring/5.0f), 1.0f, 0.26f);
    }
    for (int i = 0; i < 720; ++i) {
        float a = TAU * rnd01(i*5u) + t*(0.2f + 0.4f*rnd01(i*7u));
        float rr = 320 * (1.0f - smoothstepf(0.0f, 1.0f, u)) + 40 + 100 * rnd01(i*11u);
        float x = cx + cosf(a) * rr;
        float y = cy + sinf(a) * rr * 0.62f;
        float tx = cx + cosf(a + 1.2f*sinf(t+i)) * (40 + 22*rnd01(i));
        float ty = cy + sinf(a + 1.2f*sinf(t+i)) * (32 + 14*rnd01(i));
        Color pc = cmix(C_BLUE, C_GREEN, rnd01(i*13u));
        line_add(x, y, tx, ty, pc, 0.035f);
        disc_add(tx, ty, 1.6f + 1.4f*rnd01(i*17u), pc, 0.46f);
    }
    draw_lattice_sigil(cx, cy, 14.0f + 2.5f*sinf(t*1.8f), C_WHITE, 0.70f);
    draw_text_center((int)cx, (int)(cy+100), "Y_UNI : PARTICLE CLASSES MERGE INTO ONE FIELD", 2, C_WHITE, 0.66f);
}

static void draw_quantum_deceleration(float t, float u) {
    float cx = W*0.5f, cy = H*0.42f;
    Color c = cmix(C_GOLD, C_GREEN, 0.45f + 0.25f*sinf(t));
    for (int i = 0; i < 480; ++i) {
        float a = TAU * rnd01(i*31u);
        float speed = 1.0f - smoothstepf(0.0f, 1.0f, u);
        float rr = 70 + (260 + 220*rnd01(i*7u)) * speed;
        float x = cx + cosf(a + t*(1.2f + rnd01(i))) * rr;
        float y = cy + sinf(a + t*(1.2f + rnd01(i))) * rr * 0.58f;
        disc_add(x, y, 1.2f + 1.6f*rnd01(i*3u), c, 0.38f);
        if (i % 7 == 0) line_add(cx, cy, x, y, c, 0.028f);
    }
    for (int r = 0; r < 6; ++r) {
        float rr = 90 + r*46;
        circle_glow(cx, cy, rr, cmix(C_GOLD, C_BLUE, r/6.0f), 0.9f, 0.14f * (1.0f - 0.10f*r));
    }
    rect_blend((int)(cx-220), (int)(cy+94), (int)(cx+220), (int)(cy+152), C_BLACK, 0.55f);
    draw_text_center((int)cx, (int)(cy+109), "DELTA_Q -> 0", 3, C_WHITE, 0.78f);
    draw_text_center((int)cx, (int)(cy+134), "MOTION DAMPED  -  COHERENCE RISING", 2, c, 0.62f);
}

static void draw_cosmic_regenesis(float t, float u) {
    float cx = W*0.5f, cy = H*0.42f;
    for (int i=0;i<1000;i++) {
        float a = TAU*rnd01(i*57u);
        float r0 = 690*rnd01(i*61u) + 35;
        float m = (u < 0.5f) ? (1.0f - smoothstepf(0.0f,0.5f,u)) : smoothstepf(0.5f,1.0f,u);
        float twist = 8.0f * (u-0.5f) + rnd01(i)*2.0f + 0.08f*sinf(t+i);
        float x = cx + cosf(a+twist)*r0*m;
        float y = cy + sinf(a+twist)*r0*m*0.70f;
        Color pc = (u < 0.5f) ? cmix(C_RED,C_PURPLE,rnd01(i)) : cmix(C_GREEN,C_BLUE,rnd01(i));
        disc_add(x,y,1.0f+2.4f*rnd01(i*3u),pc,0.45f);
        if (i%30==0) line_add(cx,cy,x,y,pc,0.04f);
    }
    disc_add(cx,cy,24+90*fabsf(0.5f-u), (u<0.5f)?C_RED:C_GREEN, 0.6f);
    circle_glow(cx,cy,60+400*smoothstepf(0.5f,1.0f,u),cmix(C_GREEN,C_PINK,0.4f),1.3f,0.30f);
    draw_lattice_sigil(cx, cy, 10.0f + 12.0f*smoothstepf(0.5f,1.0f,u), C_WHITE, 0.76f);
    draw_text_center((int)cx,(int)(cy+88), (u<0.5f ? "UNIVERSE NULLIFIED" : "NEW UNIVERSE BORN"), 2, C_WHITE, 0.74f);
}

static const char *scene_name(int s) {
    switch(s) {
        case 0: return "LATTICRA SUBSTRATE";
        case 1: return "MATRIX SUBSTRATE";
        case 2: return "SIGKOKILLA MODUL";
        case 3: return "ABSTRACTION FIELD";
        case 4: return "AXIOM SPLIT";
        case 5: return "UNIFICATION FIELD";
        case 6: return "QUANTUM DECELERATION";
        default:return "COSMIC REGENESIS";
    }
}

static const char *theorem_title(int s) {
    switch(s) {
        case 0: return "PRIMORDIAL LATTICRA SUBSTRATE THEOREM";
        case 1: return "LATTICRA MATRIX SUBSTRATE THEOREM";
        case 2: return "SIGKOKILLA MODUL EXPANSION THEOREM";
        case 3: return "CONTAINMENT FIELD OF ABSTRACTION THEOREM";
        case 4: return "AXIOMATIC FRACTURE THEOREM";
        case 5: return "UNIFICATION FIELD OF PARTICLES THEOREM";
        case 6: return "QUANTUM DECELERATION THEOREM";
        default:return "ONE-MINUTE COSMIC REGENESIS THEOREM";
    }
}

static const char *eq1(int s) {
    switch(s) {
        case 0: return "L0 = < N, E, PSI > ; CLOSURE(L0) => SUBSTRATE OF ALL TRANSITIONS";
        case 1: return "LPURE = SUBMIN(MR) ; PSI_CHASE(LPURE) => MR = M1 + M2";
        case 2: return "E_SIG = MOD_SK(LR) ; PSI_CHASE(E_SIG) => OMEGA_BURST = XOR(LAMBDA_K)";
        case 3: return "B_E = FRAC(OMEGA_EXP) ; PI_2D(B_E) <= A_FIELD ; DELTA_Q -> 0";
        case 4: return "S = {A1..AN} ; APPLY E_EGO => S' = UNION(AI_UP XOR AI_DOWN)";
        case 5: return "Y_UNI(P) => A_FIELD ; SUM(P_I) -> RHO_UNI ; DIVERSITY -> COHERENCE";
        case 6: return "DELTA_Q = dQ/dt ; LAMBDA_DAMP(DELTA_Q) => LIM(T->INF) DELTA_Q = 0";
        default:return "OMEGA_MINUS(U)->NULL ; OMEGA_PLUS(NULL,I)->U' ; DT = 60S";
    }
}

static const char *eq2(int s) {
    switch(s) {
        case 0: return "A VISUAL FIELD OF NODES, LINKS, RECURSION, AND NUMERIC ORDER 1..9";
        case 1: return "PURE SUBSTRATE OF MATRIX REALITY - SPLITTABLE INTO COUPLED SUBSTRUCTURES";
        case 2: return "EXPLOSIVE MODULAR LATTICE SURGE - CRYSTALLIZED THROUGH SIGNAL";
        case 3: return "BROKEN EXPANSION CONFINED TO A PROJECTED 2D ABSTRACT PLANE";
        case 4: return "AXIOMS OF SPACE SEPARATE AS COHESION FALLS TOWARD NULL";
        case 5: return "PARTICLE CLASSES COLLAPSE INTO A SINGLE COHERENT LATTICE FIELD";
        case 6: return "ENERGY VELOCITY FALLS - THE FIELD BECOMES SLOW, STABLE, AND EXACT";
        default:return "NULLIFICATION PRECEDES RECONSTRUCTION - A NEW FIELD EMERGES FROM ZERO";
    }
}

static Color scene_color(int s, float t) {
    switch(s) {
        case 0: return cmix(C_RED, C_PINK, 0.5f+0.5f*sinf(t));
        case 1: return cmix(C_RED, C_PINK, 0.55f+0.35f*sinf(t*1.4f));
        case 2: return cmix(C_PINK, C_RED, 0.5f);
        case 3: return cmix(C_BLUE, C_PINK, 0.4f+0.25f*sinf(t));
        case 4: return cmix(C_PURPLE, C_PINK, 0.5f);
        case 5: return cmix(C_BLUE, C_GREEN, 0.45f+0.25f*sinf(t));
        case 6: return cmix(C_GOLD, C_GREEN, 0.45f+0.2f*sinf(t));
        default:return cmix(C_GREEN, C_PINK, 0.4f);
    }
}

static void draw_side_panels(float t, int scene) {
    Color c = scene_color(scene, t);
    rect_blend(42, 146, 334, 292, C_BLACK, 0.50f);
    line_glow(42,146,334,146,c,0.9f,0.28f); line_glow(42,292,334,292,c,0.9f,0.28f);
    draw_text(58, 162, "FIELD OPS", 2, C_WHITE, 0.56f);
    draw_text(58, 194, "1..9 -> LATTICE", 2, c, 0.56f);
    draw_text(58, 224, "SUBSTRATE := PURE", 2, c, 0.56f);
    draw_text(58, 254, "RECURSION ACTIVE", 2, C_WHITE, 0.52f);

    rect_blend(W-334, 146, W-42, 292, C_BLACK, 0.50f);
    line_glow(W-334,146,W-42,146,c,0.9f,0.28f); line_glow(W-334,292,W-42,292,c,0.9f,0.28f);
    draw_text(W-316, 162, "MODEL STATE", 2, C_WHITE, 0.56f);
    draw_text(W-316, 194, scene_name(scene), 2, c, 0.56f);
    draw_text(W-316, 224, "2D PROJECTION", 2, c, 0.56f);
    draw_text(W-316, 254, "VIDEO FIELD ENGINE", 1, C_WHITE, 0.52f);
}

static void draw_panel(float t, int scene, float u, int seconds, int frame) {
    int x0 = 80, y0 = H - 202, x1 = W - 80, y1 = H - 70;
    Color pcol = scene_color(scene, t);
    rect_blend(x0,y0,x1,y1,C_BLACK,0.76f);
    line_glow(x0,y0,x1,y0,pcol,1.4f,0.46f); line_glow(x1,y0,x1,y1,pcol,1.4f,0.46f);
    line_glow(x1,y1,x0,y1,pcol,1.4f,0.46f); line_glow(x0,y1,x0,y0,pcol,1.4f,0.46f);
    draw_text_center(W/2, y0+18, theorem_title(scene), 2, C_WHITE, 0.86f);
    line_glow(x0+40,y0+44,x1-40,y0+44,pcol,0.9f,0.35f);
    draw_text_center(W/2, y0+58, eq1(scene), 2, cmix(C_WHITE,pcol,0.45f), 0.82f);
    draw_text_center(W/2, y0+92, eq2(scene), 2, C_WHITE, 0.62f);
    char buf[160];
    int elapsed = frame / FPS;
    int remaining = seconds - elapsed;
    if (remaining < 0) remaining = 0;
    snprintf(buf,sizeof(buf),"MODEL %d/%d  -  %s  -  PROGRESS %02d%%  -  T-REMAIN %03ds", scene+1, SCENES, scene_name(scene), (int)(u*100.0f), remaining);
    draw_text_center(W/2, H-50, buf, 2, cmix(C_GOLD,C_PINK,0.35f+0.35f*sinf(t)), 0.66f);
}

static void draw_scene(int scene, float t, float u) {
    switch(scene) {
        case 0: draw_substrate_core(t, u); break;
        case 1: draw_matrix_substrate(t, u); break;
        case 2: draw_sigkokilla_expansion(t, u); break;
        case 3: draw_abstraction_field(t, u); break;
        case 4: draw_axiom_split(t, u); break;
        case 5: draw_unification_field(t, u); break;
        case 6: draw_quantum_deceleration(t, u); break;
        default: draw_cosmic_regenesis(t, u); break;
    }
}

static void render_frame(int frame, int total_frames, int seconds) {
    float t = (float)frame / FPS;
    float global = (float)frame / (float)(total_frames - 1);
    int scene = (int)floorf(global * SCENES);
    if (scene > SCENES - 1) scene = SCENES - 1;
    float u = global * SCENES - scene;
    u = clampf(u, 0.0f, 1.0f);

    clear_frame(t);
    draw_border(t);
    draw_scene(scene, t, u);
    draw_side_panels(t, scene);

    Color title = scene_color(scene, t);
    draw_text_center(W/2, 30, "LATTICRA SUBSTRATE ENGINE", 4, title, 0.62f);
    draw_text_center(W/2, 76, "SUBSTRATE  -  EXPANSION  -  CONTAINMENT  -  AXIOMS  -  UNITY  -  DECELERATION  -  REGENESIS", 2, C_WHITE, 0.60f);
    draw_panel(t, scene, u, seconds, frame);

    if (global > 0.94f) {
        float q = smoothstepf(0.94f, 1.0f, global);
        draw_text_center(W/2, H/2-18, "LATTICRA REBUILDS THE FIELD FROM FIRST PRINCIPLES", 3, cmix(C_GREEN,C_PINK,0.5f+0.5f*sinf(t*9)), 0.80f*q);
        circle_glow(W/2,H/2,60+500*q,C_GREEN,1.5f,0.25f*q);
    }
}

int main(int argc, char **argv) {
    const char *out = (argc > 1) ? argv[1] : "latticra_substrate_engine.mp4";
    int seconds = (argc > 2) ? atoi(argv[2]) : DEFAULT_SECONDS;
    if (seconds < 16) seconds = 16;
    int total = FPS * seconds;

    fb = (unsigned char*)malloc((size_t)W * H * 3);
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
        W, H, FPS, out);

    FILE *pipe = popen(cmd, "w");
    if (!pipe) {
        fprintf(stderr, "Could not open ffmpeg pipe. Is ffmpeg installed?\n");
        free(fb);
        return 1;
    }

    for (int f = 0; f < total; ++f) {
        render_frame(f, total, seconds);
        size_t wrote = fwrite(fb, 1, (size_t)W * H * 3, pipe);
        if (wrote != (size_t)W * H * 3) {
            fprintf(stderr, "Short write to ffmpeg.\n");
            break;
        }
        if (f % FPS == 0) fprintf(stderr, "rendering %02d/%02d seconds\r", f/FPS, seconds);
    }
    fprintf(stderr, "\nfinalizing mp4...\n");
    int rc = pclose(pipe);
    free(fb);
    if (rc != 0) {
        fprintf(stderr, "ffmpeg exited with code %d. If libx264 is missing, install full ffmpeg or change -c:v libx264 to -c:v mpeg4 in the command string.\n", rc);
        return 1;
    }
    fprintf(stderr, "done: %s\n", out);
    return 0;
}
