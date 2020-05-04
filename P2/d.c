// Krzysztof Wydrzynski
#include <stdio.h>
#include <stdlib.h>

void addFrontRow (int*** structure, int* rows, int** cols, int howManyElements) {
    int** newStructure = (int**)malloc((*rows + 1) * sizeof(int*));

    int i;
    *(newStructure) = (int*)malloc(howManyElements * sizeof(int));

    for (i = 0; i < *rows; i++) {
        *(newStructure + i + 1) = *(*(structure) + i);
    }

    int* newCols = malloc((*rows + 1) * sizeof(int));

    *newCols = howManyElements;

    for (i = 0; i < *rows; i++) {
        *(newCols + i + 1) = *(*(cols) + i);
    }

    free(*cols);
    *cols = newCols;

    free(*structure);
    *structure = newStructure;

    *rows += 1;
}

void addLastRow (int*** structure, int* rows, int** cols, int howManyElements) {
    int** newStructure = (int**)malloc((*rows + 1) * sizeof(int*));

    *(newStructure + *rows) = (int*)malloc(howManyElements * sizeof(int));

    int i;
    for (i = 0; i < *rows; i++) {
        *(newStructure + i) = *(*(structure) + i);
    }

    int* newCols = malloc((*rows + 1) * sizeof(int));

    *(newCols + *rows) = howManyElements;

    for (i = 0; i < *rows; i++) {
        *(newCols + i) = *(*(cols) + i);
    }

    free(*cols);
    *cols = newCols;

    free(*structure);
    *structure = newStructure;

    *rows += 1;
}

void addFirstColumn (int*** structure, int* rows, int** cols, int howMuch, int howManyElements) {
    int i;
    for (i = 0; i < howMuch; i++) {
        int* newStructure = (int*)malloc((howManyElements + *(*(cols) + i)) * sizeof(int));
        int j;
        for (j = 0; j < *(*(cols) + i); j++) {
            *(newStructure + j + howManyElements) =  *(*(*(structure) + i) + j);
        }
        *(*(cols) + i) += howManyElements;
        free(*(*(structure) + i));
        *(*(structure) + i) = newStructure;
    }

}

void addLastColumn (int*** structure, int* rows, int** cols, int howMuch, int howManyElements) {
    int i;
    for (i = 0; i < howMuch; i++) {
        int* newStructure = (int*)malloc((howManyElements + *(*(cols) + i)) * sizeof(int));
        int j;
        for (j = 0; j < *(*(cols) + i); j++) {
            *(newStructure + j) =  *(*(*(structure) + i) + j);
        }
        *(*(cols) + i) += howManyElements;
        free(*(*(structure) + i));
        *(*(structure) + i) = newStructure;
    }

}

void insertBeforeRow (int*** structure, int* rows, int** cols, int howManyElements, int rowNumber) {
    int** newStructure = (int**)malloc((*rows + 1) * sizeof(int*));
    int* newCols = malloc((*rows + 1) * sizeof(int));
    int i, j;
    for (i = 0, j = 0; i < *rows + 1; i++, j++) {
        if (i == rowNumber) {
            *(newStructure + i) = (int*)malloc(howManyElements * sizeof(int));
            *(newCols + i) = howManyElements;
            j--;
        } else {
            *(newStructure + i) = *(*(structure) + j);
            *(newCols + i) = *(*(cols) + j);
        }
    }

    free(*structure);
    free(*cols);
    *rows += 1;
    *cols = newCols;
    *structure = newStructure;
}

void insertAfterRow (int*** structure, int* rows, int** cols, int howManyElements, int rowNumber) {
    int** newStructure = (int**)malloc((*rows + 1) * sizeof(int*));
    int* newCols = malloc((*rows + 1) * sizeof(int));
    int i, j;
    for (i = 0, j = 0; i < *rows + 1; i++, j++) {
        if (i == rowNumber + 1) {
            *(newStructure + i) = (int*)malloc(howManyElements * sizeof(int));
            *(newCols + i) = howManyElements;
            j--;
        } else {
            *(newStructure + i) = *(*(structure) + j);
            *(newCols + i) = *(*(cols) + j);
        }
    }
    free(*structure);
    free(*cols);
    *rows += 1;
    *cols = newCols;
    *structure = newStructure;
}

