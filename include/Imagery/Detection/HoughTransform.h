#ifndef HOUGHTRANSFORM_H
#define HOUGHTRANSFORM_H

#include "Matrix/matrix.h"
#include "Imagery/Tools/image.h"


typedef struct Node_T
{
    void *value;
    struct Node_T *next;
    struct Node_T *prev;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    size_t length;
} LinkedList;

typedef struct Dot
{
    int X;
    int Y;
} Dot;

typedef struct Line
{
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    double theta;
} Line;

typedef struct Square
{
    Line top;
    Line bottom;
    Line left;
    Line right;
} Square;

void draw_line(Image *image, int w, int h, Line *line, Pixel *color, int thickness,int draw);
double radian_To_Degree(double radian);
double degrees_ToRadians(double degrees);
void append(LinkedList *list, void *value);
LinkedList houghtransform(Image *image, Image *copy,
                          double *max_Theta);
void *Line_tovptr(Line line);
void free_node(Node *node);
void free_list(LinkedList *list);
Node *initializeNode(void *value);
Node *get_node(LinkedList *list, size_t index);
void *Square_tovptr(Square square);
#endif // HOUGHTRANSFORM_H
