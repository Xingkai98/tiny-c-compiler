#include "lexer.h"

//�����﷨��������
char cc[100];

//��������С
const int BUFFER_SIZE = 1000;
//����������
const int LEFT = 1;
//����������
const int RIGHT = 2;
//�ؼ��ָ���
const int KW_NUM = 66;
//ÿ�����ʣ������ؼ��ֺ��û��Զ��������󳤶ȣ�
const int MAX_LEN = 30;
//�����ɹؼ��ֺͱ�������
const int TBL_LEN = 100;

//�ؼ��ʱ�
char KW_LIS[TBL_LEN][MAX_LEN] = {
	"asm",         "do",              "if",                "return",           "try",
	"auto",        "double",          "inline",            "short",            "typedef",
	"bool",        "dynamic_cast",    "int",               "signed",           "typeid",
	"break",       "else",            "long",              "static",           "union",
	"case",        "enum",            "mutable",           "static_cast",      "unsigned",
	"catch",       "explicit",        "namespace",         "struct",           "using",
	"char",        "export",          "new",               "switch",           "virtual",
	"class",       "extern",          "register",          "sizeof",           "typename",
	"const",       "false",           "operator",          "template",         "void",
	"const_cast",  "float",           "private",           "this",             "volatile",
	"continue",    "for",             "protected",         "throw",            "wchar_t",
	"default",     "friend",          "public",            "true",             "while",
	"delete",      "goto",            "reinterpret_cast",
	"include",     "stdio",           "string",
};
//�û��ؼ��ֱ�
char user_table[TBL_LEN][MAX_LEN];

//��С�Ƚϲ���������
const int LT = 1;
const int LE = 2;
const int EQ = 3;
const int NE = 4;
const int GT = 5;
const int GE = 6;
//relop��ָ��С�ȽϷ�
const int relop = 1;
//assign_op��ָ��ֵ����
const int assign_op = 2;
//iskey��ָΪ�ؼ���
const int iskey = 3;
//ID��ָΪ�û��Զ���ı����Ǻ�
const int ID = 4;
//NUM��ָ����
const int NUM = 5;

//����Ϊ������
//1Ϊ�����������ֿ�ͷ
const int ERROR_VAR = 1;
//δ֪����
const int ERROR_UNK = 2;
//С���������δ֪����
const int ERROR_DIG = 3;

//���ż���
int BIG_CLO;
int MED_CLO;
int SML_CLO;

char a;
int state;
char C;

//������
char buffer_l[BUFFER_SIZE];
char buffer_r[BUFFER_SIZE];
//��ǰ����
char token[MAX_LEN];
//ָ��õ��ʵĿ�ʼ��
char* lexemebegin;
//��ǰ̽
char* forward;



void load_buffer(int index) {
	if (index == LEFT) {
		a = getchar();
		while (a != EOF && strlen(buffer_l) <= BUFFER_SIZE) {
			buffer_l[strlen(buffer_l)] = a;
			a = getchar();
		}
	}
	else if (index == RIGHT) {
		a = getchar();
		while (a != EOF && strlen(buffer_r) <= BUFFER_SIZE) {
			buffer_r[strlen(buffer_r)] = a;
			a = getchar();
		}
	}
	else {
		printf("Please specify a valid buffer index.\n");
	}
}

void print_buf(int index) {
	if (index == LEFT) {
		printf("%s\n", buffer_l);
	}
	else if (index == RIGHT) {
		printf("%s\n", buffer_r);
	}
	else {
		printf("Please specify a valid buffer index.\n");
	}
}

//��ʼ��

