#include <cmath>
#include "physics.hpp"

Physics::Physics() {}

Physics::~Physics() {}

void Physics::ReverseVelocity(int posX, int posY, float x[][SIZE], bool solid[][SIZE]) {

        if (!solid[posX][posY- 1] ){
            float temp = 0.0f;
            int countT = 0;

            if (!solid[posX - 1][posY - 1]) {
                temp += x[posX - 1][posY - 1];
                countT++;
            }
            if (!solid[posX + 1][posY - 1]) {
                temp += x[posX + 1][posY - 1];
                countT++;
            }
            if (!solid[posX][posY - 2]) {
                temp += x[posX][posY - 2];
                countT++;
            }
            if(countT)
            x[posX][posY - 1] = temp / countT;       
        }           

        if (!solid[posX - 1][posY]) {
            float temp = 0.0f;
            int countT = 0;

            if (!solid[posX - 1][posY - 1]) {
                temp += x[posX - 1][posY - 1];
                countT++;
            }
            if (!solid[posX - 2][posY]) {
                temp += x[posX - 2][posY];
                countT++;
            }
            if (!solid[posX - 1][posY + 1]) {
                temp += x[posX - 1][posY + 1];
                countT++;
            }
            if (countT)
                x[posX-1][posY] = temp / countT;
        }

    
        if (!solid[posX][posY + 1]){
            float temp = 0.0f;
            int countT = 0;

            if (!solid[posX - 1][posY + 1]) {
                temp += x[posX - 1][posY + 1];
                countT++;
            }
            if (!solid[posX][posY + 2]) {
                temp += x[posX][posY + 2];
                countT++;
            }
            if (!solid[posX + 1][posY + 1]) {
                temp += x[posX + 1][posY + 1];
                countT++;
            }
            if (countT)
                x[posX][posY + 1] = temp / countT;
        }

   
        if (!solid[posX + 1][posY]) {
            float temp = 0.0f;
            int countT = 0;

            if (!solid[posX + 1][posY + 1]) {
                temp += x[posX + 1][posY + 1];
                countT++;
            }
            if (!solid[posX + 1][posY - 1]) {
                temp += x[posX + 1][posY - 1];
                countT++;
            }
            if (!solid[posX + 2][posY]) {
                temp += x[posX + 2][posY];
                countT++;
            }
            if (countT)
                x[posX + 1][posY] = temp / countT;
        }

}

void Physics::SetBnd(int b, float x[][SIZE], bool solid[][SIZE]) {

        for (int i = 2; i < SIZE - 2; i++) {
             for (int j = 2; j < SIZE - 2; j++) {
                if (solid[i][j]) {
                ReverseVelocity(i, j, x, solid);
                x[i][j] = 0.0f;
                }
            }
        }
        for (int i = 1; i < SIZE - 1; i++) {
            x[i][0] = b == 2 ? -x[i][1] : x[i][1];
            x[i][SIZE - 1] = b == 2 ? -x[i][SIZE - 2] : x[i][SIZE - 2];
        }

        for (int j = 1; j < SIZE - 1; j++) {
            x[0][j] = b == 1 ? -x[1][j] : x[1][j];
            x[SIZE - 1][j] = b == 1 ? -x[SIZE - 2][j] : x[SIZE - 2][j];
        }

        x[0][0] = 0.5f * (x[1][0] + x[0][1]);
        x[0][SIZE - 1] = 0.5f * (x[1][SIZE - 1] + x[0][SIZE - 2]);
        x[SIZE - 1][0] = 0.5f * (x[SIZE - 2][0] + x[SIZE -1][1]);
        x[SIZE - 1][SIZE - 1] = 0.5f * (x[SIZE - 2][SIZE -1] + x[SIZE - 1][SIZE - 2]);
}

void Physics::LinSolve(int b, float x[][SIZE], float x0[][SIZE], float a, float c, int iter, bool solid[][SIZE]) {
    float cRecip = 1.0 / c;
    for (int k = 0; k < iter; k++) {
        for (int j = 1; j < SIZE - 1; j++) {
            for (int i = 1; i < SIZE - 1; i++) {
                x[i][j] = (x0[i][j] + a * (x[i + 1][j] + x[i - 1][j] + x[i][j + 1] + x[i][j - 1])) * cRecip;
            }
        }       
            this->SetBnd(b, x, solid);       
    }
}

void Physics::Diffuse(int b, float x[][SIZE], float x0[][SIZE], float diff, float dt, int iter, bool solid[][SIZE]) {
    float a = dt * diff * (SIZE - 2) * (SIZE - 2);
    this->LinSolve(b, x, x0, a, 1 + 6 * a, iter, solid);
}

void Physics::Project(float vx[][SIZE], float vy[][SIZE], float p[][SIZE], float div[][SIZE], int iter, bool solid[][SIZE]) {
    for (int j = 1; j < SIZE - 1; j++) {
        for (int i = 1; i < SIZE - 1; i++) {
            div[i][j] = -0.5f * (vx[i + 1][j] - vx[i - 1][j] + vy[i][j + 1] - vy[i][j - 1]) / SIZE;
            p[i][j] = 0;
        }
    }

    this->SetBnd(0,div, solid);
    this->SetBnd(0,p, solid);
    this->LinSolve(0, p, div, 1, 6, iter, solid);

    for (int j = 1; j < SIZE - 1; j++) {
        for (int i = 1; i < SIZE - 1; i++) {
            vx[i][j] -= 0.5f * (p[i + 1][j] - p[i - 1][j]) * SIZE;
            vy[i][j] -= 0.5f * (p[i][j + 1] - p[i][j - 1]) * SIZE;
        }
    }
    this->SetBnd(1, vx, solid);
    this->SetBnd(2, vy, solid);
}

void Physics::Advect(int b, float d[][SIZE], float d0[][SIZE], float vx[][SIZE], float vy[][SIZE], float dt, bool solid[][SIZE]) {
    float i0, i1, j0, j1;

    float dtx = dt * (SIZE - 2);
    float dty = dt * (SIZE - 2);

    float s0, s1, t0, t1;
    float tmp1, tmp2, x, y;

    float Nfloat = SIZE;
    float ifloat, jfloat;

    int i, j;

    for (j = 1, jfloat = 1; j < SIZE - 1; j++, jfloat++) {
        for (i = 1, ifloat = 1; i < SIZE - 1; i++, ifloat++) {
            tmp1 = dtx * vx[i][j];
            tmp2 = dty * vy[i][j];
            x = ifloat - tmp1;
            y = jfloat - tmp2;

            if (x < 0.5f) x = 0.5f;
            if (x > Nfloat + 0.5f) x = Nfloat + 0.5f;
            i0 = ::floorf(x);
            i1 = i0 + 1.0f;
            if (y < 0.5f) y = 0.5f;
            if (y > Nfloat + 0.5f) y = Nfloat + 0.5f;
            j0 = ::floorf(y);
            j1 = j0 + 1.0f;

            s1 = x - i0;
            s0 = 1.0f - s1;
            t1 = y - j0;
            t0 = 1.0f - t1;

            int i0i = i0;
            int i1i = i1;
            int j0i = j0;
            int j1i = j1;

            d[i][j] =
                s0 * (t0 * d0[i0i][j0i] + t1 * d0[i0i][j1i]) +
                s1 * (t0 * d0[i1i][j0i] + t1 * d0[i1i][j1i]);
        }
    }
        
         this->SetBnd(b, d, solid);
}