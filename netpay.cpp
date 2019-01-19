/*
 * Class:       NetPay
 * Purpose:     Entity object used for modelling paystub pay information.
 */

#include "netpay.h"

NetPay::NetPay()
{
    this->amt = 0;
    this->ded = 0;
    this->netAmt = 0;
    this->ytdAmt = 0;
    this->ytdDed = 0;
}

NetPay::NetPay(int amt, int netAmt, int ded, int ytdAmt, int ytdDed)
{
    this->amt = amt;
    this->ded = ded;
    this->netAmt = netAmt;
    this->ytdAmt = ytdAmt;
    this->ytdDed = ytdDed;
}

int NetPay::getAmt()
{ return this->amt; }

int NetPay::getDed()
{ return this->ded; }

int NetPay::getNetAmt()
{ return this->netAmt; }

int NetPay::getYtdAmt()
{ return this->ytdAmt; }

int NetPay::getYtdDed()
{ return this->ytdDed; }

void NetPay::setAmt(int amt)
{ this->amt = amt; }

void NetPay::setDed(int ded)
{ this->ded = ded; }

void NetPay::setNetAmt(int netAmt)
{ this->netAmt = netAmt; }

void NetPay::setYtdAmt(int ytdAmt)
{ this->ytdAmt = ytdAmt; }

void NetPay::setYtdDed(int ytdDed)
{ this->ytdDed = ytdDed; }
