#pragma once

#include "pagesim.h"
#include "paging.h"
#include "swap.h"
#include "types.h"

extern swap_queue_t swap_queue;

/**
 * Determines if the given page table entry has a swap entry.
 *
 * @param entry a pointer to the page table entry to check
 */
static inline int swap_exists(pte_t *entry) {
    return entry->swap != 0;
}

/**
 * Reads bytes from a page table entry's swap entry into physical
 * memory. Copies PAGE_SIZE bytes from swap to memory starting at dst.
 *
 * @param entry a pointer to the page table entry
 * @param dst the destination to which bytes read from swap should be
 * copied. This should be a pointer to the start of the relevant frame
 * in your mem[] array.
 */
void swap_read(pte_t *entry, void *dst);

/**
 * Writes bytes from physical memory into a swap space corresponding
 * to the supplied page table entry. Copies PAGE_SIZE bytes from
 * memory starting at src into swap.
 *
 * If no swap entry is currently allocated for the page, a new one
 * will be allocated. This entry must later be freed with swap_free to
 * avoid a memory leak. The page table entry's swap field is updated
 * automatically.
 *
 * @param entry a pointer to the page table entry
 * @param src the source address from which bytes should be copied
 * into swap. This should be a pointer to the start of the relevant
 * frame in your mem[] array.
 */
void swap_write(pte_t *entry, void *src);

/**
 * Frees the swap entry associated with the given page table entry.
 *
 * The space held by the swap entry is de-allocated and the swap field
 * in the page table is automatically cleared.
 *
 * @param entry a pointer to the page table entry
 */
void swap_free(pte_t *entry);

/**
 * Allocates new diskmap for a given process
 *
 * @param process a pointer to the desired process
 */
void diskmap_init(pcb_t* process);

/**
 * Deallocates the diskamp for a terminated proccess
 *
 * @param process a pointer to the desired process
 */
void diskmap_free(pcb_t* process);

/**
 * Reads a new, empty page from disk space into memory.
 *
 * Writes to swap space to create a newly intialized swap entry
 * and immediately reads page to return to virtual memory manager.
 *
 * @param entry a pointer to the page table entry
 * @param dst the destination to which the intialized empty page should be
 * copied. This should be a pointer to the start of relevant frame in your
 * mem[] array.
 */
void diskmap_read(pte_t* entry, void* dst);

/**
 * Updates the current process' diskmap
 *
 * NOTE: Should be called after each change to swap space or disk map operation
 *
 * @param vpn the virtual page number corresponding to the affected page
 * @param swap the swap entry token corresponding to the affected page
 */

void diskmap_update(vpn_t vpn, swap_entry_t swap);

