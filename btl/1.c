#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define SIZE 100
#define PI 3.14158926535

    int n, k, bc, bg, temp, temp1;
    int n1, ld1;
    float nepdu, snbc, snbg, nepdu1;
    int dc;
    int min2;
    int dg;
    int ld;
    float nepdu2;
    char w[100];

void Windfall();
void Fogfall();
void Cloudy();
void Sunrise();
void Rainfall();
void check();

int main(){
    FILE* filein;
    filein = fopen("input.inp", "r");
    fscanf(filein, "%d %d %d %d %s", &n, &dc, &dg, &ld, w);
    fclose(filein);

    FILE* fileout;
    fileout = fopen("output.out", "w");
    if (strcmp(w, "Wind")==0 ){
        Windfall();
        fprintf(fileout,"%d %d %0.3f", bc, bg, nepdu);
    }
    
    if (strcmp(w, "Rain")== 0)
    {
        Rainfall();
        fprintf(fileout, "%d %d %0.3f", bc, bg, nepdu);
    }
    
    
    
    fclose(fileout);
    
} 
void check()
{
    if (n < 1 || n > 1000)
    {
        bc = -1;
        bg = -1;
        nepdu = n;
        FILE* fileout;
        fileout = fopen("output.out", "w");
        fprintf(fileout, "%d %d %f ", bc, bg, nepdu);
        fclose(fileout);
        exit(0);
    }

    if (dc < 1)
    {
        snbg = (dg*dg*PI)/4;
        bc = 0;
        bg = n/snbg;
        nepdu = n - bg*snbg;
    
        FILE* fileout;
        fileout = fopen("output.out", "w");
        fprintf(fileout, "%d %d %0.3f %s", bc, bg, nepdu, w);
        fclose(fileout);
        exit(0);
    }

    if (dg < 1)
    {
        snbc = dc*dc;
        bg = 0;
        bc = n/snbc;
        nepdu = n - bc*snbc;
    
        FILE* fileout;
        fileout = fopen("output.out", "w");
        fprintf(fileout, "%d %d %0.3f %s", bc, bg, nepdu, w);
        fclose(fileout);
        exit(0);
    }
    if (ld < 1 || ld > 300)
    {
        bc = -1;
        bg = -1;
        nepdu = n;
        FILE* fileout;
        fileout = fopen("output.out", "w");
        fprintf(fileout, "%d %d %f ", bc, bg, nepdu);
        fclose(fileout);
        exit(0);
    }
    
     
    
}
void Windfall()
{
    int min = n;
    int i;
    int j;
    
    snbc = dc*dc;
    snbg = (dg*dg*PI)/4;
    bc = n/snbc;
    temp = n -(bc * snbc);
    bg = temp / snbg;
    nepdu = temp - (bg * snbg);

    if (bc + bg < ld)
    {
        bc = n/snbc;
        temp = n -(bc * snbc);
        bg = temp / snbg;
        nepdu = temp - (bg * snbg);
    }

    if (bc + bg >= ld )
    {
        for (i = 1; i < ld; i++)
            {
                for ( j = 1; j < ld - i; j++)
                {
                    bc = i ;
                    bg = ld - i;
                    nepdu = n - bc*snbc - bg*snbg;
                    
                }
                
            }
        }
    }
void Rainfall()
{
    int i;
    int j;
    int bcdau, bgdau, bc1, bg1;
    int bcm, bgm;
    float nepdubc, nepdubg;
    float min = 1000;
    float min1 = 1000;
    float min2 = 1000;
    int twobanh;
    snbc = dc * dc;
    snbg = (dg * dg * PI) / 4;

    for (twobanh = 1; twobanh <= ld / 2; twobanh++) {
        nepdu1 = n - (twobanh * dc * dc) - (twobanh * dg * dg * PI / 4);
        if (nepdu1 < min && nepdu1 >= 0) {
            bcdau = twobanh;
            bgdau = twobanh;
            min = nepdu1;
        }
    }

    int stop = 0;

    while (min > dc * dc && stop == 0)
    {
        if (ld - bcdau > 0)
        {
            for (bcm = 1; bcm <= ld - bcdau; bcm++)
            {
                nepdubc = min - dc * dc * bcm;
                if (nepdubc >= 0)
                {
                    min1 = nepdubc;
                    bg = bgdau;
                    nepdu = min1;
                    if (min > nepdu)
                        {
                            temp1 = nepdu;
                            bc1 = temp1/(dc*dc);
                            nepdu1 = nepdu - bc1*snbc;
                            nepdu = nepdu1;
                        }
                    bc = bcdau + bcm + bc1;
                    stop = 1;
                    break;
                }
            }
        }
        else
        {
            bc = bcdau;
            nepdu = min1;
            stop = 1;
        }
    }

    while (min > (dg * dg * PI) / 4 && stop == 0)
    {
        if (ld - bgdau > 0)
        {
            for (bgm = 1; bgm <= ld - bgdau; bgm++)
            {
                nepdubg = min - (dg * dg * PI / 4) * bgm;
                if (nepdubg >= 0)
                {
                    min1 = nepdubg;
                    bc = bcdau;
                    nepdu = min1;
                    if (min > nepdu)
                        {
                            temp1 = nepdu;
                            bg1 = temp1/(dg * dg * PI / 4);
                            nepdu1 = nepdu - bg1*snbg;
                            nepdu = nepdu1;
                        }
                    bg = bgdau + bgm + bg1;
                    stop = 1;
                    break;
                }
            }
        }
        else
        {
            bg = bgdau;
            nepdu = min2;
            stop = 1;
        }
    }
    if (min < dc * dc || min < (dg * dg * PI) / 4)
    {
        bc = bcdau;
        bg = bgdau;
        nepdu = min;
    }
}

void Sunrise(){
    int G = dc%6;
    int H = ld%5;
    int X[5][6]=  { {5,7,10,12,15,20},
                        {20,5,7,10,12,15},
                        {15,20,5,7,10,12},
                        {12,20,5,7,10,12},
                        {10,12,15,20,5,7}  };
    n = n + n*X[H][G]*1.0/100;
    ld = ld - X[H][G];


    if((dc + dg)%3 == 0)
    {
        strcpy(w,"Rain");
    }
    if((dc + dg)%3 == 1)
    {
        strcpy(w,"Wind");
    }
    if((dc + dg)%3 == 2)
    {
        strcpy(w,"Cloud");
    }

    FILE *filein2;
    filein2 = fopen("output.out", "w");
    fprintf(filein2, "%d %d %d %d %s", n, dc, dg, ld, w);
    fclose(filein2);
   
    

}

void Fogfall(){}

void Cloudy(){
    int divisornum1;
    int divisornum2;
    for (int i = 0; i < n; i++)
    {
        if (n/i == 0)
        {
            divisornum1 += i;
        }
        
    }

    for (int i = 0; i < ld; i++)
    {
        if (ld/i == 0)
        {
            divisornum2 += i;
        }
    }
    if ((n == divisornum2) && (ld == divisornum1))
    {
        bc = 0;
        ld = 0;
        n = n;
    }
    
    else{
        snbc = dc*dc;
        snbg = (dg*dg*PI)/4;
        if (snbc > snbg)
        {
            bc = n/snbc;
            nepdu1 = n - (bc*snbc);
        }
        else{
            bg = n/snbg;
            temp1 = n -(bg * snbg);
            bc = temp1 / snbc;
            nepdu1 = temp1 - (bc * snbc);
        }

        

    }

}














