#ifndef USERNAME_H
#define USERNAME_H

#include <QString>

class UserName
{
    public:
        UserName();
        UserName(const QString&, const QString&);

    public:
        const QString& getFName() const;
        const QString& getLName() const;
        void         setFName(const QString&);
        void         setLName(const QString&);

    private:
        QString fName;
        QString lName;
};

#endif // USERNAME_H