void insertBeforeColumn (int*** structure, int* rows, int** cols, int howManyElements, int columnNumber) {
    int i;
    howManyElements = howManyElements > *rows ? *rows : howManyElements;
    for (i = 0; i < howManyElements; i++) {
        int* newCols = malloc((*(*(cols) + i) + 1) * sizeof(int));
        int j, k;
        for (j = 0, k=0; j < *(*(cols) + i) + 1; j++, k++) {
            if (j == columnNumber) {
                *(newCols + j) = 0;
                k--;
            } else {
                *(newCols + j) = *(*(*(structure) + i) + k);
            }
        }
        *(*(cols) + i) += 1;
        free(*(*(structure) + i));
        *(*(structure) + i) = newCols;
    }
}

void insertAfterColumn (int*** structure, int* rows, int** cols, int howManyElements, int columnNumber) {
    int i;
    howManyElements = howManyElements > *rows ? *rows : howManyElements;
    for (i = 0; i < howManyElements; i++) {
        int* newCols = malloc((*(*(cols) + i) + 1) * sizeof(int));
        int j, k;
        for (j = 0, k=0; j < *(*(cols) + i) + 1; j++, k++) {
            if (j == columnNumber + 1) {
                *(newCols + j) = 0;
                k--;
            } else {
                *(newCols + j) = *(*(*(structure) + i) + k);
            }
        }
        *(*(cols) + i) += 1;
        free(*(*(structure) + i));
        *(*(structure) + i) = newCols;
    }
}

void swapWithRows (int*** structure, int* rows, int** cols, int firstRow, int secondRow) {
    if (*rows <= firstRow || *rows <= secondRow) {
        return;
    }
    void* ptr = *(*(structure) + firstRow);
    *(*(structure) + firstRow) = *(*(structure) + secondRow);
    *(*(structure) + secondRow) = ptr;

    int swap = *(*(cols) + firstRow);
    *(*(cols) + firstRow) = *(*(cols) + secondRow);
    *(*(cols) + secondRow) = swap;
}

void swapWithColumns (int*** structure, int* rows, int** cols, int firstColumn, int secondColumn) {
    int i;
    for (i = 0; i < *rows; i++) {
        if (*(*(cols) + i) > firstColumn && *(*(cols) + i) > secondColumn) {
            int swap = *(*(*(structure) + i) + firstColumn);
            *(*(*(structure) + i) + firstColumn) = *(*(*(structure) + i) + secondColumn);
            *(*(*(structure) + i) + secondColumn) = swap;
        }
    }
}

void deleteParticularRow (int*** structure, int* rows, int** cols, int row) {
    if (*rows < 1 || row >= *rows) return;
    int i, j;
    int** newStructure = (int**)malloc((*rows - 1) * sizeof(int*));
    int* newCols = malloc((*rows + 1) * sizeof(int));
    for (i = 0, j = 0; i < *rows; i++, j++) {
        if (i == row) {
            j--;
        } else {
            *(newStructure + j) = *(*(structure) + i);
            *(newCols + j) = *(*(cols) + i);
        }
    }
    free(*(*(structure) + row));
    free(*structure);
    free(*cols);
    *rows -= 1;
    *structure = newStructure;
    *cols = newCols;
}

void deleteFirstColumn (int*** structure, int* rows, int** cols) {
    if (*rows < 1) return;
    int i;
    for (i = 0; i < *rows; i++) {
        int j;
        int* newRow = (int*)malloc((*(*(cols) + i) - 1) * sizeof(int));
        for (j = 1; j < *(*(cols) + i); j++) {
            *(newRow + j - 1) = *(*(*(structure) + i) + j);
        }
        if (*(*(cols) + i) > 1) {
            free(*(*(structure) + i));
            *(*(structure) + i) = newRow;
            *(*(cols) + i) -= 1;
        } else {
            free(newRow);
            deleteParticularRow(structure, rows, cols, i);
            i--;
        }
    }
}

