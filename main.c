            #include<stdlib.h>
            #include<stdbool.h>
            #include<stdio.h>
            #include<string.h>
            #include<math.h>
            #include"svg.h"
            #include <time.h>

            void demo1(void);

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

            void svg_print(svg* psvg)
            {
                printf("%s\n", psvg->svg);
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

            void svg_fill(svg* psvg, char* Fill)
            {
                svg_rectangle(psvg, psvg->width, psvg->height, 0, 0, Fill, Fill, 0, 0, 0);
            }

            void svg_rectangle(svg* psvg, int width, int height, int x, int y, char* fill, char* stroke, int strokewidth, int radiusx, int radiusy)
            {
                appendstringtosvg(psvg, "<rect fill='");
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


            void svg_line(svg* psvg, char* stroke, int strokewidth, int x1, int y1, int x2, int y2)
            {
                appendstringtosvg(psvg, "<line stroke='");
                appendstringtosvg(psvg, stroke);
                appendstringtosvg(psvg, "' stroke-width='");
                appendnumbertosvg(psvg, strokewidth);
                appendstringtosvg(psvg, "px' y2='");
                appendnumbertosvg(psvg, y2);
                appendstringtosvg(psvg, "' x2='");
                appendnumbertosvg(psvg, x2);
                appendstringtosvg(psvg, "' y1='");
                appendnumbertosvg(psvg, y1);
                appendstringtosvg(psvg, "' x1='");
                appendnumbertosvg(psvg, x1);
                appendstringtosvg(psvg, "' />\n");
            }

            void svg_text(svg* psvg, int x, int y, char* fontfamily, int fontsize, char* fill, char* stroke, char* text)
            {
                appendstringtosvg(psvg, "<text x='");
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
            void svg_circle(svg* psvg, char* stroke, int strokewidth, char* fill, int r, int cx, int cy)
            {
                appendstringtosvg(psvg, "<circle stroke='");
                appendstringtosvg(psvg, stroke);
                appendstringtosvg(psvg, "' stroke-width='");
                appendnumbertosvg(psvg, strokewidth);
                appendstringtosvg(psvg, "px' fill='");
                appendstringtosvg(psvg, fill);
                appendstringtosvg(psvg, "' r='");
                appendnumbertosvg(psvg, r);
                appendstringtosvg(psvg, "' cy='");
                appendnumbertosvg(psvg, cy);
                appendstringtosvg(psvg, "' cx='");
                appendnumbertosvg(psvg, cx);
                appendstringtosvg(psvg, "' />\n");
            }

            void svg_ellipse(svg* psvg, int cx, int cy, int rx, int ry, char* fill, char* stroke, int strokewidth)
            {
                appendstringtosvg(psvg, "<ellipse cx='");
                appendnumbertosvg(psvg, cx);
                appendstringtosvg(psvg, "' cy='");
                appendnumbertosvg(psvg, cy);
                appendstringtosvg(psvg, "' rx='");
                appendnumbertosvg(psvg, rx);
                appendstringtosvg(psvg, "' ry='");
                appendnumbertosvg(psvg, ry);
                appendstringtosvg(psvg, "' fill='");
                appendstringtosvg(psvg, fill);
                appendstringtosvg(psvg, "' stroke='");
                appendstringtosvg(psvg, stroke);
                appendstringtosvg(psvg, "' stroke-width='");
                appendnumbertosvg(psvg, strokewidth);
                appendstringtosvg(psvg, "' />\n");
            }

            char getRectStroke(void)
            {

            }

            void demo2(void)
            {
                svg* psvg;
                psvg = svg_create(512, 512);

                if(psvg == NULL)
                {
                    puts("psvg is NULL");
                }
                else
                {
                    svg_fill(psvg, "#DADAFF");

                    svg_text(psvg, 32, 32, "Courier New", 16, "#000000", "#000000", "text");
                    svg_circle(psvg, "#000080", 4, "#0000FF", 32, 64, 96);
                    svg_ellipse(psvg, 64, 160, 32, 16, "#FF0000", "#800000", 4);

                    svg_line(psvg, "#000000", 2, 32, 192, 160, 192);

                    svg_rectangle(psvg, 64, 64, 32, 224, "#00FF00", "#008000", 4, 4, 4);

                    svg_finalize(psvg);

                    svg_save(psvg, "demo2.svg");
                    svg_free(psvg);
                }
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

            int main()
            {
                svg* psvg;
                FILE * fPointer;

                fPointer = fopen("demo2.svg","r");
                char singleLine[150];
                int counter = 1;

                char option[20];




                while (!feof(fPointer))
                {
                    fgets(singleLine,150,fPointer);




                    if (singleLine[1] == 's' && singleLine[2] == 'v' && singleLine[3] == 'g')
                    {
                        printf("%s\n",singleLine);
                        printf("SVG Image Detected, Would you like to resize the image?\n[Options] yes no: ");
                        scanf("%s",&option);

                        if (option[0] == 'y' && option[1] == 'e' && option[2] == 's')
                        {
                            int newSVGWidth;
                            int newSVGHeight;


                            printf("Enter new image width: ");
                            scanf("%d",&newSVGWidth);
                            printf("Enter new image height: ");
                            scanf("%d",&newSVGHeight);
                            psvg = svg_create(newSVGWidth, newSVGHeight);
                        }

                        else if (option[0] == 'n' && option[1] == 'o' )
                        {
                                     char old_svgWidth[20];

                char old_svgWidthCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == ' ' && singleLine[loop+1] == 'w'  && singleLine[loop+2] == 'i'&& singleLine[loop+3] == 'd' && singleLine[loop+4] == 't' && singleLine[loop+5] == 'h'    )
                        {

                            for (int i = loop+8; singleLine[i] != 'p';i++)
                            {


                                old_svgWidth[old_svgWidthCounter1] = singleLine[i];
                                old_svgWidthCounter1 += 1;
                            }
                        }

                    }


                old_svgWidth[old_svgWidthCounter1] = '\0';

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


                psvg = svg_create(atoi(old_svgWidth),atoi(old_svgHeight));



                        }


                    }
                    else if (singleLine[1] == 'r' && singleLine[2] == 'e' && singleLine[3] == 'c'&& singleLine[4] == 't')
                    {
                        char fillOption[5];









                        char oldRectFill[20];


                        char oldRectFillCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == 'f' && singleLine[loop+1] == 'i' && singleLine[loop+2] == 'l' && singleLine[loop+3] == 'l')
                        {

                            for (int i = loop+6; singleLine[i] != '\'';i++)
                            {


                                oldRectFill[oldRectFillCounter1] = singleLine[i];
                                oldRectFillCounter1 += 1;
                            }
                        }

                    }
                    printf("%s\n",singleLine);
                        printf("Rectangle Object Detected!\n");

                          printf("Do you want to fill the rectangle?: ");
                        scanf("%s",&fillOption);



                     if (fillOption[0] == 'y' && fillOption[1] == 'e' && fillOption[2] =='s')
                        {
                            char newFill[10];
                            printf("Enter the new fill color for rectangle: ");
                            scanf("%s",&newFill);

                            for (int f = 0;f < sizeof(newFill);f++)
                            {
                                oldRectFill[f] = newFill[f];
                            }

                        }


                        printf("[Rectangle Options] move rotate or skip: ");
                          scanf("%s",&option);




                    char oldRectStroke[20];

                char oldRectStrokeCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == 's' && singleLine[loop+1] == 't' && singleLine[loop+2] == 'r' && singleLine[loop+3] == 'o' && singleLine[loop+8] != 'w')
                        {

                            for (int i = loop+8; singleLine[i] != '\'';i++)
                            {


                                oldRectStroke[oldRectStrokeCounter1] = singleLine[i];
                                oldRectStrokeCounter1 += 1;
                            }
                        }

                    }


                oldRectStroke[7] = '\0';





                    oldRectFill[oldRectFillCounter1] = '\0';
                    char oldRectStrokeWidth[20];
                char oldRectStrokeWidthCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == '-' && singleLine[loop+1] == 'w' && singleLine[loop+2]   )
                        {

                            for (int i = loop+8; singleLine[i] != 'p';i++)
                            {


                                oldRectStrokeWidth[oldRectStrokeWidthCounter1] = singleLine[i];
                                oldRectStrokeWidthCounter1 += 1;
                            }
                        }

                    }


                oldRectStrokeWidth[oldRectStrokeWidthCounter1] = '\0';

                char oldRectWidth[20];

                char oldRectWidthCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == ' ' && singleLine[loop+1] == 'w'    )
                        {

                            for (int i = loop+8; singleLine[i] != '\'';i++)
                            {


                                oldRectWidth[oldRectWidthCounter1] = singleLine[i];
                                oldRectWidthCounter1 += 1;
                            }
                        }

                    }


                oldRectWidth[oldRectWidthCounter1] = '\0';

                char oldRectHeight[20];

                char oldRectHeightCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == 'h' && singleLine[loop+1] == 'e' && singleLine[loop+2] == 'i'  && singleLine[loop+3] == 'g'  && singleLine[loop+4] == 'h'     )
                        {

                            for (int i = loop+8; singleLine[i] != '\'';i++)
                            {


                                oldRectHeight[oldRectHeightCounter1] = singleLine[i];
                                oldRectHeightCounter1 += 1;
                            }
                        }

                    }


                oldRectHeight[oldRectHeightCounter1] = '\0';
                char oldRectY[20];

                char oldRectYCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == ' ' && singleLine[loop+1] == 'y'  && singleLine[loop+2] == '='    )
                        {

                            for (int i = loop+4; singleLine[i] != '\'';i++)
                            {


                                oldRectY[oldRectYCounter1] = singleLine[i];
                                oldRectYCounter1 += 1;
                            }
                        }

                    }


                oldRectY[oldRectYCounter1] = '\0';
                 char oldRectX[20];

                char oldRectXCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == ' ' && singleLine[loop+1] == 'x'  && singleLine[loop+2] == '='    )
                        {

                            for (int i = loop+4; singleLine[i] != '\'';i++)
                            {


                                oldRectX[oldRectXCounter1] = singleLine[i];
                                oldRectXCounter1 += 1;
                            }
                        }

                    }


                oldRectX[oldRectXCounter1] = '\0';
                 char oldRectRY[20];
                char oldRectRYCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == ' ' && singleLine[loop+1] == 'r'  && singleLine[loop+2] == 'y'    )
                        {

                            for (int i = loop+5; singleLine[i] != '\'';i++)
                            {


                                oldRectRY[oldRectRYCounter1] = singleLine[i];
                                oldRectRYCounter1 += 1;
                            }
                        }

                    }


                oldRectRY[oldRectRYCounter1] = '\0';
                char oldRectRX[20];
                char oldRectRXCounter1 = 0;

                         for (int loop = 0; singleLine[loop] != '>';loop++)

                    {

                        if (singleLine[loop] == ' ' && singleLine[loop+1] == 'r'  && singleLine[loop+2] == 'x'    )
                        {

                            for (int i = loop+5; singleLine[i] != '\'';i++)
                            {


                                oldRectRX[oldRectRXCounter1] = singleLine[i];
                                oldRectRXCounter1 += 1;
                            }
                        }

                    }


                oldRectRX[oldRectRXCounter1] = '\0';

    //            printf("%s\n",oldRectFill);
    //            printf("%s\n",oldRectStroke);
    //            printf("%s\n",oldRectStrokeWidth);
    //            printf("%s\n",oldRectWidth);
    //            printf("%s\n",oldRectHeight);
    //            printf("%s\n",oldRectY);
    //            printf("%s\n",oldRectX);
    //            printf("%s\n",oldRectRY);
    //            printf("%s\n",oldRectRX);
                if (option[0] == 'm' && option[1] == 'o' && option[2] == 'v'&& option[3] == 'e')
                        {
                            int newRectX,newRectY;
                            printf("Enter new X coordinate: ");
                            scanf("%d",&newRectX);
                            printf("Enter new Y coordinate: ");
                            scanf("%d",&newRectY);
                            svg_rectangle(psvg,atoi(oldRectWidth),atoi(oldRectHeight),newRectX,newRectY,oldRectFill,oldRectStroke,atoi(oldRectStrokeWidth),atoi(oldRectRX),atoi(oldRectRY));



                        }
                else if (option[0] == 's' && option[1] == 'k' && option[2] == 'i'&& option[3] == 'p')
                {

                    svg_rectangle(psvg,atoi(oldRectWidth),atoi(oldRectHeight),atoi(oldRectX),atoi(oldRectY),oldRectFill,oldRectStroke,atoi(oldRectStrokeWidth),atoi(oldRectRX),atoi(oldRectRY));



                }

                 else if (option[0] == 'r' && option[1] == 'o' && option[2] == 't'&& option[3] == 'a' && option[4] == 't' && option[5] == 'e')
                {
                    int angle;
                    printf("Enter the rotation angle from 90 180 270 or -90 -180 -270: ");
                    scanf("%d",&angle);

                    if (angle == -90)
                    {
                        angle = 270;
                    }
                    else if( angle == -180)
                    {
                        angle =180;
                    }
                    else if(angle == -270)
                    {
                        angle = 90;
                    }



                    if (angle == 90)
                    {
                        svg_rectangle(psvg,atoi(oldRectHeight),atoi(oldRectWidth),atoi(oldRectX),atoi(oldRectY)+atoi(oldRectHeight)/2,oldRectFill,oldRectStroke,atoi(oldRectStrokeWidth),atoi(oldRectRX),atoi(oldRectRY));
                    }

                    else if (angle == 180)
                    {
                        svg_rectangle(psvg,atoi(oldRectWidth),atoi(oldRectHeight),atoi(oldRectX),atoi(oldRectY)+atoi(oldRectHeight)/2,oldRectFill,oldRectStroke,atoi(oldRectStrokeWidth),atoi(oldRectRX),atoi(oldRectRY));

                    }
                    else if (angle == 270)
                    {
                        svg_rectangle(psvg,atoi(oldRectHeight),atoi(oldRectWidth),atoi(oldRectX)-atoi(oldRectX)/2,atoi(oldRectY)+atoi(oldRectHeight)/2,oldRectFill,oldRectStroke,atoi(oldRectStrokeWidth),atoi(oldRectRX),atoi(oldRectRY));

                    }


                }








                    }












                }




            svg_finalize(psvg);

                    svg_save(psvg, "transform.svg");
                    svg_free(psvg);








                return EXIT_SUCCESS;
            }

            void demo1(void)
            {
                svg* psvg;
                psvg = svg_create(512, 512);

                if(psvg == NULL)
                {
                    puts("psvg is NULL");
                }
                else
                {
                    svg_fill(psvg, "#000010");
                    svg_rectangle(psvg,200,100,100,200,"red","white",1,1,1);

                    svg_finalize(psvg);

                    svg_save(psvg, "demo1.svg");
                    svg_free(psvg);
                }
            }
