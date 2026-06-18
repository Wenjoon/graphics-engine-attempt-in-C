#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//POINTS
//will be converted into vectors for math stuff later, though centering a point so i can make life easy
typedef struct point {
    float ent[3];
} pt;
//centering protocol, assume center point is shifted to (0,0,0)
vec centPos(pt* c, pt* A) {
    vec new;
    for (int i = 0; i < 3; i++) {
        new.ent[i] = A->ent[i] - c->ent[i];
    }
    return new;
}
//SCENES
//size represents the power of 2 of the size of the pointer to the array of pointers, which should start at 1
typedef struct scene {
    pt*** pts;
    int used;
    int size;
} scn;
//use after declaring a scene to initialize it
void scnInit(scn* A) {
    A->size = 1;
    A->used = 0;
    *(A->pts) = malloc(sizeof(pt*));
}
//use to add points to the scene. 
void scnAdd(scn* A, pt* p) {
    if (A->used == pow(2, A->size)) {
        A->size += 1;
        *(A->pts) = realloc(A->pts, sizeof(pt*) * pow(2, A->size));
    }
    *(A->pts)[A->used] = p;
    A->used += 1;
}
//CAMERAS
//resolution is the number of pixels per length 1, size is the height and width of the camera, distance is the modifier to the vanishing point
typedef struct camera {
    int res;
    float size[2];
    int dist;
    vec basis[3];
    scn scene;
} cam;

void camInit(cam* A) {
    //to init, define rese, size, dist, basis 0 (direction), and scene
    A->basis[0] = vecnorm(&A->basis[0]);
    vec sideBase = {-(A->basis[0]).ent[1], (A->basis[0]).ent[0], 0};
    vec topBase = veccrossprod(&(A->basis[0]), &sideBase);
    A->basis[1] = sideBase, A->basis[2;;] = topBase;
}

//Camera point (for rendering)
//Run across points in the scene, return null if not in size and return a point if in scope. Leave room for adjusting brightness based on distance/lighting
typedef struct cameraPoint {
    float ent[2];
    //float bright;
} campt;

campt ptcheck(pt* A, cam* camera) {
    vec placeholder = vecproj(A, &camera->dir);
    float zdist = veclen(&placeholder);
    placeholder = vecproj(A, &camera->basis[0]);
    float xdist = veclen(&placeholder);
    placeholder = vecproj(A, &camera->basis[1]);
    float ydist = veclen(&placeholder);
    campt new = {xdist / (zdist / camera->dist), ydist / (zdist / camera->dist)};
    return new;
}

int main() {

}
