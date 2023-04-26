#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int countLetters(string text, int length);
int countWords(string text, int length);
int countSentences(string text, int length);
int defineGrade(float letters, float words, float sentences);
void response(int grade);

int main(void)
{
    string text = get_string("Text: ");
    int length = strlen(text);
    // count propely
    int letters = countLetters(text, length);
    int words = countWords(text, length);
    int sentences = countSentences(text, length);
    // define grade
    int grade = defineGrade(letters, words, sentences);

    response(grade);
}

int countLetters(string text, int length)
{
    int lettersNum = 0;
    for (int i = 0; i < length; i++)
    {
        int c = (int)text[i];
        //     !         '           ,          " "         .         ?
        if (c != 33 && c != 39 && c != 44 && c != 32 && c != 46 && c != 63)
        {
            lettersNum++;
        }
        else
        {
            continue;
        }
    }
    return lettersNum;
}

int countWords(string text, int length)
{
    int wordsNum = 0;
    for (int i = 0; i < length; i++)
    {
        int c = (int)text[i];
        //      " "
        if (c == 32)
        {
            wordsNum++;
        }
        else
        {
            continue;
        }
    }
    // added 1 because last char doesn't exist
    return wordsNum + 1;
}

int countSentences(string text, int length)
{
    int sentNum = 0;
    for (int i = 0; i < length; i++)
    {
        int c = (int)text[i];
        //      .         !          ?
        if (c == 46 || c == 33 || c == 63)
        {
            sentNum++;
        }
        else
        {
            continue;
        }
    }
    return sentNum;
}



int defineGrade(float letters, float words, float sentences)
{
    // grade, letters, sentences and words number definition;
    float grade = 0;

    // printf("L is: %f,\nW is: %f,\nS is: %f.\n", (float)letters, (float)words, (float)sentences);

    letters = (letters * 100) / words;
    sentences = (sentences * 100) / words;

    // grade formula
    grade = round(0.0588 * letters - 0.296 * sentences - 15.8);

    return grade;
}

void response(int grade)
{
    if (grade > 16)
    {
        printf("Grade 16+");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1");
    }
    else if (1 <= grade && grade <= 16)
    {
        printf("Grade %i", grade);
    }
    else
    {
        printf("IDK!!");
    }

    printf("\n");
}