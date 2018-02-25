#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

struct IpV4_Address {
    std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>
        data_;

     IpV4_Address(const std::string& strAddress = "") {
        std::vector<std::string> result;

        boost::algorithm::split(result, strAddress, boost::is_any_of(". ")); 

        if (result.size() == 4) {
            data_ = std::make_tuple(boost::lexical_cast<short>(result[0]),
                                    boost::lexical_cast<short>(result[1]),
                                    boost::lexical_cast<short>(result[2]),
                                    boost::lexical_cast<short>(result[3]));
        }
    }

   bool operator>(const IpV4_Address& rhs) const {
       return this->data_ > rhs.data_;
   }

   std::string to_string() const {
       return boost::lexical_cast<std::string>(static_cast<short>(std::get<0>(data_))) + "." +
           boost::lexical_cast<std::string>(static_cast<short>(std::get<1>(data_))) + "." +
           boost::lexical_cast<std::string>(static_cast<short>(std::get<2>(data_))) + "." +
           boost::lexical_cast<std::string>(static_cast<short>(std::get<3>(data_)));
   }

};

std::istream& operator>>(std::istream& is, IpV4_Address& rhs) {
    std::string str;
   
    is >> str;
    rhs = str;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const IpV4_Address& rhs) {
    os << rhs.to_string() << std::endl;
    return os;
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<IpV4_Address> ip_pool{std::istream_iterator<IpV4_Address>(std::cin),
            std::istream_iterator<IpV4_Address>()};

        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<IpV4_Address>());

        for (const auto& el : ip_pool) {
            std::cout << el.to_string() << std::endl;
        }

        std::copy_if(ip_pool.begin(), ip_pool.end(), std::ostream_iterator<IpV4_Address>(std::cout),
                [](auto elem) { return std::get<0>(elem.data_) == 1; });

        std::copy_if(ip_pool.begin(), ip_pool.end(), std::ostream_iterator<IpV4_Address>(std::cout),
                [](auto elem) { return std::get<0>(elem.data_) == 46 && std::get<1>(elem.data_) == 70; });

        std::copy_if(ip_pool.begin(), ip_pool.end(), std::ostream_iterator<IpV4_Address>(std::cout),
                [](auto elem) { return std::get<0>(elem.data_) == 46 || 
                                       std::get<1>(elem.data_) == 46 ||
                                       std::get<2>(elem.data_) == 46 ||
                                       std::get<3>(elem.data_) == 46; });

   }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
