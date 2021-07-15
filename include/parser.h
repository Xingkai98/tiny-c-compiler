#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <list>
#include <map>
#include <string>

#define mp make_pair
const char NUM = '!';
const int ACC = 0;
const int S1 = 201, S2 = 202, S3 = 203, S4 = 204, S5 = 205, S6 = 206;
const int S7 = 207, S8 = 208, S9 = 209, S10 = 210, S11 = 211, S12 = 212;
const int S13 = 213, S14 = 214, S15 = 215, S16 = 216, S17 = 217, S18 = 218;
const int S19 = 219, S20 = 220, S21 = 221, S22 = 222, S23 = 223, S24 = 224;
const int S25 = 225, S26 = 226, S27 = 227, S28 = 228, S29 = 229;
const int R1 = 301, R2 = 302, R3 = 303, R4 = 304, R5 = 305, R6 = 306, R7 = 307, R8 = 308;

bool isShift(int a);
bool isReduce(int a);

class Parser{
    public:
        Parser();
        void parse();
    private:
        void call_lexer();
        void init_map();
        void output_stack();
        void output_CC();
        //�ʷ������Ľ����������ΪCC��������
        int ip = 0;
        char cc[100];
        char CC[100];
        char print_stack[50];
        char print_CC[50];

        //״̬ջ���ַ�ջ
        std::list<int> l1;
        std::list<char> l2;

        //������
        std::map <std::pair< int, char >, int > m;
        //����ʽ�Ҳ�������ѯ
        std::map <int, int> beta_query;
        std::map <int, std::string> R_query;
};

#endif