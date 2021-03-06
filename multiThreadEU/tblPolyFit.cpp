//
//  tblPolyFit.cpp
//  multiThreadEnergyUsage
//
//  Created by Clifford Campo on 6/15/18.
//  Copyright © 2018 CliffordCampo. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include "myPrototypes.hpp"
#include "tblPolyFit.hpp"
#include "setupForMultiFit.hpp"
#include "varyingType.hpp"

TblPolyFit::TblPolyFit(SetupForMultiFit *smf, const char *cs, short mID, int nv, int rsltFmt, short pd ) {
    SUMF = smf;  //SUMF is a pointer of type void. It should really be a pointer to Type SetupForMultiFit.
    usmeterID = (unsigned short)mID;
    polynomialDegree = pd;
    ptrMeterID = &usmeterID;
    ptrPolynomialDegree = &polynomialDegree;
    connString = cs; //Point to the connection string TblPolyFit wishes to use.
    nParams = nv;
    resultFormat = rsltFmt;
    parmValues = new const char * const [nv]{};
    paramTypes = new const Oid[nv]{INT2OID,FLOAT8OID, FLOAT8OID, FLOAT8OID, FLOAT8OID, INT2OID, FLOAT8OID, FLOAT8OID};
    paramLengths = new const int[nv]{2,8,8,8,8,2,8,8};
    paramFormats = new const int [nv]{1,1,1,1,1,1,1,1};
    memset (&cov[0], (double)0, sizeof(cov) );
 }


TblPolyFit::TblPolyFit(const char *cs, short mID, int nv, int rsltFmt, short pd )  { 
    SUMF = NULL;  //SUMF is NULL since we were instatiated without the smf pointer (see above polymirphic twin).
    usmeterID = (unsigned short)mID;
    polynomialDegree = pd;
    ptrMeterID = &usmeterID;
    ptrPolynomialDegree = &polynomialDegree; 
    connString = cs; //Point to the connection string TblPolyFit wishes to use.
    nParams = nv;
    resultFormat = rsltFmt;
    parmValues = new const char * const [nv]{};
    paramTypes = new const Oid[nv]{INT2OID,FLOAT8OID, FLOAT8OID, FLOAT8OID, FLOAT8OID, INT2OID, FLOAT8OID, FLOAT8OID};
    paramLengths = new const int[nv]{2,8,8,8,8,2,8,8};
    paramFormats = new const int [nv]{1,1,1,1,1,1,1,1};
 
}

TblPolyFit::~TblPolyFit() {
    if (parmValues != nullptr) delete [] parmValues;
    if (paramTypes != nullptr) delete [] paramTypes;
    if (paramLengths != nullptr) delete [] paramLengths;
    if (paramFormats != nullptr ) delete [] paramFormats;
}

//χ-squared value ---------------------------------------------------------------------------------------------------+
//Correlation Coefficient --------------------------------------------------------------------------------+          |
 //Meter Descriptor ----------------------------------------------------------------------------+         |          |
 //coefficient C3 -------------------------------------------------------------------+          |         |          |
 //coefficient C2 --------------------------------------------------------+          |          |         |          |
 //coefficient C1 ---------------------------------------------+          |          |          |         |          |
 //coefficient C0 -----------------------------------+         |          |          |          |         |          |
 //short int showing polynomial degree ---+          |         |          |          |          |         |          |
 //    Base Class ----------+             |          |         |          |          |          |         |          |
