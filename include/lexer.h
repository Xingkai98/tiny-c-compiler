#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>

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
const int NUMBER = 5;

//����Ϊ������
//1Ϊ�����������ֿ�ͷ
const int ERROR_VAR = 1;
//δ֪����
const int ERROR_UNK = 2;
//С���������δ֪����
const int ERROR_DIG = 3;

//�ؼ��ʱ�
const char KW_LIS[TBL_LEN][MAX_LEN] = {
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

class Lexer{
    public:
        Lexer(std::string s);
        void lex();
    private:
        void load_buffer(int index);
        void print_buf(int index);
        void get_char();
        //ȥ�ո�
        void get_nbc();
        //�ַ�����token
        void cat();
        int letter();
        int digit();
        void retract();
        //�ж��Ƿ�Ϊ�ؼ���
        int reserve();
        int stoi(char* token);
        double stof(char* token);
        //�û��Զ���Ǻ�
        int table_insert();
        //���
        void return_t(int type, int value);
        //���������
        void return_t_double(int type, double value);
        //������
        void error(int a);
        //��Ϊ̽�������ʵ��ַ����˺�
        void set_to_next_word();
        //������
        void check_closure();
        //���cc����

        //�����﷨��������
        char cc[100];

        //�û��ؼ��ֱ�
        char user_table[TBL_LEN][MAX_LEN];

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
};

#endif // !LEXER_H

