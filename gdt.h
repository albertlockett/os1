#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H

/** gdt: a helpful structure for holding info about entries in the gdt
 */
struct gdt {
	unsigned int address;
	unsigned short size;
} __attribute__((packed));


/** lgdt:
 *  Load an entry in the global descriptor table
 *
 *  @param segment the struct for the gdt entry to load
 */
void load_gdt(struct gdt segment);

#endif
