#ifndef APPLYRAISESCONTROL_H
#define APPLYRAISESCONTROL_H

#include <QString>

class ApplyRaisesControl
{
    public:
        ApplyRaisesControl();
        static double applyRaise(const QString&, double, bool);
};

#endif // APPLYRAISESCONTROL_H
