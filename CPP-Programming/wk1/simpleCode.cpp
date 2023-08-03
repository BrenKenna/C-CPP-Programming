/**
 * Some basic c++ stuff
 * 
*/


#include <iostream>
using namespace:: std;
const double milesToKiloMeter = 1.609;

inline double convert(int mi) {
    return mi * milesToKiloMeter;
}

/**
 * Could be the 'data' element of a binary search tree/array
 *   - Allowing the one chunk of code, to serve a collection
 *     of use cases
 * 
 * # Compile
 * g++ -o simpleCode simpleCode.cpp
*/
template<typename T> struct GenericAttribute {
    T value;
};

template<typename T> class GenericArray {

    // Attributes
    private: 
        T* arrPtr;
        int sizeOf;

    /**
     * Constructor
    */
    public: GenericArray(T arr[], int size) {
        arrPtr = arr;
        sizeOf = size;
    }

    /**
     * Get first elm
    */
    public: T getFirstElm() {
        return this-> arrPtr[0];
    }

    /**
     * Get size of arr
    */
    public: int getSize() {
        return this-> sizeOf;
    }
};

/**
 * Program
*/
int main() {

    // Init user var
    auto miles = 1;

    // Test generic attribute
    cout << "\nTesting a generic template:";
    GenericAttribute<char> myCharHolder;
    GenericAttribute<int> myIntHolder;
    myCharHolder.value = 'a';
    myIntHolder.value = -1;
    cout << "\nMy char is '" << myCharHolder.value << "'";
    cout << "\nMy int is '" << myIntHolder.value << "'\n";

    // Test generic class
    cout << "\nTesting generic array class:\n";
    int myIntArr[] = {1, 2, 3};

    // No inference Java-like & initializing requires default constructor
    GenericArray<int> myGenArr = GenericArray<int>(myIntArr, 3);
    cout << "The size of my generic array is '" << myGenArr.getSize() << "'\n";
    cout << "The first element of my generic array of type int is '" << myGenArr.getFirstElm() << "'\n";

    // Convert while user wants to
    cout << "\nDemonstrating the use of cout/in:";
    while( miles != 0 ) {
        cout << "\nPlease enter your distance in miles to convert to km, or 0 to terminate\n>>> ";
        cin >> miles;
        if ( miles > 1 ) {
            cout << "\nDistance in kilo meters is:\t'" << convert(miles) << "' km" <<endl;
        }
        else {
            cout << "\nTerminating program";
        }
    }
    cout << endl;

    // End program
    cout << "\n";
    return 0;
}