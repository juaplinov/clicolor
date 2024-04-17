
#include <stdio.h>

class ColorPrefix
{
private:

public:
    char bgColor;
    char fgColor;
};



      
int resolutionX;//  data from byte value
int resolutionY;//  data from byte value
bool flip = true;//  data from byte value


int resolutionXIterator = 0;//  data for creating array info
int resolutionYIterator = 0;//  data for creating array info
int byteIterator = 0;//  data for creating array info
int endOfLineStopMarker;// data for creating array info (to know is there are empty bytes)
int resolutionIterator = 0;//!  data for creating array info (probably needs to be replaced with resolutionXIterator)


int byteValue;// temp variable only while reading a file
int R, G, B;// color values in int



int SkipAndReturnStartValue();//  skips all unnecesary bytes and returns StartValue
void GatherInfoAndSkipToStart(int startValue);// collect info from bytes and go to adress of start of the image's colors
void ColorReading();//  read image's colors from bytes
bool Skipper();//  skips empty bytes, if there are any

void ColorWriting();//  returns image's colors as strings for output
bool EndOfFile(int value);//  checks if it is end of file
int roundUp(int color, int multiple);//!  rounds a int to limit color palette (27 colors) !!using cmath!!


char* BMPName();//  function to get filename of image
bool CheckBMP();//  check if the file actually exists

char *bmp = BMPName();//  filename of image
FILE *fp = fopen(bmp, "rb");// open file in binary mode

ColorPrefix** colorPrefix;


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

        R = roundUp(R, 128);
        G = roundUp(G, 128);
        B = roundUp(B, 128);
        
        ColorWriting();

        resolutionXIterator++;
    }
}

bool EndOfFile(int value)
{
    if (value == EOF)
    {
        return 1;
    } else return 0;

}

int roundUp(int color, int multiple)
{
    for (int i = 0; i <= 256; i += multiple)
    {
        if (color >= i - multiple/2 && color <= i+multiple/2)
        {
            color = i;
            break;
        }
        
    }
    return color;
}

void ColorWriting()
{
    if (R == 0 && G == 0 && B == 0)//BLACK
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '0';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '0';
        return;
    }

    if (R == 0 && G == 0 && B == 128)//DARK BLUE
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '4';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '0';
        return;
    }

    if (R == 0 && G == 0 && B == 256)//BLUE
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '4';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '4';
        return;
    }

    if (R == 0 && G == 128 && B == 0)//DARK GREEN
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '2';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '0';
        return;
    }

    if (R == 0 && G == 128 && B == 128)//DARK CYAN
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '6';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '4';
        return;
    }

    if (R == 0 && G == 128 && B == 256)//GREENISH BLUE
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '6';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '2';
        return;
    }

    if (R == 0 && G == 256 && B == 0)//GREEN
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '2';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '2';
        return;
    }

    if (R == 0 && G == 256 && B == 128)//BLUEISH GREEN
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '2';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '6';
        return;
    }

    if (R == 0 && G == 256 && B == 256)//CYAN
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '6';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '6';
        return;
    }

    if (R == 128 && G == 0 && B == 0)//DARK RED
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '1';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '0';
        return;
    }

    if (R == 128 && G == 0 && B == 128)//DARK MAGENTA
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '5';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '0';
        return;
    }

    if (R == 128 && G == 0 && B == 256)//DARK MAGENTA BUT A BIT OF KINDA BLUE BUT NOT REALLY
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '5';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '4';
        return;
    }

    if (R == 128 && G == 128 && B == 0)//DARK YELLOW
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '3';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '0';
        return;
    }

    if (R == 128 && G == 128 && B == 128)//GREY
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '0';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '7';
        return;
    }

    if (R == 128 && G == 128 && B == 256)//BLUE BUT SLIGHTLY LIGHTER THAN DARK BLUE
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '4';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '5';
        return;
    }

    if (R == 128 && G == 256 && B == 0)//LIME GREEN WITH YELLOW
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '2';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '3';
        return;
    }

    if (R == 128 && G == 256 && B == 128)//LIGHT GREEN
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '2';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '7';
        return;
    }

    if (R == 128 && G == 256 && B == 256)//GREENISH CYAN
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '6';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '2';
        return;
    }

    if (R == 256 && G == 0 && B == 0)//RED
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '1';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '1';
        return;
    }

    if (R == 256 && G == 0 && B == 128)//BLUEISH MAGENTA
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '5';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '4';
        return;
    }

    if (R == 256 && G == 0 && B == 256)//MAGENTA
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '5';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '5';
        return;
    }

    if (R == 256 && G == 128 && B == 0)//ORANGE
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '3';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '1';
        return;
    }

    if (R == 256 && G == 128 && B == 128)//PINK!!!!!!!!!!!!!!!!!!!! NOT PINK
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '1';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '3';
        return;
    }

    if (R == 256 && G == 128 && B == 256)//PINK
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '5';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '7';
        return;
    }

    if (R == 256 && G == 256 && B == 0)//YELLOW
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '3';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '3';
        return;
    }

    if (R == 256 && G == 256 && B == 128)//LIGHT YELLOW
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '3';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '7';
        return;
    }

    if (R == 256 && G == 256 && B == 256)//WHITE
    {
        colorPrefix[resolutionXIterator][resolutionYIterator].bgColor = '7';
        colorPrefix[resolutionXIterator][resolutionYIterator].fgColor = '7';
        return;
    }
}

bool Skipper()
{
    if (resolutionIterator > endOfLineStopMarker)
    {
        resolutionIterator = 0;
        for (int i = 0; i < ((resolutionX * 3 + 4 - 1) / 4 * 4) - (3 * resolutionX); i++)
        {
            fgetc(fp);
        }
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


    //! NEW
    colorPrefix = new ColorPrefix*[resolutionX];
    for(int i = 0; i < resolutionX; ++i) 
    {
        colorPrefix[i] = new ColorPrefix[resolutionY];
    }

    ColorReading();//                               чтение фотки
    
    fclose(fp);

    //! NEW
    if (flip)
    {
        for (int j = 0; j < resolutionY; j++)
        {
            for (int i = 0; i < resolutionX; i++)
            {
                printf("\033[0;4%c;3%cm⩨⩨⩨\033[0m", colorPrefix[i][j].bgColor, colorPrefix[i][j].fgColor);
            }
            printf("\n");
        
        }
    }else
    {
        for (int j = resolutionY-1; j > 0 ; j--)
        {
            for (int i = 0; i < resolutionX; i++)
            {
                printf("\033[0;4%c;3%cm⩨⩨⩨\033[0m", colorPrefix[i][j].bgColor, colorPrefix[i][j].fgColor);
            }
            printf("\n");
        
        }   
    }

    for(int i = 0; i < resolutionY; ++i) {
        delete [] colorPrefix[i];
    }
    delete [] colorPrefix;

    return 0;
}
