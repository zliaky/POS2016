#include <stdio.h>

int base = 0x220;
int virtual_address = 0x317a;
int physic_page[0x80][0x20];

int main() {

	freopen("data.txt", "r", stdin);
	for (int pp = 0x00; pp < 0x80; ++pp) {
		int page_no;
		scanf("page %x: ", &page_no);
		for (int delta = 0x00; delta < 0x20; ++delta) {
			scanf("%x", &physic_page[pp][delta]);
		}
		scanf("\n");
	}

	printf("Virtual Address %x:\n", virtual_address);

	int pde = virtual_address >> 10;
	int pte = (virtual_address >> 5) & 0x1f;
	int delta = virtual_address & 0x1f;

	int pde_content = physic_page[base >> 5][pde];
	int pde_valid = pde_content >> 7;
	pde_content = pde_content & 0x7f;

	printf("  --> pde index:0x%x  pde contents:(valid %x, pfn 0x%x)\n", pde, pde_valid, pde_content);

	if (pde_valid == 0) {
		printf("      --> Fault (page directory entry not valid)\n");
		return 0;
	}

	int pte_content = physic_page[pde_content][pte];
	int pte_valid = pte_content >> 7;
	pte_content = pte_content & 0x7f;

    printf("    --> pte index:0x%x  pte contents:(valid %x, pfn 0x%x)\n", pte, pte_valid, pte_content);

    if (pte_valid == 0) {
    	printf("      --> Fault (page table entry not valid)\n");
    	return 0;
    }

    int physic_address = (pte_content << 5) + delta;
    int value = physic_page[pte_content][delta];
    printf("      --> Translates to Physical Address 0x%x --> Value: %x\n", physic_address, value);

	return 0;
}
