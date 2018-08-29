/*
RMIT University Vietnam
Course: EEET2448 Computing Engineering
Semester: 2018A
Lecturer: Mr. Quang Tran
Assessment: Group Project
Author: Luong Tan Huy s3726121
Group: 8
Created date: 25/05/2018
Acknowledgment: https://www.youtube.com/watch?v=5wzmEKjNqiU
*/
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
////////////////////////////////////////////////////////////////////////////////
//                  global variables declaration                               //
////////////////////////////////////////////////////////////////////////////////

const int STEP = 100; //the size of each memory allocation

//to store in numerical command line argument values
int from_age, to_age;
float from_weight, to_weight, from_income, to_income;

////////////////////////////////////////////////////////////////////////////////
//                  Local function                                            //
////////////////////////////////////////////////////////////////////////////////

//loadfile() allocates memory and stores records further it reads into bigdata.txt
char **loadfile(FILE *fptr, int *flength) {
    //local variable declaration
    int arr_length = 0;
    int lines_count = 0;
    char buf[100];

    //initialize char ** as NULL so that the first realloc behaves like a malloc
    char **lines = NULL;

    //read into bigdata and allocate memory as we read
    //each record is stored into a buffer
    while (fgets(buf, 100, fptr) != NULL) {

        //check if char ** is full, then reallocate more memory if it is
        if (lines_count == arr_length) {
            //increment by the value of STEP
            arr_length += STEP;
            //reallocate xSTEP char* of memory each time
            char **newlines = realloc(lines, arr_length * sizeof(char *));
            if (newlines == NULL) {
                printf("Error! Cannot allocate more memory\nExit program\n");
                exit(1);
            }
            //assign back the new address to the old address
            lines = newlines;
        }

        //trim off the newline char in buffer
        buf[strlen(buf) - 1] = '\0';

        //get buffer size
        int buf_length = strlen(buf);

        //allocate memory for 1 record
        char *str1 = (char *) malloc((buf_length + 1) * sizeof(char));

        //copy string from buffer to record
        strcpy(str1, buf);

        //add record to the array for records
        lines[lines_count] = str1;

        //increment lines counter
        lines_count++;

    }

    //return the number of records
    *flength = lines_count;

    return lines;
}

////////////////////////////////////////////////////////////////////////////////

//extractargword() extracts each word in the "name" command line argument
char *extractargword(const char *ip, int *index) {
    //local variable declaration
    char buf[25];
    int j = 0;
    int i = *index;

    //store into a buffer
    while ((islower(ip[i]) == 1) || (isupper(ip[i]) == 1))  {
        buf[j] = ip[i];
        j++;
        i++;
    }

    //add null char
    buf[j] = '\0';

    //increment the index if char is space
    if (ip[i] == 32) {
        i++;
    }

    //get buffer length
    int buf_length = strlen(buf);

    //allocate memory for string
    char *str2 = (char *) malloc((buf_length + 1) * sizeof(char));

    //copy buffer into string
    strcpy(str2, buf);

    //return index value
    *index = i;

    return str2;
}

////////////////////////////////////////////////////////////////////////////////

//extractargnum() reads and stores numerical values in the command line
void extractargnum(const char **ip) {

    from_age = atoi(ip[2]);
    to_age = atoi(ip[3]);

    from_weight = atof(ip[4]);
    to_weight = atof(ip[5]);

    from_income = atof(ip[6]);
    to_income = atof(ip[7]);

}

////////////////////////////////////////////////////////////////////////////////

//extractname() extracts "name" in each record from bigdata
char *extractname(char *ip, int *index) {
    //local variable declaration
    char buf[50];
    int i = *index;

    //store name into a buffer
    while (isdigit(ip[i]) == 0) {
        buf[i] = ip[i];
        i++;
    }

    //trim off the space char in buffer
    buf[i - 1] = '\0';

    //get buffer length
    int buf_length = strlen(buf);

    //allocate memory for name
    char *str3 = (char *) malloc((buf_length + 1) * sizeof(char));

    //copy buffer into name
    strcpy(str3, buf);

    //return the index's value
    *index = i;

    return str3;
}

////////////////////////////////////////////////////////////////////////////////

//extractage() extracts "age" in each record from bigdata
int extractage(char *ip, int *index) {
    //local variable declaration
    char buf[5];
    int i = 0;
    int j = *index;

    //store age into a buffer
    while (isspace(ip[j]) == 0) {
        buf[i] = ip[j];
        i++;
        j++;
    }

    //copy buffer into age
    int age = atoi(buf);

    //return the index's value
    *index = j;

    return age;
}

////////////////////////////////////////////////////////////////////////////////

//extractweight() extracts "weight" in each record from bigdata
float extractweight(char *ip, int *index) {
    //local variable declaration
    char buf[7];
    int i = 0;
    int j = *index;
    //move index to the next digit char
    j++;

    //store weight into a buffer
    while (isspace(ip[j]) == 0) {
        buf[i] = ip[j];
        i++;
        j++;
    }

    //copy buffer into weight
    float weight = atof(buf);

    //return the index's value
    *index = j;

    return weight;
}

