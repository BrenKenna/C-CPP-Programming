/**
 * Uses custom types for modelling days of a month
 * 
 * A month is enum, date is struct. The date structure, has a
 *  last date member allowing each month to iterated up to this value
*/

#include <stdio.h>
#include <stdbool.h>
#define string char*
#define MONTHS_IN_YEAR 12


/**
 * Data structures
*/
typedef enum month {
    Jan, Feb, Mar, Apr, May, June, July,
    Aug, Sept, Oct, Nov, Dec
} month;


typedef struct date {
    month name;
    int lastDate;
    int today;
} date;

/**
 * Methods
*/

// Return day count of exceptions, default is 30
int dayCount(month query);

// Fetch the valid date, or 0
int nextDate(date query){
    if ( query.today < query.lastDate ) {
        return (query.today + 1);
    }
    return 0;
}

// Return the next month, or 0
month nextMonth(month query, bool cycleThrough);

// Check if query is a valid month
int isValid(month query) {
    return query < MONTHS_IN_YEAR;
}

// Helper method to return list of configured months
date * configureMonths();


/**
 * Program
*/
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

        // Fetch today
        myMonth.today = 1;

        // Append to date arr
        months[i+1] = myMonth;
    }

    // Log notable months: Jan, Feb, Apr, Dec
    printf("\nLast date of Jan is '%d', id of month is '%d', id of next is '%d'", months[0].lastDate, months[0].name, nextMonth(months[0].name, true));
    printf("\nLast date of Feb is '%d', id of month is '%d', id of next is '%d'", months[1].lastDate, months[1].name, nextMonth(months[1].name, true));
    printf("\nLast date of Mar is '%d', id of month is '%d', id of next is '%d'", months[2].lastDate, months[2].name, nextMonth(months[2].name, true));
    printf("\nLast date of Dec is '%d', id of month is '%d', id of next is '%d'\n", months[11].lastDate, months[11].name, nextMonth(months[11].name, true));

    // Progress through the calendar
    printf("\nProgressing through the year:");
    int monthId = 0;
    while (isValid(monthId)) {
        printf("\n\nCurrent month is '%d', last day should be '%d'", (monthId+1), months[monthId].lastDate);
        int handle = 1;
        while(handle)  {
        
            // Display date
            printf("\nToday is '%d/%d/2023'", months[monthId].today, (months[monthId].name)+1);

            // Handle tomorrow
            int temp = nextDate(months[monthId]);
            if ( temp > 0 ) {
                months[monthId].today = temp;
            }

            // Otherwise go to next month
            else {
                monthId++;
                handle = 0;
            }
        }
    }

    printf("\n\n");
    return 0;
}


/**
 * Print next month, allowing for continous flow through or ceasing
*/
month nextMonth(month query, bool cycleThrough) {
    switch(cycleThrough) {
        case true:
            if ( query == 11 ) {
                return Jan;
            }
            return query+1;
            break;
        
        default:
            return (query + 1 % MONTHS_IN_YEAR);
    }
}

// Define the max dates
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


// Configure the months in the year
date* configureMonths() {

    // Init vars
    date months[12];
    date myMonth;

    // Configure months
    for ( int i = -1; i <= MONTHS_IN_YEAR; i++) {
        month current = nextMonth(i, false);
        myMonth.name = current;
        myMonth.lastDate = dayCount(myMonth.name);
    }

    return months;
}