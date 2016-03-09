#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_BLOCK 10000

struct unit {
	struct unit *next;
	unsigned int size;
};

struct unit base;
struct unit *freep;

struct unit *addr[MAX_BLOCK];
unsigned int freed[MAX_BLOCK];
unsigned int unit_num;

void my_free(void *ap) {
	struct unit *bp, *p;
	bp = (struct unit*) ap - 1;
	for (p = freep; !(bp > p && bp < p->next); p = p->next) {
		if ((p >= p->next) && ((bp > p) || (bp < p->next))) {
			break;
		}
	}
	if (bp + bp->size == p->next) {
		bp->size += p->next->size;
		bp->next = p->next->next;
	}
	else {
		bp->next = p->next;
	}
	if (p + p->size == bp) {
		p->size += bp->size;
		p->next = bp->next;
	}
	else {
		p->next = bp;
	}
	freep = p;
}

struct unit *my_more(unsigned int nu) {
	char *p;
	struct unit *hp;
	if (nu < 4096) {
		nu = 4096;
	}
	p = sbrk(nu * sizeof(struct unit));
	if (p == (char*) -1) {
		return 0;
	}
	hp = (struct unit*) p;
	hp->size = nu;
	my_free((void*) (hp + 1));
	return freep;
}

void *my_alloc(unsigned int nbytes) {
	struct unit *p, *prevp;
	unsigned int nunits;
	nunits = (nbytes + sizeof(struct unit) - 1) / sizeof(struct unit) + 1;
	if ((prevp = freep) == 0) {
		base.next = freep = prevp = &base;
		base.size = 0;
	}
	for (p = prevp->next; ; prevp = p, p = p->next) {
		if (p->size >= nunits) {
			if (p->size == nunits) {
				prevp->next = p->next;
			}
			else {
				p->size -= nunits;
				p += p->size;
				p->size = nunits;
			}
			freep = prevp;
			return (void*) (p + 1);
		}
		if (p == freep) {
			if ((p = my_more(nunits)) == 0) {
				return 0;
			}
		}
	}
}

void my_list() {
	struct unit *p;
	unsigned int no = 0;
	if ((p = freep) == 0) {
		base.next = freep = p = &base;
		base.size = 0;
	}
	for (p = freep; p != &base; p = p->next) {
		++no;
		printf("Free Block %u: addr = %u, size = %u, next addr = %u.\n", no, (unsigned int) p, p->size, (unsigned int) p->next);
	}
	for (no = 0; no < unit_num; ++no) {
		if (freed[no] == 0) {
			printf("Using Block %u: addr = %u.\n", no, (unsigned int) addr[no]);
		}
	}
	// printf("Base addr = %u, size = %u, next addr = %u.\n", (unsigned int) &base, base.size, (unsigned int) base.next);
	// printf("Free addr = %u, size = %u, next addr = %u.\n", (unsigned int) freep, freep->size, (unsigned int) freep->next);
}

int main() {
	char command[1000];
	unsigned int size;
	unsigned int no;

	unit_num = 0;

	while (1) {
		printf(">> ");
		scanf("%s", command);
		if (strcmp(command, "quit") == 0) {
			break;
		}
		else if (strcmp(command, "malloc") == 0) {
			scanf(" %u", &size);
			if (unit_num >= MAX_BLOCK) {
				break;
			}
			addr[unit_num] = my_alloc(sizeof(struct unit) * size);
			freed[unit_num] = 0;
			++unit_num;
		}
		else if (strcmp(command, "free") == 0) {
			scanf(" %u", &no);
			if (no >= unit_num) {
				printf("The maximum of block is %u.\n", unit_num);
				continue;
			}
			if (freed[no] == 1) {
				printf("Block %u is already freed.\n", no);
				continue;
			}
			my_free(addr[no]);
			freed[no] = 1;
		}
		else if (strcmp(command, "list") == 0) {
			my_list();
		}
		else {
			printf("Unknown command.\n");
		}
	}

	return 0;
}