//                          V             V          V         V          V          V          V         V          V
int TblPolyFit::doInsertInto(const char *cs, short *p1, double *p2, double *p3, double *p4, double *p5, short *p6, double *p7, double *p8) {
    
    VaryingType<short> *tp1 =new VaryingType<short>(); //This tp1 object, for type short, should serve us well for making input parameters p1 and p6 in network byte order.
    tp1->in64.d64 = *p1;
    tp1->VaryingType<short>::toNetworkByteOrder();
    this->nbop1 = tp1->out64.d64;
// --------------------------------------------
    tp1->in64.d64 = *p6; //Reuse the short object that we created above
    tp1->VaryingType<short>::toNetworkByteOrder();
    this->nbop6 = tp1->out64.d64;
// --------------------------------------------
    VaryingType<double> *tp2_8 =new VaryingType<double>();  //This tp2_8 object, for type double, should serve uswell for making input parameters p2, p3, p4, p5, p7, and p8 in network byte order.
    tp2_8->in64.d64 = *p2;
    tp2_8->VaryingType<double>::toNetworkByteOrder();
    this->nbop2 = tp2_8->out64.d64;
// --------------------------------------------
    tp2_8->in64.d64 = *p3;
    tp2_8->VaryingType<double>::toNetworkByteOrder();
    this->nbop3 = tp2_8->out64.d64;
// --------------------------------------------
    tp2_8->in64.d64 = *p4;
    tp2_8->VaryingType<double>::toNetworkByteOrder();
    this->nbop4 = tp2_8->out64.d64;
// --------------------------------------------
    tp2_8->in64.d64 = *p5;
    tp2_8->VaryingType<double>::toNetworkByteOrder();
    this->nbop5 = tp2_8->out64.d64;
// --------------------------------------------
    tp2_8->in64.d64 = *p7;
    tp2_8->VaryingType<double>::toNetworkByteOrder();
    this->nbop7 = tp2_8->out64.d64;
// --------------------------------------------
    tp2_8->in64.d64 = *p8;
    tp2_8->VaryingType<double>::toNetworkByteOrder();
    this->nbop8 = tp2_8->out64.d64;
// --------------------------------------------
    //In the next statement, note how c++ initializes an array ***without the use of an equal sign*** between the closing `]` and the opening `{`.   ----+
    //                                                                                                                                                   |
    //                                                                                                                                                   |
    //                       +-------------------------------NO = sign!! --------------------------------------------------------------------------------+
    //                       |
    //                       V
    Oid *const arrayOfOid = new Oid[8]{INT2OID, FLOAT8OID, FLOAT8OID, FLOAT8OID, FLOAT8OID, INT2OID, FLOAT8OID, FLOAT8OID};
    this->paramTypes = arrayOfOid;
    //What follows is the crazyiest demonstration of "type-casting" I've ever seen: `(char *)&`. See The PostgreSQL 9.0 Reference Manual, Volume 2: Programming Guide, bottom of page 82. I highlighted this cited page in yellow.
    const char * const *arrayOfParmValues = new const char *[8]{ (char *)&this->nbop1, (char *)&this->nbop2, (char *)&this->nbop3, (char *)&this->nbop4, (char *)&this->nbop5, (char *)&this->nbop6, (char *)&this->nbop7, (char *)&this->nbop8};
    this->parmValues = arrayOfParmValues;
    int *const arrayOfParamLengths = new  int[8]{sizeof(short), sizeof(double), sizeof(double), sizeof(double), sizeof(double), sizeof(short), sizeof(double), sizeof(double)};
    this->paramLengths = arrayOfParamLengths;
    const int *const arrayOfParamFormats = new const int[8]{BINARYRESULTS, BINARYRESULTS, BINARYRESULTS, BINARYRESULTS, BINARYRESULTS, BINARYRESULTS, BINARYRESULTS, BINARYRESULTS};
    this->paramFormats = arrayOfParamFormats;
// --------------------------------------------
    this->conn  = PQconnectdb(this->connString);  //Use the connString from the Private Data Member.
    if(PQstatus(this->conn) != CONNECTION_OK) {
        std::cout << "Connection to database failed: " << PQerrorMessage(this->conn) << std::endl;
        PQfinish(this->conn);
        if (tp2_8 != nullptr) delete tp2_8;
        if (tp1 != nullptr) delete tp1;
        exit(1);
    } else {
        std::cout << "Looks like we connected to database ok." << std::endl;
    }
    this->res = PQexecParams(this->conn, this->insertINTO, 8, arrayOfOid, arrayOfParmValues, arrayOfParamLengths, arrayOfParamFormats, 1 );
    if (PQresultStatus(this->res) != PGRES_COMMAND_OK) { //INSERTS usually return PGRES_COMMAND_OK when they do a successful insert.\
        PGRES_COMMAND_OK is the successful indicator status for commands, like INSERT INTO, that reurn no data.
        std::cout << "Insert Operation failed: " << PQerrorMessage(this->conn);
        this->rc=1;
    } else {
        std::cout << "Successful insert!" << std::endl;
    }
    PQclear(this->res);
    PQfinish(this->conn);
    if (tp2_8 != nullptr)  delete tp2_8;
    if (tp1 != nullptr) delete tp1;
    return this->rc;
}


