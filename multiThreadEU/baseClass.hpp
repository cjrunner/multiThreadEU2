//
//  baseClass.hpp
//  
//
//  Created by Clifford Campo on 5/2/18.
//  Copyright © 2018 CliffordCampo. All rights reserved.
//
#ifndef __BASECLASS__
#define __BASECLASS__

#include <typeinfo>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include <gsl/gsl_vector.h>
#include "tblPolyFit.hpp"
#include "currentDateTime.hpp"
#include "cmdLineArgs.hpp"
#include "myPrototypes.hpp"
#include "alignField.hpp"
//#include <iostream>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_statistics.h>
#include "/usr/local/pgsql/pgsql101/include/libpq-fe.h"
#include "baseClass.hpp" //Need this to resolve the inherited MakeConnectionString class.
#include "tblPolyFit.hpp"
#define PD 3
#define FLOAT8OID 701
#define TEXTOID 25
#define INT2OID 21
#define  NUMBEROFPARAMETERS 8
#define  TEXTRESULTS 0    //Used to set resultFormat in public space
#define  BINARYRESULTS 1 //Used to set resultFormat in public space
//#include "/Users/cjc/c++/energyUsage/energyUsage/BitFlags.hpp"
#include "BitFlags.hpp"

//#include "/usr/local/pgsql/pgsql101/include/libpq-fe.h"
#define WONDERFUL 0
#define MAXTEMPERATURE 100
#define MINTEMPERATURE 0
#define MAXNUMBEROFAVGTEMPS 100
#define IV 0
#define EMO IV+1
#define EDVA EMO + 1
#define ODVA EDVA + 1
#define BADWHICH 1
#define MAXLENGTHPASSWORD 32
#define SELECTFROMTABLE 0
#define CLOSEPORTAL 1 + SELECTFROMTABLE
#define CREATETHETABLE 1 + CLOSEPORTAL
#define DROPTHETABLE 1 + CREATETHETABLE
#define ENDTRANSACTION 1 + DROPTHETABLE
#define EXECUTESQL 1 + ENDTRANSACTION
#define FETCHALLTRANSACTION 1 + EXECUTESQL
#define INSERTBUCKETIZEDVALUESINTOTABLE 1 + FETCHALLTRANSACTION
#define BEGINTRANSACTION 1 + INSERTBUCKETIZEDVALUESINTOTABLE
#define NUMBEROFVALUES 9
#define NUMBEROFPGRESULTOBJCECTS 9
#define WORKBUFSIZE 80
class BaseClass    {
    friend CmdLineArgs;
private: //These values get set during execution time, not during compile time.

    const size_t szBaseClass = sizeof(BaseClass);

    const size_t maxNumberOfAvgTemps = MAXNUMBEROFAVGTEMPS;   //number of elements to be initially allocated to the gsl_vector type named independentVariableAvgTemp 100; //number of elements to be initially allocated to the gsl_vector type named independentVariableAvgTemp
    const char *const dbnameEqual   = "dbname=";         // dbname= will always be the first parameter in the connection string, thus the absense of the leading blank.
    const char *const useridEqual   = " user=";          //
    const char *const passwordEqual = " password=";   //
    const char *const hostidEqual   = " hostaddr=";     //
    const char *const portidEqual   = " port=";          //
    const char *const basicSELECT   = "SELECT avtempf, avtempk, m1kwh, m2kwh, m1m2kwh FROM tbl_energy_usage WHERE date_part('J', date) BETWEEN ";
    size_t lengthOfStaticPartsOfConnectionString = strlen(dbnameEqual) + strlen(useridEqual) + strlen(passwordEqual) + strlen(hostidEqual) + strlen(portidEqual);
    size_t lengthOfDynamicPartsOfConnectionString;
    CmdLineArgs *CLA;   //Points to the class named CmdLineArgs. This class is a friend of class CmdLineArgs
    const size_t szPrivateBaseClass = sizeof(szBaseClass) + sizeof(szPrivateBaseClass) + sizeof(maxNumberOfAvgTemps) + sizeof(dbnameEqual) + sizeof(useridEqual) + sizeof(passwordEqual) + sizeof(hostidEqual) + sizeof(portidEqual) + sizeof(basicSELECT) + sizeof(lengthOfStaticPartsOfConnectionString) + sizeof(lengthOfDynamicPartsOfConnectionString) +sizeof(*CLA) + sizeof(szPublicPartsOfBaseClass);
    const size_t szPublicPartsOfBaseClass = szBaseClass - szPrivateBaseClass;
public:
    const size_t *ptrMaxNumberOfAvgTemps;  //number of elements to be initially allocated to the gsl_vector type named independentVariableAvgTemp 100; //number of elements to be initially allocated to the gsl_vector type named independentVariableAvgTemp
    PGconn *conn; //PostgreSQL's Connection Object
    PGresult *res;
    BitFlags debugFlags;
    
