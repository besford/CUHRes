/*
 * Class:       PayStub
 * Purpose:     Entity object responsible for modelling employee paystub data.
 */

#include "paystub.h"

PayStub::PayStub()
{
    this->eID = 0;
    this->hours = 0;
    this->rate = 0;
    this->pay = NetPay();
    this->name = UserName();
    this->term = WorkTerm();
}

PayStub::PayStub(int eID, int hours, int rate, const NetPay& pay, const UserName& name, const WorkTerm& term)
{
    this->eID = eID;
    this->hours = hours;
    this->rate = rate;
    this->pay = pay;
    this->name = name;
    this->term = term;
}

int PayStub::getEID()
{ return this->eID; }

int PayStub::getHours()
{ return this->hours; }

int PayStub::getRate()
{ return this->rate; }

NetPay& PayStub::getNetPay()
{ return this->pay; }

UserName& PayStub::getName()
{ return this->name; }

WorkTerm& PayStub::getTerm()
{ return this->term; }

void PayStub::setEID(int eID)
{ this->eID = eID; }

void PayStub::setHours(int hours)
{ this->hours = hours; }

void PayStub::setRate(int rate)
{ this->rate = rate; }

void PayStub::setNetPay(const NetPay& pay)
{ this->pay = pay; }

void PayStub::setName(const UserName& name)
{ this->name = name; }

void PayStub::setTerm(const WorkTerm& term)
{ this->term = term; }
