#include <stdio.h>

#define MAX_E 13 // MAX_ELEMENT
#define MAX_STR 10 // 단어 최대 길이

typedef char bool;
#define FALSE 0
#define TRUE 1

// HashTable
typedef struct HashTable {
	char* key_pointer;
}ht;

bool full[MAX_E]; // 각 bucket이 full인지 검사
ht hashtable[MAX_E]; // bucket의 갯수가 MAX_E이고 s이 1인 HashTable 생성

void ht_insert(char* word); // 단어를 저장하는 함수
void ht_probe(char* word); // 단어를 탐색하는 함수
int hash_function(char* word); // h(x)값 반환

int main(void)
{
	char word_1[MAX_STR] = "do"; char word_2[MAX_STR] = "for";
	char word_3[MAX_STR] = "if"; char word_4[MAX_STR] = "case";
	char word_5[MAX_STR] = "else"; char word_6[MAX_STR] = "return";
	char word_7[MAX_STR] = "function";
	int i;

	// full 모두 FALSE로 초기화
	for (i = 0; i < MAX_E; i++)
		full[i] = FALSE;

	// HashTable에 단어 저장
	ht_insert(word_1); ht_insert(word_2);
	ht_insert(word_3); ht_insert(word_4);
	ht_insert(word_5); ht_insert(word_6);
	ht_insert(word_7);

	// HashTable에 저장된 결과 출력
	printf("====================\n");
	for (i = 0; i < MAX_E; i++) {
		// 빈 bucket
		if (hashtable[i].key_pointer == '\0')
			printf("[%d]\n", i);
		else
			printf("[%d]\t%s\n", i, hashtable[i].key_pointer);
	}
	printf("====================\n\n");

	// HashTable 단어 탐색
	ht_probe(word_1); ht_probe(word_2);
	ht_probe(word_3); ht_probe(word_4);
	ht_probe(word_5); ht_probe(word_6);
	ht_probe(word_7);

	return 0;
}

void ht_insert(char* word)
{
	int i, num;

	num = hash_function(word); // hash function의 결과를 num에 저장
	i = num; // linear probing을 진행하기 위해 i에 num을 저장

	// num의 bucket이 비어있다면 단어 저장
	if (full[num] != TRUE) {
		hashtable[num].key_pointer = word;
		full[num] = TRUE;
	}

	// linear probing
	else {
		do {
			// i를 1씩 늘려가며(12 다음은 0) 비어있는 bucket을 찾음
			i = (i + 1) % MAX_E;
			if (full[i] != TRUE) {
				hashtable[i].key_pointer = word;
				full[i] = TRUE;
				break;
			}
		} while (i != num);

		// 모두 돌았다면 Hash Table이 꽉 참
		if (i == num)
			printf("FULL HASH TABLE!\n");
	}
}
void ht_probe(char* word)
{
	int num, i;

	num = hash_function(word); // hash function의 결과를 num에 저장
	i = num; // linear probing으로 인한 결과를 탐색하기 위해 i 사용

	// 해당 num 단어가 있으면 출력
	if (word == hashtable[num].key_pointer)
		printf("탐색 %s: 위치 = %d\n", hashtable[num].key_pointer, num);
	
	// 없다면 i를 1씩 늘려가며 HashTable 탐색
	else {
		do {
			i = (i + 1) % MAX_E;
			if (word == hashtable[i].key_pointer) {
				printf("탐색 %s: 위치 = %d\n", hashtable[i].key_pointer, i);
				break;
			}
		} while (i != num);

		// 모두 돌면 해당 단어는 없음
		if (i == num)
			printf("%s라는 단어를 저장하고 있지 않음\n", word);
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