void deleteLastColumn (int*** structure, int* rows, int** cols) {
    if (*rows < 1) return;
    int i;
    for (i = 0; i < *rows; i++) {
        int j;
        int* newRow = (int*)malloc((*(*(cols) + i) - 1) * sizeof(int));
        for (j = 0; j < *(*(cols) + i) - 1; j++) {
            *(newRow + j) = *(*(*(structure) + i) + j);
        }
        if (*(*(cols) + i) > 1) {
            free(*(*(structure) + i));
            *(*(structure) + i) = newRow;
            *(*(cols) + i) -= 1;
        } else {
            free(newRow);
            deleteParticularRow(structure, rows, cols, i);
            i--;
        }
    }
}

void removeParticularColumn (int*** structure, int* rows, int** cols, int column) {
    if (*rows < 1) return;
    int i;
    for (i = 0; i < *rows; i++) {
        int j, k;
        int* newRow = (int*)malloc((*(*(cols) + i) - 1) * sizeof(int));
        if (column < *(*(cols) + i)) {
            for (j = 0, k = 0; j < *(*(cols) + i); j++, k++) {
                if (j == column) {
                    k--;
                } else {
                    *(newRow + k) = *(*(*(structure) + i) + j);
                }
            }
            if (*(*(cols) + i) > 1) {
                free(*(*(structure) + i));
                *(*(structure) + i) = newRow;
                *(*(cols) + i) -= 1;
            } else {
                free(newRow);
                deleteParticularRow(structure, rows, cols, i);
                i--;
            }
        }
    }
}



int compare (const char* operation, const char* compare) {
    if ((*operation == *compare) && (*(operation + 1) == *(compare + 1)) && (*(operation + 2) == *(compare + 2))) {
        return 1;
    }
    return 0;
}

void afr(int*** structure, int* rows, int** cols, int* elements, int howManyElements) {
    addFrontRow(structure, rows, cols, howManyElements);
    int i;
    for (i = 0; i < howManyElements; i++) {
        *(*(*(structure) + 0) + i) = *(elements + i);
    }
}

void alr(int*** structure, int* rows, int** cols, int* elements, int howManyElements) {
    addLastRow(structure, rows, cols, howManyElements);
    int i;
    for (i = 0; i < howManyElements; i++) {
        *(*(*(structure)+ *rows - 1) + i) = *(elements + i);
    }
}

void afc (int*** structure, int* rows, int** cols, int* elements, int howManyElements) {
    int extra = 0;
    if (howManyElements > *rows) {
        extra = howManyElements - *rows;
        howManyElements = *rows;
    }
    addFirstColumn(structure, rows, cols, howManyElements, 1);
    int i;
    for (i = 0; i < howManyElements; i++) {
        *(*(*(structure) + i) + 0) = *(elements + i);
    }

    for (i = *rows; i < extra + howManyElements; i++) {
        int *extraElement = malloc(sizeof(int));
        *extraElement = *(elements + i);
        alr(structure, rows, cols, extraElement, 1);
        free(extraElement);
    }
}

void alc (int*** structure, int* rows, int** cols, int* elements, int howManyElements) {
    int extra = 0;
    if (howManyElements > *rows) {
        extra = howManyElements - *rows;
        howManyElements = *rows;
    }
    addLastColumn(structure, rows, cols, howManyElements, 1);
    int i;
    for (i = 0; i < howManyElements; i++) {
        *(*(*(structure) + i) + *(*(cols) + i) - 1) = *(elements + i);
    }

    for (i = *rows; i < extra + howManyElements; i++) {
        int *extraElement = malloc(sizeof(int));
        *extraElement = *(elements + i);
        alr(structure, rows, cols, extraElement, 1);
        free(extraElement);
    }
}

