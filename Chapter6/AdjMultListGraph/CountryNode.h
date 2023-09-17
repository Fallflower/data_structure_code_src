/*
 * @Author: Metaphor
 */
#ifndef __COUNTRYNODE_H_
#define __COUNTRYNODE_H_
//#pragma execution_character_set("utf-8")
#include<iostream>
#include<string>
using namespace std;


struct CountryNode
{
    string name;
    int population;

    CountryNode(string Name = "Noname", int p = 0) : name(Name), population(p){}
    CountryNode(const CountryNode &copy)
    {
        name = copy.name;
        population = copy.population;
    }

    CountryNode &operator=(const CountryNode &copy)
    {
        name = copy.name;
        population = copy.population;
        return (*this);
    }

    istream &Input(istream &in)
    {
        in >> name >> population;
        return in;
    }
    ostream &Output(ostream &out) const
    {
        out << "村名: " << name << "\t人口: " << population;
        return out;
    }
};

istream& operator>>(istream& in, CountryNode& c)
{
    c.Input(in);
    return in;
}

ostream& operator<<(ostream& out, const CountryNode& c)
{
    c.Output(out);
    return out;
}

#endif