    double *ptrExpMinusObsDepVarArray;
    double *ptrObsDepVarArray;
    double *ptrExpDepVarArray;
    double *ptrIndVariableArray;
    
    double depVarArray[MAXNUMBEROFAVGTEMPS];
    double indVarArray[MAXNUMBEROFAVGTEMPS];
    const char *errmsg;
    const char *BFS; //New to multiThread version Points to motherOfAllSelectStatements specific to this thread 
    const char *lookAtMyConnectionString;
    const char *clUserID;
    const char *clDatabaseName;
    const char *clPortID;
    const char *clHostID;
    size_t sizeOfEachArray;
    char pwBuffer[MAXLENGTHPASSWORD];
    const char *results_File;  //Name of the results file
    const char *clPW;
    char *MCS;
    const char *clSQL; //Points to the sql statement provided in the command line switch, if Any.
    //Variables specifict to selectFromTable
    char *start;
    char *end;
    std::ostringstream *ptros;
    std::ofstream myTempFile; //Create an object for writing to a file (an ofstream)
    std::ostringstream *outstring; //Create a pointer to object that replaces std::cout or std::cerr with a character string.
    size_t len;
    //    double julianDate = 2458243.209030; unused
    char s;
    size_t bufferOffset;
    int minBucketTemp;
    int buckettemp;
    int maxBucketTemp;
    int countOfGoodEntries;
    int loopCounter;
    int rowBeingProcessed;
    int numberOfReturnedRows;
    int numberOfReturnedColumns;
    int rc[8];
    int grc;
    int brc;
    int k;
    int resultsPQputCopyEnd;
    int resultsPQputCopyData;
    //    int trc=INITIALVALUE;
    size_t grc_t; //Good Row Count
    size_t brc_t; //Bad Row Count
    size_t trc_t; //Total Row Count = grc_t + brc_t
    int thisCount;
    int selectFromTable_RC; //Return code from selectFromTable
    int worthyOfPolynomialFitProcessing;
    char *temp;
    char *eu;
    char *copyBuffer;
    char *sqlbuffer;
    char *subCharBuffer;
    char *sql;
    double averageVariencePerValidReading;
    double squareRootOfSumOfTheSquaresOfTheVarience ;
    double values[NUMBEROFVALUES];
    double *ptrValues;
    char  workbuf[WORKBUFSIZE];
    char connectionString[WORKBUFSIZE];   //Will hold the actual connection string.
    //Variables specific to dropTheTable
    PGresult *resD;
    
    //Variables specific to effectConnection
    
    //Variables specific to insertBucketizedEnergyValuesIntoTable.cpp
    
    //Variables specific to currentDateTime.cpp
    time_t     now;
    struct tm  tstruct;
    char buf[WORKBUFSIZE];
    //
    PGconn  *connI;
    PGresult *resI;
    int numberOfReturnedRowsI;
    int numberOfReturnedColumnsI;
    char e;
    void allocateArrays(size_t);
    char *sqlI; //Need to do const char *sql rather than just char *sql to make the C++11 compiler happy.
    //Prototypes
    BaseClass(void);
    BaseClass(int);
    BaseClass(CmdLineArgs *,  const char = '0', const char * = "cjc", const char * = "LocalWeather", const char * = "5436", const char * = "127.0.0.1", const size_t = MAXNUMBEROFAVGTEMPS );
    const char *getPrivate(CmdLineArgs &,char);
    ~BaseClass();

    void setConString(const char *cs);
    int setArray(int, int, double);

}; //EndOfClass BaseClass
//
//  SetupForMultiFit.hpp
//  energyUsage
//
//  Created by Clifford Campo on 5/13/18.
//  Copyright © 2018 CliffordCampo. All rights reserved.
//


#ifndef __SETUPFORMULTIFIT__
#define __SETUPFORMULTIFIT__

// #include "insertIBucketizedEnergyValuesIntoTable.hpp" //The Class for SetupForMultiFit is defined here.
//
//  2018-05-20T11:45:10 Name chaged to setupForMultifit.hpp from
//  insertIBucketizedEnergyValuesIntoTable.hpp
//  energyUsage
//
//  Created by Clifford Campo on 5/5/18, 2018-05-20
//  Copyright © 2018 CliffordCampo. All rights reserved.
//
//  The class, SetupForMultiFit , inherits from the BaseClass
//

