#include <cmath>
#include <string>

using namespace std;

      
int resolutionX;//  data from byte value
int resolutionY;//  data from byte value
bool flip = true;//  data from byte value


int resolutionXIterator = 0;//  data for creating array info
int resolutionYIterator = 0;//  data for creating array info
int byteIterator = 0;//  data for creating array info
int endOfLineStopMarker;// data for creating array info (to know is there are empty bytes)
int resolutionIterator = 0;//!  data for creating array info (probably needs to be replaced with resolutionXIterator)


int byteValue;// temp variable only while reading a file
float R, G, B;// color values in float


string** imageArrayInit();

int SkipAndReturnStartValue();//  skips all unnecesary bytes and returns StartValue
void GatherInfoAndSkipToStart(int startValue);// collect info from bytes and go to adress of start of the image's colors
void ColorReading();//  read image's colors from bytes
bool Skipper();//  skips empty bytes, if there are any

string ColorWriting();//  returns image's colors as strings for output
bool EndOfFile(float value);//  checks if it is end of file
void roundUp(float multiple);//!  rounds a float to limit color palette (27 colors) !!using cmath!!


char* BMPName();//  function to get filename of image
bool CheckBMP();//  check if the file actually exists

char *bmp = BMPName();//  filename of image
FILE *fp = fopen(bmp, "rb");// open file in binary mode
string** imageArray;//  image array

string** imageArrayInit()//  function to initialize 2d array of the image
{
    return NULL;
}

char* BMPName()//  function to get filename of image
{
    static char fname[16];
    printf("Enter a filename of picture\n\tImage should be 24-bit .BMP format and less then 255px by 255px\n>>>");
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

int SkipAndReturnStartValue(){
    fgetc(fp);
    int startValue;
    for (byteIterator; byteIterator < 10; byteIterator++)
    {
        startValue = fgetc(fp);
    }
    printf("\n");
    return startValue;
    
}

void GatherInfoAndSkipToStart(int startValue)
{
    for (byteIterator; byteIterator < startValue - 1; byteIterator++)
    {
        byteValue = fgetc(fp);
        if (byteIterator == 17)
        {
            resolutionX = byteValue;
            endOfLineStopMarker = (resolutionX + 4 - 1) / 4 * 4 - (((resolutionX + 4 - 1) / 4 * 4) - (3 * resolutionX));
        }
        if (byteIterator == 21)
        {
            resolutionY = byteValue;
            printf("%i",resolutionY);
        }
        if (byteIterator == 24)
        {
            if (byteValue == 255)
            {
                flip = true;
                resolutionY =  256 - resolutionY;
            }
            else
                flip = false;
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
        
        imageArray[resolutionXIterator][resolutionYIterator] = ColorWriting();

        resolutionXIterator++;
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
        return "\033[0;41;33m";
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
    if (resolutionIterator > endOfLineStopMarker)
    {
        resolutionIterator = 0;
        for (int i = 0; i < ((resolutionX * 3 + 4 - 1) / 4 * 4) - (3 * resolutionX); i++)
        {
            //printf(":)");
            fgetc(fp);
        }
        //printf("\n");
        resolutionYIterator++;// переход на новую строку
        resolutionXIterator = 0;
        return true;
            
    }
    return false;
}


int main(){  
    //  getting bmp before main...

    if (!CheckBMP())//  if bmp is missing, quit
    {
        return 0;
    }

    int startValue = SkipAndReturnStartValue();//  get start value
    
    GatherInfoAndSkipToStart(startValue);//  скип до начала фотки

    imageArray = new string*[resolutionX];
    for(int i = 0; i < resolutionX; ++i) 
    {
        imageArray[i] = new string[resolutionY];
    }

    ColorReading();//                               чтение фотки
    
    fclose(fp);

    if (flip)
    {
        for (int j = 0; j < resolutionY; j++)
        {
            for (int i = 0; i < resolutionX; i++)
            {
                printf("%s⩨⩨⩨\033[0m", imageArray[i][j].c_str());
            }
            printf("\n");
        
        }
    }else
    {
        for (int j = resolutionY-1; j > 0 ; j--)
        {
            for (int i = 0; i < resolutionX; i++)
            {
                printf("%s⩨⩨⩨\033[0m", imageArray[i][j].c_str());
            }
            printf("\n");
        
        }   
    }

    for(int i = 0; i < resolutionY; ++i) {
        delete [] imageArray[i];
    }
    delete [] imageArray;

    return 0;
}
