// #include <n7OS/paging.h>
// #include <stddef.h> // nécessaire pour NULL

// void initialise_paging() {
//     PageDirectory *dir = (PageDirectory*) kmalloc(sizeof(PageDirectory));
//     for (int i = 0; i < 1024; i++) {
//         dir[i].present = 0;
//         dir[i].rw = 0;
//         dir[i].user = 0;
//         dir[i].accessed = 0;
//         dir[i].dirty = 0;
//         dir[i].unused = 0;
//         dir[i].frame = 0;
//     }
//     __asm__ __volatile__("mov␣%0,␣%%cr3"::"r"(&dir ));
//     uint32_t cr0;
//     __asm__ __volatile__("mov␣%0,␣%%cr0"::"r"(&dir ));
// }

// PageTable alloc_page_entry(uint32_t address, int is_writeable, int is_kernel) {
//     PageTable pgtab= NULL;
//     pgtab = (PageTable) kmalloc(sizeof(Page_Table_Entry)*1024);
//     for (int i = 0; i < 1024; i++) {
//         pgtab[i].present = 0;
//         pgtab[i].rw = is_writeable;
//         pgtab[i].user = is_kernel;
//         pgtab[i].accessed = 0;
//         pgtab[i].dirty = 0;
//         pgtab[i].unused = 0;
//         pgtab[i].frame = 0;
//     }
//     return pgtab;
// }
