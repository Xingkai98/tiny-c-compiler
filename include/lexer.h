#pragma once
#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void load_buffer(int index);
void print_buf(int index);
//��ʼ��
void default_init_for_parser();
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
void lex();
void check_closure();
//���cc����

#endif // !LEXER_H

