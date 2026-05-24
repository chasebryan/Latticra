#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define W 1280
#define H 720
#define FPS 30
#define DEFAULT_SECONDS 60
#define PI 3.14159265358979323846f
#define TAU 6.28318530717958647692f

static unsigned char *fb;

typedef struct { float r, g, b; } Color;
static const Color C_RED    = {255,  30,  55};
static const Color C_PINK   = {255,  36, 196};
static const Color C_PURPLE = {185,  54, 255};
static const Color C_BLUE   = { 40, 190, 255};
static const Color C_GREEN  = { 65, 255, 145};
static const Color C_WHITE  = {255, 240, 245};
static const Color C_GOLD   = {255, 198,  42};

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
    // Sparse cosmic noise field, deterministic per frame.
    for (int i = 0; i < 950; ++i) {
        float x = rnd01(i*17u + 11u) * W;
        float y = fmodf(rnd01(i*31u + 7u) * H + t * (10.0f + 38.0f*rnd01(i*5u)), (float)H);
        float tw = 0.35f + 0.65f * sinf(t*3.0f + i*1.731f);
        int ix = (int)x, iy = (int)y;
        if (ix >= 0 && ix < W && iy >= 0 && iy < H) {
            int k = (iy*W + ix)*3;
            fb[k+0] = (unsigned char)clampf(18 + 34*tw, 0, 255);
            fb[k+1] = (unsigned char)clampf(2 + 12*tw, 0, 255);
            fb[k+2] = (unsigned char)clampf(20 + 45*tw, 0, 255);
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
    int seg = 220;
    float px = cx + rx, py = cy;
    for (int i = 1; i <= seg; ++i) {
        float a = TAU * i / seg;
        float x = cx + cosf(a)*rx, y = cy + sinf(a)*ry;
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
    for (int i=0;i<4;i++) line_glow(q[i][0],q[i][1],q[(i+1)%4][0],q[(i+1)%4][1],c,1.2f,power);
    line_add(q[0][0],q[0][1],q[2][0],q[2][1],c,power*0.8f);
    line_add(q[1][0],q[1][1],q[3][0],q[3][1],c,power*0.8f);
    disc_add(cx, cy, s*0.3f, c, power*0.8f);
}

// 5x7 font. Each row uses low 5 bits.
static const unsigned char *glyph(char ch) {
    static const unsigned char BL[7] = {0,0,0,0,0,0,0};
    static const unsigned char A[7]={14,17,17,31,17,17,17}; static const unsigned char B[7]={30,17,17,30,17,17,30};
    static const unsigned char C[7]={15,16,16,16,16,16,15}; static const unsigned char D[7]={30,17,17,17,17,17,30};
    static const unsigned char E[7]={31,16,16,30,16,16,31}; static const unsigned char F[7]={31,16,16,30,16,16,16};
    static const unsigned char G[7]={15,16,16,23,17,17,15}; static const unsigned char GH[7]={17,17,17,31,17,17,17};
    static const unsigned char I[7]={31,4,4,4,4,4,31};     static const unsigned char J[7]={1,1,1,1,17,17,14};
    static const unsigned char K[7]={17,18,20,24,20,18,17}; static const unsigned char L[7]={16,16,16,16,16,16,31};
    static const unsigned char M[7]={17,27,21,21,17,17,17}; static const unsigned char N[7]={17,25,21,19,17,17,17};
    static const unsigned char O[7]={14,17,17,17,17,17,14}; static const unsigned char P[7]={30,17,17,30,16,16,16};
    static const unsigned char Q[7]={14,17,17,17,21,18,13}; static const unsigned char R[7]={30,17,17,30,20,18,17};
    static const unsigned char S[7]={15,16,16,14,1,1,30};   static const unsigned char T[7]={31,4,4,4,4,4,4};
    static const unsigned char U[7]={17,17,17,17,17,17,14}; static const unsigned char V[7]={17,17,17,17,17,10,4};
    static const unsigned char GW[7]={17,17,17,21,21,21,10}; static const unsigned char X[7]={17,17,10,4,10,17,17};
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
    static const unsigned char LB[7]={14,8,8,8,8,8,14};   static const unsigned char RB[7]={14,2,2,2,2,2,14};
    static const unsigned char COL[7]={0,4,4,0,4,4,0};    static const unsigned char DOT[7]={0,0,0,0,0,12,12};
    static const unsigned char COM[7]={0,0,0,0,0,4,8};    static const unsigned char EXC[7]={4,4,4,4,4,0,4};
    static const unsigned char QST[7]={14,17,1,2,4,0,4};  static const unsigned char STAR[7]={0,21,14,31,14,21,0};
    static const unsigned char HASH[7]={10,31,10,10,31,10,0}; static const unsigned char BAR[7]={4,4,4,4,4,4,4};
    static const unsigned char APOS[7]={4,4,8,0,0,0,0};   static const unsigned char CARET[7]={4,10,17,0,0,0,0};
    static const unsigned char AMP[7]={12,18,20,8,21,18,13};
    if (ch >= 'a' && ch <= 'z') ch = (char)(ch - 32);
    switch (ch) {
        case 'A':return A; case 'B':return B; case 'C':return C; case 'D':return D; case 'E':return E; case 'F':return F;
        case 'G':return G; case 'H':return GH; case 'I':return I; case 'J':return J; case 'K':return K; case 'L':return L;
        case 'M':return M; case 'N':return N; case 'O':return O; case 'P':return P; case 'Q':return Q; case 'R':return R;
        case 'S':return S; case 'T':return T; case 'U':return U; case 'V':return V; case 'W':return GW; case 'X':return X;
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
    float cx = W*0.5f, cy = H*0.62f;
    for (int i = -9; i <= 9; ++i) {
        float a = i / 9.0f;
        float x0 = cx + a * 640.0f;
        line_glow(cx, cy-62, x0, H-86, c, 0.9f, power*0.55f);
    }
    for (int j = 0; j < 12; ++j) {
        float z = j / 11.0f;
        float y = mixf(cy - 58, H-90, z*z);
        float rx = mixf(50, 650, z);
        line_glow(cx-rx, y, cx+rx, y, c, 0.6f, power*0.35f);
    }
    for (int r=1; r<=5; ++r) ellipse_glow(cx, cy, r*72.0f + 12*sinf(t+r), r*20.0f + 3*sinf(t*1.3f+r), c, 0.7f, power*0.45f);
}

static void draw_matrix_substrate(float t, float u) {
    (void)u;
    Color c = cmix(C_RED, C_PINK, 0.35f + 0.4f*sinf(t*2.0f));
    float ox = W*0.5f, oy = H*0.44f;
    int N = 9;
    float step = 40.0f;
    for (int y=0;y<N;y++) for (int x=0;x<N;x++) {
        float px = ox + (x-(N-1)/2.0f)*step + sinf(t*2.0f+y)*6.0f;
        float py = oy + (y-(N-1)/2.0f)*step*0.62f + cosf(t*1.7f+x)*5.0f;
        disc_add(px,py,2.0f,c,0.7f);
        if (x+1<N) {
            float qx = ox + (x+1-(N-1)/2.0f)*step + sinf(t*2.0f+y)*6.0f;
            float qy = py;
            line_add(px,py,qx,qy,c,0.12f);
        }
        if (y+1<N) {
            float qx = px;
            float qy = oy + (y+1-(N-1)/2.0f)*step*0.62f + cosf(t*1.7f+x)*5.0f;
            line_add(px,py,qx,qy,c,0.12f);
        }
    }
    for (int i=0;i<70;i++) {
        float a = TAU*rnd01(i*71u) + t*0.2f;
        float r = 210 + 80*rnd01(i*13u) + 18*sinf(t + i);
        shard(ox + cosf(a)*r, oy + sinf(a)*r*0.72f, 8+18*rnd01(i*5u), a+t*0.3f, c, 0.26f);
    }
}

static void draw_sigkokilla_expansion(float t, float u) {
    float cx = W*0.5f, cy = H*0.45f;
    float burst = smoothstepf(0.0f,0.18f,u) * (1.0f-smoothstepf(0.90f,1.0f,u));
    for (int i=0;i<420;i++) {
        float a = TAU*rnd01(i*19u) + 0.25f*sinf(t + i);
        float speed = 110 + 680*rnd01(i*23u);
        float rr = (40 + speed * powf(u,0.72f));
        float wig = sinf(t*4 + i)*18;
        float x = cx + cosf(a)*(rr+wig);
        float y = cy + sinf(a)*(rr+wig)*0.74f;
        Color pc = cmix(C_RED, C_PINK, rnd01(i*29u));
        disc_add(x,y,1.2f+3.0f*rnd01(i*31u),pc,0.35f+0.5f*burst);
        if (i%5==0) line_add(cx,cy,x,y,pc,0.035f);
    }
    for (int i=0;i<36;i++) {
        float a = TAU*i/36.0f + t*0.17f;
        float r = 78 + 290*powf(u,0.52f) + 30*sinf(t+i);
        shard(cx+cosf(a)*r, cy+sinf(a)*r*0.73f, 18+9*sinf(t+i), a+t, C_PINK, 0.42f);
    }
    circle_glow(cx,cy,70+260*u,C_PINK,1.1f,0.35f);
    circle_glow(cx,cy,130+420*u,C_RED,1.0f,0.18f);
}

static void draw_abstraction_field(float t, float u) {
    Color c = cmix(C_PINK, C_BLUE, 0.35f + 0.25f*sinf(t));
    draw_lattice_plane(t, c, 0.85f);
    float cx = W*0.5f, cy = H*0.60f;
    // Containment rectangle/diamond projected onto 2D plane.
    float w = 560, h = 160;
    line_glow(cx-w/2,cy,cx,cy-h/2,c,1.7f,0.55f);
    line_glow(cx,cy-h/2,cx+w/2,cy,c,1.7f,0.55f);
    line_glow(cx+w/2,cy,cx,cy+h/2,c,1.7f,0.55f);
    line_glow(cx,cy+h/2,cx-w/2,cy,c,1.7f,0.55f);
    for (int i=0;i<520;i++) {
        float a = TAU*rnd01(i*43u) + t*(0.4f+0.3f*rnd01(i));
        float base = 610*rnd01(i*7u);
        float decel = powf(1.0f-u, 2.3f);
        float r = 65 + base*decel;
        float x = cx + cosf(a)*r;
        float y = cy + sinf(a)*r*0.32f;
        disc_add(x,y,1.2f+2*rnd01(i*2u), cmix(C_BLUE,C_PINK,rnd01(i*3u)), 0.46f);
    }
    draw_text_center((int)cx, (int)(cy-13), "PI_2D CONTAINMENT FIELD", 2, C_WHITE, 0.65f);
}

static void draw_axiom_split(float t, float u) {
    float cx = W*0.5f, cy = H*0.48f;
    Color c = cmix(C_PURPLE,C_PINK,0.45f+0.25f*sinf(t));
    for (int i=0;i<9;i++) {
        float y = 130 + i*43 + 8*sinf(t+i);
        float x0 = W*0.5f + 30*sinf(t*1.4f+i);
        float sep = 60 + 300*smoothstepf(0.05f,0.9f,u);
        float a = 0.8f*sinf(t*2+i);
        float x1 = x0 - sep*(0.45f+0.1f*sinf(i));
        float x2 = x0 + sep*(0.45f+0.1f*cosf(i));
        line_glow(x0,y,x1,y-18*sinf(a),c,1.0f,0.5f);
        line_glow(x0,y,x2,y+18*cosf(a),c,1.0f,0.5f);
        disc_add(x0,y,5,c,0.55f); disc_add(x1,y-18*sinf(a),4,C_RED,0.65f); disc_add(x2,y+18*cosf(a),4,C_BLUE,0.65f);
        char lab[8]; snprintf(lab,sizeof(lab),"A%d",i+1);
        draw_text((int)x0-10,(int)y-25,lab,1,C_WHITE,0.7f);
    }
    circle_glow(cx,cy,100+60*sinf(t*1.5f),c,1.2f,0.28f);
    circle_glow(cx,cy,180+20*sinf(t*1.1f),C_PURPLE,1.0f,0.20f);
}

static void draw_cosmic_regenesis(float t, float u) {
    float cx = W*0.5f, cy = H*0.45f;
    Color c = u < 0.5f ? C_RED : C_GREEN;
    for (int i=0;i<900;i++) {
        float a = TAU*rnd01(i*57u);
        float r0 = 690*rnd01(i*61u) + 35;
        float m;
        if (u < 0.5f) m = 1.0f - smoothstepf(0.0f,0.5f,u);
        else m = smoothstepf(0.5f,1.0f,u);
        float twist = 8.0f * (u-0.5f) + rnd01(i)*2.0f + 0.08f*sinf(t+i);
        float x = cx + cosf(a+twist)*r0*m;
        float y = cy + sinf(a+twist)*r0*m*0.70f;
        Color pc = u < 0.5f ? cmix(C_RED,C_PURPLE,rnd01(i)) : cmix(C_GREEN,C_BLUE,rnd01(i));
        disc_add(x,y,1.0f+2.4f*rnd01(i*3u),pc,0.45f);
        if (i%30==0) line_add(cx,cy,x,y,pc,0.04f);
    }
    disc_add(cx,cy,24+90*fabsf(0.5f-u),c,0.6f);
    circle_glow(cx,cy,60+400*smoothstepf(0.5f,1.0f,u),cmix(C_GREEN,C_PINK,0.4f),1.3f,0.30f);
    draw_text_center((int)cx,(int)(cy+70), u<0.5f ? "UNIVERSE NULLIFIED" : "NEW UNIVERSE BORN", 2, C_WHITE, 0.75f);
}

static void draw_particles_master(float t, int phase, float u) {
    if (phase == 0) draw_matrix_substrate(t,u);
    else if (phase == 1) draw_sigkokilla_expansion(t,u);
    else if (phase == 2) draw_abstraction_field(t,u);
    else if (phase == 3) draw_axiom_split(t,u);
    else draw_cosmic_regenesis(t,u);
}

static void draw_character(float t, int phase) {
    float cx = W*0.5f, cy = H*0.385f + 8*sinf(t*1.2f);
    Color outline = (phase==2) ? C_BLUE : ((phase==3) ? C_PURPLE : C_PINK);
    Color black = {2, 2, 8};
    // Energy behind character.
    circle_glow(cx, cy+10, 95 + 18*sinf(t*2), outline, 1.5f, 0.22f);
    // Body/hood.
    ellipse_blend(cx, cy+105, 74, 92, black, 0.82f);
    ellipse_blend(cx, cy+40, 45, 52, black, 0.88f);
    line_glow(cx-58,cy+70,cx-145,cy+140,outline,3.0f,0.45f);
    line_glow(cx+58,cy+70,cx+145,cy+140,outline,3.0f,0.45f);
    line_glow(cx-150,cy+138,cx-235,cy+98,outline,2.2f,0.45f);
    line_glow(cx+150,cy+138,cx+260,cy+82,outline,2.2f,0.45f);
    // Hands.
    disc_blend(cx-246, cy+95, 20, black, 0.75f); disc_blend(cx+270, cy+78, 22, black, 0.75f);
    disc_add(cx-246, cy+95, 23, outline, 0.20f); disc_add(cx+270, cy+78, 25, outline, 0.25f);
    for (int i=0;i<5;i++) {
        float aa = -1.8f + i*0.42f;
        line_glow(cx+270,cy+78,cx+270+52*cosf(aa),cy+78+52*sinf(aa),outline,1.8f,0.45f);
        line_glow(cx-246,cy+95,cx-246-44*cosf(aa),cy+95+44*sinf(aa),outline,1.5f,0.35f);
    }
    // Face and cap.
    ellipse_blend(cx, cy+25, 40, 47, black, 0.9f);
    line_glow(cx-48,cy-5,cx+36,cy-19,outline,2.0f,0.45f); // brim
    ellipse_blend(cx-4, cy-22, 45, 22, black, 0.85f);
    ellipse_glow(cx-4, cy-22, 45, 22, outline, 1.0f, 0.28f);
    line_glow(cx-17,cy+17,cx-4,cy+13,C_RED,1.8f,0.8f);
    line_glow(cx+12,cy+11,cx+27,cy+8,C_RED,1.8f,0.8f);
    // Chest lattice sigil.
    float sx = cx, sy = cy+105, s = 13;
    for (int i=-1;i<=1;i++) { line_glow(sx-2*s,sy+i*s,sx+2*s,sy+i*s,outline,1.0f,0.55f); line_glow(sx+i*s,sy-2*s,sx+i*s,sy+2*s,outline,1.0f,0.55f); }
    circle_glow(sx,sy,42,outline,0.7f,0.12f);
}

static const char *stage_name(int p) {
    switch(p) {
        case 0: return "MATRIX SUBSTRATE";
        case 1: return "SIGKOKILLA MODUL";
        case 2: return "ABSTRACTION FIELD";
        case 3: return "AXIOMS SPLIT BY PURE EGO";
        default:return "COSMIC REGENESIS";
    }
}
static const char *theorem_title(int p) {
    switch(p) {
        case 0: return "LATTICRA MATRIX SUBSTRATE THEOREM";
        case 1: return "SIGKOKILLA MODUL EXPANSION THEOREM";
        case 2: return "CONTAINMENT FIELD OF ABSTRACTION THEOREM";
        case 3: return "AXIOMATIC FRACTURE THEOREM";
        default:return "ONE-MINUTE COSMIC REGENESIS THEOREM";
    }
}
static const char *eq1(int p) {
    switch(p) {
        case 0: return "LPURE = SUBMIN(MR); PSI_CHASE(LPURE) => MR = M1 + M2";
        case 1: return "E_SIG = MOD_SK(LR); PSI_CHASE(E_SIG) => OMEGA_BURST = XOR(LAMBDA_K)";
        case 2: return "B_E = FRAC(OMEGA_EXP); PI_2D(B_E) <= A_FIELD; DELTA_Q -> 0";
        case 3: return "S={A1..AN}; APPLY E_EGO => S' = UNION(AI_UP XOR AI_DOWN)";
        default:return "OMEGA_MINUS(U)->NULL; OMEGA_PLUS(NULL,I)->U'; DT = 60S";
    }
}
static const char *eq2(int p) {
    switch(p) {
        case 0: return "PURE SUBSTRATE OF MATRIX REALITY - SPLITTABLE BY RECURSION";
        case 1: return "EXPLOSIVE MODULAR LATTICE SURGE - CRYSTALLIZED THROUGH SIGNAL";
        case 2: return "BROKEN EXPANSION ENCLOSED ON THE ABSTRACT 2D PLANE";
        case 3: return "AXIOMS OF SPACE SEPARATE AS COHESION FALLS TO ZERO";
        default:return "END. BEGIN. SEED. LAW. TIME FOLDS INTO THE NEW FIELD";
    }
}

static void draw_panel(float t, int phase, float u) {
    int x0 = 85, y0 = H - 198, x1 = W - 85, y1 = H - 72;
    Color pcol = (phase==2) ? C_BLUE : ((phase==3)? C_PURPLE : C_RED);
    rect_blend(x0,y0,x1,y1,(Color){5,0,12},0.72f);
    line_glow(x0,y0,x1,y0,pcol,1.3f,0.45f); line_glow(x1,y0,x1,y1,pcol,1.3f,0.45f);
    line_glow(x1,y1,x0,y1,pcol,1.3f,0.45f); line_glow(x0,y1,x0,y0,pcol,1.3f,0.45f);
    draw_text_center(W/2, y0+18, theorem_title(phase), 2, C_WHITE, 0.85f);
    line_glow(x0+40,y0+44,x1-40,y0+44,pcol,0.9f,0.35f);
    draw_text_center(W/2, y0+58, eq1(phase), 2, cmix(C_WHITE,pcol,0.45f), 0.82f);
    draw_text_center(W/2, y0+92, eq2(phase), 2, C_WHITE, 0.62f);
    char buf[128];
    int seconds_left = (int)ceilf((1.0f-u) * 12.0f);
    snprintf(buf,sizeof(buf),"MODEL %d/5  -  %s  -  LOCAL T-MINUS %02d", phase+1, stage_name(phase), seconds_left);
    draw_text_center(W/2, H-50, buf, 2, cmix(C_GOLD,C_PINK,0.35f+0.35f*sinf(t)), 0.65f);
}

static void draw_side_equations(float t, int phase) {
    (void)t;
    Color c = phase==2 ? C_BLUE : (phase==3 ? C_PURPLE : C_RED);
    rect_blend(42, 146, 310, 274, (Color){3,0,10}, 0.42f);
    line_glow(42,146,310,146,c,0.8f,0.25f); line_glow(42,274,310,274,c,0.8f,0.25f);
    draw_text(58, 162, "FIELD OPS", 2, C_WHITE, 0.55f);
    draw_text(58, 194, "1..9 -> LATTICE", 2, c, 0.55f);
    draw_text(58, 224, "DELTA_Q -> 0", 2, c, 0.55f);
    draw_text(58, 254, "COHESION := PURE", 1, C_WHITE, 0.55f);

    rect_blend(W-310, 146, W-42, 274, (Color){3,0,10}, 0.42f);
    line_glow(W-310,146,W-42,146,c,0.8f,0.25f); line_glow(W-310,274,W-42,274,c,0.8f,0.25f);
    draw_text(W-292, 162, "2D PLANE", 2, C_WHITE, 0.55f);
    draw_text(W-292, 194, "PARTICLES UNIFY", 2, c, 0.55f);
    draw_text(W-292, 224, "EXPANSION BREAKS", 2, c, 0.55f);
    draw_text(W-292, 254, "REGENESIS STARTS", 1, C_WHITE, 0.55f);
}

static void render_frame(int frame, int total_frames) {
    float t = (float)frame / FPS;
    float global = (float)frame / (float)(total_frames - 1);
    int phase = (int)floorf(global * 5.0f);
    if (phase > 4) phase = 4;
    float u = global * 5.0f - phase;
    u = clampf(u, 0.0f, 1.0f);

    clear_frame(t);
    draw_border(t);
    draw_particles_master(t, phase, u);
    draw_side_equations(t, phase);
    draw_character(t, phase);

    Color title = phase==2 ? C_BLUE : (phase==3 ? C_PURPLE : C_PINK);
    draw_text_center(W/2, 32, "LATTICRA THEOREM ENGINE", 4, title, 0.60f);
    draw_text_center(W/2, 78, "SPACE AXIOMS  -  EXPANSION BREAK  -  2D ABSTRACTION  -  REGENESIS", 2, C_WHITE, 0.58f);
    draw_panel(t, phase, u);

    // Final signature flare.
    if (global > 0.93f) {
        float q = smoothstepf(0.93f, 1.0f, global);
        draw_text_center(W/2, H/2-18, "I USE LATTICRA B/T/W", 5, cmix(C_GREEN,C_PINK,0.5f+0.5f*sinf(t*9)), 0.85f*q);
        circle_glow(W/2,H/2,60+500*q,C_GREEN,1.5f,0.25f*q);
    }
}

int main(int argc, char **argv) {
    const char *out = (argc > 1) ? argv[1] : "latticra_theorem_engine.mp4";
    int seconds = (argc > 2) ? atoi(argv[2]) : DEFAULT_SECONDS;
    if (seconds < 5) seconds = 5;
    int total = FPS * seconds;

    fb = (unsigned char*)malloc((size_t)W * H * 3);
    if (!fb) { fprintf(stderr, "Could not allocate framebuffer.\n"); return 1; }

    char cmd[2048];
    snprintf(cmd, sizeof(cmd),
        "ffmpeg -y -f rawvideo -pix_fmt rgb24 -s %dx%d -r %d -i - "
        "-f lavfi -i anullsrc=channel_layout=stereo:sample_rate=44100 "
        "-shortest -c:v libx264 -profile:v high -level:v 4.0 "
        "-preset veryfast -crf 20 -pix_fmt yuv420p "
        "-c:a aac -b:a 128k -movflags +faststart \"%s\"",
        W, H, FPS, out);

    FILE *pipe = popen(cmd, "w");
    if (!pipe) { fprintf(stderr, "Could not open ffmpeg pipe. Is ffmpeg installed?\n"); free(fb); return 1; }

    for (int f = 0; f < total; ++f) {
        render_frame(f, total);
        size_t wrote = fwrite(fb, 1, (size_t)W * H * 3, pipe);
        if (wrote != (size_t)W * H * 3) { fprintf(stderr, "Short write to ffmpeg.\n"); break; }
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
