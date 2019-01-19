#ifndef PAYSTUB_H
#define PAYSTUB_H

#include "workterm.h"
#include "username.h"
#include "netpay.h"


class PayStub
{
    public:
        PayStub();
        PayStub(int, int, int, const NetPay&, const UserName&, const WorkTerm&);

    public:
        int         getEID();
        int         getHours();
        int         getRate();
        NetPay&     getNetPay();
        UserName&   getName();
        WorkTerm&   getTerm();
        void        setEID(int);
        void        setHours(int);
        void        setRate(int);
        void        setNetPay(const NetPay&);
        void        setName(const UserName&);
        void        setTerm(const WorkTerm&);


    private:
        int         eID;
        int         hours, rate;
        NetPay      pay;
        UserName    name;
        WorkTerm    term;


};

#endif // PAYSTUB_H
