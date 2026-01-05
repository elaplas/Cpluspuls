// Observer design patterns enables loose coupling and it is used to allow one object (subject)
// notify other objects (observers) about changes in its state. 
// This is static design avoiding virtual dispatch cost (the cost caused by looking for the fucntion calls in the 
// virtuall table ). It is used in highly efficient codes

#include <iostream>
#include <set>

template<class Policy>
class Handel{
    public:
    using TElement = typename Policy::Type;
    using TVisitor = typename Policy::Visitor; 

    void visit(TElement& element)
    {
        m_visitor.visit(element);
    }

    private:
       TVisitor m_visitor; 
};

struct Quote{
    int id;
    float bid;
    float ask;
    int quantity;
};

struct Trade{
    int buyId;
    int sellId;
    int dealtPrice;
    int DealtQuantity;
};

class Print{
    public:
        virtual void visit(Quote& q)
        {
            std::cout<<q.id<<"\n";
        }
};


class Analysis{
    public:
        virtual void visit(Quote& q)
        {
            q.ask *= q.ask;
        }
};

struct Policy1{
    using Type = Quote;
    using Visitor = Print;
}

struct Policy2{
    using Type = Trade;
    using Visitor = Analysis;
}



int main()
{
    Handel<Policy1> handel1;
    Handel<Policy2> handel1;

    return 0;
}