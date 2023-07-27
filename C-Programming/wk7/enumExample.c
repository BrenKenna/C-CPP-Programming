#include <stdio.h>
#define string char*

// weekend
enum day {
    Saturday,
    Sunday
};

void printDay(enum day d) {
    switch(d) {
        case Saturday:
            printf("Saturday");
            break;

        case Sunday:
            printf("Sunday");
            break;
        
        default:
            printf("Error: Day '%d' not in week", d);
    }
}

enum day nextDay(enum day d) {
    switch(d) {
        case Saturday:
            return Sunday;
            break;

        default:
            return Saturday;
    }
}

enum day nextDayOther(enum day d) {
    if ( d == 1) {
        return Saturday;
    }
    return d + 1;
}

char* toString(enum day d) {
    switch(d) {
        case Saturday:
            return "Saturday";
            break;

        case Sunday:
            return "Sunday";
            break;
        
        default:
            return "NULL";
    }
}

int main() {
    
    // Simple
    enum day myDay = Sunday;
    printf("\nMy day is:\t\t\t%s", toString(myDay));

    // Print all
    printf("\nThe day is:\t\t\t");
    printDay(myDay);

    // Next day
    enum day theNextDay = nextDay(myDay);
    printf("\nThe next day is:\t\t%s", toString(theNextDay));
    theNextDay = nextDay(theNextDay);
    printf("\nThe next day is:\t\t%s", toString(theNextDay));

    // Next day like class
    enum day theOtherNextDay = nextDayOther(theNextDay);
    printf("\nThe other next day is:\t\t%s", toString(theOtherNextDay));
    theOtherNextDay = nextDayOther(theOtherNextDay);
    printf("\nThe other next day is:\t\t%s", toString(theOtherNextDay));

    // Print string of dat
    string test = toString(myDay);
    printf("\nTesting mock string type:\t%s\n\n", test);


    enum month{jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};
    
    enum month next_month(enum month m)
    {
        return((m + 1) % 12);
    }
    
    printf("%u\n", next_month(dec + 1));

    // End
    return 0;
}