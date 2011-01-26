/*
 * header file for RTF-to-LaTeX2e translation writer code.
 * (c) 1999 Ujwal S. Sathyam
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */


# define    rtf2latex2e_version "2.0"

# define    WRAP_LIMIT  80
# define    PACKAGES    9

# define    UNINITIALIZED -99

#ifndef boolean
typedef unsigned char boolean;
#endif
# define    New(t)  ((t *) RTFAlloc (sizeof (t)))
# define    Swap(a, b) {int tmp;\
                        tmp = a;\
                        a = b;\
                        b = tmp;}

#if defined(UNIX)
    # define    PATH_SEP    '/'
    # define    ENV_SEP     ':'
#else 
    # define    PATH_SEP    '\\'
    # define    ENV_SEP     ';'
#endif

#ifndef false
    #define false 0
#endif

#ifndef true
    #define true 1
#endif

void    WriterInit (void);
int BeginLaTeXFile (void);
void EndLaTeXFile (void);

void RTFSetOutputStream (FILE *ofp);

enum pictType {unknownPict, pict, wmf, gif, jpeg, bin, png};
enum objClass {unknownObjClass, EquationClass, WordPictureClass, MSGraphChartClass};
enum word97ObjectClass {unknownWord97Object, word97Object, standardObject, word97Picture, word97ObjText};
enum {left, center, right};
enum {singleSpace, oneAndAHalfSpace, doubleSpace};
typedef enum {tinySize, scriptSize, footNoteSize, smallSize, normalSize, 
            largeSize, LargeSize, LARGESize, giganticSize, GiganticSize} fontSize;
enum cellMergeFlag {none, first, previous};

typedef struct 
{
    int count;
    int type;
    int32_t width;
    int32_t height;
    int32_t goalWidth;
    int32_t goalHeight;
    int32_t scaleX;
    int32_t scaleY;
    int     llx;
    int     lly;
    int     urx;
    int     ury;
    char    name[rtfBufSiz];
} pictureStruct;

typedef struct
{
    int count;
} equationStruct;


typedef struct
{
    int bold;
    int italic;
    int underlined;
    int dbUnderlined;
    int shadowed;
    int allCaps;
    int smallCaps;
    int subScript;
    int superScript;
    int fontSize;
    int foreColor;
    int backColor;
} textStyleStruct;

typedef struct
{
    int alignment;
    int lineSpacing;
    int firstIndent;
    int leftIndent;
    int rightIndent;
    int spaceBefore;
    int spaceAfter;
    int parbox;
    char *headingString;
    int extraIndent;
} parStyleStruct;

typedef struct cell
{
    int x;
    int y;
    int left;
    int right;
    double  width;
    int     columnSpan;
    int     index;
    int     mergePar;   
    long    textColor;
    boolean textBold;
    boolean textItalic;
    boolean textUnderlined;
    struct cell *nextCell;
} cell;

typedef struct
{
    boolean inside;
    int     rows;
    int     cols;
    int     cellCount;
    int     leftEdge;
    cell    *cellInfo;
    int     rowInfo[rtfBufSiz];
    int     *columnBorders;
    int     cellMergePar;
    int     previousColumnValue;
    boolean newRowDef;
    boolean multiCol;
    boolean multiRow;
} tableStruct;

short ReadPrefFile (char *file);

extern parStyleStruct paragraph, paragraphWritten;
extern textStyleStruct textStyle, textStyleWritten;


