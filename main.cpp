// 10627130 資工二甲 林冠良 & 10627131 資工二甲 李峻瑋 // CodeBlocks 17.12
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <time.h>

using namespace std ;

typedef struct DataStruct {
    string number = 0 ;
    string name = "\0" ;
    string type1 = "\0" ;
    int total = 0 ;
    int HP = 0 ;
    int ATK = 0 ;
    int DEF = 0 ;
    string whole = "\0" ;
    DataStruct* parent = NULL ;
    DataStruct* leftChild = NULL ;
    DataStruct* rightChild = NULL ;
} DataStruct ;

static ifstream input ;
static ofstream output ;
static string FileN = "0" ;
static int Count = 0 ;

class CollegeHighGoGoGo {
    DataStruct* root = NULL ;
    DataStruct* leftMost = NULL ;
    DataStruct* rightMost = NULL ;
public:
    int GetHP() ;
    int GetATK() ;
    int GetDEF() ;
    int GetHeight() ;
    void Insert( DataStruct* tempData ) {
        bool NotYet = true;
        DataStruct* parentWalker = NULL ;
        DataStruct* treeWalker = NULL ;

        if ( root == NULL ) {
                root = tempData ;
                treeWalker = root;
        } // if

        else {
            treeWalker = root;
            while( NotYet ){

                if ( treeWalker->HP == tempData->HP ) {
                  parentWalker = treeWalker;
                  while( parentWalker->parent != NULL ){
                    parentWalker = parentWalker->parent;
                  } // while

                  parentWalker->parent = tempData;
                } // if

                else if( treeWalker->HP < tempData->HP ){
                  if( treeWalker->rightChild == NULL ) {
                        treeWalker->rightChild = tempData ;
                        NotYet = false;
                  } // if

                  else treeWalker = treeWalker->rightChild ;
                } // if

                else if( treeWalker->HP > tempData->HP ){
                  if( treeWalker->leftChild == NULL ) {
                        treeWalker->leftChild = tempData ;
                        NotYet = false;
                  } // if

                  else treeWalker = treeWalker->leftChild ;
                } // if
            } // while

        } // else
    } // Insert by HP, print out the data

    void Analyze() {
        root = NULL ;
        DataStruct* tempData = NULL ;
        string value = "\0" ;
        getline( input, value ) ; // read the labels in the first line
        tempData = new DataStruct;

        while ( getline( input, value ) ) {
            // cout << value << endl ;
            vector<string> cut ;
            string token ;
            istringstream cutStream( value ) ;

            while ( getline( cutStream, token, '\t' ) ) // cut the token one by one
                cut.push_back( token ) ;

            tempData->number = cut[0] ;
            tempData->name = cut[1] ;
            tempData->type1 = cut[2] ;
            tempData->total = cut[4] ;
            tempData->HP = atoi( cut[5].c_str() ) ;
            tempData->ATK = atoi( cut[6].c_str() ) ;
            tempData->DEF = atoi( cut[7].c_str() ) ;
            Count++ ;
            Insert( tempData ) ;
        } // get the whole file
    } // Analyze the whole input file

    void Search( int data ) ;
    void Delete( int data ) ;
    DataStruct* GetLeftMost() ;
    DataStruct* GetRightMost() ;
} ;

