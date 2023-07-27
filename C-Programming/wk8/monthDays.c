#include <stdio.h>
#include <stdbool.h>
#define string char*

typedef enum month {
    Jan, Feb, Mar, Apr, May, June, July,
    Aug, Sept, Oct, Nov, Dec
} month;


typedef struct date {
    month name;
    int lastDate;
} date;

// Return day count of exceptions, default is 30
int dayCount(month query);

// Return next month
month nextMonth(month query, bool cycleThrough);

// Check is valid
bool isValid(month query) {
    bool output = query <= 12;
    return output;
}

// Helper method to return list of configured months
date * configureMonths();

int main() {
    
    // Init vars
    date months[12];

    // Configure months
    printf("\nConfiguring Months:\n");
    for ( int i = -1; i < 11; i++) {
        
        // Init vars
        date myMonth;
        month current;
        int lastDay;

        // Fetch month
        current = nextMonth(i, false);
        myMonth.name = current;
        printf("Current month:\t%d\n", current);
        
        // Fetch last day
        lastDay = dayCount(current);
        myMonth.lastDate = lastDay;
        printf("Last day:\t%d\n\n", lastDay);

        // Append to date arr
        months[i+1] = myMonth;
    }

    // Print first month
    printf("\nLast day of second month is '%d', id is '%d'\n\n", months[1].lastDate, months[1].name);
    return 0;
}


/**
 * Print next month, allowing for continous flow through or ceasing
*/
month nextMonth(month query, bool cycleThrough) {
    switch(cycleThrough) {
        case true:
            if ( query == 12 ) {
                return Jan;
            }
            return query+1;
            break;
        
        default:
            return (query + 1 % 12);
    }
}

/**
 * Return day count for month
*/
int dayCount(month query) {
    switch (query) {
        case Sept:
            return 30; break;

        case Apr:
            return 30; break;
        
        case June:
            return 30; break;
        
        case Nov:
            return 30; break;
        
        case Feb:
            return 28; break;
        
        default:
            return 31;
    }
}



date* configureMonths() {

    // Init vars
    date months[12];
    date myMonth;

    // Configure months
    for ( int i = -1; i <= 12; i++) {
        month current = nextMonth(i, false);
        myMonth.name = current;
        myMonth.lastDate = dayCount(myMonth.name);
    }

    return months;
}