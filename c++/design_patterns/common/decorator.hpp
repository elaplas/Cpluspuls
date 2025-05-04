
//Decorator Pattern
//Purpose: Adds new responsibilities to objects dynamically without altering their structure.
//Use case: UI toolkits, middleware frameworks, stream handling (like Java I/O).
//Benefit: Supports open/closed principle (open for extension, closed for modification).

#include <iostream>
#include <memory>


class EmailNotifier{
public:
    virtual void send()
    {
        std::cout<<"Email notification\n";
    }
};

class SmsNotifier: public EmailNotifier{
private:
    std::unique_ptr<EmailNotifier> m_emailNotifier;

public:
    SmsNotifier(std::unique_ptr<EmailNotifier>&& emailNotifier):
    m_emailNotifier(std::move(emailNotifier))
    {   
    }

    virtual void send() override 
    {
        m_emailNotifier.get()->send();
        std::cout<<"Sms notification\n";
    }
};



class TeamsNotifiier: public SmsNotifier{
private:
    std::unique_ptr<SmsNotifier> m_smsNotifier;

public:
    TeamsNotifiier(std::unique_ptr<EmailNotifier>&& emailNotifier, 
    std::unique_ptr<SmsNotifier>&& smsNotifier):
    SmsNotifier(std::move(emailNotifier)),
    m_smsNotifier(std::move(smsNotifier))
    {   
    }

    virtual void send() override 
    {
        m_smsNotifier.get()->send();
        std::cout<<"teams notification\n";
    }
};

int main()
{   
    TeamsNotifiier teamsNotifier(std::unique_ptr<EmailNotifier>(new EmailNotifier),
    std::unique_ptr<SmsNotifier>(new SmsNotifier(std::unique_ptr<EmailNotifier>(new EmailNotifier))));
    teamsNotifier.send();
    return 0;
}