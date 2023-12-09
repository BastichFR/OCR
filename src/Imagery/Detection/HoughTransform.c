#include "Imagery/Detection/HoughTransform.h"


/// @brief an image
/// @param image The image to black and white

LinkedList houghtransform(Image *image, Image *copy,
                          double *max_Theta)
{
    
    const double width = copy->width, height = copy->height;
    const double diagonal = sqrt(width * width + height * height);

    const double maxTheta = 180.0, minTheta = 0.0;
    const double maxRho = diagonal, minRho = -diagonal;
    const double nbRho = 2 * diagonal, nbTheta = nbRho;

    double rhoStep = (maxRho - minRho) / nbRho;
    double *arrayRhos = calloc(nbRho + 1, sizeof(double));
    int index = 0;
    for (double val = minRho; val <= maxRho && index < nbTheta;
         val += rhoStep, index++)
    {
        arrayRhos[index] = val;
    }

    double step = (maxTheta - minTheta) / nbTheta;
    double *arrayThetas = calloc(nbTheta + 1, sizeof(double));
    index = 0;
    for (double val = minTheta; val <= maxTheta && index < nbTheta;
         val += step, index++)
    {
        arrayThetas[index] = val;
    }

    double *saveCos = calloc(nbTheta + 1, sizeof(double));
    double *saveSin = calloc(nbTheta + 1, sizeof(double));
    for (int theta = 0; theta < nbTheta; theta++)
    {
        arrayThetas[theta] = degrees_ToRadians(arrayThetas[theta]);

        saveCos[theta] = cos(arrayThetas[theta]);
        saveSin[theta] = sin(arrayThetas[theta]);
    }

    Matrix* accumulator = createMatrix(nbTheta + 1, nbRho + 1);


    unsigned int m = 0;
    double rho;
    int croppedRho;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (image->pixels[x][y].red == 255)
            {
                for (int theta = 0; theta <= nbTheta; theta++)
                {
                    rho = x * saveCos[theta] + y * saveSin[theta];
                    croppedRho = rho + diagonal;
                    accumulator->data[croppedRho][theta]++;
                    if (accumulator->data[croppedRho][theta] > m)
                    {
                        m = accumulator->data[croppedRho][theta];
                    }
                }
            }
        }
    }

    free(saveCos);
    free(saveSin);

    int lineThreshold = m * 0.4;

    LinkedList Lines = { NULL, NULL, 0 };

    double tempMaxTheta = 0.0;
    unsigned int histogram[181] = { 0 };
    unsigned int rounded_angle;

    int prev = accumulator->data[0][0];
    int prev_theta = 0, prev_rho = 0;
    int boolIsIncreasing = 1;

    Pixel pixel = { .red = 40, .green = 40, .blue = 200 };

    for (int theta = 0; theta <= nbTheta; theta++)
    {
        for (int rho = 0; rho <= nbRho; rho++)
        {
            int val = accumulator->data[rho][theta];

            if (val >= prev)
            {
                prev = val;
                prev_rho = rho;
                prev_theta = theta;
                boolIsIncreasing = 1;
                continue;
            }
            else if (val < prev && boolIsIncreasing)
            {
                boolIsIncreasing = 0;
            }
            else if (val < prev)
            {
                prev = val;
                prev_rho = rho;
                prev_theta = theta;
                continue;
            }

            if (val >= lineThreshold)
            {
                double r = arrayRhos[prev_rho], t = arrayThetas[prev_theta];

                if (t > tempMaxTheta)
                {
                    tempMaxTheta = t;
                    rounded_angle = (unsigned int)radian_To_Degree(t);
                    histogram[rounded_angle]++;
                }

                double c = cos(t), s = sin(t);
                Dot d0, d1, d2;

                d0.X = (int)(c * r);
                d0.Y = (int)(s * r);

                d1.X = d0.X + (int)(diagonal * (-s));
                d1.Y = d0.Y + (int)(diagonal * c);

                d2.X = d0.X - (int)(diagonal * (-s));
                d2.Y = d0.Y - (int)(diagonal * c);

                Line line;
                line.xStart = d1.X;
                line.xEnd = d2.X;
                line.yStart = d1.Y;
                line.yEnd = d2.Y;
                line.theta = t;

                draw_line(copy, width, height, &line, &pixel, 1, 1);

                void *p = Line_tovptr(line);
                append(&Lines, p);
            }
        }
    }

    free(arrayThetas);
    free(arrayRhos);
    freeMatrix(accumulator);

    LinkedList *list = &Lines;

    unsigned int angle = 0;
    for (unsigned int i = 0; i < 180; i++)
    {
        if (histogram[i] > histogram[angle])
            angle = i;
    }

    *max_Theta = degrees_ToRadians(angle);
    return *list;
}

double degrees_ToRadians(double degrees)
{
    return degrees * M_PI / 180.0;
}

double radian_To_Degree(double radian)
{
    return radian * 180.0 / M_PI;
}

void draw_line(Image *image, int w, int h, Line *line, Pixel *color,
               int thickness, int draw)
{
    int x0 = line->xStart;
    int y0 = line->yStart;

    int x1 = line->xEnd;
    int y1 = line->yEnd;

    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;

    int err = dx + dy;

    while (1)
    {
        if (0 <= x0 && x0 < w && 0 <= y0 && y0 < h)
        {
            image->pixels[x0][y0].red = color->red;
            image->pixels[x0][y0].green = color->green;
            image->pixels[x0][y0].blue = color->blue;

            if (thickness == 2)
            {
                if (0 <= (x0 + 1) && (x0 + 1) < w && 0 <= (y0 + 1)
                    && (y0 + 1) < h)
                {
                    image->pixels[x0 + 1][y0 + 1].red = color->red;
                    image->pixels[x0 + 1][y0 + 1].green = color->green;
                    image->pixels[x0 + 1][y0 + 1].blue = color->blue;
                }
                if (0 <= (x0 - 1) && (x0 - 1) < w && 0 <= (y0 - 1)
                    && (y0 - 1) < h)
                {
                    image->pixels[x0 - 1][y0 - 1].red = color->red;
                    image->pixels[x0 - 1][y0 - 1].green = color->green;
                    image->pixels[x0 - 1][y0 - 1].blue = color->blue;
                }
            }
        }

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void append(LinkedList *list, void *value)
{
    Node *node = initializeNode(value);
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
    list->length++;
}

void free_node(Node *node)
{
    node->next = NULL;
    node->prev = NULL;
    free(node->value);
    free(node);
}

void *Line_tovptr(Line line)
{
    void *p = malloc(sizeof(Line));
    if (p == NULL)
        errx(1, "Not enough memory");
    *(Line *)p = line;
    return p;
}

Node *initializeNode(void *value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
        errx(1, "Initialize Node: not enough memory");
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Getting nodes and their values
Node *get_node(LinkedList *list, size_t index)
{
    if (index >= list->length)
        return NULL;
    Node *node = list->head;
    for (; index > 0; index--)
    {
        node = node->next;
    }
    return node;
}

void *Square_tovptr(Square square)
{
    void *p = malloc(sizeof(Square));
    if (p == NULL)
        errx(1, "Not enough memory");
    *(Square *)p = square;
    return p;
}

void free_list(LinkedList *list)
{
    Node *tmp = list->head;
    while (tmp != NULL)
    {
        Node *n = tmp->next;
        free_node(tmp);
        tmp = n;
    }
}