void ibr (int*** structure, int* rows, int** cols, int* elements, int howManyElements, int rowNumber) {
    if (rowNumber >= *rows) return;
    insertBeforeRow(structure, rows, cols, howManyElements, rowNumber);
    int i;
    for (i = 0; i < howManyElements; i++) {
        *(*(*(structure) + rowNumber) + i) = *(elements + i);
    }
}

void iar (int*** structure, int* rows, int** cols, int* elements, int howManyElements, int rowNumber) {
    if (rowNumber >= *rows) return;
    insertAfterRow(structure, rows, cols, howManyElements, rowNumber);
    int i;
    for (i = 0; i < howManyElements; i++) {
        *(*(*(structure) + rowNumber + 1) + i) = *(elements + i);
    }
}

void ibc (int*** structure, int* rows, int** cols, int* elements, int howManyElements, int columnNumber) {
    int i;
    insertBeforeColumn(structure, rows, cols, howManyElements, columnNumber);
    for (i = 0; i < howManyElements; i++) {
        if (i >= *rows) {
            int* element = malloc(sizeof(int));
            *element = *(elements + i);
            alr(structure, rows, cols, element, 1);
            free(element);
        } else {
            if (*(*(cols) + i) - 1 > columnNumber) {
                *(*(*(structure) + i ) + columnNumber) = *(elements + i);
            } else {
                *(*(*(structure) + i ) + (*(*(cols) + i)) - 1) = *(elements + i);
            }
        }
    }
}

void iac (int*** structure, int* rows, int** cols, int* elements, int howManyElements, int columnNumber) {
    int i;
    insertAfterColumn(structure, rows, cols, howManyElements, columnNumber);
    for (i = 0; i < howManyElements; i++) {
        if (i >= *rows) {
            int* element = malloc(sizeof(int));
            *element = *(elements + i);
            alr(structure, rows, cols, element, 1);
            free(element);
        } else {
            if (*(*(cols) + i) - 1 > columnNumber) {
                *(*(*(structure) + i ) + columnNumber + 1) = *(elements + i);
            } else {
                *(*(*(structure) + i ) + ((*(*(cols) + i)) - 1)) = *(elements + i);
            }
        }
    }
}

void swr (int*** structure, int* rows, int** cols, int firstRow, int secondRow) {
    swapWithRows(structure, rows, cols, firstRow, secondRow);
}

void swc (int*** structure, int* rows, int** cols, int firstColumn, int secondColumn) {
    swapWithColumns(structure, rows, cols, firstColumn, secondColumn);
}

void dfr (int*** structure, int* rows, int** cols) {
    deleteParticularRow(structure, rows, cols, 0);
}

void dlr (int*** structure, int* rows, int** cols) {
    deleteParticularRow(structure, rows, cols, *rows - 1);
}

void dfc (int*** structure, int* rows, int** cols) {
    deleteFirstColumn(structure, rows, cols);
}

void dlc (int*** structure, int* rows, int** cols) {
    deleteLastColumn(structure, rows, cols);
}

void rmr (int*** structure, int* rows, int** cols, int row) {
    deleteParticularRow(structure, rows, cols, row);
}

void rmc (int*** structure, int* rows, int** cols, int column) {
    removeParticularColumn(structure, rows, cols, column);
}

void isb (int*** structure, int* rows, int** cols, int** elements, int rowStart, int columnStart, int rowQty, int columnQty) {
    int i, m, o;

    for (i = rowStart, m = 0; i < rowStart + rowQty; i++, m++) {
        int j, k;
        if (i < *rows) {
            int* row = (int*)malloc((*(*(cols) + i) + columnQty) * sizeof(int));
            int newColumnStart = columnStart >= *(*(cols) + i) ? *(*(cols) + i) : columnStart;
            for (j = 0, k = 0, o = 0; j < *(*(cols) + i) + columnQty; j++, k++) {
                    if (j >= newColumnStart && j < newColumnStart + columnQty) {
                        *(row + j) = *(*(elements + m) + o);
                        k--;
                        o++;
                    } else {
                        *(row + j) = *(*(*(structure) + i) + k);
                    }
            }
            *(*(cols) + i) += columnQty;
            free(*(*(structure) + i));
            *(*(structure) + i) = row;
        } else {
            alr(structure, rows, cols, *(elements + m), columnQty);
        }
    }
}

