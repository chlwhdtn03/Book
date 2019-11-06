/*
#include <stdio.h>
int main(void) {
	FILE *fp;
	char *f_name = "age.txt";
	int age, i, n;
	fp = fopen(f_name, "a");
	if (fp == NULL) {
		printf("%s 파일 열기 에러! \n", f_name);
		exit(1);
	}
	printf("회원의 나이를 입력하면 %s 파일에 추가합니다.\n", f_name);																					
	printf("추가할 회원의 수는? ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		printf("회원의 나이는? ");
		scanf("%d", &age);
		fprintf(fp, "%d\n", age);
	}

	fclose(fp);
	printf("회원 %d명의 나이를 %s 파일에 추가했습니다.\n", n, f_name);
	return 0;
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int check_exists();
int add();
int loadList();
int printList();
int del();


typedef struct People {
	char name[20];
	char company[20];
	char family[20];
}People;

People list[100];
int index = 0;

int main(void) {
	int selected;
	loadList();
	while (1) {
		printf("\n\n");
		printf("1. 목록출력\n");
		printf("2. 추가\n");
		printf("3. 삭제\n");
		printf("4. 종료\n");
		scanf("%d", &selected);
		switch (selected)
		{
		case 1:
			if (!check_exists())
				continue;
			printList();
			break;
		case 2:
			add();
			break;
		case 3:
			if (!check_exists())
				continue;
			del();
			break;
		case 4:
			exit(1);
			break;
		default:
			continue;
		}
	}
}

int check_exists() {
	FILE *read = fopen("address.txt", "r");
	if (read == NULL) {
		printf("목록이 존재하지 않습니다.\n");
		return 0;
	}
	fclose(read);
	return 1;
}
int del() {

	char remove[20];
	printf("삭제할 이름을 입력하세요. : ");
	scanf("%s", remove);
	for (int i = 0; i < index; i++) {
		if (strcmp(remove, list[i].name) == 0 ) {
			printf("찾음");
			for (int j = i; j < index; j++) {
				list[j] = list[j + 1];
			}
			index--;
		}
	}
	save();
	return 1;
}

int save() {
	FILE *write = fopen("address.txt", "w");
	for (int i = 0; i < index; i++) {
		fprintf(write, "%s %s %s\n", list[i].name, list[i].company, list[i].family);
	}
	fclose(write);
}

int add() {
	FILE *write = fopen("address.txt", "a");
	printf("이름을 입력하세요 : ");
	scanf("%s", list[index].name);
	printf("회사를 입력하세요 : ");
	scanf("%s", list[index].company);
	printf("가족을 입력하세요 : ");
	scanf("%s", list[index].family);
	fprintf(write, "%s %s %s\n", list[index].name, list[index].company, list[index].family);
	fclose(write);
	index++;
	loadList();
}

int loadList() {
	index = 0; 
	FILE *read = fopen("address.txt", "r");
	if (read == NULL)
		return 0;
	do {
		fscanf(read, "%s %s %s\n", list[index].name, list[index].company, list[index].family);

		index++;
	} while (!feof(read));
	fclose(read);
}
int printList() {
	for (int i = 0; i < index; i++) {
		printf("이름 : %s\t회사 : %s\t가족 : %s\t\n", list[i].name, list[i].company, list[i].family);
	}
}