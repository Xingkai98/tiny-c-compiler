#pragma once
#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void load_buffer(int index);
void print_buf(int index);
//初始化
void default_init_for_parser();
void get_char();
//去空格
void get_nbc();
//字符存入token
void cat();
int letter();
int digit();
void retract();
//判断是否为关键字
int reserve();
int stoi(char* token);
double stof(char* token);
//用户自定义记号
int table_insert();
//输出
void return_t(int type, int value);
//浮点数输出
void return_t_double(int type, double value);
//错误处理
void error(int a);
//因为探到不合适的字符会退后
void set_to_next_word();
//主程序
void lex();
void check_closure();
//输出cc数组

#endif // !LEXER_H

