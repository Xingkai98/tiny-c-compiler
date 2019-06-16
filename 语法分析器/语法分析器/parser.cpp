#include "lexer.h"
#include <vector>
#include <list>
#include <map>
#include <string>
#define mp make_pair
using namespace std;
//词法分析的结果存入了名为CC的数组中
int ip = 0;
extern char cc[100];
char CC[100];
char print_stack[50];
char print_CC[50];

const char NUM = '!';
const int ACC = 0;
const int S1 = 201, S2 = 202, S3 = 203, S4 = 204, S5 = 205, S6 = 206;
const int S7 = 207, S8 = 208, S9 = 209, S10 = 210, S11 = 211, S12 = 212;
const int S13 = 213, S14 = 214, S15 = 215, S16 = 216, S17 = 217, S18 = 218;
const int S19 = 219, S20 = 220, S21 = 221, S22 = 222, S23 = 223, S24 = 224;
const int S25 = 225, S26 = 226, S27 = 227, S28 = 228, S29 = 229;
const int R1 = 301, R2 = 302, R3 = 303, R4 = 304, R5 = 305, R6 = 306, R7 = 307, R8 = 308;

//状态栈和字符栈
list<int> l1;
list<char> l2;

//动作表
map <pair< int, char >, int > m;
//产生式右侧字数查询
map <int, int> beta_query;
map <int, string> R_query;

bool isShift(int a) {
	if (a >= 201 && a < 300)
		return true;
	else
		return false;
}

bool isReduce(int a) {
	if (a >= 301 && a < 310)
		return true;
	else
		return false;
}

void call_lexer() {
	default_init_for_parser();
	//print_buf(1);
	printf("词法分析阶段调用成功！\n");
	lex();
	check_closure();
	CC[strlen(CC)] = '$';
}
void init_map() {
	//strcpy_s(CC, "3+s3-5*7+7-4*8$");
	strcpy_s(CC, cc);
	//CC[strlen(CC)] = '$';
	m[mp(0, '(')] = S4;
	m[mp(0, NUM)] = S5;
	m[mp(0, 'E')] = 1;
	m[mp(0, 'T')] = 2;
	m[mp(0, 'F')] = 3;

	m[mp(1, '+')] = S6;
	m[mp(1, '-')] = S7;
	m[mp(1, '$')] = ACC;

	m[mp(2, '+')] = R3;
	m[mp(2, '-')] = R3;
	m[mp(2, '*')] = S8;
	m[mp(2, '/')] = S9;
	m[mp(2, '$')] = R3;

	m[mp(3, '+')] = R6;
	m[mp(3, '-')] = R6;
	m[mp(3, '*')] = R6;
	m[mp(3, '/')] = R6;
	m[mp(3, '$')] = R6;

	m[mp(4, '(')] = S13;
	m[mp(4, NUM)] = S14;
	m[mp(4, 'E')] = 10;
	m[mp(4, 'T')] = 11;
	m[mp(4, 'F')] = 12;

	m[mp(5, '+')] = R8;
	m[mp(5, '-')] = R8;
	m[mp(5, '*')] = R8;
	m[mp(5, '/')] = R8;
	m[mp(5, '$')] = R8;

	m[mp(6, '(')] = S4;
	m[mp(6, NUM)] = S5;
	m[mp(6, 'T')] = 15;
	m[mp(6, 'F')] = 3;

	m[mp(7, '(')] = S4;
	m[mp(7, NUM)] = S5;
	m[mp(7, 'T')] = 16;
	m[mp(7, 'F')] = 3;

	m[mp(8, '(')] = S4;
	m[mp(8, NUM)] = S5;
	m[mp(8, 'F')] = 17;

	m[mp(8, '(')] = S4;
	m[mp(8, NUM)] = S5;
	m[mp(8, 'F')] = 17;

	m[mp(9, '(')] = S4;
	m[mp(9, NUM)] = S5;
	m[mp(9, 'F')] = 18;

	m[mp(10, '+')] = S20;
	m[mp(10, '-')] = S21;
	m[mp(10, ')')] = S19;

	m[mp(11, '+')] = R3;
	m[mp(11, '-')] = R3;
	m[mp(11, '*')] = S22;
	m[mp(11, '/')] = S23;
	m[mp(11, ')')] = R3;

	m[mp(12, '+')] = R6;
	m[mp(12, '-')] = R6;
	m[mp(12, '*')] = R6;
	m[mp(12, '/')] = R6;
	m[mp(12, ')')] = R6;

	m[mp(13, '(')] = S13;
	m[mp(13, NUM)] = S14;
	m[mp(13, 'E')] = 24;
	m[mp(13, 'T')] = 11;
	m[mp(13, 'F')] = 12;

	m[mp(14, '+')] = R8;
	m[mp(14, '-')] = R8;
	m[mp(14, '*')] = R8;
	m[mp(14, '/')] = R8;
	m[mp(14, ')')] = R8;

	m[mp(15, '+')] = R1;
	m[mp(15, '-')] = R1;
	m[mp(15, '*')] = S8;
	m[mp(15, '/')] = S9;
	m[mp(15, '$')] = R1;

	m[mp(16, '+')] = R2;
	m[mp(16, '-')] = R2;
	m[mp(16, '*')] = S8;
	m[mp(16, '/')] = S9;
	m[mp(16, '$')] = R2;

	m[mp(17, '+')] = R4;
	m[mp(17, '-')] = R4;
	m[mp(17, '*')] = R4;
	m[mp(17, '/')] = R4;
	m[mp(17, '$')] = R4;

	m[mp(18, '+')] = R5;
	m[mp(18, '-')] = R5;
	m[mp(18, '*')] = R5;
	m[mp(18, '/')] = R5;
	m[mp(18, '$')] = R5;

	m[mp(19, '+')] = R7;
	m[mp(19, '-')] = R7;
	m[mp(19, '*')] = R7;
	m[mp(19, '/')] = R7;
	m[mp(19, '$')] = R7;

	m[mp(20, '(')] = S13;
	m[mp(20, NUM)] = S14;
	m[mp(20, 'T')] = 25;
	m[mp(20, 'F')] = 12;

	m[mp(21, '(')] = S13;
	m[mp(21, NUM)] = S14;
	m[mp(21, 'T')] = 26;
	m[mp(21, 'F')] = 12;

	m[mp(22, '(')] = S13;
	m[mp(22, NUM)] = S14;
	m[mp(22, 'F')] = 27;

	m[mp(23, '(')] = S13;
	m[mp(23, NUM)] = S14;
	m[mp(23, 'F')] = 28;

	m[mp(24, '+')] = S20;
	m[mp(24, '-')] = S21;
	m[mp(24, ')')] = S29;

	m[mp(25, '+')] = R1;
	m[mp(25, '-')] = R1;
	m[mp(25, '*')] = S22;
	m[mp(25, '/')] = S23;
	m[mp(25, ')')] = R1;

	m[mp(26, '+')] = R2;
	m[mp(26, '-')] = R2;
	m[mp(26, '*')] = S22;
	m[mp(26, '/')] = S23;
	m[mp(26, ')')] = R2;

	m[mp(27, '+')] = R4;
	m[mp(27, '-')] = R4;
	m[mp(27, '*')] = R4;
	m[mp(27, '/')] = R4;
	m[mp(27, ')')] = R4;

	m[mp(28, '+')] = R5;
	m[mp(28, '-')] = R5;
	m[mp(28, '*')] = R5;
	m[mp(28, '/')] = R5;
	m[mp(28, ')')] = R5;

	m[mp(29, '+')] = R7;
	m[mp(29, '-')] = R7;
	m[mp(29, '*')] = R7;
	m[mp(29, '/')] = R7;
	m[mp(29, ')')] = R7;

	beta_query[R1] = 3;
	beta_query[R2] = 3;
	beta_query[R3] = 1;
	beta_query[R4] = 3;
	beta_query[R5] = 3;
	beta_query[R6] = 1;
	beta_query[R7] = 3;
	beta_query[R8] = 1;

	R_query[R1] = "E->E+T";
	R_query[R2] = "E->E-T";
	R_query[R3] = "E->T";
	R_query[R4] = "T->T*F";
	R_query[R5] = "T->T/F";
	R_query[R6] = "T->F";
	R_query[R7] = "F->(E)";
	R_query[R8] = "F->num";
}
void output_stack() {
	int blank = 80;
	auto one = l1.begin();
	auto two = l2.begin();
	while (one != l1.end() || two != l2.end()) {
		printf("%d ",*one);
		if (*one >= 10)
			blank -= 3;
		else	
			blank -= 2;
		one++;
		if (two != l2.end()) {
			if (*two >= '0' && *two <= '9')
				printf("N ");
			else
				printf("%c ", *two);
			two++;
			blank -= 2;
		}
	}
	for (int i = 0; i < blank; i++)
		printf(" ");
}
void output_CC() {
	memset(print_CC, 0, sizeof(print_CC));
	for (int i = ip; i < strlen(CC); i++) {
		if (i == ip)
			print_CC[0] = CC[i];
		else
			print_CC[strlen(print_CC)] = CC[i];
	}
}

