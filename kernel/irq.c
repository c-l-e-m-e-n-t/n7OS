#include <inttypes.h>
#include <n7OS/irq.h>
#include <n7OS/segment.h>


typedef union {
    idt_entry_t entry;
    uint64_t value;
} idt_t;

void init_irq_entry(int num_line, uint32_t handler) {
    
    idt_t ligne;
    ligne.entry.offset_inf = handler;
    ligne.entry.sel_segment = KERNEL_CS;
    ligne.entry.zero = 0x00000000;
    ligne.entry.type_attr = 0x8E;
    ligne.entry.offset_sup = handler >> 16;
    idt[num_line] = ligne.value;
}