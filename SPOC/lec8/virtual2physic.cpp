#include <stdio.h>

int pdbr;
int virtual_address = 0x1c13;
int physic[0x80][0x20];
int disk[0x80][0x20];

int main() {

	freopen("data.txt", "r", stdin);

	scanf("PDBR content: %x\n\n", &pdbr);
	for (int pp = 0x00; pp < 0x80; ++pp) {
		int page_no;
		scanf("page %x: ", &page_no);
		for (int delta = 0x00; delta < 0x20; ++delta) {
			scanf("%x", &physic[pp][delta]);
		}
		scanf("\n");
	}
	for (int pp = 0x00; pp < 0x80; ++pp) {
		int disk_no;
		scanf("disk %x: ", &disk_no);
		for (int delta = 0x00; delta < 0x20; ++delta) {
			scanf("%x", &disk[pp][delta]);
		}
		scanf("\n");
	}

	printf("Virtual Address %04x:\n", virtual_address);

	int pde = virtual_address >> 10;
	int pte = (virtual_address >> 5) & 0x1f;
	int delta = virtual_address & 0x1f;

	int pde_content = physic[pdbr >> 5][pde];
	int pde_valid = pde_content >> 7;
	pde_content = pde_content & 0x7f;

	printf("\t--> pde index:0x%02x  pde contents:(valid %01x, pfn 0x%02x)\n", pde, pde_valid, pde_content);

	if (pde_valid == 0) {
		printf("\t\t--> Fault (page directory entry not valid)\n");
		return 0;
	}

	int pte_content = physic[pde_content][pte];
	int pte_valid = pte_content >> 7;
	pte_content = pte_content & 0x7f;

	printf("\t\t--> pte index:0x%02x  pte contents:(valid %01x, pfn 0x%02x)\n", pte, pte_valid, pte_content);

	if (pte_valid == 0) {
		int disk_address = (pte_content << 5) + delta;
		int value = disk[pte_content][delta];
		printf("\t\t\t--> To Disk Sector Address 0x%04x --> Value: %02x\n", disk_address, value);
		return 0;
	}

	int physic_address = (pte_content << 5) + delta;
	int value = physic[pte_content][delta];
	printf("\t\t\t--> To Physical Address 0x%04x --> Value: %02x\n", physic_address, value);

	return 0;
}
