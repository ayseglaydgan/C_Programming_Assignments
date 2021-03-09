/*
** hw1_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
** Programmer: Aysegul Aydogan. 190104004009
** Revision: 2021.09.03.16.59
** 
*/
/* ---- Libraries and header files which is needed*/
#include <stdio.h>
#include<math.h>
#include "hw1_lib.h"
#include "hw1_io.h"


/* ---- The Midpoint-Rule has been applied to calculate integral of 3-degree polynomial*/
double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)
{
    double sum = 0;
    for (float i = xs + (delta/2); i <= xe; i+=delta)
    {
        sum = sum + ((a0*powf(i,3) + a1*powf(i,2) + a2*(i) + a3)*delta);
    }
    return sum;
}

/* ---- The Midpoint-Rule has been applied to calculate integral of 4-degree polynomial*/
double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta)
{
    double sum = 0;
    for (float i = xs + (delta/2); i <= xe; i+=delta)
    {
        sum = sum + ((a0*powf(i,4) + a1*powf(i,3) + a2*powf(i,2) + a3*(i) + a4)*delta);
    }
    return sum;
}

/* ---- Bisection Method has been applied to find approximate root of 3-degree polynomial*/
double root3(double a0, double a1, double a2, double a3, double xs, double xe)
{
    float tol = 0.0001;
    double func_xs = a0*powf(xs,3) + a1*powf(xs,2) + a2*(xs) + a3;
    double func_xe = a0*powf(xe,3) + a1*powf(xe,2) + a2*(xe) + a3;
    double mid = (xe + xs) / 2;
    double func_mid = xs;
    while ((xe - xs) >= tol)
    {
        mid = (xe + xs) / 2;
        func_mid = a0*powf(mid,3) + a1*powf(mid,2) + a2*(mid) + a3;
        if(func_mid == 0.0)
        {
            break;
        }
        else if(func_mid*func_xs < 0)
        {
            xe = mid;
        }
        else
        {
            xs = mid;
        }
    }
    
    return mid;
}

/* ---- Bisection Method has been applied to find approximate root of 4-degree polynomial*/
double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe)
{
    float tol = 0.0001;
    double func_xs = a0*powf(xs,4) + a1*powf(xs,3) + a2*powf(xs,2) + a3*(xs) + a4;
    double func_xe = a0*powf(xe,4) + a1*powf(xe,3) + a2*powf(xe,2) + a3*(xe) + a4;
    double mid = (xe + xs) / 2;
    double func_mid = xs;
    while ((xe - xs) >= tol)
    {
        mid = (xe + xs) / 2;
        func_mid = a0*powf(mid,4) + a1*powf(mid,3) + a2*powf(mid,2) + a3*(mid) + a4;
        if(func_mid == 0.0)
        {
            break;
        }
        else if(func_mid*func_xs < 0)
        {
            xe = mid;
        }
        else
        {
            xs = mid;
        }
    }
    
    return mid;
}

