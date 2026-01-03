/* Implement a matching order engine (an order book) that matches buy orders against sell orders and vice versa. 
If there is an incoming order, it should be matched to a resting order, an order already stored. The selling orders
should be matched agaist best bids and the buying order should be matched against best asks. The adding and 
removal of orders should be logaritmic.*/
#include <map>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cmath>

class BookOrder{
    public:
        enum Side{
            BUY,
            SELL
        };

        struct Order
        {
            size_t id;
            size_t priceLimit;
            size_t quantity;
            Side side;

            Order(size_t i, size_t p, size_t q, Side s): id(i), 
            priceLimit(p), quantity(q), side(s){}
        };

        struct Trade{
            size_t incomingOrderID;
            size_t restingOrderID;
            size_t price;
            size_t quantity;

            Trade(size_t inId, size_t resId, size_t p, size_t q):incomingOrderID(inId), 
            restingOrderID(resId), 
            price(p),
            quantity(q){}
        };

        void bookOrder(Order& incomingOrder, std::vector<Trade>& trades)
        {
            if (incomingOrder.side == Side::BUY)
            {
                matchBuyOrder(incomingOrder, trades);
                if (incomingOrder.quantity > 0)
                {
                    if (m_bids.find(incomingOrder.priceLimit) == m_bids.end())
                    {
                        std::queue<Order> tmp;
                        tmp.push(incomingOrder);
                        m_bids[incomingOrder.priceLimit] = tmp;

                    }
                    else
                    {
                        m_bids[incomingOrder.priceLimit].push(incomingOrder);
                    }
                }
            }
            else
            {
                matchSellOrder(incomingOrder, trades);
                if (incomingOrder.quantity > 0)
                {
                    if (m_asks.find(incomingOrder.priceLimit) == m_asks.end())
                    {
                        std::queue<Order> tmp;
                        tmp.push(incomingOrder);
                        m_asks[incomingOrder.priceLimit] = tmp;

                    }
                else
                    {
                        m_asks[incomingOrder.priceLimit].push(incomingOrder);
                    }
                }
            }
        }

        void matchBuyOrder(Order& buyOrder, std::vector<Trade>& trades)
        {
            for( auto it= m_asks.begin(); it != m_asks.end() && buyOrder.quantity > 0; ++it)
            {
                if (it->first > buyOrder.priceLimit)
                    break;

                auto& curQue = it->second;
                while (buyOrder.quantity > 0 && !curQue.empty())
                {
                    auto& curAsk = curQue.front();
                    auto dealtQuantity = std::min(curAsk.quantity, buyOrder.quantity);
                    curAsk.quantity -= dealtQuantity;
                    buyOrder.quantity -= dealtQuantity;
                    trades.emplace_back(buyOrder.id, curAsk.id, curAsk.priceLimit, dealtQuantity);
                    if (curAsk.quantity == 0)
                        curQue.pop();
                }

                if(curQue.empty())
                {
                    m_asks.erase(it);
                    it = m_asks.begin(); // update iterator because after removal, it is not valid anymore
                }
            }
        }

         void matchSellOrder(Order& sellOrder, std::vector<Trade>& trades)
        {
            for( auto it= m_bids.begin(); it != m_bids.end() && sellOrder.quantity > 0; ++it)
            {
                if (it->first < sellOrder.priceLimit)
                    return;
                
                auto& curQue = it->second;
                while (sellOrder.quantity > 0 && !curQue.empty())
                {
                    auto& curBid = curQue.front();
                    auto dealtQuantity = std::min(curBid.quantity, sellOrder.quantity);
                    trades.emplace_back(sellOrder.id, curBid.id, curBid.priceLimit, dealtQuantity);
                    curBid.quantity -= dealtQuantity;
                    sellOrder.quantity -= dealtQuantity;
                    
                    if (curBid.quantity == 0)
                        curQue.pop();
                }

                if (m_bids.empty())
                {
                    m_bids.erase(it);
                    it = m_bids.begin();
                }
            }
        }


    private:
        std::map<size_t, std::queue<Order>> m_asks;
        std::map<size_t, std::queue<Order>, std::greater<size_t>> m_bids;
};


int main()
{
    BookOrder::Order sellorder1(1, 50, 20, BookOrder::Side::SELL);
    BookOrder::Order sellorder2(2, 52, 50, BookOrder::Side::SELL);
    BookOrder::Order sellorder3(3, 49, 80, BookOrder::Side::SELL);

    BookOrder::Order buyorder1(1, 60, 20, BookOrder::Side::BUY);
    BookOrder::Order buyorder2(2, 55, 50, BookOrder::Side::BUY);
    BookOrder::Order buyorder3(3, 50, 80, BookOrder::Side::BUY);

    BookOrder bookOrder;
    std::vector<BookOrder::Trade> trades;
    bookOrder.bookOrder(sellorder1, trades);
    bookOrder.bookOrder(sellorder2, trades);
    bookOrder.bookOrder(sellorder3, trades);

    bookOrder.bookOrder(buyorder1, trades);
    bookOrder.bookOrder(buyorder2, trades);
    bookOrder.bookOrder(buyorder3, trades);

    for (auto& trade: trades)
    {
        std::cout<<"incomingId: "<<trade.incomingOrderID<<", restingID: " <<trade.restingOrderID<<", price: "<<trade.price<<", quantitiy: "<<trade.quantity<<"\n";
    }

    return 0;
}

/**
 * queue/deque are prefered over list because pushes and pops are faster; it avoids costly 
 *  allocations and their memory layout are more cache friendly.  
 * 
 * map uses a self-balancing tree garanting that insert and remove have logarithmic time complixity but it is
 * not cache friendly as it uses non-contiguous memory layout. In addition, it benefits from the ordered keys to
 * find the best possible resting orders. For more efficiency we can use a std::flat_map or the ones having the
 * contigeuous memory layout. 
 */