#include <iostream>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_statistics.h>
#include "/usr/local/pgsql/pgsql101/include/libpq-fe.h"
#include "baseClass.hpp" //Need this to resolve the inherited MakeConnectionString class.
#include "tblPolyFit.hpp"
#define PD 3
#define FLOAT8OID 701
#define TEXTOID 25
#define INT2OID 21
#define  NUMBEROFPARAMETERS 8
#define  TEXTRESULTS 0    //Used to set resultFormat in public space
#define  BINARYRESULTS 1 //Used to set resultFormat in public space
// ¿enum bucketColNames is already defined in BaseClass, so why define it again? enum bucketColNames  {_avgtemp, _avgeu, _stddeveu, _mineu, _maxeu, _countu};
class SetupForMultiFit   {  //SetupForMultiFit inherits from BaseClass
private:
    
    size_t polynomialDegree; //From constructor parameter;
    size_t numberOfEntries;  // From count
    const double *arrayOfValues; //Pointer to array of current values, per enum, above, bucketColNames
    size_t &maxNumberOfRows = numberOfEntries;  // Use a c++-type reference rather than a C-type pointer.
    
public:
    BaseClass   *bc; 
    size_t onePlusPolynomialDegree;
    const  double initialValue = 1;
    double dblwork;
    double computedValue;
    double chiSquared;
    double *ptrChiSquared;
    double TSS; //total sum of squares
    double goodnessOfFit;
    double correlationCoefficient;
    double meanOfIndependentVariable;
    double meanOfDependentVariables;
    double traceOfCovarientMatrix;
    double *ptrReturnFromGslCoefficient;
    double returnFromGslCoefficient;
    size_t loopCounter;
    gsl_multifit_linear_workspace *work;
    gsl_matrix *independentVariable;
    gsl_matrix *covarienceMatrix;
    gsl_vector *independentVariableTemp;
    gsl_vector *dependentVariable;
    gsl_vector *computedDependetVariable;
    gsl_vector *weights;
    gsl_vector *coefficients;
    int rc;
    //Declaration of various member functions
    ~SetupForMultiFit();
    
    SetupForMultiFit(BaseClass *, size_t,  size_t, double *) ;
    
    SetupForMultiFit(void);
    int doMultiFit(void) ;
    
    void  setIntoMatrix(gsl_matrix *, int, int, double);
    
    void  setIntoVector(gsl_vector *, int, double);
    
    double  getFromMatrix(gsl_matrix *, int, int);
    
    double  getFromVector(gsl_vector *, int);
    
    int  outputPolynomial(const char *, const char *);
    
    double  outputCovarianceMatrix(const char *, const char *);
    
    void captureIndependentVariableValues( int, double []);  //☞Note  that the `[]` is necessary in this declaration
    
    double computeTrace(double *, int);
    
    double  computeCorrelationBetweenIndependentAndDependentVariables(BaseClass *);
    
    double computeGoodnessOfResults (BaseClass *);
    double     getCoefficient(int );      //Return the value of the sought-after coefficient
    double *ptrGetCoefficient(int );  //Return pointer to the sought-after coefficient
    
    double *getChi2(void);         //Return pointer to the sought-after chi-squared value.
    
    double *getCorrelationCoefficient(void);  //Return pointer to the sought-after correlation-coefficient.
    //    SetupForMultiFit(size_t polynomialDegree, size_t count, double *);
    //    ~SetupForMultiFit();
    //void setIntoMatrix(gsl_matrix *, int, int, double);
    //void setIntoVector(gsl_vector *, int, double);
    //double getFromMatrix(gsl_matrix *, int, int);
    //double getFromVector(gsl_vector *, int);
    //void captureIndependentVariableValues( int, double * );//
    // int doMultiFit(void );
    //int outputPolynomial(const char *);
    //double outputCovarianceMatrix(const char *);  //Prints out covarience matrix and returns value of χ-squared.
};

