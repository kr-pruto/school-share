#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define SIZE 10

struct excel {
	int i_data;
	char c_data[20];
};

int main(void) {
	struct excel cell[10][10];
	int i, j;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			struct excel cell[i][j] = { 0, "비어있음"};
		}
	}
	int m;
	do {
		printf("?? 간단한 엑실 프로그램 ($10 \time 10$)\n");
		printf("=======================");
		printf("1. 전체 표 조회 (간략)\n");
		printf("2. 데이터 저장\n");
		printf("3. 데이터 조회 (상세)\n");
		printf("4. 데이터 삭제\n");
		printf("5. 프로그램 종료\n");
		printf("-----------------------------------------------\n");
		printf("메뉴 선택 (1~5): ");
		scanf("%d", &m);
		if (m == 1) {
			printf("--- 현재 엑셀 표 상태 ---");
			for (i = 0; i < 10; i++) {
				for (j = 0; j < 10; j++) {
					if (cell[i][j].c_data == "비어있음") {
						printf("%d", cell[i][j].i_data);
					}
					else {
						printf("%s", cell[i][j].c_data);
					}
				}
			}
			printf("\n\n");
			printf("=======================");
		}
		if (m == 2) {
			printf("--- 데이터 저장 ---");
			printf("행 인덱스 (0부터 9까지): ");
			scanf("%d");
			printf("열 인덱스 (0부터 9까지): ");
			scanf("%d");
			printf("저장할 정수 데이터: ");
			scanf("%d", &cell[][].i_data);
			printf("저장할 문자열 데이터 (최대 20자): ");
			scanf("%s", &cell[][].c_data);
			printf("\n\n ? [%d행, %d열]에 데이터가 저장되었습니다.\n\n\n");
			printf("=======================");
		}
		if (m == 3) {
			printf("--- 데이터 조회 ---\n");
			printf("행 인덱스 (0부터 9까지): ");
			scanf("%d");
			printf("열 인덱스 (0부터 9까지): ");
			scanf("%d");
			printf("\n\n");
			printf("--- [%d행, %d열] 데이터 ---\n");
			printf("정수 데이터: %d\n", cell[][].i_data);
			printf("문자열 데이터: %s\n", cell[][].c_data);
			printf("=======================");
		}
		if (m == 4) {
			printf("--- 데이터 삭제 ---\n");
			printf("행 인덱스 (0부터 9까지): ");
			scanf("%d");
			printf("열 인덱스 (0부터 9까지): ");
			scanf("%d");
			printf("\n\n");
			printf("데이터를 삭제하였습니다.\n");
			printf("=======================");
		}
		if (m == 5) {
			printf("? 프로그램을 종료합니다. \n\n\n");
		}
	} while (m == 5);
	return 0;
}
