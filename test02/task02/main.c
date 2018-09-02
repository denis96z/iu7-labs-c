#include <stdio.h>
#include <string.h>

#define MAX_SENTENCES 100


int readData(char *fileName, char sentences[MAX_SENTENCES][255], int *n)
{
    FILE *f = fopen(fileName, "r");

    if (!f)
    {
        return 1;
    }

    char c;

    int counter = 0;
    int p = -1;
    while (!feof(f))
    {
        p++;
        fscanf(f, "%c", &c);

        sentences[counter][p] = c;
        if (c == '\n')
        {
            sentences[counter][p + 1] = '\0';
            counter++;
            p = -1;
        }
    }

    *n = counter + 1;

    return 0;
}


int seekKey(char sentences[MAX_SENTENCES][255], int n, char letters[2][26])
{
    char current[MAX_SENTENCES][255];
    char keySnt[255] = "the quick brown fox jumps over the lazy dog";
    char keySentence[MAX_SENTENCES][255] = { "the",
                                             "quick",
                                             "brown",
                                             "fox",
                                             "jumps",
                                             "over",
                                             "the",
                                             "lazy",
                                             "dog" };
    int keyIndex = -1;

    for (int i = 0; i < n; i++)
    {
        int counter = sscanf(sentences[i], "%s%s%s%s%s%s%s%s%s", current[0],
            current[1], current[2], current[3], current[4], current[5], current[6],
            current[7], current[8]);

        if (counter != 9)
        {
            continue;
        }

        int result = 1;

        for (int j = 0; j < counter; j++)
        {
            if (strlen(keySentence[j]) != strlen(current[j]))
            {
                result = 0;
                break;
            }
        }
        if (result == 1)
        {
            keyIndex = i;
            break;
        }
    }

    if (keyIndex > -1)
    {
        for (int i = 0; i < strlen(sentences[keyIndex]); i++)
        {
            for (int k = 0; k < 26; k++)
            {
                if (sentences[keyIndex][i] == letters[0][k])
                {
                    letters[1][k] = keySnt[i];
                    break;
                }
            }
        }
    }

    return keyIndex;
}


void decodeSentences(char sentences[MAX_SENTENCES][255], int n, char letters[2][26])
{
    FILE *f = fopen("out.txt", "w");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < strlen(sentences[i]); j++)
        {
            for (int k = 0; k < 26; k++)
            {
                if (sentences[i][j] == ' ')
                {
                    fprintf(f, "%c", ' ');
                    break;
                }
                if (letters[0][k] == sentences[i][j])
                {
                    fprintf(f, "%c", letters[1][k]);
                    break;
                }
            }
        }
        fprintf(f, "\n");
    }
    fclose(f);
}


int main()
{
    char fileName[255];
    printf("Input file name: ");
    scanf("%s", fileName);

    char sentences[MAX_SENTENCES][255];
    int n = -1;

    readData(fileName, sentences, &n);

    char letters[2][26];

    int counter = 0;
    for (char c = 'a'; c <= 'z'; c++)
    {
        letters[0][counter] = c;
        letters[1][counter] = ' ';
        counter++;
    }

    if (seekKey(sentences, n, letters) > -1)
    {
        decodeSentences(sentences, n, letters);
        printf("File created.");
    }

    return 0;
}
