/* SPDX-License-Identifier: AGPL-3.0-or-later */

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

static volatile u16 *const vga = (volatile u16 *)0xB8000;

static inline void outb(u16 port, u8 value) {
    __asm__ volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline u8 inb(u16 port) {
    u8 value;
    __asm__ volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static void serial_init(void) {
    outb(0x3F8u + 1u, 0x00u);
    outb(0x3F8u + 3u, 0x80u);
    outb(0x3F8u + 0u, 0x03u);
    outb(0x3F8u + 1u, 0x00u);
    outb(0x3F8u + 3u, 0x03u);
    outb(0x3F8u + 2u, 0xC7u);
    outb(0x3F8u + 4u, 0x0Bu);
}

static void serial_putc(char c) {
    while ((inb(0x3F8u + 5u) & 0x20u) == 0u) {}
    outb(0x3F8u, (u8)c);
}

static void serial_puts(const char *s) {
    u32 i = 0u;
    while (s[i] != 0) {
        serial_putc(s[i]);
        i++;
    }
}

static void vga_puts(const char *s) {
    u32 i = 0u;
    while (s[i] != 0) {
        vga[i] = (u16)(0x0F00u | (u8)s[i]);
        i++;
    }
}

void kernel_main(u32 magic, u32 info) {
    (void)magic;
    (void)info;

    serial_init();
    serial_puts("LATTICRA_BOOT_SEED_OK\n");
    vga_puts("Latticra boot seed: GRUB loaded the kernel");

    outb(0xF4u, 0x42u);
    for (;;) {
        __asm__ volatile("hlt");
    }
}
