#include <iostream>

#include <thread>
#include <Poco/NObserver.h>
#include <Poco/Notification.h>
#include <Poco/NotificationCenter.h>
#include <Poco/Observer.h>
// #include <boost/current_function.hpp>
// #include <boost/timer/timer.hpp>
#include <chrono>
#include <fmt/format.h>
#include <pqxx/pqxx>
#include <mutex>
#include <string>

const std::string host{"erdb-integration.cksefz1vwqmf.us-east-1.rds.amazonaws.com"};
const std::string port{"5432"};
const std::string db{"erUAT"};
const std::string user{"dataadmin"};
const std::string password{"RiskAdmin"};

int var{0};
std::mutex m;
using namespace std::chrono_literals;

class Notification : public Poco::Notification
{
};

struct Target
{
    void
    handleNotification(const Poco::AutoPtr<Notification>& pNotification)
    {
        std::lock_guard <std::mutex> l(m);
        var++;
        // std::cout << std::this_thread::get_id() << '\t' << BOOST_CURRENT_FUNCTION << std::endl;
    }

};

void notificationTest()
{
    auto& nc = Poco::NotificationCenter::defaultCenter();

    Target target;
    nc.addObserver(Poco::NObserver<Target, Notification>(target, &Target::handleNotification));

    std::thread t([&]() {
        std::this_thread::sleep_for(5s);
        std::cout << "First sleep" << std::endl;
            std::cout << std::this_thread::get_id() << std::endl;
        nc.postNotification(new Notification());
        std::this_thread::sleep_for(2s);
        std::cout << "Done Sleeping" << std::endl;
    });

    std::cout << "-----" << std::endl;

    std::thread t2([&](){
            
            std::this_thread::sleep_for(1s);
            std::cout << std::this_thread::get_id() << std::endl;
            std::cout << "*****" << std::endl;
            std::this_thread::sleep_for(1s);
            std::cout << "*****" << std::endl;

            std::this_thread::sleep_for(1s);
            std::cout << "*****" << std::endl;

            std::this_thread::sleep_for(1s);
            std::cout << "*****" << std::endl;

            nc.postNotification(new Notification());
            std::this_thread::sleep_for(1s);
            std::cout << "*****" << std::endl;

            std::this_thread::sleep_for(1s);
            std::cout << "*****" << std::endl;

            nc.postNotification(new Notification());
            std::this_thread::sleep_for(1s);
            std::cout << "*****" << std::endl;

        });
    t.join();
    t2.join();

    std::cout << "Var: " << var << std::endl;
}

void
formatTest()
{
    // std::string s = "surya";
    auto s = fmt::format(R"(abc "def" {})", 10);
    std::cout << s << std::endl;
}

int
main(void)
{
    // notificationTest();
    formatTest();
    return 0;
}