void parse() {
	//步骤数
	int step = 1;
	init_map();
	printf("\ntoken数组：\n%s\n", CC);
	//S0为0入栈
	l1.push_back(0);
	int top = 0;
	char a = '.';
	do {
		printf("%5d       ", step);
		//初始化栈顶和目前所读取的符号
		if (!l1.empty())
			top = l1.back();
		else
			printf("l1已经为空。\n");
		a = CC[ip];
		//t为操作代号
		//这里的数字（num非终结符）不应该直接以数字本身make_pair
		//而应该以NUM来make_pair
		int t = 0;
		if(a>='0' && a<='9')
			t = m[mp(top, NUM)];
		else
			t = m[mp(top, a)];
		if (isShift(t)) {
			l1.push_back(t-200);
			l2.push_back(a);
			ip += 1;
			//输出动作t
			step++;
			output_stack();
			output_CC();
			printf("%s", print_CC);
			puts("");
		}
		else if (isReduce(t)) {
			//弹出|beta|个符号
			for (int i = 0; i < beta_query[t]; i++) {
				if (!l1.empty())
					l1.pop_back();
				else
					printf("l1已空。\n");
				if (!l2.empty())
					l2.pop_back();
				else
					printf("l2已空。\n");
			}
			int ss = l1.back();
			char A = R_query[t][0];
			int Goto = m[mp(ss, A)];
			l1.push_back(Goto);
			l2.push_back(A);
			//输出产生式t
			step++;
			output_stack();
			output_CC();
			printf("%s", print_CC);
			puts("");
		}
		else if (t == ACC) {
			return;
		}
		else {
			printf("解析过程出错。\n");
		}
	} while (1);
}
int main() {
	call_lexer();
	parse();
	system("pause");
	return 0;
}