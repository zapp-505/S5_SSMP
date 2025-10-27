#include <stdio.h>
#include <string.h>
#include <stdlib.h>

///////////////////////////////////////////////
// FUNCTION: Check if a label exists in SYMTAB
///////////////////////////////////////////////
int searchSymtab(char label[])
{
    char symbol[10];
    FILE *symtab;
    int value;
    symtab = fopen("symtab.txt", "r");

    while (!feof(symtab))
    {
        fscanf(symtab, "%s %d", symbol, &value);
        if (!strcmp(label, symbol))
        {
            fclose(symtab);
            return 1; // Symbol already exists
        }
    }
    fclose(symtab);
    return 0; // Symbol not found
}

/////////////////////////////////////////////////
// FUNCTION: Check if opcode exists in OPTAB
/////////////////////////////////////////////////
int searchOpcode(char opcode[])
{
    FILE *optab;
    char op[10];
    optab = fopen("optab.txt", "r");

    while (!feof(optab))
    {
        fscanf(optab, "%s", op);
        if (!strcmp(op, opcode))
        {
            fclose(optab);
            return 1; // Opcode exists
        }
    }
    fclose(optab);
    return 0; // Opcode not found
}

/////////////////////////////////////////////////
// MAIN FUNCTION : PASS ONE IMPLEMENTATION
/////////////////////////////////////////////////
int main()
{
    FILE *in, *out, *sym;
    int sA, locctr, op;
    char label[10], opcode[10], operand[10];

    // STEP 1: Open required files
    in = fopen("input.txt", "r");
    out = fopen("intermediate.txt", "w");
    sym = fopen("symtab.txt", "w"); // Clear SYMTAB
    fclose(sym);

    ////////////////////////////////////////////
    // STEP 2: Read first line and check START
    ////////////////////////////////////////////
    if (!feof(in))
    {
        fscanf(in, "%s%s%d", label, opcode, &op);

        if (!strcmp(opcode, "START"))
        {
            sA = op;     // Save starting address
            locctr = op; // Initialize LOCCTR
            fprintf(out, "%s %s %s %d\n", " - ", label, opcode, op);
        }
        else
        {
            locctr = 0; // No START
            sA = 0;
        }
    }

    ////////////////////////////////////////////////
    // STEP 3: Process each line until END opcode
    ////////////////////////////////////////////////
    while (!feof(in))
    {
        fscanf(in, "%s%s%s", label, opcode, operand);
        fprintf(out, "%d %s %s %s\n", locctr, label, opcode, operand);

        ////////////////////////////////////////////
        // Case 1: No LABEL (label = "**")
        ////////////////////////////////////////////
        if (!strcmp(label, "**"))
        {
            if (!strcmp(opcode, "END"))
                break;
            else if (searchOpcode(opcode))
                locctr += 3;
            else if (!strcmp(opcode, "WORD"))
                locctr += 3;
            else if (!strcmp(opcode, "RESW"))
                locctr += 3 * atoi(operand);
            else if (!strcmp(opcode, "RESB"))
                locctr += atoi(operand);
            else if (!strcmp(opcode, "BYTE"))
            {
                if (operand[0] == 'C')
                    locctr += strlen(operand) - 3;
                else if (operand[0] == 'X')
                /*as hexa stored as halfbytes*/
            }
            else
                printf("Opcode error for %s\n", opcode);
        }
        ////////////////////////////////////////////
        // Case 2: LABEL is present
        ////////////////////////////////////////////
        else
        {
            // Check for duplicate symbol
            if (searchSymtab(label))
            {
                printf("Symbol Error\n");
            }
            else
            {
                // Case: OPCODE is valid
                if (searchOpcode(opcode))
                {
                    locctr += 3;
                }
                // Case: WORD directive
                else if (!strcmp(opcode, "WORD"))
                {
                    sym = fopen("symtab.txt", "a");
                    fprintf(sym, "%s %d\n", label, locctr);
                    fclose(sym);
                    locctr += 3;
                }
                // Case: RESW directive
                else if (!strcmp(opcode, "RESW"))
                {
                    sym = fopen("symtab.txt", "a");
                    fprintf(sym, "%s %d\n", label, locctr);
                    fclose(sym);
                    op = atoi(operand);
                    op *= 3;
                    locctr += op;
                }
                // Case: BYTE directive
                else if (!strcmp(opcode, "BYTE"))
                {
                    sym = fopen("symtab.txt", "a");
                    fprintf(sym, "%s %d\n", label, locctr);
                    fclose(sym);
                    locctr += (strlen(operand) - 3); // Exclude C' '
                }
                // Case: RESB directive
                else if (!strcmp(opcode, "RESB"))
                {
                    sym = fopen("symtab.txt", "a");
                    fprintf(sym, "%s %d\n", label, locctr);
                    fclose(sym);
                    op = atoi(operand);
                    locctr += op;
                }
                // Invalid opcode
                else
                {
                    printf("opcode error");
                }
            }
        }
    }

    ///////////////////////////////////////////
    // STEP 4: PRINT PROGRAM LENGTH
    ///////////////////////////////////////////
    printf("length = %d\n", locctr - sA);

    // STEP 5: Close files
    fclose(in);
    fclose(out);

    return 0;
}