class TblPolyFit : private SetupForMultiFit {
private:
    const char *connString = "dbname=LocalWeather port=5436 user=cjc password=apple";  //Connection String goes here.
    //   enum kinds {_m1m2kwh, _m1kwh, _m2kwh};
    // Should look something like: INSERT INTO tbl_poly_fit (lt,pd,coeff,kind,correl,chi2) VALUES(now(), 3, '{51.0091, 1.40023, -0.0656151, 0.000525268}', 'm1kwh', -0.945637, 4.8905);
    //                                                               OID = FLOAT8OID (701) --------------------------------------+---+
    //                                                               OID = INT2OID (21) ------------------------------------+    |   |
    //                                                               OID = FLOAT8OID (701) --------------+---+---+---+      |    |   |
    //                                                               OID = INT2OID  (21) ----------+     |   |   |   |      |    |   |
    //                                                                                             V     V   V   V   V      V    V   V
    //  const char *insertINTO = "INSERT INTO tbl_poly_fit (lt,pd,coeff,kind,correl,chi2) VALUES (now(), $1,  {$2, $3, $4, $5},$6,  $7, $8);";
    const char *insertINTO = "INSERT INTO tbl_poly_fit (lt,pd,coeff[1], coeff[2], coeff[3], coeff[4], kind,correl, chi2) VALUES (now(), $1,  $2, $3, $4, $5,  $6, $7, $8);";
    // NB: kind = 0 => m1m2kwh, kind = 1 => m1kwh, kind = 2 => m2kwh
    int  rc=0;  //Set the return code, assuming success;
public:
    SetupForMultiFit *SUMF;
    double c0 ;
    double c1 ;
    double c2 ;
    double c3 ;
    double cc ;
    double chi2 ;
    double cov[1+PD][1+PD];   //Space for covariance matrix.
    double *ptrCov;
    //
    double nboCOV[1+PD][1+PD]; //Above covariance matirx with the same elements but in network byte order.
    double *ptrNboCov;
    short  *ptrPolynomialDegree;
    union {
        short  pd ; //Polynomial Degree
        short  polynomialDegree;
    };
    unsigned short  usmeterID;
    unsigned short *ptrMeterID;
    
    
    short  nbop1; //contains the polynomial order, as a short int, in Network Byte Order
    double nbop2;   //contains the c0 coefficient, as a double, in Network Byte Order
    double nbop3;   //contains the c1 coefficient, as a double, in Network Byte Order
    double nbop4;   //contains the c2 coefficient, as a double, in Network Byte Order
    double nbop5;   //contains the c3 coefficient, as a double, in Network Byte Order
    short  nbop6;  //points to meter definition
    double nbop7;   //contains correlation coefficient, as a double, in Network Byte Order
    double nbop8;   //contains χ-squared value, as a double, in Network Byte Order
    const Oid *paramTypes; //Pointer to array of length = nParams and of type Oid (see /Users/cjc/C/postgres10/postgresql-10.1/postgresql-10.1/tmp_install/usr/local/pgsql/pgsql101/include/server/catalog/pg_type.h)
    const char * const *parmValues; //Pointer to array of length = nParams
    const int *paramLengths; //Pointer to array of length = nParams. Specifies the actual data lengths of binary-format parameters. Ignored for NULL parameters and text-format parameters.
    const int *paramFormats; //Pointer to array of integers specifying if the value is text (array entry is 0), or binary (array entry is 1). Values passed in binary format require knowledge of the internal representation expected by the backend. For example, integers must be passed in network byte order (BIG ENDIAN). Passing numeric values requires knowledge of the server storage format, as implemented in `src/backend/utils/adt/:::numeric_send()` and `src/backend/utils/adt/numeric.c::numeric_recv()`
    PGconn *conn;
    PGresult *res;
    int  resultFormat; //Specify 0 to obtain results in text format; specify 1 to obtain results in binary format.
    int nParams; // Number of Parameters. Also the lengths (number of elements) of the following four arrays. This value used by constructor for allocating the dynamic storage when instantiating the next four pointers.
    //   SetupForMultiFit *smf;
    TblPolyFit(SetupForMultiFit *, const char *, short , int=NUMBEROFPARAMETERS , int=TEXTRESULTS , short=PD  );
    TblPolyFit(const char *, short, int=NUMBEROFPARAMETERS, int=TEXTRESULTS, short=PD ) ; //This constructor takes the third (right-most) parameter and uses it to set the value of nParams and then dynamically allocate storageTblPolyFit(SetupForMultiFit *,  int=NUMBEROFPARAMETERS, int=TEXTRESULTS); //This constructor takes the third (right-most) parameter and uses it to set the value of nParams and then dynamically allocate storage
    ~TblPolyFit();  //Needs to delete the four dynamic storage objects  allocated by the above constructor.
    int doInsertInto(const char *, short *, double *, double *, double *, double *, short *, double *, double *);  //used for inserting into tbl_poly_fit the \
    usual short and double data types plus the values, of type double, into the array data type of field coeff. Note that all nine parameters \
    are pointers! These are the series of four `double *` between the two `short *`. The right-most two `double *` are for specifying pointers \
    to the correlation coefficient and the chi-squred value. the left-most `const char *` is for specifying the connection string. \
    This connection string can probably be obtained by other means, say by accessing the private member data named connString.
    
};
#endif /* __SETUPFORMULTIFIT__ */

#endif


