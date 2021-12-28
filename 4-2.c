#include <stdio.h>

#define MAX_E 13 // MAX_ELEMENT
#define MAX_STR 10 // �ܾ� �ִ� ����

typedef char bool;
#define FALSE 0
#define TRUE 1

// HashTable
typedef struct HashTable {
	char* key_pointer;
}ht;

bool full[MAX_E]; // �� bucket�� full���� �˻�
ht hashtable[MAX_E]; // bucket�� ������ MAX_E�̰� s�� 1�� HashTable ����

void ht_insert(char* word); // �ܾ �����ϴ� �Լ�
void ht_probe(char* word); // �ܾ Ž���ϴ� �Լ�
int hash_function(char* word); // h(x)�� ��ȯ

int main(void)
{
	char word_1[MAX_STR] = "do"; char word_2[MAX_STR] = "for";
	char word_3[MAX_STR] = "if"; char word_4[MAX_STR] = "case";
	char word_5[MAX_STR] = "else"; char word_6[MAX_STR] = "return";
	char word_7[MAX_STR] = "function";
	int i;

	// full ��� FALSE�� �ʱ�ȭ
	for (i = 0; i < MAX_E; i++)
		full[i] = FALSE;

	// HashTable�� �ܾ� ����
	ht_insert(word_1); ht_insert(word_2);
	ht_insert(word_3); ht_insert(word_4);
	ht_insert(word_5); ht_insert(word_6);
	ht_insert(word_7);

	// HashTable�� ����� ��� ���
	printf("====================\n");
	for (i = 0; i < MAX_E; i++) {
		// �� bucket
		if (hashtable[i].key_pointer == '\0')
			printf("[%d]\n", i);
		else
			printf("[%d]\t%s\n", i, hashtable[i].key_pointer);
	}
	printf("====================\n\n");

	// HashTable �ܾ� Ž��
	ht_probe(word_1); ht_probe(word_2);
	ht_probe(word_3); ht_probe(word_4);
	ht_probe(word_5); ht_probe(word_6);
	ht_probe(word_7);

	return 0;
}

void ht_insert(char* word)
{
	int i, num;

	num = hash_function(word); // hash function�� ����� num�� ����
	i = num; // linear probing�� �����ϱ� ���� i�� num�� ����

	// num�� bucket�� ����ִٸ� �ܾ� ����
	if (full[num] != TRUE) {
		hashtable[num].key_pointer = word;
		full[num] = TRUE;
	}

	// linear probing
	else {
		do {
			// i�� 1�� �÷�����(12 ������ 0) ����ִ� bucket�� ã��
			i = (i + 1) % MAX_E;
			if (full[i] != TRUE) {
				hashtable[i].key_pointer = word;
				full[i] = TRUE;
				break;
			}
		} while (i != num);

		// ��� ���Ҵٸ� Hash Table�� �� ��
		if (i == num)
			printf("FULL HASH TABLE!\n");
	}
}
void ht_probe(char* word)
{
	int num, i;

	num = hash_function(word); // hash function�� ����� num�� ����
	i = num; // linear probing���� ���� ����� Ž���ϱ� ���� i ���

	// �ش� num �ܾ ������ ���
	if (word == hashtable[num].key_pointer)
		printf("Ž�� %s: ��ġ = %d\n", hashtable[num].key_pointer, num);
	
	// ���ٸ� i�� 1�� �÷����� HashTable Ž��
	else {
		do {
			i = (i + 1) % MAX_E;
			if (word == hashtable[i].key_pointer) {
				printf("Ž�� %s: ��ġ = %d\n", hashtable[i].key_pointer, i);
				break;
			}
		} while (i != num);

		// ��� ���� �ش� �ܾ�� ����
		if (i == num)
			printf("%s��� �ܾ �����ϰ� ���� ����\n", word);
	}
}

int hash_function(char* word)
{
	char* ch;
	int num = 0;
	
	ch = word;
	while (*ch != '\0')
		num += *ch++;
	num = num % 13;

	return num;
}