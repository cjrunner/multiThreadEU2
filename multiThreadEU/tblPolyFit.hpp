//
//  tblPolyFit.hpp
//  multiThreadEnergyUsage
//
//  Created by Clifford Campo on 6/15/18.
//  Copyright © 2018 CliffordCampo. All rights reserved.
//

#ifndef tblPolyFit_hpp
#define tblPolyFit_hpp

#include <stdio.h>
#include <iostream>
#include "/usr/local/pgsql/pgsql101/include/libpq-fe.h"
#include "myPrototypes.hpp"
#define PD 3
#define FLOAT8OID 701
#define TEXTOID 25
#define INT2OID 21
#define  NUMBEROFPARAMETERS 8
#define  TEXTRESULTS 0    //Used to set resultFormat in public space
#define  BINARYRESULTS 1 //Used to set resultFormat in public space
typedef struct ll64 {
    union {
        double d64;
        uint64_t b64;
        uint8_t b0;
        uint8_t  arr[8]; //An Array of eight, eight-bit, bytes.
    } u64;
} ll64;
class TblPolyFit  {
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
    double c0 ;
    double c1 ;
    double c2 ;
    double c3 ;
    double cc ;
    double chi2 ;
    short  pd ; //Polynomial Degree
    unsigned short *ptrMeterID;
    short  polynomialDegree;
    short  *ptrPolynomialDegree;
    unsigned short  usmeterID;
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
    int nParams; // Number of Parameters. Also the lengths (number of elements) of the following four arrays. This value used by constructor for allocating the dynamic storage when instantiating the next four pointers.
 //   SetupForMultiFit *smf;


    int  resultFormat; //Specify 0 to obtain results in text format; specify 1 to obtain results in binary format.

TblPolyFit(const char *, short, int=NUMBEROFPARAMETERS, int=TEXTRESULTS, short=PD ); //This constructor takes the third (right-most) parameter and uses it to set the value of nParams and then dynamically allocate storageTblPolyFit(SetupForMultiFit *,  int=NUMBEROFPARAMETERS, int=TEXTRESULTS); //This constructor takes the third (right-most) parameter and uses it to set the value of nParams and then dynamically allocate storage
~TblPolyFit();  //Needs to delete the four dynamic storage objects  allocated by the above constructor.
int doInsertInto(const char *, short *, double *, double *, double *, double *, short *, double *, double *);
};
#endif /* tblPolyFit_hpp */
