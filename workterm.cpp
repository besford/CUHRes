/*
 * Class:       WorkTerm
 * Purpose:     Entity object responsible for modeling employee workterms.
 */

#include "workterm.h"

WorkTerm::WorkTerm()
{
    this->sDate = "n/a";
    this->eDate = "n/a";
}

WorkTerm::WorkTerm(const QString& sDate, const QString& eDate)
{
    this->sDate = sDate;
    this->eDate = eDate;
}

const QString& WorkTerm::getSDate() const
{ return this->sDate; }

const QString& WorkTerm::getEDate() const
{ return this->eDate; }

void WorkTerm::setSDate(const QString& sDate) {
    this->sDate = sDate;
}

void WorkTerm::setEDate(const QString& eDate) {
    this->eDate = eDate;
}


