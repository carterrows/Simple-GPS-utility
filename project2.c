// Mini Project 2
// Made by Carter Rows
// November 2022

// MAYBE USEFUL LATER:
//  printf("User:\t%s\n", ourUser.name);
//  printf("Longtitude:\t%lf\n", ourUser.longtitude);
//  printf("Latitude:\t%lf\n", ourUser.latitude);
//  printf("Altitude:\t%lf\n", ourUser.altitude);
//  printf("Time:\t%lf\n", ourUser.time);

#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct user
{
    char name[50];
    double longtitude;
    double latitude;
    double altitude;
    double time;
} user;

user scanUser();
void scanOtherUsers(user temp[], int n);

int main()
{
    printf("\nWelcome to my GPS Utility!\n");
    printf("Please input your data:\n\n");

    user myUser;
    myUser = scanUser();

    printf("\n%s's data:\n", myUser.name);
    printf("\nLongtitude = %lf", myUser.longtitude);
    printf("\nLatitude = %lf", myUser.latitude);
    printf("\nAltitude = %lf", myUser.altitude);
    printf("\nTime = %lf\n", myUser.time);
    
    int userCount;
    char choice[10];
    char f[10] = "file";
    char m[10] = "manual";
    printf("\nWould you like to manually enter other user data or use a file?\nPlease type 'file' or 'manual'\n\n");
    scanf("%s", &choice);

    if(strcmp(choice, f) == 0)
    {
        char fileName[50];
        printf("Enter file name for the data:\t");
        scanf("%s", &fileName);
    }

    else if(strcmp(choice, m) == 0)
    {
        printf("\nInput number of other users:\t");
        scanf("%d", &userCount);

        user otherUsers[userCount];

        scanOtherUsers(otherUsers, userCount);

        printf("\nUser 1's data:\n\n");
        printf("Name: %s", otherUsers[0].name);
        printf("\nLongtitude = %lf", otherUsers[0].longtitude);
        printf("\nLatitude = %lf", otherUsers[0].latitude);
        printf("\nAltitude = %lf", otherUsers[0].altitude);
        printf("\nTime = %lf\n", otherUsers[0].time);

    }

    else
    {
        printf("Please input a valid choice.\n\n");
    }
    
    return 0;
}

user scanUser()
{
    user temp;
    
    printf("Please input name:\t");
    scanf("%s", temp.name);

    printf("Please input longtitude:\t");
    scanf("%lf", &temp.longtitude);

    printf("Please input latitude:\t");
    scanf("%lf", &temp.latitude);

    printf("Please input altitude:\t");
    scanf("%lf", &temp.altitude);

    printf("Please input time:\t");
    scanf("%lf", &temp.time);

    return temp;
}

void scanOtherUsers(user temp[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("\n");
        temp[i] = scanUser();
    }
}