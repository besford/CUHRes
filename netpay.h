#ifndef NETPAY_H
#define NETPAY_H


class NetPay
{
    public:
        NetPay();
        NetPay(int, int, int, int, int);

    public:
        int  getAmt();
        int  getNetAmt();
        int  getYtdAmt();
        int  getDed();
        int  getYtdDed();
        void setAmt(int);
        void setNetAmt(int);
        void setYtdAmt(int);
        void setDed(int);
        void setYtdDed(int);

    private:
        int amt, netAmt;
        int ytdAmt;
        int ded, ytdDed;
};

#endif // NETPAY_H
