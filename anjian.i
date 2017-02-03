/* File : example.i */
%module(directors="1") anjian
%feature("director") anjian;



%{
#include "anjian.h"
#include "keyboard.h"
#include "mouse.h"
%}


/* Let's just grab the original header file here */
typedef struct {
    long  x;
    long  y;
}POINT;

%nodefaultctor CAnJian;

%include "anjian.h"
%include "keyboard.h"
%include "mouse.h"
