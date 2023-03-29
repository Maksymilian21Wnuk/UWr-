/*
 * Wnuk Maksymilian
 * PO Lista 1 zadanie 2
 * gcc zad2.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define new_u malloc(sizeof(Ulamek))

typedef struct u {
    int licznik;
    int mianownik;
} Ulamek;


int nwd(int a, int b){
    while (a != b){
        if (a > b){
            a -= b;
        }
        else{
             b-= a;
        }
    }
    return a;
}

void skroc(Ulamek *u){
    int nwd_res = nwd(u->licznik, u->mianownik);
    while(nwd_res != 1){
        u->licznik /= nwd_res;
        u->mianownik /= nwd_res;    
        nwd_res = nwd(u->licznik, u->mianownik);
    }
}


Ulamek *nowy_ulamek(int num, int denom){
    if (denom == 0){
        fprintf(stdout, "%s", "0 denom, error, exiting program.\n");
        exit(EXIT_FAILURE);
    }
    Ulamek *u = new_u;
    u->licznik = num;
    u->mianownik = denom;
    skroc(u);

    return u;
}

void show(Ulamek *u){
    printf("%d/%d\n", u->licznik, u->mianownik);
}


// subtraction and addition functions

Ulamek *find_nww(Ulamek *u1, Ulamek *u2, char sign){
    Ulamek *u3 = new_u;
    int nww = (u1->mianownik * u2->mianownik) / nwd(u1->mianownik, u2->mianownik);

    int u1_new = (nww / u1->mianownik) * u1->licznik;
    int u2_new =  (nww / u2->mianownik) * u2->licznik;

    u3->licznik = (sign == '+') ? u1_new + u2_new : u1_new - u2_new;
    u3->mianownik = nww;
    
    skroc(u3);
    return u3;

}


Ulamek *add(Ulamek *u1, Ulamek *u2){
    return find_nww(u1, u2, '+');
}

Ulamek *sub(Ulamek *u1, Ulamek *u2){
    return find_nww(u1, u2, '-');
}

void add_second(Ulamek *u1, Ulamek *u2){
    Ulamek *u3 = find_nww(u1, u2, '+');
    memcpy(u2, u3, sizeof(Ulamek));
    free(u3);
}


void sub_second(Ulamek *u1, Ulamek *u2){
    Ulamek *u3 = find_nww(u1, u2, '-');
    memcpy(u2, u3, sizeof(Ulamek));
    free(u3);
}

// ***********************************



// multiplication and div functions
Ulamek *mult(Ulamek *u1, Ulamek *u2){
    int num, denom;
    num = u1->licznik * u2->licznik;
    denom = u1->mianownik * u2->mianownik;

    return nowy_ulamek(num, denom);
}

void mult_second(Ulamek *u1, Ulamek *u2){
    u2->licznik *= u1->licznik;
    u2->mianownik *= u1->mianownik;
    skroc(u2);
}

Ulamek *div_u(Ulamek *u1, Ulamek *u2){
    Ulamek *temp_u = nowy_ulamek(u2->mianownik, u2->licznik);
    temp_u = mult(u1, temp_u);
    return temp_u;
}

void div_second(Ulamek *u1, Ulamek *u2){
    mult_second(u1, nowy_ulamek(u2->mianownik, u2->licznik));
}

// **************





// main function for testing
int main(){
    // TEST skracania
    Ulamek *u1 = nowy_ulamek(80, 120);
    show(u1);

    Ulamek *u2 = nowy_ulamek(1, 6);
    show(u2);

    Ulamek *u3 = mult(u1, u2);
    show(u3);

    // MULT TEST
    printf("mult test: \n");
    show(u1);
    show(u2);
    show(mult(u1, u2));

    // ADD TEST
    printf("add test \n");
    show(u1);
    show(u2);
    show(add(u1, u2));

    // ADD TEST WITH MEMCPY
    printf("memory on second argument test add: \n");
    show(u1);
    show(u2);
    add_second(u1, u2);
    show(u2);

    // SUB TEST
    printf("sub test \n");
    show(u2);
    show(u3);
    show(sub(u2, u3));

    return 0;
}