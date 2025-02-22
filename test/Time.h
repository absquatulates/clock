// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   madeleine.a.nilsson@liu.se

// Komplettering: Era tester måste gå igenom! Jag missade att anmärka 
// på det vid förra inlämningen, så därför har ni fortfarande möjlighet
// att få bonusen för endast en komplettering

#ifndef TIME_H
#define TIME_H

#include <string>

class Time
{
public:

    //Konstruktorer
    Time();
    Time(int const h, int const m, int const s);
    Time(std::string const& time_string);

    //Funktioner
    std::string to_string(bool us = false) const;
    bool is_am() const;
    int get_hour() const;
    int get_minute() const;
    int get_second() const;

    void log_time();
    

    //Operatorer
    Time& operator++();
    Time operator++(int);
    Time& operator--();
    Time operator--(int);

    bool operator<(Time const& rhs) const;
    bool operator>(Time const& rhs) const;
    bool operator<=(Time const& rhs) const;
    bool operator>=(Time const& rhs) const;
    bool operator==(Time const& rhs) const;
    bool operator!=(Time const& rhs) const;

    //Bonus
    Time operator+(int const& i);
    Time operator-(int const& i);
    Time& operator+=(int const& i);
    Time& operator-=(int const& i);


private:

    int hour {};
    int minute {};
    int second {};

    void check_time() const;
};

std::ostream& operator<<(std::ostream& os, Time const& rhs);
std::istream& operator>>(std::istream& is, Time & rhs);

//KOMMUTATIVITET
Time operator+(int const& i, Time const& time);




#endif