////////////////////////////////////////////////////////////////////////////////

//extractincome() extracts "income" in each record from bigdata
float extractincome(char *ip, int *index) {
    //local variable declaration
    char buf[10];
    int i = 0;
    int j = *index;
    //move index to the next digit char
    j++;

    //store weight into a buffer
    while (ip[j] != '\0') {
        buf[i] = ip[j];
        i++;
        j++;
    }

    //copy buffer into income
    float income = atof(buf);

    return income;
}

////////////////////////////////////////////////////////////////////////////////

//countargwords() counts the number of words in the "name" command line argument
int countargwords(const char *ip) {
    int count = 1;
    int i = 0;

    while (ip[i] != '\0') {
        if (ip[i] == 32) {
            count++;
        }
        i++;
    }

    return count;
}

////////////////////////////////////////////////////////////////////////////////

//mystrcmp() compares two strings, returns 1 when string1 contains string2
int mystrcmp(char *ip, char *ip1) {
    //local variable declaration
    int j = 0;
    int size = strlen(ip);
    int size1 = strlen(ip1);
    char temp[size1 + 1];

    //strings cascade compare
    while (j <= (size - size1)) {
        //store part of string1 into a temporary string which has string2 size
        for (int i = 0; i <= size1; i++) {
            temp[i] = ip[i + j];
            if (i == size1) {
                temp[i] = '\0';
            }
        }

        //compare temp with string2
        if (strcmp(temp, ip1) == 0) {
            return 1;
            exit(1);
        }

        //increment the cascade
        j++;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

//agecmp() compares command line arg "age" and record "age"
int agecmp(int age) {
    if (from_age == 0 && to_age == 0) {
        return 1;
    } else if (from_age == 0) {
        if (age <= to_age) {
            return 1;
        } else {
            return 0;
        }
    } else if (to_age == 0) {
        if (age >= from_age) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (from_age <= age && age <= to_age) {
            return 1;
        } else {
            return 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

//weightcmp() compares command line arg "weight" and record "weight"
int weightcmp(float weight) {
    if (from_weight == 0 && to_weight == 0) {
        return 1;
    } else if (from_weight == 0) {
        if (weight <= to_weight) {
            return 1;
        } else {
            return 0;
        }
    } else if (to_weight == 0) {
        if (weight >= from_weight) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (from_weight <= weight && weight <= to_weight) {
            return 1;
        } else {
            return 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

//incomecmp() compares command line arg "income" and record "income"
int incomecmp(float income) {
    if (from_income == 0 && to_income == 0) {
        return 1;
    } else if (from_income == 0) {
        if (income <= to_income) {
            return 1;
        } else {
            return 0;
        }
    } else if (to_income == 0) {
        if (income >= from_income) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (from_income <= income && income <= to_income) {
            return 1;
        } else {
            return 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

//recordcmp() compares each record with the command line argument
int recordcmp(char *ip, const char *ip1, int word_count) {

    //extract data from record
    int i = 0, j = 0;
    char *name = extractname(ip, &i);
    int age = extractage(ip, &i);
    float weight = extractweight(ip, &i);
    float income = extractincome(ip, &i);

    //compare each word in argv[1] with the command line name entry
    i = 0;
    while (j < word_count) {
        //extract each words in argv[1]
        char *argv_word = extractargword(ip1, &i);
        //compare each argv_word with record entry
        if (mystrcmp(name, argv_word) == 0) {
            return 0;
            exit(1);
        }
        //increment if strings match
        j++;
    }

    //compare age
    if (agecmp(age) == 0) {
        return 0;
        exit(1);
    }

    //compare weight
    if (weightcmp(weight) == 0) {
        return 0;
        exit(1);
    }

    //compare income
    if (incomecmp(income) == 0) {
        return 0;
        exit(1);
    }

    return 1;
}

////////////////////////////////////////////////////////////////////////////////
//                  main                                                      //
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
    //variables declaration
    int rec_line = 0;
    int result = 0;
    int word_count = countargwords(argv[1]);

    //check command line format
    if (argc != 8) {
        printf("Error! wrong format in command lines\nExit program\n");
        exit(1);
    }

    //read and store numerical command line arguments
    extractargnum(argv);

    //read and compare each record in bigdata, then write results in records found
    FILE *fptr = fopen("bigdata.txt", "r");
    FILE *fptr1 = fopen("records found.txt", "w");

    if ((fptr == NULL) || (fptr1 == NULL)) {
        printf("Error! bigdata.txt not found or cannot create output text file\nExit program\n");
        exit(1);
    }

    char **data = loadfile(fptr, &rec_line);

    //test each record for rec_line records
    for (char **ip = data; ip <= &data[rec_line - 1]; ip++) {
        if (recordcmp(*ip, argv[1], word_count) == 1) {
            //write in output file
            fprintf(fptr1, "%s\n", *ip);
            result++;
        }
    }

    //print result
    printf("Task completed!\n%d record(s) found\nSee results in output text file\n", result);

    //free up allocated memory
    free(data);
    data = NULL;

    fclose(fptr);
    fclose(fptr1);

    return 0;
}
