#include "lexer.h"
#include "parser.h"

using namespace std;
//�ʷ������Ľ����������ΪCC��������
int ip = 0;
extern char cc[100];
char CC[100];
char print_stack[50];
char print_CC[50];

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

Parser::Parser(){
	Parser::call_lexer();
	Parser::init_map();
}

void Parser::call_lexer() {
	Lexer l;
	l.lex();
	this->CC[strlen(this->CC)] = '$';
}
void Parser::init_map() {
	//strcpy(CC, "3+s3-5*7+7-4*8$");
	strcpy(CC, cc);
	//CC[strlen(CC)] = '$';
	this->m[mp(0, '(')] = S4;
	this->m[mp(0, NUM)] = S5;
	this->m[mp(0, 'E')] = 1;
	this->m[mp(0, 'T')] = 2;
	this->m[mp(0, 'F')] = 3;

	this->m[mp(1, '+')] = S6;
	this->m[mp(1, '-')] = S7;
	this->m[mp(1, '$')] = ACC;

	this->m[mp(2, '+')] = R3;
	this->m[mp(2, '-')] = R3;
	this->m[mp(2, '*')] = S8;
	this->m[mp(2, '/')] = S9;
	this->m[mp(2, '$')] = R3;

	this->m[mp(3, '+')] = R6;
	this->m[mp(3, '-')] = R6;
	this->m[mp(3, '*')] = R6;
	this->m[mp(3, '/')] = R6;
	this->m[mp(3, '$')] = R6;

	this->m[mp(4, '(')] = S13;
	this->m[mp(4, NUM)] = S14;
	this->m[mp(4, 'E')] = 10;
	this->m[mp(4, 'T')] = 11;
	this->m[mp(4, 'F')] = 12;

	this->m[mp(5, '+')] = R8;
	this->m[mp(5, '-')] = R8;
	this->m[mp(5, '*')] = R8;
	this->m[mp(5, '/')] = R8;
	this->m[mp(5, '$')] = R8;

	this->m[mp(6, '(')] = S4;
	this->m[mp(6, NUM)] = S5;
	this->m[mp(6, 'T')] = 15;
	this->m[mp(6, 'F')] = 3;

	this->m[mp(7, '(')] = S4;
	this->m[mp(7, NUM)] = S5;
	this->m[mp(7, 'T')] = 16;
	this->m[mp(7, 'F')] = 3;

	this->m[mp(8, '(')] = S4;
	this->m[mp(8, NUM)] = S5;
	this->m[mp(8, 'F')] = 17;

	this->m[mp(8, '(')] = S4;
	this->m[mp(8, NUM)] = S5;
	this->m[mp(8, 'F')] = 17;

	this->m[mp(9, '(')] = S4;
	this->m[mp(9, NUM)] = S5;
	this->m[mp(9, 'F')] = 18;

	this->m[mp(10, '+')] = S20;
	this->m[mp(10, '-')] = S21;
	this->m[mp(10, ')')] = S19;

	this->m[mp(11, '+')] = R3;
	this->m[mp(11, '-')] = R3;
	this->m[mp(11, '*')] = S22;
	this->m[mp(11, '/')] = S23;
	this->m[mp(11, ')')] = R3;

	this->m[mp(12, '+')] = R6;
	this->m[mp(12, '-')] = R6;
	this->m[mp(12, '*')] = R6;
	this->m[mp(12, '/')] = R6;
	this->m[mp(12, ')')] = R6;

	this->m[mp(13, '(')] = S13;
	this->m[mp(13, NUM)] = S14;
	this->m[mp(13, 'E')] = 24;
	this->m[mp(13, 'T')] = 11;
	this->m[mp(13, 'F')] = 12;

	this->m[mp(14, '+')] = R8;
	this->m[mp(14, '-')] = R8;
	this->m[mp(14, '*')] = R8;
	this->m[mp(14, '/')] = R8;
	this->m[mp(14, ')')] = R8;

	this->m[mp(15, '+')] = R1;
	this->m[mp(15, '-')] = R1;
	this->m[mp(15, '*')] = S8;
	this->m[mp(15, '/')] = S9;
	this->m[mp(15, '$')] = R1;

	this->m[mp(16, '+')] = R2;
	this->m[mp(16, '-')] = R2;
	this->m[mp(16, '*')] = S8;
	this->m[mp(16, '/')] = S9;
	this->m[mp(16, '$')] = R2;

	this->m[mp(17, '+')] = R4;
	this->m[mp(17, '-')] = R4;
	this->m[mp(17, '*')] = R4;
	this->m[mp(17, '/')] = R4;
	this->m[mp(17, '$')] = R4;

	this->m[mp(18, '+')] = R5;
	this->m[mp(18, '-')] = R5;
	this->m[mp(18, '*')] = R5;
	this->m[mp(18, '/')] = R5;
	this->m[mp(18, '$')] = R5;

	this->m[mp(19, '+')] = R7;
	this->m[mp(19, '-')] = R7;
	this->m[mp(19, '*')] = R7;
	this->m[mp(19, '/')] = R7;
	this->m[mp(19, '$')] = R7;

	this->m[mp(20, '(')] = S13;
	this->m[mp(20, NUM)] = S14;
	this->m[mp(20, 'T')] = 25;
	this->m[mp(20, 'F')] = 12;

	this->m[mp(21, '(')] = S13;
	this->m[mp(21, NUM)] = S14;
	this->m[mp(21, 'T')] = 26;
	this->m[mp(21, 'F')] = 12;

	this->m[mp(22, '(')] = S13;
	this->m[mp(22, NUM)] = S14;
	this->m[mp(22, 'F')] = 27;

	this->m[mp(23, '(')] = S13;
	this->m[mp(23, NUM)] = S14;
	this->m[mp(23, 'F')] = 28;

	this->m[mp(24, '+')] = S20;
	this->m[mp(24, '-')] = S21;
	this->m[mp(24, ')')] = S29;

	this->m[mp(25, '+')] = R1;
	this->m[mp(25, '-')] = R1;
	this->m[mp(25, '*')] = S22;
	this->m[mp(25, '/')] = S23;
	this->m[mp(25, ')')] = R1;

	this->m[mp(26, '+')] = R2;
	this->m[mp(26, '-')] = R2;
	this->m[mp(26, '*')] = S22;
	this->m[mp(26, '/')] = S23;
	this->m[mp(26, ')')] = R2;

	this->m[mp(27, '+')] = R4;
	this->m[mp(27, '-')] = R4;
	this->m[mp(27, '*')] = R4;
	this->m[mp(27, '/')] = R4;
	this->m[mp(27, ')')] = R4;

	this->m[mp(28, '+')] = R5;
	this->m[mp(28, '-')] = R5;
	this->m[mp(28, '*')] = R5;
	this->m[mp(28, '/')] = R5;
	this->m[mp(28, ')')] = R5;

	this->m[mp(29, '+')] = R7;
	this->m[mp(29, '-')] = R7;
	this->m[mp(29, '*')] = R7;
	this->m[mp(29, '/')] = R7;
	this->m[mp(29, ')')] = R7;

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
void Parser::parse() {
	//������
	int step = 1;
	Parser::init_map();
	//S0Ϊ0��ջ
	l1.push_back(0);
	int top = 0;
	char a = '.';
	do {
		printf("%5d       ", step);
		//��ʼ��ջ����Ŀǰ����ȡ�ķ���
		if (!l1.empty())
			top = l1.back();
		else
			printf("l1�Ѿ�Ϊ�ա�\n");
		a = CC[ip];
		//tΪ��������
		//��������֣�num���ս������Ӧ��ֱ�������ֱ���make_pair
		//��Ӧ����NUM��make_pair
		int t = 0;
		if(a>='0' && a<='9')
			t = m[mp(top, NUM)];
		else
			t = m[mp(top, a)];
		if (isShift(t)) {
			l1.push_back(t-200);
			l2.push_back(a);
			ip += 1;
			//�������t
			step++;
			output_stack();
			output_CC();
			printf("%s", print_CC);
			puts("");
		}
		else if (isReduce(t)) {
			//����|beta|������
			for (int i = 0; i < beta_query[t]; i++) {
				if (!l1.empty())
					l1.pop_back();
				else
					printf("l1�ѿա�\n");
				if (!l2.empty())
					l2.pop_back();
				else
					printf("l2�ѿա�\n");
			}
			int ss = l1.back();
			char A = R_query[t][0];
			int Goto = m[mp(ss, A)];
			l1.push_back(Goto);
			l2.push_back(A);
			//�������ʽt
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
			printf("�������̳�����\n");
		}
	} while (1);
}

void Parser::output_stack() {
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
void Parser::output_CC() {
	memset(print_CC, 0, sizeof(print_CC));
	for (int i = ip; i < strlen(CC); i++) {
		if (i == ip)
			print_CC[0] = CC[i];
		else
			print_CC[strlen(print_CC)] = CC[i];
	}
}
