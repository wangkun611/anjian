/* File : example.i */
%module(directors="1") anjian
%feature("director") anjian;



%{
#include "anjian.h"
#include "keyboard.h"
#include "mouse.h"
#include "window.h"
%}


/* Let's just grab the original header file here */
typedef struct {
    long  x;
    long  y;
}POINT;

typedef struct {
    long    left;
    long    top;
    long    right;
    long    bottom;
} RECT;

%nodefaultctor CAnJian;

%include <std_string.i>
%include "anjian.h"
%include "keyboard.h"
%include "mouse.h"
%include "window.h"

%include "std_vector.i"

namespace std {
   %template(vectorw) vector<CAJWindow>;
};