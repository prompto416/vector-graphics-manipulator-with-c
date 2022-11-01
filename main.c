#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

typedef struct svg
{
    char* svg;
    int height;
    int width;
    bool finalized;
} svg;

static void appendstringtosvg(svg* psvg, char* text)
{
    int l = strlen(psvg->svg) + strlen(text) + 1;

    char* p = realloc(psvg->svg, l);

    if(p)
    {
        psvg->svg = p;
    }

    strcat(psvg->svg, text);
}
static void appendnumbertosvg(svg* psvg, int n)
{
    char sn[16];

    sprintf(sn, "%d", n);

    appendstringtosvg(psvg, sn);
}

svg* svg_create(int width, int height)
{
    svg* psvg = malloc(sizeof(svg));

    if(psvg != NULL)
    {
        *psvg = (svg){.svg = NULL, .width = width, .height = height, .finalized = false};

        psvg->svg = malloc(1);

        sprintf(psvg->svg, "%s", "\0");

        appendstringtosvg(psvg, "<svg width='");
        appendnumbertosvg(psvg, width);
        appendstringtosvg(psvg, "px' height='");
        appendnumbertosvg(psvg, height);
        appendstringtosvg(psvg, "px' xmlns='http://www.w3.org/2000/svg' version='1.1' xmlns:xlink='http://www.w3.org/1999/xlink'>\n");

        return psvg;
    }
    else
    {
        return NULL;
    }
}

void svg_finalize(svg* psvg)
{
    appendstringtosvg(psvg, "</svg>");

    psvg->finalized = true;
}

void svg_rectangle(svg* psvg, int width, int height, int x, int y, char* fill, char* stroke, int strokewidth, int radiusx, int radiusy)
{
    appendstringtosvg(psvg, "    <rect fill='");
    appendstringtosvg(psvg, fill);
    appendstringtosvg(psvg, "' stroke='");
    appendstringtosvg(psvg, stroke);
    appendstringtosvg(psvg, "' stroke-width='");
    appendnumbertosvg(psvg, strokewidth);
    appendstringtosvg(psvg, "px' width='");
    appendnumbertosvg(psvg, width);
    appendstringtosvg(psvg, "' height='");
    appendnumbertosvg(psvg, height);
    appendstringtosvg(psvg, "' y='");
    appendnumbertosvg(psvg, y);
    appendstringtosvg(psvg, "' x='");
    appendnumbertosvg(psvg, x);
    appendstringtosvg(psvg, "' ry='");
    appendnumbertosvg(psvg, radiusy);
    appendstringtosvg(psvg, "' rx='");
    appendnumbertosvg(psvg, radiusx);
    appendstringtosvg(psvg, "' />\n");
}

void svg_save(svg* psvg, char* filepath)
{
    if(!psvg->finalized)
    {
        svg_finalize(psvg);
    }

    FILE* fp;

    fp = fopen(filepath, "w");

    if(fp != NULL)
    {
        fwrite(psvg->svg, 1, strlen(psvg->svg), fp);

        fclose(fp);
    }
}

void svg_free(svg* psvg)
{
    free(psvg->svg);

    free(psvg);
}
void svg_text(svg* psvg, int x, int y, char* fontfamily, int fontsize, char* fill, char* stroke, char* text)
{
    appendstringtosvg(psvg, "    <text x='");
    appendnumbertosvg(psvg, x);
    appendstringtosvg(psvg, "' y = '");
    appendnumbertosvg(psvg, y);
    appendstringtosvg(psvg, "' font-family='");
    appendstringtosvg(psvg, fontfamily);
    appendstringtosvg(psvg, "' stroke='");
    appendstringtosvg(psvg, stroke);
    appendstringtosvg(psvg, "' fill='");
    appendstringtosvg(psvg, fill);
    appendstringtosvg(psvg, "' font-size='");
    appendnumbertosvg(psvg, fontsize);
    appendstringtosvg(psvg, "px'>");
    appendstringtosvg(psvg, text);
    appendstringtosvg(psvg, "</text>\n");
}

void drawrectangles(void);


int main()
{

    char singleLine[150] = "<svg width='512px' height='513px' xmlns='http://www.w3.org/2000/svg' version='1.1' xmlns:xlink='http://www.w3.org/1999/xlink'>";
    int newRectX = 2;
    int newRectY = 3;
    
    char old_svgHeight[20];
    
    char old_svgHeightCounter1 = 0;
    
             for (int loop = 0; singleLine[loop] != '>';loop++)

        {

            if (singleLine[loop] == ' ' && singleLine[loop+1] == 'h'  && singleLine[loop+2] == 'e'&& singleLine[loop+3] == 'i' && singleLine[loop+4] == 'g' && singleLine[loop+5] == 'h'    )
            {
                
                for (int i = loop+9; singleLine[i] != 'p';i++)
                {
                    
                   
                    old_svgHeight[old_svgHeightCounter1] = singleLine[i];
                    old_svgHeightCounter1 += 1;
                }
            }

        }
    
   
    old_svgHeight[old_svgHeightCounter1] = '\0';
    printf("%s\n",old_svgHeight);

    int angle; 
    scanf("%d",&angle);
    printf("%d",angle);
    
    
    


}


void drawrectangles(void)
{
    svg* psvg;
    psvg = svg_create(1000, 1000);

    if(psvg == NULL)
    {
        puts("psvg is NULL");
    }
    else
    {

        svg_text(psvg, 32, 32, "sans-serif", 16, "#000000", "#000000", "Phobphoomin Siriboon 64011548 Vector Graphic Manipulation ");
        svg_rectangle(psvg, 50, 50, 200, 200, "Black", "White", 1, 0, 0);





        svg_finalize(psvg);
        svg_save(psvg, "rectangles.svg");
        svg_free(psvg);
    }
}




