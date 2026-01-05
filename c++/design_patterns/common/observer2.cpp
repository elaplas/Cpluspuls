/* When there are a set of elements (data structures that are usually fixed) and new operation on data structures 
might be needed in the future. For example in trading there is a stream of data like quote, trade and we want 
to display them, or analyse them, ...*/

#include <iostream>

struct Quote;
struct Trade;


class Visitor{
    public:
        virtual void visit(Quote& q) = 0;
        virtual void visit(Trade& t) = 0;
};

struct Element{
    virtual void accept(Visitor& v) = 0;
};


struct Quote: Element{
    int id;
    float bid;
    float ask;
    int quantity;
    void accept(Visitor& v){ v.visit(*this);};
};

struct Trade: Element{
    int buyId;
    int sellId;
    int dealtPrice;
    int DealtQuantity;
    void accept(Visitor& v){v.visit(*this);}
};


class Print: public Visitor{
    public:
        virtual void visit(Quote& q)
        {
            std::cout<<q.id<<"\n";
        }
        virtual void visit(Trade& t)
        {
            std::cout<<t.buyId<<"\n";
            std::cout<<t.sellId<<"\n";
        }
};


class Analysis: public Visitor{
    public:
        virtual void visit(Quote& q)
        {
            q.ask *= q.ask;
        }
        virtual void visit(Trade& t)
        {
            t.dealtPrice *= t.dealtPrice;
        }
};

void handel(Element& el, Visitor& v) // implicit static cast: derived calss ---> base class 
{
    
    el.accept(v); // virtual dispatch: accept() refers to Quote.accept or Trade.accept
}

int main()
{
    Quote q;
    q.id=5;
    Print p;

    handel(q, p);

    return 0;
}
