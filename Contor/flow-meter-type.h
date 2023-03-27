/*
 * Water flow meters structure and DB
 * Author: Constantin
 */

#ifndef FLOWMETERTYPE_H
#define FLOWMETERTYPE_H

#include <string>

/*
 * Water Flow Meters type structure
 *
 */
struct MeterFlowType {
    MeterFlowType (
        std::string _nameWaterMeter,
        unsigned _nominalDiameter,
        double _nominalFlow,
        double _maximumFlow,
        double _trasitionFlow,
        double _minimumFlow,
        double _nominalError,
        double _maximumError ) :
        nameWaterMeter ( _nameWaterMeter ),
        nominalDiameter ( _nominalDiameter ),
        nominalFlow ( _nominalFlow ),
        maximumFlow ( _maximumFlow ),
        trasitionFlow ( _trasitionFlow ),
        minimumFlow ( _minimumFlow ),
        nominalError ( _nominalError ),
        maximumError ( _maximumError )
    {};

    std::string nameWaterMeter;
    unsigned nominalDiameter;
    double nominalFlow;
    double maximumFlow;
    double trasitionFlow;
    double minimumFlow;
    double nominalError;
    double maximumError;
};

/*
 * Water Flow Meters DB
 *
 */
MeterFlowType MeterFlowDB[] = {
    // -----------------------------------------------------------------------------------------------
    //                  Type                 DN       QN      Qmax     Qt     Qmin   ErrNom  ErrMax
    //                                       mm       l/h      l/h     l/h     l/h     %      %
    // -----------------------------------------------------------------------------------------------
    MeterFlowType ( "Itron Flodis Dn 15",      15,     1500,    3000,    15,      5,    2,     5 ),
    MeterFlowType ( "Itron Flodis Dn 20",      20,     2500,    5000,    25,      6,    2,     5 ),
    MeterFlowType ( "Itron Flodis Dn 25",      25,     3500,    7000,    35,     10,    2,     5 ),
    MeterFlowType ( "Itron Flodis Dn 32",      32,     6000,   12000,    60,     12,    2,     5 ),
    // -----------------------------------------------------------------------------------------------
    MeterFlowType ( "Itron Flostar Dn 40",     40,    16000,   20000,   160,     80,    2,     5 ),
    MeterFlowType ( "Itron Flostar Dn 50",     50,    25000,   31250,   127,     79,    2,     5 ),
    MeterFlowType ( "Itron Flostar Dn 65",     65,    40000,   50000,   160,    100,    2,     5 ),
    MeterFlowType ( "Itron Flostar Dn 80",     80,    63000,   78000,   252,    157,    2,     5 ),
    MeterFlowType ( "Itron Flostar Dn 100",   100,   100000,  125000,   400,    250,    2,     5 ),
    MeterFlowType ( "Itron Flostar Dn 150",   150,   160000,  200000,   406,    254,    2,     5 ),
    // ----------------------------------------------------------------------------------------------
    MeterFlowType ( "FGH MNK Dn 15 R80",       15,     2500,    3125,    50,    31.25,  2,     5 ),
    MeterFlowType ( "FGH MNK Dn 15 R160",      15,     2500,    3125,    25,    15.63,  2,     5 ),
    MeterFlowType ( "FGH MNK Dn 20 R80",       20,     4000,    5000,   100,    62.5,   2,     5 ),
    MeterFlowType ( "FGH MNK Dn 20 R160",      20,     4000,    5000,    40,    25,     2,     5 ),
    MeterFlowType ( "FGH MNK Dn 25 R80",       25,     6300,    7875,   126,    78.75,  2,     5 ),
    MeterFlowType ( "FGH MNK Dn 25 A",         25,     6300,    7875,    63,    39.4,   2,     5 ),
    MeterFlowType ( "FGH MNK Dn 25 B",         25,     8000,   10000,   160,    100,    2,     5 ),
    MeterFlowType ( "FGH MNK Dn 25 C",         25,     8000,   10000,    80.64,  50.4,  2,     5 ),
    MeterFlowType ( "FGH MNK Dn 32 R80",       32,    10000,   12000,   200,    125,    2,     5 ),
    MeterFlowType ( "FGH MNK Dn 32 R160",      32,    10000,   12000,   100,     62.5,  2,     5 ),
    MeterFlowType ( "FGH MNK Dn 40 R80",       40,    16000,   20000,   320,    200,    2,     5 ),
    MeterFlowType ( "FGH MNK Dn 40 R160",      40,    16000,   20000,   160,    100,    2,     5 ),
    MeterFlowType ( "FGH MNK Dn 50 R80",       50,    25000,   31250,   500,    312.5,  2,     5 ),
    MeterFlowType ( "FGH MNK Dn 50 R255",      50,    25000,   31250,   160,    100,    2,     5 ),
};

#endif // FLOWMETERTYPE_H