int main() {
    int command = 0 ;
    bool continueOrNot = false ;
    CollegeHighGoGoGo dataBase ;

    do {
        cout << "********************************************************" << endl ; // welcome message
        cout << "*****                  Pokemon BST                 *****" << endl ;
        cout << "***** 0 : Quit                                     *****" << endl ;
        cout << "***** 1 : Input by HP, and count the tree height   *****" << endl ;
        cout << "***** 2 : Filter and update                        *****" << endl ;
        cout << "***** 3 : Merge two files                          *****" << endl ;
        cout << "********************************************************" << endl ;
        cout << endl << "Please enter your choice:" << endl ;

        cin >> command ; // read in user command

        if ( command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl ;
            return 0 ;
        } // quit

        else if ( command > 3 || command < 0 ) {
            cout << "Error command! please enter an acceptable command:" << endl << endl ;
            continueOrNot = true ;
        } // wrong command

        else if ( command == 1 ) { // read, count and copy
            bool function1Confirm = false ;

            do {
                cout << "Please enter the file you want to analyze or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == "0" ) {
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else {
                    string fileName = "input" + FileN + ".txt" ;
                    string tempLine = "\0" ;
                    input.open( fileName.c_str() ) ;
                    dataBase.Analyze() ;
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // open file and input data to BST
            } while( ! function1Confirm ) ;

            Count = 0 ;
            FileN = 0 ;
            input.close() ;
            output.close() ;
        } // mission 1

        else if ( command == 2 ) {
            bool function2Confirm = false ;

            do {
                cout << "Please enter the file ( 201 - 205 ) you want to filter or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == 0 ) {
                    function2Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else if ( FileN != 201 && FileN != 202 && FileN != 203 && FileN != 204 && FileN != 205 )
                    cout << "*****  copy" << FileN << ".txt does not exist!  *****" << endl ;

                else if ( FileN == 201 ) {
                    input.open( "copy201.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy201.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 201
                } // test if you have already create a copy file

                else if ( FileN == 202 ) {
                    input.open( "copy202.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy202.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 202
                } // test if you have already create a copy file

                else if ( FileN == 203 ) {
                    input.open( "copy203.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy203.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 203
                } // test if you have already create a copy file

                else if ( FileN == 204 ) {
                    input.open( "copy204.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy204.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 204
                } // test if you have already create a copy file

                else if ( FileN == 205 ) {
                    input.open( "copy205.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy205.txt does not exist!  *****" << endl ;

                    else {
                        function2Confirm = true ;
                        continueOrNot = true ;
                        Class.Filter() ;
                    } // find copy 205
                } // test if you have already create a copy file
            } while ( ! function2Confirm ) ;

            cout << "Data Count: " << Count << endl << endl ;
            Count = 0 ;
            FileN = 0 ;
            input.close() ;
            output.close() ;
        } // mission 2

        else if ( command == 3 ) {
            int firstFile = 0 ;
            int secondFile = 0 ;
            bool firstOpen = false ;
            bool secondOpen = false ;
            bool continueOrNot2 = false;

            while ( ! firstOpen ) {
                cout << "Please enter the first file ( 201 - 205 ) that you want to merge or [0] to quit:" << endl ;
                cin >> firstFile ;

                if ( firstFile == 0 ) {
                    continueOrNot = true ;
                    firstOpen = true ;
                } // quit

                else if ( firstFile != 201 && firstFile != 202 && firstFile != 203 && firstFile != 204 && firstFile != 205 )
                    cout << "*****  copy" << firstFile << ".txt does not exist!  *****" << endl ;

                else if ( firstFile == 201 ) {
                    input.open( "copy201.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy201.txt does not exist!  *****" << endl ;
                    else{
                        firstOpen = true;
                        continueOrNot = true ;
                    } // else
                } // 201

                else if ( firstFile == 202 ) {
                    input.open( "copy202.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy202.txt does not exist!  *****" << endl ;
                    else{
                        firstOpen = true;
                        continueOrNot = true ;
                    } // else
                } // 202

                else if ( firstFile == 203 ) {
                    input.open( "copy203.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy203.txt does not exist!  *****" << endl ;
                    else{
                        firstOpen = true;
                        continueOrNot = true ;
                    } // else
                } // 203

                else if ( firstFile == 204 ) {
                    input.open( "copy204.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy204.txt does not exist!  *****" << endl ;
                    else{
                        firstOpen = true;
                        continueOrNot = true ;
                    } // else
                } // 204

                else if ( firstFile == 205 ) {
                    input.open( "copy205.txt" ) ;
                    if ( ! input.is_open() ) cout << "*****  copy205.txt does not exist!  *****" << endl ;
                    else{
                        firstOpen = true;
                        continueOrNot = true ;
                    } // else
                } // 205
            } // if the first input is acceptable

            while ( firstOpen && ! continueOrNot2 ) {
                cout << "Please enter the second file ( 201 - 205 ) that you want to merge or [0] to quit:" << endl ;
                cin >> secondFile ;

                if ( secondFile == 0 ) continueOrNot2 = true ;

                else if ( secondFile != 201 && secondFile != 202 && secondFile != 203 && secondFile != 204 && secondFile != 205 && secondFile != 0 ) {
                    cout << "*****  copy" << secondFile << ".txt does not exist!  *****" << endl ;
                } // wrong filename

                else if ( secondFile == 201 ) {
                    input2.open( "copy201.txt" ) ;
                    if ( ! input2.is_open() ) cout << "*****  copy201.txt does not exist!  *****" << endl ;
                    else{
                        secondOpen = true;
                        continueOrNot2 = true ;
                    } // else
                } // 201

                else if ( secondFile == 202 ) {
                    input2.open( "copy202.txt" ) ;
                    if ( ! input2.is_open() ) cout << "*****  copy202.txt does not exist!  *****" << endl ;
                    else{
                        secondOpen = true;
                        continueOrNot2 = true ;
                    } // else
                } // 202

                else if ( secondFile == 203 ) {
                    input2.open( "copy203.txt" ) ;
                    if ( ! input2.is_open() ) cout << "*****  copy203.txt does not exist!  *****" << endl ;
                    else{
                        secondOpen = true;
                        continueOrNot2 = true ;
                    } // else
                } // 203

                else if ( secondFile == 204 ) {
                    input2.open( "copy204.txt" ) ;
                    if ( ! input2.is_open() ) cout << "*****  copy204.txt does not exist!  *****" << endl ;
                    else{
                        secondOpen = true;
                        continueOrNot2 = true ;
                    } // else
                } // 204

                else if ( secondFile == 205 ) {
                    input2.open( "copy205.txt" ) ;
                    if ( ! input2.is_open() ) cout << "*****  copy205.txt does not exist!  *****" << endl ;
                    else{
                        secondOpen = true;
                        continueOrNot2 = true ;
                    } // else
                } // 205
            } // second file


            if ( firstOpen && secondOpen ) {
                FileN = firstFile;
                FileN2 =secondFile ;
                Class.Merge();
                firstOpen = false;
                secondOpen = false;
            } // if

            cout << "Data Count: " << Count << endl << endl ;
            Count = 0 ;
            FileN = 0 ;
            FileN2 = 0;
            input.close() ;
            input2.close() ;
            output.close() ;

        } // mission 3

    } while( continueOrNot ) ;
} // Main function
