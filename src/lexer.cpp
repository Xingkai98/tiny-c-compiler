#include "lexer.h"
#include <iostream>
#include <string>

Lexer::Lexer(std::string s){
	memset(cc, 0, sizeof(cc));
	memset(buffer_l, 0, sizeof(buffer_l));
	memset(buffer_r, 0, sizeof(buffer_r));
	lexemebegin = buffer_l;
	forward = buffer_l;
	buffer_l[BUFFER_SIZE - 1] = EOF;
	buffer_r[BUFFER_SIZE - 1] = EOF;
	//const char* str = "int main(){int a=3;}";
	//strcpy(buffer_l, str);
	strcpy(buffer_l, s.c_str());
	//buffer_l[strlen(buffer_l)] = EOF;
	std::cout<<s.length()<<std::endl;
	buffer_l[s.length()] = EOF;
	std::cout << buffer_l << std::endl;
	std::cout << buffer_r << std::endl;
}

void Lexer::load_buffer(int index) {
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

void Lexer::print_buf(int index) {
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
void Lexer::get_char() {
	C = *forward;
	forward += 1;
}
//ȥ�ո�
void Lexer::get_nbc() {
	while (C == ' ') {
		get_char();
	}
}
//�ַ�����token
void Lexer::cat() {
	token[strlen(token)] = C;
}
int Lexer::letter() {
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
int Lexer::digit() {
	if (C >= '0' && C <= '9') {
		return 1;
	}
	else return 0;
}
void Lexer::retract() {
	forward -= 1;
}
//�ж��Ƿ�Ϊ�ؼ���
int Lexer::reserve() {
	for (int i = 0; i <= KW_NUM - 1; i++) {
		if (strcmp(token, KW_LIS[i]) == 0) {
			return i;
		}
	}
	return -1;
}
//string-->int
int Lexer::stoi(char* token) {
	int t = atoi(token);
	if (t > 0) {
		return t;
	}
	else {
		return -1;
	}
}
//string-->double
double Lexer::stof(char* token) {
	double t = atof(token);
	if (t > 0) {
		return t;
	}
	else {
		return -1;
	}
}
//�û��Զ���Ǻ�
int Lexer::table_insert() {
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
void Lexer::return_t(int type, int value) {
	if (type == iskey) {
		printf("<  %s  ,  keyword  >\n", KW_LIS[value]);
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
		printf("  ,  operator  >\n");
	}
	else if (type == assign_op) {
		if (value == -1) {
			printf("<  ==  ,  operator  >\n");
		}
		else if (value == -2) {
			printf("<  +=  ,  operator  >\n");
		}
		else {
			printf("<  -=  ,  operator  >\n");
		}

	}
	else if (type == ID) {
		printf("<  %s  ,  user-defined symbol  >\n", user_table[value]);
	}
	else if (type == NUMBER) {
		cc[strlen(cc)] = '0' + value;
		printf("<  %d  ,  integer  >\n", value);
	}
	else if (value == -1 && type > 3) {
		cc[strlen(cc)] = (char)type;
		printf("<  %c  ,  symbol  >\n", type);
	}
	else {
		printf("Error code: %d %d.\n", type, value);
	}
}
//���������
void Lexer::return_t_double(int type, double value) {
	printf("<  %.4f  ,  double  >\n", value);
}
//������
void Lexer::error(int a) {
	if (a == ERROR_UNK) {
		//���з��ʹ���������������������
		if (C == '\n' || C == 0 || C == '\t') {
			return;
		}
		else {
			printf("<  Error: Unknown characters  >\n");
		}
	}
	else if (a == ERROR_VAR) {
		printf("<  Error: Variable name cannot start with digits  >\n");
	}
	else if (a == ERROR_DIG) {
		printf("<  Error: Invalid floating-point numbers.  >\n");
	}
	system("pause");
	exit(0);
}
//��Ϊ̽�������ʵ��ַ����˺�
void Lexer::set_to_next_word() {
	if (forward == buffer_l || forward == buffer_r) {

	}
	else {
		forward += 1;
		lexemebegin = forward;
	}
}
//������
void Lexer::lex() {
	state = 0;
	do {

		if (forward - buffer_l >= BUFFER_SIZE) {
			printf("buffer read finished.\n");
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
				return_t(NUMBER, stoi(token));
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
				return_t_double(NUMBER, stof(token));
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
	//Lexer::check_closure();
}
void Lexer::check_closure() {
	if (SML_CLO != 0) {
		std::cout<<SML_CLO<<std::endl;
		printf("<  Error: 小括号不匹配  >\n");
	}
	if (MED_CLO != 0) {
		std::cout<<MED_CLO<<std::endl;
		printf("<  Error: 中括号不匹配  >\n");
	}
	if (BIG_CLO != 0) {
		std::cout<<BIG_CLO<<std::endl;
		printf("<  Error: 大括号不匹配  >\n");
	}
}
