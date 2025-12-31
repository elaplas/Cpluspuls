/*
The following is a sequential workflow: parse, validate and compute an stream of lines line-by-line. How
you can increase the performance (throughput) of the code?
*/

std::string parse(std::string str)
{
    return str + "_parsed";
}

bool validate(std::string& str)
{
    if (str.size() > 5)
    {
        str = str + "_validated";
        return true;
    }
    
    return false;
}

std::string compute(std::string str)
{
    return str + "_computed";
}

void sequential_workflow(std::vector<std::string> lines)
{
    for (auto& line: lines)
    {
        auto parsed = parse(line);
        if (validate(parsed))
        {
            auto computed = compute(parsed);
            std::cout<<computed<<"\n";
        }
    }
}

/* pipilned workflow: parse, validate and compute lines in parallel. For example while the first line is being 
validated, the second line is parsed increasing the throughput(number of lines proccessed per milli second).
Because we have a producer and consumption relation between tasks and need to synch the workflow, we can use 
two thread-safe queues. One is used by parser and validator and the other by the validator and computer. 
*/
template<class T>
class ThreadQueue
{
    public:

        ThreadQueue(): m_done(false){}
        void push(const T& value)
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            m_que.push(value);
            m_cv.notify_one();
        }

        T pop()
        {
            std::unique_lock<std::mutex> ul(m_mutex);
            m_cv.wait(ul, [this]{
                return !m_que.empty() || m_done;});
            if (m_que.empty())
            {
                throw std::runtime_error("queue is empty");
            }
            auto popped = m_que.front();
            m_que.pop();
            return popped;
        }

        void setDone()
        {
            m_done = true;
            m_cv.notify_all();
        }

        bool empty()
        {
            std::lock_guard<std::mutex> lg(m_mutex);
            return m_que.empty();
        }

        ~ThreadQueue()
        {
            m_done = true;
            m_cv.notify_all();
        }

    private:
        std::condition_variable m_cv;
        std::queue<T> m_que;
        std::mutex m_mutex;
        bool m_done;
};

class PipelinedWorkflow{
    public:
        void parser(std::vector<std::string> lines)
        {
            for (auto& line: lines)
            {
                auto parsed = parse(line);
                m_q1.push(parsed);
            }
            m_q1.setDone();
        }

        void validator()
        {
            while (true)
            {
                try{
                    auto popped = m_q1.pop();
                    if (validate(popped))
                    {
                        m_q2.push(popped);
                        if (m_q1.empty())
                        {
                            m_q2.setDone();
                        }
                    }
                }
                catch(std::runtime_error rte)
                {
                    std::cout<<rte.what()<<"\n";
                    break;
                }
            }
        }

        void computer()
        {
            while(true)
            {
                try{
                    auto popped = m_q2.pop();
                    auto computed = compute(popped);
                    std::cout<<computed<<"\n";
                }
                catch(std::runtime_error rte)
                {
                    std::cout<<rte.what()<<"\n";
                    break;
                }
            }
        }

        void process(std::vector<std::string>& vec)
        {
            std::thread t1(&PipelinedWorkflow::parser, this, vec);
            std::thread t2(&PipelinedWorkflow::validator, this);
            std::thread t3(&PipelinedWorkflow::computer ,this);

            t1.join();
            t2.join();
            t3.join();
        }
    
    private:
       ThreadQueue<std::string> m_q1; 
       ThreadQueue<std::string> m_q2; 
};

int main() {
    
    std::vector<std::string> lines{"abc", "def", "ghi", "ebi", "sara", "damoon"};

    std::cout<<"......................sequential.....................\n";
    //sequential_workflow(lines);
    std::cout<<"......................parallel.....................\n";
    PipelinedWorkflow pipelinedWF;
    pipelinedWF.process(lines);
    
    
    return 0;
}