#include <stdio.h>
#include <cmath>
#include <string>
#include <map>

using namespace std;

      
int resolution;

int byteIterator = 0;
int byteValue;//нада сделать локальными в colorreading
float R, G, B;

int resolutionStopMarker;
int resolutionIterator = 0;

char* BMPName();
bool CheckBMP();
int SkipTo10();
void SkipToStart(int temp);
void ColorReading();
bool EndOfFile(float value);
void roundUp(float multiple);
string ColorWriting();
bool Skipper();
char *bmp = BMPName();
FILE *fp = fopen(bmp, "rb");// open file in binary mode



int main(){
    
    string modifiedString = "\033[0;41m  \033[0m\n";
    printf("%s", modifiedString.c_str());
    printf("\n %i\n", resolutionStopMarker);
    

    if (!CheckBMP())//                              проверка на наличие
    {
        return 0;
    }

    int temp = SkipTo10();//                                   скип до цифры с числом старта фотки
    
    SkipToStart(temp);//                            скип до начала фотки

    ColorReading();//                               чтение фотки
    

    fclose(fp);
    return 0;
}

char* BMPName()
{

    static char fname[16];
    scanf("%s",fname);
    return fname;
}
bool CheckBMP()
{
    
    if (fp == NULL) {
        fprintf(stderr, "Can't read file");
        return 0;
    } else
    {
        printf("File found \n");
        return 1;
    }
}

int SkipTo10(){
    fgetc(fp);
    int startValue;
    for (byteIterator; byteIterator < 10; byteIterator++)
    {
        startValue = fgetc(fp);
    }
    printf("\n");
    return startValue;
    
}

void SkipToStart(int temp)
{
    for (byteIterator; byteIterator < temp-1; byteIterator++)
    {
        byteValue = fgetc(fp);
        if (byteIterator == 17)
        {
            resolution = byteValue;
            resolutionStopMarker = (resolution + 4 - 1) / 4 * 4 - (((resolution + 4 - 1) / 4 * 4) - (3 * resolution));
        }
    }
    
}

void ColorReading()
{
    while (true)
    {
        
        if (EndOfFile(R))
            break;

        resolutionIterator++;

        if(Skipper())
        {
            continue;
        }



        B = fgetc(fp);

        if (EndOfFile(B))
            break;

        resolutionIterator++;

        if(Skipper())
        {
            continue;
        }



        G = fgetc(fp);

        if (EndOfFile(G))
            break;

        resolutionIterator++;

        
        R = fgetc(fp);
        if(Skipper())
        {
            continue;
        }

        roundUp(128);

        printf("%s###\033[0m", ColorWriting().c_str());
            

    }
}

bool EndOfFile(float value)
{
    if (value == EOF)
    {
        return 1;
    } else return 0;

}

void roundUp(float multiple)
{
    R = round(R / multiple) * multiple;
    G = round(G / multiple) * multiple;
    B = round(B / multiple) * multiple;
}

string ColorWriting()
{
    if (R == 0 && G == 0 && B == 0)//BLACK
    {
        return "\033[0;40;30m";
    }

    if (R == 0 && G == 0 && B == 128)//DARK BLUE
    {
        return "\033[0;44;30m";
    }

    if (R == 0 && G == 0 && B == 256)//BLUE
    {
        return "\033[0;44;34m";
    }

    if (R == 0 && G == 128 && B == 0)//DARK GREEN
    {
        return "\033[0;42;30m";
    }

    if (R == 0 && G == 128 && B == 128)//DARK CYAN
    {
        return "\033[0;46;34m";
    }

    if (R == 0 && G == 128 && B == 256)//GREENISH BLUE
    {
        return "\033[0;46;32m";
    }

    if (R == 0 && G == 256 && B == 0)//GREEN
    {
        return "\033[0;42;32m";
    }

    if (R == 0 && G == 256 && B == 128)//BLUEISH GREEN
    {
        return "\033[0;42;36m";
    }

    if (R == 0 && G == 256 && B == 256)//CYAN
    {
        return "\033[0;46;36m";
    }

    if (R == 128 && G == 0 && B == 0)//DARK RED
    {
        return "\033[0;41;30m";
    }

    if (R == 128 && G == 0 && B == 128)//DARK MAGENTA
    {
        return "\033[0;45;30m";
    }

    if (R == 128 && G == 0 && B == 256)//DARK MAGENTA BUT A BIT OF KINDA BLUE BUT NOT REALLY
    {
        return "\033[0;45;34m";
    }

    if (R == 128 && G == 128 && B == 0)//DARK YELLOW
    {
        return "\033[0;43;30m";
    }

    if (R == 128 && G == 128 && B == 128)//GREY
    {
        return "\033[0;40;37m";
    }

    if (R == 128 && G == 128 && B == 256)//BLUE BUT SLIGHTLY LIGHTER THAN DARK BLUE
    {
        return "\033[0;44;35m";
    }

    if (R == 128 && G == 256 && B == 0)//LIME GREEN WITH YELLOW
    {
        return "\033[0;42;33m";
    }

    if (R == 128 && G == 256 && B == 128)//LIGHT GREEN
    {
        return "\033[0;42;37m";
    }

    if (R == 128 && G == 256 && B == 256)//GREENISH CYAN
    {
        return "\033[0;46;32m";
    }

    if (R == 256 && G == 0 && B == 0)//RED
    {
        return "\033[0;41;31m";
    }

    if (R == 256 && G == 0 && B == 128)//BLUEISH MAGENTA
    {
        return "\033[0;45;34m";
    }

    if (R == 256 && G == 0 && B == 256)//MAGENTA
    {
        return "\033[0;45;35m";
    }

    if (R == 256 && G == 128 && B == 0)//ORANGE
    {
        return "\033[0;43;31m";
    }

    if (R == 256 && G == 128 && B == 128)//PINK!!!!!!!!!!!!!!!!!!!! NOT PINK
    {
        return "\033[0;43;31m";
    }

    if (R == 256 && G == 128 && B == 256)//PINK
    {
        return "\033[0;45;37m";
    }

    if (R == 256 && G == 256 && B == 0)//YELLOW
    {
        return "\033[0;43;33m";
    }

    if (R == 256 && G == 256 && B == 128)//LIGHT YELLOW
    {
        return "\033[0;43;37m";
    }

    if (R == 256 && G == 256 && B == 256)//WHITE
    {
        return "\033[0;47;37m";
    }



    
    return "\033[0;47m";
}

bool Skipper()
{
    if (resolutionIterator > resolutionStopMarker)
    {
        resolutionIterator = 0;
        for (int i = 0; i < ((resolution * 3 + 4 - 1) / 4 * 4) - (3 * resolution); i++)
        {
            printf(":)");
            fgetc(fp);
        }
        printf("\n");
        return true;
            
    }
    return false;
}