void rmb (int*** structure, int* rows, int** cols, int rowStart, int columnStart, int rowQty, int columnQty) {
    int i, m;
    int maxRow = *rows < rowStart + rowQty ? *rows : rowStart + rowQty;
    for (i = rowStart, m = rowStart; m < maxRow; i++, m++) {
        if (columnStart < *(*(cols) + i)) {
            int j, k;
            int maxColumn = *(*(cols) + i) < columnStart + columnQty ? *(*(cols) + i) : columnStart + columnQty;
            if (*(*(cols) + i) - (maxColumn - columnStart) > 0) {
                int* row = (int*)malloc((*(*(cols) + i) - (maxColumn - columnStart)) * sizeof(int));
                for (j = 0; j < columnStart; j++) {
                    *(row + j) = *(*(*(structure) + i) + j);
                }
                for (j = columnStart + columnQty, k = columnStart; j < *(*(cols) + i); j++, k++) {
                    *(row + k) = *(*(*(structure) + i) + j);
                }
                *(*(cols) + i) = *(*(cols) + i) - (maxColumn - columnStart);
                free(*(*(structure) + i));
                *(*(structure) + i) = row;
            } else {
                rmr(structure, rows, cols, i);
                i--;
            }
        }
    }
}

void prt(int** structure, const int*rows, const int* cols) {
    int i, j;
    for (i = 0; i < *rows; i++) {
        for (j = 0; j < *(cols + i); j++) {
            printf("%d ", *(*(structure + i) + j));
        }
        printf("\n");
    }
}

