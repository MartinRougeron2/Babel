/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** security.cpp
*/

#include "security.hpp"

boost::array<std::bitset<6>, max_length> security::encoder(std::string data)
{
    boost::array<std::bitset<6>, max_length> payload;

    std::cout << "ENCODED: " << std::endl;
    for (std::size_t i = 0; i < data.size(); i++) {
        payload[i] = (std::bitset<6>(data.c_str()[i]));
        std::cout << std::bitset<6>(data.c_str()[i]) << std::endl;
    }

    return (payload);
}

std::string security::decoder(boost::array<std::bitset<6>, max_length> data)
{
    char tmp;
    char previous;
    std::vector<char> dump;
    std::map<char, char> replace = {
        { '{', ';' },
        { '`', ' ' }
    };

    std::cout << "DECODED: " << std::endl;
    for (std::size_t i = 0; data[i] != security::limit && i < max_length; i++) {
        tmp = static_cast<char>(std::bitset<6>(data[i]).to_ulong() + 64);

        if (replace.find(tmp) != replace.end())
            tmp = replace[tmp];
        if (tmp == 'o' && previous == ';')
            tmp = '/';
        previous = tmp;
        dump.push_back(tmp);
    }
    std::string payload(dump.begin(), dump.end());
    std::cout << payload << std::endl;

    return (payload);
}

std::size_t security::get_size(boost::array<std::bitset<6>, max_length> data)
{
    std::size_t size = 0;

    for (std::size_t i = 0; data[i] != security::limit && i < max_length; i++, size++) {
        std::cout << data[i] << std::endl;
    }

    return (size);
}

void security::display(boost::array<std::bitset<6>, max_length> data)
{
    for (std::size_t i = 0; data[i] != security::limit && i < max_length; i++) {
        std::cout << data[i] << std::endl;
    }
}