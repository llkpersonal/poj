#include <cstdio>
#include <string>
#include <map>
using namespace std;

string haab_months[] = {"pop", "no", "zip", "zotz",
    "tzec", "xul", "yoxkin", "mol",
    "chen", "yax", "zac", "ceh",
    "mac", "kankin", "muan", "pax", "koyab", "cumhu"};

string tzolkin_months[] = {"imix", "ik", "akbal", "kan", "chicchan",
    "cimi", "manik", "lamat", "muluk", "ok",
    "chuen", "eb", "ben", "ix", "mem",
    "cib", "caban", "eznab", "canac", "ahau"};

map<string, int> month_number;

struct HaabDate{
    int number_of_the_day;
    string month;
    int year;
};

struct TzolkinDate{
    int number;
    int name_of_the_day_index;
    int year;
};

TzolkinDate convertHaabDateToTzolkinDate(HaabDate& date) {
    TzolkinDate t_date;
    int month_day = getMonthDay(getMonthNumber(date.month));
    int total_day = date.year * 365 + month_day + date.number_of_the_day;
    t_date.year = total_day / 260;
    total_day %= 260;
    t_date.name_of_the_day_index = total_day % 20;
    t_date.number = total_day % 13 + 1;
    return t_date;
}

int getMonthDay(int month_number) {
    return month_number * 20;
}

int getMonthNumber(const string& month) {
    if(month_number.find(month) == month_number.end()) return 18;
    return month_number[month];
}

void inputHaabDate(HaabDate& date) {
    char buff[100];
    scanf("%d. %s %d", &date.number_of_the_day, buff, &date.year);
    date.month = string(buff);
}

void init() {
    for(int i = 0; i < 18; i++) {
        month_number[haab_months[i]] = i;
    }
}

void outputTzolkinDate(TzolkinDate& date) {
    printf("%d %s %d\n", date.number,
           tzolkin_months[date.name_of_the_day_index].c_str(), date.year);
}

int main() {
    init();
    int n;
    scanf("%d", &n);
    printf("%d\n", n);
    HaabDate haab_date;
    for(int i = 0; i < n; i++) {
        inputHaabDate(haab_date);
        TzolkinDate t_date = convertHaabDateToTzolkinDate(haab_date);
        outputTzolkinDate(t_date);
    }
    return 0;
}