int main() {
    int* rows = malloc(sizeof(int));
    *rows = 0;
    int* cols = malloc(*rows * sizeof(int));
    int** structure = (int**)malloc(*rows * sizeof(int*));
    char* operation = malloc(4 * sizeof(char));

    scanf("%s", operation);
    while (compare(operation, "END") == 0) {
        if (compare(operation, "AFR") == 1) {
            int howManyElements;
            scanf("%i", &howManyElements);
            int i;
            int* elements = malloc(howManyElements * sizeof(int));
            for (i = 0; i < howManyElements; i++) {
                scanf("%i", elements + i);
            }
            afr(&structure, rows, &cols, elements, howManyElements);
            free(elements);
        } else if (compare(operation, "ALR") == 1) {
            int howMuchElements;
            scanf("%i", &howMuchElements);
            int i;
            int* elements = malloc(howMuchElements * sizeof(int));
            for (i = 0; i < howMuchElements; i++) {
                scanf("%i", elements + i);
            }
            alr(&structure, rows, &cols, elements, howMuchElements);
            free(elements);
        } else if (compare(operation, "AFC") == 1) {
            int howMuchElements;
            scanf("%i", &howMuchElements);
            int i;
            int* elements = malloc(howMuchElements * sizeof(int));
            for (i = 0; i < howMuchElements; i++) {
                scanf("%i", elements + i);
            }
            afc(&structure, rows, &cols, elements, howMuchElements);
            free(elements);
        } else if (compare(operation, "ALC") == 1) {
            int howMuchElements;
            scanf("%i", &howMuchElements);
            int i;
            int* elements = malloc(howMuchElements * sizeof(int));
            for (i = 0; i < howMuchElements; i++) {
                scanf("%i", elements + i);
            }
            alc(&structure, rows, &cols, elements, howMuchElements);
            free(elements);
        } else if (compare(operation, "IBR") == 1) {
            int rowNumber;
            scanf("%i", &rowNumber);
            int howMuchElements;
            scanf("%i", &howMuchElements);
            int i;
            int* elements = malloc(howMuchElements * sizeof(int));
            for (i = 0; i < howMuchElements; i++) {
                scanf("%i", elements + i);
            }
            ibr(&structure, rows, &cols, elements, howMuchElements, rowNumber);
            free(elements);
        } else if (compare(operation, "IAR") == 1) {
            int rowNumber;
            scanf("%i", &rowNumber);
            int howMuchElements;
            scanf("%i", &howMuchElements);
            int i;
            int* elements = malloc(howMuchElements * sizeof(int));
            for (i = 0; i < howMuchElements; i++) {
                scanf("%i", elements + i);
            }
            iar(&structure, rows, &cols, elements, howMuchElements, rowNumber);
            free(elements);
        } else if (compare(operation, "IBC") == 1) {
            int columnNumber;
            scanf("%i", &columnNumber);
            int howMuchElements;
            scanf("%i", &howMuchElements);
            int i;
            int* elements = malloc(howMuchElements * sizeof(int));
            for (i = 0; i < howMuchElements; i++) {
                scanf("%i", elements + i);
            }
            ibc(&structure, rows, &cols, elements, howMuchElements, columnNumber);
            free(elements);
        } else if (compare(operation, "IAC") == 1) {
            int columnNumber;
            scanf("%i", &columnNumber);
            int howMuchElements;
            scanf("%i", &howMuchElements);
            int i;
            int* elements = malloc(howMuchElements * sizeof(int));
            for (i = 0; i < howMuchElements; i++) {
                scanf("%i", elements + i);
            }
            iac(&structure, rows, &cols, elements, howMuchElements, columnNumber);
            free(elements);
        } else if (compare(operation, "SWR") == 1) {
            int firstRow;
            scanf("%i", &firstRow);
            int secondRow;
            scanf("%i", &secondRow);
            swr(&structure, rows, &cols, firstRow, secondRow);
        } else if (compare(operation, "SWC") == 1) {
            int firstColumn;
            scanf("%i", &firstColumn);
            int secondColumn;
            scanf("%i", &secondColumn);
            swc(&structure, rows, &cols, firstColumn, secondColumn);
        } else if (compare(operation, "DFR") == 1) {
            dfr(&structure, rows, &cols);
        } else if (compare(operation, "DLR") == 1) {
            dlr(&structure, rows, &cols);
        } else if (compare(operation, "DFC") == 1) {
            dfc(&structure, rows, &cols);
        } else if (compare(operation, "DLC") == 1) {
            dlc(&structure, rows, &cols);
        } else if (compare(operation, "RMR") == 1) {
            int row;
            scanf("%i", &row);
            rmr(&structure, rows, &cols, row);
        } else if (compare(operation, "RMC") == 1) {
            int column;
            scanf("%i", &column);
            rmc(&structure, rows, &cols, column);
        } else if (compare(operation, "ISB") == 1) {
            int rowStart;
            scanf("%i", &rowStart);
            int columnStart;
            scanf("%i", &columnStart);
            int rowQty;
            scanf("%i", &rowQty);
            int columnQty;
            scanf("%i", &columnQty);
            int i;
            int** elements = (int**)malloc(rowQty * sizeof(int*));
            for (i = 0; i < rowQty; i++) {
                *(elements + i) = (int*)malloc(columnQty * sizeof(int));
                int j;
                for (j = 0; j < columnQty; j++) {
                    scanf("%i", (*(elements + i) + j));
                }
            }
            isb(&structure, rows, &cols, elements, rowStart, columnStart, rowQty, columnQty);
            for (i = 0; i < rowQty; i++) {
                free(*(elements + i));
            }
            free(elements);
        } else if (compare(operation, "RMB") == 1) {
            int rowStart;
            scanf("%i", &rowStart);
            int rowQty;
            scanf("%i", &rowQty);
            int columnStart;
            scanf("%i", &columnStart);
            int columnQty;
            scanf("%i", &columnQty);
            rmb(&structure, rows, &cols, rowStart, columnStart, rowQty, columnQty);
        } else if (compare(operation, "PRT") == 1) {
            prt(structure, rows, cols);
        }
        fflush(stdin);
        scanf("%s", operation);
    }

    while (*rows > 0) {
        dfr(&structure, rows, &cols);
    }
    free(structure);
    free(operation);
    free(rows);
    free(cols);
    return 0;
}
