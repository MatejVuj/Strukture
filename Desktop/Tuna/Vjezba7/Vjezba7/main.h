#include "Header.h"

int main() {

	Directory Root, Current, prev;
	Position temp, p, q;

	Root.child = NULL;
	Root.sibling = NULL;

	stack Head;
	Head.Next = NULL;
	Position p_root = &Root;

	int insert = 0, choise = 0;

	while (choise != 5) {

		choise = ChoiseFunction(insert);

		switch (choise) {
		case 1:
			CreateDirectory(p_root, NULL);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			PrintDIR(Root.child);
			break;
		case 5:
			break;

		default:
			printf("Niste odabrali mogucu DOS-NAREDBU");
		}
	}


	return 0;
}
