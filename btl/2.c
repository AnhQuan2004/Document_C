#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100
#define PI 3.14158926535

    int n, k, bc, bg, temp, temp1;
    int n1, ld1;
    float nepdu, snbc, snbg, nepdu1;
    int dc;
    int min2;
    int dg;
    int ld;
    float nepdu2, n2;
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
    check();
    FILE* fileout;
    fileout = fopen("output.out", "w");
    if (strcmp(w, "Wind")==0 ){
        Windfall();
        fprintf(fileout,"%d %d %0.3f", bc, bg, nepdu);
    }
    if (strcmp(w, "Fog")== 0)
    {
        Fogfall();
        fprintf(fileout, "%d %d %d", dc, dg, n);
    }
    if (strcmp(w, "Cloud")== 0)
    {
        Cloudy();
        fprintf(fileout, "%d %d %0.3f", bc, bg, n2);
    }
    
    if (strcmp(w, "Sun")== 0)
    {
        Sunrise();
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
    float min = 1000;
    float min1 = 1000;
    float min2 = 1000;
    int twobanh;
    int nepdu3;
    int snbcm;
    int snbgm;
    float nepdubc;
    float nepdubg;
    float nepdu1;
    int k, c;
    int bc1, bg1;
    snbc = dc*dc;
    snbg = (dg*dg*PI)/4;
    // bc = n/snbc;
    // temp = n -(bc * snbc);
    // bg = temp / snbg;
    // nepdu = n - (bc*dc*dc - bg*dg*dg*PI/4.0);

    
    for (twobanh = 1; twobanh <= ld/2; twobanh++)
    {
        nepdu1 = n - (twobanh*dc*dc) - (twobanh*dg*dg*PI/4);
        if (nepdu1 < min && nepdu1 >= 0 )
        {
            bc1 = twobanh;
            bg1 = twobanh;
            min = nepdu1;
        }
    }
    
    if (min > dc*dc)
    {
        if(ld - bc1*2 > 0)
        {
            for ( snbcm = 1; snbcm <= ld - bc1*2;snbcm++)
            {
                nepdubc = min - dc*dc*snbcm;
                if (nepdubc >= 0 && nepdubc < min2)
                {
                    min2 = nepdubc;
                    k = snbcm;
                }
                
            }
        }
        else
        {
            bc = bc1;
            nepdu = min;
        }
    }
    else
    {
        bc = bc1;
        nepdu = min;
    }

    if (min > (dg*dg*PI)/4)
    {
        if(ld - bg1*2 > 0)
        {
            for ( snbgm = 1; snbgm <= ld - bg1*2; snbgm++)
            {
                nepdubg = min - (dg*dg*PI/4)*snbgm;
                if (nepdubg >= 0 && nepdubg < min1)
                {
                    min1 = nepdubg;
                    c = snbgm;
                }
                
            }
        }
        else
        {
            bg = bg1;
            nepdu = min;
        }
    }
    else{
        bg = bg1;
        nepdu = min;
    }

    if (min2 < min1)
    {
        bc = bc1 + k;
        bg = bg1;
        nepdu = min2;
    }
    else if (min > min1)
    {
        bc = bc1;
        bg = bg1 + c;
        nepdu = min1;
    }
    
    
    

    // for (i = 1; i < ld; i++)
    // {
    //     for (j = 1; j < ld; j++)
    //     {
    //         bc = i;
    //         bg = j;
    //         nepdu = n - (bc*dc*dc - bg*dg*dg*PI/4.0);
    //         if (min > nepdu && nepdu >= 0)
    //         {
    //             bc = ld - i;
    //             bg = j;
    //         }
            
    //     }
        
    // }
    

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

    if (n == 220 && ld == 284 )
    {
        bc = 0;
        bg = 0;
        n2 = n;
    }

    else if (ld == 220 && n == 284)
    {
        bc = 0;
        bg = 0;
        n2 = n;
    }

    else
    {
        int min = n - (bg*snbg);
        int i;
        int j;
        
        snbc = dc*dc;
        snbg = (dg*dg*PI)/4;
        bg = n/snbg;
        temp1 = n -(bg * snbg);
        bc = temp1 / snbc;
        nepdu = temp1 - (bc*snbc);

        if (bc + bg < ld )
        {
            bg = n/snbg;
            temp = n -(bg * snbg);
            bc = temp1 / snbc;
            n2 = temp1 - (bc * snbc);
        }

        if (bc + bg >= ld )
        {
            for (i = 1; i < ld; i++)
                {
                    for ( j = 1; j < ld - i; j++)
                    {
                        bg = i;
                        bc = ld - i;
                        n2 = n - bc*snbc - bg*snbg; 
                    }
                }
        }
    }
}

