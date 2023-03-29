
typedef enum f_types {
    SQUARE = 0,
    TRIANGLE = 1,
    CIRCLE = 2
} Fig_type;

static const char* str_table[3] = {
    "Square",
    "Triangle",
    "Circle",
};

typedef struct fig{
    Fig_type typfig;
    float x1, x2, x3;
    float y1, y2, y3;
    float x4, y4; // tylko kwadrat

    float r;  // Tylko dla koła, promień
} Figura;


Figura *new_square(float x1, float y1, float bok);
Figura *new_triangle(float x1, float y1, float bok1, float bok2);
Figura *new_circle(float x1, float y1, float r);


float pole(Figura *f);
float sumapol(Figura* f[], int size);
void przesun(Figura *f, float x, float y);
void show(Figura *f);