void default_init_for_parser() {
	memset(cc, 0, sizeof(cc));
	lexemebegin = buffer_l;
	forward = buffer_l;
	buffer_l[BUFFER_SIZE - 1] = EOF;
	buffer_r[BUFFER_SIZE - 1] = EOF;
	const char* s = " 3+3-4*6";
	//const char* ss = "3-4+6*7";
	strcpy(buffer_l, s);
	buffer_l[strlen(buffer_l)] = EOF;
	printf("%s\n", s);
}
void get_char() {
	C = *forward;
	forward += 1;
}
//ȥ�ո�
void get_nbc() {
	while (C == ' ') {
		get_char();
	}
}
//�ַ�����token
void cat() {
	token[strlen(token)] = C;
}
int letter() {
	if (C >= 'a' && C <= 'z') {
		return 1;
	}
	else if (C >= 'A' && C <= 'Z') {
		return 1;
	}
	else {
		return 0;
	}
}
int digit() {
	if (C >= '0' && C <= '9') {
		return 1;
	}
	else return 0;
}
void retract() {
	forward -= 1;
}
//�ж��Ƿ�Ϊ�ؼ���
int reserve() {
	for (int i = 0; i <= KW_NUM - 1; i++) {
		if (strcmp(token, KW_LIS[i]) == 0) {
			return i;
		}
	}
	return -1;
}
//string-->int
int stoi(char* token) {
	int t = atoi(token);
	if (t > 0) {
		return t;
	}
	else {
		return -1;
	}
}
//string-->double
double stof(char* token) {
	double t = atof(token);
	if (t > 0) {
		return t;
	}
	else {
		return -1;
	}
}
//�û��Զ���Ǻ�
int table_insert() {
	for (int i = 0; i < TBL_LEN; i++) {
		if (strlen(user_table[i]) == 0) {
			strcpy(user_table[i], token);
			return i;
		}
	}
	printf("The table is full.\n");
	return -1;
}
//���
void return_t(int type, int value) {
	if (type == iskey) {
		printf("<  %s  ,  �����ؼ���  >\n", KW_LIS[value]);
	}
	else if (type == relop) {
		printf("<  ");
		switch (value) {
		case LT:printf("<"); break;
		case LE:printf("<="); break;
		case EQ:printf("="); break;
		case NE:printf("<>"); break;
		case GT:printf(">"); break;
		case GE:printf(">="); break;
		}
		printf("  ,  �����  >\n");
	}
	else if (type == assign_op) {
		if (value == -1) {
			printf("<  ==  ,  �����  >\n");
		}
		else if (value == -2) {
			printf("<  +=  ,  �����  >\n");
		}
		else {
			printf("<  -=  ,  �����  >\n");
		}

	}
	else if (type == ID) {
		printf("<  %s  ,  �û��Զ������  >\n", user_table[value]);
	}
	else if (type == NUM) {
		cc[strlen(cc)] = '0' + value;
		printf("<  %d  ,  ������  >\n", value);
	}
	else if (value == -1 && type > 3) {
		cc[strlen(cc)] = (char)type;
		printf("<  %c  ,  ����  >\n", type);
	}
	else {
		printf("���󷵻�ֵ��%d %d.\n", type, value);
	}
}
//���������
void return_t_double(int type, double value) {
	printf("<  %.4f  ,  ������  >\n", value);
}
//������
void error(int a) {
	if (a == ERROR_UNK) {
		//���з��ʹ���������������������
		if (C == '\n' || C == 0 || C == '\t') {
			return;
		}
		else {
			printf("<  �����������δ֪�ַ���  >\n");
		}
	}
	else if (a == ERROR_VAR) {
		printf("<  ������󣡱��������������ֿ�ͷ��  >\n");
	}
	else if (a == ERROR_DIG) {
		printf("<  ������󣡲��Ϸ��ĸ�������  >\n");
	}
	system("pause");
	exit(0);
}
//��Ϊ̽�������ʵ��ַ����˺�
void set_to_next_word() {
	if (forward == buffer_l || forward == buffer_r) {

	}
	else {
		forward += 1;
		lexemebegin = forward;
	}
}
//������
void lex() {
	state = 0;
	do {

		if (forward - buffer_l >= BUFFER_SIZE) {
			printf("buffer��ȡ����.\n");
			return;
		}
		switch (state) {
		case 0:
			set_to_next_word();
			memset(token, '\0', sizeof(token));
			//printf("begin:%d,forward:%d\n", lexemebegin, forward);
			get_char();
			get_nbc();
			switch (C) {
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':state = 1; break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				//����ʶ������
			case '9':state = 2; break;
				//<��<=
			case '<':state = 8; break;
				//>��>=
			case '>':state = 9; break;
			case '=':state = 10; break;
			case '+':state = 14; break;
			case '-':state = 15; break;
				//ע��
			case '/':state = 11; break;
				//case '=':state = 0; return_t('=', -1); break;
			case '*':state = 0; retract(); return_t('*', -1); break;
			case '.':state = 0; retract(); return_t('.', -1); break;
			case '(':SML_CLO++; state = 0; retract(); return_t('(', -1); break;
			case ')':SML_CLO--; state = 0; retract(); return_t(')', -1); break;
				//;����retract����Ϊ;����һ�㶼�ǻ��з�"\n"��ֱ���̵�
			case ';':state = 0; return_t(';', -1); break;
			case '#':state = 0; retract(); return_t('#', -1); break;
			case '\\':state = 0; retract(); return_t('\\', -1); break;
			case '\'':state = 0; retract(); return_t('\'', -1); break;
			case '\"':state = 0; retract(); return_t('\"', -1); break;
			case '[':MED_CLO++; state = 0; retract(); return_t('[', -1); break;
			case ']':MED_CLO--; state = 0; retract(); return_t(']', -1); break;
			case '{':BIG_CLO++; retract(); state = 0; return_t('{', -1); break;
			case '}':BIG_CLO--; retract(); state = 0; return_t('}', -1); break;
			default: state = 13; break;
			};
			break;
			//ʶ������ĸ���ɵĵ���
		case 1:
			cat();
			get_char();
			if (letter() || digit()) {
				state = 1;
			}
			else {
				retract();
				retract();
				state = 0;
				int key = reserve();
				if (key != -1) {
					return_t(iskey, key);
				}
				else {
					for (int i = 0; i < TBL_LEN; i++) {
						if (strlen(user_table[i]) == 0) {
							strcpy(user_table[i], token);
							return_t(ID, i);
							break;
						}
					}
				}
			}
			break;
			//ʶ������
		case 2:
			cat();
			get_char();
			switch (C) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':state = 2; break;
			case '.':state = 3; break;
			case 'E':
			case 'e':state = 5; break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':error(ERROR_VAR);  retract(); state = 0; break;
			default:
				retract();
				//��Ϊ��ʼʱset_to_next_word��������forward��һ
				//�����ڵ�ǰforward��ָ�ַ��Ѿ�����Ҫ����ʶ����ַ�
				//�����ȼ�һ�ټ�һ
				retract();
				state = 0;
				return_t(NUM, stoi(token));
				break;
			}
			break;
			//ʶ��С��
		case 3:
			cat();
			get_char();
			if (digit())
				state = 4;
			else {
				error(ERROR_DIG);
				state = 0;
			}
			break;
			//ʶ���ѧ������
		case 4:
			cat();
			get_char();
			switch (C) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':state = 4; break;
			case 'E':state = 5; break;
			default:
				retract();
				retract();
				state = 0;
				return_t_double(NUM, stof(token));
				break;
			}
			break;
		case 5:
			cat();
			get_char();
			switch (C) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':state = 7; break;
			case '-':state = 6; break;
			default:
				retract();
				retract();
				error(0);
				state = 0;
				break;
			}
			break;
		case 6:
			cat();
			get_char();
			if (digit())
				state = 7;
			else {
				retract();
				error(0);
				state = 0;
			}
			break;
		case 7:
			cat();
			get_char();
			if (digit())
				state = 7;
			break;
			//ʶ��<��<=
		case 8:
			cat();
			get_char();
			switch (C) {
			case '=':
				cat(); state = 0; return_t(relop, LE); break;
			case '>':
				cat(); state = 0; return_t(relop, NE); break;
			default:
				retract();
				state = 0;
				return_t(relop, LT);
				break;
			}
			break;
			//ʶ��>��>=
		case 9:
			cat();
			get_char();
			if (C == '=') {
				cat();
				state = 0;
				return_t(relop, GE);
			}
			else {
				retract();
				state = 0;
				return_t(relop, GT);
			}
			break;
			//ʶ��==
		case 10:
			cat();
			get_char();
			if (C == '=') {
				cat();
				//retract
				retract();
				state = 0;
				return_t(assign_op, -1);
			}
			else {
				//retract
				retract();
				retract();
				state = 0;
				return_t('=', -1);
			}
			break;
			//ʶ������ע�ͣ���Ϊ��������ת��16
		case 11:
			cat();
			get_char();
			if (C == '*') {
				//����ע��
				state = 12;
			}
			else if (C == '/') {
				//����ע��
				state = 16;
			}
			else {
				retract();
				retract();
				state = 0;
				//����
				return_t('/', -1);
			}
			break;
		case 12:
			get_char();
			while (C != '*')
				get_char();
			get_char();
			if (C == '/') {
				retract();
				state = 0;
			}
			else
				state = 12;
			break;
			//δ֪����
		case 13:
			error(ERROR_UNK);
			retract();
			state = 0;
			break;
			//ʶ��+=
		case 14:
			cat();
			get_char();
			if (C == '=') {
				cat();
				//retract
				retract();
				state = 0;
				return_t(assign_op, -2);
			}
			else {
				//retract
				retract();
				retract();
				state = 0;
				return_t('+', -1);
			}
			break;
			//ʶ��-=
		case 15:
			cat();
			get_char();
			if (C == '=') {
				cat();
				//retract
				retract();
				state = 0;
				return_t(assign_op, -3);
			}
			else {
				//retract
				retract();
				retract();
				state = 0;
				return_t('-', -1);
			}
			break;
			//ʶ��//����ע��
		case 16:
			while (C != '\n')
				get_char();
			retract();
			state = 0;
			break;
		}
	} while (C != EOF);
	cc[strlen(cc)] = '$';
}
void check_closure() {
	if (SML_CLO != 0) {
		printf("<  ������ʾ��С����������ƥ�䣡  >\n");
	}
	if (MED_CLO != 0) {
		printf("<  ������ʾ��������������ƥ�䣡  >\n");
	}
	if (BIG_CLO != 0) {
		printf("<  ������ʾ��������������ƥ�䣡  >\n");
	}
}
