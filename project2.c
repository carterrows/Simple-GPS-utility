// Mini Project 2
// For ENGG1410
// Made by Carter Rows - 1170615
// November 2022

// include required libraries
#include <stdio.h>
#include <string.h>
#include <math.h>

// define max size for our users struct array
#define MAX 100

// first array type for a single user
typedef struct user
{
    char name[50];
    double longtitude;
    double latitude;
    double altitude;
    double time;
} user;

// second array type to hold name and relative distance from local user
typedef struct position
{
    char name[50];
    double distance;
} position;

// function prototypes
user scanUser();
void scanOtherUsers(user temp[], int n);
void findDistances(user origin, user temp1[], position temp2[], int n);
position findClosestUser(position temp2[], int n);
int scanFile(user fileData[], char fileName[]);

int main()
{
    // print welcome messages
    printf("\nWelcome to my GPS Utility!\n");
    printf("Please input your data:\n\n");

    // declare local user structure
    user myUser;
    // scan data into local user stucture using "scanUser" function
    myUser = scanUser();

    printf("\n%s's data successfully collected.\n", myUser.name);
    
    // declare a few required variables & constants
    int userCount;
    char choice[10];
    
    // prompt for manual or file data collection
    printf("\nWould you like to manually enter other user data or use a file?\nPlease type 'file' or 'manual'\n\n");
    scanf("%s", choice);

    // path if user wants to use file data collection
    if(strcmp(choice, "file") == 0)
    {
        // collect file name
        char fileName[50];
        printf("\nEnter file name for the data:\t");
        scanf("%s", fileName);

        // declare an array of structures to hold other user data
        user otherUsers[MAX];

        // scan other user data using "scanFile" function
        // also returns the number of users
        int userCount = scanFile(otherUsers, fileName);

        // declare a position structure array of size user count
        position otherUserPosition[userCount];

        // find all distances of other users from local user, store in otherUserPosition array
        findDistances(myUser, otherUsers, otherUserPosition, userCount);

        // now declare a single structure that holds the data for the closest user
        position closestUser;
        // this finds the closest user and scans data into the struct declared above
        closestUser = findClosestUser(otherUserPosition, userCount);

        // finally print all the data for the closest user
        printf("\nThe closest user to %s is:\n\n", myUser.name);
        printf("Name:\t%s", closestUser.name);
        printf("\nDistance:\t%.3lf\n\n", closestUser.distance);
    }

    // path if user wants to use manual data collection
    else if(strcmp(choice, "manual") == 0)
    {
        // prompt for number of other users
        printf("\nInput number of other users:\t");
        scanf("%d", &userCount);

        // check if 0 users is inputted
        if(userCount == 0)
        {
            printf("\nPlease input valid number of users.\n\n");
            return 0;
        }

        // all of this below is the same process as above
        user otherUsers[userCount];

        scanOtherUsers(otherUsers, userCount);

        position otherUserPosition[userCount];

        findDistances(myUser, otherUsers, otherUserPosition, userCount);

        position closestUser;
        closestUser = findClosestUser(otherUserPosition, userCount);

        printf("\nThe closest user to %s is:\n\n", myUser.name);
        printf("Name:\t%s", closestUser.name);
        printf("\nDistance:\t%.3lf\n\n", closestUser.distance);
    }

    // if user does not enter file or manual data collection
    else
    {
        printf("Please input a valid choice.\n\n");
    }
    
    return 0;
}

// function to scan a single user and returns a struct holding their data
// does not take any arguments
user scanUser()
{
    user temp;
    
    // collect information
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

    // return filled struct
    return temp;
}

// function to scan other users manually
// must have a struct array and size in argument
void scanOtherUsers(user temp[], int n)
{
    // collect individual information until struct array is filled
    for(int i = 0; i < n; ++i)
    {
        printf("\n");
        temp[i] = scanUser();
    }
}

// function to find distances of other users relative to local user
// passes the local user struct, the other users struct array, and a position array, all arrays have size "user count"
void findDistances(user origin, user temp1[], position temp2[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        // fill all of the name data 
        strcpy(temp2[i].name, temp1[i].name);
        // now fill the distance data for all of the other users
        temp2[i].distance = sqrt((origin.longtitude - temp1[i].longtitude)*(origin.longtitude - temp1[i].longtitude) + (origin.latitude - temp1[i].latitude)*(origin.latitude - temp1[i].latitude) + (origin.altitude - temp1[i].altitude)*(origin.altitude - temp1[i].altitude));
    }
}

// function that returns the closest user to the local user
// passes the struct array of all distance data of other users
position findClosestUser(position temp2[], int n)
{
    // assume closest user is the first of the other users
    position temp;
    temp = temp2[0];
    
    // now for all the other users, check if they are closer
    // if they are, set the temp struct to he closest user
    for(int i = 1; i < n; ++i)
    {
        if(temp2[i].distance < temp.distance)
        {
            temp = temp2[i];
        }
    }

    // return structure of closet user
    return temp;
}

// function to scan data from file
// passes the file name and an empty struct array for the user data
int scanFile(user fileData[], char fileName[])
{
    // open the file in read
    FILE *fptr = fopen(fileName, "r");

    // scan user count from file
    int count;
    fscanf(fptr, "%d", &count);

    // scan data for "count" users
    for(int i = 0; i < count; ++i)
    {
        fscanf(fptr, "%s", fileData[i].name);
        fscanf(fptr, "%lf", &fileData[i].longtitude);
        fscanf(fptr, "%lf", &fileData[i].latitude);
        fscanf(fptr, "%lf", &fileData[i].altitude);
        fscanf(fptr, "%lf", &fileData[i].time);
    }

    // return the user count for future use
    return count;
}
