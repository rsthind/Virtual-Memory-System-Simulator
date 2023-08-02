#include <stdlib.h>

#include "swapops.h"
#include "util.h"

static void sim_diskmap_dump(swap_entry_t *diskmap, uint32_t pid) {
    printf("\tPID %d Diskmap Dump:\n", pid);
    for (int i = 0; i < NUM_PAGES; i++) {
        if (diskmap[i] != 0){
            printf("\t\tvpn %5d -> swap entry %8ld\n", i, diskmap[i]);
        }
    }
    printf("\tEnd of Diskmap dump\n");
}

swap_queue_t swap_queue;

void swap_read(pte_t *pte, void *dst) {

    swap_info_t *info = swap_queue_find(&swap_queue, pte->swap);
    if (!info) {
        panic("Attempted to read an invalid swap entry.\nHINT: How do you check if a swap entry exists, and if it does not, what should you put in memory instead?");
    }
    memcpy(dst, info->page_data, PAGE_SIZE);
}

void swap_write(pte_t *pte, void *src) {

    swap_info_t *info = swap_queue_find(&swap_queue, pte->swap);
    if (!info) {
        info = create_entry();
        swap_queue_enqueue(&swap_queue, info);
        pte->swap = info->token;
    }
    memcpy(info->page_data, src, PAGE_SIZE);
}

void swap_free(pte_t *pte) {
    swap_entry_t swp_entry = pte->swap;
    if (!swap_queue_find(&swap_queue, swp_entry)) {
        panic("Attempted to free an invalid swap entry!");
    }
    swap_queue_dequeue(&swap_queue, pte->swap);
    pte->swap = 0;
}

void diskmap_init(pcb_t* process) {
    swap_entry_t *dm = (swap_entry_t *)calloc((size_t) NUM_PAGES, sizeof(swap_entry_t));

    if(dm == NULL)
    {
        panic("Disk map allocation failed due to memory issues\n");
    }

    process->diskmap = dm;
}

void diskmap_free(pcb_t* process) {
    if (process->diskmap == NULL) {
        panic("Attempted to free unintialized diskmap\n");
    }

    sim_diskmap_dump(process -> diskmap, process -> pid);

    free(process->diskmap);
}

void diskmap_update(vpn_t vpn, swap_entry_t swap) {
    current_process -> diskmap[vpn] = swap;
}

void diskmap_read(pte_t *pte, void *dst) {
    void * temp = calloc(PAGE_SIZE, sizeof(uint8_t));
    swap_write(pte, temp);
    swap_read(pte, dst);
    free(temp);
}

