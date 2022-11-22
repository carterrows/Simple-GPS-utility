// Mini Project 2
// Made by Carter Rows
// November 2022

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

typedef struct position
{
    char name[50];
    double distance;
} position;

user scanUser();
void scanOtherUsers(user temp[], int n);
void findDistances(user origin, user temp1[], position temp2[], int n);
position findClosestUser(position temp2[], int n);

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
    scanf("%s", choice);

    if(strcmp(choice, f) == 0)
    {
        char fileName[50];
        printf("Enter file name for the data:\t");
        scanf("%s", fileName);
    }

    else if(strcmp(choice, m) == 0)
    {
        printf("\nInput number of other users:\t");
        scanf("%d", &userCount);

        user otherUsers[userCount];

        scanOtherUsers(otherUsers, userCount);

        position otherUserPosition[userCount];

        findDistances(myUser, otherUsers, otherUserPosition, userCount);

        position closestUser;
        closestUser = findClosestUser(otherUserPosition, userCount);

        printf("\nThe closest user to %s is:\n\n", myUser.name);
        printf("Name:\t%s", closestUser.name);
        printf("\nDistance:\t%lf\n\n", closestUser.distance);
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

void findDistances(user origin, user temp1[], position temp2[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        strcpy(temp2[i].name, temp1[i].name);

        temp2[i].distance = sqrt((origin.longtitude - temp1[i].longtitude)*(origin.longtitude - temp1[i].longtitude) + (origin.latitude - temp1[i].latitude)*(origin.latitude - temp1[i].latitude) + (origin.altitude - temp1[i].altitude)*(origin.altitude - temp1[i].altitude));
    }
}

position findClosestUser(position temp2[], int n)
{
    position temp;
    temp = temp2[0];
    
    for(int i = 1; i < n; ++i)
    {
        if(temp2[i].distance < temp.distance)
        {
            temp = temp2[i];
        }
    }

    return temp;
}