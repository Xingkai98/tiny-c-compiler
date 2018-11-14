#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//缓存区大小
const int BUFFER_SIZE = 1000;
//缓存区左右
const int LEFT = 1;
//缓存区左右
const int RIGHT = 2;
//关键字个数
const int KW_NUM = 66;
//每个单词（包括关键字和用户自定义变量最大长度）
const int MAX_LEN = 30;
//可容纳关键字和变量多少
const int TBL_LEN = 100;

//关键词表
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
//用户关键字表
char user_table[TBL_LEN][MAX_LEN];

//大小比较操作符代号
const int LT = 1;
const int LE = 2;
const int EQ = 3;
const int NE = 4;
const int GT = 5;
const int GE = 6;
//relop代指大小比较符
const int relop = 1;
//assign_op代指赋值符号
const int assign_op = 2;
//iskey代指为关键字
const int iskey = 3;
//ID代指为用户自定义的变量记号
const int ID = 4;
//NUM代指数字
const int NUM = 5;

//以下为错误码
//1为变量名以数字开头
const int ERROR_VAR = 1;
//未知符号
const int ERROR_UNK = 2;
//小数点后不能有未知符号
const int ERROR_DIG = 3;

//括号计数
int BIG_CLO;
int MED_CLO;
int SML_CLO;

char a;
int state;
char C;

//缓存区
char buffer_l[BUFFER_SIZE];
char buffer_r[BUFFER_SIZE];
//当前单词
char token[MAX_LEN];
//指向该单词的开始处
char* lexemebegin;
//向前探
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

//初始化
void init() {
	lexemebegin = buffer_l;
	forward = buffer_l;
	buffer_l[BUFFER_SIZE - 1] = EOF;
	buffer_r[BUFFER_SIZE - 1] = EOF;
	load_buffer(LEFT);
}

void get_char() {
	C = *forward;
	forward += 1;
}
//去空格
void get_nbc() {
	while (C == ' ') {
		get_char();
	}
}
//字符存入token
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
//判断是否为关键字
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
//用户自定义记号
int table_insert() {
	for (int i = 0; i < TBL_LEN; i++) {
		if (strlen(user_table[i]) == 0) {
			strcpy_s(user_table[i], token);
			return i;
		}
	}
	printf("The table is full.\n");
	return -1;
}
//输出
void return_t(int type, int value) {
	if (type == iskey) {
		printf("<  %s  ,  保留关键字  >\n", KW_LIS[value]);
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
		printf("  ,  运算符  >\n");
	}
	else if (type == assign_op) {
		if (value == -1) {
			printf("<  ==  ,  运算符  >\n");
		}
		else if (value == -2) {
			printf("<  +=  ,  运算符  >\n");
		}
		else {
			printf("<  -=  ,  运算符  >\n");
		}
		
	}
	else if (type == ID) {
		printf("<  %s  ,  用户自定义符号  >\n", user_table[value]);
	}
	else if (type == NUM) {
		printf("<  %d  ,  整型数  >\n", value);
	}
	else if (value == -1 && type > 3) {
		printf("<  %c  ,  符号  >\n", type);
	}
	else {
		printf("错误返回值：%d %d.\n", type, value);
	}
}
//浮点数输出
void return_t_double(int type, double value) {
	printf("<  %.4f  ,  浮点数  >\n",value);
}
//错误处理
void error(int a) {
	if (a == ERROR_UNK) {
		//换行符和代码结束这两种情况都忽略
		if (C == '\n' || C==0 || C=='\t') {
			return;
		}
		else {
			printf("<  编译错误！遇到未知字符！  >\n");
		}
	}
	else if (a == ERROR_VAR) {
		printf("<  编译错误！变量名不能以数字开头！  >\n");
	}
	else if (a == ERROR_DIG) {
		printf("<  编译错误！不合法的浮点数！  >\n");
	}
	system("pause");
	exit(0);
}
//因为探到不合适的字符会退后
void set_to_next_word() {
	if (forward == buffer_l || forward == buffer_r) {

	}
	else {
		forward += 1;
		lexemebegin = forward;
	}
}
//主程序
void lex() {
	state = 0;
	do {

			if (forward - buffer_l >= BUFFER_SIZE) {
				printf("buffer读取结束.\n");
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
				//继续识别数字
				case '9':state = 2; break;
				//<和<=
				case '<':state = 8; break;
				//>和>=
				case '>':state = 9; break;
				case '=':state = 10; break;
				case '+':state = 14; break;
				case '-':state = 15; break;
				//注释
				case '/':state = 11; break;
				//case '=':state = 0; return_t('=', -1); break;
				case '*':state = 0; retract(); return_t('*', -1); break;
				case '.':state = 0; retract(); return_t('.', -1); break;
				case '(':SML_CLO++; state = 0; retract(); return_t('(', -1); break;
				case ')':SML_CLO--; state = 0; retract(); return_t(')', -1); break;
				//;后不用retract，因为;后面一般都是换行符"\n"，直接吞掉
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
			//识别由字母构成的单词
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
								strcpy_s(user_table[i], token);
								return_t(ID, i);
								break;
							}
						}
					}
				}
				break;
			//识别数字
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
					//因为开始时set_to_next_word函数会让forward加一
					//而现在当前forward所指字符已经是需要重新识别的字符
					//所以先减一再加一
					retract();
					state = 0;
					return_t(NUM, stoi(token));
					break;
				}
				break;
			//识别小数
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
			//识别科学记数法
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
			//识别<和<=
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
			//识别>和>=
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
			//识别==
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
			//识别良种注释，若为单行则跳转至16
			case 11:
				cat();
				get_char();
				if (C == '*') {
					//多行注释
					state = 12;
				}
				else if (C == '/') {
					//单行注释
					state = 16;
				}
				else {
					retract();
					retract();
					state = 0;
					//除法
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
			//未知错误
			case 13:
				error(ERROR_UNK);
				retract();
				state = 0;
				break;
			//识别+=
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
			//识别-=
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
			//识别“//”型注释
			case 16:
				while (C != '\n')
					get_char();
				retract();
				state = 0;
				break;
			}
	} while (C != EOF);
}
void check_closure() {
	if (SML_CLO != 0) {
		printf("<  错误提示！小括号数量不匹配！  >\n");
	}
	if (MED_CLO != 0) {
		printf("<  错误提示！中括号数量不匹配！  >\n");
	}
	if (BIG_CLO != 0) {
		printf("<  错误提示！大括号数量不匹配！  >\n");
	}
}
int main() {
	init();
	print_buf(LEFT);
	lex();
	check_closure();
	system("pause");
	return 0;
}
