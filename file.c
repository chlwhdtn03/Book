/*
#include <stdio.h>
int main(void) {
	FILE *fp;
	char *f_name = "age.txt";
	int age, i, n;
	fp = fopen(f_name, "a");
	if (fp == NULL) {
		printf("%s ���� ���� ����! \n", f_name);
		exit(1);
	}
	printf("ȸ���� ���̸� �Է��ϸ� %s ���Ͽ� �߰��մϴ�.\n", f_name);																					
	printf("�߰��� ȸ���� ����? ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		printf("ȸ���� ���̴�? ");
		scanf("%d", &age);
		fprintf(fp, "%d\n", age);
	}

	fclose(fp);
	printf("ȸ�� %d���� ���̸� %s ���Ͽ� �߰��߽��ϴ�.\n", n, f_name);
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
		printf("1. ������\n");
		printf("2. �߰�\n");
		printf("3. ����\n");
		printf("4. ����\n");
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
		printf("����� �������� �ʽ��ϴ�.\n");
		return 0;
	}
	fclose(read);
	return 1;
}
int del() {

	char remove[20];
	printf("������ �̸��� �Է��ϼ���. : ");
	scanf("%s", remove);
	for (int i = 0; i < index; i++) {
		if (strcmp(remove, list[i].name) == 0 ) {
			printf("ã��");
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
	printf("�̸��� �Է��ϼ��� : ");
	scanf("%s", list[index].name);
	printf("ȸ�縦 �Է��ϼ��� : ");
	scanf("%s", list[index].company);
	printf("������ �Է��ϼ��� : ");
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
		printf("�̸� : %s\tȸ�� : %s\t���� : %s\t\n", list[i].name, list[i].company, list[i].family);
	}
}