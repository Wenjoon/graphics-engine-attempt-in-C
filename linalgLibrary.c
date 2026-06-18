#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct vector {
    float ent[3];
} vec;
void vecprint(vec* A) {
    printf("[%f, %f, %f]\n", A->ent[0], A->ent[1], A->ent[2]);
}
float veclen(vec* A) {
    return sqrtf(powf(A->ent[0], 2) + powf(A->ent[1], 2) + powf(A->ent[2], 2));
}
vec vecscale(float c, vec* A) {
    vec new;
    for (int i = 0; i < 3; i++) {
        new.ent[i] = A->ent[i] * c;
    }
    return new;
}
vec vecnorm(vec* A) {
    return vecscale(1 / veclen(A), A);
}
float vecdot(vec* A, vec* B) {
    return A->ent[0] * B->ent[0] + A->ent[1] * B->ent[1] + A->ent[2] * B->ent[2];
}
vec vecadd(vec* A, vec* B) {
    vec new;
    for (int i = 0; i < 3; i++) {
        new.ent[i] = A->ent[i] + B->ent[i];
    }
    return new;
}
vec vecproj(vec* A, vec* B) {
    //outputs projection of A onto B
    vec new;
    float mod = (vecdot(A, B)) / (vecdot(B, B));
    new = vecscale(mod, A);
    return new;
}
float det2(float a, float b, float c, float d) {
    return a*d - b*c;
}
vec veccrossprod(vec* A, vec* B) {
    vec new;
    new.ent[0] = det2(A->ent[1], A->ent[2], B->ent[1], B->ent[2]);
    new.ent[1] = det2(A->ent[2], A->ent[0], B->ent[2], B->ent[0]);
    new.ent[2] = det2(A->ent[0], A->ent[1], B->ent[0], B->ent[1]);
    return new;
}

typedef struct vecspace {
    vec basis[3];
} vspc;
vec vecbaschange(vec* A, vspc* B) {
    vec new;
    for (int i = 0; i < 3; i++) {
        vec j = vecproj(A, &B->basis[i]);
        new.ent[i] = veclen(&j);
    }
    return new;
}

typedef struct matrix {
    vec ent[3];
} mat;
void matprint(mat* A) {
    for (int row = 0; row < 3; row++) {
        vecprint(&A->ent[row]);
    }
};
mat matscale(float c, mat* A) {
    mat new;
    for (int i = 0; i < 3; i++) {
        new.ent[i] = vecscale(c, &A->ent[i]);
    }
    return new;
}
mat mattrans(mat* A) {
    mat new;
    for (int row = 0; row < 3; row++) {
        vec b = {A->ent[0].ent[row], A->ent[1].ent[row], A->ent[2].ent[row]};
        new.ent[row] = b;
    }
    return new;
}
vec mvmult(mat* M, vec* A) {
    vec new;
    for (int row = 0; row < 3; row++) {
        new.ent[row] = vecdot(&M->ent[row], A);
    }
    return new;
}
mat mmmult(mat* A, mat* B) {
    mat C;
    mat Btrans = mattrans(B);
    for (int row = 0; row < 3; row++) {
        C.ent[row] = mvmult(A, &Btrans.ent[row]);
    }
    return mattrans(&C);
}
